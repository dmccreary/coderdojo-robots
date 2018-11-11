
int SPEAKER_PIN = A0;
int LED_PIN = 13;

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
 digitalWrite(LED_PIN, HIGH);
 // play a 1Khz tone for 200 msec
 tone(SPEAKER_PIN, 200, 200);
 delay(500);
 tone(SPEAKER_PIN, 500, 200);
 delay(500);
 tone(SPEAKER_PIN, 1000, 200);
 delay(500);
 tone(SPEAKER_PIN, 2000, 200);
 delay(500);
 tone(SPEAKER_PIN, 3000, 200);
 delay(500);
 tone(SPEAKER_PIN, 4000, 200);
 delay(500);
 tone(SPEAKER_PIN, 5000, 200);
 digitalWrite(LED_PIN, LOW);
 delay(3000);
}
