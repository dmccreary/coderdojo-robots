
#include "IRLremote.h"

// Choose a valid PinInterrupt or PinChangeInterrupt* pin of your Arduino board
#define pinIR 2

CNec IRLremote;

#define pinLed LED_BUILTIN
#define right_forward 3
#define right_reverse 5
#define left_forward 9
#define left_reverse 6

int forward_speed=200;
int reverse_speed=200;
int turn_speed=200;
int turn_time=200; // turn for these ms
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

  // Check if new IR protocol data is available
  if (IRLremote.available())
  {
    // Light Led
    digitalWrite(pinLed, HIGH);

    // Get the new data from the remote
    auto data = IRLremote.read();
    switch (data.command) {
         case 0x0:
           // no-op
          break;
        case 0x11:
          Serial.println("forward");
          analogWrite(right_forward, forward_speed);
          analogWrite(right_reverse, 0);
          analogWrite(left_forward, forward_speed);
          analogWrite(left_reverse, 0);
          break;
        case 0x16:
          Serial.println("left");
          analogWrite(right_forward, turn_speed);
          analogWrite(left_reverse, turn_speed);
          analogWrite(right_reverse, 0);
          analogWrite(left_forward, 0);
          delay(turn_time);
          analogWrite(right_forward, 0);
          analogWrite(left_reverse, 0);
          break;
        case 0x14:
          Serial.println("right");
          analogWrite(right_reverse, turn_speed);
          analogWrite(left_forward, turn_speed);
          analogWrite(right_forward, 0);
          analogWrite(left_reverse, 0);
          delay(turn_time);
          analogWrite(right_reverse, 0);
          analogWrite(left_forward, 0);
          break;
        case 0x19:
           Serial.println("reverse");
           analogWrite(right_reverse, turn_speed);
           analogWrite(left_reverse, turn_speed);
           analogWrite(right_forward, 0);
           analogWrite(left_forward, 0);
           break;
        case 0x15:
           Serial.println("stop");
           analogWrite(right_reverse, 0);
           analogWrite(left_reverse, 0);
           analogWrite(right_forward, 0);
           analogWrite(left_forward, 0);
           break;
        default:
          Serial.println("unknown command");
      }

    // Turn Led off after printing the data
    delay(100);
    digitalWrite(pinLed, LOW);
    Serial.print(data.command);
  }
  
}
