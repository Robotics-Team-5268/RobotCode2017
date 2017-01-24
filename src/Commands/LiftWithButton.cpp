#include "LiftWithButton.h"

LiftWithButton::LiftWithButton() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(lift.get());
}

// Called just before this Command runs the first time
void LiftWithButton::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LiftWithButton::Execute() {
	lift->takeInput();
}

// Make this return true when this Command no longer needs to run execute()
bool LiftWithButton::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void LiftWithButton::End() {
	lift->setMotors(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LiftWithButton::Interrupted() {
	End();
}
