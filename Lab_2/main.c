//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTRÓNICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_2.c
// Descripción: Laboratorio, librerias LCD, ADC y UART.
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
char buffer[16];  // Buffer para las cadenas de caracteres a mostrar en el LCD
uint16_t adc_results[2];  // Array para almacenar los resultados del ADC
int counter = 0;  // Contador inicial

////////////////////////////////////////////////////
// Programa Principal
////////////////////////////////////////////////////

int main(void)
{
	// Configuración de puertos y periféricos
	DDRD = 0xFF;  // Configura todos los pines del puerto D como salidas
	DDRB = 0x03;  // Configura los primeros dos pines del puerto B como salidas
	Lcd_InitLCD8bits();  // Inicializa el LCD en modo de 8 bits
	ADC_Init();  // Inicializa el ADC
	UART_Init(BAUD);  // Inicializa la UART

	uint8_t adc_channels[] = {7, 6};  // Canales ADC a leer (ADC7 y ADC6)

	// Configuración inicial del LCD
	Lcd_Set_Cursor(1, 0);
	Lcd_Write_String("S1:   S2:   S3:");

	while (1)
	{
		// Leer los valores de los ADC
		ADC_Read_Multiple(adc_channels, adc_results, 2);

		// Mostrar los valores en el LCD
		Lcd_Set_Cursor(2, 0);
		snprintf(buffer, sizeof(buffer), "%4uV", adc_results[1]);
		Lcd_Write_String(buffer);
		
		snprintf(buffer, sizeof(buffer), "%4uV", adc_results[0]);
		Lcd_Set_Cursor(2, 6);
		Lcd_Write_String(buffer);

		snprintf(buffer, sizeof(buffer), "%4d", counter);
		Lcd_Set_Cursor(2, 11);
		Lcd_Write_String(buffer);
		
		// Enviar los valores de los ADC y el contador a través de UART
		snprintf(buffer, sizeof(buffer), "ADC6:%u,ADC7:%u,Count:%d\r\n", adc_results[1], adc_results[0], counter);
		UART_TransmitString(buffer);
		
		// Leer y procesar los comandos de la UART
		if (UCSR0A & (1 << RXC0)) {  // Verificar si hay datos disponibles en el buffer de recepción
			unsigned char received_char = UART_Receive();
			if (received_char == '+') {
				counter++;  // Incrementar el contador
				} else if (received_char == '-') {
				counter--;  // Decrementar el contador
			}
		}
		
		_delay_ms(500);  // Espera medio segundo antes de la siguiente actualización
	}
}
