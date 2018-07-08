#include <SPI.h>
#include <Wire.h>
#include <NewPing.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define LEFT_TRIGGER_PIN    A0  // Arduino pin tied to trigger pin on the left ultrasonic sensor.
#define LEFT_ECHO_PIN       A1  // Arduino pin tied to echo pin on the left ultrasonic sensor.
#define CENTER_TRIGGER_PIN  A2
#define CENTER_ECHO_PIN     A3
#define RIGHT_TRIGGER_PIN   A4
#define RIGHT_ECHO_PIN      A5
#define MAX_DISTANCE 100
#define TURN_DISTANCE_THRESHOLD 12

// If using software SPI (the default case):
#define OLED_CLK   13   // SCL
#define OLED_MOSI  12   // SDA
#define OLED_RESET 11   // RST
#define OLED_DC    10   // DC
#define OLED_CS    8    //CS
#define LINE_HIGHT  10   // 10 pixels per line

NewPing sonar_left(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_center(CENTER_TRIGGER_PIN, CENTER_ECHO_PIN, MAX_DISTANCE);
NewPing sonar_right(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int left_dist = 0;
int center_dist =  0;
int right_dist =  0;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("9 3-ping display tst");
  display.display();
  delay(3000);
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

  // erase everything
  display.clearDisplay();
  // we have 64 pixels to work with
  display.setCursor(0,LINE_HIGHT);
  display.print("L:");
  display.setCursor(10,LINE_HIGHT);
  display.print(left_dist);

  display.setCursor(50,LINE_HIGHT);
  display.print("M:");
  display.setCursor(60,LINE_HIGHT);
  display.print(center_dist);

  display.setCursor(100,LINE_HIGHT);
  display.print("R:");
  display.setCursor(110,LINE_HIGHT);
  display.print(right_dist);

    
  if (right_dist < TURN_DISTANCE_THRESHOLD && right_dist > 0) {
    display.setCursor(0,3*LINE_HIGHT);
    display.print("Turning left");
  }
    else if (left_dist < TURN_DISTANCE_THRESHOLD && left_dist > 0) {
      display.setCursor(0,3*LINE_HIGHT);
      display.print("Turning right");
    }
    else if (center_dist < TURN_DISTANCE_THRESHOLD && center_dist > 0) {
      display.setCursor(0,3*LINE_HIGHT);
      display.print("Turn center - backing up");
      // measure again
      left_dist = sonar_left.ping_cm();
      right_dist =  sonar_right.ping_cm();
      // if we have more room on the right, turn right
      display.setCursor(0,4*LINE_HIGHT);
      if (right_dist > left_dist) {  
        display.print("Next turn right");
      }
        else {
          display.print("Next turn left");
        }
    }
  display.display();
}

