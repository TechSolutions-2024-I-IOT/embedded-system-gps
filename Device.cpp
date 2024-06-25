#include "Device.h"
#include <Arduino.h>
#include "config.h"  

Device::Device()
  : wifiManager(WIFI_SSID, WIFI_PASSWORD, EDGE_BACKEND_URL) { 
}

void Device::setup() {
    gpsModule.begin(115200);
    wifiManager.connectWifi();
    wifiManager.setBusId(BUS_ID);
    lastSendTime = 0;
}

void Device::loop() {
    gpsModule.readData();
    
    gpsData.latitude = gpsModule.getLatitude();
    gpsData.longitude = gpsModule.getLongitude();
    gpsData.speed = gpsModule.getSpeed();

    // Enviar datos al backend
    unsigned long currentTime = millis();
    if (currentTime - lastSendTime >= sendInterval) {
        wifiManager.sendData(gpsData.latitude, gpsData.longitude, gpsData.speed);
        lastSendTime = currentTime;
    }
}
