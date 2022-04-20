#include <Arduino.h>
#include "constants.hpp"
#include "leddisplay.hpp"
#include "ultrasonic.hpp"

//Runtime globals
unsigned long lastUltrasonicUpdate = 0;
const int ultrasonicUpdateInterval = 100;
Ultrasonic* ultrasonic;
LEDdisplay* display;

void setup() {
	display = new LEDdisplay(2, PIN_7SEG_A, PIN_7SEG_B, PIN_7SEG_C, PIN_7SEG_D, PIN_7SEG_E, PIN_7SEG_F, PIN_7SEG_G);
	display->addModule(0, PIN_7SEG_G1);
	display->addModule(1, PIN_7SEG_G2);
	ultrasonic = new Ultrasonic(PIN_US_ECHO, PIN_US_TRIG);
}

void loop() {
	display->multiplex();
	
	//Read ultrasonic periodically
	if (millis() - lastUltrasonicUpdate > ultrasonicUpdateInterval) { //Check if the time has come to check
		lastUltrasonicUpdate = millis();
		display->setCurrentlyDisplayingNumber(ultrasonic->getDistance());
	}
	
}