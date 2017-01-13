// Usable Pins
// D0 = NodeMCU built in LED, also deepsleep stuff
// D1 = GPIO5
// D2 = GPIO4
// D4 = GPIO2 (ESP8266 onboard LED, also serial input)
// D5 = (GPIO 14)
// D6 = GPIO12
// D7 = GPIO13
// D8 = GPIO15 (input with pulldown resistor/tied to gnd)
// SD2 (GPIO 10)
// input:
// SD1 (GPIO 9)


#define COM_BUS_THIS_ID 44
#define COM_BUS_ARDUINO_ID 45

#define AIR_SENSOR_DHT_PIN D0
#define FAN_PIN D1
#define GROW_LIGHT_PIN D2
#define AIR_PUMP_PIN D3
#define HOMIE_STATUS_PIN D4
#define WATER_PUMP_PIN D5
#define WATER_LEVEL_PIN D6
#define COM_BUS_PIN D7

#define AIR_SENSOR_DHT DHT11

#define SEND_STATS_INTERVAL 10*1000
#define WATER_LEVEL_MIN 4.5
#define AIR_TEMP_OVERHEAT 80.0
#define DEFAULT_GROW_LIGHT_ON_AT 6
#define DEFAULT_GROW_LIGHT_OFF_AT 18
