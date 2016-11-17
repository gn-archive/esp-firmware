#include "Arduino.h"
#include "../../components/Led/Led.cpp"

class InternetManager
{
	Led status_led;
	// private:

  public:
		InternetManager();
		void setup();
		void loop();
};

// Constructor - creates a InternetManager
// and initializes the member variables and state
InternetManager::InternetManager() :
	status_led(D4) {}



void InternetManager::setup() {
	status_led.setMode(3);
}


void InternetManager::loop() {
	status_led.update();
}
