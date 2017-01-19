
#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "CommandBase.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/Autonomous.h"

class Robot : public IterativeRobot {
public:
	static std::unique_ptr<Autonomous> autonomousCommand;
	std::shared_ptr<frc::SendableChooser<int*> > autonomousChooser;
	LiveWindow *lw = LiveWindow::GetInstance();

	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	virtual void TestInit();
};
#endif
