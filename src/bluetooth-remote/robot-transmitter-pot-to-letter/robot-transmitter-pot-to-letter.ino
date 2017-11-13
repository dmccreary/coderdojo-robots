// Load into and Arduino hooked up to the HC-05 in Master Mode
// must be a master to a slave using the HC-06 receiver

#include <SoftwareSerial.h>

const int tranmit_to_bluetooth_pin=10; // connect to RDX on HC-05
const int receive_from_bluetooth_pin=11;  // connect to TDX on HC-05
const int fwd_rev_pot_pin = A0;
const int right_left_pot_pin = A1;

// setup a serial port for the Bluetooth
SoftwareSerial bt(receive_from_bluetooth_pin, tranmit_to_bluetooth_pin); 

int fwd_rev_val;
int right_left_val;

void setup() {
   connect();
   Serial.begin(9600);
   bt.begin(38400); // the default value for the HC-05
   Serial.print("Ready to Transmit Robot Commands");
}

void loop() {
   fwd_rev_val = analogRead(fwd_rev_pot_pin);
   right_left_val = analogRead(right_left_pot_pin);
   
   // forward
   if (fwd_rev_val > 525) {
     bt.print("k");
   }
   
   // back
   if (fwd_rev_val < 500) {
     bt.print("j");
   }
   
   // left
   if (right_left_val < 300) {
     bt.print("h");
   }
   
   // right
   if (right_left_val > 700) {
     bt.print("l");
   }
   
   // fast
   if (fwd_rev_val > 1000) {
     bt.print("/");
   }
   
   // stop
   if (fwd_rev_val > 500 && fwd_rev_val < 525) {
     bt.print(".");
   }     

delay(100);

}

void connect() {
  bt.print("k");
};
