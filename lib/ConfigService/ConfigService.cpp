#include "Arduino.h"
#include <Homie.h>
#include <ESP8266WiFi.h>


class ConfigService
{
	private:
	int ledPin;

  public:
		ConfigService(int pin);
		void loop();
};

// Constructor - creates a ConfigService
// and initializes the member variables and state
ConfigService::ConfigService(int pin) {
	ledPin = pin;
}

void ConfigService::loop() {
	const char* host = "www.example.com";

	WiFiClient client;

Serial.printf("\n[Connecting to %s ... ", host);
if (client.connect(host, 80))
{
	Serial.println("connected]");

	Serial.println("[Sending a request]");
	client.print(String("GET /") + " HTTP/1.1\r\n" +
							 "Host: " + host + "\r\n" +
							 "Connection: close\r\n" +
							 "\r\n"
							);

	Serial.println("[Response:]");
	while (client.connected())
	{
		if (client.available())
		{
			String line = client.readStringUntil('\n');
			Serial.println(line);
		}
	}
	client.stop();
	Serial.println("\n[Disconnected]");
}
else
{
	Serial.println("connection failed!]");
	client.stop();
}
	// if (Homie.isConnected) {
	//
	// }
}
