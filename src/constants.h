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


// #define AIR_SENSOR_DHT_PIN D0
#define I2C_SDA D1
#define I2C_SCL D2
// D3 is ESP8266 Reset pin (GPIO0). Ground to reset
#define HOMIE_STATUS_PIN D4
#define WATER_TEMP_PIN D5

#define SHIFT_DATA_PIN D6
#define SHIFT_LATCH_PIN D7
#define SHIFT_CLOCK_PIN D8


#define SEND_STATS_INTERVAL 10*1000
#define WATER_LEVEL_MIN 4.5
#define AIR_TEMP_OVERHEAT 95.0
#define DEFAULT_GROW_LIGHT_ON_AT 6
#define DEFAULT_GROW_LIGHT_OFF_AT 18
#define DEFAULT_TIMEZONE_ID "America/Los_Angeles"
