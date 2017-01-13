#ifndef COM_BUS_H
#define COM_BUS_H

#pragma once

#include "Arduino.h"
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
};


extern ComBusClass ComBus;

#endif
