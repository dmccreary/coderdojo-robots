/*
 * Use this test to verify that all the connections (except the moters) are working.
 * Verify that the OLED display is working
 * Verify Mode and Set buttons work (you can press them and see screen indicators change)
 * Verify Encoder (a screen values updates)
 * Verify Ping sensor (a screen values updates)
 * Verify Speaker (a tone plays if you are within a specific distance)
 */
#include <Arduino.h>
//// https://github.com/olikraus/u8g2/wiki
#include <U8g2lib.h>
#include <SPI.h>
#include <NewPing.h>
#include <Encoder.h>
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

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

// https://github.com/olikraus/u8g2/wiki/u8x8setupcpp#constructor-reference
// We are using the 128 byte 4 wire Hardware SPI (pin 11 and 13 impiled) with no screen rotation which only uses 27% of dynamic memory
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, CS_PIN, DC_PIN, RDS_PIN);

#define TRIGGER_PIN  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

//   Good Performance: only the first pin has interrupt capability
// we use just one interrupt pin for good performance
#define ENC_A_PIN 2 // an interrupt pin
#define ENC_B_PIN 4 // not an interrupt pin
Encoder myEnc(ENC_A_PIN, ENC_B_PIN);

long oldPosition  = -999;

/* this is the mode of the robot 
0 = running with faces
1 = set forward speed
2 = set turn distance
3 = set turn distance
4 = set turn speed
5 = debug mode
*/
byte mode = 0; // default mode on power up
byte mode_count = 6;

#define SET_PIN 12 // set the current encoder value to be the new variable
#define MODE_PIN A5 // change the programming mode - note that A6 and A7 don't have an INPUT_PULLUP
Bounce debouncer_set = Bounce();
Bounce debouncer_mode = Bounce();

// speaker or piezo speaker
#define SPEAKER_PIN A0

int dist_to_object; // distance in CM from the Ping sensor
int turning_flag;
int turn_threshold = 16; // distance that we turn
int forward_power_level = 180; // try a number from 100 to 255 for 4 AA batteries forard motors PWM on signal

int turn_delay = 500; // time to turn in milliseconds 
int turn_power_level = 200; // power while turning


// 0 means no, 1 means yes
unsigned char change_mode_flag = 0;
unsigned char change_set_flag = 0;
unsigned int know_value = 0;

// this is the mode of the robot 0 = running, 1,2,3 are set modes
int counter; // main loop counter
#define FACE_CENTER 90 // center of face in the horizontal (X) direction

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
  debouncer_mode.interval(10); // Use a debounce interval of 25 milliseconds
  randomSeed(analogRead(6)); // seed with staic on Analog 6
  Serial.begin(9600);      // open the serial port at 9600 bps
}

void loop () {

  // get a non-zero distance
  do {
    delay(33);
    dist_to_object = sonar.ping_cm();
  } while (dist_to_object == 0);
  
  if (dist_to_object < turn_threshold) turning_flag = 1; else turning_flag = 0;
  
  debouncer_set.update(); // Update the Bounce instance
  if (debouncer_set.fell()) {
     tone(SPEAKER_PIN, 2000, 200);
     change_set_flag = !change_set_flag;
  }   // Call code if button transitions from HIGH (default) to LOW

  debouncer_mode.update();
  if (debouncer_mode.fell()) {
    tone(SPEAKER_PIN, 3000, 200);
    change_mode_flag = !change_mode_flag;  // Call code if button transitions from HIGH to LOW
  }

  long newPosition = myEnc.read();
  newPosition = newPosition % 255;
  byte stop_value = newPosition/4;
  byte mode = stop_value % mode_count;
  byte random_number;

  // if (mode == 0)  then do this in final
    u8g2.firstPage();
    do {
        // Face
        // u8g2.drawFilledEllipse(63,31,20,28);
        u8g2.drawCircle(FACE_CENTER,31,30,U8G2_DRAW_ALL);
        // eyes
        u8g2.drawFilledEllipse(FACE_CENTER - 10,24,4,4);
        u8g2.drawFilledEllipse(FACE_CENTER + 10,24,4,4);
        // mouth
        if (turning_flag)
           u8g2.drawFilledEllipse(FACE_CENTER,44,8,6); // shock
           else u8g2.drawCircle(FACE_CENTER,40, 10, U8G2_DRAW_LOWER_LEFT|U8G2_DRAW_LOWER_RIGHT);  // lower have of circle for smile
           
        // rotery encoder 
        u8g2.drawStr(0,8,"Pos:");
        u8g2.setCursor(22,8);
        u8g2.print(newPosition);

        // set
        u8g2.drawStr(0,18,"SFlg:");
        u8g2.setCursor(28,18);
        u8g2.print(change_set_flag);

        // mode
        u8g2.drawStr(0,28,"MFlg:");
        u8g2.setCursor(28,28);
        u8g2.print(change_mode_flag);
        
        // ping sensor
        u8g2.drawStr(0,63,"Dist:");
        u8g2.setCursor(22,63);
        u8g2.print(dist_to_object);
    } while ( u8g2.nextPage() );
 

    if (turning_flag) {
      tone(SPEAKER_PIN, 1000, 200);
      move_reverse();
      delay(300);
      random_number = random(2);
      if ( random_number == 0) {
          tone(SPEAKER_PIN, 1300, 200);
          turn_right();
          }
        else {
          tone(SPEAKER_PIN, 700, 200);
          turn_left();
        }
      delay(300);
      move_forward();
    }
//    counter++;
}

void move_forward() {
  //Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, forward_power_level);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, forward_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
}

void move_reverse() {
  //Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, forward_power_level);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, forward_power_level);
}

void turn_right() {
  //Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, turn_power_level);
  analogWrite(LEFT_FORWARD_PIN, turn_power_level);
  analogWrite(LEFT_REVERSE_PIN, LOW);
  delay(turn_delay);
 all_motors_off();
}

void turn_left() {
  //Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, turn_power_level);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(LEFT_FORWARD_PIN, LOW);
  analogWrite(LEFT_REVERSE_PIN, turn_power_level);
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
