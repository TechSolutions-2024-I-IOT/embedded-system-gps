#include "WiFiBackendManager.h"
#include <Arduino.h>
#include "config.h"

WiFiBackendManager::WiFiBackendManager()
        : ssid(WIFI_SSID), password(WIFI_PASSWORD), backendUrl(EDGE_BACKEND_URL), unitBusId(BUS_ID) {}

WiFiBackendManager::WiFiBackendManager(const char* ssid, const char* password, const char* backendUrl)
        : ssid(ssid), password(password), backendUrl(backendUrl), unitBusId(0) {}

void WiFiBackendManager::connectWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
}

void WiFiBackendManager::setBusId(int id) {
    unitBusId = id;
}

void WiFiBackendManager::sendData(float latitude, float longitude, float speed) {
    if (!isConnected()) {
        Serial.println("WiFi not connected. Reconnecting...");
        connectWifi();
    }

    String jsonData = "{\"unitBusId\":" + String(unitBusId) +
                      ",\"latitude\":" + String(latitude, 6) +
                      ",\"longitude\":" + String(longitude, 6) +
                      ",\"speed\":" + String(speed) + "}";

    Serial.println("Sending data to backend:");
    Serial.println("URL: " + String(backendUrl));
    Serial.println("Data: " + jsonData);

    client_http.begin(backendUrl);
    client_http.addHeader("Content-Type", "application/json");

    int httpCode = client_http.POST(jsonData);

    if (httpCode > 0) {
        String payload = client_http.getString();
        Serial.println("Status code: " + String(httpCode));
        Serial.println("Response: " + payload);
    } else {
        Serial.println("Error sending data to backend");
        Serial.println("Error: " + client_http.errorToString(httpCode));
    }

    client_http.end();
}

bool WiFiBackendManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
