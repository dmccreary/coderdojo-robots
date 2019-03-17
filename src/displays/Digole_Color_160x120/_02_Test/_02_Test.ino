
#define Ver 33  //if firmware version is V2.9 and early, use welOld[] format, if V3.0~3.2 use welNew, if V3.3 and newer, use wel33
#define _Digole_Serial_UART_  //To tell compiler compile the special communication only, 

#include <DigoleSerial.h>

DigoleSerialDisp mydisp(&Serial, 9600); //UART:Arduino UNO: Pin 1(TX)on arduino to RX on module

int counter;

void setup() {
  mydisp.begin();
  mydisp.clearScreen();
  delay(10);
  mydisp.setColor(1); // white
  mydisp.setPrintPos(0, 0, _TEXT_);
  mydisp.println("CoderDojo Rocks!");
  mydisp.drawDisc(100,80,10);
  
  // RRRG GGBB
  mydisp.setColor(0x03); // blue
  mydisp.setPrintPos(0, 1, _TEXT_);
  mydisp.println("Digole Color $21");
  mydisp.drawDisc(100,100,10);
  
  // RRRG GGBB
  mydisp.setColor(0xE0); // Red
  mydisp.setPrintPos(0, 2, _TEXT_);
  mydisp.println("160x120");
  mydisp.drawDisc(120,80,10);

  // RRRG GGBB
  mydisp.setColor(0x1C); // Green
  mydisp.setPrintPos(0, 3, _TEXT_);
  mydisp.println("Serial Interface");
  mydisp.drawDisc(120,100,10);
  
  mydisp.drawHLine(0,118,158);
  
  
  mydisp.setFont(120); // a larger font
  mydisp.setColor(1);
}
void loop() {
  //mydisp.clearScreen();
 

  mydisp.setPrintPos(0, 2, _TEXT_);
  mydisp.println(counter);
  counter++;
  delay(100);
}


