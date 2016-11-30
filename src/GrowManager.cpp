// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>
#define LEDPIN D4

// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
plant_stages_json("plant_stages", "JSON array of growth stages, each with lighting and air constraints"),
grow_start_at("start_at", "Seconds from UNIX epoch of when the grow was started."),
grow_aborted("aborted", "True = stop growing")
{
}

void GrowManager::setup() {
  Serial << "GrowManager..." << endl;
  pinMode(D4, OUTPUT);
}

void GrowManager::loop() {
  if (timeStatus() == timeSet && !grow_aborted.get()) {

    DynamicJsonBuffer jsonBuffer;
    JsonArray& plant_stages = jsonBuffer.parseArray(plant_stages_json.get());
    for (auto& plant_stage : plant_stages) {
       long from_abs = (long)plant_stage["from_rel"] + grow_start_at.get();
       long to_abs = (long)plant_stage["to_rel"] + grow_start_at.get();

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
