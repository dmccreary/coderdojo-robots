/*
Robot Motors Direction Tests
 This test makes sure we get all four of the motor dirction pins correct.
 The program moves the right wheel forward, right reverse, left forward and left reverse.
 Keep changing these numbers or jumper wires until you get it right directions for each wheel
 Use the serial monitor to verify which one should be working
 Note, On the Arduino Nano, only pins 3,5,6,9,10 and 11 have PWM output.  You must use these to drive the motors.
 See https://www.arduino.cc/en/Main/ArduinoBoardNano
 
 The convention is to use the first four pins (3,5,6,9) for the motor controls
 If you use a ribbon connector the order will be 5,3,6 and 9
*/

int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;
int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 1000; // delay between tests
int delay_end_of_test= 3000; // delay between tests

int brightness = 100; // 0=off, 255 is full on
#include <Adafruit_NeoPixel.h>
#define LEDPIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12 // the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Turn these pins on for PWM OUTPUT
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  // turn all the motors off
  digitalWrite(right_forward, LOW);
  digitalWrite(right_reverse, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);
  
  // turn on the first (0) red LED to 1/5th brightness
  strip.begin();
  strip.setPixelColor(0, 50, 0, 0);
  strip.show();
  
  // for debugging.  The output will appear on the serial monitor
  // To open the serial monitor, click the magnafing glass icon in the upper right corner
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop() {
  Serial.println("Right Forward Test");
  // turn pixel 2 on
  strip.setPixelColor(1, 0, 0, brightness);
  strip.show();
  digitalWrite(right_forward, HIGH);
  delay(delay_time_on);
  // turn pixel 2 off
  strip.setPixelColor(1, 0, 0, 0);
  strip.show();
  digitalWrite(right_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Right reverse test");
  strip.setPixelColor(2, 0, 0, brightness);
  strip.show();
  digitalWrite(right_reverse, HIGH);
  delay(delay_time_on);
  strip.setPixelColor(2, 0, 0, 0);
  strip.show();
  digitalWrite(right_reverse, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Forward Test");
  strip.setPixelColor(3, 0, 0, brightness);
  strip.show();
  digitalWrite(left_forward, HIGH);
  delay(delay_time_on);
  strip.setPixelColor(3, 0, 0, 0);
  strip.show();
  digitalWrite(left_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Reverse Test");
  strip.setPixelColor(4, 0, 0, brightness);
  strip.show();
  digitalWrite(left_reverse, HIGH);
  delay(delay_time_on);
  strip.setPixelColor(4, 0, 0, 0);
  strip.show();
  digitalWrite(left_reverse, LOW);
  
  delay(delay_end_of_test);
}
