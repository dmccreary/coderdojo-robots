#include <NewPing.h>

//Setup Ultrasonic Sensor Pins
#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// motor pins.  Note that only pins 2,5,6,9 and 10 can be used for pwm
#define RIGHT_FORWARD_PIN 5
#define RIGHT_REVERSE_PIN 3
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 9

// This LED strip is used for distance feedback
// The closer we get to an object in front of us, the further up the blue pixel is on
#include <Adafruit_NeoPixel.h>
#define LEDPIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12
// the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// constants don't change
const int per_pixel_distance = (MAX_DISTANCE / NUMBER_PIXELS) / 2;
const int turn_distance = 6; //threshold for obstacles (in cm). try a range of 5 to 30
const int forward_power_level = 150; // a number from 0 to 255 for forard motors PWM on signal
const int turn_power_level = 100; // power while turning
const int forward_delay = 100; // time between ping checks when moving forward 
const int turn_delay = 500; // time to turn in milliseconds 

int front_distance = 0; // the distance in front of our robot in cm
int m1, m2, m3; // three measurements
int pixel_index = 0; // where on the LED strip to update the front_distance

void setup()
{
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  
  Serial.begin(9600); // Start serial for output debugging

  // flash the LED strip
  strip.begin();
  // test the LED strip
  flash_led_test();
  delay(1000);
  
  Serial.print("Each pixel is");
  Serial.print("per_pixel_distance");
  Serial.println(" cm."); 
  
  // Message to serial monitor declaring that robot is ready
  Serial.println("Setup Complete"); 
}

void loop()
{
  m1 = sonar.ping_cm();
  delay(20);
  m1 = sonar.ping_cm();
  delay(20);
  m1 = sonar.ping_cm();
  front_distance = (m1  +m2 + m3) / 3;
  Serial.println(front_distance);
  
  if (front_distance == 0) {
    set_led_green();
    move_forward(); //move forward
    }
    else if (front_distance < turn_distance) // 0 is no signal
        turn_right();    
    else { // if path is blocked 
      update_led(front_distance);
      move_forward(); //move forward
    }
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
  set_led_red();
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
}

void update_led(int front_distance) {
  pixel_index  = front_distance / per_pixel_distance;
  // erase the old display values
  for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 0);
  // draw the new value
  Serial.print("Pixel Index: ");
  Serial.println(pixel_index);
  for (int i=0; i < pixel_index; i++)
        strip.setPixelColor(pixel_index, 0, 0, 30);
  strip.show();
}

void set_led_red() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 25, 0, 0);
   strip.show();
}

void set_led_green() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 25, 0);
   strip.show();
}

void flash_led_test() {
  strip.setPixelColor(0, 50, 0, 0); // red
  strip.setPixelColor(4, 50, 25, 50); // orange
  strip.setPixelColor(3, 50, 50, 0); // yellow
  strip.setPixelColor(5, 0, 50, 0); // green
  strip.setPixelColor(6, 0, 0, 50); // blue
  strip.setPixelColor(7, 50, 0, 50); // indigo
  strip.setPixelColor(8, 25, 0, 25); // violet
  
  strip.setPixelColor(9, 0, 50, 50); // cyan
  strip.setPixelColor(10, 25, 50, 0);
  strip.setPixelColor(11, 25, 25, 50);
  strip.setPixelColor(NUMBER_PIXELS - 1, 50, 50, 50); // set last pixel to white
  strip.show();
  
}


