#ifndef Sighting_H
#define Sighting_H

#include <Commands/Subsystem.h>

class Sighting : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	Sighting();
	void InitDefaultCommand();
	void FindDesiredHeading();
};

#endif  // Sighting_H
