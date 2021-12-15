#include <Arduino.h>

#include <Wire.h>

#include "CL6017S.h"
#include "SSD1306Wire.h"
#include "AiEsp32RotaryEncoder.h"

#include "images.h"

#define ROTARY_ENCODER_A_PIN 18
#define ROTARY_ENCODER_B_PIN 19
#define ROTARY_ENCODER_BUTTON_PIN 5
#define ROTARY_ENCODER_STEPS 4

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);

#define OLED_ADDR 0x3c
#define OLED_SDA 5
#define OLED_SCL 4

CL6017S radio;
SSD1306Wire display(OLED_ADDR, OLED_SDA, OLED_SCL);

/**
 * TODO:
 * encoder control:
 * - scroll encoder - frequency +/-
 * - press+scroll - volume +/-
 * - double-press - save frequency
 * 
 * screen control:
 * - display current volume, frequency
 */
void setup()
{
  Wire.begin();
  Serial.begin(115200);

  Serial.println("CL6017S Demo");

  display.init();
  // draw welcome logo
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.display();
  delay(3000); // wait for 3 seconds

  //radio.debugEnable();
  radio.init();
  radio.enable(true);
  radio.seekUp();
  radio.setVolume(14);
}

char buff[25];
void updateScreen()
{
  // clear the display
  display.clear();

  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // battery level
  sprintf(buff, "Frequency: %d", radio.getFrequency());
  display.drawString(0, 10, buff);

  // moisture sensor level
  sprintf(buff, "Volume: %d", radio.getVolume());
  display.drawString(0, 26, buff);
  display.display();
}

void loop()
{
  updateScreen();
}