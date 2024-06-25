#ifndef DEVICE_H
#define DEVICE_H

#include "GPSModule.h"
#include "GPSData.h"
#include "WiFiBackendManager.h"

class Device {
private:
    GPSModule gpsModule;
    GPSData gpsData;
    WiFiBackendManager wifiManager;
    unsigned long lastSendTime;
    const unsigned long sendInterval = 10000;

public:
    Device();
    void setup();
    void loop();
};

#endif
