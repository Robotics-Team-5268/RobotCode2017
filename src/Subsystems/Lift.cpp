#include "Lift.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

Lift::Lift() : Subsystem("Lift") {
	speedController1 = RobotMap::speedControllerLift1;
	speedController2 = RobotMap::speedControllerLift2;
}

void Lift::takeInput(){
	bool buttonA = CommandBase::oi->getShooterButtonPressed(1);

	setMotors((float)buttonA);
}

//Both motors move in same direction, so only 1 speed is necessary.
void Lift::setMotors(float speed){
	speedController1->Set(speed);
	speedController2->Set(speed);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
