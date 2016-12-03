// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>

// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
h_plant_stages_json("plant_stages", "JSON array of growth stages, each with lighting and air constraints"),
h_grow_start_at("start_at", "Seconds from UNIX epoch of when the grow was started."),
h_grow_aborted("aborted", "True = stop growing"),
growLightNode("grow_light", "switch"),
fanNode("fan", "switch")
{
  growManagerSetupRan = false;
}

void GrowManager::setup() {
  Serial << "GrowManager..." << endl;

  plant_stages_json = h_plant_stages_json.get();
  grow_start_at = h_grow_start_at.get();
  grow_aborted = h_grow_aborted.get();

  // Refactor these
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  fanOn = false;
  fanNode.advertise("on");
  fanNode.setProperty("on").send("false");

  pinMode(GROW_LIGHT_PIN, OUTPUT);
  digitalWrite(GROW_LIGHT_PIN, LOW);
  growLightOn = false;
  growLightNode.advertise("on");
  growLightNode.setProperty("on").send("false");
}

void GrowManager::loop(float air_temp_f) {
  if (timeStatus() != timeSet || grow_aborted) {
    return;
  }
  // need to run after homie setup to send off values on bootup
  if (!growManagerSetupRan) {
    growManagerSetupRan = true;
    setup();
  }

    StaticJsonBuffer<450> jsonBuffer;
    JsonArray& plant_stages = jsonBuffer.parseArray(plant_stages_json);
    if (!plant_stages.success())
    {
        Serial << "parsing plant stages failed!" << endl;
        return;
    }

    for (auto& plant_stage : plant_stages) {
       long from_abs = (long)plant_stage["from_rel"] + grow_start_at;
       long to_abs = (long)plant_stage["to_rel"] + grow_start_at;

       if (now() >= from_abs && now() < to_abs) {
         /* If this is the current plant stage */

        //  Control Grow Light
         if (second() >= (int)plant_stage["light_on_at"] && second() < (int)plant_stage["light_off_at"]) {
           if (!growLightOn) {
             Serial << "Time: " << second() << " Grow light is " << (growLightOn ? "on" : "off") << ", turning ON" << endl;
             growLightOn = true;
             growLightNode.setProperty("on").send("true");
             digitalWrite(GROW_LIGHT_PIN, HIGH);
           }
         } else {
           if (growLightOn) {
              Serial << "Time: " << second() << " Grow light is " << (growLightOn ? "on" : "off") << ", turning OFF" << endl;
              growLightOn = false;
              growLightNode.setProperty("on").send("false");
              digitalWrite(GROW_LIGHT_PIN, LOW);
          }
         }


        //  Control Fan
        if (!isnan(air_temp_f)) {
          if (!fanOn && (air_temp_f > (float)plant_stage["air_temp_high"])) {
            Serial << "Temp: " << air_temp_f << " Fan is " << (fanOn ? "on" : "off") << ", turning ON" << endl;
            fanOn = true;
            fanNode.setProperty("on").send("true");
            digitalWrite(FAN_PIN, HIGH);
          }
        } else {
          if (fanOn && (air_temp_f < (float)plant_stage["air_temp_low"])) {
             Serial << "Temp: " << air_temp_f << " Fan is " << (fanOn ? "on" : "off") << ", turning OFF" << endl;
             fanOn = false;
             fanNode.setProperty("on").send("false");
             digitalWrite(FAN_PIN, LOW);
         }
        }



       }
    }
}
