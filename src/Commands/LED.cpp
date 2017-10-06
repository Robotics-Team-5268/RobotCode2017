#include "LED.h"

LED::LED(): num(1)
{
	Requires(leds.get());
}
LED::LED(int x): num(x)
{
	Requires(leds.get());
}

// Called just before this Command runs the first time
void LED::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void LED::Execute()
{
	leds->IsOn(num) ? leds->TurnOff(num) : leds->TurnOn(num);
}

// Make this return true when this Command no longer needs to run execute()
bool LED::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void LED::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LED::Interrupted()
{

}
