#include <avr/io.h>
#include "klawiatura.h"
void SW_numer (unsigned int SW_numer) {
	unsigned int bw = (SW_numer - 1) / 4;
	unsigned int bk = 4 + (SW_numer - 1) % 4;
	DDRD &= ~_BV(bw);
	DDRD |= _BV(bk);
	PORTD |= _BV(bk);
}
unsigned int SW_odczyt (unsigned int SW_numer) {
	unsigned int bw = (SW_numer - 1) / 4;
	unsigned int bk = 4 + (SW_numer - 1) % 4;
	uint8_t w = 0x00, k = 0x00;
	if ((PIND & 0x0F) != 0x0F) {
		w = PIND & 0x0F;
		w = (~w & 0x0F);
		DDRD ^= 0xFF;
		PORTD ^= 0xFF;
		_delay_us(2);
		k = PIND & 0xF0;
		k = (~k & 0xF0);
		DDRD ^= 0xFF;
		PORTD ^= 0xFF;
	}
	if (w == _BV(bw) && k == _BV(bk)) return 1;
	return 0;
}
unsigned int SW_czytaj (void) {
	uint8_t w = 0x00, k = 0x00;
	if ((PIND & 0x0F) != 0x0F) {
		w = PIND & 0x0F;
		w = (~w & 0x0F);
		DDRD ^= 0xFF;
		PORTD ^= 0xFF;
		_delay_us(2);
		k = PIND & 0xF0;
		k = (~k & 0xF0);
		DDRD ^= 0xFF;
		PORTD ^= 0xFF;
	}
	return (w | k);
}
