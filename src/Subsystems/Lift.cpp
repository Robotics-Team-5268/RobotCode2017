#include "Lift.h"
#include "../RobotMap.h"
#include "../CommandBase.h"
#include "../Commands/LiftWithButton.h"

Lift::Lift() : Subsystem("Lift") {
	speedController1 = RobotMap::speedControllerLift1;
	speedController2 = RobotMap::speedControllerLift2;
	dynamic_cast<WPI_TalonSRX*>(speedController1.get())->Set(ctre::phoenix::motorcontrol::ControlMode::Position, 0);
}

void Lift::takeInput(bool ForR){
	bool buttonA = CommandBase::oi->getDriverButtonPressed(4);

	// SmartDashboard::PutNumber("Encoder Position",((TalonSRX*)speedController1.get())->GetEncPosition());
	//State machine
	if(dynamic_cast<WPI_TalonSRX*>(speedController1.get())->GetOutputCurrent() >= 15){
		if(getclimbing_rope()==false){
			setclimbing_rope(true);
			dynamic_cast<WPI_TalonSRX*>(speedController1.get())->Set(ctre::phoenix::motorcontrol::ControlMode::Position, 0);
		}
	}
	if(ForR)
	setMotors(0.5 * (float)buttonA); // we're multiplying by a decimal because buttonA is only 0 or 1
	else
	setMotors(-0.5 * (float)buttonA);
}

//Both motors move in same direction, so only 1 speed is necessary.
void Lift::setMotors(float speed){
	speedController1->Set(-speed);
	speedController2->Set(-speed);

}

void Lift::InitDefaultCommand()
{
	SetDefaultCommand(new LiftWithButton(1));
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
