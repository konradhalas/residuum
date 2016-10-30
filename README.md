# Residuum - line following robot

Residuum is a line following robot. It's a simple construction based on Arduino
board, array of eight reflectance sensors and two DC motors.

![Residuum Robot](/other/photos/photo_1.jpg?raw=true)

The main goal of this project was to take part in a robots contest as quick as
possible. Such attitude helped me to finish this construction in a short time
(~2 months), but also resolved many of my doubts - whenever I had a few possible
solutions, I chose the easier one. Of course such approach has also drawbacks -
Residuum it's definitely not a speed daemon.

However, project is done and I learned a lot during this time. Robots contest
was also a very good lesson for such beginner like I am. I have many ideas
which I want to implement so this is definitely not my last line follower.

Let's go briefly through all construction details.

## Electronics

*Arduino Leonardo* is a Residuum brain. I used this board because a years ago I
attended to soldering workshops and during this event we assembled Arduino
Leonardo. So it's not an original board, but my own production. It has
*ATmega32U4* microcontroller with 32kB flash memory, 2.5kB RAM, 1kB EEPROM, built
in USB 2.0 controller and a few standard LEDs and buttons. Nothing fancy, but
what was more important in this project - it's easy to use.

![electronics](/other/photos/photo_electronics.jpg?raw=true)

Next body part - eyes. I used *Pololu QTR-8RC* with 8 reflectance sensors to
detect line in front of my construction. This module is specially designed for
line following robots. Moreover, supplier provides library for Arduino family
and all you have to do is call `readLine()` function - simple like that. Another
advantage of QTR-8RC is that it works with digital I/O pins, so limited number
of analog-to-digital converters it's not a problem (e.g. my Arduino has only 6
of them).

![sensors](/other/photos/photo_sensors.jpg?raw=true)

Ok, so we have brain and eyes - we can see the line and we can decide where to
go - now we have to move robot in given direction.

Residuum is using *Pololu DRV8835 dual motor driver* to control two DC motors.
This tiny H-bridge module allows you to drive pair of motors with standard PWM
speed control and also it separates your main circuit from motors voltage
supply.

I used *Dualsky Li-Pol 7.4V (220mAh 25C 2S) battery* as a source of power for
Residuum. My main requirement choosing this part was weight. This battery is
only 16g and it can power my robot for a few minutes of driving. It's more then
enough in context of robots contest, where you can change your battery for a
fresh one even every single ride.

Voltage from two cells Li-Pol is ideal for motors, but it's a little bit too
high for a digital part of Residuum. I have to use *Pololu D24V10F3 step-down
voltage regulator*, which reduces 7.4V to 3.3V.

Last but not least - LCD screen and a few tact switches. This is interface
between my and the robot. I'm using *SparkFun Graphic LCD 84x48* (which is mostly
known as a screen from Nokia 5110) to display and control all robots settings
and functions.

![sensors](/other/photos/photo_board.jpg?raw=true)

All those parts were soldered on a single board in a shape of Arduino shield. I
used 50 x 70 mm PCB prototype matrix board.

## Mechanics

