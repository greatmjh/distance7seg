# Distance7seg
Displays the distance recorded by a HC-SR04 ultrasonic sensor on 7 segment displays

## Circuit
The circuit that goes along with this program must have 1 or more (preferrably 2) 7 segment modules connected in a multiplex configuration where all the non-ground pins are joined together.
These non-ground pins should then be connected to the Arduino via a resistor (470 ohm recommended). Note that the letters mentioned in `constants.hpp` does not correspond physically to the pin layout of the modules, and you most refer to the datasheet of your modules to see where the pins connect.
The HC-SR04 sensor must connect to the Arduino in a way that corresponds to `constants.hpp`.

### Wiring with constants.hpp left as is
```
5V     --> HC-SR04 VCC
GND    --> HC-SR04 GND
Pin 2  --> Ground of left display
Pin 3  --> Ground of right display
Pin 4  --> 470R resistor --> Segment A
Pin 5  --> 470R resistor --> Segment B
Pin 6  --> 470R resistor --> Segment C
Pin 7  --> 470R resistor --> Segment D
Pin 8  --> 470R resistor --> Segment E
Pin 9  --> 470R resistor --> Segment F
Pin 10 --> 470R resistor --> Segment G
Pin 11 --> 470R resistor --> Decimal point (not currently used)
Pin 12 --> HC-SR04 ECHO
Pin 13 --> HC-SR04 TRIG
```

## Expansion
More modules can be easily added by adding them to the multiplex following these steps:
1. Connect the new module to the multiples.
2. Connect the ground of it to a free pin.
3. Assign the pin in `constants.hpp`.
4. Increment the first argument of `display = new LEDdisplay()` in `setup()` in `main.cpp`.
5. Add a `display->addModule()` line below the others with the pin as in `constants.hpp` and the next number.
