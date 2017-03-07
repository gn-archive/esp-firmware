#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_power_state = false; // initialize to false
	_is_initialized = false;
	_last_overheat = 0;
}


	void GrowLight::setup() {
		_growLightNode.advertise("on");
	}

void GrowLight::uploadCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (_power_state) {
		_growLightNode.setProperty("on").send("true");
	} else {
		_growLightNode.setProperty("on").send("false");
	}
}

	void GrowLight::loop() {

		if (Sensors.air_sensor.getTemp() > AIR_TEMP_OVERHEAT) {
			if (!_last_overheat) {
				Serial.println(Sensors.air_sensor.getTemp());
				_last_overheat = millis();
				setState(false, "Grow light is overheating, turning OFF");
			}
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
