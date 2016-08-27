
/* YourDuino.com Example Software Sketch
 20 character 4 line I2C Display
 Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
 Connect Vcc and Ground, SDA to A4, SCL to A5 on Arduino
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

// must be a PWM pin, 3, 5, 6, 9, 10, and 11
const int forwardMotorPin = 5;
const int reverseMotorPin = 6;
int sensorPin = A0;
int sensorValue = 0; // input comes in from 0 to 1023
int forward_PWMValue = 0; // output must be converted to an integer from 0 to 255
int reverse_PWMValue = 0; // output must be converted to an integer from 0 to 255

void setup()
{
  pinMode(forwardMotorPin, OUTPUT);
  pinMode(reverseMotorPin, OUTPUT);
  lcd.begin(16,2); // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.backlight(); // turn the backlight on  
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Welcome to the");
  lcd.setCursor(0,1);
  lcd.print("Motor Direction");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("Lab             ");
  lcd.setCursor(0,1);
  lcd.print("Have Fun!       ");
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("Sensor=         ");
  lcd.setCursor(0,1);
  lcd.print("Fwd=     Rev=   ");
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value=");
  Serial.print(sensorValue);
  lcd.setCursor(8,0);
  print_right_aligned(sensorValue, 4);
  
  // convert the sensor Value to a PWM value
  if (sensorValue > 512) {
    // forward
    forward_PWMValue = map(sensorValue, 512, 1023, 0, 255);
    reverse_PWMValue = 0;
  } else {
    reverse_PWMValue = map(sensorValue, 0, 511, 255, 0);
    forward_PWMValue = 0;
  }
  
  lcd.setCursor(4,1);
  print_right_aligned(forward_PWMValue, 3);
  lcd.setCursor(12,1);
  print_right_aligned(reverse_PWMValue, 3);
  
  Serial.print(" forward PWM value=");
  Serial.print(forward_PWMValue);
  Serial.print(" reverse PWM value=");
  Serial.println(reverse_PWMValue);
  analogWrite(forwardMotorPin, forward_PWMValue);
  analogWrite(reverseMotorPin, reverse_PWMValue);
  delay(200);
}

// print right aligned into space
void print_right_aligned(int in, int spaces) {
    if ( (spaces == 4 && in > 999 )
          || (spaces == 3 && in > 99 )
        )
      {
        lcd.print(" ");
      }
    else if ( (spaces == 4 && in > 99 )
          || (spaces == 3 && in > 9 )
        )
        {
          lcd.print("  ");
        }
     else if ( spaces == 4 && in > 9 ) {
        lcd.print("   ");
     }
     lcd.print(in);
}
