#include <NewPing.h>

//Setup Ultrasonic Sensor Pins
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
#define right_forward_pin = 5;
#define right_reverse_pin = 3;
#define left_forward_pin = 6;
#define left_reverse_pin = 9;

const int turn_distance = 10; //threshold for obstacles (in cm)
int front_dist_cm = 0;
int forward_speed 150; // a number from 0 to 255 for forard motors PWM

void setup()
{
  pinMode(pingPin, INPUT);
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  
  Serial.begin(9600); // Start serial for output debugging
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Set modes for motor controller pins
  pinMode(enA, OUTPUT);   
  pinMode(enB, OUTPUT);   
  pinMode(in1, OUTPUT);   
  pinMode(in2, OUTPUT);   
  pinMode(in3, OUTPUT);   
  pinMode(in4, OUTPUT);
  // Message to serial monitor declaring that robot is ready
  Serial.println("Setup Complete");
  Serial.println("Hammerstein Ready!");
  
}

void loop()
{
  if (distance_front > turn_distance) // if path is clear
     move_forward(); //move forward
  else // if path is blocked
     turn();
}

void turn() {
    Stop(); 
    sensor_servo.write(0); 
    delay(500);
    right_distance = sonar.ping_cm(); //scan to the right
    delay(500);
    sensor_servo.write(180);
    delay(700);
    left_distance = sonar.ping_cm(); //scan to the left
    delay(500);
    sensor_servo.write(90); //return to center
    delay(100);
    compareDistance();
    if (leftDistance>rightDistance) //if left is less obstructed 
        {
          Left(); //turn left
          delay(500); 
        }
     else if (rightDistance>leftDistance) //if right is less obstructed
        {
          Right(); //turn right
          delay(500);
        }
      else //if they are equally obstructed
        {
          Left(); //turn 180 degrees
          delay(1000);
        }
}

