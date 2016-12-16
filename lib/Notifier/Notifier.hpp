#pragma once

#include "Arduino.h"
#include <Homie.h>


class NotifierClass
{
	public:
    NotifierClass();
		void setup();
    void send(const char* body);
		void setOverheat(bool new_overheating);
		void setWaterLevelLow(bool new_water_level_low);
  private:
    HomieNode notifierNode;

    bool overheating;
    unsigned long overheated_at;

		bool water_level_low;
};

extern NotifierClass Notifier;
