// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <Arduino.h>
#include <NewPing.h>
#include <U8g2lib.h> // note version 2 of the U8g library!
#include <SPI.h>

#define RIGHT_FORWARD_PIN 3
#define RIGHT_REVERSE_PIN 5
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 9

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define DATA_PIN 11 // SDA, MOSI
#define CLOCK_PIN 13 // SCL
#define CS_PIN A0 // chip select
#define DC_PIN A1 // Also known as address 0 or A0, not analog 0
#define RES_PIN A2 //  for SPI mode the RES pin becomes "Chip Select".
// We are using a 4 wire hardware SPI communications system.  Data is on pin 11 and clock on 13
// U8G2_R0 is the rotation number
// The Frame buffer option (1,2,F) should be 1 due limitations of memory.  1 uses under 32% of 2K RAM
U8G2_SSD1306_128X64_VCOMH0_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RES_PIN);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
char buf[20];
int counter = 0;

void setup() {
  pinMode(DC_PIN, OUTPUT);
  digitalWrite(DC_PIN, 0);  // default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0
  u8g2.begin();
  // load standard 20px high font
  u8g2.setFont(u8g_font_unifont);

  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
int dist = sonar.ping_cm();
  u8g2.clearBuffer();
  u8g2.drawStr(0,10,"Hello World!");
  // convert the integer into a string
  sprintf(buf, "1/10 sec: %d", counter);
  u8g2.drawStr(0,24,buf);

  sprintf(buf, "dist: %d", dist);
  u8g2.drawStr(0,44,buf);
  u8g2.sendBuffer();
  // wait between pings
  delay(100);
  counter++;
                   
  Serial.print("Ping: ");
  Serial.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
}
