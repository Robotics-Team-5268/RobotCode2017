#include "Sighting.h"
#include "../RobotMap.h"
#include <math.h>

Sighting::Sighting() : Subsystem("Sighting"), gyro( nullptr ) {
	//readTable();
}

void Sighting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}
double Sighting::findBoardAngle() {
	//readTable(); // REMOVE THIS LATER ***************************************************************
	const double KHyp = 8.5; // distance between middle of contours
	const int yres = 480; // y resolution of Microsoft Life Camera
	//const int xres = 720; // x resolution of Microsoft Life Camera
	const double vertAng = 0.58800142; // 33.69 degrees
	//const double horiAng = 60.69; //degrees

	int pixelHeight1 = 0; //from contours table
	int pixelHeight2 = 0; //from contours table

	int topCutContour = 0;
	int bottomCutContour = 0;


	// checks if there is a set of broken contours from the peg
	// by seeing if their X values are close to each other

	for (uint i = 0; i < area.size(); i++) // area.size() gives the number of contours
		{
		frc::SmartDashboard::PutNumber("i", i);
			for (uint j = i + 1; j < area.size(); j++)
			{
				frc::SmartDashboard::PutNumber("j", j);
				if (fabs(centerX[j] - centerX[i]) < X_ERROR_MARGIN) //Check if within margin of error
				{
					frc::SmartDashboard::PutNumber("1", 1);
					if (centerY[j] > centerY[i]) { // Find the top contour
						frc::SmartDashboard::PutNumber("2", 2);
						topCutContour = j;
						bottomCutContour = i;
					} else {
						frc::SmartDashboard::PutNumber("3", 3);
						bottomCutContour = j;
						topCutContour = i;
					}
					i = area.size(); // jump to end of loop
					j = area.size();
				}
			}
		}

	// this runs through all of the contours
	// and ensures that they are at similar heights
	// and that they are similar in area

	for (uint i = 0; i < area.size(); i++) // area.size() gives the number of contours
	{
		frc::SmartDashboard::PutNumber("i2", i);
		for (uint j = i + 1; j < area.size(); j++)
		{
			frc::SmartDashboard::PutNumber("j2", j);
			if (fabs(centerY[j] - centerY[i]) < Y_ERROR_MARGIN && //Check if within margin of error
					(area[j] - area[i]) / area[j] < AREA_ERROR_MARGIN)
			{
				frc::SmartDashboard::PutNumber("4", 4);
				if (centerX[j] > centerX[i]) { // Find the left contour
					frc::SmartDashboard::PutNumber("5", 5);
					pixelHeight1 = height[i];
					pixelHeight2 = height[j];
				} else {
					frc::SmartDashboard::PutNumber("6", 6);
					pixelHeight2 = height[i];
					pixelHeight1 = height[j];
				}
				frc::SmartDashboard::PutNumber("Countours Fit", 1);
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}
	frc::SmartDashboard::PutNumber("Pixel Height 1", pixelHeight1);
	frc::SmartDashboard::PutNumber("Pixel Height 2", pixelHeight2);

	d1 = 5 * yres / (2 * pixelHeight1 * tan(vertAng)); // distance to left contour
	frc::SmartDashboard::PutNumber("Distance 1", d1);
	d2 = 5 * yres / (2 * pixelHeight2 * tan(vertAng)); // distance to right contour
	frc::SmartDashboard::PutNumber("Distance 2", d2);
	boardAng = (asin((d2 - d1) / KHyp)/ 3.14159265) * 180; // positive if left of target, negative if right
	frc::SmartDashboard::PutNumber("Board Angle", boardAng);

	return boardAng;

}
double Sighting::FindDesiredAngle() {
	return gyro->GetAngle() - Sighting::findBoardAngle();
}
bool Sighting::LeftOrRight() {
	// true if right of target, false if left of target
	if (Sighting::findBoardAngle() < 0.0) {
		return true;
	}
	else { return false; }
}

double Sighting::DistanceToTarget() {
	int pixelHeight = 0; // get from countours report
	return 5 * 480 / (2 * pixelHeight * tan(33.69));
}

//Update networktable and fill ContoursReport vectors
void Sighting::readTable()
{
	this->networktable = NetworkTable::GetTable("roboRIO-5268-frc.local");

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
double Sighting::getCenterX() {
	if (TwoTargetsAvailable()){
		return (centerX[0] + centerX[1]) / 2;
	}
	else {
		return 0.0;
	}
}
