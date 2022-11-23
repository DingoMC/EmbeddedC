/*
 * GccApplication1.c
 *
 * Created: 23.11.2022 10:20:12
 * Author : Student_PL
 */ 
// PA0-7 -> D0-7
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (9600 * 16UL))) - 1)

void UART_Init (void) {
	UCSRB |= (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}
unsigned char UART_RxChar () {
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}

void UART_TxChar (char ch) {
	while (! (UCSRA & (1<<UDRE)));
	UDR = ch;
}

void UART_SendString (char *str) {
	unsigned char j=0;
	while (str[j]!=0) {
		UART_TxChar(str[j]);
		j++;
	}
}

static unsigned char cnt = 0;

ISR (TIMER0_COMP_vect) {
	if (++cnt == 50) {
		cnt = 0;
		PORTA ^= 0b00000001;
	}
}

ISR (USART_RXC_vect) {
	static char x;
	x = UDR;
	if ((int) x >= 49 && (int) x <= 55) {
		x++;
		PORTA ^= 0b00000001 << (x - 49);
	}
	else if(x == 'c') {
		PORTA = 0b00000000;
	}
	else if(x == 's') {
		PORTA = 0b11111111;
	}
	else {
		UART_SendString("Wcisnieto zly klawisz");
	}
}

int main(void) {
	// Zadanie 1
    UART_Init();
    UART_SendString("Marcin Basak\r\n");
	
	// Zadanie 2
	char c;
	UART_SendString("Nacisnij klawisz [d]:");
	c = UART_RxChar();
	if (c == 'd') UART_SendString("Znak OK\r");
	else UART_SendString("Bledny Znak!\n");
	
	// Zadanie 3
	DDRA = 0b11111111;	// LED in
	PORTA = 0b00000000;	// Led wył.
	TCCR0 |= 1 << WGM01;
	TCCR0 &= ~(1 << WGM00);
	OCR0 = 156;
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TIMSK |= 1 << OCIE0;
	TIFR |= 1 << OCF0;
	sei();
    while (1) {
		
    }
}

