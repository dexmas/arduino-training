/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <GyverEncoder.h>
#include <buttonMinim.h>

#define OLED_SOFT_BUFFER_64
#define USE_MICRO_WIRE

#include <GyverOLED.h>

#define LED_FIRST 12
#define LED_COUNT 8

#define ENC_CLK 4
#define ENC_DT 2
#define ENC_SW 3

#define BTN_PIN A3

#define POT_PIN A6
#define OPT_PIN A2

#define IR_RC_PIN A7
#define IR_TX_PIN A7

Encoder enc1(ENC_CLK, ENC_DT, ENC_SW);
GyverOLED oled;
buttonMinim butt1(BTN_PIN);

byte enc = 0;

void setup()
{
  Serial.begin(9600);
  
  for(int i=LED_FIRST;i>=(LED_FIRST - LED_COUNT); i--)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    delay(1000);
    digitalWrite(i, HIGH);
  }

  enc1.setType(TYPE2);

  oled.init(OLED128x64);
  enc = 0;

  delay(1000);
}

void loop()
{
  enc1.tick();
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
  if (enc1.isHold())
  {
    oled.inverse(true);
  }

  oled.print("ENC");
  oled.inverse(false);
  oled.print(" ");
  oled.println();

  if (enc1.isLeft()) 
  {
    enc++;
  }
  else
  if (enc1.isRight()) 
  {
    enc--;
  }
  
  oled.scale1X();
  oled.print("POT: ");
  oled.print(analogRead(POT_PIN));
  oled.print("     ");
  oled.println();
  oled.print("OPT: ");
  oled.print(analogRead(OPT_PIN));
  oled.print("     ");
  oled.println();
  oled.print("ENC: ");
  oled.print(enc);
  oled.print("     ");

  oled.update();

  //if (enc1.isRight()) Serial.println("Encoder right"); 
  //if (enc1.isLeft()) Serial.println("Encoder left");
  //if (enc1.isClick()) Serial.println("Encoder click"); 

  //Serial.print("Pot: ");
  //Serial.print(analogRead(POT_PIN)); 
  //Serial.print("\t\t Light: ");
  //Serial.print(analogRead(OPT_PIN));
  //Serial.println();
}
