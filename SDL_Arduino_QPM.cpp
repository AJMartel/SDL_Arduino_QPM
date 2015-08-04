//
//   SDL_Arduino_QuadPower Library
//   SDL_Arduino_QuadPower.cpp Arduino code - runs in continuous mode
//   Version 1.1
//   SwitchDoc Labs   June 15, 2015
//
//




#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#include "SDL_Arduino_QPM.h"

/**************************************************************************/
/*! 
    @brief  Sends a single command byte over I2C
*/
/**************************************************************************/
void SDL_Arduino_QuadPower::wireWriteRegister (uint8_t reg, uint8_t value)
{
  //Serial.print("I2C Addr= 0x");
  //Serial.println(QuadPower_i2caddr,HEX);
  //Serial.print("WriteAddress=0x");
  //Serial.print(reg, HEX);
  //Serial.print(" value=0x");
  //Serial.println(value, HEX);
  
  Wire.beginTransmission(QuadPower_i2caddr);
  #if ARDUINO >= 100
    Wire.write(reg);
    delay(100);
    // Register
    Wire.write(value & 0xFF);              // Lower 8-bits
  #else
    Wire.send(reg);                        // Register
    Wire.send(value & 0xFF);               // Lower 8-bits
  #endif
  Wire.endTransmission();
}

/**************************************************************************/
/*! 
    @brief  Reads a8 bit values over I2C
*/
/**************************************************************************/
void SDL_Arduino_QuadPower::wireReadRegister(uint8_t reg, uint8_t *value)
{

  Wire.beginTransmission(QuadPower_i2caddr);
  #if ARDUINO >= 100
    Wire.write(reg);                       // Register
  #else
    Wire.send(reg);                        // Register
  #endif
  Wire.endTransmission();
  
 

  Wire.requestFrom(QuadPower_i2caddr, (uint8_t)1);
//Serial.print("Wire.available =");
//Serial.println(Wire.available());
  #if ARDUINO >= 100
    // Shift values to create properly formed integer
    *value = Wire.read();
  #else
    // Shift values to create properly formed integer
    *value = Wire.receive();
  #endif
}



/**************************************************************************/
/*! 
    @brief  Instantiates a new SDL_Arduino_QuadPower class
*/
/**************************************************************************/
SDL_Arduino_QuadPower::SDL_Arduino_QuadPower(uint8_t addr) {
    
    QuadPower_i2caddr = addr;

    QuadPower_direction = 0xff;
    QuadPower_pullup = 0;
    QuadPower_pulldown = 0;
    QuadPower_interruptmask = 0;
    
    
    


 
}

/**************************************************************************/
/*! 
    @brief  Setups the HW (defaults to 32V and 2A for calibration values)
*/
/**************************************************************************/
void SDL_Arduino_QuadPower::begin() {
  Wire.begin();    

  //Serial.print("address="); Serial.println(QuadPower_i2caddr);

  
    uint8_t value;
    
    // Disable all channels - make inputs
    
    value = 0xFF;
    QuadPower_direction = value;
    
    wireWriteRegister(QuadPower_REGDIR_ADDR, value);
    
    //Serial.print("QuadPower_REGDIR_ADDR=");
    //Serial.println(value,HEX);
    
    
    
    // write all 0 to GPIO

    writeGPIO(0);
    
}

/**************************************************************************/
/*! 
    @brief  Reads 8 bits of GPIO
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::readGPIO() {
  uint8_t value;
  wireReadRegister(QuadPower_REGDATA_ADDR, &value);
    //Serial.print("GPIO Read Raw=");
    //Serial.println(value,HEX);

  return value;
}

/**************************************************************************/
/*! 
    @brief  Writes upper 4 bits of GPIO
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::writeGPIO(uint8_t value) {

    uint8_t currentvalue;
    uint8_t newvalue;
    wireReadRegister(QuadPower_REGDATA_ADDR, &currentvalue);
    
    newvalue = currentvalue &0x0F | value &0xF0;
    
    wireWriteRegister(QuadPower_REGDATA_ADDR, newvalue);
    //Serial.print("GPIO Write Raw=");
    //Serial.println(newvalue,HEX);
    

  return value;
}

/**************************************************************************/
/*! 
    @brief  Set direction of GPIO channel
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::setDirectionGPIOChannel(uint8_t channel, uint8_t direction) {
  uint8_t value;
    
    // protect power lines from setting
    
    channel = channel & 0xF0;
  
  if (direction == QuadPower_INPUT)
  {
       value = QuadPower_direction | channel;
       
 
  }
  else
  {
    // assume output
       value = QuadPower_direction & ((~channel) &0xFF) ; 
    
  }

  QuadPower_direction = value;

  wireWriteRegister(QuadPower_REGDIR_ADDR, value);

   //Serial.print("GPIO Direction=");
   //Serial.println(value,HEX);

  return QuadPower_direction;
}
/**************************************************************************/
/*!
 @brief  Power Management
 
 */
