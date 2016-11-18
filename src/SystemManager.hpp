#include "Arduino.h"

#include <NtpManager.hpp>
#include <GrowManager.hpp>

class SystemManager
{
	private:
		NtpManager ntp_manager;
		GrowManager grow_manager;
  public:
    SystemManager();
    void loop();
		void setup();
};
