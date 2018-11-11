/*
Robot Motors Direction Tests
 This test makes sure we get all four of the motor dirction pins correct.
 The program should moves the right wheel forward, right reverse, left forward and left reverse.
 Keep changing these numbers or jumper wires until you get it right directions for each wheel
 Use the serial monitor to verify which one should be working
 Note, On the Arduino Nano, ONLY pins 3,5,6,9,10 and 11 have PWM output.  You must use these to drive the motors.
 See https://www.arduino.cc/en/Main/ArduinoBoardNano
 
 The convention is to use the first four pins (3,5,6,9) for the motor controls
 If you use a ribbon connector the order will be 5,3,6 and 9
 https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
*/

// change these numbers until you get right forward, right backward, left forward, left reverse
// you can only use PWM pins.  On the Arduino Nano these are 3, 5, 6, 9, 10 and 11
// We are going to tuse pin 3 as an interrupt so we can't use it here
#define RIGHT_FORWARD_PIN 5
#define RIGHT_REVERSE_PIN 9
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 10

int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 1000; // delay between tests
int delay_end_of_test= 3000; // delay between tests

void setup() {
  // Turn these pins on for PWM OUTPUT
  // you can use digitalWrite for testing if the PWM pins are not free
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  // turn all the motors off
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, 0);
  // for debugging.  The output will appear on the serial monitor
  // To open the serial monitor, click the magnafing glass icon in the upper right corner
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop() {
  Serial.println("Right Forward Test");
  digitalWrite(RIGHT_FORWARD_PIN, 255);
  delay(delay_time_on);
  analogWrite(RIGHT_FORWARD_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Right reverse test");
  digitalWrite(RIGHT_REVERSE_PIN, 255);
  delay(delay_time_on);
  digitalWrite(RIGHT_REVERSE_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Left Forward Test");
  digitalWrite(LEFT_FORWARD_PIN, 255);
  delay(delay_time_on);
  digitalWrite(LEFT_FORWARD_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Left Reverse Test");
  digitalWrite(LEFT_REVERSE_PIN, 255);
  delay(delay_time_on);
  digitalWrite(LEFT_REVERSE_PIN, 0);
  
  delay(delay_end_of_test);
}
