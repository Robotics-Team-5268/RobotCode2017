#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "PIDController.h"
#include "CANTalon.h"

std::shared_ptr<SpeedController> RobotMap::speedControllerFL;
std::shared_ptr<SpeedController> RobotMap::speedControllerFR;
std::shared_ptr<SpeedController> RobotMap::speedControllerBL;
std::shared_ptr<SpeedController> RobotMap::speedControllerBR;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift1;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift2;
std::shared_ptr<RobotDrive> RobotMap::driveRobotDrive4;

std::shared_ptr<Sighting> RobotMap::sighting;

 std::shared_ptr<ADXRS450_Gyro> RobotMap::driveGyro;
//std::shared_ptr<AnalogGyro> RobotMap::driveGyro;

std::shared_ptr<Relay> RobotMap::ledRelay1;
std::shared_ptr<Relay> RobotMap::ledRelay2;
std::shared_ptr<Relay> RobotMap::ledRelay3;

std::shared_ptr<Sighting> sighting;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    speedControllerFL.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_FL_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller FL", (CANTalon&) speedControllerFL);
    
    speedControllerFR.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_FR_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller FR", (CANTalon&) speedControllerFR);
    
    speedControllerBL.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_BL_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller BL", (CANTalon&) speedControllerBL);
    
    speedControllerBR.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_BR_CHANNEL));
    lw->AddActuator("Drive", "Speed Controller BR", (CANTalon&) speedControllerBR);
    
    speedControllerLift1.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_1));
        lw->AddActuator("Lift", "Speed Controller Lift", (CANTalon&) speedControllerLift1);

	speedControllerLift2.reset(new CANTalon(DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_2));
		  lw->AddActuator("Lift", "Speed Controller Lift", (CANTalon&) speedControllerLift1);

    driveRobotDrive4.reset(new RobotDrive(speedControllerFL, speedControllerBL,
              speedControllerFR, speedControllerBR));
    sighting.reset(new Sighting());
    
    driveRobotDrive4->SetSafetyEnabled(false);
	driveRobotDrive4->SetExpiration(0.1);
	driveRobotDrive4->SetSensitivity(0.5);
	driveRobotDrive4->SetMaxOutput(1.0);

	speedControllerFL->SetInverted(SCFL_INVERTED);
	speedControllerBL->SetInverted(SCBL_INVERTED);
	speedControllerFR->SetInverted(SCFR_INVERTED);
	speedControllerBR->SetInverted(SCBR_INVERTED);


    driveGyro.reset(new ADXRS450_Gyro(SPI::kOnboardCS0));
	// driveGyro.reset(new AnalogGyro(GYRO_ANALOG_PORT));
    driveGyro->Calibrate();
    //lw->AddActuator("Drive", "Drive Gyro", driveGyro);
    //shooterSpeedController->SetControlMode(CANSpeedController::kSpeed);
    //shooterSpeedController->SetPID(.3, .003, 3.0, 0.0);

    ledRelay1.reset(new Relay(0, Relay::kForwardOnly));
	ledRelay1->Set(Relay::kOff);
	ledRelay2.reset(new Relay(1, Relay::kForwardOnly));
	ledRelay2->Set(Relay::kOff);
	ledRelay3.reset(new Relay(2, Relay::kForwardOnly));
	ledRelay3->Set(Relay::kOff);
}
