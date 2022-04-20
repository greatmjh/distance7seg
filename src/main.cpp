#include <Arduino.h>
#include <math.h>
#include "constants.hpp"
#include "led.hpp"

//Runtime globals
unsigned long lastNumberUpdate = 0;
const int numberUpdateInterval = 250;

void setup() {
	setupLED();
}

void loop() {
	displayNumber(); // Display what we have

	//Number incrementing code
	if (millis() - lastNumberUpdate > numberUpdateInterval) { //Check if the time has come to increment
		lastNumberUpdate = millis();
		setCurrentlyDisplayingNumber(getCurrentlyDisplayingNumber() + 1);
		if (getCurrentlyDisplayingNumber() > pow(10, ARRAY_LENGTH(grounds)) - 1) setCurrentlyDisplayingNumber(0);
	}
}