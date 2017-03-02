#pragma once

#include <Arduino.h>

#include <System/TimeManager.hpp>
#include <System/Settings.hpp>

class SystemClass
{
	public:
    SystemClass();
		void setup();
    void loop();
		Settings settings;
  private:
    TimeManager time_manager;
};

extern SystemClass System;
