#include "GrowProgram/WaterPump.hpp"

WaterPump::WaterPump():
_waterPumpNode("water_pump", "relay")
{
	_power_state = false; // initialize to false
	_power_state_changed_at = 0;
}


void WaterPump::setup() {
	_waterPumpNode.advertise("on");
	setState(true);
}

void WaterPump::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (_power_state) {
		_waterPumpNode.setProperty("on").setRetained(false).send("true");
	} else {
		_waterPumpNode.setProperty("on").setRetained(false).send("false");
	}
}

void WaterPump::loop() {
	if (_power_state) {
		// Turn the pump off if it has been on for more than WATER_PUMP_ON_DURATION_MS
		if (millis() - _power_state_changed_at > WATER_PUMP_ON_DURATION_MS) {
			setState(false);
		}
	} else {
		// Turn the pump on if it has been off for more than WATER_PUMP_OFF_DURATION_MS
		if (millis() - _power_state_changed_at > WATER_PUMP_OFF_DURATION_MS) {
			setState(true);
		}
	}
}



void WaterPump::setState(bool set_on) {
	if (set_on == _power_state && _power_state_changed_at) {
		// Return if water pump is already in the desired state
		// AND the water pump has been changed once.
		return;
	}

	_power_state = set_on;
	_power_state_changed_at = millis();
	uploadCurrentState();

	if (set_on) {
		Homie.getLogger() << F("Water pump is turning ON") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, LOW); // relay module is active low
	} else {
		Homie.getLogger() << F("Water pump is turning OFF") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, HIGH); // relay module is active low
	}
}
