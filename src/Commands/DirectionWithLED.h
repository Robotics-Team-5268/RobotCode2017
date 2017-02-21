#ifndef DirectionWIthLED_H
#define DirectionWIthLED_H

#include "../CommandBase.h"
#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../RobotParameters.h"

class DirectionWithLED : public CommandBase {
public:
	DirectionWithLED();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DirectionWIthLED_H
