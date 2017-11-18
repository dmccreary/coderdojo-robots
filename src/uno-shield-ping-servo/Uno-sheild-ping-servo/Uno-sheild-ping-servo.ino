// ArduCAM Smart_Robot_Car demo (C)2017
//Before using this demo, you shold install AFMotor library
//which are in the InstallLibrary folder.
// This demo support smart mode .
//video link: https://youtu.be/0FB7J-Qzcag

/***********************[NOTICE]*********************************
  We can't guarantee that the motor load
  is exactly the same, so it increases the compensation
  factor. You should adjust them to suit for your motor
****************************************************************/
#define leftFactor 10
#define rightFactor 10

#define speedSet  200
#define TURN_DIST 20
#define TURN_TIME 500
#define TURN_POWER 100
#define FORWARD_DELAY 2000
#define TURN_HEAD_DELAY 1000
#define offset -20

#include <Servo.h>
#include <AFMotor.h>

Servo neckControllerServoMotor;
AF_DCMotor leftMotor(3, MOTOR34_64KHZ);
AF_DCMotor rightMotor(4, MOTOR34_64KHZ);

int trig = A2;
int echo = A3;
unsigned int S;
unsigned int Sleft;
unsigned int Sright;

void setup() {
  Serial.begin(9600);
  Serial.println("Running setup");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  neckControllerServoMotor.attach(10);
  neckControllerServoMotor.write(90 + offset);
  delay(2000);
}

void loop() {
  Serial.println("In Loop");
  // point ping streight ahead
  neckControllerServoMotor.write(90 + offset);
  delay(100);
  range();
  Serial.print("Forward Range=");
  Serial.println(S);
  if (S < TURN_DIST ) 
    turn();
    else moveForward();
   
}

void turn() {
  moveStop();
  // turn 60 to the left
  neckControllerServoMotor.write(150 + offset);
  delay(TURN_HEAD_DELAY);
  range();
  Sleft = S;

  // point ahead
  neckControllerServoMotor.write(90 + offset);
  delay(TURN_HEAD_DELAY);

  // point 60 to the right
  neckControllerServoMotor.write(30 + offset);
  delay(TURN_HEAD_DELAY);
  range();
  Sright = S;

  // now point ahead
  neckControllerServoMotor.write(90 + offset);
  delay(500);
  if (Sleft <= TURN_DIST && Sright <= TURN_DIST) {
    moveBackward();
    delay(500);
    int x = random(1);
    if (x = 0) {
      turnRight();
    }
    else {
      turnLeft();
    }
  } else {
    if (Sleft >= Sright) {
      turnLeft();
    } else {
      turnRight();
    }
  }
}

void range() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(trig, LOW);
  int distance = pulseIn(echo, HIGH);
  distance = distance / 58;
  S = distance;
  Serial.print("Range=");
  Serial.println(S);
  if (S < TURN_DIST) {
    delay(50);
  }
}

void moveForward() {
  Serial.println("moving forward");
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  leftMotor.setSpeed(speedSet + leftFactor);
  rightMotor.setSpeed(speedSet + rightFactor);
  delay(FORWARD_DELAY);
}

void turnLeft() {
  Serial.println("turning left");
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  leftMotor.setSpeed(TURN_POWER + leftFactor);
  rightMotor.setSpeed(TURN_POWER + rightFactor);
  delay(TURN_TIME);
  moveStop();
}

void turnRight() {
  Serial.println("turning right");
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  leftMotor.setSpeed(TURN_POWER + leftFactor);
  rightMotor.setSpeed(TURN_POWER + rightFactor);
  delay(TURN_TIME);
  moveStop();
}

void moveBackward() {
  leftMotor.run(BACKWARD);
  rightMotor.run(BACKWARD);
  leftMotor.setSpeed(speedSet + leftFactor);
  rightMotor.setSpeed(speedSet + rightFactor);
  delay(1000);
}

void moveStop() {
  leftMotor.run(RELEASE); rightMotor.run(RELEASE);
}

