
#include "Autonomous.h"
#include "Commands/Move.h"
#include "Commands/Rotate.h"
#include "Commands/RadialDrive.h"
#include "Robot.h"

Autonomous::Autonomous(int selection) : CommandGroup("Autonomous") {
	switch(selection){
	case 1: //right
		//forward, turn right, aim, forward
		AddSequential(new Move(0.5, 1.0));
		AddSequential(new Rotate(-90));
		AddSequential(new RadialDrive(0.0));
		AddSequential(new Move(0.5, 1.0));
		break;
	case 2: //center
		//Move forward
		AddSequential(new Move(0.5, 0.5));
		break;
	case 3: //left
		//forward, turn left, aim, forward
		AddSequential(new Move(0.5, 1.0));
		AddSequential(new Rotate(45));
		AddSequential(new RadialDrive(0.0));
		AddSequential(new Move(0.5, 1.0));
		break;
	default:
		break;
	}
}
