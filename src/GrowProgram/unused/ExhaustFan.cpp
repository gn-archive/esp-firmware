// #include "GrowProgram/ExhaustFan.hpp"
//
// ExhaustFan::ExhaustFan():
// fanNode("fan", "relay")
// {
// 	fanOn = false;
// }
//
//
// void ExhaustFan::setup() {
// 	fanNode.advertise("on");
//
// 	setState(true);
// }
//
// void ExhaustFan::uploadCurrentState() {
// 	if (!Homie.isConnected()) {
// 		return;
// 	}
// 	if (fanOn) {
// 		fanNode.setProperty("on").send("true");
// 	} else {
// 		fanNode.setProperty("on").send("false");
// 	}
// }
//
// void ExhaustFan::loop() {
// 	setState(true);
// }
//
// void ExhaustFan::setState(bool new_state) {
// 	if (fanOn == new_state) {
// 		return;
// 	}
//
// 	fanOn = new_state;
// 	uploadCurrentState();
//
// 	if (new_state) {
// 		Homie.getLogger() << F("Exhaust fan is turning ON") << endl;
// 		// MCUBus.send(MCU_BUS_ARDUINO_ID, "exhaust_fan=on", 13);
// 	} else {
// 		Homie.getLogger() << F("Exhaust fan is turning OFF") << endl;
// 		// MCUBus.send(MCU_BUS_ARDUINO_ID, "exhaust_fan=off", 14);
// 	}
// }
