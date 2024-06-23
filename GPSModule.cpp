#include "GPSModule.h"
#include <Arduino.h>
#include "NMEA.h"

void GPSModule::begin(long baudRate) {
    Serial.begin(baudRate);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    Serial.println("Data received from GPS Fake:");
}

void GPSModule::readData() {

    while (Serial2.available()) {
        char serialData = Serial2.read();
        
        if (gps.decode(serialData)) {
            if (gps.gprmc_status() == 'A') {
                velocidadeGPS.valor = gps.gprmc_speed(KMPH);
            } else {
                velocidadeGPS.valor = 0;
            }

            latitude = gps.gprmc_latitude();
            longitude = gps.gprmc_longitude();

            Serial.println();
            Serial.println();

            Serial.print(" Latitude: ");
            Serial.println(latitude, 8);

            Serial.print("Longitude: ");
            Serial.println(longitude, 8);

            Serial.print("    Speed: ");
            Serial.print(velocidadeGPS.valor);
            Serial.println(" Km/h");
        }
    }
}

float GPSModule::getLatitude() {
    return latitude;
}

float GPSModule::getLongitude() {
    return longitude;
}

float GPSModule::getSpeed() {
    return velocidadeGPS.valor;
}