
// must be a PWM pin, 3, 5, 6, 9, 10, and 11
const int motorPin = 5;
int sensorPin = A0;
int sensorValue = 0; // input comes in from 0 to 1023
int PWMValue = 0; // output must be converted to an integer from 0 to 255

void setup()
{
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value=");
  Serial.print(sensorValue);
  // convert the sensor Value to a PWM value
  PWMValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.print(" PWM value=");
  Serial.println(PWMValue);
  analogWrite(motorPin, PWMValue);
  delay(200);
}



