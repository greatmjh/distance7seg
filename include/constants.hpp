#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <Arduino.h>

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

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

#endif //CONSTANTS_HPP