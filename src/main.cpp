#include <Arduino.h>

#include <Wire.h>
#include "CL6017S.h"

CL6017S radio;

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  Serial.println("CL6017S Demo");

  radio.debugEnable();
  radio.init();
  radio.enable(true);
  radio.seekUp();
  radio.setVolume(14);
}

void loop()
{
  Serial.print("Playing: ");
  Serial.println(radio.getFrequency());
  delay(60 * 1000);
}