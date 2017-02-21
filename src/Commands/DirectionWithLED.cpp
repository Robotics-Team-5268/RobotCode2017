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
	if(sighting->findBoardAngle() > 5.0)
		{
			leds->TurnOff(LED_RED);
			leds->TurnOff(LED_GREEN);
			leds->TurnOn(LED_BLUE);
			SmartDashboard::PutNumber("Greater than 5", 1);
			SmartDashboard::PutNumber("Less than -5", 0);
			SmartDashboard::PutNumber("Right on, dude!", 0);
			SmartDashboard::PutNumber("I got nothing, man", 0);

		}
		else if(sighting->findBoardAngle() < -5.0)
		{
			leds->TurnOff(LED_BLUE);
			leds->TurnOff(LED_GREEN);
			leds->TurnOn(LED_RED);
			SmartDashboard::PutNumber("Greater than 5", 0);
			SmartDashboard::PutNumber("Less than -5", 1);
			SmartDashboard::PutNumber("Right on, dude!", 0);
			SmartDashboard::PutNumber("I got nothing, man", 0);
		}
		else if(sighting->TwoTargetsAvailable())
		{
			leds->TurnOff(LED_BLUE);
			leds->TurnOn(LED_GREEN);
			leds->TurnOff(LED_RED);
			SmartDashboard::PutNumber("Greater than 5", 0);
			SmartDashboard::PutNumber("Less than -5", 0);
			SmartDashboard::PutNumber("Right on, dude!", 1);
			SmartDashboard::PutNumber("I got nothing, man", 0);
		}
		else
		{
			leds->TurnOff(LED_BLUE);
			leds->TurnOff(LED_GREEN);
			leds->TurnOff(LED_RED);
			SmartDashboard::PutNumber("I got nothing, man", 1);
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
