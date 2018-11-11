
// test to see if the LED strip is working
// also make sure that the number of pixels is set correctly
#include <Adafruit_NeoPixel.h>
#define LEDPIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12
// the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int counter = 1;
int pattern_delay = 900; // 900 milliseconds
int loop_delay = 100; // 1/10 of a second

void setup()
{
  Serial.begin(9600); // Start serial for output debugging
  // flash the LED strip
  strip.begin();
  // test the LED strip
  flash_led_test();
  delay(pattern_delay*4);
  set_led_red();
  delay(pattern_delay);
  set_led_green();
  delay(pattern_delay);
  set_led_blue();
  delay(pattern_delay);
}

void loop()
{
  // show the counter moving up the LED strip
  show_counter(counter % NUMBER_PIXELS);
  Serial.print("Counter: ");
  Serial.println(counter);
  delay(loop_delay);
  counter++;
}

void show_counter(int counter) {
 for (int i=0; i < NUMBER_PIXELS; i++)
      strip.setPixelColor(i, 0, 0, 0);  
  strip.setPixelColor(counter, 50, 50, 50);
  strip.show();
}

void clear_strip() {
   for (int i=0; i < NUMBER_PIXELS; i++)
      strip.setPixelColor(i, 0, 0, 0);
   strip.show();
}

void set_led_red() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 25, 0, 0);
   strip.show();
}

void set_led_green() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 40, 0);
   strip.show();
}

void set_led_blue() {
    for (int i=0; i < NUMBER_PIXELS; i++)
        strip.setPixelColor(i, 0, 0, 50);
   strip.show();
}

void flash_led_test() {
  strip.setPixelColor(0, 50, 0, 0); // red
  strip.setPixelColor(1, 50, 25, 0); // orange
  strip.setPixelColor(2, 50, 50, 0); // yellow
  strip.setPixelColor(3, 0, 50, 0); // green
  strip.setPixelColor(4, 0, 0, 50); // blue
  strip.setPixelColor(5, 30, 0, 50); // indigo
  strip.setPixelColor(6, 10, 0, 5); // violet
  strip.setPixelColor(NUMBER_PIXELS - 1, 100, 100, 100); // set last pixel to white
  strip.show();
  
}

