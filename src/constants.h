#include <env.h>

// ESP8266 connections
#define I2C_SDA D1
#define I2C_SCL D2
// D3 is factory reset pin. Ground for 5 seconds to clear flash.
#define HOMIE_STATUS_PIN D4



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
