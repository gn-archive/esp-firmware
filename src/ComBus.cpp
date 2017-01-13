#include "ComBus.hpp"

// Constructor - creates a ComBusClass
// and initializes the member variables and state
ComBusClass::ComBusClass():
bus(COM_BUS_THIS_ID) // <Strategy name> bus(selected device id)
{
}

ComBusClass ComBus;


void ComBusClass::setup() {
  bus.strategy.set_pin(COM_BUS_PIN);
  bus.begin();
  bus.set_receiver([](uint8_t *payload, uint16_t length, const PacketInfo &packet_info) {
    Serial.print("Received: ");
    for(uint8_t i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println("");
  });
}

void ComBusClass::loop() {

      bus.update();
      bus.receive(1000);
}

void ComBusClass::send(int to_device_id, String string_to_send) {
  bus.send(to_device_id, string_to_send.c_str(), string_to_send.length());
}
