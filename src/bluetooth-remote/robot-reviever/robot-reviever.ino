// Bluetooth-robot v1
// Use Bluetooth HC-06 receive commands from another bluetooth device or terminal
// vi direction keys
// Uses keys "h" = left, "j" = reverse, "k" = forward, and "l" = right
// speed control is also implemented using "," = speed down, "." = speed up, and "/" = max speed.
#include <SoftwareSerial.h>
// L293 motor control pins
// we can only use 3, 5, 6, 9, 10, and 11 for PWM Pins
const int right_forward_pin = 2;
const int right_reverse_pin = 5;
const int left_forward_pin = 6;
const int left_reverse_pin = 9;
// leave 10 and 11 for Bluetooth serial communication
const int bluetooth_rdx_pin = 10;  // transmit to RDX of bluetooth
const int bluetooth_tdx_pin = 11;  // revieve to TDX of bluetooth
SoftwareSerial bt(bluetooth_rdx_pin, bluetooth_tdx_pin); // RX, TX

// LED pin attached to Arduino D13
int LED = 13;

// variable to store serial data
int incomingByte = 0;

// variable to store speed value
int speed_val = 255;

//////////////////////////////


void setup(){
  pinMode(right_forward_pin, OUTPUT);
  pinMode(right_reverse_pin, OUTPUT);
  pinMode(left_forward_pin, OUTPUT);
  pinMode(left_reverse_pin, OUTPUT);
  pinMode(bluetooth_tdx_pin, OUTPUT);
  pinMode(bluetooth_rdx_pin, INPUT);
  Serial.begin(9600);
  Serial.println("Listening for hjkl,./ commands on the bluetooh serial ");
  // the HC-06 does default to 9,600.  Just pair and go!
  bt.begin(9600);
  bt.println("Listening for hjkl,./ commands on this port... ");
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
      // delay 10 milliseconds to allow serial update time
      delay(10);
      
      switch (incomingByte) {
        case 46:  // "," - raise speed
          speed_val = speed_val + 5;
          Serial.print("Faster speed=");
          Serial.println(speed_val);
          break;
        
        case 44:  // "." - lower speed
          speed_val = speed_val - 5;
          Serial.print("Slower speed=");
          Serial.println(speed_val);
          break;
       
       case 47:  // "/" - max speed
          speed_val = 255;
          Serial.println("Turbo max speed!");
          break;
        
        case 105:  // "j" or "i" forward
          forward(speed_val);
          Serial.println("forward");
          break;
        
        case 106:  // "j" or "i" forward
          forward(speed_val);
          Serial.println("forward");
          break;
          
        case 104:  // "h" left
          left(speed_val);
          Serial.println("left");
          break;       

        case 108:  // "l" right
          right(speed_val);
          Serial.println("right");
          break;       
        
        case 107:  // "k" reverse
          reverse(speed_val);
          Serial.println("reverse");
          break;
          
        default:
          Serial.print("Unknown command.  Stopping.");
          stop();
       }
  }
  else {
    stop();
    digitalWrite(LED, LOW);
  }
}


// robot movement

void forward(int speed) {
  analogWrite(right_forward_pin, speed);
  analogWrite(right_reverse_pin, 0);
  analogWrite(left_forward_pin, speed);
  analogWrite(left_reverse_pin, 0);
}

void reverse(int speed){
  analogWrite(right_forward_pin, 0);
  analogWrite(right_reverse_pin, speed);
  analogWrite(left_forward_pin, 0);
  analogWrite(left_reverse_pin, speed);
}

void right(int speed){
  analogWrite(right_forward_pin, 0);
  analogWrite(right_reverse_pin, speed);
  analogWrite(left_forward_pin, speed);
  analogWrite(left_reverse_pin, 0);
}

void left(int speed){
  analogWrite(right_forward_pin, speed);
  analogWrite(right_reverse_pin, 0);
  analogWrite(left_forward_pin, 0);
  analogWrite(left_reverse_pin, speed);
}

void stop(){
  analogWrite(right_forward_pin, 0);
  analogWrite(right_reverse_pin, 0);
  analogWrite(left_forward_pin, 0);
  analogWrite(left_reverse_pin, 0);
}
