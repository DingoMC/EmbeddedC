#include <avr/io.h>
#define F_CPU 1000000L
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int cnt = 0;
volatile int led_time = 5;

ISR (TIMER0_OVF_vect) {
	TCNT0 = 159;
	if (++cnt == 10) {
		PORTA ^= 0x01;
		cnt = 0;
	}
}
ISR (TIMER0_OVF_vect) {
	TCNT0 = 159;
	if (++cnt == >= led_time) {
		PORTB ^= 0x01;
		cnt = 0;
	}
}
ISR (INT0_vect) {
	_delay_ms(15);
	GIFR |= _BV(INTF0);
	if ((PIND & 0x04) == 0) {
		uint8_t i = ((~PINA) & 0x0F);
		uint8_t w = 0, k = 0, p = 0;
		while (i) {
			w++;
			i = i >> 1;
		}
		while (k < 4) {
			PORTA |= _BV(k+4);
			_delay_us(2);
			if ((PINA & 0x0F) == 0x0F) break;
			PORTA &= ~_BV(k+4);
			k++;
		}
		PORTA &= 0x0F;
		p = (w - 1) * 4 + k;
		if (p < 14) led_time = p + 1;
		else if (p == 14) TCCR0 &= ~(_BV(CS00) | _BV(CS02));
		else {
			cnt = 0;
			TCNT0 = 159;
			TCCR0 |= _BV(CS00) | _BV(CS02);
		}
	}
}
int main(void)
{
	// Zadanie 1
	DDRA |= 0x01;
	PORTA |= 0x01;
	TCNT0 = 159;
	TCCR0 = _BV(CS00) | _BV(CS02);
	while (1) {
		while (!(TIFR & (1 << TOV0)));
		TIFR |= (1 << TOV0);
		TCNT0 = 159;
		if (++cnt == 10) {
			PORTA ^= 0x01;
			cnt = 0;
		}
	}
	// Zadanie 2
	DDRA |= 0x01;
	PORTA |= 0x01;
	TCNT0 = 159;
	TIMSK |= _BV(TOIE0);
	TIFR |= _BV(TOV0);
	TCCR0 |= _BV(CS00) | _BV(CS02);
	sei();
	// Zadanie 3
	DDRA = 0xF0;
	PORTA = 0x0F;
	DDRC |= 0x01;
	PORTC |= 0x01;
	DDRD &= ~_BV(2);
	PORTD |= 0x40;
	MCUCR |= _BV(ISC01);
	GICR |= _BV(INT0);
	GIFR |= _BV(INTF0);
	TCNT0 = 159;
	TIMSK |= _BV(TOIE0);
	TIFR |= _BV(TOV0);
	TCCR0 |= _BV(CS00) | _BV(CS02);
	sei();
	while (1) {
		
	}
	return 0;
}

