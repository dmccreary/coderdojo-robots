// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <Arduino.h>
#include <NewPing.h>
#include <U8g2lib.h> // note version 2 of the U8g library!
#include <SPI.h>

#define RIGHT_FORWARD_PIN 3
#define RIGHT_REVERSE_PIN 5
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 9

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define DATA_PIN 11 // SDA, MOSI
#define CLOCK_PIN 13 // SCL
#define CS_PIN A0 // chip select
#define DC_PIN A1 // Also known as address 0 or A0, not analog 0
#define RES_PIN A2 //  for SPI mode the RES pin becomes "Chip Select".
// We are using a 4-wire hardware SPI communications system.
// The Frame buffer option (1,2,F) should be 1 due limitations of memory.  1 uses under 32% of 2K RAM
// Data is on pin 11 and clock on 13
// U8G2_R0 is the rotation number
U8G2_SSD1309_128X64_NONAME2_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RES_PIN);

// put a pizzo speaker between this pin and GND
#define SPEAKER_PIN 2

#define FORWARD_POWER_LEVEL 150 // 150 to 255
#define TURN_POWER_LEVEL 180 // 150 to 255
#define TURN_DISTANCE 13 // distance threshold in cm
#define TURN_DELAY_TIME 400 // delay in msec - longer makes us turn more

// face parameters
#define EYE_DIAMETER 6

#define NOTE_C5  523
#define NOTE_C6  1047
#define NOTE_C7  2093
#define NOTE_C8  4186
#define NOTE_DURATION 500

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
char buf[20];
int counter = 0;
int half_display_width = 64;
int half_display_height = 32;

void setup() {
  pinMode(DC_PIN, OUTPUT);
  digitalWrite(DC_PIN, 0);  // default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0
  u8g2.begin();
  // load standard 20px high font
  u8g2.setFont(u8g2_font_6x12_tn);
  // dynamic update for portability to other screens
  half_display_width = u8g2.getDisplayWidth() / 2;
  half_display_height = u8g2.getDisplayHeight() / 2;
  // Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
int dist = sonar.ping_cm();
  u8g2.firstPage();
  
  

  if (dist < TURN_DISTANCE) {
      stop();
      tone(SPEAKER_PIN, NOTE_C5, NOTE_DURATION);
      delay(500);
      move_reverse();
      delay(500);
        if (random(1,3) > 2) {
          draw_face(7, dist);
          tone(SPEAKER_PIN, NOTE_C6, NOTE_DURATION);
          turn_right();
        }
          else {
            draw_face(-7, dist);
            tone(SPEAKER_PIN, NOTE_C7, NOTE_DURATION);
            turn_left();
          };
        
      
    } else {
      move_forward();
      draw_face(0, dist);
      // wait 35 ms between pings
      delay(25);
    }

  
}

void turn_right() {
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, TURN_POWER_LEVEL);
  analogWrite(LEFT_FORWARD_PIN, TURN_POWER_LEVEL);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(TURN_DELAY_TIME);
}

void turn_left() {
  analogWrite(RIGHT_FORWARD_PIN, TURN_POWER_LEVEL);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, TURN_POWER_LEVEL);
  delay(TURN_DELAY_TIME);
}

void move_forward() {
  analogWrite(RIGHT_FORWARD_PIN, FORWARD_POWER_LEVEL);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, FORWARD_POWER_LEVEL);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}

void move_reverse() {
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, FORWARD_POWER_LEVEL);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, FORWARD_POWER_LEVEL);
}

void stop() {
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}

void draw_face(int eye_offset, int dist) {
  do {
        u8g2.drawCircle(half_display_width, 32, 30, U8G2_DRAW_ALL);
        // eyes x, y, d, all
        u8g2.drawDisc(half_display_width - 15 + eye_offset, half_display_height - 5, EYE_DIAMETER, U8G2_DRAW_ALL);
        u8g2.drawDisc(half_display_width + 15 + eye_offset, half_display_height - 5, EYE_DIAMETER, U8G2_DRAW_ALL);
        // mouth x, y, length
        u8g2.drawHLine(half_display_width -10, half_display_height + 13, 20);
    
        // ping distance value
        sprintf(buf, "dist: %i", dist);
        u8g2.drawStr(0,64,buf);
        
      } while ( u8g2.nextPage() );
}

