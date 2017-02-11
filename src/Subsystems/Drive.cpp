
#include <Commands/DriveWithJoystick.h>
#include "Robot.h"
#include "Drive.h"
#include "../RobotMap.h"

Drive::Drive() : Subsystem("Drive"){
    speedControllerFL = RobotMap::speedControllerFL;
    speedControllerFR = RobotMap::speedControllerFR;
    speedControllerBL = RobotMap::speedControllerBL;
    speedControllerBR = RobotMap::speedControllerBR;
    robotDrive4 = RobotMap::driveRobotDrive4;
    //speedController1->SetInverted(true);
    //speedController2->SetInverted(true);
    //speedController3->SetInverted(false);
    //speedController4->SetInverted(false);
    gyro = RobotMap::driveGyro;
}
void Drive::AddSmartDashboardItems()
{
	SmartDashboard::PutNumber("Speed Controller 1", speedControllerFL->Get());
	SmartDashboard::PutNumber("Speed Controller 2", speedControllerFR->Get());
	SmartDashboard::PutNumber("Speed Controller 3", speedControllerBL->Get());
	SmartDashboard::PutNumber("Speed Controller 4", speedControllerBR->Get());
	SmartDashboard::PutNumber("Gyro Angle", gyro->GetAngle());
	SmartDashboard::PutNumber("Joystick X", CommandBase::oi->getDriverJoystick()->GetX());
	SmartDashboard::PutNumber("Joystick Y", CommandBase::oi->getDriverJoystick()->GetY());
	SmartDashboard::PutNumber("Left Trigger", CommandBase::oi->getDriverJoystick()->GetRawAxis(LEFT_TRIGGER));
	SmartDashboard::PutNumber("Right Trigger", CommandBase::oi->getDriverJoystick()->GetRawAxis(RIGHT_TRIGGER));
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
	speedControllerFL->Set(leftSpeed);
	speedControllerFR->Set(rightSpeed);
	speedControllerBL->Set(leftSpeed);
	speedControllerBR->Set(rightSpeed);
}
float Drive::returnAngle(){
	return gyro->GetAngle();
}
ADXRS450_Gyro* Drive::getGyro()
{
	return gyro.get();
}

