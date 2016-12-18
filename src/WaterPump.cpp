#include <WaterPump.hpp>

WaterPump::WaterPump():
waterPumpNode("water_pump", "switch")
{}


void WaterPump::setup() {
	Serial << "WaterPump::setup()" << endl;
	pinMode(WATER_PUMP_PIN, OUTPUT);
  digitalWrite(WATER_PUMP_PIN, HIGH);
  waterPumpOn = true;
  waterPumpNode.advertise("on").settable([&](const HomieRange& range, const String& value) {
		if (value != "true" && value != "false") return false;
		waterPumpOn = (value == "true");
		digitalWrite(WATER_PUMP_PIN, waterPumpOn ? HIGH : LOW);
		waterPumpNode.setProperty("on").send(value);
		return true;
	});
}

void WaterPump::sendCurrentState() {
	if (!Homie.isConnected()) {
		return;
	}
	if (waterPumpOn) {
		waterPumpNode.setProperty("on").send("true");
	} else {
		waterPumpNode.setProperty("on").send("false");
	}
}

// void WaterPump::loop(GrowSettings grow_settings, SensorManager sensors) {
//
// }
