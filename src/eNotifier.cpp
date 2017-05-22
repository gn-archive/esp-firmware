// #include "eNotifier.hpp"
//
// NotifierClass::NotifierClass():
// notifierNode("notification", "pushed to app")
// {
// }
// // Initialize Notifier global/extern
// NotifierClass Notifier;
//
// void NotifierClass::setup() {
// 	Serial.println(F("NotifierClass::setup()"));
// 	notifierNode.advertise("send");
// }
//
// void NotifierClass::send(const char* body) {
// 	if (Homie.isConnected()) {
// 		Serial.print(F("Sending notification: "));
// 		Serial.println(body);
// 		notifierNode.setProperty("send").send(body);
// 	}
// }
