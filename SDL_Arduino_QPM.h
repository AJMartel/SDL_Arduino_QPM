//
//   SDL_Arduino_QuadPower Library
//   SDL_Arduino_QuadPower.h Arduino code 
//   Version 1.1
//   SwitchDoc Labs  June 15, 2015
//
//


#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define QuadPower_ADDRESS                         (0x21)    // 0x21 (Addr=VDD)

/*=========================================================================*/

/*=========================================================================
    REGISTERS (R/W)
    -----------------------------------------------------------------------*/

   #define QuadPower_REGDATA_ADDR                   (0x00) // RegData
   #define QuadPower_REGDIR_ADDR                    (0x01) // Direction
   #define QuadPower_REGPULLUP_ADDR                 (0x02) // Pullups
   #define QuadPower_REGPULLDOWN_ADDR               (0x03) // Pulldowns
   
   #define QuadPower_INTERRUPTMASK_ADDR             (0x05) // Interrupt Mask
   #define QuadPower_SENSEHIGH_ADDR                 (0x06) // Interrupt direction 7-4
   #define QuadPower_SENSELOW_ADDR                  (0x07) // Interrupt direction 3-0
   
   #define QuadPower_INTERRUPTSOURCE_ADDR           (0x08) // Interrupt Source 
   #define QuadPower_EVENTSTATUS_ADDR               (0x09) // Event Status of I/Os
   
   #define QuadPower_REGPLDMODE_ADDR                (0x10) // PLD Mode  
   #define QuadPower_REGPLDPLDTABLE0_ADDR           (0x11) // PLD Truth Table 
   #define QuadPower_REGPLDPLDTABLE1_ADDR           (0x12) // PLD Truth Table  
   #define QuadPower_REGPLDPLDTABLE2_ADDR           (0x13) // PLD Truth Table  
   #define QuadPower_REGPLDPLDTABLE3_ADDR           (0x14) // PLD Truth Table  
   #define QuadPower_REGPLDPLDTABLE4_ADDR           (0x15) // PLD Truth Table  
 
   #define QuadPower_REGADVANCED_ADDR               (0xAB) // Advanced Settings
   

   
/*---------------------------------------------------------------------*/
   #define QuadPower_CONFIG_RESET                    (0x8000)  // Reset Bit
	
   #define QuadPower_REG_IO7                     (0x80)  // Channel IO7 
   #define QuadPower_REG_IO6                     (0x40)  // Channel IO6 
   #define QuadPower_REG_IO5                     (0x20)  // Channel IO5 
   #define QuadPower_REG_IO4                     (0x10)  // Channel IO4 
   #define QuadPower_POWER_CHANNEL_IO3                     (0x08)  // Power Channel IO3
   #define QuadPower_POWER_CHANNEL_IO2                     (0x04)  // Power Channel IO2
   #define QuadPower_POWER_CHANNEL_IO1                     (0x02)  // Power Channel IO1
   #define QuadPower_POWER_CHANNEL_IO0                     (0x01)  // Power Channel IO0
   
   #define QuadPower_INPUT                       (0x01)  // 1 means input
   #define QuadPower_OUTPUT                      (0x00)  // 0 means output
   
    #define QuadPower_OFF                         (0x00)  // 0 means off
    #define QuadPower_ON                          (0x01)  // 1 means on

    #define QuadPower_DISABLE                        (0x01)  // 0 means off
    #define QuadPower_ENABLE                         (0x00)  // 1 means on


   #define QuadPower_REG_SENS_NONE              (0x0)  // None - Interrupt Edge Sensitivity
   #define QuadPower_REG_SENS_RISING            (0x1)  // Rising - Interrupt Edge Sensitivity
   #define QuadPower_REG_SENS_FALLING           (0x2)  // Falling - Interrupt Edge Sensitivity
   #define QuadPower_REG_SENS_BOTH              (0x3)  // None - Interrupt Edge Sensitivity


    
    
    


class SDL_Arduino_QuadPower{
 public:
    SDL_Arduino_QuadPower(uint8_t addr = QuadPower_ADDRESS);
    void begin(void);
    uint8_t readGPIO();
    uint8_t writeGPIO(uint8_t value);
    uint8_t setDirectionGPIOChannel(uint8_t channel, uint8_t direction);
    uint8_t setPullupGPIOChannel(uint8_t channel, uint8_t state);
    uint8_t setPulldownGPIOChannel(uint8_t channel, uint8_t state);
    uint8_t setInterruptMaskGPIOChannel(uint8_t channel, uint8_t state);

    uint8_t enablePowerChannel(uint8_t channel, uint8_t enable);
    uint8_t setPowerChannel(uint8_t channel, uint8_t state);

 private:
    uint8_t QuadPower_i2caddr;
    uint8_t QuadPower_direction;
    uint8_t QuadPower_pullup;
    uint8_t QuadPower_pulldown;
    uint8_t QuadPower_interruptmask;


  
    void wireWriteRegister(uint8_t reg, uint8_t value);
    void wireReadRegister(uint8_t reg, uint8_t *value);


};

