
// ping sensor
const int pingPin = 11;
int dist_in_cm = 100; // pick a high number to start
int power_turn_level = 255; /* power on turns */

// adjust these till the robot goes streight to compensate for motor differences
int power_forward_right = 150; /* half power on turns */
int power_forward_left = 150; /* half power on turns */
int test_delay = 500;

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;

// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 100;
// if we are under this distance, make a turn.  For higher power, make this larger
int cm_for_turn = 20;
int delay_time_forward = 100;

void setup() {
  Serial.begin(9600);
  
  pinMode(pingPin, INPUT);
  
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  
  // Test connections
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
  
  Serial.println('Setup done');
}

void loop() {
  
  delay(100);
  
  // get the distance from the ping sensor in CM
  dist_in_cm = get_distance_cm();
  
  // new_strip_index = constrain(new_strip_index, 0, NUMBER_PIXELS - 1)
  
  // if there is something in front, turn right
  if (dist_in_cm < cm_for_turn) {
      turn_right();
    } else {
      move_forward();
    }
  
  Serial.print("distance cm=");
  Serial.print(dist_in_cm);

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

