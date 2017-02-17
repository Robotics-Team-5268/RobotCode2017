#include "RadialDrive.h"

RadialDrive::RadialDrive(){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Command::Requires(drive.get());
	Command::Requires(sighting.get());
	pidAngle = nullptr;
	pidDistance = nullptr;
	if(sighting->TwoTargetsAvailable())
		theDistancePID.reset(new RadialDriveDistancePIDOut(sighting.get()));
	else
		Cancel();
}

// Called just before this Command runs the first time
void RadialDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RadialDrive::Execute() {
	// this outputs the pid values to the Smart Dashboard
	if(pidAngle){
			SmartDashboard::PutNumber("P", pidAngle->GetP());
			SmartDashboard::PutNumber("I", pidAngle->GetI());
			SmartDashboard::PutNumber("D", pidAngle->GetD());
			SmartDashboard::PutNumber("F", pidAngle->GetF());

			sighting->readTable();
			pidAngle->SetSetpoint(drive->getGyro()->GetAngle() + sighting->findBoardAngle());
		}else{
			pidAngle = new PIDController(
								SmartDashboard::GetNumber("P", .03),
								SmartDashboard::GetNumber("I", .005),
								SmartDashboard::GetNumber("D", .01),
								SmartDashboard::GetNumber("F", 0),
								drive->getGyro(),
								this
								);
			pidAngle->SetInputRange(-180, 180);
			pidAngle->SetOutputRange(-.75, .75);
			pidAngle->SetAbsoluteTolerance(3);
			pidAngle->Enable();
		}
	if(pidDistance){
				SmartDashboard::PutNumber("P", pidDistance->GetP());
				SmartDashboard::PutNumber("I", pidDistance->GetI());
				SmartDashboard::PutNumber("D", pidDistance->GetD());
				SmartDashboard::PutNumber("F", pidDistance->GetF());
			}else{
				pidDistance = new PIDController(
									SmartDashboard::GetNumber("P", .03),
									SmartDashboard::GetNumber("I", .005),
									SmartDashboard::GetNumber("D", .01),
									SmartDashboard::GetNumber("F", 0),
									theDistancePID.get(),
									theDistancePID.get()
									);
				pidDistance->SetInputRange(-1, 1);
				pidDistance->SetOutputRange(-.75, .75);
				pidDistance->SetAbsoluteTolerance(.05);
				pidDistance->Enable();
				pidDistance->SetSetpoint(0.0);
			}
	CommandBase::drive->robotDrive4->MecanumDrive_Cartesian(pidDistance->Get(), 0.0, pidAngle->Get());

}

// Make this return true when this Command no longer needs to run execute()
bool RadialDrive::IsFinished() {
	return pidAngle->OnTarget();
}

// Called once after isFinished returns true
void RadialDrive::End() {
	pidAngle->Disable();
	delete pidAngle;
	pidAngle = nullptr;
	pidDistance->Disable();
	delete pidDistance;
	pidDistance = nullptr;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RadialDrive::Interrupted() {}

void RadialDrive::PIDWrite(double output) {}

RadialDriveDistancePIDOut::RadialDriveDistancePIDOut(Sighting* obj):sighting(obj){

}
void RadialDriveDistancePIDOut::PIDWrite(double output){}

double RadialDriveDistancePIDOut::PIDGet(){
	sighting->readTable();
	return X_ORIGIN_OFFSET + sighting->getCenterX();
}
