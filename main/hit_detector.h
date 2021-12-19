#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class hit_detector {
private:
    Adafruit_MPU6050 mpu;
    bool failedToInit = false;
    int indicatorPin;
    float hitMagnitudeDelta = 10;
    float lastNHits[100];
    void copySwap(hit_detector& l, hit_detector& r);
    float averageMagnitude();
public:
    float hitDetectAccel = 0;
    hit_detector(int alertPin);
    ~hit_detector() = default;
    bool checkForHit();
    uint32_t waitForHit();
    hit_detector& operator=(hit_detector o);
    bool operator!();
    void printData(int hitTime);
};