#include "led.hpp"
#include "math.h"

//Constants for LED
const int grounds[2] = {2, 3};

const int segments[7] = {
	4, //A
	5, //B
	6, //C
	7, //D
	8, //E
	9, //F
	10,//G
};

const bool numbers[11][7] = {
	{true, true, true, true, true, true, false},
	{false, true, true, false, false, false, false},
	{true, true, false, true, true, false, true},
	{true, true, true, true, false, false, true},
	{false, true, true, false, false, true, true},
	{true, false, true, true, false, true, true},
	{true, false, true, true, true, true, true},
	{true, true, true, false, false, false, false},
	{true, true, true, true, true, true, true},
	{true, true, true, true, false, true, true},
	{false, false, false, true, true, true, false}
};

//Runtime globals
unsigned int currentlyDisplayingLED = 0;
unsigned int lastDisplayedDigit = ARRAY_LENGTH(numbers);
unsigned long lastMultiplexUpdate = 0;
const int multiplexUpdateInterval = 2;
unsigned int currentlyDisplayingNumber;

//Declarations
void displayDigit(unsigned int digit);
void updateCurrentDisplay();

void displayNumber() {	
	//Split the currently displayed digit into an array
	unsigned int currentlyDisplayingDigits[ARRAY_LENGTH(grounds)]; 
	if (currentlyDisplayingNumber <= pow(10, ARRAY_LENGTH(grounds)) - 1) {
		unsigned int place = 1;
		for (size_t i = ARRAY_LENGTH(currentlyDisplayingDigits); i > 0; i--) { //loop backwards from the 
			currentlyDisplayingDigits[i - 1] = (currentlyDisplayingNumber / place) % 10;
			place *= 10;
		}
	} else {
		currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 2] = 0;
		currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 1] = 10;
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

void setupLED() {
	currentlyDisplayingNumber = 0;
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

void setCurrentlyDisplayingNumber(unsigned int num) {
	currentlyDisplayingNumber = num;
}
unsigned int getCurrentlyDisplayingNumber() {
	return currentlyDisplayingNumber;
}

unsigned int getMaximumDisplayable() {
	return pow(10, ARRAY_LENGTH(grounds)) - 1;
}