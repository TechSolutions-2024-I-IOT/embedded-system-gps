#ifndef WIFI_BACKEND_MANAGER_H
#define WIFI_BACKEND_MANAGER_H

#include "WiFi.h"
#include <HTTPClient.h>

class WiFiBackendManager {
private:
    HTTPClient client_http;
    const char* ssid;
    const char* password;
    const char* backendUrl;
    int unitBusId;

public:
    WiFiBackendManager();
    WiFiBackendManager(const char* ssid, const char* password, const char* backendUrl);
    void connectWifi();
    void sendData(float latitude, float longitude, float speed);
    void setBusId(int id);
    bool isConnected();
};

#endif
