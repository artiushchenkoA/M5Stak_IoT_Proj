// Main application for the Gateway: processes incoming sensor data and syncs with InfluxDB Cloud.

#include <M5Stack.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include "Config.h"
#include "NetworkManager.h"

NetworkManager net(WIFI_SSID, WIFI_PASS, MQTT_SERVER, "M5_Gateway");
InfluxDBClient influx(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Function onMsg processes MQTT messages, implements the frequency control logic, and writes to the DB.
// @param topic The MQTT topic, @param payload The message body, @param length Data length.
void onMsg(char* t, uint8_t* p, unsigned int l) {
    String msg = ""; for(int i=0; i<l; i++) msg += (char)p[i];
    String topic = String(t);

    M5.Lcd.printf("MQTT In: %s -> %s\n", topic.c_str(), msg.c_str());

// Logic: If motion detected (PIR=1), set Node frequency to 100ms, else 2000ms.
    if (topic == "m5/sensor/a") {
        if (msg == "1") net.publish("m5/system/cfg", "FREQ:100");
        else net.publish("m5/system/cfg", "FREQ:2000");
    }
    Point row("measurements");
    row.addTag("device", "SensorNode_1");
    if (topic == "m5/sensor/a") row.addField("pir_state", msg.toInt());
    else row.addField("hall_value", msg.toFloat());
// Function writePoint sends the packaged data point to InfluxDB Cloud.
    if (influx.writePoint(row)) {
        M5.Lcd.setTextColor(GREEN);
        M5.Lcd.println(" > InfluxDB: OK");
    } else {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.printf(" > Influx Error: %s\n", influx.getLastErrorMessage().c_str());
    }
    M5.Lcd.setTextColor(WHITE);
}

// Function setup initializes hardware, WiFi, and verifies the Cloud database connection.
void setup() {
    M5.begin();
    M5.Power.begin();
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("GATEWAY DEBUG MODE");
    M5.Lcd.setTextSize(1);

    M5.Lcd.print("WiFi: Connecting...");
    net.begin(onMsg);
    M5.Lcd.println(" [OK]");

    M5.Lcd.print("MQTT: Subscribing...");
    net.subscribe("m5/sensor/a");
    net.subscribe("m5/sensor/b");
    M5.Lcd.println(" [OK]");

    M5.Lcd.print("InfluxDB Cloud: Connecting...");
    if (influx.validateConnection()) {
        M5.Lcd.println(" [OK]");
    } else {
        M5.Lcd.setTextColor(RED);
        M5.Lcd.printf(" [FAIL: %s]\n", influx.getLastErrorMessage().c_str());
        M5.Lcd.setTextColor(WHITE);
    }
}
// Function loop maintains the MQTT network state and processes system updates.
void loop() {
    net.loop();
    M5.update();
}