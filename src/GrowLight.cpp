#include <GrowLight.hpp>

GrowLight::GrowLight():
growLightNode("grow_light", "switch")
{}


void GrowLight::setup() {
	Serial << "GrowLight::setup()" << endl;
	pinMode(GROW_LIGHT_PIN, OUTPUT);
  digitalWrite(GROW_LIGHT_PIN, LOW);
  growLightOn = false;
  growLightNode.advertise("on");
  growLightNode.setProperty("on").send("false");
}



void GrowLight::loop() {

	if (SensorManager.getAirTempF() >= (float)GrowSettings.get_air_temp_high() ) {
		// Overheating, shut down lights
		growLightOn = false;
		growLightNode.setProperty("on").send("false");
		digitalWrite(GROW_LIGHT_PIN, LOW);
		return;
	}


	//  Control Grow Light
	if (second() >= GrowSettings.get_light_on_at() && second() < GrowSettings.get_light_off_at()) {
		ensureOn(true);
	} else {
		ensureOn(false);
	}
}

void GrowLight::ensureOn(bool yes) {
	if (yes && !growLightOn) {
		Serial << "Time: " << second() << " Grow light is " << (growLightOn ? "on" : "off") << ", turning ON" << endl;
		growLightOn = true;
		growLightNode.setProperty("on").send("true");
		digitalWrite(GROW_LIGHT_PIN, HIGH);
	}

	if (!yes && growLightOn) {
		Serial << "Time: " << second() << " Grow light is " << (growLightOn ? "on" : "off") << ", turning OFF" << endl;
		growLightOn = false;
		growLightNode.setProperty("on").send("false");
		digitalWrite(GROW_LIGHT_PIN, LOW);
	}
}
