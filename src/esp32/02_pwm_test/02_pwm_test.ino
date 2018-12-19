/*
https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogOut/LEDCSoftwareFade/LEDCSoftwareFade.ino#L30
 */
#define LED_1 2
#define LED_2 4

int delay_time = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}
// the loop function runs over and over again forever
void loop() {
  for (int i=0; i<256; i++) {
    ledcAnalogWrite(LED_1, i);
    delay(delay_time);
  }
  for (int i=256; i>=0; i--) {
    ledcAnalogWrite(LED_1, i);
    delay(delay_time);
  }
  for (int i=0; i<256; i++) {
    ledcAnalogWrite(LED_2, i);
    delay(delay_time);
  }
  for (int i=256; i>=0; i--) {
    ledcAnalogWrite(LED_2, i);
    delay(delay_time);
  }
}


