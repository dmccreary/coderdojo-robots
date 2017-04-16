#include <AFMotor.h>
AF_DCMotor motor_left_rear(1, MOTOR12_64KHZ);
AF_DCMotor motor_right_rear(2, MOTOR12_64KHZ);
AF_DCMotor motor_right_front(3, MOTOR12_64KHZ);
AF_DCMotor motor_left_front(4, MOTOR12_64KHZ);

// ping sensor
const int pingPin = 10;
int dist_in_cm = 120;

// This LED strip is used for distance feedback
// The closer we get to an object in front of us, the further up the blue pixel is on
#include <Adafruit_NeoPixel.h>
#define LEDPIN 9 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12 // the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int old_strip_index = 0;
int new_strip_index = 0;
int power_turn_level = 150; /* power on turns */

// adjust these till the robot goes streight to compensate for motor differences
int power_forward_right = 75; /* power on forward to right wheels */
int power_forward_left = 75; /* power on forward to left wheels */


// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 500;
// if we are under this distance, make a turn.  For higher power, make this larger
int cm_for_turn = 20;
int delay_time_forward = 100;

void setup() {
  Serial.begin(9600);

  motor_left_front.setSpeed(power_forward_left);
  motor_right_front.setSpeed(power_forward_right); 
  motor_left_rear.setSpeed(power_forward_left);
  motor_right_rear.setSpeed(power_forward_right);
  
  strip.begin();
  strip.setPixelColor(0, 10, 0, 0);
  strip.show();
  delay(200);

  pinMode(pingPin, INPUT);
  pinMode(LEDPIN, OUTPUT);

}

void loop() {
  
  
  
  // get the distance from the ping sensor in CM
  dist_in_cm = get_distance_cm();
  new_strip_index = (dist_in_cm / 5) - 1;
  
  // don't go over the max
 new_strip_index = constrain(new_strip_index, 0, NUMBER_PIXELS - 1);
  
  // only draw if there is a change
  if ( old_strip_index != new_strip_index) {
    // erase the old strip
     for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 0);
    // turn on new value to a light blue
     strip.setPixelColor(new_strip_index, 0, 0, 255);
     strip.show();
  };
  
  // if there is something in front, turn right
  if (dist_in_cm < cm_for_turn) {
      turn_right();
    } else {
      move_forward();
    }
  
  Serial.print("dist cm=");
  Serial.print(dist_in_cm);
  Serial.print(" ");
  delay(100);
}

void turn_right() {
  Serial.println("turning right");
  // left go forward
  motor_left_front.run(FORWARD);
  motor_left_rear.run(FORWARD);
  // right go backward
  motor_right_front.run(BACKWARD);
  motor_right_rear.run(BACKWARD);
  delay(delay_time_ninty_turn);
}

void move_forward() {
  Serial.println("moving forward");
  motor_left_front.run(FORWARD);
  motor_right_front.run(FORWARD);
  motor_left_rear.run(FORWARD);
  motor_right_rear.run(FORWARD);
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
  // Serial.print(" cm=");
  // Serial.println(cm);
  return cm;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

