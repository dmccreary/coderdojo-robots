#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#include <AFMotor.h>

// ping sensor
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SERVO_PIN 10

const int ledPin = 12; // the pin that the LED strip is on
const int numberPixels = 12;

int dist_in_cm = 120;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo myservo;  // create servo object to control a servo 
int servoInitPos = 90;    // variable to store the servo position 
// This LED strip is used for distance feedback
// The closer we get to an object in front of us, the further up the blue pixel is on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberPixels, ledPin, NEO_GRB + NEO_KHZ800);

int old_strip_index = 0;
int new_strip_index = 0;
int power_turn_level = 150; /* full power on turns */

// adjust these till the robot goes streight to compensate for motor differences
// 100 is OK for a 9v systems
int power_forward_right = 100; 
int power_forward_left = 100; 
int test_delay = 1000; // how long to wait for each initial test
// motor pins.  Note that only pins 2,5,6, 9 and 10 can be used for pwm
int right_forward = 3;
int right_reverse = 5;
int left_forward = 6;
int left_reverse = 9;

// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 200;
// if we are under this distance, make a turn
int cm_for_turn = 10;
int delay_time_forward = 100;
int look_delay = 1000;

void setup() {
  Serial.begin(9600);
  strip.begin();
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);

  // LED strip test
  strip.setPixelColor(0, 100, 0, 0);
  strip.show();
  delay(test_delay);
  strip.setPixelColor(1, 0, 100, 0);
  strip.show();
  delay(test_delay);
  strip.setPixelColor(2, 0, 0, 100);
  strip.show();
  delay(test_delay);
  // make the last pixel white
  strip.setPixelColor(11, 100, 100, 100);
  strip.show();
  delay(test_delay);

  // Motor Test - check the the motors are hooked up right
  // verfity the order: right forward, right reverse, left forware, left reverse
  analogWrite(right_forward, 100);
  delay(test_delay);
  analogWrite(right_forward, 0);
  analogWrite(right_reverse, 100);
  delay(test_delay);
  analogWrite(right_reverse, 0);
  analogWrite(left_forward, 100);
  delay(test_delay);
  analogWrite(left_forward, 0);
  analogWrite(left_reverse, 100);
  delay(test_delay);
  analogWrite(left_reverse, 0);
 
  
  // for debugging
  Serial.println('Start');
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 11 to the servo object 
  myservo.write(servoInitPos); // the servo scans from 0 to 180
  myservo.write(0);
  delay(test_delay);
  myservo.write(90);
  delay(test_delay);
  myservo.write(180);
  delay(test_delay);

  // green means go!
  strip.setPixelColor(0, 0, 200, 0);
  strip.show();
  
  delay(2000); // wait to see that we are good to go
}

void loop() {
  myservo.write(servoInitPos);
  delay(100);
  
  // get the distance from the ping sensor in CM
  dist_in_cm =sonar.ping_cm();
  
  // we are counting 0 in the rear
  new_strip_index = numberPixels - (dist_in_cm / 5);
  
  // don't go over the max distance
  if (new_strip_index < 0) {
    new_strip_index = 0;
  }
  
  // only draw if there is a change
  if ( old_strip_index != new_strip_index) {
    // erase the old strip
     for (int i=0; i < numberPixels; i++)
        strip.setPixelColor(i, 0, 0, 0);
    // turn on new value to a light blue
     strip.setPixelColor(new_strip_index, 0, 0, 30);
     strip.show();
  };
  
  // if there is something in front, turn right
  if (dist_in_cm < cm_for_turn) {
      stop();
      // look left
      myservo.write(0);
      delay(look_delay);
      // look front
      myservo.write(90);
      delay(look_delay);
      // look right
      myservo.write(180);
      delay(look_delay);
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

void turn_left() {
  Serial.println("turning right");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
  delay(delay_time_ninty_turn);
}

void stop() {
  Serial.println("stop");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
  analogWrite(left_reverse, LOW);
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
  delay(delay_time_forward);
}

// test of get distance
int get_distance_cm()
{
  int cm;
  cm = sonar.ping_cm();
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
