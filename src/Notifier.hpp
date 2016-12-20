#pragma once
#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "Arduino.h"
#include <Homie.h>


class NotifierClass
{
	public:
    NotifierClass();
		void setup();
		void send(const char* body);
  private:
    HomieNode notifierNode;
};

extern NotifierClass Notifier;

#endif
