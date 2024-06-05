/*
 * lcd.h
 *
 *  Created on: 7 dic. 2022
 *      Author: foto
 */

#ifndef LCD_H_
#define LCD_H_

/*#define		D4			0,9
#define		D5			0,10
#define		D6			0,11
#define		D7			0,12
#define		RS			0,14
#define		EN			0,13
*/


//=-=-=--=-==--=-=-=---=-=-=-=-==--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define		LCD_Clear()		LCD_Push( 0x01 , LCD_CONTROL )

void LCD_Display(const char *string, uint8_t line ,uint8_t pos);

//---------------------------------------------------------------------

#define		LCD_CONTROL		1
#define		LCD_DATA		0

#define 	LCD_BUFFER_SIZE	340

#define	 	LCD_LINE_SIZE	20
#define 	LCD_LINES		2

#define 	DSP0			0
#define 	DSP1			1

#define 	LINE_1_ADDRESS	0x00
#define 	LINE_2_ADDRESS	0x40

#define		LCD_Clear()		LCD_Push( 0x01 , LCD_CONTROL )

void LCD_Display(const char *string, uint8_t line ,uint8_t pos);


#define		LCD_CONTROL		1
#define		LCD_DATA		0

#define 	LCD_BUFFER_SIZE	340

#define	 	LCD_LINE_SIZE	20
#define 	LCD_LINES		2

#define 	DSP0			0
#define 	DSP1			1

#define 	LINE_1_ADDRESS	0x00
#define 	LINE_2_ADDRESS	0x40

extern uint32_t volatile lcdDelay;

void InicializarLCD( void );
int8_t LCD_Push( uint8_t data , uint8_t control );
int16_t LCD_Pop( void );
void EscrituraLCD( void );

#endif /* LCD_H_ */
