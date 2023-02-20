/* Source Code for the Inputs
 * tennisInputs.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */


#include "tennisInputs.h"
volatile unsigned int *PS2_DATA = (unsigned int *) 0xFF200100;
volatile unsigned int *PS2_CONTROL = (unsigned int *) 0xFF200104;
volatile unsigned int *KEY_ptr       = (unsigned int *) 0xFF200050;
volatile unsigned int keyBuffer[3] = {0,0,0};
bool inputsIsInit = false;
volatile unsigned int mode;

// Function to manipulate the interrupts from the controller
void keyboardISR(HPSIRQSource interruptID, bool isInit, void* initParams){
	if (!isInit){
		*PS2_CONTROL |= 0x0;
		inputKeyboard();

		*PS2_CONTROL |= 0x1;
		emptyFIFO();
	}
	HPS_ResetWatchdog();
}

void pushbuttonISR(HPSIRQSource interruptID, bool isInit, void* initParams) {
    if (!isInit) {
        unsigned int press;
        // Taking the keypresses
        press = KEY_ptr[3];KEY_ptr[3] = press;

        if (press == 1){
        	Input(_UP, keySpeed);
        }
        else if (press == 2){
        	Input(_DOWN, keySpeed);
        }
        else if (press == 4){
        	Input(_W, keySpeed);
        }
        else if (press == 8){
        	Input(_S, keySpeed);
        }
        else if (press == 10){
        	Input(99, keySpeed);
        }
    }

    HPS_ResetWatchdog();
}


void inputsInitialise(void) {
	if (!inputsIsInit){

		HPS_IRQ_registerHandler(IRQ_LSC_PS2_PRIMARY, keyboardISR);
		HPS_ResetWatchdog();
		HPS_IRQ_registerHandler(IRQ_LSC_KEYS, pushbuttonISR);
		HPS_ResetWatchdog();
		inputsIsInit = true;
		HPS_ResetWatchdog();
	}
}

char PS2Scan( void ) {
	int keyboard_data, RVALID;
	char inputKey;
	// Reading the Data register
	keyboard_data = *(PS2_DATA);
	RVALID = keyboard_data & 0x8000;
	if (RVALID){
		inputKey = keyboard_data & 0xFF; HPS_ResetWatchdog();
	} else { inputKey = 0; }
	HPS_ResetWatchdog();

	return inputKey;
}

void inputKeyboard( void ) {
	char key = PS2Scan();
	keyBuffer[0] = keyBuffer[1];
	keyBuffer[1] = keyBuffer[2];
	keyBuffer[2] = PS2Scan();

	if (key == _W) 				{
		keyBuffer[2] = 1; Input(_W, keyBSpeed);
	} else if (key == _S)		{
		keyBuffer[2] = 2; Input(_S, keyBSpeed);
	} else if (key == _UP) 		{
		keyBuffer[2] = 3; Input(_UP, keyBSpeed);
	} else if (key == _DOWN) 	{
		keyBuffer[2] = 4; Input(_DOWN, keyBSpeed);
	} else if (key == _ESC)		{
		keyBuffer[2] = 5; Input(_ESC, keyBSpeed);
	} else if (key == _RETURN)	{
		keyBuffer[2] = 6; Input(_RETURN, keyBSpeed);
	} else if ((key == _BKSPACE) && (keyBuffer[0] != 7)) {
		keyBuffer[2] = 7; toggleSound();
	} else if (key == _LEFT) 		{
		keyBuffer[2] = 8; Input(_LEFT, keyBSpeed);
	} else if (key == _RIGHT) 	{
		keyBuffer[2] = 9; Input(_RIGHT, keyBSpeed);
	}
	if ((key == 0xF0) || (key == 0xE0)) keyBuffer[2] = 0;

	if ((keyBuffer[2] == keyBuffer[0]) && (keyBuffer[1] == 0)) keyBuffer[2] = 0;

	HPS_ResetWatchdog();
}

void emptyFIFO( void ){
	int RAVAIL = *(PS2_DATA) & 0xFFFF0000;
	while (RAVAIL > 0x1000){
		char temp;
		temp = *(PS2_DATA) & 0xFF;
		RAVAIL = *(PS2_DATA) & 0xFFFF0000;
		temp &= temp;
	}
}

void Input(unsigned int key, unsigned int speed){
	if ((mode == GAME) || (mode == GAME_AI)){
		if (key == _W){
			pongEngine_paddleMove(1, DOWN, 	speed);

		}
		else if (key == _S){
			pongEngine_paddleMove(1, UP, 	speed);

		} else if (key == _ESC){
			setInputMode(MENUS);
		}
	}
// For Multiplayer
	if (mode == GAME){
		if (key == _UP){
			pongEngine_paddleMove(2, DOWN, 	speed);

		}
		else if (key == _DOWN){
			pongEngine_paddleMove(2, UP, 	speed);

		}
	}


	if (mode == MENUS){
		if (speed == keyBSpeed){
			if (key == _UP){
				menuMove(_UP);
			} else if (key == _DOWN){
				menuMove(_DOWN);
			} else if (key == _LEFT){
				menuMove(_LEFT);
			} else if (key == _RIGHT){
				menuMove(_RIGHT);
			} else if (key == _RETURN){
				setMenu(4, 1); menuMove(0);
			}
		} else {
			if (key == _UP){
				menuMove(_RIGHT);
			} else if (key == _DOWN){
				menuMove(_LEFT);
			} else if (key == _W){
				menuMove(_UP);
			} else if (key == _S){
				menuMove(_DOWN);
			}
		}
	}


	if (key == _BKSPACE){
		toggleSound();
	}
	ResetWDT();
}

// Function to enable the interrupts
void enableInputs(int enable){
	if (enable == 1){

		KEY_ptr[2] = 0xF;

		*PS2_CONTROL = (1<<0);
	} else {

		KEY_ptr[2] = 0x00;

		*PS2_CONTROL = (0<<0);
	}
}
// Initialising the mode.
void setInputMode(unsigned int _mode){

	mode = _mode;
	if (mode == MENUS){ Displays_mode(NOFRAMEBUFFER); } else { Displays_mode(SOFTWAREOCTOFB); }
}

int getInputMode( void ){
	return mode;
}
