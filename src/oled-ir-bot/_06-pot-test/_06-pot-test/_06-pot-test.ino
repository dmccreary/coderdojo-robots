// program to test the ranges of the potentiometer
int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int max = 0;
int min = 1023;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);

  // get the min and max values to find the range of the pot
  if (sensorValue > max)
     max = sensorValue;

  if (sensorValue < min)
     min = sensorValue;

  Serial.print("min=");
  Serial.print(min);
  Serial.print(" max=");
  Serial.print(max);
  Serial.print(" value=");
  Serial.println(sensorValue);
  delay(300);
}
