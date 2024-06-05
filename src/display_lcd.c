/*
 * display_lcd.c
 *
 *  Created on: 29 nov. 2022
 *      Author: foto
 */

#include "cabeza.h"
extern volatile uint32_t lcd_delay;
volatile uint8_t lcd_buff[LCD_BUFF_SIZE];
volatile uint8_t lcd_i_push=0;
volatile uint8_t lcd_i_pop=0;
extern volatile uint8_t match_out;

void inicializar_display_LCD()
{
	uint8_t i=0;

	//------pines--------------
	SetPIN(D4,0);
	SetDIR(D4,SALIDA);
	SetPINMODE_OUT(PIN_D4,PUSH_PULL);

	SetPIN(D5,0);
	SetDIR(D5,SALIDA);
	SetPINMODE_OUT(PIN_D5,PUSH_PULL);

	SetPIN(D6,0);
	SetDIR(D6,SALIDA);
	SetPINMODE_OUT(PIN_D6,PUSH_PULL);

	SetPIN(D7,0);
	SetDIR(D7,SALIDA);
	SetPINMODE_OUT(PIN_D7,PUSH_PULL);

	SetPIN(EN,0);
	SetDIR(EN,SALIDA);
	SetPINMODE_OUT(PIN_EN,PUSH_PULL);

	SetPIN(RS,0);
	SetDIR(RS,SALIDA);
	SetPINMODE_OUT(PIN_RS,PUSH_PULL);

	//--------------display-------------
	//lcd_delay=50;
	//while(lcd_delay);
	timer(100,coicidencia,mili);
	while(!match_out);
	for(i=0;i<3;i++)
	{
		comando(0,0x3,1);
		//lcd_delay=50;
		//while(lcd_delay);
		timer(100,coicidencia,mili);
		while(!match_out);
	}
	comando(0,0x2,1);

	LCD_Push(0x28,CONTROL);
	LCD_Push(0x08,CONTROL);
	LCD_Push(0x01,CONTROL);
	LCD_Push(0x06,CONTROL);
	LCD_Push(0x0c,CONTROL);
}


void comando(uint8_t rs,uint8_t value,uint8_t init)
{
	SetPIN(RS,rs);

	SetPIN(D4,value&0x1);
	SetPIN(D5,(value>>1)&0x1);
	SetPIN(D6,(value>>2)&0x1);
	SetPIN(D7,(value>>3)&0x1);

	if(init)
	{
		SetPIN(EN,1);
		SetPIN(EN,0);
	}
	else
	{
		SetPIN(EN,0);
		SetPIN(EN,1);
	}
}

void EscrituraLCD()
{
	uint16_t data;

	if(lcd_delay)
		lcd_delay--;

	if ((data=LCD_Pop())==-1 )
		return;

	if(((uint8_t)data)&0x80)
		comando(0,data,0);
	else
		comando(1,data,0);
}

void LCD_Push(uint8_t dato,uint8_t ctrl)
{
	lcd_buff[lcd_i_push]=(dato>>4)&0x0f;
	if(ctrl==CONTROL)
		lcd_buff[lcd_i_push]&=0x80;
	lcd_i_push++;

	lcd_buff[lcd_i_push]=(dato)&0x0f;
	if(ctrl==CONTROL)
		lcd_buff[lcd_i_push]&=0x80;

	lcd_i_push++;
	lcd_i_push%=LCD_BUFF_SIZE;
}

uint8_t LCD_Pop()
{
	uint8_t dato;

	if(lcd_i_push==lcd_i_pop)
		return -1;

	dato=lcd_buff[lcd_i_pop];
	lcd_i_pop++;
	lcd_i_pop%=LCD_BUFF_SIZE;
	return dato;
}

void display_lcd(const char *string, uint8_t line ,uint8_t pos)
{
	uint8_t i=0;
	pos%=16;

	if(!line)
		LCD_Push(pos+(0x80|LINE_1),CONTROL);
	else
		LCD_Push(pos+(0x80|LINE_2),CONTROL);

	for(i=0;string[i]!='\0';i++)
		LCD_Push(string[i],DATA);
}


