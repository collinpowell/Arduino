#include "NodeLcd.h"
#include "NodeX.h"
NodeLcd::NodeLcd(uint8_t rs, uint8_t enable,
                 uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                 uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  Serial.begin(9600);
  rsPin = rs;
  enablePin = enable;
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3;
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7;

  pinModeX(rs, OUTPUTX);
  pinModeX(enable, OUTPUTX);

  // Sequence 4,5,  6,0,1,2,0,1,2,3

  pinModeX(d0, OUTPUTX);

  DDRC = high(DDRC, d1);
  DDRC = high(DDRC, d2);
  DDRC = high(DDRC, d3);

  DDRB = high(DDRB, d4);
  DDRB = high(DDRB, d5);
  DDRB = high(DDRB, d6);
  DDRB = high(DDRB, d7);
}

void NodeLcd::lcdInit() {
  lcdCmd(0x38); _delay_ms(5);
  lcdCmd(0x02); _delay_ms(5);
  lcdCmd(0x01); _delay_ms(5);
  lcdCmd(0x06); _delay_ms(5);
  lcdCmd(0x0C); _delay_ms(5);
  lcdCmd(0x80); _delay_ms(5);
}


void NodeLcd::pinHigh(uint8_t pin) {
  PORTD |= (1 << pin);
}
void NodeLcd::pinLow(uint8_t pin) {
  PORTD &= ~(1 << pin);
}

/* Works
  void NodeLcd::lcdWrite(unsigned char cmd) {
  if ((cmd & ( 1 << 0 )) >> 0 == 0) {
    PORTD = low(PORTD, _data_pins[0]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 0 )) >> 0 == 1) {
    PORTD = high(PORTD, _data_pins[0]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 1 )) >> 1 == 0) {
    PORTC = low(PORTC, _data_pins[1]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 1 )) >> 1 == 1) {
    PORTC = high(PORTC, _data_pins[1]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 2 )) >> 2 == 0) {
    PORTC = low(PORTC, _data_pins[2]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 2 )) >> 2 == 1) {
    PORTC = high(PORTC, _data_pins[2]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 3 )) >> 3 == 0) {
    PORTC = low(PORTC, _data_pins[3]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 3 )) >> 3 == 1) {
    PORTC = high(PORTC, _data_pins[3]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 4 )) >> 4 == 0) {
    PORTB = low(PORTB, _data_pins[4]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 4 )) >> 4 == 1) {
    PORTB = high(PORTB, _data_pins[4]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 5 )) >> 5 == 0) {
    PORTB = low(PORTB, _data_pins[5]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 5 )) >> 5 == 1) {
    PORTB = high(PORTB, _data_pins[5]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 6 )) >> 6 == 0) {
    PORTB = low(PORTB, _data_pins[6]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 6 )) >> 6 == 1) {
    PORTB = high(PORTB, _data_pins[6]);
    Serial.println(1);
  }

  if ((cmd & ( 1 << 7 )) >> 7 == 0) {
    PORTB = low(PORTB, _data_pins[7]);
    Serial.println(0);
  } else if ((cmd & ( 1 << 7 )) >> 7 == 1) {
    PORTB = high(PORTB, _data_pins[7]);
    Serial.println(1);
  }

  }*/

void NodeLcd::lcdWrite(unsigned char cmd) {
  for (byte i = 0; i < 8; i++) {
    if ((cmd & ( 1 << i )) >> i == 0) {
      if (i == 0) {
        PORTD = low(PORTD, _data_pins[i]);
      } else if (i > 0 && i <= 3) {
        PORTC = low(PORTC, _data_pins[i]);
      } else if ( i > 3) {
        PORTB = low(PORTB, _data_pins[i]);
      }
    } else if ((cmd & ( 1 << i )) >> i == 1) {
      if (i == 0) {
        PORTD = high(PORTD, _data_pins[i]);
      } else if (i > 0 && i <= 3) {
        PORTC = high(PORTC, _data_pins[i]);
      } else if ( i > 3) {
        PORTB = high(PORTB, _data_pins[i]);
      }
    }
  }
}

void NodeLcd::lcdCmd(unsigned char cmd) {
  // write to D0 - D7
  lcdWrite(cmd);

  pinLow(rsPin);
  pinHigh(enablePin);
  _delay_ms(1);
  pinLow(enablePin);
}
void NodeLcd::lcdData(unsigned char data) {
  // write to D0 - D7
  lcdWrite(data);
  pinHigh(rsPin);
  pinHigh(enablePin);
  _delay_ms(1);
  pinLow(enablePin);
}
