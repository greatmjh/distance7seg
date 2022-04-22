#ifndef LEDDISPLAY_HPP
#define LEDDISPLAY_HPP

#include "constants.hpp"

class LEDdisplay {
private:
	//Internal module info
	const unsigned int moduleCount; //Number of modules being multiplexed by this object
	unsigned int* moduleGrounds = nullptr; //Dynamic array of ground pins for multiplexing
	
	//Constants
	const bool numbers[11][7] = { //The "font" to use to display things
		{true, true, true, true, true, true, false}, 		//0
		{false, true, true, false, false, false, false}, 	//1
		{true, true, false, true, true, false, true}, 		//2
		{true, true, true, true, false, false, true},		//3
		{false, true, true, false, false, true, true},		//4
		{true, false, true, true, false, true, true},		//5
		{true, false, true, true, true, true, true},		//6
		{true, true, true, false, false, false, false},		//7
		{true, true, true, true, true, true, true},			//8
		{true, true, true, true, false, true, true},		//9
		{false, false, false, false, false, false, false}	//Blank
	};
	const unsigned int multiplexUpdateInterval = 2; //How often to multiplex
	const unsigned int segmentPins[7]; //Will get initialised in initialiser

	//Globals
	unsigned int currentlyDisplayingModule = 0; //Which module is being targeted by multiplexor
	unsigned long lastMultiplexUpdate = 0; //Last time multiplexing happened
	unsigned int currentlyDisplayingNumber; //The number being displayed over the whole module

	//Internal utility functions
	void displayDigit(unsigned int digit); //Push a digit to the pins
	void updateCurrentDisplay(); //Push the current multiplexing info to ground pins

public:
	//Setup
	LEDdisplay(unsigned int _moduleCount, unsigned int segmentA, unsigned int segmentB, unsigned int segmentC, unsigned int segmentD, unsigned int segmentE, unsigned int segmentF, unsigned int segmentG);
	void addModule(size_t moduleID, unsigned int module); //Initialiser won't add modules, so run this after
	void multiplex(); //Run every loop cycle
	//Setters
	void setCurrentlyDisplayingNumber(unsigned int num);
	//Getters
	unsigned int getCurrentlyDisplayingNumber();
	unsigned int getMaximumDisplayableNumber();
};

#endif