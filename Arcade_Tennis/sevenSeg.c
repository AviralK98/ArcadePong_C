/*
 * sevenSeg.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#include "sevenSeg.h"
// Initialising the array with the hexadecimal values
int HexSDisplay[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

// Initialising the 7-Segment Display
void SDisplay_set(int Display, int HexValue){

	volatile int *HEX0 = (int* ) 0XFF200020;
	volatile int *HEX1 = (int* ) 0XFF200030;
	int invClearBits = 0x7F;
	int shiftAmount = 8;
	int hex1Adjust = 4;
	if(Display < 4){
		*HEX0 &= ~(invClearBits << (Display * shiftAmount));
		*HEX0 |= (HexSDisplay[HexValue] << (Display * shiftAmount));
	}
	else{
		*HEX1 &= ~(invClearBits << ((Display - hex1Adjust) * shiftAmount));
		*HEX1 |= (HexSDisplay[HexValue] << ((Display - hex1Adjust) * shiftAmount));
	}
}
void SDisplay_PNum(int number, int pair){

	int number0 = number/10;
	int number1 = number % 10;
	int pairdisplay0 = 2*pair;
	int pairdisplay1 = 2*pair+1;
	SDisplay_set(pairdisplay0,number1);
	SDisplay_set(pairdisplay1,number0);
}

// Emptying the buffer for the 7-Segment Display
void SDisplay_clearAll(){

	volatile int *HEX0 = (int* ) 0XFF200020;
	volatile int *HEX1 = (int* ) 0XFF200030;
	int zero = 0x00;
	*HEX0 &= zero;
	*HEX1 &= zero;
}

