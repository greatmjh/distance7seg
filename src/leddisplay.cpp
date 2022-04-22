#include "leddisplay.hpp"

void LEDdisplay::displayDigit(unsigned int digit) {
	if (digit > ARRAY_LENGTH(numbers)) return; //If the digit isn't defined in the array, don't do anything
	for (size_t i = 0; i < ARRAY_LENGTH(segmentPins); i++) { //Loop through pins
		digitalWrite(segmentPins[i], numbers[digit][i]); 
	}
}

void LEDdisplay::updateCurrentDisplay() {
	for (size_t i = 0; i < moduleCount; i++) { //Loop through the ground pins
		if (i == currentlyDisplayingModule) {
			digitalWrite(moduleGrounds[i], LOW); //If we hit the right ground pin, bring it low to actually be a ground pin
		} else {
			digitalWrite(moduleGrounds[i], HIGH); //Else, bring it high to disable the module
		}
	}
}

LEDdisplay::LEDdisplay(unsigned int _moduleCount, unsigned int segmentA, unsigned int segmentB, unsigned int segmentC, unsigned int segmentD, unsigned int segmentE, unsigned int segmentF, unsigned int segmentG) : 
moduleCount(_moduleCount), segmentPins{segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG} {
	moduleGrounds = new unsigned int[moduleCount]; //Allocate memory for dynamic array
	currentlyDisplayingNumber = 0; //Initialise the variable

	//Setup LED pins
	for (size_t i = 0; i < ARRAY_LENGTH(segmentPins); i++) {
		pinMode(segmentPins[i], OUTPUT);
	}
}

void LEDdisplay::addModule(size_t moduleID, unsigned int moduleGroundPin) {
	if (moduleID >= moduleCount) return; //Prevent buffer overrun
	moduleGrounds[moduleID] = moduleGroundPin; //Set the ground pin in the array
	digitalWrite(moduleGroundPin, HIGH); //Disable the module before making the pin an output
	pinMode(moduleGroundPin, OUTPUT);
}

void LEDdisplay::multiplex() {
	//Is it time to do the next multiplex?
	if (millis() - lastMultiplexUpdate > multiplexUpdateInterval) {
		lastMultiplexUpdate = millis();
		currentlyDisplayingModule++;
		if (currentlyDisplayingModule > ARRAY_LENGTH(moduleGrounds)) currentlyDisplayingModule = 0; //Select the next display module to multiplex

		//Split the currently displayed digit into an array
		unsigned int currentlyDisplayingDigits[moduleCount]; 
		if (currentlyDisplayingNumber <= getMaximumDisplayableNumber()) {
			unsigned int place = 1;
			for (size_t i = ARRAY_LENGTH(currentlyDisplayingDigits); i > 0; i--) { //loop backwards from the most right place
				currentlyDisplayingDigits[i - 1] = (currentlyDisplayingNumber / place) % 10; //gets the digit from the number
				place *= 10;
			}
		} else { //Number too big, display blank
			currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 2] = 10;
			currentlyDisplayingDigits[ARRAY_LENGTH(currentlyDisplayingDigits) - 1] = 10;
		}

		//Push values
		displayDigit(10); //Clear to prevent ghosting on other displays
		updateCurrentDisplay(); //Push that change
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