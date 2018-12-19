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
#define DC_PIN 7 // DC moved from pin 9 which is needed as a PWM pin
#define CS_PIN 8 // chip select top

#define TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int echo_time;
int distance_cm;
int counter; // main loop counter

void setup() {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
}

void loop() {
  echo_time = sonar.ping();

  // keep polling until we get a non-zero value
  do {
    delay(33);
    distance_cm = sonar.ping_cm();
  } while (distance_cm == 0);
  
  u8g2.firstPage();
  do {
    u8g2.home();
    u8g2.drawStr(10, 10,"Ping Test");

    u8g2.drawStr(0, 20,"Echo Time:");
    u8g2.setCursor(80, 20);
    u8g2.print(echo_time);
    
    u8g2.drawStr(0, 30,"Distance (cm):");
    u8g2.setCursor(80, 30);
    u8g2.print(distance_cm);

    u8g2.drawStr(0,40,"Counter:");
    u8g2.setCursor(80, 40);
    u8g2.print(counter);

    if (distance_cm < 13)
       u8g2.drawStr(0, 6
       0,"Turning...");
  } while ( u8g2.nextPage() );
  
  delay(100);
  counter++;
}

