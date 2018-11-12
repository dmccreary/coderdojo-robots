#include <Arduino.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>
#include <NewPing.h>
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.

// the mode is running or programming one of the parameters
#define MODE_BUTTON_PIN 2 // momentary push button tied to GNG (interrupt 0)

// when the select button goes low the value of the POT is copied to the variable
#define SELECT_BUTTON_PIN 3 // momentary push button tied to GNG

// motor pins - they must be on the PWM pins 3,5,6,9
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


// The OLED is 128 wide and 64 high
// This is where we place numbers in the second column
#define OLED_COL_2 90
// not using the reset...
#define OLED_RESET 4

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4W Hardware SPI with no rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

#define TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define SET_PIN 12 // set the current encoder value to be the new variable
#define MODE_PIN A5 // change the programming mode - note that A6 and A7 don't have an INPUT_PULLUP
Bounce debouncer_set = Bounce();
Bounce debouncer_mode = Bounce();

// convert to CM
int turn_sensor_value = 400; //threshold for IR sensor - a non-linear function - above this it is not reliable
int forward_power_level = 180; // try a number from 100 to 255 for 4 AA batteries forard motors PWM on signal

int turn_power_level = 200; // power while turning
int turn_delay = 700; // time to turn in milliseconds 

// 0 means no, 1 means yes
unsigned char change_mode_flag = 0;
unsigned char change_set_flag = 0;

// this is the mode of the robot 0 = running, 1,2,3 are set modes
unsigned char mode = 0;
unsigned char number_modes = 4;
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

  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(MODE_PIN, INPUT_PULLUP);
  debouncer_set.attach(SET_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_set.interval(25); // Use a debounce interval of 25 milliseconds
  
  debouncer_mode.attach(MODE_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_mode.interval(25); // Use a debounce interval of 25 milliseconds 
  
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop () {
  int dist_to_object = sonar.ping_cm();
  
  debouncer_set.update(); // Update the Bounce instance
  if ( debouncer_set.fell() ) change_set_flag = 1;  // Call code if button transitions from HIGH (default) to LOW

   debouncer_mode.update();
   if ( debouncer_mode.fell() ) change_mode_flag = 1;  // Call code if button transitions from HIGH to LOW

  u8g2.firstPage();
    do {    
      u8g2.drawStr(0,8,"Integration Test");
      u8g2.drawStr(0,18,"Mode:");
      u8g2.setCursor(40,18);
      u8g2.print(change_mode_flag);

      u8g2.drawStr(0,28,"Set:");
      u8g2.setCursor(40,28);
      u8g2.print(change_set_flag);
      
      u8g2.drawStr(0,38,"Dist:");
      u8g2.setCursor(40,38);
      u8g2.print(dist_to_object);
      
      u8g2.setCursor(0,63);
      u8g2.print(counter);
    } while ( u8g2.nextPage() );

    counter++;
}
