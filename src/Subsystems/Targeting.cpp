#include "Targeting.h"
#include "../RobotMap.h"
#include <cmath>

Targeting::Targeting() :
		Subsystem("Targeting")
{
	NetworkTable::SetClientMode();
	NetworkTable::SetIPAddress("roborio-5268-frc.local");
	NetworkTable::SetUpdateRate(.2);
	gripTable = NetworkTable::GetTable("grip");
}

void Targeting::InitDefaultCommand()
{
	//SetDefaultCommand(new CheckHotTarget());
}

bool Targeting::calculateIsHot()
{
	/*
	std::shared_ptr<ITable> contoursTable = gripTable->GetSubTable("Contours");
	std::vector<double> solidity = contoursTable->GetNumberArray("solidity", llvm::ArrayRef<double>());
	std::vector<double> area = contoursTable->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> centerX = contoursTable->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> centerY = contoursTable->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> height = contoursTable->GetNumberArray("height", llvm::ArrayRef<double>());
	std::vector<double> width = contoursTable->GetNumberArray("width", llvm::ArrayRef<double>());


	std::vector<Contour> contours;
	for(uint i = 0; i < solidity.size(); i++){
		if(solidity[i] > .4){
			continue;
		}
	}
	SmartDashboard::PutNumber("ContoursNum", contours.size());
	if(contours.size() == 0){
		return false;
	}
	Contour bestContour = contours[0];
	for(uint i = 1; i < contours.size(); i++)
	{
		if(bestContour.width < contours[i].width){
			bestContour = contours[i];
		}
	}
	// 0.66439841151 is tan(33.6), the 20 is distance in
	// feet to the goal.
	double absDistance = ((7.0/6.0 * 360.0) / ( 2 * bestContour.height * 0.66439841151));

	SmartDashboard::PutNumber("AbsDist", absDistance);

	if( pow(absDistance, 2) - pow((85.0/12.0 - 1), 2) > 255 ){ // Square of the max distance: 255 -- to be changed, height of tower: 7 1/12
		return false;										   // 1 is the height of the camera--to be changed
	}

	return true;
	*/
	return false;
}
