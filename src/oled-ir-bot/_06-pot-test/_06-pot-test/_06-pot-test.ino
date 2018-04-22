// program to test the ranges of the potentiometer
// select the input pin for the potentiometer
#define POT_PIN  A1
int potValue = 0;  // variable to store the value coming from the sensor
int pot_max = 0;
int pot_min = 1023;

void setup() {
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  Serial.print("Reading potentiometer on pin:");
  Serial.print("POT_PIN");
}

void loop() {
  potValue = analogRead(POT_PIN);

  // get the min and max values to find the range of the pot
  if (potValue > pot_max)
     pot_max = potValue;

  if (potValue < pot_min)
     pot_min = potValue;

  Serial.print("min=");
  Serial.print(pot_min);
  Serial.print(" max=");
  Serial.print(pot_max);
  Serial.print(" value=");
  Serial.println(potValue);
  delay(300);
}
