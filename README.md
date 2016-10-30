# Residuum

Residuum is a line following robot. It's a simple construction based on Arduino
board, array of eight reflectance sensors and two DC motors.

![Residuum Robot](/other/photos/photo_1.jpg?raw=true)

The main goal of this project was to take part in a robots contest as fast as
possible. Such attitude helped me to finish this project quite fast (~2 months),
but also resolved many of my doubts - whenever I had a few possible solutions,
I chose the easier one. Of course such approach has also drawbacks - Residuum
it's definitely not a speed daemon.

However, project is done and I learned a lot during this time. Robots contest
was also a very good lesson for such beginner like I am. I have many ideas
which I want to implement so stay tuned for the next version of Residuum.

Let's go briefly through all construction details.

## Electronics

Arduino Leonardo is a Residuum brain. I used this board because a years ago I
attended to soldering workshops and during this event we assembled Arduino
Leonardo. So it's not a original board, but my own production. It has ATmega32U4
microcontroller with 32kB flash memory, 2.5kB RAM, 1kB EEPROM, built in USB
2.0 controller and a few standard LEDs and buttons. Nothing fancy, but what was
more important in this project - Arduino is very easy to use.

![electronics](/other/photos/photo_electronics.jpg?raw=true)

Next body part - eyes. I used Pololu QTR-8RC with 8 reflectance sensors to
detect line in front of my construction. This module is specially designed for
line following robots. Moreover, supplier provides library for Arduino family
and all you have to do is call `readLine()` function - simple like that. Another
advantage of QTR-8RC is that it works with digital I/O pins, so limited number
of analog-to-digital converters it's not a problem (e.g. my Arduino has only 6
of them).

![sensors](/other/photos/photo_sensors.jpg?raw=true)

Ok, so we have brain and eyes - we can see the line and we can decide where to
go - now we have to move robot in given direction.

Residuum is using Pololu DRV8835 dual motor driver to control two DC motors.
This tiny H-bridge module allows you to drive pairs of motors with standard PWM
speed control and also separate your main circuit from motors voltage supply.

I used Dualsky Li-Pol 7.4V (220mAh 25C 2S) battery as a source of power for
Residuum. My main requirement choosing this part was weight. This battery is
only 16g and it can power my robot for a few minutes of driving. It's more then
enough in context of robots contest, where you can change your battery for a
fresh one even every single ride.

Voltage from Li-Pol is ideal for motors, but it's a little bit high for digital
part of Residuum. I have to use Pololu D24V10F3 step-down voltage regulator,
which reduces 7.4V to 3.3V.

Last but not least - LCD screen and a few tact switches. This is interface
between my and the robot. I'am using SparkFun Graphic LCD 84x48 (which is mostly
known as a screen from Nokia 5110) to display and control all robots settings
and functions.

![sensors](/other/photos/photo_board.jpg?raw=true)

All those parts was soldered in a shape of Arduino shield. I used 50 x 70 mm
PCB prototype matrix board.

## Mechanics

Finally something interesting - motors! Residuum uses two Pololu 30:1 micro
motors (Micro Metal Gearmotor MP 6V) to move forward and change direction. To be
honest I didn't spend much time to calculate is it the best choice in my case.
I've seen that many people are using those motors, so I ordered them too. Torque
is high enough to move my construction smoothly. I bought also two Pololu 60×8mm
wheels, Pololu motors brackets and Pololu ball caster (3/8" Plastic Ball) which
is placed in front of the Residuum. The same supplier means that everything fits
perfectly together.

![sensors](/other/photos/photo_mechanics.jpg?raw=true)

Of course all those elements have to be attached to some type of chassis. In
this case I used 3D print technology. Residuum was designed in *SketchUp* - very
simply and available also for free 3D modeling program. It took me only a few
hours to prepare a model from scratch and to find somebody on *3D Hubs* who will
print it. It's really amazing feeling when something from your screen transform
into physical object in a matter of hours.

![sensors](/other/photos/photo_chassis_3d.gif?raw=true)

Maybe Residuum chassis does not follow latest design fashions but it combines
with other parts perfectly.

## Software

TODO - C++, PlatformIO, PID and Menu

## Parts and costs

TODO - add intro about Arduino and other not listed parts (resistors, buttons)

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
* 3D print - 61,90 PLN

Sum: 491 PLN

## What's next

TODO - describe next version of Residuum
