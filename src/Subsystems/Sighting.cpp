#include "Sighting.h"
#include "../RobotMap.h"
#include <math.h>

Sighting::Sighting() : Subsystem("Sighting") {
	startTable();
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

	// this runs through all of the contours
	// and ensures that they are at similar heights
	// and that they are similar in area
	for (int i = 0; i < area.size(); i++) // area.size() gives the number of contours
	{
		for (int j = i + 1; j < area.size(); j++)
		{
			if (fabs(centerY[j] - centerY[i]) < Y_ERROR_MARGIN && //Check if within margin of error
					(area[j] - area[i]) / area[j] < AREA_ERROR_MARGIN)
			{
				if (centerX[j] > centerX[i]) { // Find the left contour
					pixelHeight1 = height[i];
					pixelHeight2 = height[j];
				} else {
					pixelHeight2 = height[i];
					pixelHeight1 = height[j];
				}
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}

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
double Sighting::DistanceToTarget() {
	int pixelHeight = 0; // get from countours report
	return 5 * 480 / (2 * pixelHeight * tan(33.69));
}
void Sighting::startTable()
{
	this->networktable = NetworkTable::GetTable("ChangeThisLater");

	solidity = networktable->GetNumberArray("solidity", llvm::ArrayRef<double>());
	area = networktable->GetNumberArray("area", llvm::ArrayRef<double>());
	centerX = networktable->GetNumberArray("centerX", llvm::ArrayRef<double>());
	centerY = networktable->GetNumberArray("centerY", llvm::ArrayRef<double>());
	height = networktable->GetNumberArray("height", llvm::ArrayRef<double>());
	width = networktable->GetNumberArray("width", llvm::ArrayRef<double>());
}

bool Sighting::TwoTargetsAvailable() {
	return solidity.size() >= 2; // returns true if there are at least 2 contours
}
