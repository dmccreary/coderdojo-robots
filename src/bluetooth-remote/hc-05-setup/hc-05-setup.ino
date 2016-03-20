/* Simple Programming sketch for HC=05 Bluetooth Module
Module must be powered up in AT mode
Use command #1 to test for connection. If you get an OK, you have a valid connection
When using any of the set commands, it's the letter followed by what you want the setting to be.
After the SET commands are used you should see an OK. Use command #1 until you get OK response again
Set your monitor window to CR + NL
Written by Mel Patrick - Wabbit Wanch Design
*/
//
// D3   >>>  Rx
// D2   >>>  Tx

#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11); // RX, TX
byte btData;
byte crud;

String atQuestEnd="?\r\n";
String atSetEnd="\r\n";
String atStart="AT+";
String Version="VERSION";
String Address="ADDR";
String Name="NAME";
String Role="ROLE";
String UART="UART";
String State="STATE";
String Password="PSWD";
String Reset="ORGL";
//
String capture="";
boolean doCapture=false;
byte setCMD=0;
//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(38400);
  delay(2000);
  showMenu();
}

void loop() {
  if (Serial.available() > 0) {
    if (!doCapture) {
      crud=Serial.read();
    }
    else
    {
      char theVal=Serial.read();
      if (capture.length() == 0 && theVal == ',') {// skip the comma
        //Serial.println("got the comma");
      }
      else
      {
        capture.concat(theVal);
        if (theVal == '\n') {
          handleSetCMD(setCMD);// go do the function
        }
      }
    }
  }
  if (crud != 0) {
    switch (crud) {
    case 'm':
      showMenu();
      break;
    case '1':
      bt.write("AT\r\n");
      break;
    case '2':
      bt.print(atStart + Version + atQuestEnd);
      break;
    case '3':
      bt.print(atStart + Address + atQuestEnd);
      break;
    case '4':
      bt.print(atStart + Name + atQuestEnd);
      break;
    case '5':
      bt.print(atStart + Role + atQuestEnd);
      break;
    case '6':
      bt.print(atStart + UART + atQuestEnd);
      break;
    case '7':
      bt.print(atStart + State + atQuestEnd);
      break;
    case '8':
      bt.print(atStart + Password + atQuestEnd);
      break;
    case '9':
      bt.print(atStart + Reset + atSetEnd);
      break;
    case 'a':// set device name
      doCapture=true;
      crud=0;
      setCMD=1;
      break;
    case 'b':// set role
      doCapture=true;
      crud=0;
      setCMD=2;
      break;
    case 'c':// set password
      doCapture=true;
      crud=0;
      setCMD=3;
      break;
    case 'd':// set UART baudRate, Stop, Parity
      doCapture=true;
      crud=0;
      setCMD=4;
      break;
    }
  }
  if (bt.available()){
    btData=bt.read();
    Serial.write(btData);
  }
  delay(100);// prepare for next data ...
}
//
void handleSetCMD(byte whichCMD) {
  switch (whichCMD) {
  case 1:// set the device name
    bt.print(atStart + Name + "="+ capture + atSetEnd);
    break;
  case 2:// set the role
    bt.print(atStart + Role + "="+ capture + atSetEnd);// 0,1,2 (slave, master, slave loop)
    break;
  case 3:// set the password (four digits; most computers using 0000)
    bt.print(atStart + Password + "="+ capture + atSetEnd);
    break;
  case 4:// set the UART (baud, stop, parity)
    bt.print(atStart + UART + "="+ capture + atSetEnd);
    break;
  }
  capture="";
  doCapture=false;
  crud=0;
  setCMD=0;
}
//      bt.write("AT+NAME=Toothy_1\r\n");
//		bt.write("AT+ROLE=1\r\n");
//      bt.write("AT+PSWD=1234\r\n");
//      bt.write("AT+UART=9600,0,0\r\n");
//
void showMenu(){
  Serial.println(" ");
  Serial.println(F("HC-05 BlueTooth Programmer"));
  Serial.println(F("1. AT test           a. Set Device Name (a,name)"));
  Serial.println(F("2. Version           b. Set Role (b,0)"));
  Serial.println(F("3. Address           c. Set Password (c,1234)"));
  Serial.println(F("4. Name              d. Set UART (d,Baud,Stop,Parity)"));
  Serial.println(F("5. Role              m. Display this menu"));
  Serial.println(F("6. UART"));
  Serial.println(F("7. State"));
  Serial.println(F("8. Password"));
  Serial.println(F("9. Device Reset"));
  Serial.println(" ");
}
