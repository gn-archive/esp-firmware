#include "AirPump.hpp"

AirPump::AirPump():
airPumpNode("air_pump", "relay")
{}


void AirPump::setup() {
	Serial << "AirPump::setup()" << endl;
	pinMode(AIR_PUMP_PIN, OUTPUT);
  digitalWrite(AIR_PUMP_PIN, HIGH);
  airPumpOn = true;
  airPumpNode.advertise("on").settable([&](const HomieRange& range, const String& value) {
		if (value != "true" && value != "false") return false;
		airPumpOn = (value == "true");
		digitalWrite(AIR_PUMP_PIN, airPumpOn ? HIGH : LOW);
		return true;
	});
}


void AirPump::sendCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (airPumpOn) {
		airPumpNode.setProperty("on").send("true");
	} else {
		airPumpNode.setProperty("on").send("false");
	}
}



// void AirPump::loop(GrowSettings grow_settings, SensorManager sensors) {
//
// }
