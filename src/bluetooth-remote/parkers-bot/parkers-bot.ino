#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

// If you are using Software Serial....
// The following macros declare the pins used for SW serial, you should
// use these pins if you are connecting the UART Friend to an UNO
#define BLUEFRUIT_SWUART_RXD_PIN        9    // Required for software serial!
#define BLUEFRUIT_SWUART_TXD_PIN        10   // Required for software serial!
#define BLUEFRUIT_UART_CTS_PIN          11   // Required for software serial!
#define BLUEFRUIT_UART_RTS_PIN          -1   // Optional, set to -1 if unused

// If you are using Hardware Serial
// The following macros declare the Serial port you are using. Uncomment this
// line if you are connecting the BLE to Leonardo/Micro or Flora
//#define BLUEFRUIT_HWSERIAL_NAME           Serial1

// Other recommended pins!
#define BLUEFRUIT_UART_MODE_PIN         12   // Optional but recommended, set to -1 if unused

/*=========================================================================
    APPLICATION SETTINGS

    VERBOSE_MODE            If set to 1 enables full data output (for
                            debugging), otherwise set it to 0 to disable
                            verbose output
    BLE_READPACKET_TIMEOUT  The timeout in ms waiting for a data packet
    -----------------------------------------------------------------------*/
    #define VERBOSE_MODE                    1
    #define BLE_READPACKET_TIMEOUT          500
/*=========================================================================*/
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 2;
int power_forward_right = 200; /* half power on turns */
int power_forward_left = 200; /* half power on turns */
int waitTime = 100;
#define LEDPIN  7 // connect the Data In pin
#define NUMBER_PIEXELS 12// connect the Data In pin
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIEXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
// this constant won't change:


/* Create the bluefruit object, either software serial... */

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);

Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN,
                      BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

/* ...or hardware serial, which does not need the RTS/CTS pins. Uncomment this line */
//Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);


// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BluefruitLE_UART *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];


/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void setup(void){
  while (!Serial);
  delay(500);
  strip.begin();
  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit App Controller Example"));
  Serial.println(F("-----------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

    /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.print(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }
  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();
  
  ble.verbose(false);  // debug info is a little annoying after this point!
  
  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  // turn all off
  digitalWrite(right_forward, LOW);
  digitalWrite(right_reverse, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);

  // for debugging
  // Serial.println('Start');
  delay(1000);   
      
      
}
  
  Serial.println(F("*****************"));

  // Set module to DATA mode
  if (BLUEFRUIT_UART_MODE_PIN >= 0) {
    Serial.println( F("Switching to DATA mode using the MODE pin!") );
    ble.setModePin(BLUEFRUIT_MODE_DATA);
  } else {
    Serial.println( F("Switching to DATA mode using +++!") );
    ble.println("+++");
    delay(10);
  }

  Serial.println(F("*****************"));

}

/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop(void){  

  /* Wait for new data to arrive */
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  /* Got a packet!
  // printHex(packetbuffer, len);

  // Color
  if (packetbuffer[1] == 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    Serial.print ("RGB #"); 
    if (red < 0x10) Serial.print("0");
    Serial.print(red, HEX);
    if (green < 0x10) Serial.print("0");
    Serial.print(green, HEX);
    if (blue < 0x10) Serial.print("0");
    Serial.println(blue, HEX);
  }*/
  
  // Buttons
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    int ButtonNumber = packetbuffer[2];
    boolean pressed = packetbuffer[3] - '0';
    Serial.print(ButtonNumber);
    if (pressed) {
      Serial.println(" pressed");
      if (ButtonNumber == 53){
        move_forward();
      }
      if (ButtonNumber == 54){
        move_backward();
      }
      if (ButtonNumber == 55){
        turn_right();
      }
      if (ButtonNumber == 56){
        turn_left();
      }
      if (ButtonNumber == 49){
        colorWipe(strip.Color(0,0,0), waitTime);
      }
      if (ButtonNumber == 50){
        colorWipe(strip.Color(255, 0, 0), waitTime); // Red
      }
      if (ButtonNumber == 51){
        colorWipe(strip.Color(0, 255, 0), waitTime); // Green
      }
      if (ButtonNumber == 52){
        colorWipe(strip.Color(0, 0, 255), waitTime); // Blue
      }
    } else {
      Serial.println(" released");
        do_nothing();
        
    }
  }
  
}



  /*=// GPS Location
  if (packetbuffer[1] == 'L') {
    float lat, lon, alt;
    lat = parsefloat(packetbuffer+2);    
    lon = parsefloat(packetbuffer+6);    
    alt = parsefloat(packetbuffer+10);
    Serial.print("GPS Location\t"); 
    Serial.print("Lat: "); Serial.print(lat, 4); // 4 digits of precision!
    Serial.print('\t');
    Serial.print("Lon: "); Serial.print(lon, 4); // 4 digits of precision!
    Serial.print('\t');
    Serial.print(alt, 4); Serial.println(" meters");
  }
  
  // Accelerometer
  if (packetbuffer[1] == 'A') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);    
    y = parsefloat(packetbuffer+6);    
    z = parsefloat(packetbuffer+10);
    Serial.print("Accel\t"); 
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
  }
  
  // Magnetometer
  if (packetbuffer[1] == 'M') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);    
    y = parsefloat(packetbuffer+6);    
    z = parsefloat(packetbuffer+10);
    Serial.print("Mag\t"); 
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
  }
  
  // Gyroscope
  if (packetbuffer[1] == 'G') {
    float x, y, z;
    x = parsefloat(packetbuffer+2);    
    y = parsefloat(packetbuffer+6);    
    z = parsefloat(packetbuffer+10);
    Serial.print("Gyro\t"); 
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.println();
  }
  
  // Quaternions
  if (packetbuffer[1] == 'Q') {
    float x, y, z, w;
    x = parsefloat(packetbuffer+2);    
    y = parsefloat(packetbuffer+6);    
    z = parsefloat(packetbuffer+10);
    w = parsefloat(packetbuffer+14);
    Serial.print("Quat\t"); 
    Serial.print(x); Serial.print('\t');
    Serial.print(y); Serial.print('\t');
    Serial.print(z); Serial.print('\t');
    Serial.print(w); Serial.println();
  }*/