Finally something interesting - motors! Residuum uses two *Pololu 30:1 micro
motors* (Micro Metal Gearmotor MP 6V) to move forward and change direction. To be
honest I didn't spend much time to calculate is it the best choice in my case.
I've seen that many people are using those motors, so I ordered them too. Torque
is high enough to move my construction smoothly. I bought also two Pololu 60×8mm
wheels, Pololu motors brackets and Pololu ball caster (3/8" Plastic Ball) which
is placed in front of Residuum. The same supplier means that everything fits
perfectly together.

![sensors](/other/photos/photo_mechanics.jpg?raw=true)

Of course all those elements have to be attached to some type of chassis. In
this case I used 3D print technology. Residuum was designed in *SketchUp* - very
simply and available for free 3D modeling program. It took me only a few hours
to prepare a model from scratch and to find somebody on [3D Hubs](https://www.3dhubs.com/)
who will print it. It's really amazing feeling when something from your screen
transform into physical object in a matter of hours.

![sensors](/other/photos/photo_chassis_3d.gif?raw=true)

Maybe Residuum chassis does not follow latest design fashions but it combines
with other parts perfectly.

## Software

Residuum program is written in *C++*. I used [PlatformIO](http://platformio.org/)
environment to manage build process, requirements and tests. *PlatformIO*
toolset provides many useful features like CI integration and *Atom* editor
plugin. It really helps me a lot to find myself in a little bit old-school C++
world.

Main following algorithm is based on *PID controller*, more precisely it uses
only two members - P and D. I think that in this case short code example will be
more suitable than any description.

```cpp
void Follower::follow() {
  int error = this->lineDetector.detectLine();
  int speedDelta = this->kP * error + this->kD * (error - this->lastError);
  this->lastError = error;
  this->motorsDriver.setLeftMotorSpeed(this->motorsDriver.getBaseMotorSpeed() + speedDelta);
  this->motorsDriver.setRightMotorSpeed(this->motorsDriver.getBaseMotorSpeed() - speedDelta);
}
```

Those few lines are the most important part in Residuum code. Lets go quickly
through them. `detectLine()` function returns `0` if line is exactly under
middle sensor, `-X` if its under leftmost, and `+X` if its under rightmost. In
my case (8 sensors) `X` is equal 3500 (1000 per sensor), so `detectLine()`
returns values between `-3500` and `3500`. When we have "line error", we can
calculate delta which should be applied to our motors. I'm using here simple
version of PD controller, which calculates motors speed delta based on current
error and previous one. Finding proper value of each member gain (`kP` and `kD`)
is the most tricky part in such algorithm. When we have calculated speed delta,
we can change speed of each motor.

All settings like `kP` and `kD` values, base motors speed, and so one, are
available via menu system which I implemented specially for this project. All
menu items are rendered on LCD screen and user can move between them with tact
switches. My menu configuration looks like that:

```cpp
menu.addItem(new ActionMenuItem("FOLLOW", new FollowCommand(lineDetector, motorsDriver, EDIT_BUTTON_PIN)));
menu.addItem(new ActionMenuItem("CALIBRATE", new CalibrateCommand(qtr)));
menu.addItem(new IntegerValueMenuItem("BASE SPEED", settings.motorsBaseSpeed, new UpdateMotorsBaseSpeedCommand()));
menu.addItem(new FloatValueMenuItem("KP", settings.followerKp, FOLLOWER_KP_BASE, new UpdateFollowerKpCommand()));
menu.addItem(new FloatValueMenuItem("KD", settings.followerKd, FOLLOWER_KD_BASE, new UpdateFollowerKdCommand()));
```

During development I was trying to implement all parts os Residuum program
as a standard C++ libraries, without messing around with Arduino specific code.
This approach gives ma ability to test nearly my whole code very easily in my
local environment. Moreover, this code is now portable. Of course, it has to be
connection between my code and Arduino. This thin layer is realized
as an implementation of a few abstract base classes, which acts as interfaces in
my architecture.

## Parts and costs

Below you will find a list of all Residuum parts and other expenses. As I said,
I didn't buy my Arduino, but I think that it should be listed here, because it's
comparatively expensive part. On the other hand, I didn't put here some
common (and inexpensive) elements like resistors, wires, solder, etc.

* Pololu 30:1 Micro Metal Gearmotor MP 6V x 2 - 129,80 PLN
* Pololu Ball Caster with 3/8" Plastic Ball - 7,90 PLN
* Pololu QTR-8RC Reflectance Sensor Array - 39,90 PLN
* Pololu Wheel 60×8mm Pair Black - 29,90 PLN
* Pololu DRV8835 Dual Motor Driver Carrier - 17,90 PLN
* Pololu 3.3V, 1A Step-Down Voltage Regulator D24V10F3 - 30,90 PLN
* Pololu Micro Metal Gearmotor Bracket Pair Black - 18,50 PLN
* Dualsky Li-Pol 220mAh 25C 2S 7.4V - 22,90 PLN
* SparkFun Graphic LCD 84x48 - Nokia 5110 - 38,90 PLN
* PCB Prototype Matrix Board 50 x 70 mm  - 4,50 PLN
* Arduino Leonardo - 88,00 PLN
* 3D print via 3dhubs.com - 61,90 PLN

Sum: **491 PLN** (110 EUR / 125 USD)

## What's next

I achieved the main goal of this project - I took part in robots contest, but...
I placed almost last. Only two LEGO-based robots were slower then me. My best
time was `13.046` and fastest robot finished the same track in `6.683`. It
means that I can't upgrade Residuum, I have to build something from scratch, but
this time with other requirements. I will focus on robot weight and speed.

## Robocomp 2016

One of my fastest ride from *Robocomp 2016* in Kraków:

[![Residuum during Robocomp 2016](https://img.youtube.com/vi/713GhhHsxbs/0.jpg)](https://www.youtube.com/watch?v=713GhhHsxbs)
