#include "Robot.h"
#include "Commands/LiftWithButton.h"

std::unique_ptr<Autonomous> Robot::autonomousCommand;

void Robot::RobotInit() {
	RobotMap::init();
	CommandBase::init();

	CommandBase::drive->safetyOff();

	autonomousChooser.reset(new SendableChooser<int*>());
	autonomousChooser->AddDefault("Right", new int(1));
	autonomousChooser->AddObject("Center", new int(2));
	autonomousChooser->AddObject("Left", new int(3));
	SmartDashboard::PutData("Autonomous", autonomousChooser.get());
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	RobotMap::driveGyro->Reset();
	int* selection = autonomousChooser->GetSelected();
	autonomousCommand.reset(new Autonomous(2));// replace with selection
	autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
	CommandBase::drive->AddSmartDashboardItems();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if(autonomousCommand.get() != nullptr)
	{
		autonomousCommand->Cancel();
	}
	CommandBase::drive->getGyro()->Reset();
	CommandBase::oi->setLiftDirection(1);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	CommandBase::drive->AddSmartDashboardItems();
	//CommandBase::sighting->findBoardAngle();
}

void Robot::TestPeriodic() {
	Scheduler::GetInstance()->Run();
	CommandBase::drive->AddSmartDashboardItems();
}
void Robot::TestInit(){
	CommandBase::oi->setLiftDirection(0);
}
START_ROBOT_CLASS(Robot);
