#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_state = DISABLED;
}


	void GrowLight::setup() {
		Homie.getLogger() << F("GrowLight::setup()") << endl;
		_growLightNode.advertise("on");

		setState(OFF);		// Setting state to OFF will change it out of the DISABLED state.
	}

void GrowLight::sendCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	switch (_state) {
		case ON:
			_growLightNode.setProperty("on").send("true");
		break;

		case OFF:
		case OVERHEAT:
		case DISABLED:
			_growLightNode.setProperty("on").send("false");
		break;
	}
}

	void GrowLight::loop(GrowErrors grow_errors) {
		if (_state == DISABLED) {
			return;
		}

		if (grow_errors.getOverheat() ) {
			setState(OVERHEAT);
			return;
		}

		//  Control Grow Light
		if (hour() >= GrowSettings.get_light_on_at() && hour() < GrowSettings.get_light_off_at()) {
		// if (second() % 2 == 0) {
			setState(ON);
		} else {
			setState(OFF);
		}
	}



	void GrowLight::setState(State state) {
		if (state == _state) {
			return;
		}

		_state = state;
		sendCurrentState();

		switch (_state) {
			case ON:
				Homie.getLogger() << F("Time: ") << hour() << F(" Grow light turning ON") << endl;
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=on", 13);
			break;

			case OFF:
				Homie.getLogger() << F("Time: ") << hour() << F(" Grow light is turning OFF") << endl;
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=off", 14);
			break;

			case OVERHEAT:
				Homie.getLogger() << F("Time: ") << hour() << F(" Grow light is overheating, turning OFF") << endl;
				_growLightNode.setProperty("on").send("false");
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=off", 14);
			break;

			case DISABLED:
				Homie.getLogger() << F("Time: ") << hour() << F(" Grow light is overheating, turning OFF") << endl;
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light=off", 14);
			break;
		}
	}
