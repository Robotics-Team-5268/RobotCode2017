#ifndef RadialDrive_H
#define RadialDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Sighting.h"
#include "../RobotMap.h"

class RadialDriveDistancePIDOut;

class RadialDrive : public CommandBase, public PIDOutput {
public:
	RadialDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	PIDController* pidAngle;
	PIDController* pidDistance;
	void PIDWrite(double output);
private:
	std::shared_ptr<ADXRS450_Gyro> gyro;
	std::unique_ptr<RadialDriveDistancePIDOut> theDistancePID;
};

class RadialDriveDistancePIDOut : public PIDOutput, public PIDSource {
	public:
	RadialDriveDistancePIDOut(double centerX1, double centerX2);
	void PIDWrite(double output);
	double PIDGet();
	double centerX;
};
#endif  // RadialDrive_H
