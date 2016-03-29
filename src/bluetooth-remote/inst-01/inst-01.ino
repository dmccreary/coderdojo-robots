
#include <SoftwareSerial.h>
#define BIB 2
#define BIA 4
#define AIB 11
#define AIA 12
int enable = 9;
int enable2 = 10; //PWM CONTROL SPEED
int speed1 = 0; // PWM controll speed
 // for incoming serial data
SoftwareSerial bluetooth(0,1); // RX, TX
int BluetoothData;

void setup()
{
   bluetooth.begin(9600);
  pinMode(BIB,OUTPUT); // left motor B
  pinMode(BIA,OUTPUT); // left motor A
  pinMode(AIB,OUTPUT); // right motor B
  pinMode(AIA,OUTPUT); // right motor A
  pinMode(enable, OUTPUT);
  pinMode(enable2, OUTPUT);
 }

void loop()
{
  
    if (bluetooth.available()>0)
   {
     BluetoothData=bluetooth.read();
   }
 switch(BluetoothData)
  {
    case 'W':
     analogWrite(5,255);
     break;
     case 'w':
     analogWrite(5,0);
     break;
       case 'U':
     analogWrite(6,255);
     break;
       case 'u':
     analogWrite(6,0);
     break;
     case 'V':
     analogWrite(8,255);
     break;
     case 'v':
     analogWrite(8,0);
     break;
     case 'F':  // control to stop the robot
       forward();
       break;
    
     case 'R':  //control for right
     right();
       analogWrite(enable, speed1);
       analogWrite(enable2, speed1);
       break;
   
      case 'L':  //control for left
       left();
       analogWrite(enable, speed1);
       analogWrite(enable2, speed1);
       
     break;
    
     case 'S': //control for stop
      stop();
       analogWrite(enable, speed1);
       analogWrite(enable2, speed1);
      break;

    
       case 'B': //control for backward
       reverse();
        analogWrite(enable, speed1);
       analogWrite(enable2, speed1);
     break;
     
     
     
     
  case 'O':    // PWM speed values
    speed1 = 0 ;
    break;
    
    case '1':
    speed1 = 155;
    break;
   
     case '2':
    speed1 = 165;
    break;
    
      case '3':
   speed1 = 175;
    break;
   
     case '4':
    speed1 = 185;
    break;
   
     case '5':
    speed1 = 195;
    break;
    
    case '6':
    speed1 = 205;
    break;
    
    case '7':
    speed1 = 215;
    break;
    
    case '8':
    speed1 = 225;
    break;
    
    case '9':
   speed1 = 235;
    break;
    
    case 'q':
    speed1 = 255;
    break;
 }
} 
void forward()
{
  //LEFT WHEEL FORWARD
  digitalWrite(BIB,0);
  digitalWrite(BIA,1);
  //RIGHT WHEEL FORWARD
  digitalWrite(AIB,1);
  digitalWrite(AIA,0);
}

void stop()
{
  //LEFT WHEEL STOPPED
  digitalWrite(BIB,0);
  digitalWrite(BIA,0);
  //RIGHT WHEEL STOPPED
  digitalWrite(AIB,0);
  digitalWrite(AIA,0);
}
void reverse()
{
  //LEFT WHEEL REVERESE
  digitalWrite(BIB,1);
  digitalWrite(BIA,0);
  //RIGHT WHEEL REVERSE
  digitalWrite(AIB,0);
  digitalWrite(AIA,1);
}
void left()
{
  //LEFT WHEEL STOPPED
  digitalWrite(BIB,1);
  digitalWrite(BIA,1);
  //RIGHT WHEEL FORWARD
  digitalWrite(AIB,1);
  digitalWrite(AIA,0);
}
void right()
{
  //LEFT WHEEL FORWARD
  digitalWrite(BIB,0);
  digitalWrite(BIA,1);
  //RIGHT WHEEL STOPPED
  digitalWrite(AIB,1);
  digitalWrite(AIA,1);
}


