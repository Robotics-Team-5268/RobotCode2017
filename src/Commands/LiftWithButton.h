#ifndef LiftWithButton_H
#define LiftWithButton_H

#include "../CommandBase.h"

class LiftWithButton : public CommandBase {
public:
	LiftWithButton();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // LiftWithButton_H
