/*  The LED Matrix lab introduces the control of a 8x8 LED Matrix that is connected using the MAX7219 LED Display driver Chip.
 *  This lab requires the LedControl library to be installed. You can get it from https://github.com/wayoda/LedControl.
 *  
 *  Make the following connections:
 *  MAX7219 8x8 Dot Matrix Module PIN VCC -> Arduino 5V
 *  MAX7219 8x8 Dot Matrix Module PIN GND -> Arduino GND
 *  MAX7219 8x8 Dot Matrix Module PIN DIN -> Arduino D12
 *  MAX7219 8x8 Dot Matrix Module PIN CS  -> Arduino D10
 *  MAX7219 8x8 Dot Matrix Module PIN CLK -> Arduino D11
 *  Potentiometer Pin 1                   -> Arduino 5V
 *  Potentiometer Pin 2                   -> Arduino A0
 *  Potentiometer Pin 3                   -> Arduino GND
 *  A simplified breadboard schematic is also available in this folder. 
 */


#include "LedControl.h"

LedControl lc=LedControl(12,11,10,1);     // DIN,CLK and CS Pins of LED Matrix and # of Matrices

int moodPotPin = 0;                       // Potentiometer pin
int moodPotValue = 0;                     // Value read from the potentiometer, initialized to zero


/*  Arrays of characters that can be displayed on the LED Matrix. 
 *  Each line(byte) represents a row, each bit represents a pixel.
 *  A '0' will turn the pixel OFF and a '1' will turn a pixel ON.
 *  These array can be generated using tools such as the one 
 *  available here: http://blog.riyas.org/2013/12/online-led-matrix-font-generator-with.html
 */

byte happy_bytes[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte sad_bytes[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

byte straight_bytes[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10000001,
  B10111101,
  B01000010,
  B00111100
};

byte surprise_bytes[] =
{
  B00111100,
  B01000010,
  B10100101,
  B10011001,
  B10100101,
  B10100101,
  B01011010,
  B00111100
};



void setup()
{
  lc.shutdown(0,false);                   // Wake up displays
  lc.setIntensity(0,5);                   // Set intensity levels
  lc.clearDisplay(0);                     // Clear Displays
}


//  Functions to take values in Arrays and Display them
void happy()
{
  for (int i = 0; i < 8; i++)             // Cycle through the number of rows (8)
  {
    lc.setRow(0,i,happy_bytes[i]);        // Program each row of the matrix with value from the array
  }
}

void sad()
{
  for (int i = 0; i < 8; i++)             // Cycle through the number of rows (8)
  {
    lc.setRow(0,i,sad_bytes[i]);          // Program each row of the matrix with value from the array
  }
}

void straight()
{
  for (int i = 0; i < 8; i++)             // Cycle through the number of rows (8) 
  {
    lc.setRow(0,i,straight_bytes[i]);     // Program each row of the matrix with value from the array
  }
}

void surprise()
{
  for (int i = 0; i < 8; i++)             // Cycle through the number of rows (8)
  {
    lc.setRow(0,i,surprise_bytes[i]);     // Program each row of the matrix with value from the array
  }
}

void loop()
{
  moodPotValue = analogRead(moodPotPin);  // Check for the value read from the potentiometer (this will have a value between 0 and 1024)
  
  if (moodPotValue < 256 )                // If the value is between 0 and 256
  {
    happy();                              // Display happy face
  }
  else if (moodPotValue < 512 )           // If the value is between 256 and 512
  {
    sad();                                // Display sad face
  }
  else if (moodPotValue < 768 )           // If the value is between 512 and 768
  {
    straight();                           // Display straight face
  }
  else                                    // If the value is between 768 and 1024
  {
    surprise();                           // Display surprise face
  }
}
