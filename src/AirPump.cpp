#include <AirPump.hpp>

AirPump::AirPump():
airPumpNode("air_pump", "switch")
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
		airPumpNode.setProperty("on").send(value);
		return true;
	});
  airPumpNode.setProperty("on").send("true");
}



// void AirPump::loop(GrowSettings grow_settings, SensorManager sensors) {
//
// }
