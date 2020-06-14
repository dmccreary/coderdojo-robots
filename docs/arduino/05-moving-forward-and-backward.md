The next step is to make our robot move forward and then backward.
To move forward we will send a "move forward" signal to both the right and left motors.
We will then delay for two seconds.  After that we will stop for one second and
move backward for two seconds.  We can repeat this in our loop.

```C
int right_forward = 5;
int right_reverse = 3;
int left_forward = 6;
int left_reverse = 9;
int forward_time = 2000; // how long should we move forward?
int stop_time = 1000; // how long should we stop between directions?
int reverse_time = 2000; // how long should we go backward?
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
## Creating functions
We can also create a set of functions for each of our drive commands.  Functions
not only makes it easy to reuse code, but they also make our programs easier
for us to read.

Here are two C functions for going turning right and moving forward.  These
two functions are all we will need to create a simple collision avoidance robot.

```C
void turn_right() {
  Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, LOW);
  analogWrite(RIGHT_REVERSE_PIN, power_turn_level);
  analogWrite(left_forward, power_turn_level);
  analogWrite(left_reverse, LOW);
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, power_forward_right);
  analogWrite(RIGHT_REVERSE_PIN, LOW);
  analogWrite(left_forward, power_forward_left);
  analogWrite(left_reverse, LOW);
}
```

## Advanced Motion Functions
Here are four C functions for going forward, reverse and turning right and left.
Note that the turning functions (turn right and turn left) both have 
a function parameter.  This is the length of time that the robots
will be turning.  The longer the delay, the larger an angle the
robot will turn.

```C
// turn right for turn_delay_time ms
void turn_right(int turn_delay_time) {
  Serial.println("turning right");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, power_turn_level);
  analogWrite(LEFT_FORWARD_PIN, power_turn_level);
  analogWrite(LEFT_REVERSE_PIN, 0);
  delay(turn_delay_time);
}

void turn_left(int turn_delay_time) {
  Serial.println("turning left");
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(RIGHT_FORWARD_PIN, power_turn_level);
  analogWrite(LEFT_REVERSE_PIN, power_turn_level);
  analogWrite(LEFT_FORWARD_PIN, 0);
  delay(turn_delay_time);
}

void move_forward() {
  Serial.println("moving forward");
  analogWrite(RIGHT_FORWARD_PIN, power_forward_right);
  analogWrite(RIGHT_REVERSE_PIN, 0);
  analogWrite(LEFT_FORWARD_PIN, power_forward_left);
  analogWrite(LEFT_REVERSE_PIN, 0);
}

void move_reverse() {
  Serial.println("moving reverse");
  analogWrite(RIGHT_FORWARD_PIN, 0);
  analogWrite(RIGHT_REVERSE_PIN, power_forward_right);
  analogWrite(LEFT_FORWARD_PIN, 0);
  analogWrite(LEFT_REVERSE_PIN, power_forward_left);
}
```




