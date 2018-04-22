#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define IR_SENSOR_PIN A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define POT_PIN  A1 // 50K pot on Analog pin 1 (not 0)

// the mode is running or programming one of the parameters
#define MODE_BUTTON_PIN 2 // momentary push button tied to GNG (interrupt 0)

// when the select button goes low the value of the POT is copied to the variable
#define SELECT_BUTTON_PIN 3 // momentary push button tied to GNG

// motor pins - they must be on the PWM pins 3,5,6,9
#define RIGHT_FORWARD_PIN 5
#define RIGHT_REVERSE_PIN 9
#define LEFT_FORWARD_PIN 6
#define LEFT_REVERSE_PIN 10

#define ARDUINO_LED_PIN 13

#define LED_STRIP_PIN 12 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 12
// the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

// The OLED is 128 wide and 64 high
// This is where we place numbers in the second column
#define OLED_COL_2 90
// not using the reset...
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// convert to CM
int turn_sensor_value = 400; //threshold for IR sensor 
int forward_power_level = 180; // try a number from 100 to 255 for 4 AA batteries forard motors PWM on signal

int turn_power_level = 200; // power while turning
int turn_delay = 700; // time to turn in milliseconds 

// global variables
int sensor_value = 0;
int pot_value = 0;
// the default min and max of the pot
int pot_max = 1000;
int pot_min = 20;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 2000;    // the debounce time; increase if the output flickers

// 0 means no, 1 means yes
unsigned char change_mode_flag = 0;
unsigned char select_pressed_flag = 0;

// this is the mode of the robot 0 = running, 1,2,3 are set modes
unsigned char mode = 0;
unsigned char number_modes = 4;

void setup() {
  // when we press this button we are going to change mode
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  // interrupt 0 on pin 2 when mode pressed
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON_PIN), change_mode, FALLING);
  // interrupt 1 on pin 3 when select is pressed
  attachInterrupt(digitalPinToInterrupt(SELECT_BUTTON_PIN), select_pressed, FALLING);
  // Turn these pins on for PWM OUTPUT
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_FORWARD_PIN, OUTPUT); 
  pinMode(LEFT_REVERSE_PIN, OUTPUT);


  // configure the button pin D2 for interrupt input
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP); // floats high, pull down to GND to change mode
  strip.begin();
  flash_led_test();
  delay(300);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  Serial.begin(9600);
}

// this is the interrupt service routine - don't put delay, tone or print here
// only change if we have not changed within the last debounceDelay time
// fired when the user wants to change a mode
void change_mode() {
 if ((millis() - lastDebounceTime) > debounceDelay) {
    change_mode_flag = 1;
    lastDebounceTime = millis(); // record when we got the interrupt for debouncing
 }
}

// fired when the user selects a value on the pot
void select_pressed() {
 if ((millis() - lastDebounceTime) > debounceDelay) {
    select_pressed_flag = 1;
    lastDebounceTime = millis(); // record when we got the interrupt for debouncing
 }
}

void loop () {

  if (change_mode_flag) {
    change_mode_flag = 0;
    // the new mode is to add one and modulo the number of modes
    mode = (mode + 1) % number_modes;

    // toggle the LED
    if (mode % 2 == 0)
       digitalWrite(ARDUINO_LED_PIN, LOW);
    else digitalWrite(ARDUINO_LED_PIN, HIGH);

    // play a 2K tone beep on pin 7 for 100 ms
    tone(8, 2000, 100);
  }
    
  // select the mode
  switch (mode) {
        case 0: avoid_obstacle();break; // run the main obstacle avoidance program
        case 1: change_forward_power();break; // change the forward speed
        case 2: change_turn_distance();break; // change the turn distance
        case 3: change_turn_time();break; // change the turn time
     }

  //Serial.print("mode=");
  //Serial.println(mode);
}

/*
// take the average of "count" valid values
int average_sensor(int count) {
  int sum_valid;
  int dist;
  int valid_readings = 0;
  int average_distance = 0;
  for (int i=1; i<=count; i++) {
       dist = distance_cm();
       if (dist != 0 && dist < 1000) {
          sum_valid += dist; // add this one in
          valid_readings++; // add total valid readings
//          Serial.print("valid distance=");
//          Serial.println(dist);
       }
       else {
          Serial.print("invalid distance=");
          Serial.println(dist); 
       };
       delay(50);  // Wait 50ms between measurements
    }
    average_distance =  round(sum_valid / valid_readings) + 1;
    Serial.print("average distance=");
    Serial.println(average_distance);
    return average_distance;
}


int distance_cm() {
  float volts = analogRead(IR_SENSOR_PIN)*0.0048828125;  // value from sensor * (5/1024)
  return 13*pow(volts, -1);
}
*/

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

