
#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Drive: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<SpeedController> speedController1;
	std::shared_ptr<SpeedController> speedController2;
	std::shared_ptr<SpeedController> speedController3;
	std::shared_ptr<SpeedController> speedController4;
	std::shared_ptr<RobotDrive> robotDrive4;

	std::shared_ptr<ADXRS450_Gyro> gyro;
public:
	Drive();
	void safetyOff(){robotDrive4->SetSafetyEnabled(false);}
	void InitDefaultCommand();
	void AddSmartDashboardItems();
	ADXRS450_Gyro* getGyro();
	void setMotors(float leftSpeed, float rightSpeed);
	float returnAngle();
	void takeInput();
};

#endif
