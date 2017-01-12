#include <main.h>


void setup()
{
  delay(200);
  Serial.begin(74880);

  Serial << endl << endl;
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
	Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent);
  Homie.setup();
  ntp_manager.setup();
  grow_program.setup();

  bus.strategy.set_pin(COM_BUS_PIN);
  bus.begin();
  bus.set_receiver(receiver_function);
}

void loop()
{
    Homie.loop();
    ntp_manager.loop();

    bus.receive(1000);
    
    if ( GrowSettings.get_aborted() ) {
      grow_program.setState(GrowProgram::STOPPED);
    } else {
      grow_program.setState(GrowProgram::RUNNING);
    }

    grow_program.loop();
}
