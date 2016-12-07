#include <ExhaustFan.hpp>

ExhaustFan::ExhaustFan():
fanNode("fan", "switch")
{}


	void ExhaustFan::setup() {
		Serial << "ExhaustFan::setup()" << endl;
		pinMode(FAN_PIN, OUTPUT);
		digitalWrite(FAN_PIN, LOW);
		fanOn = false;
		fanNode.advertise("on");
		fanNode.setProperty("on").send("false");
	}


	// Turn the fan on if the temperature is below the minimum temperature.

	void ExhaustFan::loop(GrowSettings grow_settings, SensorManager sensors) {
		// Control Fan
		if (isnan(sensors.getAirTempF())) {
			return;
		}

		if (sensors.getAirTempF() < (float)grow_settings.get_air_temp_low() ) {
			shouldBeOn(false);
		} else if (sensors.getAirTempF() <= (float)grow_settings.get_air_temp_high() ) {
			// If the air temp is within tolerance. Aka above the low cutoff but less than the danger temp
			shouldBeOn(true);
		} else {
			// If the air temp is above the danger temp
				shouldBeOn(true);
		}
	}


	void ExhaustFan::shouldBeOn(bool yes) {
		// if (yes && !fanOn) {
		// 	// turn on the fan if it is not already on
		// 	Serial << " Fan is " << (fanOn ? "on" : "off") << ", turning ON" << endl;
		// 	fanOn = true;
		// 	fanNode.setProperty("on").send("true");
		// 	digitalWrite(FAN_PIN, HIGH);
		// }
		// if (!yes && fanOn) {
		// 	Serial << " Fan is " << (fanOn ? "on" : "off") << ", turning OFF" << endl;
		// 	fanOn = false;
		// 	fanNode.setProperty("on").send("false");
		// 	digitalWrite(FAN_PIN, LOW);
		// }
	}
