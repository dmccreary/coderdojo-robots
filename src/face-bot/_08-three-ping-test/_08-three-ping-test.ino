#include <NewPing.h>
 
#define LEFT_TRIGGER_PIN    A0  // Arduino pin tied to trigger pin on the left ultrasonic sensor.
#define LEFT_ECHO_PIN       A1  // Arduino pin tied to echo pin on the left ultrasonic sensor.
#define CENTER_TRIGGER_PIN  A2
#define CENTER_ECHO_PIN     A3
#define RIGHT_TRIGGER_PIN   A4
#define RIGHT_ECHO_PIN      A5
#define MAX_DISTANCE 100
 
NewPing sonar_left(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_center(CENTER_TRIGGER_PIN, CENTER_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_right(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);

int left_dist = 0;
int center_dist =  0;
int right_dist =  0;
  
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  left_dist = sonar_left.ping_cm();
  center_dist =  sonar_center.ping_cm();
  right_dist =  sonar_right.ping_cm();

  Serial.print("Left: ");
  Serial.print(left_dist);
  Serial.print(" middle: ");
  Serial.print(center_dist); 
  Serial.print(" right: ");
  Serial.println(right_dist);
}

