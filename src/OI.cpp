
#include <Commands/DriveWithButton.h>
#include "OI.h"
#include "Commands/Rotate.h"
#include "Commands/Move.h"
#include "Commands/LED.h"
#include "Commands/LiftWithButton.h"
#include "SmartDashboard/SmartDashboard.h"

OI::OI() {
    // Process operator interface input here.
    driverJoystick.reset(new Joystick(0));

    for(int i = 1; i <= 10; i++){
    	driverBtns.push_back(new JoystickButton(driverJoystick.get(), i));
    }

    driverBtns[1]->WhenPressed(new LED(1));
    driverBtns[2]->WhenPressed(new LED(2));
    driverBtns[3]->WhenPressed(new LED(3));

    driverBtns[4]->WhenPressed(new LiftWithButton());

    // SmartDashboard Buttons
    SmartDashboard::PutData("Rotate", new Rotate(90));
    SmartDashboard::PutData("Move", new Move(3, .3));
}

std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

bool OI::getDriverButtonPressed(int btnNum)
{
	return driverBtns[btnNum-1]->Get();
}

