// ESP8266 connections
#define SHIFT_CLOCK_PIN D0
#define I2C_SDA D1
#define I2C_SCL D2
// D3 is factory reset pin. Ground for 5 seconds to clear flash.
#define HOMIE_STATUS_PIN D4
#define ONE_WIRE_BUS D5

#define SHIFT_DATA_PIN D6
#define AIR_SENSOR_PIN D7
#define SHIFT_LATCH_PIN D8


// Shift register connections
#define GROW_LIGHT_SR_PIN 0
#define WATER_PUMP_SR_PIN 1
// #define AIR_PUMP_SR_PIN 2
// #define FAN_SR_PIN 3

// Software configuration

#define SEND_SENSOR_DATA_INTERVAL 10*1000
#define WATER_LEVEL_MIN 4.5
#define AIR_TEMP_OVERHEAT 95
#define DEFAULT_DARK_HOURS "14,15,16,17,"
#define TIMEZONE_OFFSET -8 // UTC
