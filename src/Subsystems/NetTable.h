#ifndef NetTable_H
#define NetTable_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

class NetTable : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	NetTable();
	void InitDefaultCommand();
};

#endif  // NetTable_H
