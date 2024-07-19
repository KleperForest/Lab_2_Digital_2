//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Universidad del Valle de Guatemala
// IE3054: ELECTRÓNICA DIGITAL 2
// Autor: Alan Gomez
// Proyecto: LAB_2.c
// Descripción: Laboratorio, librerias LCD y ADC.
// Hardware: ATmega328p
// Created: 7/19/24 8:07 a.m.
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "LCD_4_8/LCD.h"

////////////////////////////////////////////////////
// Variables.
////////////////////////////////////////////////////

#define LED_PIN PB5  // El pin PB5 corresponde al pin digital 13 en el Arduino Nano


////////////////////////////////////////////////////
//Rutinas
////////////////////////////////////////////////////

void setup() {
	// Configurar el pin del LED como salida
	DDRB |= (1 << LED_PIN);
}

void loop() {
	// Encender el LED
	PORTB |= (1 << LED_PIN);
	_delay_ms(500);
	// Apagar el LED
	PORTB &= ~(1 << LED_PIN);
	_delay_ms(500);
}

////////////////////////////////////////////////////
//Programa Principal
////////////////////////////////////////////////////


int main(void) {
	setup();
	while (1) {
		loop();
	}
	return 0;
}
