#define ir_sensor_pin A0

int sensor_value;
// pick typical mid sensor range values
int min_sensor_value = 400;
int max_sensor_value = 500;
int dist_scaled;
int dist_cm;
int readpin=A0;
void setup() {
    pinMode(ir_sensor_pin,INPUT);
    Serial.begin(9600);
}

void loop() {
    // sensor_value=analogRead(ir_sensor_pin);

    // get 10 readings and average them
    sensor_value=average_n_sensor_values(10);
    if (sensor_value < min_sensor_value) min_sensor_value = sensor_value;
    if (sensor_value > max_sensor_value) max_sensor_value = sensor_value;
   
    Serial.print(" ");
    Serial.print(sensor_value);
    Serial.print(" min=");
    Serial.print(min_sensor_value);
    Serial.print(" max=");
    Serial.print(max_sensor_value);
    dist_scaled = map(sensor_value, min_sensor_value, max_sensor_value, 100, 1);
    dist_cm=(6762/(sensor_value-9))-4;
    Serial.print(" dist_scaled=");
    Serial.print(dist_scaled);
    Serial.print(" dist_cm=");
    Serial.println(dist_cm);
}

int average_n_sensor_values(int n) {
int total=0;
  for (int i=0; i<n; i++) {
    total += analogRead(ir_sensor_pin);
    delay(10);
  }
  return (int) total / n;
}

