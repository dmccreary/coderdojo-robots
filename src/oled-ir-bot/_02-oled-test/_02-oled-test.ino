// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int counter = 0;

void setup () {
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   display.setTextSize(2);
   display.setTextColor(WHITE);
}

void loop () {

    display.clearDisplay();
    // 10 over (x) 20 down (y)
    display.setCursor(10, 20);
    display.print(counter);
    display.display();
     
    delay(1000);
    counter++;
}
