#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include "NMEA.h"

#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

class GPSModule {
private:
    NMEA gps;
    union {
        char bytes[4];
        float valor;
    } velocidadeGPS;

    float latitude;
    float longitude;

public:
    GPSModule() : gps(GPRMC) {}
    
    void begin(long baudRate);
    void readData();
    float getLatitude();
    float getLongitude();
    float getSpeed();
};

#endif