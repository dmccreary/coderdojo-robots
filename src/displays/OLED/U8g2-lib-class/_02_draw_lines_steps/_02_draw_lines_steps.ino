#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

// The pins I used on the Arduino Nano
// See https://github.com/olikraus/u8g2/wiki/setup_tutorial
#define CLOCK_PIN 13 // SCL
#define DATA_PIN 11 // SDA, MOSI
#define RES_PIN 8 //  for SPI mode the RES pin becomes "Chip Select".
#define DC_PIN 9 // Also known as address 0 or A0, not analog 0
#define CS_PIN 10 // chip select

// We are using a 4 wire hardware SPI communications system.  Data is on pin 11 and clock on 13
// U8G2_R0 is the rotation number
U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RES_PIN);
void setup() 
{
  pinMode(DC_PIN, OUTPUT);
  digitalWrite(DC_PIN, 0);  // default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0
  u8g2.begin();
  // load standard 20px high font
  u8g2.setFont(u8g_font_unifont);
}

void loop() 
{
  u8g2.firstPage();  

  do {
    int steps = 4;
    int dx = 128/steps;
    int dy = 64/steps;
    int y = 0;
    for(int x=0; x<128; x+=dx) {
        u8g2.drawLine(x, 0, 127, y);
        u8g2.drawLine(127-x, 63, 0, 63-y);
       y+=dy;     
    }
  } while(u8g2.nextPage());
  delay(1000);
  

   do {
    int steps = 8;
    int dx = 128/steps;
    int dy = 64/steps;
    int y = 0;
    for(int x=0; x<128; x+=dx) {
        u8g2.drawLine(x, 0, 127, y);
        u8g2.drawLine(127-x, 63, 0, 63-y);
       y+=dy;     
    }
  } while(u8g2.nextPage());
  delay(1000);
  
  do {
    int steps = 16;
    int dx = 128/steps;
    int dy = 64/steps;
    int y = 0;
    for(int x=0; x<128; x+=dx) {
        u8g2.drawLine(x, 0, 127, y);
        u8g2.drawLine(127-x, 63, 0, 63-y);
       y+=dy;     
    }
      
  } while(u8g2.nextPage());
  delay(1000);
  
  do {
    int steps = 32;
    int dx = 128/steps;
    int dy = 64/steps;
    int y = 0;
    for(int x=0; x<128; x+=dx) {
        u8g2.drawLine(x, 0, 127, y);
        u8g2.drawLine(127-x, 63, 0, 63-y);
       y+=dy;     
    }
      
  } while(u8g2.nextPage());

 delay(1000);
   do {
    int steps = 64;
    int dx = 128/steps;
    int dy = 64/steps;
    int y = 0;
    for(int x=0; x<128; x+=dx) {
        u8g2.drawLine(x, 0, 127, y);
        u8g2.drawLine(127-x, 63, 0, 63-y);
       y+=dy;     
    }
      
  } while(u8g2.nextPage());
  delay(1000);
}


