/*
 * LPC845_GPIO_Dr.h
 *
 *  Created on: 10 ene. 2022
 *      Author: gos
 */

#ifndef LPC845_GPIO_DR_H_
#define LPC845_GPIO_DR_H_


#define SALIDA		1
#define ENTRADA 	0

#define NO_PULL		0x00
#define PULL_DOWN	0x01
#define PULL_UP		0x02
#define REP			0x03

#define PUSH_PULL	0x00
#define OPEN_DRAIN	0x01



void SetPIN(uint32_t, uint32_t, uint32_t);
void SetDIR(uint32_t, uint32_t, uint32_t);
uint32_t GetPIN(uint32_t, uint32_t);
void SetPINMODE_IN(uint32_t, uint32_t);
void SetPINMODE_OUT(uint32_t, uint32_t);
void TogglePIN(uint32_t , uint32_t);


#endif /* LPC845_GPIO_DR_H_ */
