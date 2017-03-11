#include "GrowProgram/WaterPump.hpp"

WaterPump::WaterPump():
_waterPumpNode("water_pump", "relay")
{
	_power_state = false; // initialize to false
	_initialized = false;
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
	if (
		hour() == 2  ||
		hour() == 5  ||
		hour() == 8  ||
		hour() == 11 ||
		hour() == 18 ||
		hour() == 19 ||
		hour() == 20 ||
		hour() == 23
	) {
		setState(true);
		return;
	}
	setState(false);
}



void WaterPump::setState(bool set_on) {
	if (set_on == _power_state && _initialized) {
		// Return if water pump is already in the desired state
		// AND the water pump has been changed once.
		return;
	}

	_power_state = set_on;
	_initialized = true;
	uploadCurrentState();

	if (set_on) {
		Homie.getLogger() << F("Water pump is turning ON") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, LOW); // relay module is active low
	} else {
		Homie.getLogger() << F("Water pump is turning OFF") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, HIGH); // relay module is active low
	}
}
