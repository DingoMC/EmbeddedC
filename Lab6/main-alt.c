#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define UBRR_FROM_BAUDRATE(BAUDRATE)            ((unsigned long)F_CPU / ((unsigned long)(BAUDRATE * 16UL) - 1UL))
#define UBRR_FROM_BAUDRATE_SPEED_X2(BAUDRATE)   ((unsigned long)F_CPU / ((unsigned long)(BAUDRATE * 8UL) - 1UL))

#define UART_DATABITS_5     0
#define UART_DATABITS_6     (1 << UCSZ0)
#define UART_DATABITS_7     (1 << UCSZ1)
#define UART_DATABITS_8     ((1 << UCSZ1) | (1 << UCSZ0))

#define UART_PARITY_NONE    0
#define UART_PARITY_EVEN    (1 << UPM1)
#define UART_PARITY_ODD     ((1 << UPM1) | (1 << UPM0))

#define UART_STOPBITS_1     0
#define UART_STOPBITS_2     (1 << USBS)

#define UART_RX_ENABLE      (1 << RXEN)
#define UART_TX_ENABLE      (1 << TXEN)

#define UART_SPEED_X2       (1 << U2X)
#define UART_SPEED_X1       0

#define UART_INT_RX_COMPLETE    (1 << RXCIE)
#define UART_INT_TX_COMPLETE    (1 << TXCIE)
#define UART_INT_UDR_READY      (1 << UDRIE)

void
UART_Open(uint16_t ubrr, uint8_t speed, uint8_t data_format, uint8_t rx_tx_enable)
{
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;
	UCSRA |= speed;
	UCSRB |= rx_tx_enable;
	UCSRC = (1 << URSEL) | data_format;
}

void
UART_Wait_T(void)
{
	while (!(UCSRA & (1 << UDRE)));
}


void
UART_Wait_R(void)
{
	while (!(UCSRA & (1 << RXC)));
}

void
UART_Putc(uint8_t data)
{
	UART_Wait_T();
	UDR = data;
}

uint8_t
UART_Getc(void)
{
	UART_Wait_R();
	return UDR;
}

void
UART_Puts(char* str)
{
	while (*str)
	{
		UART_Putc(*str);
		++str;
	}
}

void
UART_Enable_Interrupt(uint8_t interrupts)
{
	UCSRB |= interrupts;
}

void
UART_Disable_Interrupt(uint8_t interrupts)
{
	UCSRB &= ~interrupts;
}

volatile uint8_t timer_overflow_counter = 0;

int
main(void)
{
	UART_Open(UBRR_FROM_BAUDRATE(9600), UART_SPEED_X1, UART_DATABITS_8 | UART_STOPBITS_1 | UART_PARITY_NONE, UART_TX_ENABLE | UART_RX_ENABLE);
    
	// DO ZADANIA 3
	UART_Enable_Interrupt(UART_INT_RX_COMPLETE);
	DDRA = 0xFF;
	
	// f_cpu = 8 000 000 Hz
	// f_timer = 7 812.5 Hz
	// T_timer = 128us
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);
	OCR0 = 78;
	TIFR |= (1 << OCF0);
	TIMSK |= (1 << OCIE0);
	
	sei();
	//
	
	while (1) 
    {
		/*
		ZADANIE 1
		_delay_ms(1000);
		UART_Puts("XD\r\n");
		*/
		
		/*
		ZADANIE 2
		UART_Puts("Wcisnij klawisz [q]\r\n");
		uint8_t ch = UART_Getc();
		if (ch == 'q')
		{
			UART_Puts("OK\r\n");
		}
		else
		{
			UART_Puts("Niepoprawny znak\r\n");
		}
		*/	
    }
}

ISR(TIMER0_COMP_vect)
{
	if (++timer_overflow_counter == 100)
	{
		timer_overflow_counter = 0;
		PORTA ^= 0x01;
	}
}

ISR(USART_RXC_vect)
{
	uint8_t ch = UDR;
	if (ch > '0' && ch < '8')
	{
		PORTA ^= (1 << (ch - 48));
		UART_Putc('[');
		UART_Putc(ch);
		UART_Puts("]\r\n");
	}
	else if (ch == 'c')
	{
		PORTA &= 0x01;
	}
	else if (ch == 's')
	{
		PORTA |= 0xFE;
	}
	else
	{
		UART_Puts("Niepoprawny przycisk!\r\n");
	}
}
