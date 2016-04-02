#include <SoftwareSerial.h>
// https://www.arduino.cc/en/Reference/SoftwareSerialConstructor
const byte rxPin = 10;// Recieve on 10, Transmit on 11
const byte txPin = 11;
SoftwareSerial bt(rxPin, txPin); 

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  delay(1000);
  Serial.println("Enter AT commands to send the HC-06");
  Serial.println("Set Serial montor to 9600 baud and No line ending");
  Serial.println("AT+VERSION");
  Serial.println("To set the name use AT+NAMENEW_NAME");
}

void loop()
{
if (bt.available())
  Serial.write(bt.read());

if (Serial.available())
  bt.write(Serial.read());
}
