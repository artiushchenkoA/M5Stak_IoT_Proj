// Main application for the SensorNode:

#include <M5Stack.h>
#include "Config.h"
#include "NetworkManager.h"
#include "Sensors.h"

String topicPIR = "m5/sensor/a";
String topicHall = "m5/sensor/b";
int interval = 2000;
unsigned long lastTime = 0;

NetworkManager net(WIFI_SSID, WIFI_PASS, MQTT_SERVER, "M5_Sensor_Node");
PIRSensor pSensor(PIN_PIR);
HallSensor hSensor(PIN_HALL);

// Function logEvent prints the results of read on LCD
void logEvent(String msg) {
    static int line = 0;
    if (line > 8) { // clear LCD if the number or records exceeds screen size
        M5.Lcd.fillRect(0, 100, 320, 140, BLACK);
        line = 0;
    }
    M5.Lcd.setCursor(0, 100 + (line * 15));
    M5.Lcd.setTextSize(1);
    M5.Lcd.printf("> %lu: %s", millis()/1000, msg.c_str());
    line++;
}

void onMsg(char* t, uint8_t* p, unsigned int l) {
    String msg = ""; for(int i=0; i<l; i++) msg += (char)p[i];
    if (msg.startsWith("FREQ:")) {
        interval = msg.substring(5).toInt();
        logEvent("New Freq: " + String(interval) + "ms");
    }
}

void setup() {
    M5.begin();
    M5.Power.begin();
    M5.Lcd.clear();
    
    pSensor.init(); 
    hSensor.init();
    
    logEvent("Connecting WiFi...");
    net.begin(onMsg);
    net.subscribe(topicSystem);
    logEvent("MQTT Connected!");
}

void loop() {
    net.loop();
    M5.update();

    if (millis() - lastTime > interval) {
        int vPIR = pSensor.getValue();
        int vHall = hSensor.getValue();

        // Sending and logging
        net.publish(topicPIR, String(vPIR));
        net.publish(topicHall, String(vHall));
        logEvent("Sent A=" + String(vPIR) + " B=" + String(vHall));

        // Output the current values
        M5.Lcd.setCursor(0, 40);
        M5.Lcd.setTextSize(2);
        M5.Lcd.printf("PIR: %d  Hall: %d   \n", vPIR, vHall);
        M5.Lcd.printf("Freq: %d ms   ", interval);
        
        lastTime = millis();
    }
}