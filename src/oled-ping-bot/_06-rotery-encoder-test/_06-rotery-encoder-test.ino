#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Encoder.h>

// we will hog both the interrupt pins for best performance
#define ENC_A_PIN 2 // an interrupt pin
#define ENC_B_PIN 4 // not an interrupt pin

#define SET_PIN 12 // set the current encoder value to be the new variable
#define MODE_PIN A5 // change the programming mode

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(ENC_A_PIN, ENC_B_PIN);
long oldPosition  = -999;
byte mode = 0;
byte mode_count = 5;

#include <SPI.h>

// order on OLED - GND, VCC, SCL, SDA, RDS, DC, CS
#define SCL_PIN 13 // SCL clock - 3rd from bottom
#define SDA_PIN 11 // SDA, Data, MOSI - must be on pin 11 on the Nano
#define RDS_PIN 10 // reset
#define DC_PIN 7 // DC moved from pin 9 which is needed as a PWM pin
#define CS_PIN 8 // chip select top

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regurlar 8 pixel high font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

void loop(void) {
  // look for the new encoder number
  long newPosition = myEnc.read();
  newPosition = newPosition % 255;
  byte stop_value = newPosition/4;
  byte mode = stop_value % mode_count;
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    u8g2.firstPage();
      do {
          u8g2.drawStr(0,10,"Rotery Encoder Test");
          u8g2.drawStr(0,20,"Encoder Value:");
          u8g2.setCursor(75,20);
          // right justify but only works up to 3 digits
          u8g2.print(newPosition);

          u8g2.drawStr(0,30,"Stop Value:");
          u8g2.setCursor(75,30);
          // 1/4 of the position value
          u8g2.print(stop_value);

          u8g2.drawStr(0,40,"Mode:");
          u8g2.setCursor(75,40);
          // 1/4 of the position value
          u8g2.print(mode);
          
          } while ( u8g2.nextPage() );
   }
  delay(10);
}

