#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL  // Define la frecuencia del reloj del microcontrolador
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

////////////////////////////////////////////////////
// Definimos Pines
////////////////////////////////////////////////////
/*
Estos pines son los que se usan para la conexión del LCD
//Data
#define D0 PB3
#define D1 PB2
// Estos no son del puerto D para poder utilizar Rx y Tx
#define D2 PD2
#define D3 PD3
#define D4 PD4
#define D5 PD5
#define D6 PD6
#define D7 PD7
//RS
#define RS PB1
//E
#define Enable PB0
// R/W va a tierra.
*/

////////////////////////////////////////////////////
// Prototipos de funciones para modo 4 bits
////////////////////////////////////////////////////
void Lcd_Port_4(char a);
void Lcd_Cmd_4(char a);
void Lcd_InitLCD4bits();
void Lcd_Clear_4();
void Lcd_Set_Cursor_4(char a, char b);
void Lcd_Write_Char_4(char a);
void Lcd_Write_String_4(char *a);
void Lcd_Shift_Right_4();
void Lcd_Shift_Left_4();

////////////////////////////////////////////////////
// Prototipos de funciones para modo 8 bits
////////////////////////////////////////////////////
void Lcd_Port_8(char a);
void Lcd_Cmd_8(char a);
void Lcd_InitLCD8bits();
void Lcd_Clear_8();
void Lcd_Set_Cursor_8(char a, char b);
void Lcd_Write_Char_8(char a);
void Lcd_Write_String_8(char *a);
void Lcd_Shift_Right_8();
void Lcd_Shift_Left_8();

#endif /* LCD_H_ */
