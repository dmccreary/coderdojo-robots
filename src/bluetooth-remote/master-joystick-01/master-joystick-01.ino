#include <SoftwareSerial.h>
/*
Master Joystick program that takes values from Joystick and
converts analog signals into robot commands
*/
const byte rxPin = 10;// Recieve on 10, Transmit on 11
const byte txPin = 11;
SoftwareSerial bt(rxPin, txPin);

int fwd_rev_pin = A0; // connect the forward reverse VR2 (variable resistor 1) to this pin
int left_right_pin = A1; // connect the left right VR1 (variable resistor 2) to this pin
int beep_pin = 7; // connect the push button to the SW pin
int ledPin = 13;      // select the pin for the LED
int fwd_rev_sensor_value = 512;  // idel initial value
int left_right_sensor_value = 512;  // idel initial value
int show_sensor_values_flag = 0; // turn this to 1 to show the sensor values on the console
int moving_threshold = 40; // minimum value to from 512 to move
int moving_flag = 1; // 0 if stopped, 1 is moving

void setup() {
  // declare the inputs
  pinMode(fwd_rev_pin, INPUT);
  pinMode(left_right_pin, INPUT);
  pinMode(beep_pin, INPUT);
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println("Master joystick controller ready to send commands to robot slave via Bluetooth.");
}

void loop() {
  // read the sensor values
  fwd_rev_sensor_value = 1023 - analogRead(fwd_rev_pin);  // we use the inverse with connectors to the left
  left_right_sensor_value = analogRead(left_right_pin);

  // useful for debugging
  if (show_sensor_values_flag == 1) {
    show_sensor_values();
  }
  
  // we can't use a case statement because we are doing range comparisons
  if (left_right_sensor_value > 512 + moving_threshold) {
    moving_flag = 1;
    Serial.print("right ");
    calc_speed(left_right_sensor_value);
  }
  
  else if (left_right_sensor_value < 512 - moving_threshold) {
    moving_flag = 1;
    Serial.print("left ");
    calc_speed(left_right_sensor_value);
  }
  
  else if (fwd_rev_sensor_value > 512 + moving_threshold) {
    moving_flag = 1;
    Serial.print("forward ");
    calc_speed(fwd_rev_sensor_value);
  }
  
  else if (fwd_rev_sensor_value > 512 + moving_threshold && fwd_rev_sensor_value < 512 - moving_threshold) {
     moving_flag = 0;
     // Serial.println("stop");
  }
  
  else if (fwd_rev_sensor_value < 512 - moving_threshold) {
     moving_flag = 1;
     Serial.print("reverse ");
     calc_speed(fwd_rev_sensor_value);
  }
  delay(100);
}

void calc_speed(int sensor_value) {
  Serial.print("speed=");
  Serial.println(abs(sensor_value - 512));
}

void show_sensor_values() {
  Serial.print("fwd-rev val =");
  Serial.print(fwd_rev_sensor_value);
  Serial.print(" left-right val =");
  Serial.println(left_right_sensor_value);
}
