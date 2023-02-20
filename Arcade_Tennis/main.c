/*  Main file to call all the functions.
 *
 * main.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#include "DE1Soc_VGA/DE1SoC_VGA.h"
#include "tennisDisplay/tennisDisplay.h"
#include "tennisEngine/tennisSprites.h"
#include "tennisEngine/tennisEngine.h"
#include "tennisScreens/tennisScreens.h"
#include "tennisInputs/tennisInputs.h"
#include "tennisSound/tennisSound.h"
#include "HPS_Watchdog/HPS_Watchdog.h"


int main(void) {
	int FS = 3;

	// Initialising the displays
	Displays_init(0xC8000000,0xC9000000,0xFF200060,0xFF200080);
	Displays_frameSkip(FS);
	ResetWDT();

	// Initialising the interrupts
	HPS_IRQ_initialise(NULL);
	HPS_ResetWatchdog();

    // Initialise the keys
	inputsInitialise();

	// Initialising the sounds
	pongSound_Init();

	// Initialisng OPTIONS Screen
	pongSprites_initBall();startScreen();
	enableInputs(1);
	while(1){
		if (getInputMode() == MENUS){

			gameMenu();
		} else if (getInputMode() == GAME){

			testScreen();
		}

	}
}

