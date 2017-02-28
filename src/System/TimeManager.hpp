// CONNECTIONS:
// DS1307 SDA --> SDA
// DS1307 SCL --> SCL
// DS1307 VCC --> 5v
// DS1307 GND --> GND
#include <Arduino.h>
#include <pgmspace.h>
#define countof(a) (sizeof(a) / sizeof(a[0]))


/* for normal hardware wire use below */
#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS1307.h>
#include <NtpClientLib.h>
// #include <Timezone.h>
#include <constants.h>
#include <Homie.h>

class TimeManager
{
	private:
		RtcDS1307<TwoWire> rtc;
		unsigned long lastSerialPrintMillis;
		bool syncEventTriggered;
		NTPSyncEvent_t ntpEvent; // Last triggered event

		HomieNode timeNode;

		void processSyncEvent(NTPSyncEvent_t error);
		void setLocalSystemTimeFromRTC();
  public:
		void uploadCurrentState();
    TimeManager();
    void loop();
		void setup();
};
