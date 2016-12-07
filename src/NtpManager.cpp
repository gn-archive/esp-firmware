// synchronization is done regularly without user intervention
// no more calls to library are needed.
// Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// Since then, your own (or default 1800 seconds) adjusted period applies.
#include <NtpManager.hpp>

NtpManager::NtpManager()
{
  lastSerialClockMillis = 0;
}

void NtpManager::setup() {
  Serial << "NtpManager..." << endl;
  NTP.onNTPSyncEvent([](NTPSyncEvent_t error) {
      if (error) {
          Serial << "NtpManager: Time Sync error: ";
          if (error == noResponse)
              Serial << "NtpManager: NTP server not reachable" << endl;
          else if (error == invalidAddress)
              Serial << "NtpManager: Invalid NTP server address" << endl;
      }
      else {
          Serial << "NtpManager: Got NTP time: ";
          Serial << NTP.getTimeDateString(NTP.getLastNTPSync()) << endl;
      }
  });
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(1800);
}

void NtpManager::loop() {
  if (millis() - lastSerialClockMillis >= 1000) {
    lastSerialClockMillis = millis();
    printDateTime();
  }

  if (timeStatus() != timeSet) {
    if(!messageSent) {
      messageSent = true;
      Serial << "NtpManager: Time is not set or needs to be synced." << endl;
    }
  } else {
    messageSent = false;
  }
}



void NtpManager::printDateTime () {
  // digital clock display of the time
  Serial << year() << "-" << month() << "-" << day() << "  " << hour();
   printDigits(minute());
   printDigits(second());
   Serial << endl;
}

void NtpManager::printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
