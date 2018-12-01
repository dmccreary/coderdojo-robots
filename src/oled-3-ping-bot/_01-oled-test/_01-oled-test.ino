#include <Arduino.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>

// order on OLED - GND, VCC, SCL, SDA, RDS, DC, CS
#define SCL_PIN 13 // SCL clock - 3rd from bottom
#define SDA_PIN 11 // SDA, Data, MOSI - must be on pin 11 on the Nano
#define RDS_PIN 10 // reset
// pin 9 is a PWM reserved for the motor
#define DC_PIN 8 // DC moved from pin 9 which is needed as a PWM pin
#define CS_PIN 7 // chip select top

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int counter; // main loop counter

void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
}

void loop(void) {
  u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"CoderDojo Rocks!");
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  delay(10);
  counter++;
}


