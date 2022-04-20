#ifndef LEDDISPLAY_HPP
#define LEDDISPLAY_HPP

#include "constants.hpp"

class LEDdisplay {
private:
	//Internal module info
	const unsigned int moduleCount;
	unsigned int* moduleGrounds = nullptr;
	
	//Constants
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
		{false, false, false, false, false, false, false}
	};
	const unsigned int multiplexUpdateInterval = 2;
	const unsigned int segmentPins[7];

	//Globals
	unsigned int currentlyDisplayingModule = 0;
	unsigned int lastDisplayedDigit = ARRAY_LENGTH(numbers);
	unsigned long lastMultiplexUpdate = 0;
	unsigned int currentlyDisplayingNumber;

	//Internal utility functions
	void displayDigit(unsigned int digit);
	void updateCurrentDisplay();

public:
	//Setup
	LEDdisplay(unsigned int _moduleCount, unsigned int segmentA, unsigned int segmentB, unsigned int segmentC, unsigned int segmentD, unsigned int segmentE, unsigned int segmentF, unsigned int segmentG);
	void addModule(size_t moduleID, unsigned int module);
	void multiplex(); //Run every loop cycle
	//Setters
	void setCurrentlyDisplayingNumber(unsigned int num);
	//Getters
	unsigned int getCurrentlyDisplayingNumber();
	unsigned int getMaximumDisplayableNumber();
};

#endif