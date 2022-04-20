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
	long m_duration = pulseIn(echoPin, HIGH);
	//Serial.println(m_duration);
	m_distance = m_duration * 0.034 / 2;
	return m_distance;
}
