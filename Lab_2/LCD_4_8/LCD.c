#define F_CPU 16000000UL  // Definir la frecuencia del CPU

#include "LCD.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

////////////////////////////////////////////////////
// 8Bits.
////////////////////////////////////////////////////
void Lcd_Port_8(char a)
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

void Lcd_Cmd_8(char a)
{
	PORTB &= ~(1<<PORTB1);  // RS = 0
	Lcd_Port_8(a);
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);           // Ajustar el retardo si es necesario
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_InitLCD8bits()
{
	PORTB &= ~(1<<PORTB1);   //RS = 0, se le indica que es modo comando
	PORTB &= ~(1<<PORTB0);   //E = 0
	_delay_ms(20);     //Pequeños delay que indica el fabricante del LCD
	 Lcd_Cmd_8(0x30);     //Comando que se repite 3 veces, que indica el fabricante de la LCD
	_delay_ms(5);
	 Lcd_Cmd_8(0x30);
	_delay_ms(5);
	 Lcd_Cmd_8(0x30);
	_delay_ms(10);

	 Lcd_Cmd_8(0x38);  //Comando que indica el fabricante del LCD, usando la matriz de 5X8
	 Lcd_Cmd_8(0x0C);  //Comando que indica el fabricante del LCD, display encendido
	 Lcd_Cmd_8(0x01);  //Comando que indica el fabricante del LCD, Limpiar LCD
	 Lcd_Cmd_8(0x06);  //Comando que indica el fabricante del LCD, comenzar a almacenar en DDRAM
	
	
}

void Lcd_Clear_8()
{
	Lcd_Cmd_8(0x01);  // Comando para limpiar el LCD
	_delay_ms(2);   // Esperar para asegurar que el LCD procese el comando
}

void Lcd_Set_Cursor_8(char a, char b)
{
	char temp;
	if(a == 1)
	{
		temp = 0x80 + b;
		Lcd_Cmd_8(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b;
		Lcd_Cmd_8(temp);
	}
}

void Lcd_Write_Char_8(char a)
{
	PORTB |= (1<<PORTB1);   // RS = 1
	Lcd_Port_8(a);            // Enviar datos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_Write_String_8(char *a)
{
	while(*a)
	{
		Lcd_Write_Char_8(*a++);
	}
}

void Lcd_Shift_Right_8()
{
	Lcd_Cmd_8(0x1C);
}

void Lcd_Shift_Left_8()
{
	Lcd_Cmd_8(0x18);
}

////////////////////////////////////////////////////
// 4 Bits.
////////////////////////////////////////////////////
void Lcd_Port_4(char a)
{
	if(a & 1) PORTD |= (1<<PORTD4); else PORTD &= ~(1<<PORTD4);  // D4
	if(a & 2) PORTD |= (1<<PORTD5); else PORTD &= ~(1<<PORTD5);  // D5
	if(a & 4) PORTD |= (1<<PORTD6); else PORTD &= ~(1<<PORTD6);  // D6
	if(a & 8) PORTD |= (1<<PORTD7); else PORTD &= ~(1<<PORTD7);  // D7
}

void Lcd_Cmd_4(char a)
{
	PORTB &= ~(1<<PORTB1);  // RS = 0
	Lcd_Port_4(a >> 4);      // Enviar los 4 bits más significativos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);           // Ajustar el retardo si es necesario
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
	Lcd_Port_4(a);           // Enviar los 4 bits menos significativos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);           // Ajustar el retardo si es necesario
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_InitLCD4bits()
{
	DDRB = 0x03;            // Configurar PB0-PB1 como salidas (RS y Enable)
	DDRD = 0xF0;            // Configurar PD4-PD7 como salidas
	PORTB &= ~(1<<PORTB1);  // RS = 0
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(20);          // Esperar más tiempo para asegurar que el LCD esté listo
	Lcd_Cmd_4(0x03);
	_delay_ms(5);
	Lcd_Cmd_4(0x03);
	_delay_ms(1);
	Lcd_Cmd_4(0x03);
	_delay_ms(10);
	Lcd_Cmd_4(0x02);         // Configurar en modo de 4 bits
	Lcd_Cmd_4(0x28);         // Función de 4 bits, 2 líneas, 5x7 dots
	Lcd_Cmd_4(0x0C);         // Display ON, Cursor OFF
	Lcd_Cmd_4(0x01);         // Limpiar Display
	_delay_ms(2);
	Lcd_Cmd_4(0x06);         // Incrementar cursor
}

void Lcd_Clear_4()
{
	Lcd_Cmd_4(0x01);  // Comando para limpiar el LCD
	_delay_ms(2);    // Esperar para asegurar que el LCD procese el comando
}

void Lcd_Set_Cursor_4(char a, char b)
{
	char temp;
	if(a == 1)
	{
		temp = 0x80 + b;
		Lcd_Cmd_4(temp);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b;
		Lcd_Cmd_4(temp);
	}
}

void Lcd_Write_Char_4(char a)
{
	PORTB |= (1<<PORTB1);   // RS = 1
	Lcd_Port_4(a >> 4);      // Enviar los 4 bits más significativos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
	Lcd_Port_4(a);           // Enviar los 4 bits menos significativos
	PORTB |= (1<<PORTB0);   // Enable = 1
	_delay_ms(2);
	PORTB &= ~(1<<PORTB0);  // Enable = 0
	_delay_ms(2);
}

void Lcd_Write_String_4(char *a)
{
	while(*a)
	{
		Lcd_Write_Char_4(*a++);
	}
}

void Lcd_Shift_Right_4()
{
	Lcd_Cmd_4(0x1C);
}

void Lcd_Shift_Left_4()
{
	Lcd_Cmd_4(0x18);
}
