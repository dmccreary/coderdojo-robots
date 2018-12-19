/*
 * Sketch uses 277,379 bytes (21%) of program storage space. Maximum is 1,310,720 bytes.
   Global variables use 26,728 bytes (9%) of dynamic memory, leaving 268,184 bytes for local variables. 
   Maximum is 294,912 bytes.
   esptool.py v2.1-beta1
   
    Connecting........_
    Chip is ESP32D0WDQ6 (revision 1)
    Uploading stub...
    Running stub...
    Stub running...
    Changing baud rate to 921600
    Changed.
    Configuring flash size...
    Auto-detected Flash size: 4MB
    Compressed 8192 bytes to 47...
 */
#define LED_1 2
#define LED_2 4

int delay_time = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
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

void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // calculate duty, 8191 from 2 ^ 13 - 1
  uint32_t duty = (8191 / valueMax) * min(value, valueMax);

  // write duty to LEDC
  ledcWrite(channel, duty);
}
