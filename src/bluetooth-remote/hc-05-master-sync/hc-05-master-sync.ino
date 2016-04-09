// load this into an Arduino connected to an HC-05
#include <SoftwareSerial.h>

const byte rxPin = 10;// Recieve on 10, Transmit on 11
const byte txPin = 11;
SoftwareSerial bt(rxPin, txPin);

void setup() {
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode  
  digitalWrite(9, HIGH);
  delay(100); // wait
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, HIGH);  // now power up the HC-05 in command mode!
  digitalWrite(6, HIGH);
 
  Serial.begin(9600);
  bt.begin(38400);

  Serial.println("Enter AT commands to send the HC-05");
  // Serial.println("AT+INQM=0,10,5");
  Serial.println("AT+INIT");
  Serial.println("AT+INQ");
  Serial.println("AT+PAIR=98D3,31,FC2D54,5");
  Serial.println("AT+BIND=98D3,31,FC2D54");
  Serial.println("AT+LINK=98D3,31,FC2D54");
  // get_devices();
}

void loop()
{
if (bt.available())
  Serial.write(bt.read());

if (Serial.available()) {
   if (Serial.peek() == '109') {// m
     get_devices();
  }
  bt.write(Serial.read());
}
}

void get_devices() {
   Serial.println("Resetting");
   bt.write("AT+RMAAD\r\n");   // Clear any existing paired devices
   bt.write("AT+ROLE=1\r\n");  // Set mode to Master
   bt.write("AT+RESET\r\n");    // After changing role, reset is required
   delay(500);
   // bt.print(AT+CMODE=1\r\n");  // talk to any type of device?  Not needed?
   bt.write("AT+INQM=0,5,5");    // Inquire mode - Standard, stop after 5 devices found or after 5 seconds
   bt.write("AT+INIT");    // Start Serial Port Profile (SPP) ( If Error(17) returned - ignore as profile already loaded)
   bt.write("AT+INQ");    // Start searching for devices
   Serial.println("Done");
};
