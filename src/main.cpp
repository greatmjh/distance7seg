#include <Arduino.h>
#include "constants.hpp"

void displayNumber();
void updateCurrentDisplay();
void displayDigit(unsigned int digit);

//Runtime globals
unsigned int currentlyDisplayingNumber = 0;
unsigned int currentlyDisplayingLED = 0;
unsigned int lastDisplayedDigit = ARRAY_LENGTH(numbers);
unsigned long lastMultiplexUpdate = 0;
const int multiplexUpdateInterval = 2;

unsigned long lastNumberUpdate = 0;
const int numberUpdateInterval = 250;

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
	displayNumber(); // Display what we have

	//Number incrementing code
	if (millis() - lastNumberUpdate > numberUpdateInterval) { //Check if the time has come to increment
		lastNumberUpdate = millis();
		currentlyDisplayingNumber++;
		if (currentlyDisplayingNumber > 99) currentlyDisplayingNumber = 0;
	}
	return;
}

void displayNumber() {	
	//Split the currently displayed digit into an array
	unsigned int currentlyDisplayingDigits[ARRAY_LENGTH(grounds)]; 
	unsigned int place = 1;
	for (size_t i = ARRAY_LENGTH(currentlyDisplayingDigits); i > 0; i--) { //loop backwards from the 
		currentlyDisplayingDigits[i - 1] = (currentlyDisplayingNumber / place) % 10;
		place *= 10;
	}

	//Check if we need to change which LED we're displaying on
	if (millis() - lastMultiplexUpdate > multiplexUpdateInterval) {
		lastMultiplexUpdate = millis();
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

