// // synchronization is done regularly without user intervention
// // no more calls to library are needed.
// // Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// // Since then, your own (or default 1800 seconds) adjusted period applies.
#include <NtpManager.hpp>
//
NtpManager::NtpManager() :
Rtc(Wire) {
  lastSerialPrintMillis = 0;
}
//
void NtpManager::setup() {
  Serial << "NtpManager..." << endl;

  Serial << "Compiled at " << __DATE__ << " " << __TIME__ << endl;

  //--------RTC SETUP ------------
  Rtc.Begin();
  Wire.begin(D1, D2); // SDA, SCL

  if (!Rtc.IsDateTimeValid()) {
    Serial.println("RTC not configured or low battery!");
  }

  if (!Rtc.GetIsRunning()) {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  RtcDateTime rtc_now = Rtc.GetDateTime();
  Serial << "RTC Time: " << NTP.getTimeDateString(rtc_now.Epoch32Time()) << endl; // using NTP time string formatter to print RTC time
  setTime(rtc_now.Epoch32Time());
  Serial << "✔ Set system time from RTC: " << NTP.getTimeDateString(now()) << endl;

  NTP.onNTPSyncEvent([&](NTPSyncEvent_t error) {
      if (error) {
          Serial << "✖ Time Sync error: ";
          if (error == noResponse)
              Serial << "NTP server not reachable" << endl;
          else if (error == invalidAddress)
              Serial << "Invalid NTP server address" << endl;
      }
      else {
        Serial << "✔ Synced NTP time: ";
        Serial << NTP.getTimeDateString(NTP.getLastNTPSync()) << endl;

        RtcDateTime rtcdt_from_ntp(NTP.getLastNTPSync()-946684800);   // RTC set time takes seconds since Jan 1 2000. NTP tracks in seconds since epoch time.
        Rtc.SetDateTime(rtcdt_from_ntp);
        Serial << "✔ Set RTC using NTP time: " << NTP.getTimeDateString(now()) << endl;

      }
  });
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(1800);
}
//
void NtpManager::loop() {
  if (millis() - lastSerialPrintMillis >= 1000) {
    lastSerialPrintMillis = millis();
    Serial << NTP.getTimeDateString(now()) << endl;
  }


  // if (lastNTPSync != NTP.getLastNTPSync()) {
  //   lastNTPSync = NTP.getLastNTPSync();
  //
  //
  // }

}
