#ifndef RadialDrive_H
#define RadialDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Sighting.h"
#include "../RobotMap.h"

class RadialDrivePIDOutput;

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
	PIDController* pid2;
	RadialDrivePIDOutput* radialDrivePIDOutput;
	void PIDWrite(double output);
private:
	std::shared_ptr<ADXRS450_Gyro> gyro;
};

class RadialDrivePIDOutput : public PIDOutput, public PIDSource {
	public:
	void PIDWrite(double output);
	double PIDGet();
};
#endif  // RadialDrive_H
