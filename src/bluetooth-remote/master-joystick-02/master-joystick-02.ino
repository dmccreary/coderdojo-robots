#include <SoftwareSerial.h>
/*
Master Joystick program that takes values from Joystick and
converts analog signals into robot commands
This version sends a stream of comma separated motor values like
m123,123
for the left and right motor speed values
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
int show_calcs = 0; // turn this to 1 to show the calculations on the console

int moving_threshold = 50; // minimum value to from 512 to move
int forward_reverse_offset = -30; // number added left 
int left_right_offset = 30; // number added left 
int moving_flag = 1; // 0 if stopped, 1 is moving

void setup() {
  // declare the inputs
  pinMode(fwd_rev_pin, INPUT);
  pinMode(left_right_pin, INPUT);
  pinMode(beep_pin, INPUT);
  Serial.begin(9600);
  bt.begin(38400); // note that this is not 9600!!
  Serial.println("Master joystick controller ready to send commands to robot slave via Bluetooth.");
}

void loop() {
  // read the sensor values
  fwd_rev_sensor_value = 1023 - analogRead(fwd_rev_pin) + forward_reverse_offset;  // we use the inverse with connectors to the left
  left_right_sensor_value = analogRead(left_right_pin) + left_right_offset;
  if (abs(fwd_rev_sensor_value - 512) > moving_threshold  ||  abs(left_right_sensor_value - 512) > moving_threshold  )
       { moving_flag = 1; }
  else { moving_flag = 0; }
 
  // useful for debugging
  if (show_sensor_values_flag == 1 && moving_flag == 1) {
    show_sensor_values();
  }
  
  // we can't use a case statement because we are doing range comparisons
  if (moving_flag == 1) {
    motor_speeds(fwd_rev_sensor_value, left_right_sensor_value);
  }
  
  delay(100);
}

// both sense values are between 0 and 1023
// straight is left-right at 512
// max is 1525
void motor_speeds(int fwd_rev_sensor_value, int left_right_sensor_value) {
  int turn = abs(left_right_sensor_value - 512); // amount of turning from center
  int speed_val = abs(fwd_rev_sensor_value - 512);  // total speed always positive
  int fwd__ref_flag; // 1 for forward -1 for reverse
  int left_right_flag; // -1 for left, + 1 for right
 
  int left_motor_speed_total;
  int right_motor_speed_total;
  
  if (fwd_rev_sensor_value < 512) {
    fwd__ref_flag = -1;
  } else {
    fwd__ref_flag = 1;
  }
  
  if (left_right_sensor_value < 512) {
    left_right_flag = -1;
  } else {
    left_right_flag = 1;
  }
  

  
  if (show_calcs == 1) {
    Serial.print("speed=");
    Serial.print(speed_val);
    Serial.print(" turn=");
    Serial.print(turn);
    Serial.print(" f-r=");
    Serial.print(fwd__ref_flag);
    Serial.print(" l-r=");
    Serial.println(left_right_flag);
  };
  
  // drop the motor speed in the wheel we are turning toward
  // turning left
  if (left_right_flag == -1) {
    left_motor_speed_total = (speed_val - turn) * fwd__ref_flag; 
    right_motor_speed_total = speed_val * fwd__ref_flag;
   } else {  // right turns we keep the left motor on high and turn faster for faster turns
    right_motor_speed_total = (speed_val - turn) * fwd__ref_flag;   
    left_motor_speed_total = speed_val * fwd__ref_flag;
   }   
  
  // mapping from 0 to 512 0 and 255
  left_motor_speed_total  = map(left_motor_speed_total, -495, 470, -255, 255);
  right_motor_speed_total = map(right_motor_speed_total, -510, 480, -255, 255);
  
  // safty checks
  left_motor_speed_total = constrain(left_motor_speed_total, -255, 255);
  right_motor_speed_total = constrain(right_motor_speed_total, -255, 255);
    
  bt.print("m");
  bt.print(left_motor_speed_total);
  bt.print(",");
  bt.println(right_motor_speed_total);
  
  Serial.print("m");
  Serial.print(left_motor_speed_total);
  Serial.print(",");
  Serial.println(right_motor_speed_total);
}

void show_sensor_values() {
  Serial.print("fwd-rev val =");
  Serial.print(fwd_rev_sensor_value);
  Serial.print(" left-right val =");
  Serial.println(left_right_sensor_value);
}
