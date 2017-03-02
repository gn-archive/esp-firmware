#include "eNotifier.hpp"

NotifierClass::NotifierClass():
notifierNode("notification", "pushed to app")
{
}
// Initialize Notifier global/extern
NotifierClass Notifier;

void NotifierClass::setup() {
	Homie.getLogger() << F("NotifierClass::setup()") << endl;
	notifierNode.advertise("send");
}

void NotifierClass::send(const char* body) {
	if (Homie.isConnected()) {
		Homie.getLogger() << F("Sending notification: ") << body << endl;
		notifierNode.setProperty("send").send(body);
	}
}
