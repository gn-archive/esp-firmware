// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>
#define LEDPIN D4

// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
h_plant_stages_json("plant_stages", "JSON array of growth stages, each with lighting and air constraints"),
h_grow_start_at("start_at", "Seconds from UNIX epoch of when the grow was started."),
h_grow_aborted("aborted", "True = stop growing")
{
}

void GrowManager::setup() {
  Serial << "GrowManager..." << endl;
  pinMode(D4, OUTPUT);
  plant_stages_json = h_plant_stages_json.get();
  grow_start_at = h_grow_start_at.get();
  grow_aborted = h_grow_aborted.get();
}

void GrowManager::loop() {
  if (timeStatus() == timeSet && !grow_aborted) {

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
           digitalWrite(LEDPIN, LOW);
         } else {
           digitalWrite(LEDPIN, HIGH);
         }


         // Control Fan
        //  if (temp > (int)plant_stage["air_temp_high"])) {
        //    //  fan on
        //  }
         //
        //  if (temp < (int)plant_stage["air_temp_low"])) {
        //    /* fan off */
        //  }



       }
    }
  }
}
