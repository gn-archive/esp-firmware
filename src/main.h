#include "Arduino.h"
#include <constants.h>
#include <SPI.h>
#include <PJON.h>
#include <Homie.h>
#include <NtpManager.hpp>
#include <GrowProgram.hpp>
#include <ESP8266WiFi.h>
#include <Notifier.hpp>


void receiver_function(uint8_t *payload, uint16_t length, const PacketInfo &packet_info) {
  Serial.print("Received: ");
  for(uint8_t i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}

PJON<SoftwareBitBang> bus(COM_BUS_DEVICE_ID); // <Strategy name> bus(selected device id)

NtpManager ntp_manager;
GrowProgram grow_program;

void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      grow_program.sendCurrentState();
    break;
  }
}
