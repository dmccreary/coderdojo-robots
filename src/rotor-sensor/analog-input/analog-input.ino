

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int Motor_PWM_Pin = 3;      // select the pin for the LED
int Motor_Power_Level = 255;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(Motor_PWM_Pin, OUTPUT);
  analogWrite(Motor_PWM_Pin, Motor_Power_Level);
  Serial.begin(115200);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  if (sensorValue > 512) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
  Serial.println(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
}
