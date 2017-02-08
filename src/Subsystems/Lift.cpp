#include "Lift.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

Lift::Lift() : Subsystem("Lift") {
	speedController1 = RobotMap::speedControllerLift;
}

void Lift::takeInput(){
	bool buttonA = CommandBase::oi->getDriverButtonPressed(4);

	setMotors(0.6 * (float)buttonA); // we're multiplying by a decimal because buttonA is only 0 or 1
}

//Both motors move in same direction, so only 1 speed is necessary.
void Lift::setMotors(float speed){
	speedController1->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
