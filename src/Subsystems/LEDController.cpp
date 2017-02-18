#include "LEDController.h"
#include "../RobotMap.h"

LEDController::LEDController() : Subsystem("LEDController")
{
	for(int i = 0; i < 3; i++) {
		ledRelay[i] = RobotMap::ledRelay[i];
	}
}

void LEDController::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void LEDController::TurnOff(int num)
{
	led_state[num] = false;
	SetRelays();
}

void LEDController::TurnOn(int num)
{
	led_state[num] = true;
	SetRelays();
}
bool LEDController::IsOn(int num)
{
	return led_state[num];
}

void LEDController::SetRelays()
{
	int m_plus_led;
	int m_minus_led;
	bool m_plus;
	bool m_minus;

	for(int i = 0; i < 3; i++) {
		m_minus_led = i * 2;
		m_plus_led = m_minus_led + 1;
		m_minus = led_state[m_minus_led];
		m_plus  = led_state[m_plus_led];

		// invert all LED output states since the wiring is a common anode (positive) voltage
		if( m_plus_led == LED_RED || m_plus_led == LED_BLUE || m_plus_led == LED_GREEN )
			m_plus = !m_plus;
		if( m_minus_led == LED_RED || m_minus_led == LED_BLUE || m_minus_led == LED_GREEN )
			m_minus = !m_minus;

		if(m_minus == true && m_plus == true)
			ledRelay[i]->Set(frc::Relay::kOn);
		else if(m_minus == false && m_plus == false)
			ledRelay[i]->Set(frc::Relay::kOff);
		else if(m_minus == true && m_plus == false)
			ledRelay[i]->Set(frc::Relay::kReverse);
		else if(m_minus == false && m_plus == true)
			ledRelay[i]->Set(frc::Relay::kForward);
	}
}
