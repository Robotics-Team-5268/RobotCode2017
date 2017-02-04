#include "AutoDriveForward.h"

AutoDriveForward::AutoDriveForward() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void AutoDriveForward::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveForward::Execute() {
	if (pidAngle){
				SmartDashboard::PutNumber("Pang", pidAngle->GetP());
				SmartDashboard::PutNumber("Iang", pidAngle->GetI());
				SmartDashboard::PutNumber("Dang", pidAngle->GetD());
				SmartDashboard::PutNumber("Fang", pidAngle->GetF());
			}else{
				pidAngle = new PIDController(
									SmartDashboard::GetNumber("Pang", .03),
									SmartDashboard::GetNumber("Iang", .005),
									SmartDashboard::GetNumber("Dang", .01),
									SmartDashboard::GetNumber("Fang", 0),
									this,
									this
									);
				pidAngle->SetInputRange(-1, 1);
				pidAngle->SetOutputRange(-.5, .5);
				pidAngle->SetAbsoluteTolerance(.025);
				pidAngle->Enable();

				x1Transformed = ((CommandBase::sighting->centerX[0] - CAMERA_XRES / 2) / (CAMERA_XRES / 2));
				x2Transformed = ((CommandBase::sighting->centerX[1] - CAMERA_XRES / 2) / (CAMERA_XRES / 2));

				pidAngle->SetSetpoint((x1Transformed + x2Transformed) / 2);
			}
	/*if (pidDistance){
					SmartDashboard::PutNumber("Pdist", pidDistance->GetP());
					SmartDashboard::PutNumber("Idist", pidDistance->GetI());
					SmartDashboard::PutNumber("Ddist", pidDistance->GetD());
					SmartDashboard::PutNumber("Fdist", pidDistance->GetF());
				}else{
					pidDistance = new PIDController(
										SmartDashboard::GetNumber("Pdist", .03),
										SmartDashboard::GetNumber("Idist", .005),
										SmartDashboard::GetNumber("Ddist", .01),
										SmartDashboard::GetNumber("Fdist", 0),
										drive->getGyro(),
										this
										);
					pidDistance->SetInputRange(-180, 180);
					pidDistance->SetOutputRange(-.75, .75);
					pidDistance->SetAbsoluteTolerance(3);
					pidDistance->Enable();
					pidDistance->SetSetpoint(rotate);
				}*/
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveForward::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoDriveForward::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveForward::Interrupted() {

}
double AutoDriveForward::PIDGet(){
	return X_ORIGIN_OFFSET;
}
void AutoDriveForward::PIDWrite(double output) {

	CommandBase::drive->robotDrive4->MecanumDrive_Cartesian(0.0, 0.0, this->pidAngle->Get());
	//CommandBase::robotDrive4MecanumDrive_Cartesian(X, 0, boardAng, gyro->GetAngle());
}
