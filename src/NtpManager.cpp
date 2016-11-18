// synchronization is done regularly without user intervention
// no more calls to library are needed.
// Update frequency is higher (every 15 seconds as default) until 1st successful sync is achieved.
// Since then, your own (or default 1800 seconds) adjusted period applies.
#include <NtpManager.hpp>

NtpManager::NtpManager()
{
}

void NtpManager::setup() {
  Serial << "NtpManager...";
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
  // if ((millis() % 2000) == 0) {
      // Serial.print(NTP.getTimeDateString()); Serial.print(". ");
      // Serial.print("WiFi is ");
      // Serial.print(WiFi.isConnected() ? "connected" : "not connected"); Serial.print(". ");
      // Serial.print("Uptime: ");
      // Serial.print(NTP.getUptimeString()); Serial.print(" since ");
      // Serial.println(NTP.getTimeDateString(NTP.getFirstSync()).c_str());
  // }
}
