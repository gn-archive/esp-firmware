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

      String payload_str;
       for(uint16_t i = 0; i < length; ++i)
          payload_str += (char)payload[i];

      Serial.print("Received ");
      Serial.print(length);
      Serial.print(" bytes: ");
      Serial.println(payload_str);

      // payload_router(payload_str.c_str());
  });
}

void ComBusClass::loop() {

      bus.update();
      bus.receive(1000);
}

void ComBusClass::send(int to_device_id, String string_to_send) {
  bus.send(to_device_id, string_to_send.c_str(), string_to_send.length());
}
