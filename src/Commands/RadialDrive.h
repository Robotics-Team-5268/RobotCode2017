#ifndef RadialDrive_H
#define RadialDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Sighting.h"
#include "../RobotMap.h"

class RadialDrive : public CommandBase {
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
};
class RadialPIDOutput: public PIDOutput
{
private:
	std::shared_ptr<ADXRS450_Gyro> gyro;
public:
	void PIDWrite(double output);

	double speed;
};

#endif  // RadialDrive_H
