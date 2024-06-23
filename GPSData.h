#ifndef GPS_DATA_H
#define GPS_DATA_H

class GPSData {
public:
    float latitude;
    float longitude;
    float speed;

    GPSData() : latitude(0), longitude(0), speed(0) {}
};

#endif