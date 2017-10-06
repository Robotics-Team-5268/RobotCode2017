
#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../CommandBase.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"

class DriveWithJoystick: public CommandBase {
public:
	DriveWithJoystick();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
