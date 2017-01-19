
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "PIDController.h"

std::shared_ptr<SpeedController> RobotMap::driveSpeedController1;
std::shared_ptr<SpeedController> RobotMap::driveSpeedController2;
std::shared_ptr<SpeedController> RobotMap::driveSpeedController3;
std::shared_ptr<SpeedController> RobotMap::driveSpeedController4;
std::shared_ptr<RobotDrive> RobotMap::driveRobotDrive4;

std::shared_ptr<ADXRS450_Gyro> RobotMap::driveGyro;

std::shared_ptr<Relay> RobotMap::ledRelay1;
std::shared_ptr<Relay> RobotMap::ledRelay2;
std::shared_ptr<Relay> RobotMap::ledRelay3;
std::shared_ptr<Relay> RobotMap::ledRelay4;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    driveSpeedController1.reset(new Talon(DRIVE_SPEED_CONTROLLER_1_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 1", (Talon&) driveSpeedController1);
    
    driveSpeedController2.reset(new Talon(DRIVE_SPEED_CONTROLLER_2_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 2", (Talon&) driveSpeedController2);
    
    driveSpeedController3.reset(new Talon(DRIVE_SPEED_CONTROLLER_3_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 3", (Talon&) driveSpeedController3);
    
    driveSpeedController4.reset(new Talon(DRIVE_SPEED_CONTROLLER_4_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 4", (Talon&) driveSpeedController4);
    
    driveRobotDrive4.reset(new RobotDrive(driveSpeedController3, driveSpeedController4,
              driveSpeedController1, driveSpeedController2));
    
    driveRobotDrive4->SetSafetyEnabled(false);
	driveRobotDrive4->SetExpiration(0.1);
	driveRobotDrive4->SetSensitivity(0.5);
	driveRobotDrive4->SetMaxOutput(1.0);

    driveGyro.reset(new ADXRS450_Gyro(SPI::kOnboardCS0));
    driveGyro->Calibrate();
    //lw->AddActuator("Drive", "Drive Gyro", driveGyro);
    //shooterSpeedController->SetControlMode(CANSpeedController::kSpeed);
    //shooterSpeedController->SetPID(.3, .003, 3.0, 0.0);

    ledRelay1.reset(new Relay(0, Relay::kReverseOnly));
	ledRelay1->Set(Relay::kOff);
	ledRelay2.reset(new Relay(1, Relay::kReverseOnly));
	ledRelay2->Set(Relay::kOff);
	ledRelay3.reset(new Relay(2, Relay::kReverseOnly));
	ledRelay3->Set(Relay::kOff);
	ledRelay4.reset(new Relay(3, Relay::kReverseOnly));
	ledRelay4->Set(Relay::kOff);
}
