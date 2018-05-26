/*
  Universal 8bit Graphics Library, https://github.com/olikraus/u8glib/
*/
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 

int distance;

void draw(int distance) {
 
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(10, 20); 
  // call procedure from base class, http://arduino.cc/en/Serial/Print
  u8g.print(distance);
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
   Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}


void loop(void) {
  distance = sensor.readRangeContinuousMillimeters();
  // Serial.print(distance);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  // picture loop
  u8g.firstPage();  
  do {
    draw(distance);
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(50);
}

