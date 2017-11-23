#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <AFMotor.h>
#define SERVO_PIN 10
#define PING_PIN 11
#define LED_PIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 10 // the number of pixels in your LED strip
#define MAX_DISTANCE 200 // the max distance we display on the LED strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo servo;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int front_dist = 100; // distance measurement in front
int right_dist = 100; // distance measurement on the right
int left_dist = 100;  // distance measurement on the left

// adjust these till the robot goes streight to compensate for motor differences
int power_forward_right = 150; /* half power on turns */
int power_forward_left = 150; /* half power on turns */
int power_turn_level = 150; /* power on turns */
int test_delay = 500;
int turn_dist = 20;

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;

// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 300;
// if we are under this distance, make a turn.  For higher power, make this larger
int cm_for_turn = 25;

// how long should we drive forward before we stop and check again?
int delay_time_forward = 500;

void setup() {
  Serial.begin(9600);
  Serial.print("Attaching servo to pin: ");
  Serial.println(SERVO_PIN);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object

  Serial.print("Pointing streight ahead at 90");
  myservo.write(90);
  delay(500);
  
 Serial.print("Initializing LED memory on pin: ");
 Serial.println(LED_PIN);
 strip.begin();
 erase_led();
 front_dist = get_distance_cm(1);
 draw_dist_on_led(front_dist, 1);
 delay(1000);
}

void loop() {
  front_dist = get_distance_cm(1);
  draw_dist_on_led(front_dist, 1);

  if (front_dist > turn_dist)
     move_forward();
  else {
        Serial.println("Starting scan");
        // turn to the right clockwise
        for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 15ms for the servo to reach the position
            draw_angle_on_led(pos, 1);
        }
        right_dist = get_distance_cm(2);
        draw_dist_on_led(right_dist, 2);
        delay(1000);
        
        // turn to the left full counter clockwise
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(10);                       // waits 15ms for the servo to reach the position
            draw_angle_on_led(pos, 2);
         }
         left_dist = get_distance_cm(3);
         draw_dist_on_led(right_dist, 3);
         delay(1000);
        
        // turn back to the center
        for (pos = 180; pos >= 90; pos -= 1) { // goes from 90 degrees to 0 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(10);                       // waits 15ms for the servo to reach the position
          draw_angle_on_led(pos, 3);
        }

        if (right_dist > left_dist)
          turn_right();
        else turn_left();
          
  }
  
  delay(1000);
  erase_led();
  
}

void erase_led() {
for (int i=0; i<NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
}

void draw_angle_on_led(int angle, int mode) {
   int strip_index;
   strip_index = map(angle, 0, 180, 0, NUMBER_PIXELS);
   // blue if sweeping to the right to get measurement_right
   if (mode == 1) strip.setPixelColor(strip_index, 0, 0, 30);
   // green if sweeping to the left to get measurement_left
   else if (mode == 2) strip.setPixelColor(strip_index, 0, 30, 0);
   // red if returning to forward
   else if (mode == 3) strip.setPixelColor(strip_index, 30, 0, 0);
   strip.show();
}

void draw_dist_on_led(int dist, int mode) {
   int strip_index;
   strip_index = map(dist, 0, MAX_DISTANCE, 0, NUMBER_PIXELS);
   // distance in the front in yellow
   if (mode == 1) strip.setPixelColor(strip_index, 30, 30, 0);
   // distance on the right in white
   else if (mode == 2) strip.setPixelColor(strip_index, 30, 30, 30);
   // distance in left in purple
   else if (mode == 3) strip.setPixelColor(strip_index, 30, 0, 30);
   strip.show();
   delay(1000);
}

int get_distance_cm(int mode)
{
  long duration, cm=0;
  pinMode(PING_PIN, OUTPUT);
  digitalWrite(PING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_PIN, LOW);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(PING_PIN, INPUT);
  duration = pulseIn(PING_PIN, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  if (mode==1)Serial.print(" front=");
  if (mode==2)Serial.print(" right=");
  if (mode==3)Serial.print(" left=");
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

void move_forward() {
  Serial.println("moving forward");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
  delay(delay_time_forward);
  analogWrite(right_forward, LOW);
  analogWrite(left_forward, LOW);
}

void turn_right() {
  Serial.println("turning right");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
  delay(delay_time_ninty_turn);
 analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
}

void turn_left() {
  Serial.println("turning left");
  analogWrite(right_forward, power_turn_level);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
  analogWrite(left_reverse, power_turn_level);
  delay(delay_time_ninty_turn);
  analogWrite(right_forward, LOW);
  analogWrite(left_reverse, LOW);
}



