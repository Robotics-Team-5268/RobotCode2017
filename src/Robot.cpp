#include "Robot.h"

std::unique_ptr<Autonomous> Robot::autonomousCommand;

void Robot::RobotInit() {
	//start grip
	system("/home/lvuser/grip &");

	RobotMap::init();
	CommandBase::init();

	CommandBase::drive->safetyOff();

	//instantiate the command used for the autonomous period
	//autonomousCommand.reset(new Autonomous());

	autonomousChooser.reset(new SendableChooser<int*>());
	autonomousChooser->AddDefault("Right", new int(1));
	autonomousChooser->AddObject("Center", new int(2));
	autonomousChooser->AddObject("Left", new int(3));
	SmartDashboard::PutData("Autonomous", autonomousChooser.get());

		// We need to run our vision program in a separate Thread.
		// If not, our robot program will not run
		std::thread visionThread(VisionThread);
		visionThread.detach();

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
	//autonomousCommand.Start();
	RobotMap::driveGyro->Reset();
	int* selection = (int*) autonomousChooser->GetSelected();
	autonomousCommand.reset(new Autonomous(*selection));
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
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
	CommandBase::drive->AddSmartDashboardItems();
}

void Robot::TestPeriodic() {
	lw->Run();
}
void Robot::TestInit(){

}
START_ROBOT_CLASS(Robot);
