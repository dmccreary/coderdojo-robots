
// IR distance sensor using Sharp GP2Y0A21YK0F Analog Distance Sensor
// The sensor is hooked to A0 and returns a votage reading inversely proportional to the distance to an object
// Note that readings under 10CM and over 70CM are mostly invalid
// https://www.ebay.com/itm/GP2Y0A21YK0F-Sharp-IR-Analog-Distance-Sensor-Distance-10-80CM-Free-Cable/202121681621?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define ir_sensor_pin A0

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

int sensor_value;
// pick typical mid sensor range values
int min_sensor_value = 400;
int max_sensor_value = 500;
int dist_scaled;
int dist_cm;
int readpin=A0;
void setup() {
  display.begin();
  display.clearDisplay();
  display.setContrast(45); // change from 40 to 60...
  display.setTextSize(1); // a resonable size for Nokia 5110 display
  display.setTextColor(BLACK);
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
    display_stats();
}

int average_n_sensor_values(int n) {
   int total=0;
   for (int i=0; i<n; i++) {
    total += analogRead(ir_sensor_pin);
    delay(10);
  }
  return (int) total / n;
}

void display_stats() {
  display.clearDisplay();
  display.println("A0: ");
  display.setCursor(20,0);
  display.println(sensor_value);
  display.print("min: ");
  display.println(min_sensor_value);
  display.print("max: ");
  display.println(max_sensor_value);
  display.print("percent: ");
  display.println(dist_scaled);
  display.display();
}


