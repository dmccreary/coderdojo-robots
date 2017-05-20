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
*/

// change these numbers until you get right forward, right backward, left forward, left reverse
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;

int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 1000; // delay between tests
int delay_end_of_test= 3000; // delay between tests

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
  // for debugging.  The output will appear on the serial monitor
  // To open the serial monitor, click the magnafing glass icon in the upper right corner
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop() {
  Serial.println("Right Forward Test");
  digitalWrite(right_forward, HIGH);
  delay(delay_time_on);
  digitalWrite(right_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Right reverse test");
  digitalWrite(right_reverse, HIGH);
  delay(delay_time_on);
  digitalWrite(right_reverse, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Forward Test");
  digitalWrite(left_forward, HIGH);
  delay(delay_time_on);
  digitalWrite(left_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Reverse Test");
  digitalWrite(left_reverse, HIGH);
  delay(delay_time_on);
  digitalWrite(left_reverse, LOW);
  
  delay(delay_end_of_test);
}
