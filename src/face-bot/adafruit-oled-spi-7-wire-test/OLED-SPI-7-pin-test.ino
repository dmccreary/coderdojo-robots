/* 
 * Demo for SSD1306 based 128x64 OLED module using Adafruit SSD1306 
 * library (https://github.com/adafruit/Adafruit_SSD1306).
 * 
 * See https://github.com/pacodelgado/arduino/wiki/SSD1306-based-OLED-connected-to-Arduino 
 * for more information.
 *
 */
 
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

float counter = 0;

void setup()   {                
//  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("CoderDojo Face Robot");
  
  display.setCursor(0,12);
  display.print("Version 1");

  display.setCursor(0,24);
  display.print("128x64 OLED $19");

  display.setCursor(0,36);
  display.print("Adafruit SSD1306 SPI");
  
  display.setCursor(0,48);
  display.print("Dan.McCreary@gmail");
  
  display.display();
  delay(5000); // disply for 5 seconds
}

void loop()
{
  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;
  display.clearDisplay();
  display.setCursor(20,20);
  display.print(counter/10.0);
  display.print(" seconds");
  display.display();
  delay(100);
  counter++;
}

