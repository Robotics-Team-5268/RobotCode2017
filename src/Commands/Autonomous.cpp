
#include "Autonomous.h"
#include "Commands/Move.h"
#include "Commands/Rotate.h"
#include "Commands/RadialDrive.h"
#include "Robot.h"

Autonomous::Autonomous(int selection) : CommandGroup("Autonomous") {
	switch(selection){
	case 1: //
		// inside the command, retrieve the values from the subsystem instead
		// of passing them here.
		AddSequential(new RadialDrive(0.0));
		break;
	case 2: //
		break;
	case 3: //
		break;
	default:
		break;
	}
}
