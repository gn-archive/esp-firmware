#pragma once

#include "Arduino.h"
#include <Homie.h>


class NotifierClass
{
	public:
    NotifierClass();
		void setup();
    void loop(float tempf);
    void send(const char* body);
  private:
    HomieNode notifierNode;

    void setOverheat(bool new_overheating);
    bool overheating;
    unsigned long overheated_at;
};

extern NotifierClass Notifier;
