#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador

#include "LCD.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

////////////////////////////////////////////////////
// Inicialización en modo 4 bits (vacío)
////////////////////////////////////////////////////
void initLCD4bits(){}

////////////////////////////////////////////////////
// Inicialización en modo 8 bits
////////////////////////////////////////////////////
void Lcd_Port(char a)
{
	if(a & 1)               //0000 0001
	PORTB |= (1<<PORTB3);
	else
	PORTB &= ~(1<<PORTB3);
	
	if(a & 2)               //0000 0010
	PORTB |= (1<<PORTB2);
	else
	PORTB &= ~(1<<PORTB2);
	
	if(a & 4)               //0000 0100
	PORTD |= (1<<PORTD2);
	else
	PORTD &= ~(1<<PORTD2);
	
	if(a & 8)               //0000 1000
	PORTD |= (1<<PORTD3);
	else
	PORTD &= ~(1<<PORTD3);
	
	if(a & 16)              //0001 0000
	PORTD |= (1<<PORTD4);
	else
	PORTD &= ~(1<<PORTD4);

	if(a & 32)              //0010 0000
	PORTD |= (1<<PORTD5);
	else
	PORTD &= ~(1<<PORTD5);
	
	if(a & 64)              //0100 0000
	PORTD |= (1<<PORTD6);
	else
	PORTD &= ~(1<<PORTD6);
	
	if(a & 128)             //1000 0000
	PORTD |= (1<<PORTD7);
	else
	PORTD &= ~(1<<PORTD7);
}

void Lcd_Cmd(char a)
{
	PORTB &= ~(1<<PORTB1);  // RS = 0 (comando)
	Lcd_Port(a);            // Enviar datos al puerto
	PORTB |= (1<<PORTB0);   // E = 1
	_delay_ms(1);
	PORTB &= ~(1<<PORTB0);  // E = 0
	_delay_ms(1);
}

void Lcd_InitLCD8bits()
{
	PORTB &= ~(1<<PORTB1);  // RS = 0
	PORTB &= ~(1<<PORTB0);  // E = 0
	_delay_ms(20);
	Lcd_Cmd(0x30);
	_delay_ms(5);
	Lcd_Cmd(0x30);
	_delay_ms(1);
	Lcd_Cmd(0x30);
	_delay_ms(10);

	Lcd_Cmd(0x38);          // Configuración de 8 bits y 2 líneas
	Lcd_Cmd(0x0C);          // Encender display sin cursor
	Lcd_Cmd(0x01);          // Limpiar display
	Lcd_Cmd(0x06);          // Modo de incremento
}

void Lcd_Clear()
{
	Lcd_Cmd(1);  // Comando para limpiar el display
}

void Lcd_Set_Cursor(char a, char b)
{
	if(a == 1)
	Lcd_Cmd(0x80 + b);  // Posicionar cursor en la fila 1
	else if(a == 2)
	Lcd_Cmd(0xC0 + b);  // Posicionar cursor en la fila 2
}

void Lcd_Write_Char(char a)
{
	PORTB |= (1<<PORTB1);   // RS = 1 (dato)
	Lcd_Port(a);            // Transferir datos
	PORTB |= (1<<PORTB0);   // E = 1
	_delay_ms(1);
	PORTB &= ~(1<<PORTB0);  // E = 0
	_delay_ms(1);
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0; a[i] != '\0'; i++)
	Lcd_Write_Char(a[i]);  // Escribir cada caracter de la cadena
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x1C);  // Comando para desplazar a la derecha
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x18);  // Comando para desplazar a la izquierda
}
