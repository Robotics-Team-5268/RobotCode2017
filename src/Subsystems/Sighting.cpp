#include "../Commands/DirectionWithLED.h"
#include "Sighting.h"
#include "../RobotMap.h"
#include <math.h>

const double OFFSET_TO_FRONT = 7.0;
const double DISTANCE_CONSTANT = 5561.0;
const double KHyp = 8.5; // distance between middle of contours
//const int yres = 480; // y resolution of Microsoft Life Camera
const int xres = 640; // x resolution of Microsoft Life Camera
//const double vertAng = 0.58800142; // 33.69 degrees
const double horiAng = 0.36397895; //20.85 degrees


Sighting::Sighting() : Subsystem("Sighting"), gyro( nullptr ) {
	//readTable();
}

void Sighting::InitDefaultCommand() {
	// Set the default command for a subsystem here.
}

/*
 * Handles split contours and contours that
 * are unreasonably different in size
 */
void Sighting::cleanContours() {
	//if (area.size() < 1) return 0; // No contours

	// This for loop checks
	// if there is a set of broken contours from the peg
	// by seeing if their X values are close to each other
	// Commented out because it doesn't do anything because
	// output is never used. It should merge the contours.

	/*
	int topCutContour = 0;
	int bottomCutContour = 0;

	for (uint i = 0; i < area.size(); i++) { // area.size() gives the number of contours
		for (uint j = i + 1; j < area.size(); j++) {
			// Check if within margin of error (meaning the contour are too close together)
			// This should mean the spring is splitting a contour into two on top of each other
			if (fabs(centerX[j] - centerX[i]) < X_ERROR_MARGIN) {
				if (centerY[j] > centerY[i]) { // Find the top contour
					topCutContour = j;
					bottomCutContour = i;
				} else {
					bottomCutContour = j;
					topCutContour = i;
				}
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}*/


	// This for loop runs through all of the contours and ensures that they
	// are at similar heights and that they are similar in area

	pixelWidth1 = 0;
	pixelWidth2 = 0;

	for (uint i = 0; i < area.size(); i++) { // area.size() gives the number of contours
		for (uint j = i + 1; j < area.size(); j++) {
			if (fabs(centerY[j] - centerY[i]) < Y_ERROR_MARGIN && //Check if within margin of error
					(area[j] - area[i]) / area[j] < AREA_ERROR_MARGIN) {
				if (centerX[j] > centerX[i]) { // Find the left contour
					pixelWidth1 = width[i];
					pixelWidth2 = width[j];
				} else {
					pixelWidth2 = width[i];
					pixelWidth1 = width[j];
				}
				frc::SmartDashboard::PutNumber("Countours Fit", 1);
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}

	frc::SmartDashboard::PutNumber("Pixel Width 1", pixelWidth1);
	frc::SmartDashboard::PutNumber("Pixel Width 2", pixelWidth2);
}

double Sighting::findSightingAngle() {

	int pixelWidth1 = 0; //from contours table
	int pixelWidth2 = 0; //from contours table

	int topCutContour = 0;
	int bottomCutContour = 0;

	frc::SmartDashboard::PutNumber("Total Contours", area.size());

	if (area.size() < 1) return 0; // No contours

	// This for loop
	// checks if there is a set of broken contours from the peg
	// by seeing if their X values are close to each other
	// Commented out because it doesn't do anything because
	// output is never used. It should merge the contours.

	/*for (uint i = 0; i < area.size(); i++) { // area.size() gives the number of contours
		for (uint j = i + 1; j < area.size(); j++) {
			// Check if within margin of error (meaning the contour are too close together)
			// This should mean the spring is splitting a contour into two on top of each other
			if (fabs(centerX[j] - centerX[i]) < X_ERROR_MARGIN) {
				if (centerY[j] > centerY[i]) { // Find the top contour
					topCutContour = j;
					bottomCutContour = i;
				} else {
					bottomCutContour = j;
					topCutContour = i;
				}
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}*/


	// This for loop runs through all of the contours and ensures that they
	// are at similar heights and that they are similar in area

	for (uint i = 0; i < area.size(); i++) { // area.size() gives the number of contours
		for (uint j = i + 1; j < area.size(); j++) {
			if (fabs(centerY[j] - centerY[i]) < Y_ERROR_MARGIN && //Check if within margin of error
					(area[j] - area[i]) / area[j] < AREA_ERROR_MARGIN) {
				if (centerX[j] > centerX[i]) { // Find the left contour
					pixelWidth1 = width[i];
					pixelWidth2 = width[j];
				} else {
					pixelWidth2 = width[i];
					pixelWidth1 = width[j];
	 			}
				frc::SmartDashboard::PutNumber("Countours Fit", 1);
				i = area.size(); // jump to end of loop
				j = area.size();
			}
		}
	}

	frc::SmartDashboard::PutNumber("Pixel Width 1", pixelWidth1);
	frc::SmartDashboard::PutNumber("Pixel Width 2", pixelWidth2);

	frc::SmartDashboard::PutNumber("First centerX NT", centerX[0]);

	// KHyp is 8.5in (the distance from center to center of contours)
	// Divide by the length between centers in pixels to get inches per pixel
	const double inPerPx = KHyp / abs(centerX[0] - centerX[1]);
	double angleToGoal = 0;
	// this calculates the distance from the center of goal to center of webcam
	double distanceFromCenterPixels = ((centerX[0] + centerX[1]) / 2) - (CAMERA_XRES / 2);
	// Converts pixels to inches using the constant from above.
	double distanceFromCenterInch = distanceFromCenterPixels * inPerPx;
	// math brought to you buy Chris and Jones
	angleToGoal = atan(distanceFromCenterInch / distanceFromTarget());
	angleToGoal = (angleToGoal / 3.14159265) * 180;
	frc::SmartDashboard::PutNumber("Angle To Goal", angleToGoal);
	return angleToGoal;
}

/*
 * Finds the angle the robot is positioned relative to the target on
 * the ground. If the robot is directly in front of the target,
 * such that both contours are the same size, it will be zero.
 * NOTE: Does not work yet
 */
double Sighting::findPositionAngle() {
	cleanContours();

	if (pixelWidth1 != 0 && pixelWidth2 != 0) {
		d1 = 2 * xres / (2 * pixelWidth1 * tan(horiAng)); // distance to left contour
		frc::SmartDashboard::PutNumber("Distance 1", d1);
		d2 = 2 * xres / (2 * pixelWidth2 * tan(horiAng)); // distance to right contour
		frc::SmartDashboard::PutNumber("Distance 2", d2);
		boardAng = (asin((d2 - d1) / KHyp)/ 3.14159265) * 180; // positive if left of target, negative if right
		frc::SmartDashboard::PutNumber("Board Angle", boardAng);
		return boardAng;
	}
	else return 0;
}

bool Sighting::LeftOrRight() {
	// true if right of target, false if left of target
	return (Sighting::findSightingAngle() < 0.0);
}

double Sighting::distanceFromTarget(){
		// distance costant divided by length between centers of contours
		double lengthBetweenContours = (centerX[0] - centerX[1]) / 2;
		return (DISTANCE_CONSTANT / lengthBetweenContours) - OFFSET_TO_FRONT;
	}

//Update networktable and fill ContoursReport vectors
void Sighting::readTable()
{
	/*this->networktable = NetworkTable::GetTable("roboRIO-5268-frc.local");

	area = networktable->GetNumberArray("area", llvm::ArrayRef<double>());
	centerX = networktable->GetNumberArray("centerX", llvm::ArrayRef<double>());
	centerY = networktable->GetNumberArray("centerY", llvm::ArrayRef<double>());
	height = networktable->GetNumberArray("height", llvm::ArrayRef<double>());
	width = networktable->GetNumberArray("width", llvm::ArrayRef<double>());*/

	CommandBase::udp->GetContours(centerX, centerY, width, height, area);

	if (TwoTargetsAvailable()) {
		frc::SmartDashboard::PutNumber("distance between contours", centerX[0] - centerX[1]);
	}
}

bool Sighting::TwoTargetsAvailable() {
	return area.size() >= 2; // returns true if there are at least 2 contours
}
double Sighting::getCenterX() {
	if (TwoTargetsAvailable()){
		return (centerX[0] + centerX[1]) / 2;
	}
	else {
		return 0.0;
	}
}
