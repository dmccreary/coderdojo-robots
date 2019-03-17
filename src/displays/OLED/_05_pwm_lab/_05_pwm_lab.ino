#include <Arduino.h>
// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>

// order on OLED - GND, VCC, SCL, SDA, RDS, DC, CS
// #define SCL_PIN 13 // SCL clock - SCL is pin 13 on the Arduino Nano
// #define SDA_PIN 11 // SDA, Data, MOSI - must be on pin 11 on the Nano
#define RDS_PIN 10 // Reset
#define DC_PIN 9 // Data/Command
#define CS_PIN 8 // Chip select

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the SSD1306, 128x64, single-page, unnamed, 4 wire, Hardware, SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int width = 2; // width of the pulse
#define HEIGHT 40 // hight of the wave
#define MAX_WIDTH 64
void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
  welcome();
  delay(3000);
}

void loop(void) {
  u8g2.firstPage();
  do {
    draw_square_wave(width, HEIGHT, 50);
  } while ( u8g2.nextPage() );
  delay(500);
  width++;
  if (width > MAX_WIDTH) width = 0;
}

void draw_square_wave(int width, int height, int percent) {
    u8g2.drawHLine(0, height, width);
    u8g2.drawVLine(width, 0, height);
    u8g2.drawHLine(width, 0, width);
    u8g2.drawVLine(2*width, 0, height);
    u8g2.drawHLine(2*width, height, width);
}

void welcome() {
  u8g2.firstPage();
  do {
    u8g2.drawStr(0, 8,  "CoderDojo PWM Lab");
    u8g2.drawStr(0, 18, "http://bit.ly/2TTMxOj");
    u8g2.drawStr(0, 28, "Dan McCreary");
    u8g2.drawStr(0, 38, "Turn knob to change");
    u8g2.drawStr(0, 48, "pulse width.");
  } while ( u8g2.nextPage() );
}
