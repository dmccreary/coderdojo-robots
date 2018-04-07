#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#include <AFMotor.h>

// ping sensor
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SERVO_PIN 10

const int ledPin = 12; // the pin that the LED strip is on
#define NUMBER_PIXELS 12

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo myservo;  // create servo object to control a servo 
#define LOOK_RIGHT 20
#define LOOK_FRONT 85
#define LOOK_LEFT 160
int servoInitPos = 90; // The initial position of the server - should be streight forward
// This LED strip is used for distance feedback
// The closer we get to an object in front of us, the further up the blue pixel is on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, ledPin, NEO_GRB + NEO_KHZ800);



// adjust these till the robot goes streight to compensate for motor differences
// 100 is OK for a 9v systems
int power_forward_right = 75; 
int power_forward_left = 75;
int power_turn_level = 80; // power level when turning

int test_delay = 100; // how long to wait for each initial test
int servo_90_delay = 250; // how long to wait for the server to turn 90 degrees
// motor pins.  Note that only pins 2,5,6, 9 and 10 can be used for pwm
int right_forward = 3;
int right_reverse = 5;
int left_forward = 6;
int left_reverse = 9;

// try this time to make a right turn just above 90 degrees
int delay_time_ninty_turn = 200;
// if we are under this distance then look around and decide where to turn
int cm_for_turn = 18;

int front_dist = 0;
int left_dist = 0;
int right_dist = 0;
int delay_time_forward = 100;
int look_delay = 1000;
int debug = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 11 to the servo object 
  // motor pins are all output
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);


  if (debug==1) {
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
    strip.setPixelColor(NUMBER_PIXELS - 1, 100, 100, 100);
    strip.show();
    delay(test_delay);
    // turn all pixels off
    erase_strip();
  }
  
  if (debug==1) {
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
  };
  

  // test the range of the servo
  myservo.write(LOOK_RIGHT); // right
  delay(servo_90_delay*2); // a little extra time for the first turn
  myservo.write(LOOK_FRONT); // streight
  delay(servo_90_delay);
  myservo.write(LOOK_LEFT); // left
  delay(servo_90_delay);
  // now turn back forward
  myservo.write(LOOK_FRONT);
  delay(servo_90_delay);

  // green means go!
  for (int i=0; i< NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 100, 0);
  strip.show();
  delay(test_delay);
  for (int i=0; i < NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
}

void loop() {
  
  // get the distance from the ping sensor in CM
  myservo.write(LOOK_FRONT);
  delay(servo_90_delay);
  front_dist = ping_avg(5);

  // no reading? - forward into the purple haze
  if (front_dist == 0) {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 30, 0, 30);
      strip.show();
  };
  
  // check if there is something in front of us
  if (front_dist != 0 && front_dist < cm_for_turn) {
      stop();
      
      Serial.println("checking for obstacles");
      // look right
      Serial.println("  looking right");
      myservo.write(LOOK_RIGHT);
      delay(look_delay);
      right_dist = ping_avg(5);
      draw_scan(right_dist, 1);
      delay(1000);
      
      // look front
      Serial.println("  looking front");
      myservo.write(LOOK_FRONT);
      delay(look_delay);
      front_dist = ping_avg(5);
      draw_scan(front_dist, 2);
      delay(1000);
       
      // look left
      Serial.println("  looking left");
      myservo.write(LOOK_LEFT);
      delay(look_delay);
      left_dist = ping_avg(5);
      draw_scan(left_dist, 3);
      delay(2000);
       
      // this is the main logic
      if (left_dist > right_dist) {
         turn_left();
         left_pattern();
         delay(1000);
      }
      else {
        turn_right();
        right_pattern();
        delay(1000);
      }
      
    } else {
       move_forward();
       forward_pattern();
       delay(1000);
    }
  
    Serial.print(" front_dist=");
    Serial.println(front_dist);

    Serial.print(" left_dist=");
    Serial.println(left_dist);
    
    Serial.print(" right_dist=");
    Serial.println(right_dist);

    erase_strip();
}

void turn_right() {
  Serial.println("cmd: turning right");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
  delay(delay_time_ninty_turn);
}

void turn_left() {
  Serial.println("cmd: turning left");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
  delay(delay_time_ninty_turn);
}

void stop() {
  Serial.println("cmd: stop");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
  analogWrite(left_reverse, LOW);
}

void move_forward() {
  Serial.println("cmd: moving forward");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
  delay(delay_time_forward);
}

// get the average of non-zero measurements
int ping_avg(int measurement_count) {
  int total=0;
  int dist=0;
  int valid_count=0;
  for(int i=1; i <= measurement_count; i++) {
     dist = sonar.ping_cm();
     if (dist > 0) {
        total += dist;
        valid_count++;
     }
     delay(50);
  }
  Serial.print("  valid counts=");
  Serial.print(valid_count);
  Serial.print(" dist=");
  Serial.println(total/valid_count);
  
  return (int) total/valid_count;
}

void draw_scan(int dist, int color_code) {
int index;
index = map(dist, 0, MAX_DISTANCE, 0, NUMBER_PIXELS);

    // erase the old strip
     for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 0);
    // on red, green or blue at index
    if (color_code == 1)
      strip.setPixelColor(index, 50, 0, 0);
    else if (color_code == 2)
      strip.setPixelColor(index, 0, 50, 0);
    else
       strip.setPixelColor(index, 0, 0, 50);
     strip.show();
};

void forward_pattern() {
  for (int i=0; i < NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 30, 0);
  strip.show();
};

void right_pattern() {
  for (int i=0; i < NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 30, 0, 0);
  strip.show();
};

void left_pattern() {
  for (int i=0; i < NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 0, 30);
  strip.show();
};

void erase_strip() {
  for (int i=0; i < NUMBER_PIXELS; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
};
