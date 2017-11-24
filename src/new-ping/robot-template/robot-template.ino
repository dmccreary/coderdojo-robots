#include <NewPing.h>

//Setup Ultrasonic Sensor Pins
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
#define RIGHT_FORWARD_PIN = 5;
#define RIGHT_REVERSE_PIN = 3;
#define LEFT_FORWARD_PIN = 6;
#define LEFT_REVERSE_PIN = 9;

// constants don't change
const int turn_distance = 10; //threshold for obstacles (in cm)
int front_distance = 0; // the distance in front of our robot in cm
const int forward_power_level 150; // a number from 0 to 255 for forard motors PWM
const int turn_power_level = 150; // power while turning
const int forward_delay 100; // time between ping checks when moving forward 
const int turn_delay 500; // time to turn in milliseconds 

void setup()
{
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  
  Serial.begin(9600); // Start serial for output debugging

  // Message to serial monitor declaring that robot is ready
  Serial.println("Setup Complete"); 
}

void loop()
{
  if (front_distance > turn_distance) // if path is clear
     move_forward(); //move forward
  else // if path is blocked
     turn_right();
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, forward_power_level);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, forward_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(forward_delay);
}

void turn_right() {
  Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
}



