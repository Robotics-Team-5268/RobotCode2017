#include "Sighting.h"
#include "../RobotMap.h"

Sighting::Sighting() : Subsystem("ExampleSubsystem") {

}

void Sighting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}
double Sighting::FindDesiredHeading() {
	const double KHyp = 8.5;
	double d1 = 0.0;
	double d2 = 0.0;
	const int yres = 480;
	const int xres = 720;
	const double vertAng = 33.69; //degrees
	const double horiAng = 60.69; //degrees
	double boardAng = 0.0;
	int pixelHeight1 = 0; //from contours table
	int pixelHeight2 = 0; //from contours table
	d1 = 5 * yres / (2 * pixelHeight1 * tan(vertAng));
	d2 = 5 * yres / (2 * pixelHeight2 * tan(vertAng));
	boardAng = (d2 - d1) / KHyp;
	return gyro->GetAngle() - boardAng;

}
// Put methods for controlling this subsystem
// here. Call these from Commands.
