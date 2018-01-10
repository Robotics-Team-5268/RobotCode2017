#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "PIDController.h"
#include "SpeedController.h"

std::shared_ptr<SpeedController> RobotMap::speedControllerFL;
std::shared_ptr<SpeedController> RobotMap::speedControllerFR;
std::shared_ptr<SpeedController> RobotMap::speedControllerBL;
std::shared_ptr<SpeedController> RobotMap::speedControllerBR;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift1;
std::shared_ptr<SpeedController> RobotMap::speedControllerLift2;
std::shared_ptr<RobotDrive> RobotMap::driveRobotDrive4;

std::shared_ptr<Sighting> RobotMap::sighting;

 std::shared_ptr<ADXRS450_Gyro> RobotMap::driveGyro;
//std::shared_ptr<AnalogGyro> RobotMap::driveGyro;s

std::shared_ptr<Relay> RobotMap::ledRelay[3];

std::shared_ptr<Sighting> sighting;

void RobotMap::init() {
    LiveWindow *lw = LiveWindow::GetInstance();

    speedControllerFL.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_FL_CHANNEL));
    // lw->AddActuator("Drive",  "Speed Controller FL", (TalonSRX&) speedControllerFL);
    
    speedControllerFR.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_FR_CHANNEL));
    // lw->AddActuator("Drive", "Speed Controller FR", (TalonSRX&) speedControllerFR);
    
    speedControllerBL.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_BL_CHANNEL));
    // lw->AddActuator("Drive", "Speed Controller BL", (TalonSRX&) speedControllerBL);
    
    speedControllerBR.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_BR_CHANNEL));
    // lw->AddActuator("Drive", "Speed Controller BR", (TalonSRX&) speedControllerBR);
    
    speedControllerLift1.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_1));
    // lw->AddActuator("Lift", "Speed Controller Lift", (TalonSRX&) speedControllerLift1);

	speedControllerLift2.reset(new WPI_TalonSRX(DRIVE_SPEED_CONTROLLER_LIFT_CHANNEL_2));
	// lw->AddActuator("Lift", "Speed Controller Lift", (TalonSRX&) speedControllerLift1);

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

    for(int i = 0; i < 3; i++){
    	ledRelay[i].reset(new Relay(i, Relay::kBothDirections));
    	ledRelay[i]->Set(Relay::kOff);
    }
}
