#ifndef AutoDriveForward_H
#define AutoDriveForward_H

#include "../CommandBase.h"
#include "../Robot.h"
#include "Commands/Subsystem.h"

class AutoDriveForward : public CommandBase, public PIDOutput, public PIDSource {
public:
	AutoDriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDController* pidAngle;
	PIDController* pidDistance;
	double PIDGet();
	int x1Transformed, x2Transformed;
	void PIDWrite(double output);
};

#endif  // AutoDriveForward_H
