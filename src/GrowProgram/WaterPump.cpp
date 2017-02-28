#include "GrowProgram/WaterPump.hpp"

WaterPump::WaterPump():
waterPumpNode("water_pump", "relay")
{
	waterPumpOn = true; // initialize to true, will be set to false in setup() when setState is called
	waterPumpOnChangedAt = 0;
}


void WaterPump::setup() {
	waterPumpNode.advertise("on");

	setState(false);
}

void WaterPump::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (waterPumpOn) {
		waterPumpNode.setProperty("on").send("true");
	} else {
		waterPumpNode.setProperty("on").send("false");
	}
}

void WaterPump::loop() {
	if (waterPumpOn) {
		// Turn the pump off if it has been on for more than WATER_PUMP_ON_DURATION_MS
		if (millis() - waterPumpOnChangedAt > WATER_PUMP_ON_DURATION_MS) {
			setState(false);
		}
	} else {
		// Turn the pump on if it has been off for more than WATER_PUMP_OFF_DURATION_MS
		if (millis() - waterPumpOnChangedAt > WATER_PUMP_OFF_DURATION_MS) {
			setState(true);
		}
	}
}



void WaterPump::setState(bool set_on) {
	if (set_on == waterPumpOn) {
		return;
	}

	waterPumpOn = set_on;
	waterPumpOnChangedAt = millis();
	uploadCurrentState();

	if (set_on) {
		Homie.getLogger() << F("Water pump is turning ON") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, LOW); // relay module is active low
	} else {
		Homie.getLogger() << F("Water pump is turning OFF") << endl;
		ShiftReg.writeBit(WATER_PUMP_SR_PIN, HIGH); // relay module is active low
	}
}
