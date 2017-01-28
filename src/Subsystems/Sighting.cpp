#include "Sighting.h"
#include "../RobotMap.h"
#include <math.h>

Sighting::Sighting() : Subsystem("ExampleSubsystem") {

}

void Sighting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}
double Sighting::FindBoardAngle() {
	const double KHyp = 8.5; // distance between middle of contours
	const int yres = 480; // y resolution of Microsoft Life Camera
	//const int xres = 720; // x resolution of Microsoft Life Camera
	const double vertAng = 33.69; //degrees
	//const double horiAng = 60.69; //degrees
	int pixelHeight1 = 0; //from contours table
	int pixelHeight2 = 0; //from contours table

	d1 = 5 * yres / (2 * pixelHeight1 * tan(vertAng)); // distance to left contour
	d2 = 5 * yres / (2 * pixelHeight2 * tan(vertAng)); // distance to right contour
	boardAng = asin((d2 - d1) / KHyp); // positive if left of target, negative if right

	return boardAng;

}
double Sighting::FindDesiredAngle() {
	return gyro->GetAngle() - Sighting::FindBoardAngle();
}
bool Sighting::LeftOrRight() {
	// true if right of target, false if left of target
	if (Sighting::FindBoardAngle() < 0.0) {
		return true;
	}
	else { return false; }
}
