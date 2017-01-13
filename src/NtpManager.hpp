// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND
#include <Arduino.h>
#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
#define countof(a) (sizeof(a) / sizeof(a[0]))
/* for software wire use below
#include <SoftwareWire.h>  // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
SoftwareWire myWire(SDA, SCL);
RtcDS1307<SoftwareWire> Rtc(myWire);
 for software wire use above */

/* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
#include <NtpClientLib.h>
#include <Homie.h>

class NtpManager
{
	private:
		RtcDS1307<TwoWire> Rtc;
		bool messageSent;

		unsigned long lastSerialClockMillis;
		void printDateTime();
		void printDigits(int digits);
  public:
    NtpManager();
    void loop();
		void setup();
};
