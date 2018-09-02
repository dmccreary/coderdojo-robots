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

#define PADDLE_PIN_1 A0

#define RADIUS 3
// We are using a 4 wire hardware SPI communications system.  Data is on pin 11 and clock on 13
// U8G2_R0 is the rotation number
U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RES_PIN);

// circle positon
int x, y;
// circle direction
int xd, yd;
int paddle_pos_1;

void setup() 
{
  pinMode(DC_PIN, OUTPUT);
  digitalWrite(DC_PIN, 0);  // default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0
  u8g2.begin();
  // load standard 20px high font
  u8g2.setFont(u8g_font_unifont);
  x = random(0, 128);
  y = random(0, 64);
  xd = random(0,2);
  if (xd == 0) xd = -1;
  yd = random(0,2);
  if (yd == 0) yd = -1;
  
}

void loop() 
{
  paddle_pos_1 = analogRead(PADDLE_PIN_1);
  // scale to hieght of display less have the paddle height
  paddle_pos_1 = map(paddle_pos_1, 0, 1023, 4, 59);
  u8g2.firstPage();
  do {
    u8g2.drawBox(125, paddle_pos_1 - 4, 3, 8);
    u8g2.drawDisc(x, y, RADIUS, U8G2_DRAW_ALL);
  } while(u8g2.nextPage());

  
  
  delay(5);
  if (x - RADIUS < 0) xd = 1;
  if (x + RADIUS > 126) xd = -1;
  if (y - RADIUS < 0) yd = 1;
  if (y + RADIUS > 62) yd = -1;
  if (x > 126) x = 0;
  else x += xd;
  if (y > 62) y = 0;
  else y += yd;
}


