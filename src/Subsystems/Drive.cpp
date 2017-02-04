
#include <Commands/DriveWithJoystick.h>
#include "Robot.h"
#include "Drive.h"
#include "../RobotMap.h"

Drive::Drive() : Subsystem("Drive"){
    speedController1 = RobotMap::speedControllerFL;
    speedController2 = RobotMap::speedControllerFR;
    speedController3 = RobotMap::speedControllerBL;
    speedController4 = RobotMap::speedControllerBR;
    robotDrive4 = RobotMap::driveRobotDrive4;
    //speedController1->SetInverted(true);
    //speedController2->SetInverted(true);
    //speedController3->SetInverted(false);
    //speedController4->SetInverted(false);
    gyro = RobotMap::driveGyro;
}
void Drive::AddSmartDashboardItems()
{
	SmartDashboard::PutNumber("Speed Controller 1", speedController1->Get());
	SmartDashboard::PutNumber("Speed Controller 2", speedController2->Get());
	SmartDashboard::PutNumber("Speed Controller 3", speedController3->Get());
	SmartDashboard::PutNumber("Speed Controller 4", speedController4->Get());
	SmartDashboard::PutNumber("Gyro Angle", gyro->GetAngle());
}
void Drive::InitDefaultCommand() {
    // Set the default command for a subsystem here.
	SetDefaultCommand(new DriveWithJoystick());
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drive::takeInput(){
	float X = -CommandBase::oi->getDriverJoystick()->GetX();
	float Y = -CommandBase::oi->getDriverJoystick()->GetY();
	float rotateAmt = CommandBase::oi->getDriverJoystick()->GetRawAxis(LEFT_TRIGGER) - CommandBase::oi->getDriverJoystick()->GetRawAxis(RIGHT_TRIGGER);


	robotDrive4->MecanumDrive_Cartesian(X, Y, rotateAmt);
}
void Drive::setMotors(float leftSpeed, float rightSpeed){
	speedController1->Set(-rightSpeed);
	speedController2->Set(-rightSpeed);
	speedController3->Set(leftSpeed);
	speedController4->Set(leftSpeed);
}
float Drive::returnAngle(){
	return gyro->GetAngle();
}
AnalogGyro* Drive::getGyro()
{
	return gyro.get();
}

