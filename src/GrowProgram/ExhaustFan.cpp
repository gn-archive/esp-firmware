#include "GrowProgram/ExhaustFan.hpp"

ExhaustFan::ExhaustFan():
fanNode("fan", "relay")
{}


	void ExhaustFan::setup() {
		Homie.getLogger() << F("ExhaustFan::setup()") << endl;
		pinMode(FAN_PIN, OUTPUT);
		digitalWrite(FAN_PIN, LOW);
		fanOn = false;
		fanNode.advertise("on");
	}

	void ExhaustFan::uploadCurrentState() {
		if (!Homie.isConnected()) {
			return;
		}
		if (fanOn) {
			fanNode.setProperty("on").send("true");
		} else {
			fanNode.setProperty("on").send("false");
		}
	}

	void ExhaustFan::loop() {
		ensureOn(true);
		// if (SensorManager.getAirTemp() < AIR_TEMP_OVERHEAT ) {
		// } else {
		// 	// If the air temp is above the danger temp
		// 		ensureOn(true);
		// }
	}


	void ExhaustFan::ensureOn(bool yes) {
		if (yes && !fanOn) {
			// turn on the fan if it is not already on
			Homie.getLogger() << F(" Fan is ") << (fanOn ? "on" : "off") << F(", turning ON") << endl;
			fanOn = true;
			uploadCurrentState();
			digitalWrite(FAN_PIN, HIGH);
		}
		if (!yes && fanOn) {
			Homie.getLogger() << F(" Fan is ") << (fanOn ? "on" : "off") << F(", turning OFF") << endl;
			fanOn = false;
			uploadCurrentState();
			digitalWrite(FAN_PIN, LOW);
		}
	}
