// Configuration file: contains network credentials, MQTT server details, and hardware pin assignments.

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// WiFi Settings
const char* WIFI_SSID = "iPhone(Artemii)";
const char* WIFI_PASS = "123456789";

// MQTT Settings: Home computer acts as the MQTT broker.
const char* MQTT_SERVER = "172.20.10.4"; // Private IP adress inside the network
const int MQTT_PORT = 1883;

// Topic Management
extern String topicPIR;   
extern String topicHall;  
const String topicSystem = "m5/system/cfg"; 

// Hardware Pins for M5Stack Fire
#define PIN_HALL 36  // Port B (Black) - supports analogRead.
#define PIN_PIR  16  // Port C (Blue) - digital.
// ------------------------

// InfluxDB Cloud Credentials
#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "_7NnxzwhS8h4KDANV_FhJ8fipR24cm9VL_HHVuPPjvPkSoozBm3zyDG_NYDyb41--N8-YbQQLnQLhbXUfmgLGQ=="
#define INFLUXDB_ORG "artyuart@fit.cvut.cz"
#define INFLUXDB_BUCKET "m5_data"

#endif