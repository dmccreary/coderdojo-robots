/* This tests a momentary push button where one end is wired to GND and the other to D2
 *  Note this is exacly the same as https://www.arduino.cc/en/Tutorial/Debounce
 * with the exception that we use declare instead of const 
 * and we use INPUT_PULLUP instead of INPUT for the pinMode in the setup
*/
#define BUTTON_PIN 2
#define INTERRUPT 0 // Pin 2 is always interrupt 0

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 150;    // the debounce time; increase if the output flickers

unsigned char change_mode_flag = 0;
unsigned char mode = 0;
unsigned char number_modes = 4;

void setup() {
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  // convert the PIN to interrupt (0)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), change_mode, FALLING);
  // set initial LED state
  digitalWrite(ledPin, ledState);
  Serial.begin(9600);
}

void loop() {

  if (change_mode_flag) {
    change_mode_flag = 0;
    // the new mode is to add one and modulo the number of modes
    mode = (mode + 1) % number_modes;

    // toggle the LED
    if (mode % 2 == 0)
       digitalWrite(ledPin, LOW);
    else digitalWrite(ledPin, HIGH);

    // play a 2K tone beep on pin 7 for 100 ms
    tone(7, 2000, 100);
  }

  

  // select the mode
  switch (mode) {
        case 0: avoid_obstacle();break; // run the main obstacle avoidance program
        case 1: change_forward_speed();break; // change the forward speed
        case 2: change_turn_distance();break; // change the turn distance
        case 3: change_turn_time();break; // change the turn time
     }

  Serial.println(mode);
}

// this is the interrupt service routine - don't put delay, tone or print here
// only change if we have not changed within the last debounceDelay time
void change_mode() {
 if ((millis() - lastDebounceTime) > debounceDelay) {
    change_mode_flag = 1;
    lastDebounceTime = millis(); // record when we got the interrupt for debouncing
 }
}

void avoid_obstacle() {
  Serial.println("avoiding obstacles");
}

void change_forward_speed() {
  Serial.println("changing forward speed");
}

void change_turn_distance() {
  Serial.println("changing turn distance");
}

void change_turn_time() {
  Serial.println("changing turn time");
}


