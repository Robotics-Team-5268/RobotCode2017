#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "PIDController.h"

std::shared_ptr<SpeedController> RobotMap::speedControllerFL;
std::shared_ptr<SpeedController> RobotMap::speedControllerFR;
std::shared_ptr<SpeedController> RobotMap::speedControllerBL;
std::shared_ptr<SpeedController> RobotMap::speedControllerBR;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift1;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift2;
std::shared_ptr<RobotDrive> RobotMap::driveRobotDrive4;

std::shared_ptr<Sighting> RobotMap::sighting;

std::shared_ptr<ADXRS450_Gyro> RobotMap::driveGyro;

std::shared_ptr<Relay> RobotMap::ledRelay1;
std::shared_ptr<Relay> RobotMap::ledRelay2;
std::shared_ptr<Relay> RobotMap::ledRelay3;
std::shared_ptr<Relay> RobotMap::ledRelay4;

std::shared_ptr<Sighting> sighting;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    speedControllerFL.reset(new Talon(DRIVE_SPEED_CONTROLLER_FL_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 1", (Talon&) speedControllerFL);
    
    speedControllerFR.reset(new Talon(DRIVE_SPEED_CONTROLLER_FR_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 2", (Talon&) speedControllerFR);
    
    speedControllerBL.reset(new Talon(DRIVE_SPEED_CONTROLLER_BL_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 3", (Talon&) speedControllerBL);
    
    speedControllerBR.reset(new Talon(DRIVE_SPEED_CONTROLLER_BR_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller 4", (Talon&) speedControllerBR);
    
    speedControllerLift1.reset(new Talon(DRIVE_SPEED_CONTROLLER_LIFT_1_CHANNEL));
        lw->AddActuator("Lift", "Speed Controller Lift 1", (Talon&) speedControllerLift2);

	speedControllerLift2.reset(new Talon(DRIVE_SPEED_CONTROLLER_LIFT_2_CHANNEL));
		lw->AddActuator("Lift", "Speed Controller Lift 2", (Talon&) speedControllerLift1);

    driveRobotDrive4.reset(new RobotDrive(speedControllerFL, speedControllerBL,
              speedControllerFR, speedControllerBR));
    sighting.reset(new Sighting());
    
    driveRobotDrive4->SetSafetyEnabled(false);
	driveRobotDrive4->SetExpiration(0.1);
	driveRobotDrive4->SetSensitivity(0.5);
	driveRobotDrive4->SetMaxOutput(1.0);

	speedControllerFL->SetInverted(true);
	speedControllerBL->SetInverted(true);

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
