#include "UDPReceiver.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

// Constructor
UDPReceiver::UDPReceiver() : Subsystem("UDPReceiver")
	// Initializer list
	, mCounter(0)
	, mRun(true)
	, mThread(&UDPReceiver::ThreadBody, this)
{
}

void UDPReceiver::InitDefaultCommand() {
	// Set the default command for a subsystem here.
}

// Destructor (virtual is not a return type)
UDPReceiver::~UDPReceiver() {
	StopThread(); // Tells thread to stop

	// Wait for it to stop
	if (mThread.joinable()) {
		mThread.join();
	}
}

uint32_t UDPReceiver::GetCount() const {
	return mCounter;
}

void UDPReceiver::StopThread() {
	mRun = false;
}

void UDPReceiver::ThreadBody() {
	while (mRun == true) {
		mCounter++; // Test thread
		// Put real thread code here
	}
}

void UDPReceiver::AddSmartDashboardItems() {
	SmartDashboard::PutNumber("Thread Counter", GetCount());
}
