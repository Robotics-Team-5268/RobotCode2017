
#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"
#include "RobotParameters.h"
#include "Subsystems/Sighting.h"

class RobotMap {
public:
	static std::shared_ptr<SpeedController> speedControllerFL; // Front Left
	static std::shared_ptr<SpeedController> speedControllerFR; // Front Right
	static std::shared_ptr<SpeedController> speedControllerBL; // Back Left
	static std::shared_ptr<SpeedController> speedControllerBR; // Back Right

	static std::shared_ptr<SpeedController> speedControllerLift; // Guess what these are for.
	// Change ports of Speed Controllers to match positions of motors on Robot

	static std::shared_ptr<RobotDrive> driveRobotDrive4;
	//static std::shared_ptr<ADXRS450_Gyro>driveGyro;
	static std::shared_ptr<AnalogGyro>driveGyro;

	static std::shared_ptr<Relay> ledRelay1;
	static std::shared_ptr<Relay> ledRelay2;
	static std::shared_ptr<Relay> ledRelay3;
	static std::shared_ptr<Relay> ledRelay4;

	static std::shared_ptr<Sighting> sighting;

	static void init();
};
#endif // ROBOTMAP_H
