#ifndef Lift_H
#define Lift_H

#include "Commands/Subsystem.h"
#include "WPIlib.h"

class Lift : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<SpeedController> speedController1;
	std::shared_ptr<SpeedController> speedController2;
	bool climbing_rope = false;
	void InitDefaultCommand();
public:
	Lift();

	void setMotors(float speed);
	void takeInput(bool ForR);
	bool getclimbing_rope() {
		return climbing_rope;
	}
	void setclimbing_rope(bool climbing) {
			climbing_rope = climbing;
		}
};

#endif  // Lift_H
