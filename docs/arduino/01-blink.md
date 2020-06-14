Our first step is to verify that our PC or laptop can communicate with the Arduino.  To test this first startup the Arduino IDE.  You can download it from the internet.  Then go to the following menu:

**File** > **Examples** > **01.Basics** > **Blink**

The following program should be visible on your computer screen:

```C

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}```

Next, go to the **Tools** menu and make sure that you have selected the right Arduino processor, the right port and the right version of the bootloader.  Note that the Arduino Nano processors we use must be configured to use the old bootloader.

No click the right arrow **Upload** button above the **Blink** tab.  You should see the LEDs on the Arduino briefly blink.  After around five seconds you should see the LED on the Arduino flashing on and off every second.  You can now change the delay time from one second (1000 milliseconds) to 1/10th of a second (100 milliseconds). The loop function will now look like the following lines:

```C
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}```

Now press the **Upoad** button again.  The LED on the Arduino will now be flashing ten times as fast or 10 times per second.