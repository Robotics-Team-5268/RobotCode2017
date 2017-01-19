#ifndef LEDController_H
#define LEDController_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class LEDController: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<Relay> ledRelay1;
	std::shared_ptr<Relay> ledRelay2;
	std::shared_ptr<Relay> ledRelay3;
	std::shared_ptr<Relay> ledRelay4;
public:
	LEDController();
	void InitDefaultCommand();
	void TurnOn(int num);
	void TurnOff(int num);
	bool IsOn(int num);
};

#endif
