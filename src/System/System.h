#pragma once

#include <Arduino.h>

#include <System/TimeManager.hpp>


class SystemClass
{
	public:
    SystemClass();
		void setup();
    void loop();

  private:
    TimeManager time_manager;
};

extern SystemClass System;
