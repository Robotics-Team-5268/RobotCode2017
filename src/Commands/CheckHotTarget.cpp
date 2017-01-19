#include "CheckHotTarget.h"

/*CheckHotTarget::CheckHotTarget()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(targeting.get());
	timer.reset(new Timer());
	timer->Start();
}

// Called just before this Command runs the first time
void CheckHotTarget::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CheckHotTarget::Execute()
{
	if(timer->HasPeriodPassed(1)){
		timer->Reset();
		timer->Start();
		bool hot = targeting->calculateIsHot();
		SmartDashboard::PutBoolean("Hot", hot);
		if(hot){
			leds->TurnOn(2);
		}else{
			leds->TurnOff(2);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CheckHotTarget::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void CheckHotTarget::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheckHotTarget::Interrupted()
{

}*/
