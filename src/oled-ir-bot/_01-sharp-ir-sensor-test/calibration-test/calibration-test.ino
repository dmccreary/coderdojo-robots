// used to calibrate the IR sensor
// press the mode button each 1cm and record the value
#define IR_SENSOR_PIN A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define MODE_BUTTON_PIN 2 // momentary push button tied to GNG (interrupt 0)


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 150;    // the debounce time; increase if the output flickers
int change_mode_flag = 0;
int sensor_value = 0;
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON_PIN), change_mode, FALLING);
}

void change_mode() {
 if ((millis() - lastDebounceTime) > debounceDelay) {
    change_mode_flag = 1;
    lastDebounceTime = millis(); // record when we got the interrupt for debouncing
 }
}

void loop() {
  
  if (change_mode_flag == 1) {
    sensor_value = average_sensor(10);
    Serial.print("cm=");
    Serial.print(counter);
    Serial.print(" pot=");
    Serial.println(sensor_value);
    change_mode_flag = 0;
    counter++;
  }
}

// take count readings 50 msec apart and average them
int average_sensor(int count) {
  int reading=0, sum = 0, average=0;
  //Serial.print("reading 10 values: ");
  for (int i=1; i<=count; i++) {
      reading = analogRead(IR_SENSOR_PIN);
      //Serial.print(reading);
      //Serial.print(" ");
      sum += reading;
      delay(50);  // Wait 50ms between measurements
   };
    //Serial.println("");
    //Serial.print("sum=");
    //Serial.println(sum);
    average =  round(sum / count) + 1;
    //Serial.print("average=");
    //Serial.println(average);
    return average;
}
