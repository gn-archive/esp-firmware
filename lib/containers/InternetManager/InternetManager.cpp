/*
This example will open a configuration portal when the reset button is pressed twice.
This method works well on Wemos boards which have a single reset button on board. It avoids using a pin for launching the configuration portal.
How It Works
When the ESP8266 loses power all data in RAM is lost but when it is reset the contents of a small region of RAM is preserved. So when the device starts up it checks this region of ram for a flag to see if it has been recently reset. If so it launches a configuration portal, if not it sets the reset flag. After running for a while this flag is cleared so that it will only launch the configuration portal in response to closely spaced resets.
Settings
There are two values to be set in the sketch.
DRD_TIMEOUT - Number of seconds to wait for the second reset. Set to 10 in the example.
DRD_ADDRESS - The address in RTC RAM to store the flag. This memory must not be used for other purposes in the same sketch. Set to 0 in the example.
This example, contributed by DataCute needs the Double Reset Detector library from https://github.com/datacute/DoubleResetDetector .
*/
#include "Arduino.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/kentaylor/WiFiManager

#include "../../components/Led/Led.cpp"


class InternetManager
{
	private:
	Led status_led;
	WiFiManager wifiManager;

  public:
		InternetManager();
		void setup();
		void loop();
};

// Constructor - creates a InternetManager
// and initializes the member variables and state
InternetManager::InternetManager() :
	status_led(D4) {

	}



void InternetManager::setup() {
	Serial.println("Starting InternetManager");
	status_led.setMode(2);
	WiFiManager wifiManager;
	wifiManager.autoConnect("AP-NAME");
}


void InternetManager::loop() {
	if (WiFi.status() == WL_CONNECTED) {
		status_led.setMode(2);
	} else {
		status_led.setMode(3);
	}

	status_led.update();
}
