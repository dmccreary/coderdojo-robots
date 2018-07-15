/*

  HelloWorld.pde
  
  "Hello World!" example code.
*/


#include <Arduino.h>
#include <U8g2lib.h>
#define DATA_PIN 11 // SDA, MOSI
#define CLOCK_PIN 13 // SCL

#define CS_PIN 10 // chip select
#define DC_PIN 9 // Also known as address 0 or A0, not analog 0
#define RESET_PIN 8 // reset

// failsU8GLIB_SSD1306_128X64 u8g(CLOCK_PIN, DATA_PIN, CS_PIN, DC_PIN);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
// U8GLIB_SSD1306_128X64 u8g(CLOCK_PIN, DATA_PIN, CS_PIN, DC_PIN);	// SW SPI Com: SCK = 4, MOSI = 5, CS = 6, A0 = 7 (new white HalTec OLED)
// U8GLIB_SSD1306_128X64 u8g(CS_PIN, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)

// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI 

// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send AC

//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(13, 11, 10, 9);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9
//U8GLIB_SSD1306_ADAFRUIT_128X64 u8g(10, 9);		// HW SPI Com: CS = 10, A0 = 9 (Hardware Pins are  SCK = 13 and MOSI = 11)

U8G2_SSD1306_128X64_VCOMH0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g2.drawStr( 0, 22, "Hello World!");
}

void setup(void) {
  // flip screen, if required
  // u8g2.setRot180();
  
  // set SPI backup if required
  //u8g2.setHardwareBackup(u8g_backup_avr_spi);
}

void loop(void) {
  // picture loop
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
  // rebuild the picture after some delay
  //delay(50);
}

