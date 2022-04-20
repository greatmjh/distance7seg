#include <Arduino.h>
#include "constants.hpp"

void displayNumber();
void updateCurrentDisplay();
void displayDigit(unsigned int digit);

//Runtime globals
unsigned int currentlyDisplayingDigits[ARRAY_LENGTH(grounds)] = {6, 9};
unsigned int lastCurrentlyDisplayingDigits[ARRAY_LENGTH(grounds)] = {10, 10};
unsigned int currentlyDisplayingLED = 0;
unsigned int lastDisplayedDigit = 10;
unsigned long lastUpdate = 0;
const int updateInterval = 2;

void setup() {
	//Setup multiplexing grounds
	for (size_t i = 0; i < ARRAY_LENGTH(grounds); i++) {
		digitalWrite(grounds[i], HIGH);
		pinMode(grounds[i], OUTPUT);
	}

	digitalWrite(grounds[currentlyDisplayingLED], LOW);

	//Setup LED pins
	for (size_t i = 0; i < ARRAY_LENGTH(segments); i++) {
		pinMode(segments[i], OUTPUT);
	}

}

void loop() {
	// put your main code here, to run repeatedly:
	displayNumber();
	return;
}

void displayNumber() {
	
	//Firstly, check if we need to change which LED we're displaying on
	if (millis() - lastUpdate > updateInterval) {
		lastUpdate = millis();
		currentlyDisplayingLED++;
		if (currentlyDisplayingLED > ARRAY_LENGTH(grounds)) currentlyDisplayingLED = 0;
		updateCurrentDisplay();
	}

	//Redisplay only if the last number isn't what we're trying to display
	if (lastDisplayedDigit != currentlyDisplayingDigits[currentlyDisplayingLED]) {
		lastDisplayedDigit = currentlyDisplayingDigits[currentlyDisplayingLED];
		displayDigit(currentlyDisplayingDigits[currentlyDisplayingLED]);
	}

}

void updateCurrentDisplay() {
	for (size_t i = 0; i < ARRAY_LENGTH(grounds); i++) {
		if (i == currentlyDisplayingLED) {
			digitalWrite(grounds[i], LOW);
		} else {
			digitalWrite(grounds[i], HIGH);
		}
	}
}

void displayDigit(unsigned int digit) {
	if (digit > ARRAY_LENGTH(numbers)) return;
	for (size_t i = 0; i < ARRAY_LENGTH(segments); i++) {
		digitalWrite(segments[i], numbers[digit][i]);
	}
}

