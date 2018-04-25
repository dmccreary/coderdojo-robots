#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <NewPing.h>
#include <AFMotor.h>

// ping sensor
const int pingPin = 11;
int dist_in_cm = 100; // pick a high number to start

// This LED strip is used for distance feedback
// The closer we get to an object in front of us, the further up the blue pixel is on
#define SERVO_PIN 10
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define LED_PIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12 // the number of pixels in your LED strip

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo servo;

int old_strip_index = 0;
int new_strip_index = 0;
int power_turn_level = 150; /* power on turns */

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;

// adjust these till the robot goes streight to compensate for motor differences
// these are for a 9v setting
int power_forward_right = 100; /* half power on turns */
int power_forward_left = 100; /* half power on turns */
int test_delay = 500; // 1/2 second for initial motor tests



// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 300;
// if we are under this distance, make a turn.  For higher power, make this larger
int cm_for_turn = 25;
int delay_time_forward = 100;

void setup() {
  Serial.begin(9600);
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  
  // flash LED strip to confirm it is working
  strip.begin();
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
  delay(300);
  


  // attach and test servo
  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(500);
  servo.write(-45);
  delay(500);
  servo.write(-45);
  delay(500);
  
  // Test motor connections
  analogWrite(right_forward, power_forward_right);
  delay(test_delay);
  analogWrite(right_forward, 0);
  
  analogWrite(right_reverse, power_forward_right);
  delay(test_delay);
  analogWrite(right_reverse, 0);
  
  analogWrite(left_forward, power_forward_left);
  delay(test_delay);
  analogWrite(left_forward, 0);
  
  analogWrite(left_reverse, power_forward_left);
  delay(test_delay);
  analogWrite(left_reverse, 0);
  

  // for debugging
  // Serial.println('Start');
}

void loop() {
  
  delay(100);
  
  // get the distance from the ping sensor in CM
  dist_in_cm = sonar.ping_cm();
  new_strip_index = dist_in_cm / 5;
  
  // don't go over the max
  if (new_strip_index > (NUMBER_PIXELS - 1)) {
    new_strip_index = 11;
  }
  
  // only draw if there is a change
  if ( old_strip_index != new_strip_index) {
    // erase the old strip
     for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 0);
    // turn on new value to a light blue
     strip.setPixelColor(new_strip_index, 0, 0, 30);
     strip.show();
  };
  
  // if there is something in front, turn right
  if (dist_in_cm < cm_for_turn) {
      turn_right();
    } else {
      move_forward();
    }
  
  // Serial.print(" new=");
  // Serial.print(new_strip_index);

}

void turn_right() {
  Serial.println("turning right");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
  delay(delay_time_ninty_turn);
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
  delay(delay_time_forward);
}


int get_distance_cm()
{
  long duration, cm=0;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  Serial.print(" cm=");
  Serial.println(cm);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

