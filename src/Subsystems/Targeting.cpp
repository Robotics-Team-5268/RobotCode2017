#include "Targeting.h"
#include "../RobotMap.h"
#include <cmath>
#include "../Commands/CheckHotTarget.h"

Targeting::Targeting() :
		Subsystem("Targeting")
{
	NetworkTable::SetClientMode();
	NetworkTable::SetIPAddress("roborio-5268-frc.local");
	NetworkTable::SetUpdateRate(0.2);
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

	std::shared_ptr<ITable> linesTable = gripTable->GetSubTable("Lines");
	std::vector<double> angle = linesTable->GetNumberArray("angle", llvm::ArrayRef<double>());
	std::vector<double> length = linesTable->GetNumberArray("length", llvm::ArrayRef<double>());
	std::vector<double> x1 = linesTable->GetNumberArray("x1", llvm::ArrayRef<double>());
	std::vector<double> x2 = linesTable->GetNumberArray("x2", llvm::ArrayRef<double>());
	std::vector<double> y1 = linesTable->GetNumberArray("y1", llvm::ArrayRef<double>());
	std::vector<double> y2 = linesTable->GetNumberArray("y2", llvm::ArrayRef<double>());

	std::vector<Line> allLines;

	for(uint i = 0; i < angle.size(); i++){
		Line l;
		l.angle = angle[i];
		l.length = length[i];
		l.x1 = x1[i];
		l.x2 = x2[i];
		l.y1 = y1[i];
		l.y2 = y2[i];
		l.midX = (x1[i] + x2[i]) / 2;
		l.midY = (y1[i] + y2[i]) / 2;
		if(fabs(l.angle) < 45.0 || fabs(l.angle) > 135.0){
			l.isVert = false;
		}else{
			l.isVert = true;
		}
		allLines.push_back(l);
	}

	std::vector<Contour> contours;
	for(uint i = 0; i < solidity.size(); i++){
		if(solidity[i] > .4){
			continue;
		}

		std::vector<Line> lines;
		for(uint a = 0; a < angle.size(); a++){
			double dist = (allLines[a].midX - centerX[i]) * (allLines[a].midX - centerX[i]) + (allLines[a].midY - centerY[i]) * (allLines[a].midY - centerY[i]);
			if(dist <= (area[i] / 5)*(area[i] / 5)){ // should be changed later
				lines.push_back(allLines[a]);
			}
		}
		if(lines.size() > 0){
			Contour c;
			c.solidity = solidity[i];
			c.area = area[i];
			c.centerX = centerX[i];
			c.centerY = centerY[i];
			c.height = height[i];
			c.width = width[i];
			c.lines = lines;
			contours.push_back(c);
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
