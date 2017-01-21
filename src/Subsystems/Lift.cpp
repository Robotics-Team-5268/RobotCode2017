#include "Lift.h"
#include "../RobotMap.h"

Lift::Lift() : Subsystem("Lift") {
	speedController1 = RobotMap::speedControllerLift1;
	speedController2 = RobotMap::speedControllerLift2;
}

//Both motors move in same direction, so only 1 speed is necessary.
void Lift::setMotors(float speed){
	speedController1->Set(speed);
	speedController2->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
