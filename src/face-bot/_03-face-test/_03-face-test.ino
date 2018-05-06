/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_CLK   13   // SCL
#define OLED_MOSI  12   // SDA
#define OLED_RESET 11   // RST
#define OLED_DC    10   // DC
#define OLED_CS    8    //CS


Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

long counter = 0;
int half_width = 0;

void setup()   {                
   display.begin(SSD1306_SWITCHCAPVCC);
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.display();
   half_width = display.width()/2;
}


void loop() {
  // draw a white circle, 10 pixel radius
  display.clearDisplay();
  // 64 pixels high 32 radius
  // background circle in white
  display.fillCircle(half_width, display.height()/2, 31, WHITE);

  // left and right eye
  display.fillCircle(half_width - 10, display.height()/3, 4, BLACK);
  display.fillCircle(half_width + 10, display.height()/3, 4, BLACK);

  // mouth
  display.drawLine(half_width - 10, display.height()/3 * 2, half_width + 10, display.height()/3 * 2, BLACK);
  // font is 8 pixels high - 56 + 8 = 64
  display.setCursor(0,56);
  display.print(counter);
  display.display();
  delay(1000);
  counter++;
}


void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
}









