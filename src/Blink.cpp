/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Encoder.h>

#define OLED_SOFT_BUFFER_64
#define USE_MICRO_WIRE

#include <GyverOLED.h>

#define LED_FIRST 12
#define LED_COUNT 8

#define ENC_CLK 4
#define ENC_DT 2
#define ENC_BTN 3

#define BTN_PIN A3

#define POT_PIN A6
#define OPT_PIN A2

#define IR_RC_PIN A7
#define IR_TX_PIN A7

Encoder enc(ENC_DT, ENC_CLK);
GyverOLED oled;

byte encVal = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(ENC_BTN, INPUT_PULLUP);
  
  for(int i=LED_FIRST;i>=(LED_FIRST - LED_COUNT); i--)
  {
    pinMode(i, OUTPUT);
    //digitalWrite(i, LOW);
    //delay(1000);
    digitalWrite(i, HIGH);
  }

  oled.init(OLED128x64);
  encVal = 0;

  delay(100);
}

void loop()
{
  int newenc = enc.read() >> 2;
  if(encVal != newenc)
  {
    encVal = newenc;
  }

  oled.clear();
  oled.home();

  oled.scale2X();
  oled.inverse(false);
  oled.print(" ");
  if (!digitalRead(BTN_PIN)) 
  {
    oled.inverse(true);
  }
  oled.print("BTN");
  
  oled.inverse(false);
  oled.print("  ");
  if (!digitalRead(ENC_BTN))
  {
    oled.inverse(true);
  }

  oled.print("ENC");
  oled.inverse(false);
  oled.print(" ");
  oled.println();
  
  oled.scale1X();
  oled.print("POT: ");
  oled.println(analogRead(POT_PIN));
  oled.print("OPT: ");
  oled.println(analogRead(OPT_PIN));
  oled.print("ENC: ");
  oled.println(encVal);

  oled.update();

  for(int i=0; i<8; i++)
  {
    boolean state = ((encVal >> i) & 0x01) != 0;
    int led = LED_FIRST - i;
    digitalWrite(led, state ? LOW : HIGH);
  }
}
