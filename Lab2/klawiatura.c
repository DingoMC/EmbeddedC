#include <avr/io.h>
#include "klawiatura.h"
void SW_numer (unsigned int SW_numer) {
	unsigned int w = (SW_numer - 1) / 4;
	unsigned int k = (SW_numer - 1) % 4;
	DDRC |= w;
	DDRC &= ~k;
}
unsigned int SW_odczyt (unsigned int SW_numer) {
	if ((PINC | ~_BV(SW_numer / 4)) && (PINC & _BV(4 + SW_numer % 4))) return 0;
	return 1;
}
unsigned int SW_czytaj (void) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (SW_odczyt(i * 4 + j)) return i * 4 + j;
		}
	}
	return 0;
}