void turn_right(void){
  Serial.println("turning right");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, power_forward_right);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);

}

void move_forward(void) {
  Serial.println("moving forward");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
}

void move_backward(void){
  Serial.println("moving backward");
  analogWrite(right_reverse, power_forward_right);
  analogWrite(right_forward, LOW);
  analogWrite(left_reverse, power_forward_left);
  analogWrite(left_forward, LOW);
}

void turn_left(void){
  Serial.println("turning left");
  analogWrite(right_forward, power_forward_right);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
  analogWrite(left_reverse, power_forward_left);
}

void do_nothing(void){
  Serial.println("Doing Nothing");
  analogWrite(right_forward, LOW);
  analogWrite(right_reverse, LOW);
  analogWrite(left_forward, LOW);
  analogWrite(left_reverse, LOW);
  
}

void mainMenu() {
   strip.setPixelColor(0, 255, 0, 0);     // make the 1st pixel red
   strip.setPixelColor(1, 0, 255, 0);     // make the 2nd pixel green
   strip.setPixelColor(2, 0, 0, 255);     // make the 3rd pixel blue
   strip.setPixelColor(3, 255, 255, 255); // make the 4th pixel white
   strip.setPixelColor(4, 255, 255, 0);   // make the 5th pixel yellow
   strip.setPixelColor(5, 0, 255, 255);   // make the 6th pixel aqua
   strip.setPixelColor(6, 255, 0, 255);   // make the 7th pixel fuchsia
   strip.setPixelColor(7, 200, 130, 0);   // make the 8th pixel orange (changed from 255, 165, 0)
   strip.setPixelColor(8, 80, 0, 80);     // make the 9th pixel purple
   strip.setPixelColor(9, 143, 188, 143); // make the 10th pixel DarkSeaGreen
   strip.setPixelColor(10, 218, 165, 32);  // make the 11th pixel Goldenrod
   strip.setPixelColor(11, 127, 255, 212);  // make the 11th pixel Aquamarine
   strip.show(); // must use to refresh the strip
}

void colorWipe(uint32_t color, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(wait);
  }
}
