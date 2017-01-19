
#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	std::shared_ptr<Joystick> driverJoystick, shooterJoystick;
	std::vector<JoystickButton*> driverBtns, shooterBtns;
public:
	OI();

	std::shared_ptr<Joystick> getDriverJoystick();
	std::shared_ptr<Joystick> getShooterJoystick();
	bool getDriverButtonPressed(int btnNum);
	bool getShooterButtonPressed(int btnNum);

};

#endif
