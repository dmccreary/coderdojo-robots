/*
left motor, right motor
m0,0 - stopped
m255,255 - forward
m-255,-255 - reverse
m0,-255 - right

m255,0 - right
m255,-255 - right
m-250,-255 - right spin

m0,255 - left
m-255,0 - left
m-255,255 - left spin
*/

// Bluetooth-robot v1
// Use Bluetooth HC-06 receive commands from another bluetooth device or terminal
// vi direction keys
// Uses keys "h" = left, "j" = reverse, "k" or "i" = forward, and "l" = right
// speed control is also implemented using "," = speed down, "." = speed up, and "/" = max speed.
#include <SoftwareSerial.h>
// L293D motor control pins
// we can only use pins 3, 5, 6, 9, 10, and 11 for PWM Pins
const int right_forward_pin = 3;
const int right_reverse_pin = 5;
const int left_forward_pin = 6;
const int left_reverse_pin = 9;
// leave 10 and 11 for Bluetooth serial communication
const int bluetooth_rdx_pin = 10;  // connect this pin to the transmit TDX of bluetooth
const int bluetooth_tdx_pin = 11;  // connect this pin to the receive RDX of bluetooth
SoftwareSerial bt(bluetooth_rdx_pin, bluetooth_tdx_pin); // RX, TX

// LED pin attached to Arduino D13 - it is on if we get a command
int LED = 13;

// variable to store serial data
int incomingByte = 0;
String incomingString;

// variable to store initial speed value
int speed_val = 100;
int increment_speed = 25; // how much to add or subtract from speed

//////////////////////////////


void setup(){
  pinMode(right_forward_pin, OUTPUT);
  pinMode(right_reverse_pin, OUTPUT);
  pinMode(left_forward_pin, OUTPUT);
  pinMode(left_reverse_pin, OUTPUT);
  pinMode(bluetooth_tdx_pin, OUTPUT);
  pinMode(bluetooth_rdx_pin, INPUT);
  Serial.begin(9600);
  // the HC-06 does default to 9,600.  Just pair and go!
  bt.begin(9600);
  // bt.println("listening for motor commands");
}

void loop() {

  // check for serial data
  if (bt.available() > 0) {
        // read the incoming byte:
        incomingByte = bt.read();
        // if available, blink LED and print serial data received.
        digitalWrite(LED, HIGH);
        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte);
        if (incomingByte == 109) {
          incomingString = bt.readString();
          Serial.print("String: ");
          Serial.println(incomingString);
        }
        // delay 10 milliseconds to allow serial update time
        delay(10);
  }

}


