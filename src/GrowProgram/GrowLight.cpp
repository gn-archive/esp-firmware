#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
}


	void GrowLight::setup() {
		Homie.getLogger() << F("GrowLight::setup()") << endl;
		_growLightNode.advertise("on");

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
		if (!is_running) {
			return;
		}

		if (grow_errors.getOverheat() ) {
			setState(false, PSTR("Grow light is overheating, turning OFF"));
			return;
		}

		//  Control Grow Light
		if (hour() >= GrowSettings.get_light_on_at() && hour() < GrowSettings.get_light_off_at()) {
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
			Homie.getLogger() << F("Time: ") << hour() << F(" ") << message << endl;
			MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=on", 13);
		} else {
			Homie.getLogger() << F("Time: ") << hour() << F(" ") << message << endl;
			MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=off", 14);
		}
	}


void GrowLight::start() {
	Homie.getLogger() << F("Time: ") << hour() << F(" Grow light is running...") << endl;
	is_running = true;
}

void GrowLight::stop() {
	is_running = false;
	setState(false, PSTR("Grow light is not running, turning OFF"));
}
