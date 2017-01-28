#ifndef RadialDrive_H
#define RadialDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Sighting.h"
#include "../RobotMap.h"

class RadialDrive : public CommandBase, public PIDOutput {
public:
	RadialDrive(double rotateAmt, double spd);
	RadialDrive(double spd);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double rotate;
	double speed;
	PIDController* pid;
	void PIDWrite(double output);
private:
	std::shared_ptr<ADXRS450_Gyro> gyro;
};

#endif  // RadialDrive_H
