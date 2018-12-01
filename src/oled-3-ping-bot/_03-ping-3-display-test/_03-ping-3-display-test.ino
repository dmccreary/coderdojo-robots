// ---------------------------------------------------------------------------
// Ping Display Test
// ---------------------------------------------------------------------------
#include <Arduino.h>
#include <NewPing.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>

// order on OLED - GND, VCC, SCL, SDA, RDS, DC, CS
#define SCL_PIN 13 // SCL clock - 3rd from bottom
#define SDA_PIN 11 // SDA, Data, MOSI - must be on pin 11 on the Nano
#define RDS_PIN 10 // reset
// pin 9 is a PWM reserved for the motor
#define DC_PIN 8 // DC moved from pin 9 which is needed as a PWM pin
#define CS_PIN 7 // chip select top

#define LEFT_TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define LEFT_ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define CENTER_TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define CENTER_ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define RIGHT_TRIGGER_PIN  A4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define RIGHT_ECHO_PIN  A5  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define NUMBER_COLUMN 40

NewPing sonar_left(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_center(CENTER_TRIGGER_PIN, CENTER_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_right(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int distance_left;
int distance_center;
int distance_right;

int counter; // main loop counter

void setup() {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
}

void loop() {

  // keep polling until we get a non-zero value
  do {
    delay(33);
    distance_center = sonar_center.ping_cm();
  } while (distance_center == 0);

  distance_left = sonar_left.ping_cm();
  distance_right = sonar_right.ping_cm();
  
  u8g2.firstPage();
  do {
    u8g2.home();
    u8g2.drawStr(10, 10,"Three Ping Test");

    u8g2.drawStr(0, 20,"Left:");
    u8g2.setCursor(NUMBER_COLUMN, 20);
    u8g2.print(distance_left);
    
    u8g2.drawStr(0, 30,"Center:");
    u8g2.setCursor(NUMBER_COLUMN, 30);
    u8g2.print(distance_center);

    u8g2.drawStr(0, 40,"Right:");
    u8g2.setCursor(NUMBER_COLUMN, 40);
    u8g2.print(distance_right);

    if (distance_center < 13) {
        u8g2.drawStr(0, 50,"Turning");
        if (distance_left < distance_right)
           u8g2.drawStr(NUMBER_COLUMN, 50,"Right");
        else u8g2.drawStr(NUMBER_COLUMN, 50,"Left");
    }

    u8g2.drawStr(0,63,"Counter:");
    u8g2.setCursor(NUMBER_COLUMN+10, 63);
    u8g2.print(counter);
    
  } while ( u8g2.nextPage() );
  
  delay(33);
  counter++;
}

