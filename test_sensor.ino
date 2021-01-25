/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

int distance;

VL53L0X sensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  sensor.setTimeout(100);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
    Serial.println(sensor.readRangeContinuousMillimeters());
    // Serial.println("mm");
    // if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

    // Serial.println();
}
