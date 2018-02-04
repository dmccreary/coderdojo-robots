
/* CoderDojo IR Turn State changes
 *  In which we learn how to use state management to set the motor speeds
 *  
 */

#include "IRLremote.h"

// Choose a valid PinInterrupt or PinChangeInterrupt* pin of your Arduino board
#define pinIR 2

CNec IRLremote;

#define pinLed LED_BUILTIN
#define right_forward 3
#define right_reverse 5
#define left_forward 9
#define left_reverse 6

int right_forward_speed=0;
int right_reverse_speed=0;
int left_forward_speed=0;
int left_reverse_speed=0;

// each time we press the remote we change the state of the robot
// speed and turn state management
// the number of times the forward button has been pressed - negatve is backwards
int speed_state=0;
int turn_state=0;
int speed_increment=20;
int turn_increment=10;
void setup()
{
  pinMode(right_forward, OUTPUT);
  pinMode(right_reverse, OUTPUT); 
  pinMode(left_forward, OUTPUT); 
  pinMode(left_reverse, OUTPUT);
    // turn all the motors off
  digitalWrite(right_forward, LOW);
  digitalWrite(right_reverse, LOW);
  digitalWrite(left_forward, LOW);
  digitalWrite(left_reverse, LOW);
  // Start serial debug output
  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Startup"));

  // Set LED to output
  pinMode(pinLed, OUTPUT);

  // Start reading the remote. PinInterrupt or PinChangeInterrupt* will automatically be selected
  if (!IRLremote.begin(pinIR))
    Serial.println(F("You did not choose a valid pin."));
}

void loop()
{
  // Check if we are currently receiving data
  //if (!IRLremote.receiving()) {
    // Run code that disables interrupts, such as some led strips
  //}

  // Check if new IR protocol data is available from the remote control
  if (IRLremote.available())
  {
    // Light Led
    digitalWrite(pinLed, HIGH);

    // Get the new data from the remote
    auto data = IRLremote.read();
    switch (data.command) {
         case 0x0:
           // no-op framing commands from remote control
          break;
          
        case 0x11:
          Serial.print("CMD=forward");
          // increment the state variable for our current speed 
          speed_state++;
          // check the ranges of the state
          speed_state = constrain(speed_state, -10, 10);
          // add the speed increment but keep the speed between 0 and 255
          if (speed_state > 0) { // increment forward engines
             right_forward_speed = constrain(right_forward_speed + speed_increment, 0, 255);
             left_forward_speed = constrain(left_forward_speed + speed_increment, 0, 255);
             right_reverse_speed = 0;
             left_reverse_speed = 0;
          } else { // slow the reverse speed
             right_reverse_speed = constrain(right_reverse_speed - speed_increment, 0, 255);
             left_reverse_speed = constrain(left_reverse_speed - speed_increment, 0, 255);
             right_forward_speed = 0;
             left_forward_speed = 0;
          };
          print_state();
          update_motors();
          break;
        
        case 0x14:
          Serial.print("CMD=right  ");
          if (speed_state > 0) {
            right_forward_speed = constrain(right_forward_speed - turn_increment, 0, 255);
            left_forward_speed = constrain(left_forward_speed + turn_increment, 0, 255);
            right_reverse_speed = 0;
            left_reverse_speed = 0;
          } else {
             right_reverse_speed = constrain(right_reverse_speed + speed_increment, 0, 255);
             left_reverse_speed = constrain(left_reverse_speed - speed_increment, 0, 255);
             right_forward_speed = 0;
             left_forward_speed = 0;
          }
          print_state();
          update_motors();
          break;

        case 0x16:
          Serial.print("CMD=left   ");
          if (speed_state > 0) {
             right_forward_speed = constrain(right_forward_speed + turn_increment, 0, 255);
             left_forward_speed = constrain(left_forward_speed - turn_increment, 0, 255);
             right_reverse_speed = 0;
             left_reverse_speed = 0;
          }
          else {
             right_reverse_speed = constrain(right_reverse_speed - speed_increment, 0, 255);
             left_reverse_speed = constrain(left_reverse_speed + speed_increment, 0, 255);
             right_forward_speed = 0;
             left_forward_speed = 0;
          };
          print_state();
          update_motors();
          break;
          
        case 0x19:
           Serial.print("CMD=reverse");
           speed_state--;
           speed_state = constrain(speed_state, -10, 10);
           // keep the speed between 0 and 255
           if (speed_state > 0) {
              right_forward_speed = constrain(right_forward_speed - speed_increment, 0, 255);
              left_forward_speed = constrain(left_forward_speed - speed_increment, 0, 255);
              right_reverse_speed = 0;
              left_reverse_speed = 0;
           } else {
              right_reverse_speed = constrain(right_reverse_speed + speed_increment, 0, 255);
              left_reverse_speed = constrain(left_reverse_speed + speed_increment, 0, 255);
              right_forward_speed = 0;
              left_forward_speed = 0;
           };
           print_state();
           update_motors();
           break;
           
        case 0x15:
           // shut down all engines
           Serial.print("CMD=stop   ");
           speed_state = 0;
           turn_state = 0;
           right_forward_speed = 0;
           right_reverse_speed = 0;
           left_forward_speed = 0;
           left_reverse_speed = 0;
           update_motors();
           print_state();
           break;
           
        default:
          Serial.println("unknown command");
      }

    // Turn LED off after printing the data
    digitalWrite(pinLed, LOW);
    // Serial.print(data.command);
  }
}

// print the internal state to the serial port
void print_state() {
  Serial.print(" speed_state=");
  Serial.print(speed_state);
  Serial.print(" turn_state=");
  Serial.print(turn_state);
  Serial.print(" RF=");
  Serial.print(right_forward_speed);
  Serial.print(" RR=");
  Serial.print(right_reverse_speed);
  Serial.print(" LF=");
  Serial.print(left_forward_speed);
  Serial.print(" LR=");
  Serial.println(left_reverse_speed);
}

void update_motors() {
  analogWrite(right_forward, right_forward_speed);
  analogWrite(right_reverse, right_reverse_speed);
  analogWrite(left_forward,  left_forward_speed);
  analogWrite(left_reverse,  left_reverse_speed);
}

