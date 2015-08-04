

// SDL_Arduino_QPM_Test
// Version 1.1 6/15/15

#include <Wire.h>

#include "SDL_Arduino_QPM.h"


SDL_Arduino_QuadPower QuadPower;


void setup() {
  
  
    Wire.begin();

    Serial.begin(9600);
    // put your setup code here, to run once:
  
  
    byte error, address;
    int nDevices;
  
    Serial.println("");
    Serial.println("--------------------------");
    Serial.println("SDL_Arduino_QPM_Test");
    Serial.println("Version 1.1");
    
    
    QuadPower.begin();
/*
    nDevices = 0;
    for(address = 1; address < 127; address++ ) 
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
  
      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address<16) 
          Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("");
  
        nDevices++;
      }
      else if (error==4) 
      {
        Serial.print("Unknow error at address 0x");
        if (address<16) 
          Serial.print("0");
        Serial.println(address,HEX);
      }    
    }
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
    else
      Serial.println("done\n");
*/
}

void loop() {
  
    byte value;
 
  // Enable Channels
  QuadPower.enablePowerChannel(QuadPower_POWER_CHANNEL_IO0, QuadPower_ENABLE);  
  QuadPower.enablePowerChannel(QuadPower_POWER_CHANNEL_IO1, QuadPower_ENABLE);
  QuadPower.enablePowerChannel(QuadPower_POWER_CHANNEL_IO2, QuadPower_ENABLE);
  QuadPower.enablePowerChannel(QuadPower_POWER_CHANNEL_IO3, QuadPower_ENABLE);
  
  QuadPower.setDirectionGPIOChannel(QuadPower_REG_IO7, QuadPower_OUTPUT);
  value = QuadPower.readGPIO();
  Serial.print("------>>>> Initial GPIO Value =");
  Serial.println(value, HEX);

    // turn on I07 too
    QuadPower.writeGPIO(0x80);
    
while (1)
  {
  

    
    Serial.println("----------------");
    // turn on I07 too
    QuadPower.writeGPIO(0x80);
    Serial.println("Turn on LSW0");
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO0, QuadPower_ON);
    delay(3000);
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO0, QuadPower_OFF);
        Serial.println("Turn on LSW1");
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO1, QuadPower_ON);
    delay(3000);
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO1, QuadPower_OFF);
        Serial.println("Turn on LSW2");
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO2, QuadPower_ON);
    delay(3000);
    
    // turn off I07 too
    QuadPower.writeGPIO(0x00);
    
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO2, QuadPower_OFF);
    Serial.println("Turn on LSW3");
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO3, QuadPower_ON);
    delay(3000);
    QuadPower.setPowerChannel(QuadPower_POWER_CHANNEL_IO3, QuadPower_OFF);

  }
  

}
