#pragma once

#include <Arduino.h>

#include <System/private/TimeManager.hpp>
#include <System/public/Settings.hpp>

class SystemClass
{
	public:
    SystemClass();
		void setup();
    void loop();
		void uploadCurrentState();
		Settings settings;
  private:
    TimeManager time_manager;
};

extern SystemClass System;
