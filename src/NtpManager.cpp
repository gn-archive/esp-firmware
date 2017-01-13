// // synchronization is done regularly without user intervention
// // no more calls to library are needed.
// // Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// // Since then, your own (or default 1800 seconds) adjusted period applies.
#include <NtpManager.hpp>
//
NtpManager::NtpManager() :
Rtc(Wire) {
  lastSerialClockMillis = 0;
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
  Serial << "RTC Time: "
          << rtc_now.Year()
          << "-"
          << rtc_now.Month()
          << "-"
          << rtc_now.Day()
          << " "
          << rtc_now.Hour()
          << ":"
          << rtc_now.Minute()
          << ":"
          << rtc_now.Second()
          << endl;



  NTP.onNTPSyncEvent([&](NTPSyncEvent_t error) {
      if (error) {
          Serial << "NtpManager: Time Sync error: ";
          if (error == noResponse)
              Serial << "NTP server not reachable" << endl;
          else if (error == invalidAddress)
              Serial << "Invalid NTP server address" << endl;
      }
      else {
          RtcDateTime time_to_set;
          time_to_set.InitWithEpoch32Time(now());
          Rtc.SetDateTime(time_to_set);
          Serial << "NtpManager: Synced NTP time: ";
          Serial << NTP.getTimeDateString(NTP.getLastNTPSync()) << endl;
      }
  });
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(1800);
}
//
void NtpManager::loop() {
//   if (millis() - lastSerialClockMillis >= 1000) {
//     lastSerialClockMillis = millis();
//     printDateTime();
//   }
//
//   if (timeStatus() != timeSet) {
//     if(!messageSent) {
//       messageSent = true;
//       Serial << "NtpManager: Time is not set or needs to be synced." << endl;
//     }
//   } else {
//     messageSent = false;
//   }
}
//
//
// void NtpManager::printDateTime () {
//   // digital clock display of the time
//   Serial << year() << "-" << month() << "-" << day() << "  " << hour();
//    printDigits(minute());
//    printDigits(second());
//    Serial << endl;
// }
//
// void NtpManager::printDigits(int digits){
//   // utility function for digital clock display: prints preceding colon and leading 0
//   Serial.print(":");
//   if(digits < 10)
//     Serial.print('0');
//   Serial.print(digits);
// }
