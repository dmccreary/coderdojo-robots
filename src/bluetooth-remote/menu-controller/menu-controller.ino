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

SoftwareSerial bt(10,11); // RX, TX
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
  // put the HC-06 into command mode, don't use 3,5,9 or 11.  Save them for PWM!
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(4, HIGH); // EN Pin
  digitalWrite(7, HIGH); // Both tied to VCC
  digitalWrite(8, HIGH); // Both tied to VCC
  
  Serial.begin(9600);
  bt.begin(38400);
  // bt.print("AT\r\n");
  // delay(2000);
  showMenu();
}

void reboot_HC_05_device() {
  digitalWrite(7, LOW); // Turn it off
  digitalWrite(8, LOW); // Both tied to VCC
  delay(2000);
  digitalWrite(7, HIGH); // Turn it back on
  digitalWrite(8, HIGH); // 
};

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
    case 'i':
      bt.print(atStart + "INQM=0,5,5" + atSetEnd);
      break;
    case 'j':
      bt.print(atStart + "INIT" + atSetEnd);
      break;
    case 'k':
      bt.print(atStart + "INQ" + atSetEnd);
      break;
    case 'l':
      bt.print(atStart + "PAIR=98D3,31,FC2D54,5" + atSetEnd);
      break;
    case 'n':
      bt.print(atStart + "BIND=98D3,31,FC2D54" + atSetEnd);
      break;
    case 'o':
      bt.print(atStart + "LINK=98D3,31,FC2D54" + atSetEnd);
      break;
    case 'x':
      bt.print(atStart + "DISC" + atSetEnd);
      break;
    case 'p':
      bt.print(atStart);
      bt.write("INQM=0,10,5");
      bt.print(atSetEnd);
      delay(100);
      bt.print(atStart);
      bt.write("INIT");
      bt.print(atStart);
      delay(100);
      bt.print(atStart);
      bt.write("INQ");
      bt.print(atStart);
      break;
    case 'q':
      bt.print(atStart);
      bt.write("INIT");
      bt.print(atSetEnd);
      delay(200);
      bt.print(atStart);
      bt.write("PAIR=98D3,31,FC2D54,5");
      bt.print(atSetEnd);
      // this takes a long time
      delay(10000);
      bt.print(atStart);
      bt.write("BIND=98D3,31,FC2D54");
      bt.print(atStart);
      delay(500);
      bt.print(atStart);
      bt.write("LINK=98D3,31,FC2D54");
      bt.print(atStart);
      delay(5000);
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

void showMenu(){
  Serial.println(" ");
  Serial.println(F("HC-05 BlueTooth Programmer"));
  Serial.println(F("1. AT test           a. Set Device Name (a,name)"));
  Serial.println(F("2. Version           b. Set Role (b,0)"));
  Serial.println(F("3. Address           c. Set Password (c,1234)"));
  Serial.println(F("4. Name              d. Set UART (d,Baud,Stop,Parity)"));
  Serial.println(F("5. Role              i. Init query parameters. INQM=0,5,5"));
  Serial.println(F("6. UART              j. Init library"));
  Serial.println(F("7. State             k. Probe for BT addresses"));
  Serial.println(F("8. Password          q. Bind to Robot 22."));
  Serial.println(F("9. Device Reset      x. Disconnect from Robot 22"));
  Serial.println(F("i=query INQM=0,5,5, j=init lib INIT, k=get addrs INQ"));
  Serial.println(F("l=PAIR ,n=BIND, o=LINK"));
}
