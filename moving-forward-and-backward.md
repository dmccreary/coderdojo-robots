# Moving Forward and Backward

The next step is to make our robot move forward and then backward.
To move forward we will send a "move forward" signal to both the right and left motors.
We will then delay for two seconds.  After that we will stop for one second and
move backward for two seconds.  We can repeat this in our loop.

```
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;
int forward_time = 2000; // how long should we move forward?
int stop_time = 1000; // how long should we stop between directions?
int reverse_time = 2000; // how long should we go backward?
```

Here is our setup code:

```
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

```
void loop() {
  Serial.println("Moving Forward");
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_forward, HIGH);
  delay(delay_time_on);
  
  Serial.println("Stopping");  
  digitalWrite(right_forward, LOW);
  digitalWrite(left_forward, LOW);  
  delay(stop_time);

  Serial.println("Backing Up");
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_forward, HIGH);
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





