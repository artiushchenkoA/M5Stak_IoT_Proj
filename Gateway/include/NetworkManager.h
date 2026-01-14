#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <functional>

class NetworkManager {
private:
    WiFiClient espClient;
    PubSubClient client;
    const char* _ssid;
    const char* _pass;
    const char* _server;
    const char* _id;

public:
    NetworkManager(const char* ssid, const char* pass, const char* server, const char* id);
    void begin(std::function<void(char*, uint8_t*, unsigned int)> callback);
    void loop();
    void publish(String topic, String payload);
    void subscribe(String topic);
};
#endif