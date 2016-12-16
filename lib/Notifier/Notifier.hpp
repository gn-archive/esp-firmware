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
  private:
    HomieNode notifierNode;

    bool overheating;
    unsigned long overheated_at;
};

extern NotifierClass Notifier;
