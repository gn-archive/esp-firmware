#include <GrowLight.hpp>

GrowLight::GrowLight():
_growLightNode("grow_light", "switch")
{
	_state = DISABLED;
}


	void GrowLight::setup() {
		Serial << "GrowLight::setup()" << endl;
		pinMode(GROW_LIGHT_PIN, OUTPUT);
		_growLightNode.advertise("on");

		setState(OFF);		// Setting state to OFF will change it out of the DISABLED state.
	}



	void GrowLight::loop() {
		if (_state == DISABLED) {
			return;
		}

		if (SensorManager.getAirTempF() >= (float)GrowSettings.get_air_temp_high() ) {
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

		switch (_state) {
			case ON:
				Serial << "Time: " << second() << " Grow light turning ON" << endl;
				_growLightNode.setProperty("on").send("true");
				digitalWrite(GROW_LIGHT_PIN, HIGH);
			break;

			case OFF:
				Serial << "Time: " << second() << " Grow light is turning OFF" << endl;
				_growLightNode.setProperty("on").send("false");
				digitalWrite(GROW_LIGHT_PIN, LOW);
			break;

			case OVERHEAT:
				Serial << "Time: " << second() << " Grow light is overheating, turning OFF" << endl;
				_growLightNode.setProperty("on").send("false");
				digitalWrite(GROW_LIGHT_PIN, LOW);
			break;

			case DISABLED:
				Serial << "Time: " << second() << " Grow light is overheating, turning OFF" << endl;
				_growLightNode.setProperty("on").send("false");
				digitalWrite(GROW_LIGHT_PIN, LOW);
			break;
		}
	}
