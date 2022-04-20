#include "leddisplay.hpp"

void LEDdisplay::displayDigit(unsigned int digit) {
	if (digit > ARRAY_LENGTH(numbers)) return;
	for (size_t i = 0; i < ARRAY_LENGTH(segmentPins); i++) {
		digitalWrite(segmentPins[i], numbers[digit][i]);
	}
}

void LEDdisplay::updateCurrentDisplay() {
	for (size_t i = 0; i < moduleCount; i++) {
		if (i == currentlyDisplayingModule) {
			digitalWrite(moduleGrounds[i], LOW);
		} else {
			digitalWrite(moduleGrounds[i], HIGH);
		}
	}
}

LEDdisplay::LEDdisplay(unsigned int _moduleCount, unsigned int segmentA, unsigned int segmentB, unsigned int segmentC, unsigned int segmentD, unsigned int segmentE, unsigned int segmentF, unsigned int segmentG) : 
moduleCount(_moduleCount), segmentPins{segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG} {
	moduleGrounds = new unsigned int[moduleCount];
	currentlyDisplayingNumber = 0;

	digitalWrite(moduleGrounds[currentlyDisplayingModule], LOW);

	//Setup LED pins
	for (size_t i = 0; i < ARRAY_LENGTH(segmentPins); i++) {
		pinMode(segmentPins[i], OUTPUT);
	}
}

void LEDdisplay::addModule(size_t moduleID, unsigned int moduleGroundPin) {
	if (moduleID >= moduleCount) return; //Prevent buffer overrun
	moduleGrounds[moduleID] = moduleGroundPin;
	digitalWrite(moduleGroundPin, HIGH);
	pinMode(moduleGroundPin, OUTPUT);
}

void LEDdisplay::multiplex() {
	//Split the currently displayed digit into an array
	unsigned int currentlyDisplayingDigits[moduleCount]; 
	if (currentlyDisplayingNumber <= getMaximumDisplayableNumber()) {
		unsigned int place = 1;
		for (size_t i = ARRAY_LENGTH(currentlyDisplayingDigits); i > 0; i--) { //loop backwards from the 
			currentlyDisplayingDigits[i - 1] = (currentlyDisplayingNumber / place) % 10;
			place *= 10;
		}
	} else { //Number too big, display blank
		currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 2] = 10;
		currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 1] = 10;
	}

	//Check if we need to change which LED we're displaying on
	if (millis() - lastMultiplexUpdate > multiplexUpdateInterval) {
		lastMultiplexUpdate = millis();
		currentlyDisplayingModule++;
		if (currentlyDisplayingModule > ARRAY_LENGTH(moduleGrounds)) currentlyDisplayingModule = 0;
		updateCurrentDisplay();
	}

	//Redisplay only if the last number isn't what we're trying to display
	if (lastDisplayedDigit != currentlyDisplayingDigits[currentlyDisplayingModule]) {
		lastDisplayedDigit = currentlyDisplayingDigits[currentlyDisplayingModule];
		displayDigit(currentlyDisplayingDigits[currentlyDisplayingModule]);
	}
}

void LEDdisplay::setCurrentlyDisplayingNumber(unsigned int num) {
	currentlyDisplayingNumber = num;
}
unsigned int LEDdisplay::getCurrentlyDisplayingNumber() {
	return currentlyDisplayingNumber;
}

unsigned int LEDdisplay::getMaximumDisplayableNumber() {
	return ceil(pow(10, moduleCount)) - 1;
}