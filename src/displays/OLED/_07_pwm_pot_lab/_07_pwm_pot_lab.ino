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

#define POT_PIN A0 // Analog potentiometer

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the SSD1306, 128x64, single-page, unnamed, 4 wire, Hardware, SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int fwd_percent = 0; // percent high of total pulse width
int rev_percent = 0;
int high_width = 0;
int start;
int pot_value;
// int counter; // main loop counter for debug

#define HEIGHT 15 // hight of the pulse in pixels
#define PULSE_WIDTH 16 // pixels in the pulse width
#define NUM_PULSES 7 // pulses we can fit on the 128 wide screen screen
#define PULSE_TOP_OFFSET 15 // offset from the top of the screen down to draw the top of the pulse wave - leave room to draw the title
#define PULSE_LEFT_OFFSET 8 // offset from the top of the screen down to draw the top of the pulse wave - leave room to draw the title
#define FWD_REV_SEP 10 // separation between forward and reverse pulse waves

void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
  // u8g2.setDrawColor(1);
  welcome();
  delay(3000);
  Serial.begin(9600);
}

void loop(void) {

  // average 5 values to get rid of noise
  for (int i=0; i<10; i++) {
     pot_value += analogRead(POT_PIN);
     delay(10);
  };
  pot_value = pot_value/10;

  // scale between a negative and positive pulse width in pixels
  pot_value = map(pot_value, 10, 1010, -PULSE_WIDTH, PULSE_WIDTH);

  u8g2.firstPage();
  do {

    // draw NUM_PULSES square waves at a fixed distance apart

    start = 0;
    if (pot_value < 0) {
      // we have n reverse speed
      // draw a flat line for the forward PWM when we are going in reverse
      u8g2.drawHLine(PULSE_TOP_OFFSET, PULSE_TOP_OFFSET + (HEIGHT * 2) + 4, 123);
      // draw the lower PWM lines      
      for (int i=0; i<=NUM_PULSES; i++) {
        draw_single_pulse(start, 14, -pot_value);
        start += PULSE_WIDTH; 
      }
      fwd_percent = 0;
      rev_percent = pot_value * -6.25;
      
    } else {
      // we have a forward speed
      // draw the reverse PWM as flat
      u8g2.drawHLine(PULSE_TOP_OFFSET, PULSE_TOP_OFFSET + HEIGHT, 123);
      for (int i=0; i<=NUM_PULSES; i++) {
        draw_single_pulse(start, 35, pot_value);
        start += PULSE_WIDTH; 
      }
      fwd_percent = pot_value * 6.25;
      rev_percent = 0;
    }

    // draw the labels
    u8g2.drawStr(0, 10, "Pulse Width Modulation");

    u8g2.drawStr(0, 28, "R:");
    u8g2.drawStr(0, 50, "F:");
    
    u8g2.drawStr(0, 63, "Rev:");
    u8g2.setCursor(25, 63);
    u8g2.print(rev_percent);
    
    u8g2.drawStr(50, 63, "Fwd:");
    u8g2.setCursor(75, 63);
    u8g2.print(fwd_percent);

    u8g2.setCursor(115, 63);
    u8g2.print(pot_value);

//    u8g2.setCursor(105, 63);
//    u8g2.print(counter);
    
  } while ( u8g2.nextPage() );
  
//  high_width++; // cycles between 1 and PULSE_WIDTH
//  if (high_width > PULSE_WIDTH) high_width = 1;
  Serial.println(pot_value);
  //counter++;
}

// start is the screen x-position (horizontal) and high-with is the height of the high pulse
void draw_single_pulse(int start, int top_offset, int high_width) {
    int left_border = PULSE_TOP_OFFSET + start;
    u8g2.drawVLine(left_border, top_offset, HEIGHT); // first vertical base to top
    // u8g2.drawLine(start, top_offset, start, HEIGHT);
    u8g2.drawHLine(left_border, top_offset, high_width); // top horizontal line of width of the height of the high part of the square wave
    u8g2.drawVLine(left_border + high_width, top_offset, HEIGHT); // top down to base
    u8g2.drawHLine(left_border + high_width, HEIGHT + top_offset, PULSE_WIDTH - high_width); // lower horizontal

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
