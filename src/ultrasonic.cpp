#include "ultrasonic.hpp"
#include <Arduino.h>

Ultrasonic::Ultrasonic(unsigned int _echoPin, unsigned int _triggerPin) :
	echoPin(_echoPin), triggerPin(_triggerPin) {
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}
long Ultrasonic::getDistance() {
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);

	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);
	unsigned long m_duration = pulseIn(echoPin, HIGH, 6000);
	if (!m_duration) m_duration = -1; //If the pulse doesn't come back, make it the integer limit to show as overload instead of 0
	m_distance = m_duration * 0.034 / 2;
	return m_distance;
}
