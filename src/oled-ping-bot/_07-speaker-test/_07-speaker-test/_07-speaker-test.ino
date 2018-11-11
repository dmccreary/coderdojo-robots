int led = 13;
int peizoPin = 7;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(peizoPin, OUTPUT);
}

void loop() {
 digitalWrite(led, HIGH);
 // play a 1Khz tone for 100 msec
 tone(peizoPin, 1000, 100);
 delay(500);
 digitalWrite(led, LOW);
 delay(1000);
}
