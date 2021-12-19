#include "seven_seg.h"
#include "hit_detector.h"

seven_seg sevenSegment { 22 };
hit_detector* hitDetector;

void setup(void) {
    Serial.begin(115200);
    while (!Serial) {
        delay(10); // will pause Zero, Leonardo, etc until serial console opens
    }

    hitDetector = new hit_detector(8);

    pinMode(13, OUTPUT);
    while(!(*hitDetector)) {
        delete hitDetector;
        Serial.println("no hit detector registered");
        digitalWrite(13, HIGH);
        delay(100);
        digitalWrite(13, LOW);
        delay(100);
        hitDetector = new hit_detector(8);
    }

    sevenSegment.light();

    delay(100);
}

void loop() {
    Serial.println("waiting for hit");
    uint32_t hitTime = hitDetector->waitForHit();
    hitDetector->printData(hitTime);

    //hit has been detected
    sevenSegment++;
    sevenSegment.light();

    int randWait = random(1000, 5000);
    delay(randWait);
}
