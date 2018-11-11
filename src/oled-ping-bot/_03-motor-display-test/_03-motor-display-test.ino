/*
 * This test will cycle between the four directions for the wheel motors. The display will show the wheel
 * being tested and draw an arrow for the direction and side.
 * If you pass this test it indcates the display and wheel connections are all correct.
 */

#include <Arduino.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>

// change these numbers until you get right forward, right backward, left forward, left reverse
// you can only use PWM pins.  On the Arduino Nano these are 3, 5, 6, 9, 10 and 11
// We are going to tuse pin 3 as an interrupt so we can't use it here
#define RIGHT_FORWARD_PIN 3
#define RIGHT_REVERSE_PIN 5
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 9

// order on OLED - GND, VCC, SCL, SDA, RDS, DC, CS
#define SCL_PIN 13 // SCL clock - 3rd from bottom
#define SDA_PIN 11 // SDA, Data, MOSI - must be on pin 11 on the Nano
#define RDS_PIN 10 // reset
#define DC_PIN 7 // DC moved from pin 9 which is needed as a PWM pin
#define CS_PIN 8 // chip select top

int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 1000; // delay between tests
int delay_end_of_test= 3000; // delay between tests

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

int counter; // main loop counter

void setup() {
  // Turn these pins on for PWM OUTPUT
  // you can use digitalWrite for testing if the PWM pins are not free
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  // turn all the motors off
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, 0);
  // for debugging.  The output will appear on the serial monitor
  // To open the serial monitor, click the magnafing glass icon in the upper right corner

   u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
  
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop() {
  
  Serial.println("Right Forward Test");
  u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"Motor Test");
    u8g2.drawStr(0,18,"Right Forward");
    u8g2.drawTriangle(24,20, 40,20, 32, 48);
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  analogWrite(RIGHT_FORWARD_PIN, 255);
  delay(delay_time_on);
  analogWrite(RIGHT_FORWARD_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Right reverse test");
  u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"Motor Test");
    u8g2.drawStr(0,18,"Right Reverse");
    u8g2.drawTriangle(24,48, 40,48, 32, 20);
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  analogWrite(RIGHT_REVERSE_PIN, 255);
  delay(delay_time_on);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Left Forward Test");
  u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"Motor Test");
    u8g2.drawStr(0,18,"Left Forward");
    u8g2.drawTriangle(88,20, 104,20, 96, 48);
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  analogWrite(LEFT_FORWARD_PIN, 255);
  delay(delay_time_on);
  digitalWrite(LEFT_FORWARD_PIN, 0);
  delay(delay_time_off);
  
  Serial.println("Left Reverse Test");
    u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"Motor Test");
    u8g2.drawStr(0,18,"Left Reverse");
    u8g2.drawTriangle(88,48, 104,48, 96, 20);
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  digitalWrite(LEFT_REVERSE_PIN, 255);
  delay(delay_time_on);
  digitalWrite(LEFT_REVERSE_PIN, 0);
  
  delay(delay_end_of_test);

  u8g2.firstPage();
  do {    
    u8g2.drawStr(0,8,"Motor Test");
    u8g2.setCursor(0,63);
    u8g2.print(counter);
  } while ( u8g2.nextPage() );
  
  counter++;
}


