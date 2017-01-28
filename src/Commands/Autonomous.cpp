
#include "Autonomous.h"
#include "Commands/Move.h"
#include "Commands/Rotate.h"
#include "Commands/RadialDrive.h"
#include "Robot.h"

Autonomous::Autonomous(int selection) : CommandGroup("Autonomous") {
	switch(selection){
	case 1: //right
		//forward, turn right, aim, forward
		AddSequential(MecanumDrive_Cartesian(0.0, 1.0, 0.0))
		AddSequential(new RadialDrive(0.0));
		break;
	case 2: //center
		break;
	case 3: //left
		break;
	default:
		break;
	}
}
