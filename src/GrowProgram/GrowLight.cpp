#include "GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_state = DISABLED;
}


	void GrowLight::setup() {
		Serial << "GrowLight::setup()" << endl;
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
		MCUBus.remove(mcu_bus_ref);

		_state = state;
		sendCurrentState();

		switch (_state) {
			case ON:
				Serial << "Time: " << hour() << " Grow light turning ON" << endl;
				mcu_bus_ref = MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "grow_light_on", 13, 1000000);
			break;

			case OFF:
				Serial << "Time: " << hour() << " Grow light is turning OFF" << endl;
				mcu_bus_ref = MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "grow_light_off", 14, 1000000);
			break;

			case OVERHEAT:
				Serial << "Time: " << hour() << " Grow light is overheating, turning OFF" << endl;
				_growLightNode.setProperty("on").send("false");
				mcu_bus_ref = MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "grow_light_off", 14, 1000000);
			break;

			case DISABLED:
				Serial << "Time: " << hour() << " Grow light is overheating, turning OFF" << endl;
				mcu_bus_ref = MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "grow_light_off", 14, 1000000);
			break;
		}
	}
