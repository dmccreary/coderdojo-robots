# Adding a Face to Your Robot
This version of our robot has an nice high-contrast screen on the front of it.  We moved the ping
sensor below the chasis so that there would be room top front of the robot for the screen.  We
can draw several things on our screen, including a face with two eyes and a mouth using simple
drawing commands as well as parameters for controlling the robot.

# The OLED Screen
Although there are many types of small displays that you can use with the Arduino, my favorite
is the 128x64 OLED type.  I like it because it has a very bright high-contrast display that
is easy to view from all angles and under a variety of power conditions.  This is in contrast
to some LCD screens that are difficult to read in bright light.
You can get this display on E-Bay (as of the end of 2018) or around $17.00

[Sample E-Bay OLED Screen](https://www.ebay.com/itm/2-42-inch-OLED-Display-SSD1309-128x64-SPI-IIC-Serial-Port-Blue-For-Arduino-KO/283274161519)

This version has a stanard SSD1309 chip that drives it and by default the display is configured to use 
the SPI interface.  There are a few different versions of the OLED displays,
but the ones that are the lowest cost provide for seven SPI connectors:

Serial Peripheral Interface Pins:
1.GND (Power Supply Ground)
2.VCC (Power Supply Positive)
3.SCL (Clock Line/SCK to pin 13 on the Nano)
4.SDA (Data Line/MOSI to pin 11 on the Nano)
5.RES (Reset Line)
6.DC (Data/Command)
7.CS (Chip Select)

To use the Hardware SPI on the Arduino Nano, we MUST connect the SCL to pin 13 and the SDA to pin 11.
See the [Documentation tab](https://store.arduino.cc/usa/arduino-nano) on the Arduino web site.
Note that since 11 is also a PWM pin we have to run the motors on pins 3, 5, 6 and 9.

This chip is supported by several Arduino libraries, which we will talk about next.

# The u8g2 Monochrome Graphics Library

When I first started using these OLED displays I started out using the Adafruit libraries.  I ran into a problem with
the library using most of my Arduino dynamic memory (about 70% of the 2K available in the Arduino Nano).  
However, I found another library, the u8g2 Monochrome Graphics Library, that only used about 1/3 of the memory.  
This library has a 
[Page Buffer Picture Loop](https://github.com/olikraus/u8g2/wiki/setup_tutorial#page-buffer-mode-picture-loop)
mode that only uses a small amount of RAM.

[U8g2 Github Site](https://github.com/olikraus/U8g2_Arduino)
[U8g2 Wiki](https://github.com/olikraus/u8g2/wiki/u8g2install)

# Configuring the Right Constructor

Getting the right setup for the U8g2 library took some time.  There are several setup options that will work.
The one I chose is the 4-wire hardware SPI.  Hardware interfaces are usually a little bit faster than the software
interfaces but they also reqired a few more connections.  Here are the options I selected:

1. SSD1306 (the name of the display driver)
2. 128x64 (the size of our display)
3. NONAME (no specific brand name)
4. 1 page (single 128 byte buffer)
5. 4 wire (as opposed to a 2 wire version)
6. Hardware (as opposed to software)
7. SPI (not the IIC interface)

```
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);
```

[Setup Constructor Reference](https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference)

# Selecting The Font
The U8g2 library comes with a large number of font to choose from ranging from 4 to 92 pixels high.  
I tried several sizes of fonts and I found the 8 pixel fonts to be large enough to read even from a
looking down at the floor from a standing position.  I also selected a variable with Helvetica font
that I felt was easy to read.
You can read more about the [font installation options here](https://github.com/olikraus/u8g2/wiki/fntlistall)

Here is the setup function that supports initialization of the display and the font selection:

```
void setup(void) {
  u8g2.begin();
  // Set font to Helvetica regular 8 pixel font
  // For other options see https://github.com/olikraus/u8g2/wiki/fntlistall#8-pixel-height
  u8g2.setFont(u8g2_font_helvR08_tf);
}
```

# Getting "Hello World" to Work
Once we have the right constructor and the font initialization setup we are ready to write our first test program.
The following test program just displays "CoderDojo Rocks" with a counter that increments so you can see
that the display is updating correctly for each loop.

Here is the full program:
```
#include <Arduino.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
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
```
Video of Display Test



