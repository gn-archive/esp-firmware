#include <main.h>

NtpManager ntp_manager;
GrowProgram grow_program;

void setup()
{
  delay(200);
  Serial.begin(74880);

  Serial << endl << endl <<
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  // test_led.setMode(4);
  	Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
    Homie_setBrand("Grow Nodes"); // before Homie.setup()

    ntp_manager.setup();

    Homie.setup();
}

void loop()
{
    ntp_manager.loop();

    grow_program.loop();

    Homie.loop();
}
