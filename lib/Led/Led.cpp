#include "Arduino.h"

// Typical human breathing pattern
// - inhalation is 1.5-2 s
// - exhalation is 1.5-2 s
// - automatic pause of almost no breathing is 1.5 s
#ifndef LED_BREATH_INHALE_DURATION
#define LED_BREATH_INHALE_DURATION  2000
#define LED_BREATH_EXHALE_DURATION  2500
#define LED_BREATH_DURATION         LED_BREATH_INHALE_DURATION+LED_BREATH_EXHALE_DURATION
#define LED_BREATH_PAUSE_DURATION   1200
#endif


class Led
{
	private:
	int ledPin;
	float ledBrightness;
  int ledMode;
	unsigned long updatedAt;
	void setBrightness(float percent);

  public:
		Led(int pin);
		void update();
		void setMode(int newMode);
};

// Constructor - creates a Led
// and initializes the member variables and state
Led::Led(int pin) {
	ledPin = pin;
	ledMode = 0;
	pinMode(ledPin, OUTPUT);

	ledBrightness = 0;
	updatedAt = 0;
}

void Led::update() {
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  switch(ledMode) {
    case 0:
        ledBrightness = 0;
        break;

    case 1:
        ledBrightness = 1;
        break;

    case 2:
      if(ledBrightness == 1) {
        if (currentMillis - updatedAt > 50) {
          // LED was on for long enough
          ledBrightness = 0;
          updatedAt = currentMillis;
        }
      } else {
        if (currentMillis - updatedAt > 2000) {
          // LED was off for long enough
          ledBrightness = 1;
          updatedAt = currentMillis;
        }
      }
      break;

    case 3:
      if(currentMillis - updatedAt >= 100) {
        if (ledBrightness == 0) {
          ledBrightness = 1;
        } else {
          ledBrightness = 0;
        }
        ledBrightness = ledBrightness;
        updatedAt = currentMillis;  // Remember the time
      }
      break;

    case 4:
      // Models human breathing pattern

      // updatedAt = end of start of inhale
      if (currentMillis > updatedAt + LED_BREATH_DURATION + LED_BREATH_PAUSE_DURATION) {
        // done with previous breath+pause, take a breath now.
        updatedAt = currentMillis;
      }

      int timeSinceBreathStart = currentMillis - updatedAt;

      if (timeSinceBreathStart < LED_BREATH_INHALE_DURATION) {
        // we are currently inhaling
        ledBrightness = timeSinceBreathStart/(float)LED_BREATH_INHALE_DURATION;

      } else if (timeSinceBreathStart < LED_BREATH_DURATION) {
        // we are currently exhaling
        ledBrightness = (timeSinceBreathStart - LED_BREATH_INHALE_DURATION)/(float)LED_BREATH_EXHALE_DURATION;
        ledBrightness = 1-ledBrightness;
      } else {
        // we are currently resting
      }
      if (ledBrightness < 0.1) {
        ledBrightness = 0.1;
      }
      break;
  }

    setBrightness(ledBrightness);  // Update the actual LED
}

void Led::setMode(int newMode) {
  if (ledMode != newMode) {
    ledMode = newMode;
    ledBrightness = 0;
    updatedAt = 0;
  }
}

void Led::setBrightness(float percent) {
  float R = (100 * log10(2))/(log10(1024));

  int pwm_value = pow (2, (roundf(percent*100) / R)) - 1;

  analogWrite(ledPin, 1023-pwm_value);
}
