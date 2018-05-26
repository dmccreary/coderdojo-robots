/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <SPI.h>
#include <Wire.h>
#include <VL53L0X.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

VL53L0X sensor;
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(4);
  display.setTextColor(WHITE);

  sensor.startContinuous();
}

int distance;
void loop()
{
  distance   = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println(distance);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(distance);
  display.print(" mm");
  display.display();

}