/**************************************************************************/

/**************************************************************************/
/*!
 @brief  enable Power Channel
 
 */
/**************************************************************************/

uint8_t SDL_Arduino_QuadPower::enablePowerChannel(uint8_t channel, uint8_t enable)
{
    uint8_t value;
    
    if (enable == QuadPower_DISABLE)
    {
        value = QuadPower_direction | channel;
        
        
    }
    else
    {
        // assume output
        value = QuadPower_direction & ((~channel) &0xFF) ;
        
    }
    
    QuadPower_direction = value;
    
    wireWriteRegister(QuadPower_REGDIR_ADDR, value);
 
    //Serial.print("QuadPower_Channel=");
    //Serial.println(channel,HEX);
    //Serial.print("QuadPower_enable=");
    //Serial.println(enable,HEX);
    //
    //Serial.print("QuadPower_REGDIR_ADDR=");
    //Serial.println(value,HEX);
    
    return QuadPower_direction;

    
    
}

/**************************************************************************/
/*!
 @brief  Control Power Channel
 
 */
/**************************************************************************/

uint8_t SDL_Arduino_QuadPower::setPowerChannel(uint8_t channel, uint8_t state)
{
    
    uint8_t value;
    
    value =  SDL_Arduino_QuadPower::readGPIO();
    if (state == QuadPower_ON)
    {
        value = value | channel;
        
    }
    else
        value = value & ((~channel) &0xFF);
    
    wireWriteRegister(QuadPower_REGDATA_ADDR, value);
    //Serial.print("GPIO Power Channel Set=");
    //Serial.println(value,HEX);
    
    
    
}


/**************************************************************************/
/*! 
    @brief  Set Pullup of GPIO channel
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::setPullupGPIOChannel(uint8_t channel, uint8_t state) {
  uint8_t value;
    
    // protect power lines from setting
    
    channel = channel & 0xF0;
    
  if (state == QuadPower_OFF)
  {
      value = QuadPower_pullup & ((~channel) &0xFF) ; 
  }
  else
  {
    // assume output
    value = QuadPower_pullup | channel;
    
  }


  QuadPower_pullup = value;
  wireWriteRegister(QuadPower_REGPULLUP_ADDR, value);
    //Serial.print("GPIO Pullup=");
    //Serial.println(value,HEX);

  return QuadPower_pullup;
}

/**************************************************************************/
/*! 
    @brief  Set Pulldown of GPIO channel
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::setPulldownGPIOChannel(uint8_t channel, uint8_t state) {
  uint8_t value;
  
    
    // protect power lines from setting
    
    channel = channel & 0xF0;
    
    
  if (state == QuadPower_OFF)
  {
      value = QuadPower_pulldown & ((~channel) &0xFF) ; 
  }
  else
  {
    // assume output
    value = QuadPower_pulldown | channel;
    
  }

  QuadPower_pulldown = value;
  wireWriteRegister(QuadPower_REGPULLDOWN_ADDR, value);
    //Serial.print("GPIO Pulldown=");
    //Serial.println(value,HEX);

  return QuadPower_pulldown;
}


/**************************************************************************/
/*! 
    @brief  Set Interrupt Mask of GPIO channel
*/
/**************************************************************************/
uint8_t SDL_Arduino_QuadPower::setInterruptMaskGPIOChannel(uint8_t channel, uint8_t state) {
  uint8_t value;
   if (state == QuadPower_OFF)
  {
      value = QuadPower_interruptmask & ((~channel) &0xFF) ; 
  }
  else
  {
    // assume output
    value = QuadPower_interruptmask | channel;
    
  }
 

  QuadPower_interruptmask = value;
  wireWriteRegister(QuadPower_INTERRUPTMASK_ADDR, value);
    //Serial.print("GPIO Interrupt Mask=");
    //Serial.println(value,HEX);

  return QuadPower_interruptmask;
}





 


