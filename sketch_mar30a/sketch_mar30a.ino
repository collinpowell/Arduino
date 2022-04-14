#define OUTPUT_RUN_ID (4)
// The run-indication LED: 0 = LED off, 1 = LED on
#define F_CPU 16000000UL // Clock frequency (as unsigned long) 
#include <avr/io.h> // Recognizes pins, ports, registers, etc.
#include <util/delay.h> // Required for _delay_ms function 
int main(void) {
  DDRB = (1 << OUTPUT_RUN_ID); // Set run indication LED to output mode
  while (1) {
    PORTB |= (1 << OUTPUT_RUN_ID); // LED on
    _delay_ms(200); // Hold for approx. 500 ms
    PORTB &= ~(1 << OUTPUT_RUN_ID); // LED off
    _delay_ms(200); // Hold for approx. 500 ms
  }
}
