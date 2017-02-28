#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	is_on = true; // initialize to true, will be set to false in setup() when setState is called
}


	void GrowLight::setup() {
		_growLightNode.advertise("on");
		setState(false, "Grow light is initializing to OFF");
	}

void GrowLight::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (is_on) {
		_growLightNode.setProperty("on").send("true");
	} else {
		_growLightNode.setProperty("on").send("false");
	}
}

	void GrowLight::loop(GrowErrors grow_errors) {
		if (!is_enabled) {
			return;
		}

		if (grow_errors.getOverheat() ) {
			setState(false, PSTR("Grow light is overheating, turning OFF"));
			return;
		}

		//  Control Grow Light
		if (hour() >= System.settings.get_light_on_at() && hour() < System.settings.get_light_off_at()) {
		// if (second() % 2 == 0) {
			setState(true, "Grow light is turning ON");
		} else {
			setState(false, "Grow light is turning OFF");
		}
	}



	void GrowLight::setState(bool set_on, const char* message) {
		if (set_on == is_on) {
			return;
		}

		is_on = set_on;
		uploadCurrentState();

		if (set_on) {
			Homie.getLogger() << message << endl;
			// MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=on", 13);
		} else {
			Homie.getLogger() << message << endl;
			// MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=off", 14);
		}
	}


void GrowLight::start() {
	Homie.getLogger() << F("Grow light is enabled") << endl;
	is_enabled = true;
}

void GrowLight::stop() {
	is_enabled = false;
	setState(false, PSTR("Grow light is disabled, turning OFF"));
}
