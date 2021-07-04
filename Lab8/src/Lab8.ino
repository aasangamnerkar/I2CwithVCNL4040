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
  //loop
  display.loop();
  
  //read proximity sensor
  unsigned int proxValue = sensor.getProximity(); 
  Serial.println(proxValue);

  // I swapped the ports for Red and Blue so the wires didn't tangle in each other
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
  

  //print proximity value when button A pressed
  if (display.pressedA())
  {
    //init sensors
    sensor.powerOnProximity(); //Power down the proximity portion of the sensor
    sensor.powerOffAmbient(); //Power up the ambient sensor
    

    //reset display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    
    //format string
    String output = "Proximity Value: "; 
    output += (String) proxValue;

    //output to display
    display.println(output);
    display.display();

  }

  //print proximity value when button A pressed
  if (display.pressedB())
  {
    //init sensors
    sensor.powerOffProximity(); //Power down the proximity portion of the sensor
    sensor.powerOnAmbient(); //Power up the ambient sensor

    //reset display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    
    //get and format ambient light value
    unsigned int ambi = sensor.getAmbient(); 
    String output = "Ambient Light Value: "; 
    output += (String) ambi;

    //output to display
    display.println(output);
    display.display();

  }
  
  // button C pressed
  if (display.pressedC())
  {
    //reset display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    
    //get id and format string
    unsigned int id = sensor.getID(); 
    String output = "I2C Address: "; 
    output += (String) id;

    //output to display
    display.println(output);  
    display.display();
  }


}

