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
	autonomousChooser->AddDefault("Drive forward", new int(1));
	autonomousChooser->AddObject("Drive and shoot (lowbar)", new int(2));
	autonomousChooser->AddObject("Drive forward short", new int(3));
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
void Robot::VisionThread()
{
	// Get the USB camera from CameraServer
	cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
	// Set the resolution
	camera.SetResolution(CAMERA_XRES, CAMERA_YRES);

	// Get a CvSink. This will capture Mats from the Camera
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	// Setup a CvSource. This will send images back to the Dashboard
	cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo("Rectangle", CAMERA_XRES, CAMERA_YRES);

	// Mats are very memory expensive. Lets reuse this Mat.
	cv::Mat mat;

	while (true) {
		// Tell the CvSink to grab a frame from the camera and put it
		// in the source mat.  If there is an error notify the output.
		if (cvSink.GrabFrame(mat) == 0) {
			// Send the output the error.
			outputStream.NotifyError(cvSink.GetError());
			// skip the rest of the current iteration
			continue;
		}
		// Put a rectangle on the image
		rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
				cv::Scalar(255, 255, 255), 5);
		// Give the output stream a new image to display
		outputStream.PutFrame(mat);
	}
}
START_ROBOT_CLASS(Robot);
