We will be using the Arduino IDE to program our robot.  This system uses a variation of the C language and the Arduino library to make our motors move.

All Arduino programs have a main loop() function that will run continiously.  Most programs also have a setup() function that will run only once after the Arduino processor powers up or gets a reset event.

Here are some of the common Arduion functions we will use in our robot.

## Setup

pinMode\(pin, mode\) - used to setup a pin for input and to indicate if the internal pullup resistor is used.

## Motor Commands

analogWrite\(pin, power\) - used to set the speeds of the motor pins

delay\(msec\) - used to pause the Arduino for a msec milliseconds.  delay\(1000\) will pause for one second

## Serial Debugging

In addion to to these we will use a few functions for displaying numbers to the serial port for debugging.

Serial.begin\(9600\);

Serial.println\(\)

Serial.print\(\)

All of these commands are described on the Arduino web site: 



