#include <NewPing.h>

//Setup Ultrasonic Sensor Pins
// See https://playground.arduino.cc/Code/NewPing

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
#define RIGHT_FORWARD_PIN 5
#define RIGHT_REVERSE_PIN 3
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 9

// center taps of three 10K potentiomers 
#define FORWARD_POWER_PIN A0
#define TURN_DISTANCE_PIN A1
#define TURN_DELAY_PIN A2


int forward_power_level = 150; // a number from 0 to 255 for forard motors PWM on signal
int turn_distance = 20; //threshold for obstacles (in cm). try a range of 5 to 30
int turn_delay = 500; // time to turn in milliseconds 

// these constants don't change
const int forward_delay = 100; // time between ping checks when moving forward 
const int turn_power_level = 150; // power while turning


int front_distance = 0; // the distance in front of our robot in cm

void setup()
{
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  // potentiometers are inputs
  pinMode(FORWARD_POWER_PIN, INPUT);
  pinMode(TURN_DISTANCE_PIN, INPUT);
  pinMode(TURN_DELAY_PIN, INPUT);
  
  Serial.begin(9600); // Start serial for output debugging

  // Message to serial monitor declaring that robot is ready
  Serial.println("Setup Complete"); 
}

void loop()
{
  front_distance = sonar.ping_cm();

/*
  while (front_distance == 0) {
    front_distance = sonar.ping_cm();
    if (front_distance == 0) 
       Serial.println("Error: Front_distance=0");
    delay(100);
  }
  */

  Serial.print("Front_distance=");
  Serial.print(front_distance);
  
  // read the forward pot and convert
  forward_power_level = analogRead(FORWARD_POWER_PIN);
  forward_power_level = map(forward_power_level, 0, 1024, 0, 255);
  Serial.print(" forward_power_level=");
  Serial.print(forward_power_level);

    // read the turn_distance pot and convert
  turn_distance = analogRead(TURN_DISTANCE_PIN);
  turn_distance = map(turn_distance, 0, 1024, 3, 30);
  Serial.print(" turn_distance=");
  Serial.print(turn_distance);

    // read the turn_delay pot and convert
  turn_delay = analogRead(TURN_DELAY_PIN);
  turn_delay = map(turn_delay, 0, 1024, 0, 2000);
  Serial.print(" turn_delay=");
  Serial.print(turn_delay);
  Serial.println("");
  
  if (front_distance > turn_distance) // if path is clear
     move_forward(); //move forward
  else // if path is blocked
     turn_right();

     delay(500);
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
  analogWrite(RIGHT_REVERSE_PIN, forward_power_level);
  analogWrite(LEFT_FORWARD_PIN, forward_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);

  // turn off both motors and wait
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  delay(turn_delay);

}



