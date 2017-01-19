#include "LEDController.h"
#include "../RobotMap.h"

LEDController::LEDController() : Subsystem("LEDController")
{
	ledRelay1 = RobotMap::ledRelay1;
	ledRelay2 = RobotMap::ledRelay2;
	ledRelay3 = RobotMap::ledRelay3;
	ledRelay4 = RobotMap::ledRelay4;
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
			ledRelay1->Set(Relay::kOff);
			break;
	case 2:
			ledRelay2->Set(Relay::kOff);
			break;
	case 3:
			ledRelay3->Set(Relay::kOff);
			break;
	case 4:
			ledRelay4->Set(Relay::kOff);
			break;
	}
}

void LEDController::TurnOn(int num)
{
	switch(num)
		{
		case 1:
				ledRelay1->Set(Relay::kOn);
				break;
		case 2:
				ledRelay2->Set(Relay::kOn);
				break;
		case 3:
				ledRelay3->Set(Relay::kOn);
				break;
		case 4:
				ledRelay4->Set(Relay::kOn);
				break;
		}
}
bool LEDController::IsOn(int num)
{
	switch(num)
	{
		case 1:
			return (ledRelay1->Get() == Relay::kOn ? true : false);
		case 2:
			return (ledRelay2->Get() == Relay::kOn ? true : false);
		case 3:
			return (ledRelay3->Get() == Relay::kOn ? true : false);
		case 4:
			return (ledRelay4->Get() == Relay::kOn ? true : false);
	}
	return false;
}
