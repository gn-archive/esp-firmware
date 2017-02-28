#define AIR_SENSOR_TYPE DHT22
// ESP8266 connections
#define AIR_SENSOR_PIN D0
#define I2C_SDA D1
#define I2C_SCL D2
// D3 is factory reset pin. Ground for 5 seconds to clear flash.
#define HOMIE_STATUS_PIN D4
#define WATER_TEMP_PIN D5

#define SHIFT_DATA_PIN D6
#define SHIFT_LATCH_PIN D7
#define SHIFT_CLOCK_PIN D8


// Shift register connections
#define GROW_LIGHT_SR_PIN 0
#define WATER_PUMP_SR_PIN 1
// #define AIR_PUMP_SR_PIN 2
// #define FAN_SR_PIN 3

// Software configuration
#define WATER_PUMP_ON_DURATION_MS 60 * 60*1000
#define WATER_PUMP_OFF_DURATION_MS 15 * 60*1000

// #define WATER_PUMP_ON_DURATION_MS 2000
// #define WATER_PUMP_OFF_DURATION_MS 1000

#define SEND_STATS_INTERVAL 10*1000
#define WATER_LEVEL_MIN 4.5
#define AIR_TEMP_OVERHEAT 95.0
#define DEFAULT_GROW_LIGHT_ON_AT 6
#define DEFAULT_GROW_LIGHT_OFF_AT 18
#define TIMEZONE_OFFSET -8 // PST
