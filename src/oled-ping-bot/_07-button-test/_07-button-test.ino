/*
 * Test that the select and program buttons are working using the Bounce2 library.  Either button will toggle the LED on 13
 */
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>

#define SET_PIN 12 // set the current encoder value to be the new variable
#define PROG_PIN A5 // change the programming mode
#define LED_PIN 13

Bounce debouncer_set = Bounce();
Bounce debouncer_prog = Bounce();
int ledState = LOW;

void setup() {

  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(PROG_PIN, INPUT_PULLUP);
  debouncer_set.attach(SET_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_set.interval(25); // Use a debounce interval of 25 milliseconds
  
  debouncer_prog.attach(PROG_PIN, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer_prog.interval(25); // Use a debounce interval of 25 milliseconds 
  
  pinMode(LED_PIN, OUTPUT); // Setup the LED
  digitalWrite(LED_PIN, ledState);
 
}

void loop() {

   debouncer_set.update(); // Update the Bounce instance
   if ( debouncer_set.fell() ) {  // Call code if button transitions from HIGH to LOW
     ledState = !ledState; // Toggle LED state
     digitalWrite(LED_PIN,ledState); // Apply new LED state
   }

   debouncer_prog.update();
   if ( debouncer_prog.fell() ) {  // Call code if button transitions from HIGH to LOW
     ledState = !ledState; // Toggle LED state
     digitalWrite(LED_PIN,ledState); // Apply new LED state
   }
}

