// // synchronization is done regularly without user intervention
// // no more calls to library are needed.
// // Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// // Since then, your own (or default 1800 seconds) adjusted period applies.
#include <TimeManager.hpp>
//
TimeManager::TimeManager() :
Rtc(Wire) {
  lastSerialPrintMillis = 0;
}
//
void TimeManager::setup() {
  Homie.getLogger() << F("TimeManager...") << endl;

  Homie.getLogger() << F("Compiled at ") << __DATE__ << " " << __TIME__ << endl;

  //--------RTC SETUP ------------
  Rtc.Begin();
  Wire.begin(D1, D2); // SDA, SCL

  if (!Rtc.IsDateTimeValid()) {
    Homie.getLogger() << F("RTC not configured or low battery!");
  }

  if (!Rtc.GetIsRunning()) {
      Homie.getLogger() << F("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  // Set system time from RTC
  RtcDateTime rtc_now = Rtc.GetDateTime();
  Homie.getLogger() << F("RTC Time: ") << NTP.getTimeDateString(rtc_now.Epoch32Time()) << endl; // using NTP time string formatter to print RTC time
  setTime(rtc_now.Epoch32Time());
  Homie.getLogger() << F("✔ Set system time from RTC: ") << NTP.getTimeDateString(now()) << endl;

  // Lambda called on NTP sync
  NTP.onNTPSyncEvent([&](NTPSyncEvent_t error) {
      if (error) {
          Homie.getLogger() << F("✖ Time Sync error: ");
          if (error == noResponse)
              Homie.getLogger() << F("NTP server not reachable") << endl;
          else if (error == invalidAddress)
              Homie.getLogger() << F("Invalid NTP server address") << endl;
      }
      else {
        Homie.getLogger() << F("✔ Synced NTP time: ");
        Homie.getLogger() << NTP.getTimeDateString(NTP.getLastNTPSync()) << endl;

        // Set RTC from NTP time.
        RtcDateTime rtcdt_from_ntp(NTP.getLastNTPSync()-946684800);   // RTC set time takes seconds since Jan 1 2000. NTP tracks in seconds since epoch time.
        Rtc.SetDateTime(rtcdt_from_ntp);
        Homie.getLogger() << F("✔ Set RTC using NTP time: ") << NTP.getTimeDateString(now()) << endl;

      }
  });

  // Start NTP sync
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(1800);  // seconds between sync attempt
}
//


void TimeManager::loop() {
  // Print time every second
  if (millis() - lastSerialPrintMillis >= 1000) {
    lastSerialPrintMillis = millis();
    Homie.getLogger() << NTP.getTimeDateString(now()) << endl;
  }
}
