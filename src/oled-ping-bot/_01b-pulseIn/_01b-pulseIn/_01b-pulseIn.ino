
#define TRIGGER_PIN  A3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A2  // Arduino pin tied to echo pin on the ultrasonic sensor.

void setup() {
   pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   Serial.begin(9600);
}

void loop() {
   unsigned long duration;
   int distance;

  digitalWrite(TRIGGER_PIN, HIGH);
  delay(1);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 5700);  // Timeout if distance > 100 cm

  distance = duration / 57;  // Divide by round-trip microseconds per cm to get cm

  if (distance >= 200 || distance <= 0) 
    Serial.println("Out of range");
  else 
  Serial.println(distance);
}
