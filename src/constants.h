// ESP8266 connections
#define SHIFT_CLOCK_PIN D0
#define I2C_SDA D1
#define I2C_SCL D2
// D3 is factory reset pin. Ground for 5 seconds to clear flash.
#define HOMIE_STATUS_PIN D4

#define SHIFT_DATA_PIN D6
#define ONE_WIRE_BUS D5
#define AIR_SENSOR_PIN D7
#define SHIFT_LATCH_PIN D8

// HW controller devices
#define HWC_BUS_ID 45
#define GROW_LIGHT 13
#define PELTIER 9
#define PELTIER_FAN 6
#define WATER_PUMP 5
#define AIR_SENSOR 2
// #define FAN_SR 3



// Software configuration
#define SEND_SENSOR_DATA_INTERVAL 10*1000
#define WATER_LEVEL_MIN 4.5
#define AIR_TEMP_OVERHEAT 95
#define DEFAULT_DARK_HOURS "14,15,16,17,"
#define WATER_PUMP_DURATION 25
#define TIMEZONE_OFFSET -7 // PDT

#define PELTIER_OFF_TEMP 74
#define PELTIER_MAX_POWER_TEMP 80
#define PELTIER_INTERPOLATION_RANGE (PELTIER_MAX_POWER_TEMP - PELTIER_OFF_TEMP)
