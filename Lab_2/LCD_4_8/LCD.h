#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
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
// 4bits
////////////////////////////////////////////////////
void initLCD4bits();
////////////////////////////////////////////////////
// 8bits
////////////////////////////////////////////////////
void initLCD8bits();//Funcion INCIAL
void LCD_Comand();// Funcion primer BFs

#endif /* LCD_H_ */