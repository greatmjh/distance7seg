#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

class Ultrasonic {
private:
	const unsigned int echoPin;
	const unsigned int triggerPin;
	long m_distance;
public:
	Ultrasonic(unsigned int echoPin, unsigned int triggerPin);
	long getDistance();
};

#endif //ULTRASONIC_HPP