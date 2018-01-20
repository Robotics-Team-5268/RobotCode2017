#ifndef SRC_SUBSYSTEMS_UDPRECEIVER_H_
#define SRC_SUBSYSTEMS_UDPRECEIVER_H_

#include "Commands/Subsystem.h"
#include "WPIlib.h"

#include <atomic>
#include <cstdint>
#include <thread>

class UDPReceiver : public Subsystem {

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	void ThreadBody();

	// The order of these is important
	// So the thread doesn't start before everything's ready
	std::atomic_int mCounter;
	std::atomic_bool mRun;
	std::thread mThread;

public:
	UDPReceiver();
	~UDPReceiver();
	void InitDefaultCommand();
	uint32_t GetCount() const;
	void StopThread();
	void AddSmartDashboardItems();

};

#endif /* SRC_SUBSYSTEMS_UDPRECEIVER_H_ */
