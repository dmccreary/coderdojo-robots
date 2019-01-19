/*
  CoderDojo Robots OLED test
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

// single page - 4 wire, hardware, SPI interface where SCL is on pin 13 and SDA is on pin 11
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

int counter = 0;

void setup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.drawStr(0,24,"CoderDojo Rocks");
  } while ( u8g2.nextPage() );
  //delay(1000);
}
