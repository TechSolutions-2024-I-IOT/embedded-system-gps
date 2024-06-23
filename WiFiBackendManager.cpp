#include "WiFiBackendManager.h"
#include <Arduino.h>
#include "config.h"

WiFiBackendManager::WiFiBackendManager()
  : ssid(WIFI_SSID), password(WIFI_PASSWORD), backendUrl(EDGE_BACKEND_URL), busId(BUS_ID) {}

WiFiBackendManager::WiFiBackendManager(const char* ssid, const char* password, const char* backendUrl)
  : ssid(ssid), password(password), backendUrl(backendUrl), busId(0) {}

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
    busId = id;
}

void WiFiBackendManager::sendData(float latitude, float longitude) {
    if (!isConnected()) {
      Serial.println("WiFi not connected. Reconnecting...");
      connectWifi();
    }

    // String url = String(backendUrl) + "?latitude=" + String(latitude) + "&longitude=" + String(longitude);
    // client_http.begin(url);
    // int httpResponseCode = client_http.GET();
    // if (httpResponseCode > 0) {
    //   Serial.println("HTTP Response code: " + String(httpResponseCode));
    // } else {
    //   Serial.println("Error on sending GET: " + String(client_http.errorToString(httpResponseCode).c_str()));
    // }
    // client_http.end();
}

bool WiFiBackendManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
