/* calculate the time between changes in the LED sensor value */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int ledPin = 13;      // select the pin for the LED
int Motor_PWM_Pin = 3;      // select the pin for the LED
int Motor_Power_Level = 255;      // select the pin for the LED

int current_value = 0; // current value of sensor 1=HIGH or 0=LOW
int last_value = 0; // last value of sensor 1=HIGH or 0=LOW
int counter; // number of loops since change
unsigned long ms_at_last_change = 0; // number of MS at last change
unsigned long ms_since_change = 0;  // ms since last change

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(Motor_PWM_Pin, OUTPUT);
  analogWrite(Motor_PWM_Pin, Motor_Power_Level);
  Serial.begin(115200);
}

void loop() {
  unsigned long current_ms = millis();
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
  if (sensorValue > 512) {
    current_value = 1;
    digitalWrite(ledPin, HIGH);
  }
  else {
    current_value = 0;
    digitalWrite(ledPin, LOW);
  }
  
  // check to see if we have a new value
  if (current_value == last_value) {
    counter++;
  }
  else {
    Serial.print("Value changed counter=");
    Serial.print(counter);
    
    ms_since_change = current_ms - ms_at_last_change;
    ms_at_last_change = current_ms;
    
    Serial.print(" ms=");
    Serial.println(ms_since_change);
    counter = 0;
    last_value = current_value;
  }
}
