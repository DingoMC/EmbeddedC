#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include "led.h"
#include "klawiatura.h"

int main(void)
{
    for (int i = 0; i < 8; i++) LED_konf(i);
	for (int i = 0; i < 8; i++) {
		LED_Set(i);
		_delay_ms(200);
	}
	for (int i = 7; i >= 0; i--) {
		LED_Clear(i);
		_delay_ms(200);
	}
    while (1) 
    {
		// Testowanie funkcji LED
		/*for (int i = 0; i < 8; i++) {
			LED_Toggle(i);
			_delay_ms(100);
			if (LED_GetState(4) == 1) LED_Toggle(4);
		}*/
		// Testowanie klawiatury
		/*for (int i = 0; i < 16; i++) {
			if (SW_odczyt(i)) LED_Set(i % 8);
			else LED_Clear(i % 8);
		}*/
    }
}
