#define F_CPU 16000000UL

#include "LCD.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

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
	PORTB &= ~(1 << PORTB1);// Desactivar SR
	PORTB |= (1 << PORTB0);// Activar Enable
}

