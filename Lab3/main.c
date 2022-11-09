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
	pisz_1("Test W1");
	pisz_2("Test W2");
	_delay_ms(3000);
	LCD_clear();
	_delay_ms(500);
	pisz_xy("Test XY", 0, 5);
	pisz_xy("Test 2", 1, 3);
	_delay_ms(3000);
	LCD_clr_1();
	_delay_ms(500);
	LCD_clr_2();
	_delay_ms(500);
	pisz_xy("Test Clear XY", 0, 1);
	_delay_ms(3000);
	LCD_clr_xy(0, 5);
	_delay_ms(500);
	LCD_clear();
	_delay_ms(500);
	pisz_xy("Test OK", 1, 4);
    while (1) 
    {
    }
}
