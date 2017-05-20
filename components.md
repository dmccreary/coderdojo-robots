# Components

We have designed this robot using common components that are low cost and easy to find on-line.  You can build your own robot by purchasing parts on sites like eBay or work with a pre-built robot in the CoderDojo sessions.

Here is a summary of the parts we use.

| Part Name | Approximate Cost | Sample Link |
| :--- | ---: | :--- |
| Arduino Nano | $2.70 | [e-bay](http://www.ebay.com/itm/Mini-USB-Nano-V3-0-5V-16M-ATmega328P-CH340G-Micro-controll-wbr-er-board-For-Arduino-/122278859631) |
| Robot Chassis with 4AA battery holder | $11 | [e-bay](http://www.ebay.com/itm/2WD-4WD-Robot-Smart-Car-Chassis-Kits-Speed-Encoder-65x26mm-Tire-for-Arduino-/172355012592?var=471179903104) |
| 1/2 Size 400 point Solderless Breadboard | $1.09 | [e-bay](http://www.ebay.com/itm/400-Points-Solderless-Breadboard-Prototyping-Board-Test-Board-400-Holes-83x55m-/162145177768) |
| 170 tie point mini solderless breadboard | $1 | [e-bay](http://www.ebay.com/itm/Mini-Black-Solderless-Prototype-Breadboard-170-Tie-points-F-Arduino-NEW-C-/141977602033) |
| L293D Motor Controller | $1.54 | [e-bay](http://www.ebay.com/itm/Mini-Motor-Drive-Shield-Expansion-Board-L293D-Module-For-Arduino-UNO-MEGA2560-R3-/262136733314) |
| Ultrasonic Ping Sensor HC-SR04 | $1 | [e-bay](http://www.ebay.com/itm/1pcs-Ultrasonic-Module-HC-SR04-Distance-Measuring-Transducer-Sensor-for-Arduino-/141975951132) |
| M-F Dupont Connectors \(need 9\) | $1 | e-bay |
| Power Switch | $1 | e-bay |
| USB 2.0 Cable \(A Male to Mini\) 50cm | $1.70 | [e-bay](http://www.ebay.com/itm/Best-Black-USB-2-0-A-Male-to-Mini-5-Pin-B-Data-Charging-Cable-Cord-Adapter-DS-/261795259152) |
| 4 AA Batteries | $2.00 | [Costco](https://www.costco.com/Kirkland-Signature-AA-Alkaline-Batteries-Two-72-pack.product.100344142.html) |
| **Total** | **$24.32** |  |

There is also a sample collection of parts on e-bay [here](http://www.ebay.com/cln/mccr.da/coderdojo-robot-parts/387718727013).  Note that the links may point to items that are no longer for sale.  However you can find parts with similar descriptions and purchase these parts.

A blog post with sample parts is listed [here](http://datadictionary.blogspot.com/2015/01/30-coderdojo-robot-version-3.html).  Note that the links that this article provides might change, however you should be able to find similar parts using the keywords provided.

Now lets step through each of our individual components.

## Arduino compatible Nano

This low-cost microcontoller component is the "brains" of our robot.  The come with a USB connector so we can connect them directly to our laptop or desktop computer.  We can purchase these for under $5.00.  The Nano has eight Analog inputs and 14 Digital input/output pins, six of them can be used to control motor speed with PWM signals. Note that ONLY pings 3, 5, 6, 9, 10, and 11 have PWM output.  We will be using Digital Output pins 3,5,6 and 9 in our book.

Make sure you read our Getting Started section to properly load the CH340 USB interface.

![Arduino compatible Nano](docs/images/nano.jpeg)

See [Arduino Nano Specication](http://arduino.cc/en/Main/arduinoBoardNano) for the full specification.

## 2 DC Motors

We have decided to use simple Direct Current \(DC\) motors for our robots.  These motors are low cost and work under a variety of voltages from 6 to 12 volts.  
![DC Motor](docs/images/dc-motor.png)

## L293D Two Motor Controller

This part allows us to send signals to each motor to turn the wheels forward and backwards.

![Motor Controler](docs/images/motor-controller.jpg)

This part allow us to drive two motors.

See the [Wikipedia page](http://en.wikipedia.org/wiki/H_bridge) for more on how the H-Bridge circuit works.

You can use the keywords "Mini Motor Drive Shield Expansion Board L293D Module For Arduino" to find your own parts.

## Ultrasonic Distance Sensor

We will use low-cost HC-SR04 ultrasonic distance sensors for our robot.  They return a signal where the timing of the pulse corrisponds to a distance of and object in front of the robot.

![Ultrasonic Distance Sensore](docs/images/ultrasonic-distnace-sensor-HC-SR04.jpg)

We will also use a powerful library to convert the signals into distance measurements.  
[New Ping](https://code.google.com/p/arduino-new-ping/)

## Solderless Breadboards

The robot kit comes with two solderless breadboards,  One has 400 connection points and the other smaller board for the sensors has 170 connection points.

