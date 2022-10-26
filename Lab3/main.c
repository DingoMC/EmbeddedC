#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include "lcd.h"
/*
	PA0 - RS, PA1 - E, PA4-7 - D4-7 (JP29)
*/
int main(void)
{
    _delay_ms(15);
	LCD_init();
	/*
	pisz_1("Test W1");
	pisz_2("Test W2");
	_delay_ms(5000);
	LCD_clear();*/
	pisz_xy("Elo", 0, 5);
    while (1) 
    {
    }
}
