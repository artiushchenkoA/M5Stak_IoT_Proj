// Implementation file for Network Logic: handles WiFi and MQTT connections with unique client IDs.

#include "NetworkManager.h"

// Function NetworkManager constructor initializes connection parameters. 
// @param ssid WiFi name, @param pass WiFi password, @param server MQTT IP, @param id Unique Client ID.
NetworkManager::NetworkManager(const char* ssid, const char* pass, const char* server, const char* id) 
    : client(espClient), _ssid(ssid), _pass(pass), _server(server), _id(id) {}


// Function begin connects the device to the WiFi network. 
// @param callback The function to execute when a new MQTT message arrives.
void NetworkManager::begin(std::function<void(char*, uint8_t*, unsigned int)> callback) {
    WiFi.begin(_ssid, _pass);
    while (WiFi.status() != WL_CONNECTED) { delay(500); }
    client.setServer(_server, 1883);
    client.setCallback(callback);
}
// Function loop ensures the MQTT connection stays active and re-subscribes to topics if disconnected.
void NetworkManager::loop() {
    if (!client.connected()) {
        if (client.connect(_id)) {
            client.subscribe("m5/system/cfg");
            client.subscribe("m5/sensor/a");
            client.subscribe("m5/sensor/b");
        }
    }
    client.loop();
}

void NetworkManager::publish(String topic, String payload) {
    client.publish(topic.c_str(), payload.c_str());
}

void NetworkManager::subscribe(String topic) {
    client.subscribe(topic.c_str());
}