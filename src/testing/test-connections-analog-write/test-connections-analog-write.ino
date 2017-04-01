/*
Test that two motors can be driven both forward and reverse using PWM pins.
This runs the right motor forward for two seconds, then reverse.
Then the left motor moves forward, then reverse.
*/

int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;
int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 2000; // delay between tests
int power_level = 250;

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
  analogWrite(right_forward, power_level);
  delay(delay_time_on);
  analogWrite(right_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Right Reverse test");
  analogWrite(right_reverse, power_level);
  delay(delay_time_on);
  analogWrite(right_reverse, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Forward Test");
  analogWrite(left_forward, power_level);
  delay(delay_time_on);
  analogWrite(left_forward, LOW);
  delay(delay_time_off);
  
  Serial.println("Left Reverse Test");
  analogWrite(left_reverse, power_level);
  delay(delay_time_on);
  analogWrite(left_reverse, LOW);
  delay(delay_time_off);
}
