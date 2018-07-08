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
#include <NewPing.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// this has the sound pitches
// #include "pitches.h"
#define NOTE_C3  131
#define NOTE_C4  262
#define NOTE_C5  523
#define NOTE_C6  1047
#define NOTE_C7  2093
#define NOTE_C8  4186

// If using software SPI (the default case):
#define OLED_CLK   13   // SCL
#define OLED_MOSI  12   // SDA
#define OLED_RESET 11   // RST
#define OLED_DC    10   // DC
#define OLED_CS    8    //CS

#define LEFT_TRIGGER_PIN    A0  // Arduino pin tied to trigger pin on the left ultrasonic sensor.
#define LEFT_ECHO_PIN       A1  // Arduino pin tied to echo pin on the left ultrasonic sensor.
#define CENTER_TRIGGER_PIN  A2
#define CENTER_ECHO_PIN     A3
#define RIGHT_TRIGGER_PIN   A4
#define RIGHT_ECHO_PIN      A5
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar_left(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_center(CENTER_TRIGGER_PIN, CENTER_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_right(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);

// define pins going to the motor controller - must be PWM pins
#define RIGHT_FORWARD_PIN 3
#define RIGHT_REVERSE_PIN 5
#define LEFT_FORWARD_PIN 9
#define LEFT_REVERSE_PIN 6

// put a speaker piezoelectric disk between this pin and ground.  
#define SPEAKER_PIN 2

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int left_dist = 0;
int center_dist =  0;
int right_dist =  0;

int counter = 0;
int half_width = 0;
// these might be changed
int turn_delay_time = 400;
int reverse_delay_time = 500; // backup for 1/2 second
// must be a value from 150 to 255 - higher will be a faster turn speed
int power_turn_level = 200;
int power_forward_right = 200;
int power_forward_left = 200;
int note_delay_time = 400;
int turn_distance_threshold = 12; // distance to trigger turn in cm

void setup()   {
  // Set the PWM motor pins as OUTPUTs
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  //
  pinMode(SPEAKER_PIN, OUTPUT);
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
  Serial.begin(9600);
  motor_connection_test();
}

void loop()
{
  left_dist = sonar_left.ping_cm();
  center_dist =  sonar_center.ping_cm();
  right_dist =  sonar_right.ping_cm();

  display.clearDisplay();
  // we have 64 pixels to work with
  display.setCursor(0,0);
  display.print("L:");
  display.setCursor(10,0);
  display.print(left_dist);

  display.setCursor(0,10);
  display.print("M:");
  display.setCursor(10,10);
  display.print(center_dist);


  display.setCursor(0,20);
  display.print("R:");
  display.setCursor(10,20);
  display.print(right_dist);
  
  // yes, we are doing digital reads on analog ports!
  Serial.print("Left: ");
  Serial.print(left_dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(" middle: ");
  Serial.print(center_dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(" right: ");
  Serial.println(right_dist); // Send ping, get distance in cm and print result (0 = outside set distance range)  
  
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
  if (left_dist < turn_distance_threshold && left_dist > 0) {
    display.setCursor(0,30);
    display.print("Right");
    // look to right
    // erase forward eyes
    display.fillCircle(half_width - 10, display.height()/3, 4, WHITE);
    display.fillCircle(half_width + 10, display.height()/3, 4, WHITE);
    // draw new eyes
    display.fillCircle(half_width - 15, display.height()/3, 4, BLACK);
    display.fillCircle(half_width + 5, display.height()/3, 4, BLACK);
    display.display();
    tone(SPEAKER_PIN, NOTE_C4, note_delay_time);
    turn_left(turn_delay_time);
  };

  // LOW means there is an object in front of us
  if (center_dist < turn_distance_threshold && center_dist > 0) {
    display.setCursor(0,40);
    display.print("Center");
    // erase streight mouth
    display.drawLine(half_width - 10, display.height()/3 * 2, half_width + 10, display.height()/3 * 2, WHITE);
    // draw round mouth half width and 2/3 down
    display.fillCircle(half_width, display.height()/3 * 2, 5, BLACK);
    display.display();
    move_reverse();
    delay(reverse_delay_time);
    tone(SPEAKER_PIN, NOTE_C5, note_delay_time);
    if (random(1,3) > 1)
      turn_right(turn_delay_time);
      else turn_left(turn_delay_time);
  };

  // LOW means there is an object to the left
  if (right_dist > turn_distance_threshold && right_dist > 0) {
    display.setCursor(0,50);
    display.print("Left");
    // erase forward eyes
    display.fillCircle(half_width - 10, display.height()/3, 4, WHITE);
    display.fillCircle(half_width + 10, display.height()/3, 4, WHITE);
    // draw new eyes
    display.fillCircle(half_width - 5, display.height()/3, 4, BLACK);
    display.fillCircle(half_width + 15, display.height()/3, 4, BLACK);
    display.display();
    tone(SPEAKER_PIN, NOTE_C6, note_delay_time);
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

void stop() {
  Serial.println("stop");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, 0);
}

void motor_connection_test(){
  analogWrite(RIGHT_FORWARD_PIN, 255);
  delay(1000);
  analogWrite(RIGHT_FORWARD_PIN, 0);

  analogWrite(RIGHT_REVERSE_PIN, 255);
  delay(1000);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  
  analogWrite(LEFT_FORWARD_PIN, 255);
  delay(1000);
  analogWrite(LEFT_FORWARD_PIN, 0);

  analogWrite(LEFT_REVERSE_PIN, 255);
  delay(1000);
  analogWrite(LEFT_REVERSE_PIN, 0);

  stop();
}

// take the average of "count" valid values
int average_ping(NewPing this_ping, int count) {
  int sum_valid;
  int dist;
  int valid_readings = 0;
  int average_distance = 0;
  for (int i=1; i<=count; i++) {
       dist = this_ping.ping_cm();
       if (dist > 0 && dist < 100) {
          sum_valid += dist; // add this one in
          valid_readings++; // add total valid readings
//          Serial.print("valid distance=");
//          Serial.println(dist);
       }
//       else {
//          Serial.print("invalid distance=");
//          Serial.println(dist);
//          Serial.print("median msec=");
//          Serial.println(this_ping.ping_median(5)); 
//       };
       delay(35);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    }
    average_distance =  round(sum_valid / valid_readings) + 1;
    //Serial.print("average distance=");
    //Serial.println(average_distance);
    return average_distance;
}
