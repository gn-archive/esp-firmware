#include <main.h>

NtpManager ntp_manager;
GrowProgram grow_program;

void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      grow_program.sendCurrentState();
    break;
  }
}

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
    Homie.onEvent(onSystemEvent);
    Homie.setup();
    ntp_manager.setup();
    grow_program.setup();
}

void loop()
{
    Homie.loop();
    ntp_manager.loop();

    if ( GrowSettings.get_aborted() ) {
      grow_program.setState(GrowProgram::STOPPED);
    } else {
      grow_program.setState(GrowProgram::RUNNING);
    }

    grow_program.loop();

}
