# Two Motors
In this lab we will be controlling two motors together to move our robot forward, backward and to turn our robot.

The following program has three sections.  The first defines the pin numbers and the delay time.  The second is the setup() function that sets the pins to be Outputs and then turns the motors off.  The last section is the loop() function that will repeat forever.

## Sample Robot Movement Test

```

int right_forward = 3;
int right_backward = 5;
int left_forward = 6;
int left_backward = 9;
int delay_time = 1000;  // 1 second

void setup() {
  pinMode(right_forward, OUTPUT);
  pinMode(right_backward, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_backward, OUTPUT);
  // turn all off
  digitalWrite(right_forward, LOW);
  digitalWrite(right_backward, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_backward, LOW);

}

// repeat this function
void loop() {
  // move forward
  digitalWrite(right_forward, HIGH);
  digitalWrite(left_forward, HIGH);
  delay(delay_time);
  
  // stop
  digitalWrite(right_forward, LOW);
  digitalWrite(left_forward, LOW);
  delay(delay_time);
  
  // reverse
  digitalWrite(right_backward, HIGH);
  digitalWrite(left_backward, HIGH);
  delay(delay_time);
  
  // stop
  digitalWrite(right_backward, LOW);
  digitalWrite(left_backward, LOW);
  delay(delay_time);
  
  // turn right
  digitalWrite(left_forward, HIGH);
  digitalWrite(right_backward, HIGH);
  delay(delay_time);

  // stop
  digitalWrite(left_forward, LOW);
  digitalWrite(right_backward, LOW);
  delay(delay_time);  // adjust this to change the angle
  
  // repeat (go to the top of the loop)
}
```
Note that this program does not use the AnalogWrite() functions that use PWM signals.  The motors are either completely  on or completely off.

Also note that the delay_time is 1000ms for each interval.  You can change the amount the robot rotates by changing the value of the time in the turn right block of code.  A shorter time will turn the robot a smaller angle.

## Limitations of our Robot
You can see that we don't have a fine amount of control our robot rotates.  We can only guess the amount the robot turns by setting the timer to different amounts.  As the batteries wear down, the amount that the robot turns per unit if time will also change.  We will learn more about how to fix this limitation in our advanced labs.