// PA0-7 -> D0-7
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#define L0_DLY 500
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (9600 * 16UL))) - 1)

void UART_Init (void) {
	UCSRB |= (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

unsigned char UART_GetChar () {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

void UART_SendChar (char ch) {
	while (!(UCSRA & (1<<UDRE)));
	UDR = ch;
}

void UART_SendString (char *str) {
	unsigned char c = 0;
	while (str[c] != 0) {
		UART_SendChar(str[c]);
		c++;
	}
}

static unsigned cnt = 0;

ISR (TIMER0_COMP_vect) {
	if (++cnt == L0_DLY / 20) {
		cnt = 0;
		PORTA ^= 0x01;
	}
}

ISR (USART_RXC_vect) {
	static char x;
	x = UDR;
	if ((int) x >= 49 && (int) x <= 55) {
		PORTA ^= 0b00000001 << (x - 48);
		UART_SendString("Wcisnieto [");
		UART_SendChar(x);
		UART_SendString("]\r\n");
	}
	else if (x == 'c') PORTA &= 0b00000001;
	else if (x == 's') PORTA |= 0b11111110;
	else UART_SendString("Bledny klawisz!\r\n");
}

int main(void) {
	// Zadanie 1
	UART_Init();
	UART_SendString("Marcin Basak\r\n");
	
	// Zadanie 2
	char c;
	UART_SendString("Nacisnij klawisz [d]: ");
	c = UART_GetChar();
	if (c == 'd') UART_SendString("Znak OK\r\n");
	else UART_SendString("Bledny Znak!\r\n");
	
	// Zadanie 3
	DDRA = 0b11111111;	// LED in
	PORTA = 0b00000000;	// Led wył.
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);
	TIMSK |= 1 << OCIE0;
	TIFR |= 1 << OCF0;
	OCR0 = 78;
	sei();
    while (1) {
		
    }
}

