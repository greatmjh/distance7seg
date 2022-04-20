#include <Arduino.h>
#include "constants.hpp"
#include "leddisplay.hpp"
#include "ultrasonic.hpp"

//For non-blocking pulling from the ultrasonic sensor
unsigned long lastUltrasonicUpdate = 0;
const int ultrasonicUpdateInterval = 100;

//Objects in use
Ultrasonic* ultrasonic;
LEDdisplay* display;

void setup() {
	//Initialise a display object that has the common pins and the number of displays
	display = new LEDdisplay(2, PIN_7SEG_A, PIN_7SEG_B, PIN_7SEG_C, PIN_7SEG_D, PIN_7SEG_E, PIN_7SEG_F, PIN_7SEG_G);
	//Add the display modules to the main object
	display->addModule(0, PIN_7SEG_G1);
	display->addModule(1, PIN_7SEG_G2);
	//Initialise an ultrasonic sensor with its relevant pins
	ultrasonic = new Ultrasonic(PIN_US_ECHO, PIN_US_TRIG);
}

void loop() {
	display->multiplex(); //Multiplex the display
	
	//Read ultrasonic periodically
	if (millis() - lastUltrasonicUpdate > ultrasonicUpdateInterval) { //Check if the time has come to check
		lastUltrasonicUpdate = millis();
		display->setCurrentlyDisplayingNumber(ultrasonic->getDistance());
	}
	
}