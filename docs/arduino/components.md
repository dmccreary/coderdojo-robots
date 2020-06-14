# Components

We have designed this robot using common components that are low cost and easy to find on-line.  You can build your own robot by purchasing parts on sites like eBay or work with a pre-built robot in the CoderDojo sessions.

Here is a summary of the parts we use.

| Part Name | Approximate Cost | Sample Links |
| :--- | ---: | :--- |
| Arduino Nano | $2.70 | [e-bay](http://www.ebay.com/itm/Mini-USB-Nano-V3-0-5V-16M-ATmega328P-CH340G-Micro-controll-wbr-er-board-For-Arduino-/122278859631) [pick-click](https://picclick.com/?q=arduino+nano) |
| Robot Chassis with 4AA battery holder | $11 | [e-bay](http://www.ebay.com/itm/2WD-4WD-Robot-Smart-Car-Chassis-Kits-Speed-Encoder-65x26mm-Tire-for-Arduino-/172355012592?var=471179903104) [pick-click](https://picclick.com/?q=robot+chassis+kit+smart+car+2wd) |
| 1/2 Size 400 point Solderless Breadboard | $1.09 | [e-bay](http://www.ebay.com/itm/400-Points-Solderless-Breadboard-Prototyping-Board-Test-Board-400-Holes-83x55m-/162145177768) [pick-click](https://picclick.com/Business-Industrial/?q=solderless+breadboard+400+-transparent) |
| 170 tie point mini solderless breadboard | $1 | [e-bay](http://www.ebay.com/itm/Mini-Black-Solderless-Prototype-Breadboard-170-Tie-points-F-Arduino-NEW-C-/141977602033) |
| L293D Motor Controller | $1.54 | [e-bay](http://www.ebay.com/itm/Mini-Motor-Drive-Shield-Expansion-Board-L293D-Module-For-Arduino-UNO-MEGA2560-R3-/262136733314) [e-bay-qty-10](http://www.ebay.com/itm/112394765594) |
| Ultrasonic Ping Sensor HC-SR04 | $1 | [e-bay](http://www.ebay.com/itm/1pcs-Ultrasonic-Module-HC-SR04-Distance-Measuring-Transducer-Sensor-for-Arduino-/141975951132) |
| M-F Dupont Connectors \(need 6\) | $1 | [e-bay](http://www.ebay.com/itm/40-Pin-20cm-Dupont-Wire-Connector-Cable-2-54mm-Male-to-Female-1P-1P-For-Arduino-/391239934484?hash=item5b17b7a214:g:nVMAAOxyn~pRz4rQ) |
| Power Switch | $1 | e-bay |
| USB 2.0 Cable \(A Male to Mini\) 50cm | $1.70 | [e-bay](http://www.ebay.com/itm/Best-Black-USB-2-0-A-Male-to-Mini-5-Pin-B-Data-Charging-Cable-Cord-Adapter-DS-/261795259152) |
| 4 AA Batteries | $2.00 | [Costco](https://www.costco.com/Kirkland-Signature-AA-Alkaline-Batteries-Two-72-pack.product.100344142.html) |
| **Total** | **$24.32** |  |

There is also a sample collection of parts on e-bay [here](http://www.ebay.com/cln/mccr.da/coderdojo-robot-parts/387718727013).  Note that the links may point to items that are no longer for sale.  However you can find parts with similar descriptions and purchase these parts.  You can use our cost estimator Google Docs spreadsheet [here](https://docs.google.com/spreadsheets/d/1490iFuOG5PWHkeJBN2z3KLHy_9ROB9P-rnTeExFqWqo/edit?usp=sharing).

A blog post with sample parts is listed [here](http://datadictionary.blogspot.com/2015/01/30-coderdojo-robot-version-3.html).  Note that the links that this article provides might change, however you should be able to find similar parts using the keywords provided.

Now lets step through each of our individual components.

## Arduino compatible Nano

This low-cost microcontoller component is the "brains" of our robot.  Some of these can be ordered with a USB connector so we can connect them directly to our laptop or desktop computer.  We can purchase these for under $5.00.  The Nano has eight Analog inputs and 14 Digital input/output pins, six of them can be used to control motor speed with PWM signals. Note that ONLY pings 3, 5, 6, 9, 10, and 11 have PWM output.  We will be using Digital Output pins 3,5,6 and 9 in our book.

Make sure you read our Getting Started section to properly load the CH340 USB interface.

![Arduino compatible Nano](docs/img/nano.jpeg)

See [Arduino Nano Specication](http://arduino.cc/en/Main/arduinoBoardNano) for the full specification.

## 2 DC Motors and Wheels

We have decided to use simple Direct Current \(DC\) motors for our robots.  These motors are low cost and work under a variety of voltages from 6 to 12 volts.  They come included with our Robot Chassis.  
![DC Motor](docs/img/dc-motor.png)

## L293D Two Motor Controller

This part allows us to send signals to each motor to turn the wheels forward and backwards.  It has a set of screw terminals to connect the motors and power.  This board also has a voltage regulator that will convert voltages from 6 to 12 volts down to 5 volts for controlling our Arduino Nano.

![Motor Controler](docs/img/motor-controller.jpg)

This part allow us to drive two motors.

See the [Wikipedia page](http://en.wikipedia.org/wiki/H_bridge) for more on how the H-Bridge circuit works.

You can use the keywords "Mini Motor Drive Shield Expansion Board L293D Module For Arduino" to find your own parts. There are  many good on-line tutorials on how these parts work.  One example is [here](https://www.instructables.com/id/Control-your-motors-with-L293D-and-Arduino/).  These devices can be found for $1.54 \(including shipping\) when ordered on e-bay.

## Ultrasonic Distance Sensor

We will use low-cost HC-SR04 ultrasonic distance sensors for our robot.  They send out a set of ultrasonic pulse waves out of one speaker and listen for the pulse to return to a microphone.  The delay of the return signal corresponds to a distance of an object in front of the robot.  They can be purchased for around a dollar on e-bay.

![Ultrasonic Distance Sensore](docs/img/ultrasonic-distnace-sensor-HC-SR04.jpg)

We will also use a powerful library to convert the signals into distance measurements.  
[New Ping](https://code.google.com/p/arduino-new-ping/)

## Solderless Breadboards

The robot kit comes with two solderless breadboards,  One has 400 connection points and the other smaller board for the sensors has 170 connection points.

