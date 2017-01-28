#include "RadialDrive.h"

RadialDrive::RadialDrive(double rotateAmt, double spd) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Command::Requires(drive.get());
	Command::Requires(sighting.get());
	pid = nullptr;
	speed = spd;
	rotate = rotateAmt;
}

RadialDrive::RadialDrive(double spd) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Command::Requires(drive.get());
	Command::Requires(sighting.get());
	pid = nullptr;
	speed = spd;
	rotate = sighting->FindDesiredAngle();
}

// Called just before this Command runs the first time
void RadialDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RadialDrive::Execute() {
	// this outputs the pid values to the Smart Dashboard
	if(pid){
			SmartDashboard::PutNumber("P", pid->GetP());
			SmartDashboard::PutNumber("I", pid->GetI());
			SmartDashboard::PutNumber("D", pid->GetD());
			SmartDashboard::PutNumber("F", pid->GetF());
		}else{
			pid = new PIDController(
								SmartDashboard::GetNumber("P", .03),
								SmartDashboard::GetNumber("I", .005),
								SmartDashboard::GetNumber("D", .01),
								SmartDashboard::GetNumber("F", 0),
								drive->getGyro(),
								this
								);
			pid->SetInputRange(-180, 180);
			pid->SetOutputRange(-.75, .75);
			pid->SetAbsoluteTolerance(3);
			pid->Enable();
			pid->SetSetpoint(rotate);
		}

}

// Make this return true when this Command no longer needs to run execute()
bool RadialDrive::IsFinished() {
	return pid->OnTarget();
}

// Called once after isFinished returns true
void RadialDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RadialDrive::Interrupted() {

}

void RadialDrive::PIDWrite(double output) {
	// double LeftPoint = acos((d1^2 + 8.5^2 - d2^2)/(2 * d1 * KHyp));
	// double robotToMidPtSquared = d1^2 + KHyp^2 - 2 * d1 * KHyp * cos(LeftPoint)
	double X = 0.05;

	CommandBase::drive->robotDrive4->MecanumDrive_Cartesian(X, 0.0, this->pid->Get());
	//CommandBase::robotDrive4MecanumDrive_Cartesian(X, 0, boardAng, gyro->GetAngle());
}
