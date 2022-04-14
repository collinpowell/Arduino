#ifndef NodeLcd_h
#define NodeLcd_h

#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

class NodeLcd{
  
  public:
    NodeLcd(uint8_t rs, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);  

    void lcdInit();

    void lcdCmd(unsigned char cmd);
    void lcdData(unsigned char data);
  private:
    uint8_t rsPin; // LOW: command.  HIGH: character.
    uint8_t enablePin; // activated by a HIGH pulse.

    uint8_t _data_pins[8];
    void lcdWrite(unsigned char data);
    void pinHigh(uint8_t pin);
    void pinLow(uint8_t pin);


    
};
#endif
