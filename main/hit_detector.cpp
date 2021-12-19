#include <Arduino.h>
#include <algorithm>
#include <sstream>
#include "hit_detector.h"

hit_detector::hit_detector(int alertPin) : indicatorPin(alertPin) {
    //  Try to initialize!
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        failedToInit = true;
    }

    pinMode(alertPin, OUTPUT);
    digitalWrite(alertPin, HIGH);

    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void hit_detector::copySwap(hit_detector& l, hit_detector& r) {
    std::swap(l.mpu, r.mpu);
    std::swap(l.indicatorPin, r.indicatorPin);
}

hit_detector& hit_detector::operator=(hit_detector o) {
    copySwap(*this, o);
    return *this;
}

bool hit_detector::operator!() {
    return failedToInit;
}

uint32_t hit_detector::waitForHit() {
    digitalWrite(indicatorPin, LOW);

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    for (int i = 0; i < 100; ++i) {
        lastNHits[i] = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));
    }

    uint32_t startTime = millis();
    //get stuck waiting for hit, no threading here.
    while(!checkForHit()) { }

    uint32_t endTime = millis();

    digitalWrite(indicatorPin, HIGH);

    return endTime - startTime;
}

float hit_detector::averageMagnitude() {
    float total = 0;
    for (float f : lastNHits) {
        total += f;
    }
    total /= 100;
    return total;
}

bool hit_detector::checkForHit() {
    static int nthHit = 0;
    nthHit %= 100;

    float magnitude;
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // ACCELEROMETER STUFF
    magnitude = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));

    if (abs(magnitude - averageMagnitude()) > hitMagnitudeDelta) {
        Serial.println("hit!");
        hitDetectAccel = magnitude;
        return true;
    }

    lastNHits[nthHit] = magnitude;
    return false;
}

void hit_detector::printData(int hitTime) {
    Serial.println("Hit detection magnitude: " + String(hitDetectAccel) + "m/s^2");
    Serial.println("Running average magnitude: " + String(averageMagnitude()) + "m/s^2");
    String allAverage;
    for (int i = 0; i < 100; ++i) {
        allAverage += String(lastNHits[i]) + String(i == 99 ? "" : ",");
    }
    Serial.println(allAverage);
    Serial.println("Time from light on to hit is " + String(hitTime) + "ms");
}