#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include "lcd.h"
void LCD_sendCommand (unsigned char data) {
	PORTA = (PORTA & 0x0F) | (data & 0xF0);	// Zapisanie 4 starszych bitów
	PORTA &= ~(1 << PA0);					// RS = 0
	PORTA |= (1 << PA1);
	_delay_us(1);
	PORTA &= ~(1 << PA1);					// ENABLE = 0
	_delay_us(200);
	PORTA = (PORTA & 0x0F) | (data << 4);	// Zapisanie 4 najmłodszych bitów
	PORTA |= (1 << PA1);
	_delay_us(1);
	PORTA &= ~(1 << PA1);					// ENABLE = 0
	_delay_ms(2);
}

void LCD_init (void) {
	DDRA |= 0xF3;
	_delay_ms(20);
	LCD_sendCommand(0x33);							// Inicjalizacja zgodna z dokumentacją
	_delay_ms(8);
	LCD_sendCommand(0x32);
	_delay_ms(150);
	LCD_sendCommand(0x01);							// Czyszczenie wyświetlacza
	_delay_ms(10);
	LCD_sendCommand(0x28);
	LCD_sendCommand(0x0D);
	LCD_sendCommand(0x06);							// Ustawienie kursora
	LCD_sendCommand(0x80);
}

void LCD_sendChar (unsigned char data) {
	PORTA = (PORTA & 0x0F) | (data & 0xF0);;
	PORTA |= (1 << PA0);
	PORTA |= (1 << PA1);
	_delay_us(1);
	PORTA &= ~(1 << PA1);
	_delay_us(200);
	PORTA = (PORTA & 0x0F) | (data << 4);
	PORTA |= (1 << PA1);
	_delay_us(1);
	PORTA &= ~(1 << PA1);
	_delay_ms(2);
}

void LCD_sendString (char *str) {
	int i;
	for (i = 0; str[i] != 0; i++) LCD_sendChar(str[i]);
}

void pisz_1 (char *str) {
	LCD_sendCommand(0x80);
	LCD_sendString(str);
}
void pisz_2 (char *str) {
	LCD_sendCommand(0xC0);
	LCD_sendString(str);
}
void pisz_xy (char *str, unsigned int wiersz, unsigned int kolumna) {
	unsigned int cmd = 0x00;
	if (wiersz == 0) cmd |= 0x80;
	else cmd |= 0xC0;
	unsigned k = 0;
	while (kolumna > 0) {
		if (kolumna % 2 == 0) cmd &= ~_BV(k);
		else cmd |= _BV(k);
		k++;
		kolumna /= 2;
	}
	LCD_sendCommand(cmd);
	LCD_sendString(str);
}
void LCD_clr_1();
void LCD_clr_2();
void LCD_clr_xy();
void LCD_clear() {
	LCD_sendCommand(0x01);
	_delay_ms(2);
	LCD_sendCommand(0x80);
}
