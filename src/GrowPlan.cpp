// Manages Grow Plan
#include <GrowPlan.hpp>

// Constructor - creates a GrowPlan
// and initializes the member variables and state
GrowPlan::GrowPlan() :
grow_plan_json("growplan", "JSON representation of the grow plan.")
{
	grow_plan_json.setDefaultValue("").setValidator([] (const char* candidate) {
		if (candidate == NULL) {
			return false;
		}
		return true;
	});
}

void GrowPlan::setup() {
  Serial << "GrowPlan: Setup" << endl;
}

void GrowPlan::loop() {

}

String GrowPlan::read() {
	if (grow_plan_json.wasProvided()) {
		return grow_plan_json.get();
	} else {
		return "{}";
	}
}

bool GrowPlan::refresh() {
	// Todo
	Serial << "GrowPlan: Failed to refresh.";
	return false;
}
