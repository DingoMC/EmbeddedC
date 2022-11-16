#include <avr/io.h>
#define F_CPU 1000000L
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int cnt = 0;
volatile int l_max = 10;

void zad1(){
	TCCR0 |= _BV(CS00) | _BV(CS02);
	for(int i = 0; i < 10; i++){
		TCNT0 = 159;
		while((TIFR & 0x01)==0);
		TIFR = 0x1;
	}
	TCCR0 = 0;
	PORTA ^= _BV(0);
}

ISR (TIMER0_OVF_vect) {
	cnt++;
	if (cnt >= l_max) {
		PORTA ^= _BV(0);
		cnt = 0;
	}
	TCNT0 = 159;
}
int sw () {
	int i;
	unsigned char cz;
	for(i = 4; i < 8; i++){
		PORTC = ~_BV(i);
		_delay_ms(1);
		cz = ~PINC & 0x0f;
		if (cz) {
			return (i-3) + (cz-1)*4;
		}
	}
	return 0;
}
ISR (INT1_vect) {
	l_max = sw();
}
int main(void)
{
	// zad. 1, 2
	/*TCNT0 = 157;
	TCCR0 = _BV(CS00) | _BV(CS02);
	TIMSK = (1 << TOIE0);
	sei();*/
	// zad. 3
	
	TCNT0 = 159;
	TCCR0 = _BV(CS00) | _BV(CS02);
	TIMSK = (1<<TOIE0);
	GICR = _BV(INT1);
	MCUCR = _BV(ISC11) | _BV(ISC10);	
	sei();
	DDRA = 0xff;
	DDRC = 0xF0;
	PORTC = 0x0F;
    while (1) {
		//zad1();
    }
	return 0;
}

