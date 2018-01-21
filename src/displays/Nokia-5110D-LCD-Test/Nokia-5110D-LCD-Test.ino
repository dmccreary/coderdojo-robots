
/*
 IR distance sensor using Sharp GP2Y0A21YK0F Analog Distance Sensor
 The sensor is hooked to A0 and returns a votage reading inversely proportional to the distance to an object
 Note that readings under 10CM and over 70CM are mostly invalid
 I purchaed on eBay in 2017 for US $3.38 (includes shipping from China)
 https://www.ebay.com/itm/202121681621
 EBay Sample:  https://www.ebay.com/itm/GP2Y0A21YK0F-Sharp-IR-Analog-Distance-Sensor-Distance-10-80CM-Free-Cable/202121681621?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649
 pin 7 - Serial clock out (SCLK)
 pin 6 - Serial data out (DIN)
 pin 5 - Data/Command select (D/C)
 pin 4 - LCD chip select (CS) - note you can hard-wire this to GND
 pin 3 - LCD reset (RST)
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
int loop_counter=0;

void setup() {
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(45);
  display.clearDisplay();   // clears the screen and buffer

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Setup Complete");
  display.display();
  delay(2000); // wait 2 seconds
}

void loop () {
  display.clearDisplay();
   display.setTextSize(3);
  display.setCursor(0,20);
  display.println(loop_counter);
  display.display();
  delay(200);
  loop_counter++;
}

