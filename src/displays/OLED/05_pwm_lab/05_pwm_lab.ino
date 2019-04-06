#include <Arduino.h>
#include <U8g2lib.h>
#define DATA_PIN 11 // SDA, MOSI
#define CLOCK_PIN 13 // SCL

#define CS_PIN 10 // chip select
#define DC_PIN 9 // Also known as address 0 or A0, not analog 0
#define RESET_PIN 8 // reset


U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);



void setup(void) {
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );;
}

void loop(void) {
  
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
}

void welcome(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setFont(u8g_font_unifont);
  u8g2.drawStr(0, 12, "CoderDojo Robots PWM Lab");
}

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g2.drawStr( 0, 22, "Hello World!");
}
