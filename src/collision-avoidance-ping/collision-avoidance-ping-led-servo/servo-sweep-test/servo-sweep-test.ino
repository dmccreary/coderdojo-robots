#include <Servo.h>
#define SERVO_PIN 10

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  Serial.print("Attaching servo to pin: ");
  Serial.println(SERVO_PIN);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object

  Serial.print("Pointing streight ahead at 90");
  myservo.write(90);
  delay(1000);
}

void loop() {
  Serial.println("Starting scan");
  // turn to the right clockwise
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  // turn to the left full counter clockwise
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  // turn to the right clockwise
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(1000);
  
}
