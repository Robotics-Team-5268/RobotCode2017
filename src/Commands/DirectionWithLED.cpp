#include <Commands/DirectionWithLED.h>

DirectionWithLED::DirectionWithLED() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(leds.get());
	Requires(sighting.get());

}

// Called just before this Command runs the first time
void DirectionWithLED::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DirectionWithLED::Execute() {
	SmartDashboard::PutNumber("Board Angle", sighting->findBoardAngle());
	if(sighting->findBoardAngle() > 5.0) {
		leds->TurnOff(LED_BLUE);
		leds->TurnOff(LED_GREEN);
		leds->TurnOn(LED_RED);

	}
	else if(sighting->findBoardAngle() < -5.0) {
		leds->TurnOff(LED_RED);
		leds->TurnOff(LED_GREEN);
		leds->TurnOn(LED_BLUE);
	}
	else if(sighting->TwoTargetsAvailable()) {
		leds->TurnOff(LED_RED);
		leds->TurnOn(LED_GREEN);
		leds->TurnOff(LED_BLUE);
	}
	else { // No target found
		leds->TurnOff(LED_RED);
		leds->TurnOff(LED_GREEN);
		leds->TurnOff(LED_BLUE);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DirectionWithLED::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DirectionWithLED::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DirectionWithLED::Interrupted() {
	End();
}
