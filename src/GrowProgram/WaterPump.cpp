#include "GrowProgram/WaterPump.hpp"

WaterPump::WaterPump():
waterPumpNode("water_pump", "relay")
{
	waterPumpOn = true; // initialize to true, will be set to false in setup() when setState is called
	waterPumpOnChangedAt = 0;
}


void WaterPump::setup() {
	Homie.getLogger() << F("WaterPump::setup()") << endl;
	pinMode(WATER_PUMP_PIN, OUTPUT);
	setState(false);

  waterPumpNode.advertise("on").settable([&](const HomieRange& range, const String& value) {
		if (value != "true" && value != "false") return false;

		setState((value == "true"));

		return true;
	});
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
