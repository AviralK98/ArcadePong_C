/*Header Files for the Inputs
 * tennisInputs.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISINPUTS_H_
#define TENNISINPUTS_H_

#include <stdbool.h>
#include "../tennisEngine/tennisEngine.h"
#include "../tennisDisplay/tennisDisplay.h"
#include "../tennisSound/tennisSound.h"
#include "../tennisScreens/tennisScreens.h"
#include <string.h>
#include "../HPS_IRQ/HPS_IRQ.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include <stdio.h>
#include <stdlib.h>


#define _ESC 		0x76
#define _RETURN		0x5A
#define _BKSPACE 	0x66
#define _W			0x1D
#define _A			0x1C
#define _S			0x1B
#define _D			0x23
#define _LEFT		0x6B
#define _RIGHT		0x74
#define _UP			0x75
#define _DOWN		0x72
#define MENUS 		0
#define GAME  		1
#define GAME_AI 	2

// Frame skips for the racket
#define keySpeed  20
#define keyBSpeed 10



// Initialising the inputs
void inputsInitialise(void);char PS2Scan(void);void inputKeyboard( void );
void emptyFIFO( void );
void Input(unsigned int key, unsigned int speed);

// Input taken from the OPTIONS SCREEN
void setInputMode(unsigned int _mode);int getInputMode( void );
void enableInputs(int enable);

#endif /* TENNISINPUTS_H_ */
