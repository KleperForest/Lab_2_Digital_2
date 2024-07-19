#define F_CPU 16000000UL

#include "LCD.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

////////////////////////////////////////////////////
// Definimos Pines
////////////////////////////////////////////////////
//Data
#define D0 PB1
#define D1 PB3
// Estos no son del puerto D para poder utilizar Rx y Tx
#define D2 PD2
#define D3 PD3
#define D4 PD4
#define D5 PD5
#define D6 PD6
#define D7 PD7
//RS
#define RS PB0
//E
#define Enable PB1
// R/W va a tierra.


////////////////////////////////////////////////////
// 4Bits.
////////////////////////////////////////////////////

void initLCD4bits(){}

////////////////////////////////////////////////////
// 8Bits.
////////////////////////////////////////////////////
void initLCD8bits(){
	DDRD = 0xFC;// Def D7 a D2 output.
	DDRB = 0x0F;// Def PB0 a PB4 output.
	_delay_ms(20);
	LCD_Comand();
}

void LCD_Comand(){
	//Pines de Data
	// Comando 00 | 00110000; rs rw | D0 a D7
	PORTD |=  (1 << PORTD5) | (1 << PORTD4);
	PORTD &= ~((1 << PORTD7) | (1 << PORTD6) | (1 << PORTD3) | (1 << PORTD2));
	//Pines  RS and Enable
	PORTB &= ~(1 << PORTB0);// Desactivar SR
	PORTB |= (1 << PORTB1);// Activar Enable
}

