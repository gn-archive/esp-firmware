#include "GrowProgram/WaterPump.hpp"

WaterPump::WaterPump():
_waterPumpNode("water_pump", "relay"),
_waterPumpOverrideNode("water_pump_override", "virtual sw")
{
	_power_state = false; // initialize to false
	_overrideEnabled = false;
}

void WaterPump::setup() {
	_waterPumpNode.advertise("on");


	_waterPumpOverrideNode.advertise("enabled").settable([&](const HomieRange& range, const String& value) {
			if (value != "true" && value != "false") return false;
			_overrideEnabled = value == "true";
			uploadCurrentState();
			return true;
		});

	setState(true);
}

void WaterPump::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (_power_state) {
		_waterPumpNode.setProperty("on").send("true");
	} else {
		_waterPumpNode.setProperty("on").send("false");
	}

	if (_overrideEnabled) {
		_waterPumpOverrideNode.setProperty("enabled").send("true");
	} else {
		_waterPumpOverrideNode.setProperty("enabled").send("false");
	}
}

void WaterPump::loop() {
	if (_overrideEnabled) {
		setState(true);
		return;
	}

	// if ( (hour() == 0  || hour() == 6  || hour() == 18) && minute() < WATER_PUMP_DURATION	)
	if(second() % 2 == 0) {
		setState(true);
		return;
	}
	setState(false);
}



void WaterPump::setState(bool set_on) {
	if (set_on == _power_state) {
		// Return if water pump is already in the desired state
		return;
	}

	_power_state = set_on;
	uploadCurrentState();
	Serial.print("Water pump turning ");
	Serial.println(_power_state ? "ON" : "OFF");
	Wire.beginTransmission(HWC_I2C_ID);
	Wire.write(WATER_PUMP);
	Wire.write(_power_state);  // sends one byte
	Wire.endTransmission();    // stop transmitting
}
