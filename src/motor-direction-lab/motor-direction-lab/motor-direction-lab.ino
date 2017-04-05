
int sensorPin = A0;
int forwardMotorPin = 5;
int reverseMotorPin = 6;
int sensorValue = 0; // input comes in from 0 to 1023
int forward_PWMValue = 0; // output must be converted to an integer from 0 to 255
int reverse_PWMValue = 0; // output must be converted to an integer from 0 to 255

void setup()
{
  pinMode(forwardMotorPin, OUTPUT);
  pinMode(reverseMotorPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value=");
  Serial.print(sensorValue);
  
  // convert the sensor Value to a PWM value
  if (sensorValue > 512) {
    // forward
    forward_PWMValue = map(sensorValue, 512, 1023, 0, 300);
    forward_PWMValue = constrain(forward_PWMValue, 0, 255);
    reverse_PWMValue = 0;
  } else {
    reverse_PWMValue = map(sensorValue, 0, 511, 300, 0);
    reverse_PWMValue = constrain(reverse_PWMValue, 0, 255);
    forward_PWMValue = 0;
  }
  Serial.print(" Forward value=");
  Serial.print(forward_PWMValue);
  Serial.print(" Reverse value=");
  Serial.println(reverse_PWMValue);

  analogWrite(forwardMotorPin, forward_PWMValue);
  analogWrite(reverseMotorPin, reverse_PWMValue);
  delay(200);
}
