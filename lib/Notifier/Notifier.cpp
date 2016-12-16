#include <Notifier.hpp>

NotifierClass::NotifierClass():
notifierNode("notification", "send")
{
	overheated_at = 0;
}
// Initialize Notifier global/extern
NotifierClass Notifier;

void NotifierClass::setup() {
	Serial << "NotifierClass::setup()" << endl;
	notifierNode.advertise("send");
}

void NotifierClass::send(const char* body) {
    Serial << "sending: " << body << endl;
		notifierNode.setProperty("send").send(body);
}

void NotifierClass::setOverheat(bool new_overheating) {
	if (overheating == new_overheating && millis() - overheated_at < 1000*60*60*6 ) {
		return;
	}

	overheating = new_overheating;
	overheated_at = 0;

	if (overheating) {
		overheated_at = millis();
		send("Environment is too hot!");
	}
}
