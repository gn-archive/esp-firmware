#include "GrowProgram/WaterPump.hpp"

// ************************************************************************
// IF PYTHAGOREAN CUP EBB/FLOW METHODD IS IMPLEMENTED, RUN PUMP CONTINUOUSLY UNLESS WATER LEVEL IS LOW
// ************************************************************************

WaterPump::WaterPump():
waterPumpNode("water_pump", "relay")
{
	waterPumpOn = false; // initialize to false, will be set to true in setup() when setState is called
	waterPumpOnChangedAt = 0;
}


void WaterPump::setup() {
	Homie.getLogger() << F("WaterPump::setup()") << endl;
	waterPumpNode.advertise("on");

	pinMode(WATER_PUMP_PIN, OUTPUT);
	setState(true);
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
		Homie.getLogger() << F("Time: ") << hour() << F(" Water pump is turning ON") << endl;
		MCUBus.send(MCU_BUS_ARDUINO_ID, "water_pump=on", 13);
	} else {
		Homie.getLogger() << F("Time: ") << hour() << F(" Water pump is turning OFF") << endl;
		MCUBus.send(MCU_BUS_ARDUINO_ID, "water_pump=off", 14);
	}
}
