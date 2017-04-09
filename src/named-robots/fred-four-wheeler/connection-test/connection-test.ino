#include <AFMotor.h>
AF_DCMotor motor_left_rear(1, MOTOR12_64KHZ);
AF_DCMotor motor_right_rear(2, MOTOR12_64KHZ);
AF_DCMotor motor_right_front(3, MOTOR12_64KHZ);
AF_DCMotor motor_left_front(4, MOTOR12_64KHZ);
// ping sensor
const int pingPin = 2;


// adjust these till the robot goes streight to compensate for motor differences
int power_forward_right = 255; /* half power on turns */

void setup() {
 Serial.begin(9600);
  Serial.begin(9600);
  motor_left_rear.setSpeed(power_forward_right);
  motor_right_rear.setSpeed(power_forward_right);
  motor_left_front.setSpeed(power_forward_right);
  motor_right_front.setSpeed(power_forward_right); 
 // set up Serial library at 9600 bps
 Serial.println("Testing motor connections.  Order is left rear, right rear, left front, right front...");


}

void loop() {
 Serial.println("starting test....");

 Serial.println("motor_left_rear forward");
 motor_left_rear.run(FORWARD); // turn it on going forward
 delay(1000);
 Serial.println("motor_left_rear backward");
 motor_left_rear.run(BACKWARD); // the other way
 delay(1000);
 motor_left_rear.run(RELEASE); //stopped
 delay(1000);


 Serial.println("motor_right_rear forward");
 motor_right_rear.run(FORWARD); // turn it on going forward
 delay(1000);
 Serial.println("motor_right_rear backward");
 motor_right_rear.run(BACKWARD); // the other way
 delay(1000);
 motor_right_rear.run(RELEASE); //stopped
 delay(1000);

 Serial.println("motor_left_front forward");
 motor_left_front.run(FORWARD); // turn it on going forward
 delay(1000);
 Serial.println("motor_left_front backward");
 motor_left_front.run(BACKWARD); // the other way
 delay(1000);
 motor_left_front.run(RELEASE); //stopped
 delay(1000);
 
 Serial.println("motor_right_front forward");
 motor_right_front.run(FORWARD); // turn it on going forward
 delay(1000);
 Serial.println("motor_right_front backward");
 motor_right_front.run(BACKWARD); // the other way
 delay(1000);
 motor_right_front.run(RELEASE); //stopped

 Serial.println("Test Complete.");
 Serial.println("");
 delay(2000);
} 
