/* 
 * Drive motors based on three IR distance sensors and update OLED face
 *  
 * Uses SSD1306 based 128x64 monchrome OLED module using Adafruit SSD1306 
 * library (https://github.com/adafruit/Adafruit_SSD1306).
 * 
 * See https://github.com/pacodelgado/arduino/wiki/SSD1306-based-OLED-connected-to-Arduino 
 * for more information.
 *
 */
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_CLK   13   // SCL
#define OLED_MOSI  12   // SDA
#define OLED_RESET 11   // RST
#define OLED_DC    10   // DC
#define OLED_CS    8    //CS

#define RIGHT_IR_PIN A0
#define CENTER_IR_PIN A1
#define LEFT_IR_PIN A2

// define pins going to the motor controller - must be PWM pins
#define RIGHT_FORWARD_PIN 6
#define RIGHT_REVERSE_PIN 9
#define LEFT_FORWARD_PIN 3
#define LEFT_REVERSE_PIN 5

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int counter = 0;
int half_width = 0;
// these might be changed
int turn_delay_time = 400;
int reverse_delay_time = 500; // backup for 1/2 second
// must be a value from 150 to 255 - higher will be a faster turn speed
int power_turn_level = 200;
int power_forward_right = 200;
int power_forward_left = 200;

void setup()   {
  // Set the PWM motor pins as OUTPUTs
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
    // turn all the motors off
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, 0);        
//  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  half_width = display.width()/2; // for a 128 bit wide display this is 64
  display.setCursor(0,0);
  display.print("CoderDojo Face Robot");
  
  display.setCursor(0,12);
  display.print("Version 1");

  display.setCursor(0,24);
  display.print("128x64 OLED $19");

  display.setCursor(0,36);
  display.print("Adafruit SSD1306 SPI");
  
  display.setCursor(0,48);
  display.print("Dan.McCreary@gmail");
  
  display.display();
  // delay(5000); // disply for 5 seconds
}

void loop()
{
  // yes, we are doing digital reads on analog ports!
  int right_sensor_value = digitalRead(RIGHT_IR_PIN);
  int center_sensor_value = digitalRead(CENTER_IR_PIN);
  int left_sensor_value = digitalRead(LEFT_IR_PIN);
  display.clearDisplay();
  // white face background
  display.fillCircle(half_width, display.height()/2, 31, WHITE);
  // right eye black
  display.fillCircle(half_width - 10, display.height()/3, 4, BLACK);
  // left eye black
  display.fillCircle(half_width + 10, display.height()/3, 4, BLACK);
  // streight mouth
  display.drawLine(half_width - 10, display.height()/3 * 2, half_width + 10, display.height()/3 * 2, BLACK);
  display.display();
  
  // LOW means there is an object to the right
  if (right_sensor_value == LOW) {
    display.setCursor(0,0);
    display.print("Right");
    // look to right
    // erase forward eyes
    display.fillCircle(half_width - 10, display.height()/3, 4, WHITE);
    display.fillCircle(half_width + 10, display.height()/3, 4, WHITE);
    // draw new eyes
    display.fillCircle(half_width - 15, display.height()/3, 4, BLACK);
    display.fillCircle(half_width + 5, display.height()/3, 4, BLACK);
    display.display();
    turn_left(turn_delay_time);
  };

  // LOW means there is an object in front of us
  if (center_sensor_value == LOW) {
    display.setCursor(0,10);
    display.print("Center");
    // erase streight mouth
    display.drawLine(half_width - 10, display.height()/3 * 2, half_width + 10, display.height()/3 * 2, WHITE);
    // draw round mouth half width and 2/3 down
    display.fillCircle(half_width, display.height()/3 * 2, 5, BLACK);
    display.display();
    move_reverse();
    delay(reverse_delay_time);
    if (random(2) > 1)
      turn_right(turn_delay_time);
      else turn_left(turn_delay_time);
  };

  // LOW means there is an object to the left
  if (left_sensor_value == LOW) {
    display.setCursor(0,20);
    display.print("Left");
    // erase forward eyes
    display.fillCircle(half_width - 10, display.height()/3, 4, WHITE);
    display.fillCircle(half_width + 10, display.height()/3, 4, WHITE);
    // draw new eyes
    display.fillCircle(half_width - 5, display.height()/3, 4, BLACK);
    display.fillCircle(half_width + 15, display.height()/3, 4, BLACK);
    display.display();
    turn_right(turn_delay_time);
  };

  //display.setCursor(0,54);
  //display.print(counter);
  
  move_forward();
  //delay(100);
  counter++;
}

// turn right for turn_delay_time ms
void turn_right(int turn_delay_time) {
  Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, power_turn_level);
  analogWrite(LEFT_FORWARD_PIN, power_turn_level);
  analogWrite(LEFT_REVERSE_PIN, 0);
  delay(turn_delay_time);
}

void turn_left(int turn_delay_time) {
  Serial.println("turning left");
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(RIGHT_FORWARD_PIN, power_turn_level);
  analogWrite(LEFT_REVERSE_PIN, power_turn_level);
  analogWrite(LEFT_FORWARD_PIN, 0);
  delay(turn_delay_time);
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, power_forward_right);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, power_forward_left);
  analogWrite(LEFT_REVERSE_PIN, 0);
}

void move_reverse() {
  Serial.println("moving reverse");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, power_forward_right);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, power_forward_left);
}


