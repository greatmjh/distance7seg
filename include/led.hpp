#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>
#include <constants.hpp>

//LED Functions
void setupLED();
void displayNumber();
void setCurrentlyDisplayingNumber(unsigned int num);
unsigned int getCurrentlyDisplayingNumber();

#endif //LED_HPP