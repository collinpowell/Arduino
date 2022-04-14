
#ifndef NodeX_h
#define NodeX_h
// some declarations in
// the header file.
#define HIGHX 1
#define LOWX 0

#define OUTPUTX 1
#define INPUTX 0

#define F_CPU 16000000UL // 16 MHz clock speed

#include <avr/io.h>
#include <util/delay.h>

void pinModeX(uint8_t pin, uint8_t mode);
void digitalWriteX(uint8_t pin, uint8_t mode);
uint8_t digitalReadX(uint8_t pin);
void activateInternalPullUp(uint8_t pin);

uint8_t high(uint8_t regist, uint8_t pin);

uint8_t low(uint8_t regist, uint8_t pin);
#endif
