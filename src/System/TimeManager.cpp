// // synchronization is done regularly without user intervention
// // no more calls to library are needed.
// // Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
#include <System/TimeManager.hpp>
//
TimeManager::TimeManager() :
timeNode("current_time", "string"),
rtc(Wire) {
  lastSerialPrintMillis = 0; // for printing the time every second
  bool syncEventTriggered = false; // True if a time sync event has been triggered.
}


void TimeManager::setup() {
  timeNode.advertise("time_string");
  Serial.print(F("Compiled at "));
  Serial.print(__DATE__);
  Serial.print(F(" "));
  Serial.println(__TIME__);

  Serial.print(F("Timezone offset is "));
  Serial.print((TIMEZONE_OFFSET > 0 ? "+" : ""));
  Serial.println(TIMEZONE_OFFSET);
  //--------RTC SETUP ------------
  rtc.Begin();
  Wire.begin(I2C_SDA, I2C_SCL); // SDA, SCL

  if (!rtc.IsDateTimeValid()) {
    Serial.println(F("RTC not connected properly or low battery!"));
  }

  if (!rtc.GetIsRunning()) {
      Serial.println(F("RTC was not actively running, starting now"));
      rtc.SetIsRunning(true);
  }

  setLocalSystemTimeFromRTC();

  // Lambda called on NTP sync. Handled in loop
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
  if (!Homie.isConnected()) {
		return;
	}
  // upload to MQTT
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
    // Homie.getLogger() << NTP.getTimeDateString(now()) << F(", free heap: ") << ESP.getFreeHeap() << endl;
  }
}

void TimeManager::setLocalSystemTimeFromRTC() {
  // Set system time from RTC
  RtcDateTime rtc_now = rtc.GetDateTime();
  Serial.print(F("RTC Time (UTC): "));
  Serial.println(NTP.getTimeDateString(rtc_now.Epoch32Time())); // using NTP time string formatter to print RTC time
  setTime(rtc_now.Epoch32Time() + TIMEZONE_OFFSET*60*60);
  Serial.print(F("✔ Set local system time from RTC "));
  Serial.println(NTP.getTimeDateString(now()));
}


void TimeManager::processSyncEvent(NTPSyncEvent_t error) {
    if (error) {
        Serial.println(F("✖ Time Sync error: "));
        if (error == noResponse)
            Serial.println(F("NTP server not reachable"));
        if (error == invalidAddress)
            Serial.println(F("Invalid NTP server address"));

        setLocalSystemTimeFromRTC();
    }
    else {
      // Set RTC from NTP time.
      // RTC SetDateTime takes seconds since Jan 1 2000. NTP tracks UNIX epoch.
      RtcDateTime rtcdt_from_ntp(now()-946684800); // convert to Y2K epoch
      rtc.SetDateTime(rtcdt_from_ntp);
      Serial.print(F("↕ Synced RTC using NTP time"));
      setLocalSystemTimeFromRTC();
    }
};
