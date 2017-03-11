#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_power_state = false; // initialize to false
	_is_initialized = false;
	_overheat = false;
}


	void GrowLight::setup() {
		_growLightNode.advertise("on");
		_growLightNode.advertise("status");
	}

void GrowLight::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}

	if (_power_state) {
		_growLightNode.setProperty("on").setRetained(false).send("true");
	} else {
		_growLightNode.setProperty("on").setRetained(false).send("false");
	}

	if (_overheat) {
		_growLightNode.setProperty("status").setRetained(false).send("overheating");
	} else {
		_growLightNode.setProperty("status").setRetained(false).send("normal");
	}
}

	void GrowLight::loop() {

		if (Sensors.air_sensor.getTemp() > AIR_TEMP_OVERHEAT) {
			if (!_overheat) {
				_overheat = true;
				setState(false, "Grow light is overheating, turning OFF");
			}
			return;
		}
		_overheat = false;


		Chronos::DateTime light_on_at = Chronos::DateTime::now();
		light_on_at.setToStartOfDay();
		light_on_at += Chronos::Span::Hours(System.settings.get_light_on_at());

		Chronos::DateTime light_off_at = light_on_at + Chronos::Span::Hours(System.settings.get_light_on_duration());
		//  Control Grow Light
		if (
			Chronos::DateTime::now() > light_off_at &&
			Chronos::DateTime::now() < light_on_at
		) {
		// if (second() % 2 == 0) {
			setState(false, "Grow light is turning OFF");
		} else {
			setState(true, "Grow light is turning ON");
		}
	}



	void GrowLight::setState(bool new_power_state, const char* message) {
		if (new_power_state == _power_state && _is_initialized) {
			return;
		}

		_is_initialized = true;
		_power_state = new_power_state;
		uploadCurrentState();

		if (new_power_state) {
			Homie.getLogger() << message << endl;
			ShiftReg.writeBit(GROW_LIGHT_SR_PIN, LOW); // relay module is active low
		} else {
			Homie.getLogger() << message << endl;
			ShiftReg.writeBit(GROW_LIGHT_SR_PIN, HIGH); // relay module is active low
		}
	}
