
#include "Autonomous.h"
#include "Commands/Move.h"
#include "Commands/Rotate.h"
#include "Commands/RadialDrive.h"
#include "Robot.h"
#include "LED.h"

// Temporary, for delay
#include <thread>
#include <chrono>

Autonomous::Autonomous(int selection) : CommandGroup("Autonomous") {

	// 2 second delay so vision is ready to go
	//std::this_thread::sleep_for(std::chrono::seconds(2));

	//double angle = CommandBase::sighting->findFacingAngle();

	//SmartDashboard::PutNumber("Testing turn", 45);
	double angle = SmartDashboard::GetNumber("Testing turn", 45);

	switch(selection){
	case 1: //right
		//forward, turn right, aim, forward
		AddSequential(new Move(0.5, 1.0));
		AddSequential(new Rotate(-45));
		AddSequential(new RadialDrive());
		AddSequential(new Move(0.5, 1.0));
		break;
	case 2: //center
		//Move forward
		//AddSequential(new Move(0.5, 0.5));
		AddSequential(new LED(1));
		AddSequential(new RadialDrive());
		break;
	case 3: //left
		//forward, turn left, aim, forward
		AddSequential(new Move(0.5, 1.0));
		AddSequential(new Rotate(45));
		AddSequential(new RadialDrive());
		AddSequential(new Move(0.5, 1.0));
		break;
	case 4: // Testing
		AddSequential(new Rotate(angle));
		break;
	default:
		break;
	}
}
