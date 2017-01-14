#include <main.h>

PJON<SoftwareBitBang> MCUBus(MCU_BUS_DEVICE_ID); // <Strategy name> bus(selected device id)

TimeManager time_manager;
GrowProgram grow_program;

void onPjonPacket(uint8_t *payload, uint16_t length, const PacketInfo &packet_info) {

    String payload_str;
     for(uint16_t i = 0; i < length; ++i)
        payload_str += (char)payload[i];

    Serial.print("Received ");
    Serial.print(length);
    Serial.print(" bytes: ");
    Serial.println(payload_str);

    SensorManager.handle_incoming(payload_str);
}


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

  Serial << endl << endl;
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent);
  Homie.setup();

  MCUBus.strategy.set_pin(MCU_BUS_PIN);
  MCUBus.begin();
  MCUBus.set_receiver(onPjonPacket);
  MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "air_temp_f", 10, 6000000);
  MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "water_level", 11, 5000000);

  time_manager.setup();
  grow_program.setup();

}

void loop()
{
    Homie.loop();

    MCUBus.update();
    MCUBus.receive(1000);

    time_manager.loop();

    if ( GrowSettings.get_aborted() ) {
      grow_program.setState(GrowProgram::STOPPED);
    } else {
      grow_program.setState(GrowProgram::RUNNING);
    }

    grow_program.loop();
}
