#include <main.h>

GrowProgram grow_program;

// See Homie API for Homie Events
void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      // When MQTT is connected, upload the current state to MQTT
      grow_program.uploadCurrentState();
      Sensors.uploadCurrentState();
    break;
  }
}


void setup()
{
  // This function is run once on boot

  Wire.begin();        // join i2c bus (address optional for master)

  delay(200);
  Serial.begin(74880);

  Homie.disableLogging(); // before Homie.setup()

  Serial.println(F("=============================================================================="));
  Serial.println(F("=============================================================================="));

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  Homie_setFirmware("node-os", "0.0.15"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent); // function from above

  Homie.setup();

  // Also need to setup these, (setting the pinMode, etc)
  System.setup();
  Sensors.setup();
  grow_program.setup();

}

void loop()
{
  // Loops forever
    Homie.loop(); // IoT, MQTT library

    System.loop();
    Sensors.loop();
    grow_program.loop();
}
