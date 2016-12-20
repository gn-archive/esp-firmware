#include <Notifier.hpp>

NotifierClass::NotifierClass():
notifierNode("notification", "send")
{
}
// Initialize Notifier global/extern
NotifierClass Notifier;

void NotifierClass::setup() {
	Serial << "NotifierClass::setup()" << endl;
	notifierNode.advertise("send");
}

void NotifierClass::send(const char* body) {
    Serial << "Sending notification: " << body << endl;
		notifierNode.setProperty("send").send(body);
}
