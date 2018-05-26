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

#define RIGHT_IR_PIN A0
#define CENTER_IR_PIN A1
#define LEFT_IR_PIN A2

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
  delay(500); // disply for 5 seconds
}

void loop()
{
  int right_sensor_value = digitalRead(RIGHT_IR_PIN);
  int center_sensor_value = digitalRead(CENTER_IR_PIN);
  int left_sensor_value = digitalRead(LEFT_IR_PIN);
  display.clearDisplay();
  

  if (right_sensor_value == LOW) {
    display.setCursor(0,0);
    display.print("Right");
  };
  if (center_sensor_value == LOW) {
    display.setCursor(0,10);
    display.print("Center");
  };
  if (left_sensor_value == LOW) {
    display.setCursor(0,20);
    display.print("Left");
  };

  //display.setCursor(0,54);
  //display.print(counter);
  display.display();
  //delay(100);
  counter++;
}

