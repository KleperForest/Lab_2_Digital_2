#include "LCD.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

////////////////////////////////////////////////////
// 8Bits.
////////////////////////////////////////////////////
void Lcd_Port(char a)
{
	if(a & 1) PORTB |= (1<<PORTB3); else PORTB &= ~(1<<PORTB3);
	if(a & 2) PORTB |= (1<<PORTB2); else PORTB &= ~(1<<PORTB2);
	if(a & 4) PORTD |= (1<<PORTD2); else PORTD &= ~(1<<PORTD2);
	if(a & 8) PORTD |= (1<<PORTD3); else PORTD &= ~(1<<PORTD3);
	if(a & 16) PORTD |= (1<<PORTD4); else PORTD &= ~(1<<PORTD4);
	if(a & 32) PORTD |= (1<<PORTD5); else PORTD &= ~(1<<PORTD5);
	if(a & 64) PORTD |= (1<<PORTD6); else PORTD &= ~(1<<PORTD6);
	if(a & 128) PORTD |= (1<<PORTD7); else PORTD &= ~(1<<PORTD7);
}

void Lcd_Cmd(char a)
{
	PORTB &= ~(1<<PORTB1);  // RS = 0
	Lcd_Port(a);
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);           // Ajustar el retardo si es necesario
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_InitLCD8bits()
{
	PORTB &= ~(1<<PORTB1);  // RS = 0
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(20);          // Esperar más tiempo para asegurar que el LCD esté listo
	Lcd_Cmd(0x30);
	_delay_ms(5);
	Lcd_Cmd(0x30);
	_delay_ms(1);
	Lcd_Cmd(0x30);
	_delay_ms(10);
	Lcd_Cmd(0x38);          // Función de 8 bits, 2 líneas, 5x7 dots
	Lcd_Cmd(0x0C);          // Display ON, Cursor OFF
	Lcd_Cmd(0x01);          // Limpiar Display
	_delay_ms(2);
	Lcd_Cmd(0x06);          // Incrementar cursor
}

void Lcd_Clear()
{
	Lcd_Cmd(0x01);  // Comando para limpiar el LCD
	_delay_ms(2);   // Esperar para asegurar que el LCD procese el comando
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp;
	if(a == 1)
	{
		temp = 0x80 + b;
		Lcd_Cmd(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b;
		Lcd_Cmd(temp);
	}
}

void Lcd_Write_Char(char a)
{
	PORTB |= (1<<PORTB1);   // RS = 1
	Lcd_Port(a);            // Enviar datos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_Write_String(char *a)
{
	while(*a)
	{
		Lcd_Write_Char(*a++);
	}
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x1C);
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x18);
}
