#ifndef LED_H
#define LED_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Robot.h"

class LED: public CommandBase
{
public:
	LED();
	LED(int x);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	int num;
};

#endif
