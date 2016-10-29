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
was also a very good lesson for such a beginner like I am. I have many ideas
which I want to implement so stay tuned for the next version of Residuum.

## Electronics

Arduino Leonardo is a Residuum brain. I used this board because a years ago I
attended to soldering workshops and during this event we assembled Arduino
Leonardo. So it's not a original board, but my own production. It has ATmega32U4
microcontroller with 32kB flash memory, 2.5kB RAM, 1kB EEPROM, built in USB
2.0 controller and a few standard LEDs and buttons. Nothing fancy, but what was
more important in this project - very easy to use.

Next body part - eyes. I used Pololu QTR-8RC with 8 reflectance sensors to
detect line in front of my construction. This module is specially designed for
line following robots. Moreover, supplier provide library for Arduino family
and all you have to do is call `readLine()` function - simple like that. Another
advantage of QTR-8RC is that it works with digital I/O pins, so number of
analog-to-digital converters it's not a problem (e.g. my Arduino has only 6 of
them).

TODO -

## Mechanics

TODO - motors, wheels and chassis

## Algorithm

TODO - describe PID and Menu

## Parts and costs

TODO - add intro about Arduino and other not listed parts (resistors, buttons)

* Pololu 30:1 Micro Metal Gearmotor LP 6V x 2 - 129,80 PLN
* Pololu Ball Caster with 3/8" Plastic Ball - 7,90 PLN
* Pololu QTR-8RC Reflectance Sensor Array - 39,90 PLN
* Pololu Wheel 60×8mm Pair Black - 29,90 PLN
* Pololu DRV8835 Dual Motor Driver Carrier - 17,90 PLN
* Dualsky Li-Pol 220mAh 25C 2S 7.4V - 22,90 PLN
* Pololu 3.3V, 1A Step-Down Voltage Regulator D24V10F3 - 30,90 PLN
* SparkFun Graphic LCD 84x48 - Nokia 5110 - 38,90 PLN
* PCB Prototype Matrix Board 50 x 70 mm  - 4,50 PLN
* Pololu Micro Metal Gearmotor Bracket Pair Black - 18,50 PLN
* Arduino Leonardo - 88,00 PLN
* 3D print - 61,90 PLN

Sum: 491 PLN

## What's next

TODO - describe next version of Residuum