void move_forward() {
  //Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, forward_power_level);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, forward_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}

void turn_right() {
  //Serial.println("turning right");
  set_led_red();
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
 all_motors_off();
}

void all_motors_off() {
  //Serial.println("All motors turning off");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, 0);
}

void avoid_obstacle() {
    //Serial.println("Avoiding obstacles...");
    display.setTextSize(1);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Avoiding obstacles...");

    sensor_value = analogRead(IR_SENSOR_PIN);
   // distance = distance_cm();
    display.setCursor(0, 10);
    display.print("IR sensor:");
    display.setCursor(OLED_COL_2 , 10);
    display.print(sensor_value);
    // 10 over (x) 20 down (y)

    display.setCursor(0, 20);
    display.print("Turn distance:");
    display.setCursor(OLED_COL_2, 20);
    display.print(turn_sensor_value);
    
    display.setCursor(0, 30);
    display.print("Forward power:");
    display.setCursor(OLED_COL_2, 30);
    display.print(forward_power_level);

    display.setCursor(0, 40);
    display.print("Turn time:");
    display.setCursor(OLED_COL_2, 40);
    display.print(turn_delay);
    display.display();
    
    if (sensor_value > turn_sensor_value) {
      set_led_red();
      turn_right();
    } else {
      set_led_green();
      move_forward();
    }
    
    delay(100);
}

// programming modes
void change_forward_power() {
 int potValue = 0;
 int new_forward_power;
    //Serial.println("Changing forward speed");
    all_motors_off();
    potValue = analogRead(POT_PIN);
    if (potValue > pot_max)
       pot_max = potValue;
  
    if (potValue < pot_min)
       pot_min = potValue;
    
    display.setTextSize(1);
    display.clearDisplay();
    // 10 over (x) 20 down (y)
    display.setCursor(1, 0);
    display.print("Set forward power");
    
    display.setCursor(0, 20);
    display.print("current value");
    display.setCursor(OLED_COL_2, 20);
    display.print(forward_power_level);

    // 100 is the minimum to move forward
    new_forward_power = map(potValue, pot_min, pot_max, 100, 255);
    display.setCursor(0, 30);
    display.print("new value");
    display.setCursor(OLED_COL_2, 30);
    display.print(new_forward_power);
    display.display();

    if (select_pressed_flag) {
//      Serial.print("Changing forward speed from:");
//      Serial.print(forward_power_level);
//      Serial.print(" to: ");
//      Serial.print(new_forward_power);
      forward_power_level = new_forward_power;
      // we are done so set the select flag back to 0
      select_pressed_flag = 0;
      // we could go to the next mode..but we assume one parameter is set at a time so now test it
      mode = 0;
    }
}

void change_turn_distance() {
int new_turn_distance;
    //Serial.print("Changing turn distance");
    all_motors_off();
    
    pot_value = analogRead(POT_PIN);
    if (pot_value > pot_max)
       pot_max = pot_value;
  
    if (pot_value < pot_min)
       pot_min = pot_value;
    
    display.setTextSize(1);
    display.clearDisplay();
    // 10 over (x) 20 down (y)
    display.setCursor(0, 0);
    display.print("Setting turn distance");
    //Serial.println(turn_sensor_value);

    display.setCursor(0, 20);
    display.print("current value:");
    display.setCursor(OLED_COL_2, 20);
    display.print(turn_sensor_value);

    new_turn_distance = map(pot_value, pot_min, pot_max, 700, 300);
    display.setCursor(0, 30);
    display.print("new value:");
    display.setCursor(OLED_COL_2, 30);
    display.print(new_turn_distance);

    display.display();
    
    if (select_pressed_flag) {
//      Serial.print("Changing turn distance from:");
//      Serial.print(turn_sensor_value);
//      Serial.print(" to: ");
//      Serial.print(new_turn_distance);
      turn_sensor_value = new_turn_distance;
      select_pressed_flag = 0;
      // we could go to the next mode..or the main menu
      mode = 0;
    }
}


// turn times are usually 200 to 1000 msec
void change_turn_time() {
int new_turn_time;
  //Serial.println("Changing turn time");
  all_motors_off();
  pot_value = analogRead(POT_PIN);  
  display.setTextSize(1);
  display.clearDisplay();
  // 10 over (x) 20 down (y)
  display.setCursor(0, 0);
  display.print("Changing turn time");
  display.setCursor(0, 20);
  display.print("Current value:");
  display.setCursor(OLED_COL_2, 20);
  display.print(turn_delay);

  // calculate the new turn time
  new_turn_time = map(pot_value, pot_min, pot_max, 200, 1200);
  display.setCursor(0, 30);
  display.print("New value:");
  display.setCursor(OLED_COL_2, 30);
  display.print(new_turn_time);  
  display.display();
  
  if (select_pressed_flag) {
    turn_delay = new_turn_time;
    select_pressed_flag = 0;
    // we could go to the next mode..or the main menu
    mode = 0;
  }
}

