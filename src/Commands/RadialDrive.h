#ifndef RadialDrive_H
#define RadialDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Sighting.h"
#include "../RobotMap.h"

class RadialDriveDistancePIDOut;

class RadialDrive : public CommandBase, public PIDOutput {
public:
	RadialDrive();
	~RadialDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	PIDController* pidAngle;
	PIDController* pidDistance;
	void PIDWrite(double output);
private:
	std::unique_ptr<RadialDriveDistancePIDOut> theDistancePID;
};

class RadialDriveDistancePIDOut : public PIDOutput, public PIDSource {
	public:
		RadialDriveDistancePIDOut(Sighting* obj);
		~RadialDriveDistancePIDOut();
		void PIDWrite(double output);
		double PIDGet();

	private:
		Sighting* sighting;
};
#endif  // RadialDrive_H
