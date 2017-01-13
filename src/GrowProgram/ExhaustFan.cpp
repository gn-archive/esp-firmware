#include "ExhaustFan.hpp"

ExhaustFan::ExhaustFan():
fanNode("fan", "relay")
{}


	void ExhaustFan::setup() {
		Serial << "ExhaustFan::setup()" << endl;
		pinMode(FAN_PIN, OUTPUT);
		digitalWrite(FAN_PIN, LOW);
		fanOn = false;
		fanNode.advertise("on");
	}

	void ExhaustFan::sendCurrentState() {
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
		// if (SensorManager.getAirTempF() < AIR_TEMP_OVERHEAT ) {
		// } else {
		// 	// If the air temp is above the danger temp
		// 		ensureOn(true);
		// }
	}


	void ExhaustFan::ensureOn(bool yes) {
		if (yes && !fanOn) {
			// turn on the fan if it is not already on
			Serial << " Fan is " << (fanOn ? "on" : "off") << ", turning ON" << endl;
			fanOn = true;
			sendCurrentState();
			digitalWrite(FAN_PIN, HIGH);
		}
		if (!yes && fanOn) {
			Serial << " Fan is " << (fanOn ? "on" : "off") << ", turning OFF" << endl;
			fanOn = false;
			sendCurrentState();
			digitalWrite(FAN_PIN, LOW);
		}
	}
