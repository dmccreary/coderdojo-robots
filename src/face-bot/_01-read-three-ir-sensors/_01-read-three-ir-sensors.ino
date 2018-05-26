/*
  This reads all three IR sensors and displays the values on the serial monitor.
  You can use it to make sure the three connections are all working and use it to calibrate
  the sensivity of each IR sensor using the potentiometer on each IR sensor.

  I purchased the IR sensors on e-bay in quantity 10 for $4.70.  So each sensor 47 cents.
  Fine 1/5/10X IR Infrared Obstacle Avoidance Sensor Module Smart Car for Arduino
  https://www.ebay.com/itm/Fine-1-5-10X-IR-Infrared-Obstacle-Avoidance-Sensor-Module-Smart-Car-for-Arduino/112611368493

  The default values are about 5cm -8cm which seems about right.
  When there are no objects in front of the sensors, the analog readings are around 1005 which is a digital HIGH
  When the IR sesnors are triggered, the values are usually around 58 - which is a digital 
  LOW.
  Note the LEDs on the sensors tell you if they are triggering.
  
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);

  Serial.print("Right: ");
  Serial.print(sensorValue0);
  Serial.print(" center:");
  Serial.print(sensorValue1);
  Serial.print(" left:");
  Serial.println(sensorValue2);
  delay(100);
}
