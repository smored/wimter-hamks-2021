// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TM1637.h>

Adafruit_MPU6050 mpu; // accelerometer
TM1637 tm(21, 20); // 7 seg

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  //  Try to initialize!
  pinMode(13, OUTPUT);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
  }

 // LED pin init
  for (int i = 0; i < 12; i += 2) { 
    pinMode(i + 43, OUTPUT);  
  }
  
 //7 seg init
 tm.begin();
 tm.setBrightness(4);
 
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}


void loop() {
  static float magnitude;
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // ACCELEROMETER STUFF
  magnitude = sqrt(a.acceleration.x*a.acceleration.x + a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z);
  Serial.print(magnitude);
  Serial.println("");

  static int i = 0; i += 2;
  i %= 12;
  for (int j = 0; j < 12; j += 2) {
    digitalWrite((((j + i) % 12) + 43), j == 0 ? LOW : HIGH);
    // Serial.println("Pin " + String((((j + i) % 12) + 43)) + " is " + (j == 0 ? "on" : "off"));
  }


  // 7 SEGMENT STUFF
    tm.display(1234);
    
  //delay(50);
}
