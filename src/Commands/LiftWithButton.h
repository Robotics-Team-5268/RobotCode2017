#ifndef LiftWithButton_H
#define LiftWithButton_H

#include "../CommandBase.h"

class LiftWithButton : public CommandBase {
public:
	LiftWithButton(bool forwardOrReverse);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	bool ForR;
};

#endif  // LiftWithButton_H
