/*
 * display_lcd.h
 *
 *  Created on: 29 nov. 2022
 *      Author: foto
 */

#ifndef DISPLAY_LCD_H_
#define DISPLAY_LCD_H_

#define		D4			0,9
#define		D5			0,10
#define		D6			0,11
#define		D7			0,13
#define		RS			0,14
#define		EN			0,15

#define PIN_D4			IOCON_INDEX_PIO0_9
#define PIN_D5			IOCON_INDEX_PIO0_10
#define PIN_D6			IOCON_INDEX_PIO0_11
#define PIN_D7			IOCON_INDEX_PIO0_13
#define PIN_RS			IOCON_INDEX_PIO0_14
#define PIN_EN			IOCON_INDEX_PIO0_15

#define DATA			1
#define CONTROL			0

#define LCD_BUFF_SIZE	340
#define	LINE_1			0x00
#define LINE_2			0x40

void inicializar_display_LCD();
void comando(uint8_t,uint8_t,uint8_t);
void EscrituraLCD();
void LCD_Push(uint8_t ctrl,uint8_t dato);
uint8_t LCD_Pop();
void display_lcd(const char *string, uint8_t line ,uint8_t pos);




#endif /* DISPLAY_LCD_H_ */
