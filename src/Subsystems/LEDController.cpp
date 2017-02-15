#include "LEDController.h"
#include "../RobotMap.h"

LEDController::LEDController() : Subsystem("LEDController")
{
	ledRelay1 = RobotMap::ledRelay1;
	ledRelay2 = RobotMap::ledRelay2;
}

void LEDController::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void LEDController::TurnOff(int num)
{
	switch(num)
	{
	case 1:
			ledRelay1->Set(frc::Relay::kOff);
			break;
	case 2:
			ledRelay2->Set(frc::Relay::kOff);
			break;
	}
}

void LEDController::TurnOn(int num)
{
	switch(num)
		{
		case 1:
				ledRelay1->Set(frc::Relay::kOn);
				break;
		case 2:
				ledRelay2->Set(frc::Relay::kOn);
				break;
		}
}
bool LEDController::IsOn(int num)
{
	switch(num)
	{
		case 1:
			return (ledRelay1->Get() == frc::Relay::kOn ? true : false);
		case 2:
			return (ledRelay2->Get() == frc::Relay::kOn ? true : false);
	}
	return false;
}
