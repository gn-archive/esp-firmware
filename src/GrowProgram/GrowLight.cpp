#include "GrowProgram/GrowLight.hpp"

GrowLight::GrowLight():
_growLightNode("grow_light", "relay")
{
	_power_state = false; // initialize to false
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
		_growLightNode.setProperty("on").send("true");
	} else {
		_growLightNode.setProperty("on").send("false");
	}

	if (_overheat) {
		_growLightNode.setProperty("status").send("overheating");
	} else {
		_growLightNode.setProperty("status").send("normal");
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

		//  Control Grow Light
		if (System.settings.is_light_on_at(hour())) {
		// if (second() % 2 == 0) {
			setState(true, "Grow light is turning ON");
		} else {
			setState(false, "Grow light is turning OFF");
		}
	}



	void GrowLight::setState(bool new_power_state, const char* message) {
		if (new_power_state == _power_state) {
			return;
		}

		_power_state = new_power_state;
		uploadCurrentState();

		Serial.println(message);

		Wire.beginTransmission(HWC_I2C_ID);
		Wire.write(GROW_LIGHT);
		Wire.write(_power_state);
		Wire.endTransmission();
	}
