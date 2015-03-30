# About Our Robot
The CoderDojo robot is built around a set of low-cost components that are designed to be open and extensible.  Version 3 has the following components.

* 2 DC motors
* chasis
* Arduino compatable nano
* motor controller based on L293D
* 400 connection point solderless breadboard
* Ultrasonic distance sensor
* Addresible LED strip

Our design goals in this platform it to be a platform to teach the fundamental principals of robots and control systems.

This platform is designed to support the following learning labs.

* using the Arduio and the motor control to turn a motors on an off
* using Pulse Wave Modulation (PWM) to control motor speed
* changing motor direction
* controlling two motors
* reading data from a sensor and estimating object distance
* displaying information on an LED strip
* basic obstacle avoidance

We should note that we are using Arduino Nano that uses a CH340 serial driver.  This driver should be downloaded before you start up your Arduino software.

You can install the CH340 driver from this web site:

[http://www.wch.cn/downloads.php?name=pro&proid=5
](http://www.wch.cn/downloads.php?name=pro&proid=5)

(yes, the site is in Chinese but you can just and then look for the "English" words to download the Windows or mac driver)

## Note for Mac Users
Some of the latests versions of the Mac add a special security feature that only allows "signed" "kext" (kernel) drivers.  Our driver has not yet been signed.  If you have a recent Mac you may need to take the following additional steps

Open the Application/Utilities/Terminal application and enter the following text:
```
   sudo nvram boot-args="kext-dev-mode=1"
```

Next, reboot your Mac.

If the drivers are installed correctly you should see two addional items in your **Tools -> Serial Port** menu.  One will be for /dev/tty.SerialPort and the other for /dev/cu.SerialPort.  If you do not see these items your driver may not be installed correctly.

Note that this command disables the additional check for a signed driver.  If you are downloading any files from unknown sources you should re-enable these checks when you are done using the Arduino application and then reboot your system again.