#include <NewPing.h>

//Setup Ultrasonic Sensor Pins
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  10

// Arduino pin tied to trigger pin on the ultrasonic sensor.

#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


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
const int temp;
const int temp1;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// constants don't change
const int per_pixel_distance = (MAX_DISTANCE / NUMBER_PIXELS) / 2;
const int turn_distance = 20; //threshold for obstacles (in cm). try a range of 5 to 30
const int forward_power_level = 90; // a number from 0 to 255 for forard motors PWM on signal
const int forward_delay = 100; // time between ping checks when moving forward 

const int turn_power_level = 100; // power while turning
const int turn_delay = 500; // time to turn in milliseconds 

int front_distance = 0; // the distance in front of our robot in cm
int pixel_index = 0; // where on the LED strip to update the front_distance

void setup()
{
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);

  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  
  Serial.begin(9600); // Start serial for output debugging

  // flash the LED strip
  strip.begin();
  // test the LED strip
  flash_led_test();
  delay(1000);
  
  Serial.print("Each pixel is ");
  Serial.print(per_pixel_distance);
  Serial.println(" cm."); 
  
  // Message to serial monitor declaring that robot is ready
  Serial.println("Setup Complete"); 
}

void loop()
{
  
  front_distance = average_ping(5);
  Serial.print("front_distance=");
  Serial.println(front_distance);
  
  if (front_distance == 0) {  // 0 is no valid signal from the ping sensor
    set_led_green();
    move_forward(); //move forward
    }
    else if (front_distance < turn_distance) 
        turn_right();    
    else { // a valid value above the turn distance 
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
}

void turn_right() {
  Serial.println("turning right");
  set_led_red();
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
  // all motors off
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(1000); // delay after turning
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
        strip.setPixelColor(i, 0, 0, 50);
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
  strip.setPixelColor(1, 50, 25, 0); // orange
  strip.setPixelColor(2, 50, 50, 0); // yellow
  strip.setPixelColor(3, 0, 50, 0); // green
  strip.setPixelColor(4, 0, 0, 50); // blue
  strip.setPixelColor(5, 50, 0, 50); // indigo
  strip.setPixelColor(6, 25, 0, 25); // violet

  strip.setPixelColor(7, 25, 25, 25); // whit
  strip.setPixelColor(8, 25, 25, 25); // whit
  strip.setPixelColor(9, 25, 25, 25); // white
  strip.setPixelColor(10, 25, 25, 25);

  strip.setPixelColor(NUMBER_PIXELS - 1, 50, 50, 50); // set last pixel to white
  strip.show();
  
}

// take the average of "count" valid values
int average_ping(int count) {
  int sum_valid;
  int dist;
  int valid_readings = 0;
  int average_distance = 0;
  for (int i=1; i<=count; i++) {
       dist = sonar.ping_cm();
       if (dist != 0 && dist < 1000) {
          sum_valid += dist; // add this one in
          valid_readings++; // add total valid readings
//          Serial.print("valid distance=");
//          Serial.println(dist);
       }
       else {
          Serial.print("invalid distance=");
          Serial.println(dist);
          Serial.print("median msec=");
          Serial.println(sonar.ping_median(5)); 
       };
       delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    }
    average_distance =  round(sum_valid / valid_readings) + 1;
    Serial.print("average distance=");
    Serial.println(average_distance);
    return average_distance;
}

//unsigned long pingLoopTime;
//unsigned long pingCurrentTime;
//unsigned long pulseDuration;
//int ping(){
//  digitalWrite(TRIGGER_PIN, HIGH);
//  pingCurrentTime = millis();
//  if(pingCurrentTime >= (pingLoopTime + 10)){  
//    digitalWrite(TRIGGER_PIN, LOW);
//    pulseDuration = pulseIn(ECHO_PIN,HIGH,90000);
//   int calculatedDistance = (pulseDuration/2) / 29.1;
//    if (calculatedDistance <= 0){
//      return 4444;
//    }
//    if (calculatedDistance > 200){
//      return 9999;
//    }
//    else {
//      return calculatedDistance / 10;
//    }
//    pingLoopTime = pingCurrentTime; 
//  }
//}
