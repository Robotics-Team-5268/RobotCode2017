#include "CommandBase.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
std::unique_ptr<OI> CommandBase::oi;
std::unique_ptr<Drive> CommandBase::drive;
std::unique_ptr<LEDController> CommandBase::leds;
std::unique_ptr<Lift> CommandBase::lift;
std::unique_ptr<Sighting> CommandBase::sighting;


CommandBase::CommandBase(const std::string &name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	drive.reset(new Drive());
	leds.reset(new LEDController());
	lift.reset(new Lift());
	sighting.reset(new Sighting());
	// Keep at the end
	oi.reset(new OI());
}
