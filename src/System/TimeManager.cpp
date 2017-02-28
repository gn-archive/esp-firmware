// // synchronization is done regularly without user intervention
// // no more calls to library are needed.
// // Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// // Since then, your own (or default 1800 seconds) adjusted period applies.
#include <System/TimeManager.hpp>
//
TimeManager::TimeManager() :
timeNode("current_time", "string"),
rtc(Wire) {
  lastSerialPrintMillis = 0;
  timezone_offset = -8;    // Default to PST
  boolean syncEventTriggered = false; // True if a time even has been triggered
}


void TimeManager::setup() {
  timeNode.advertise("time_string");
  Homie.getLogger() << F("Compiled at ") << __DATE__ << " " << __TIME__ << endl;
  Homie.getLogger() << F("Timezone offset is UTC") << (timezone_offset > 0 ? "+" : "") << timezone_offset << " hours" << endl;
  //--------RTC SETUP ------------
  rtc.Begin();
  Wire.begin(I2C_SDA, I2C_SCL); // SDA, SCL

  if (!rtc.IsDateTimeValid()) {
    Homie.getLogger() << F("RTC not connected properly or low battery!") << endl;
  }

  if (!rtc.GetIsRunning()) {
      Homie.getLogger() << F("RTC was not actively running, starting now") << endl;
      rtc.SetIsRunning(true);
  }

  setLocalSystemTimeFromRTC();

  // Lambda called on NTP sync
	NTP.onNTPSyncEvent([&](NTPSyncEvent_t event) {
		ntpEvent = event;
		syncEventTriggered = true;
	});


  // Start NTP sync
  NTP.begin("pool.ntp.org", 0, true);
  NTP.setInterval(1800);  // seconds between sync attempt
}
//
void TimeManager::uploadCurrentState() {
  timeNode.setProperty("time_string").send(NTP.getTimeDateString(now()));
}

void TimeManager::loop() {

  if (syncEventTriggered) {
  		processSyncEvent(ntpEvent);
  		syncEventTriggered = false;
  	}

  // Print time every second
  if (millis() - lastSerialPrintMillis >= 1000) {
    uploadCurrentState();
    lastSerialPrintMillis = millis();
    Homie.getLogger() << NTP.getTimeDateString(now()) << F(", free heap: ") << ESP.getFreeHeap() << endl;
  }
}

void TimeManager::setLocalSystemTimeFromRTC() {
  // Set system time from RTC
  RtcDateTime rtc_now = rtc.GetDateTime();
  Homie.getLogger() << F("RTC Time (UTC): ") << NTP.getTimeDateString(rtc_now.Epoch32Time()) << endl; // using NTP time string formatter to print RTC time
  setTime(rtc_now.Epoch32Time() + timezone_offset*60*60);
  Homie.getLogger() << F("✔ Set local system time from RTC ") << NTP.getTimeDateString(now()) << endl;
}


void TimeManager::processSyncEvent(NTPSyncEvent_t error) {
    if (error) {
        Homie.getLogger() << F("✖ Time Sync error: ");
        if (error == noResponse)
            Homie.getLogger() << F("NTP server not reachable") << endl;
        if (error == invalidAddress)
            Homie.getLogger() << F("Invalid NTP server address") << endl;

        setLocalSystemTimeFromRTC();
    }
    else {
      // Set RTC from NTP time.
      RtcDateTime rtcdt_from_ntp(now()-946684800);   // RTC set time takes seconds since Jan 1 2000. NTP tracks in seconds since epoch time.
      rtc.SetDateTime(rtcdt_from_ntp);
      RtcDateTime rtc_now = rtc.GetDateTime();
      Homie.getLogger() << F("↕ Synced RTC using NTP time: ") << NTP.getTimeDateString(rtc_now.Epoch32Time()) << endl;

      setTime(now() + timezone_offset*60*60);

    }
};
