#include "NodeX.h"


uint8_t high(uint8_t regist, uint8_t pin) {
  return regist | (1 << pin);
}

uint8_t low(uint8_t regist, uint8_t pin) {
  return regist & ~ (1 << pin);
}

// Set Digital Pin As Input Or Output
void pinModeX(uint8_t pin, uint8_t mode) {
  if (mode == HIGHX) {
    DDRD = high(DDRD,pin);
    return DDRD;
  } else if (mode == LOWX) {
    DDRD = low(DDRD,pin);
    return DDRD;
  }
}

void digitalWriteX(uint8_t pin, uint8_t mode) {
  if (mode == HIGHX) {
    PORTD = high(PORTD,pin);
    return PORTD;
  } else if (mode == LOWX) {
    PORTD = low(PORTD,pin);
    return PORTD;
  }

}

uint8_t digitalReadX(uint8_t pin) {
  if (PIND & (1 << pin)) {
    return HIGHX;
  } else if (PIND & ~(1 << pin)) {
    return LOWX;
  }
}

void activateInternalPullUp(uint8_t pin) {
  PORTD = high(PORTD,pin);
}
