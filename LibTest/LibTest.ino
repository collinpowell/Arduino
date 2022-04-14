#include "NodeLcd.h"
#include "NodeX.h"



int main() {
  Serial.begin(9600);
  NodeLcd lcd(5,6,7,0,1,2,0,1,2,3);
  lcd.lcdInit();
  char u[6] = {'F','U','C','K','Y','U'};
  for(byte i = 0; i < 6;i++){
     lcd.lcdData(u[i]);
  }
  pinModeX(2, OUTPUTX);
  pinModeX(3, OUTPUTX);
  pinModeX(4, INPUTX);
  activateInternalPullUp(4);
  while (1) {
    //Serial.println(digitalReadX(4));
    if (digitalReadX(4) == LOWX) {
      digitalWriteX(2, HIGHX);
      digitalWriteX(3, LOWX);
      _delay_ms(100);
      digitalWriteX(2, LOWX);
      digitalWriteX(3, HIGHX);
      _delay_ms(500);

       
    }

  }
  return 0;
}
