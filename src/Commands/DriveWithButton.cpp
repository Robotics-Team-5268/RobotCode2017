
#include <Commands/DriveWithButton.h>


DriveWithButton::DriveWithButton(): CommandBase() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
	Requires(drive.get());
}

// Called just before this Command runs the first time
void DriveWithButton::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DriveWithButton::Execute() {
	drive->setMotors(1, 1);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithButton::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DriveWithButton::End() {
	drive->setMotors(0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithButton::Interrupted() {

}
