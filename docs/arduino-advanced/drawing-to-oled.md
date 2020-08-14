# Drawing to OLED
There are two libraries for drawing to small monochrome OLED screens: the Adfruit libraries and the u8g2 libraries.
For our robots, which only have 2K or RAM, we will be using the u8g2 libraries because they use only about 1/3 of the RAM when used in the Page Buffer Picture Loop mode.
See [Page Buffer Picture Loop](https://github.com/olikraus/u8g2/wiki/setup_tutorial#page-buffer-mode-picture-loop)

## The u8g2 Monochrome Graphics Library



[U8g2 Github Site](https://github.com/olikraus/U8g2_Arduino)

[u8g2 Reference Libreary](https://github.com/olikraus/u8g2/wiki/u8g2reference)
[U8g2 Wiki](https://github.com/olikraus/u8g2/wiki/u8g2install)


## Adafruit
Adafruit_SSD1306, which handles the low-level communication with the hardware, and Adafruit_GFX, which builds atop this to add graphics functions like lines, circles and text.

We will not be using these libraries because they are too memory intensive.  They take over 70% of the available 2K RAM on the Arduino Nano.