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

int percent = 0; // percent high of total pulse width
int high_width = 0;
int start = 0;
  
#define HEIGHT 15 // hight of the wave
#define PULSE_WIDTH 16 // pixels in the pulse width
#define NUM_PULSES 7 // pulses we can fit on the 128 wide screen screen
#define PULSE_TOP_OFFSET 20 // offset from the top of the screen down to draw the top of the pulse wave

void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
  // u8g2.setDrawColor(1);
  welcome();
  // delay(3000);
  Serial.begin(9600);
}

void loop(void) {

  u8g2.firstPage();
  do {

    // draw NUM_PULSES square waves at a fixed distance apart
    start = 0;
    for (int i=0; i<=NUM_PULSES; i++) {
      draw_single_pulse(start, 14, high_width);
      start += PULSE_WIDTH; 
    }

    start = 0;
    for (int i=0; i<=NUM_PULSES; i++) {
      draw_single_pulse(start, 35, high_width);
      start += PULSE_WIDTH; 
    }

    u8g2.drawStr(0, 10, "Pulse Width Modulation");
    
    u8g2.drawStr(0, 63, "Fwd:");
    u8g2.setCursor(30, 63);
    u8g2.print(percent);

    u8g2.drawStr(56, 63, "Rev:");
    u8g2.setCursor(80, 63);
    u8g2.print(percent);
    
    u8g2.setCursor(110, 63);
    u8g2.print(high_width);
    
    
  } while ( u8g2.nextPage() );
  
  delay(1000);
  high_width++; // cycles between 1 and CYCLE_WIDTH
  if (high_width > PULSE_WIDTH) high_width = 1;
  percent = high_width * 6.25;
}

// start is the screen x-position (horizontal) and high-with is the height of the high pulse
void draw_single_pulse(int start, int top_offset, int high_width) {
    u8g2.drawVLine(start, top_offset, HEIGHT); // first vertical base to top
    // u8g2.drawLine(start, top_offset, start, HEIGHT);
    u8g2.drawHLine(start, top_offset, high_width); // top horizontal line of width of the height of the high part of the square wave
    u8g2.drawVLine(start + high_width, top_offset, HEIGHT); // top down to base
    u8g2.drawHLine(start + high_width, HEIGHT + top_offset, PULSE_WIDTH - high_width); // lower horizontal

//    Serial.print("start: ");
//    Serial.print(start);
//    Serial.print(" high width:");
//    Serial.print(high_width);
//    Serial.print(" low width:");
//    Serial.println(PULSE_WIDTH - high_width);
//    delay(100);
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
