/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/WindyCity_IOT/Labs/Lab8/src/Lab8.ino"
void setup();
void loop();
#line 1 "d:/WindyCity_IOT/Labs/Lab8/src/Lab8.ino"
SYSTEM_THREAD(ENABLED);
#include <Wire.h>
#include "oled-wing-adafruit.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"

VCNL4040 sensor;
OledWingAdafruit display;

void setup()
{
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  Wire.begin(); //Join i2c bus

  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println();
  display.display();

  if (sensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1); //Freeze!
  }

}

void loop()
{
  display.loop();
  unsigned int proxValue = sensor.getProximity(); 
  Serial.println(proxValue);
  //very far away
  if (proxValue < 100)
  {
    analogWrite(D6, 0);
    analogWrite(D7, 255);
    analogWrite(D8, 0);
  }
  //close ish
  else if (proxValue < 1000)
  {
    analogWrite(D6, 0);
    analogWrite(D7, 128);
    analogWrite(D8, 255);
  }
  //invading the sensors personal space
  else
  {
    analogWrite(D6, 0);
    analogWrite(D7, 0);
    analogWrite(D8, 255);
  }

  if (display.pressedA())
  {

    sensor.powerOnProximity(); //Power down the proximity portion of the sensor
    sensor.powerOffAmbient(); //Power up the ambient sensor

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    
    String output = "Proximity Value: "; 
    output += (String) proxValue;

    display.println(output);
    display.display();

  }

  if (display.pressedB())
  {

    sensor.powerOffProximity(); //Power down the proximity portion of the sensor
    sensor.powerOnAmbient(); //Power up the ambient sensor

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    
    unsigned int ambi = sensor.getAmbient(); 
    String output = "Ambient Light Value: "; 
    output += (String) ambi;

    display.println(output);
    display.display();

  }

  if (display.pressedC())
  {

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    unsigned int id = sensor.getID(); 
    String output = "I2C Address: "; 
    output += (String) id;

    display.println(output);
    display.display();
  }


}

