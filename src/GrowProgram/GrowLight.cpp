#include "GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_state = DISABLED;
}


	void GrowLight::setup() {
		Serial << "GrowLight::setup()" << endl;
		// pinMode(GROW_LIGHT_PIN, OUTPUT);
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
		if (second() >= GrowSettings.get_light_on_at() && second() < GrowSettings.get_light_off_at()) {
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
				Serial << "Time: " << second() << " Grow light turning ON" << endl;
				// digitalWrite(GROW_LIGHT_PIN, HIGH);
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light_on", 13);
			break;

			case OFF:
				Serial << "Time: " << second() << " Grow light is turning OFF" << endl;
				// digitalWrite(GROW_LIGHT_PIN, LOW);
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light_off", 14);
			break;

			case OVERHEAT:
				Serial << "Time: " << second() << " Grow light is overheating, turning OFF" << endl;
				_growLightNode.setProperty("on").send("false");
				// digitalWrite(GROW_LIGHT_PIN, LOW);
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light_off", 14);
			break;

			case DISABLED:
				Serial << "Time: " << second() << " Grow light is overheating, turning OFF" << endl;
				// digitalWrite(GROW_LIGHT_PIN, LOW);
				MCUBus.send(MCU_BUS_ARDUINO_ID, "grow_light_off", 14);
			break;
		}
	}
