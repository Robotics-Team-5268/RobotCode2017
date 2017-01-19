#ifndef Targeting_H
#define Targeting_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Targeting: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<NetworkTable> gripTable;
public:
	Targeting();
	void InitDefaultCommand();
	bool calculateIsHot();
	struct Line
	{
		double angle, length, x1, y1, x2, y2, midX, midY;
		bool isVert;
	};
	struct Contour
	{
		double solidity, area, centerX, centerY, height, width, hotness;
		std::vector<Line> lines;
	};
};

#endif
