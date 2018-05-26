/****************************************************************
 * THIS PROJECT BELONG TO ENSAR LEVENT.
 * YOU CAN GET OTHER PROJECTS FROM INSTRUCTABLES
 * https://www.instructables.com/member/ensarlevent/instructables/

IMPORTANT: The APDS-9960 can only accept 3.3V!

You must have Apds-9960 library;

 https://github.com/sparkfun/APDS-9960_RGB_and_Gesture_Sensor
 
 Arduino Pin  APDS-9960 Board  Function
 
 3.3V         VCC              Power
 GND          GND              Ground
 A4           SDA              I2C Data
 A5           SCL              I2C Clock
 2            INT              Interrupto Pro Mini 3.3V

Tests the gesture sensing abilities of the APDS-9960. Configures
APDS-9960 over I2C and waits for gesture events. Calculates the
direction of the swipe (up, down, left, right) and displays it
on a serial console. 

To perform a NEAR gesture, hold your hand
far above the sensor and move it close to the sensor (within 2
inches). Hold your hand there for at least 1 second and move it
away.

To perform a FAR gesture, hold your hand within 2 inches of the
sensor for at least 1 second and then move it above (out of
range) of the sensor.

Resources:
Include Wire.h and SparkFun_APDS-9960.h

Tested with SparkFun Arduin
****************************************************************/

#include <Wire.h>
#include <SparkFun_APDS9960.h>


// Pins
#define APDS9960_INT    2 // Needs to be an interrupt pin

// Constants

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void setup() {

  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
  
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

}

void loop() {
  if( isr_flag == 1 ) {
    detachInterrupt(0);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(0, interruptRoutine, FALLING);
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
         
         
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
         
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        
        break;
      case DIR_FAR:
        Serial.println("FAR");
       
        break;
      default:
        Serial.println("NONE");
        
    }
  }
}
