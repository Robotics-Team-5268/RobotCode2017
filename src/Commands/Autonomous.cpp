
#include "Autonomous.h"
#include "Commands/Move.h"
#include "Commands/Rotate.h"

Autonomous::Autonomous(int selection) : CommandGroup("Autonomous") {
	// [AJN] I believe this is necessary to let the WPI code know that
	// each Subsystem you are going to use is needed by the command so
	// that it can ensure an instance is constructed.
	// Requires(Robot::drive.get());

	switch(selection){
	case 1: //
		break;
	case 2: //
		break;
	case 3: //
		break;
	default:
		break;
	}

}
