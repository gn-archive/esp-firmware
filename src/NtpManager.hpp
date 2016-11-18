#include "Arduino.h"

#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <Homie.h>

class NtpManager
{
	private:
  public:
    NtpManager();
    void loop();
		void setup();
};
