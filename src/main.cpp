#include <Arduino.h>
#include "constants.hpp"
#include "led.hpp"
#include "ultrasonic.hpp"

//Runtime globals
unsigned long lastUltrasonicUpdate = 0;
const int ultrasonicUpdateInterval = 100;
Ultrasonic* ultrasonic;

void setup() {
	setupLED();
	ultrasonic = new Ultrasonic(PIN_US_ECHO, PIN_US_TRIG);
	Serial.begin(9600);
}

void loop() {
	displayNumber(); // Display what we have
	//Read ultrasonic periodically
	
	if (millis() - lastUltrasonicUpdate > ultrasonicUpdateInterval) { //Check if the time has come to check
		lastUltrasonicUpdate = millis();
		setCurrentlyDisplayingNumber(ultrasonic->getDistance());
	}
	
	Serial.println(getCurrentlyDisplayingNumber());
}