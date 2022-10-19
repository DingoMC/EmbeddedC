#include <avr/io.h>
#include "led.h"

void LED_konf (unsigned int LED_number) {
	DDRB |= _BV(LED_number); // ustawienie pinu jako wyjście
}
void LED_Set (unsigned int LED_number) {
	PORTB |= _BV(LED_number);
}
void LED_Clear (unsigned int LED_number) {
	PORTB &= ~_BV(LED_number);
}
void LED_Toggle (unsigned int LED_number) {
	PORTB ^= _BV(LED_number);
}
unsigned int LED_GetState (unsigned int LED_number) {
	if (PINB & _BV(LED_number)) return 1;
	return 0;
}
