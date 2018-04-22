#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define IR_SENSOR_PIN A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define MODE_BUTTON_PIN 2 // momentary push button to GNG

// motor pins
#define RIGHT_FORWARD_PIN 3
#define RIGHT_REVERSE_PIN 5
#define LEFT_FORWARD_PIN 9
#define LEFT_REVERSE_PIN 6

#define LEDPIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12
// the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// not using the reset...
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int turn_sensor_value = 400; //threshold for IR sensor 
const int forward_power_level = 180; // try a number from 100 to 255 for 4 AA batteries forard motors PWM on signal

const int turn_power_level = 200; // power while turning
const int turn_delay = 700; // time to turn in milliseconds 

// global variables
int sensor_value = 0;
int distance = 0;
int counter = 0;

void setup() {
  // Turn these pins on for PWM OUTPUT
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  // turn all the motors off
  digitalWrite(RIGHT_FORWARD_PIN, LOW);
  digitalWrite(RIGHT_REVERSE_PIN, LOW);
  digitalWrite(LEFT_FORWARD_PIN, LOW);
  digitalWrite(LEFT_REVERSE_PIN, LOW);

  // configure the button pin D2 for interrupt input
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP); // floats high, pull down to GND to change mode
  strip.begin();
  flash_led_test();
  delay(300);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  Serial.begin(9600);
}

void loop () {
    sensor_value = analogRead(IR_SENSOR_PIN);
    distance = distance_cm();
    display.clearDisplay();
    // 10 over (x) 20 down (y)
    display.setCursor(10, 20);
    display.print(sensor_value);
    display.setCursor(10, 40);
    display.print(distance);
    display.display();

    if (sensor_value > turn_sensor_value) {
      set_led_red();
      turn_right();
    } else {
      set_led_green();
      move_forward();
    }
    
     
    delay(100);
    counter++;
}

// take the average of "count" valid values
int average_sensor(int count) {
  int sum_valid;
  int dist;
  int valid_readings = 0;
  int average_distance = 0;
  for (int i=1; i<=count; i++) {
       dist = distance_cm();
       if (dist != 0 && dist < 1000) {
          sum_valid += dist; // add this one in
          valid_readings++; // add total valid readings
//          Serial.print("valid distance=");
//          Serial.println(dist);
       }
       else {
          Serial.print("invalid distance=");
          Serial.println(dist); 
       };
       delay(50);  // Wait 50ms between measurements
    }
    average_distance =  round(sum_valid / valid_readings) + 1;
    Serial.print("average distance=");
    Serial.println(average_distance);
    return average_distance;
}

int distance_cm() {
  float volts = analogRead(IR_SENSOR_PIN)*0.0048828125;  // value from sensor * (5/1024)
  return 13*pow(volts, -1);
}

void clear_strip() {
   for (int i=0; i < NUMBER_PIXELS; i++)
      strip.setPixelColor(i, 0, 0, 0);
   strip.show();
}

void set_led_red() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 25, 0, 0);
   strip.show();
}

void set_led_green() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 40, 0);
   strip.show();
}

void set_led_blue() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 50);
   strip.show();
}

void flash_led_test() {
  strip.setPixelColor(0, 50, 0, 0); // red
  strip.setPixelColor(1, 50, 25, 0); // orange
  strip.setPixelColor(2, 50, 50, 0); // yellow
  strip.setPixelColor(3, 0, 50, 0); // green
  strip.setPixelColor(4, 0, 0, 50); // blue
  strip.setPixelColor(5, 30, 0, 50); // indigo
  strip.setPixelColor(6, 10, 0, 5); // violet
  strip.setPixelColor(NUMBER_PIXELS - 1, 100, 100, 100); // set last pixel to white
  strip.show(); 
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, forward_power_level);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, forward_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}

void turn_right() {
  Serial.println("turning right");
  set_led_red();
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
  // all motors off
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}
