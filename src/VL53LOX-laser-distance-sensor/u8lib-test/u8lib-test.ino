/*
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
*/


#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(10, 20); 
  // call procedure from base class, http://arduino.cc/en/Serial/Print
  u8g.print("Hello World!");
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
}

