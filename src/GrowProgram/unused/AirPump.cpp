// #include "GrowProgram/private/AirPump.hpp"
//
// AirPump::AirPump():
// airPumpNode("air_pump", "relay")
// {}
//
//
// void AirPump::setup() {
// 	// pinMode(AIR_PUMP_PIN, OUTPUT);
//
// 	// digitalWrite(AIR_PUMP_PIN, HIGH);
//   airPumpOn = true;
//
// 	airPumpNode.advertise("on").settable([&](const HomieRange& range, const String& value) {
// 		if (value != "true" && value != "false") return false;
// 		airPumpOn = (value == "true");
// 		// digitalWrite(AIR_PUMP_PIN, airPumpOn ? HIGH : LOW);
// 		uploadCurrentState();
// 		return true;
// 	});
// }
//
//
// void AirPump::uploadCurrentState() {
// 	if (!Homie.isConnected()) {
// 		return;
// 	}
// 	if (airPumpOn) {
// 		airPumpNode.setProperty("on").send("true");
// 	} else {
// 		airPumpNode.setProperty("on").send("false");
// 	}
// }
