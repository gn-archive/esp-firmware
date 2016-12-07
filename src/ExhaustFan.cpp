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



	void ExhaustFan::loop(GrowSettings grow_settings, SensorManager sensors) {
		// Control Fan
		if (!isnan(sensors.getAirTempF())) {
			if (!fanOn && (sensors.getAirTempF() > (float)grow_settings.get_air_temp_high() )) {
				Serial << "Temp: " << sensors.getAirTempF() << " Fan is " << (fanOn ? "on" : "off") << ", turning ON" << endl;
				fanOn = true;
				fanNode.setProperty("on").send("true");
				digitalWrite(FAN_PIN, HIGH);
			}
		} else {
			if (fanOn && (sensors.getAirTempF() < 60.0 )) {
				Serial << "Temp: " << sensors.getAirTempF() << " Fan is " << (fanOn ? "on" : "off") << ", turning OFF" << endl;
				fanOn = false;
				fanNode.setProperty("on").send("false");
				digitalWrite(FAN_PIN, LOW);
			}
		}
	}
