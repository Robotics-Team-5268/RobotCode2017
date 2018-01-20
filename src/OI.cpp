
#include <Commands/DriveWithButton.h>
#include "OI.h"
#include "Commands/Rotate.h"
#include "Commands/RadialDrive.h"
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

    driverBtns[1]->WhenPressed(new LED(LED_CAMERA));
    driverBtns[2]->WhenPressed(new LED(LED_MASTER));
    driverBtns[3]->WhenPressed(new LED(LED_BLUE));

    // SmartDashboard Buttons - don't seem to work
    SmartDashboard::PutData("Rotate", new Rotate(90));
    SmartDashboard::PutData("Move", new Move(3, .3));
    SmartDashboard::PutData("Cam Light", new LED(LED_CAMERA));
    SmartDashboard::PutData("Blue", new LED(LED_BLUE));
    SmartDashboard::PutData("All LED", new LED(LED_MASTER));
    SmartDashboard::PutData("Green", new LED(LED_GREEN));
    SmartDashboard::PutData("Red", new LED(LED_RED));
    //SmartDashboard::PutData("Radial Drive", new RadialDrive());
}


std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

bool OI::getDriverButtonPressed(int btnNum)
{
	return driverBtns[btnNum-1]->Get();
}

void OI::setLiftDirection(bool ForR)
{
	OI::driverBtns[4]->WhenPressed(new LiftWithButton(ForR));
}

