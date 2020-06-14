# Testing Motor Connections

The following are the tree blocks of code we will use to test if we have our connections are correct.

The full test code is [here](https://raw.githubusercontent.com/dmccreary/coderdojo-robots/master/src/motor-connection-test/motor-connection-test.ino):

Keep changing the numbers in the first four lines around until you get the robot wheels to go in the following order:

1. Right forward
2. Right reverse
3. Left forward
4. Left reverse

```C
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;
int delay_time_on = 2000; // how long should each wheel turn?
int delay_time_off = 1000; // delay between tests
int delay_end_of_test= 3000; // delay between tests
```

Here is our setup code:

```C
void setup() {
  // Turn these pins on for PWM OUTPUT
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
  // turn all the motors off
  digitalWrite(right_forward, LOW);
  digitalWrite(right_reverse, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);
  // for debugging.  The output will appear on the serial monitor
  // To open the serial monitor, click the magnafing glass icon in the upper right corner
  Serial.begin(9600);      // open the serial port at 9600 bps
}
```

Here is the main loop:

```C
void loop() {
  Serial.println("Right Forward Test");
  digitalWrite(right_forward, HIGH);
  delay(delay_time_on);
  digitalWrite(right_forward, LOW);
  delay(delay_time_off);

  Serial.println("Right reverse test");
  digitalWrite(right_reverse, HIGH);
  delay(delay_time_on);
  digitalWrite(right_reverse, LOW);
  delay(delay_time_off);

  Serial.println("Left Forward Test");
  digitalWrite(left_forward, HIGH);
  delay(delay_time_on);
  digitalWrite(left_forward, LOW);
  delay(delay_time_off);

  Serial.println("Left Reverse Test");
  digitalWrite(left_reverse, HIGH);
  delay(delay_time_on);
  digitalWrite(left_reverse, LOW);

  delay(delay_end_of_test);
}
```



