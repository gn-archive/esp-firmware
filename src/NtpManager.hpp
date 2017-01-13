#include <Arduino.h>

#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <Homie.h>

class NtpManager
{
	private:
		bool messageSent;
		unsigned long lastSerialClockMillis;
		void printDateTime();
		void printDigits(int digits);
  public:
    NtpManager();
    void loop();
		void setup();
};
