# Changing Motor Direction

In this lab we use the same setup as the prior speed control lab.  We use a single potentiometer to control both the speed and direction of a single wheel.

This program will be slightly different in that we will send not just one but two PWM signals to our motor.  One will be the forward speed and one will be the reverse speed.

We will also add an if/then/else statement that will change what PWM signal is sent to the motor controller.  All inputs that are in the lower half of the potentiometer range will turn one direction, and the other half will turn the opposite direction.  By placing the pot in the middle the wheel will not rotate.

```C
int potPin = A0; // the pin for the potentiometer
int motorAForwardPin = 3;  // Pin to make the motor go forward
int motorABackwardPin = 5; // Pin to make the motor go backward
// one of the inputs on the Motor controller
int potValue = 128;  // variable to store the value coming from the sensor
int speedValue = 0; // variable to store the value going to the motor

void setup() {
   pinMode(potPin, INPUT);
   pinMode(motorAForwardPin, OUTPUT);
   pinMode(motorABackwardPin, OUTPUT);
   Serial.begin(9600);
}

void loop() {
   potValue = analogRead(potPin); // get the value from the Potentiometer from 0 to 1023
   Serial.print("pot=");
  Serial.print(potValue);
   if (potValue < 512) { // we will go backward if the value us under this
      speedValue = map(potValue, 0, 511, 255, 0);  // convert to the right range
      Serial.print(" speed backward=");
      Serial.println(speedValue);
      analogWrite(motorABackwardPin, speedValue); // go back this speed
      analogWrite(motorAForwardPin, 0);
 } else {
   speedValue = map(potValue, 512, 1023, 0, 255);  
   Serial.print(" speed forward=");
   Serial.println(speedValue);
   analogWrite(motorAForwardPin, speedValue);  // go forward this speed
   analogWrite(motorABackwardPin, 0);
 }
delay(100); // sample ever 1/10th of a second
}
```
Note that there are now two map statements.  One is for the postive direction and one is for the negative direction.
