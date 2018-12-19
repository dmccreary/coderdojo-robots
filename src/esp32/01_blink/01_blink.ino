
#define LED_1 2
#define LED_2 4

int delay_time = 50;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_1, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delay_time);                       // wait for a second
  digitalWrite(LED_1, LOW);    // turn the LED off by making the voltage LOW
  delay(delay_time); 
  digitalWrite(LED_2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(delay_time);                       // wait for a second
  digitalWrite(LED_2, LOW);    // turn the LED off by making the voltage LOW
  delay(delay_time);
}
