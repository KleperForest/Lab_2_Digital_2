//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTR�NICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_2.c
// Descripci�n: Laboratorio, librerias LCD, ADC y UART.
// Hardware: ATmega328p
// Created: 7/19/24 8:07 a.m.
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "LCD_4_8/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"

////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////
char buffer[64];  // Buffer para las cadenas de caracteres a mostrar en el LCD y UART
uint16_t adc_results[2];  // Array para almacenar los resultados del ADC
int counter = 0;  // Contador inicial

int voltage1, voltage2; //Mapeo de ADC

////////////////////////////////////////////////////
// Prototipos de funciones
////////////////////////////////////////////////////
void display_menu(void);
void process_command(char command);

////////////////////////////////////////////////////
// Programa Principal
////////////////////////////////////////////////////

int main(void)
{
	// Configuraci�n de puertos y perif�ricos
	DDRD = 0xFF;  // Configura todos los pines del puerto D como salidas
	DDRB = 0x0F;  // Configura los primeros dos pines del puerto B como salidas
	Lcd_InitLCD8bits();  // Inicializa el LCD en modo de 4 bits
	ADC_Init();  // Inicializa el ADC
	UART_Init(BAUD);  // Inicializa la UART

	uint8_t adc_channels[] = {7, 6};  // Canales ADC a leer (ADC7 y ADC6)

	// Configuraci�n inicial del LCD
	Lcd_Clear_8();  // Limpiar el LCD
	_delay_ms(100);  // Esperar para asegurar que el LCD est� listo
	Lcd_Set_Cursor_8(1, 0);
	Lcd_Write_String_8("S1:   S2:   S3:");

	// Mostrar el men� inicial en la consola
	display_menu();

	while (1)
	{
		// Leer los valores de los ADC
		ADC_Read_Multiple(adc_channels, adc_results, 2);
		
		// Convertir los valores ADC a voltaje
		voltage1 = (int)(((adc_results[0] * 5.0) / 1023)*100);
		voltage2 = (int)(((adc_results[1] * 5.0) / 1023)*100);

		// Mostrar los valores en el LCD
		Lcd_Set_Cursor_8(2, 0);
		//snprintf(buffer, sizeof(buffer), "%1.2fV", voltage1);
		snprintf(buffer, 16, "%d.%02dV", voltage1 / 100, voltage1 % 100);
		Lcd_Write_String_8(buffer);

		Lcd_Set_Cursor_8(2, 6);
		//snprintf(buffer, sizeof(buffer), "%1.2fV", voltage2);
		snprintf(buffer, 16, "%d.%02dV", voltage2 / 100, voltage2 % 100);
		Lcd_Write_String_8(buffer);

		Lcd_Set_Cursor_8(2, 11);
		snprintf(buffer, sizeof(buffer), "%4d", counter);
		Lcd_Write_String_8(buffer);

		// Leer y procesar los comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles en el buffer de recepci�n
			char received_char = UART_Receive();
			process_command(received_char);
		}

		_delay_ms(500);  // Espera medio segundo antes de la siguiente actualizaci�n
	}
}

////////////////////////////////////////////////////
// Funciones auxiliares
////////////////////////////////////////////////////

void display_menu(void) {
	UART_TransmitString("\r\n***** Menu *****\r\n");
	UART_TransmitString("1. Mostrar valores de ADC\r\n");
	UART_TransmitString("2. Incrementar contador (+)\r\n");
	UART_TransmitString("3. Decrementar contador (-)\r\n");
	UART_TransmitString("4. Mostrar valor del contador\r\n");
	UART_TransmitString("*****************\r\n");
	UART_TransmitString("Seleccione una opci�n: ");
}

void process_command(char command) {
	switch (command) {
		case '1':
		snprintf(buffer, sizeof(buffer), "Valores ADC - ADC6: %u, ADC7: %u\r\n", adc_results[1], adc_results[0]);
		UART_TransmitString(buffer);
		break;
		case '+':
		counter++;
		UART_TransmitString("Contador incrementado.\r\n");
		break;
		case '-':
		counter--;
		UART_TransmitString("Contador decrementado.\r\n");
		break;
		case '4':
		snprintf(buffer, sizeof(buffer), "Valor del contador: %d\r\n", counter);
		UART_TransmitString(buffer);
		break;
		default:
		UART_TransmitString("Opci�n inv�lida. Por favor, seleccione una opci�n v�lida.\r\n");
		break;
	}
	display_menu();
}