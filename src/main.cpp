#include <main.h>

PJON<SoftwareBitBang> MCUBus(MCU_BUS_DEVICE_ID); // <Strategy name> bus(selected device id)

GrowProgram grow_program;

void onPjonPacket(uint8_t *payload, uint16_t length, const PacketInfo &packet_info) {

    char payload_str[length+1]; // +1 for null terminator
     for(uint16_t i = 0; i < length; ++i) {
        payload_str[i] = (char)payload[i];
      }
    payload_str[length] = '\0';
    Homie.getLogger() << F("Received ") << length << F(" bytes: ") << payload_str << endl;

    grow_program.sensors.handle_incoming(payload_str);
}


void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      grow_program.uploadCurrentState();
    break;
  }
}


void setup()
{
  delay(200);
  Serial.begin(74880);

  Homie.getLogger() << endl << endl;
  Homie.getLogger() << F("==============================================================================") << endl;
  Homie.getLogger() << F("                               Welcome to NodeOS!") << endl;
  Homie.getLogger() << F("==============================================================================") << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent);
  Homie.setup();

  MCUBus.strategy.set_pin(MCU_BUS_PIN);
  MCUBus.begin();
  MCUBus.set_receiver(onPjonPacket);
  MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "air_sensor", 10, 5000000);
  MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "water_level", 11, 5000000);
  MCUBus.send_repeatedly(MCU_BUS_ARDUINO_ID, "water_temp", 10, 5000000);

  System.setup();
  grow_program.setup();

}

void loop()
{
    Homie.loop();

    MCUBus.update();
    MCUBus.receive(1000);

    System.loop();
    grow_program.loop();
}
