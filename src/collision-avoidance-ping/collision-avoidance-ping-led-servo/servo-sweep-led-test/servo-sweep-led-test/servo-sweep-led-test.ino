#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#define SERVO_PIN 10
#define LED_PIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 10 // the number of pixels in your LED strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo servo;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  Serial.print("Attaching servo to pin: ");
  Serial.println(SERVO_PIN);
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object

  Serial.print("Pointing streight ahead at 90");
  myservo.write(90);

 Serial.print("Initializing LED memory on pin: ");
 Serial.println(LED_PIN);
 strip.begin();
 erase_led();
}

void loop() {
  Serial.println("Starting scan");
  // turn to the right clockwise
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    draw_angle_on_led(pos, 1);
  }
  
  // turn to the left full counter clockwise
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
     draw_angle_on_led(pos, 2);
  }

  // turn to the right clockwise
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 90 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
    draw_angle_on_led(pos, 3);
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

