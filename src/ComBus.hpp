#pragma once

#include <Arduino.h>
// #include <ESP8266WiFi.h>
#include <constants.h>
#include <SPI.h>
#include <PJON.h>

class ComBusClass
{
	private:

		PJON<SoftwareBitBang> bus;

	public:
    ComBusClass();
		void setup();
		void loop();

		void send(int to_device_id, String string_to_send);
};


extern ComBusClass ComBus;
