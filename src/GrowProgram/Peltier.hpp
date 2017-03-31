#include <Arduino.h>
#include <Homie.h>
#include <constants.h>
#include "Sensors/Sensors.hpp"
#include "System/System.hpp"

class Peltier
{
	public:
		Peltier();
		void setup();
		void loop();
		void uploadCurrentState();
  private:
		void setState(uint8_t new_power_state);
    HomieNode _peltierNode;
		uint8_t _power_state;
};
