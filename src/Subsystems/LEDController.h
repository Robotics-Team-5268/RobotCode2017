#ifndef LEDController_H
#define LEDController_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class LEDController: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<Relay> ledRelay[3];
	bool led_state[6] = {false, false, false, false, false, false};
	void SetRelays();
public:
	LEDController();
	void InitDefaultCommand();
	void TurnOn(int num);
	void TurnOff(int num);
	bool IsOn(int num);
};

#endif
