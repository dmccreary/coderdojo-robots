/* Estimate the RPM - Revolutions Per Minute
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int ledPin = 13;      // select the pin for the LED
int Motor_PWM_Pin = 3;      // select the pin for the LED
int Motor_Power_Level = 255;      // select the pin for the LED
int breaks_in_wheel = 20; // the number of holes in the disk
int transitions_per_rev = breaks_in_wheel * 2;
unsigned long total_transitions = 0; // number of times we change


int current_value = 0; // current value of sensor 1=HIGH or 0=LOW
int last_value = 0; // last value of sensor 1=HIGH or 0=LOW
int counter; // number of loops since change
float rpm; // revolutions per minute
unsigned long ms_at_last_change = 0; // number of MS at last change
unsigned long ms_since_change = 0;  // ms since last change
unsigned long ms_at_last_rpm_calculation = 0; // number of MS at last change
unsigned long rotation_time; // time to make one full rotation

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
    // Serial.print("Value changed counter=");
    // Serial.print(counter);
    total_transitions++;
    ms_since_change = current_ms - ms_at_last_change;
    ms_at_last_change = current_ms;
    
    // Serial.print(" ms=");
    // Serial.println(ms_since_change);
    // every N*2 trasitions we can recalculate the RPM
    if (!(total_transitions % transitions_per_rev)) {
      rotation_time = current_ms - ms_at_last_rpm_calculation; // time since last rotation
      // RPM is the inverse of ms per change
      Serial.print("Rotation time=");
      Serial.print(rotation_time);
      // The RPM is over 60 seconds and x1000 to convert from ms to seconds
      rpm = 60000.0 / rotation_time;
      Serial.print("ms RPM=");
      Serial.println(rpm);
      ms_at_last_rpm_calculation = current_ms;
    }
    counter = 0;
    last_value = current_value;
  }
}
