/* Source code file to initialise the screen
 * tennisScreens.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */


#include "tennisScreens.h"

volatile unsigned int menuSelector = 0;
volatile unsigned int settings[] = {0,5,4,0,0};
volatile unsigned int menuSelectorOld = 0;
volatile unsigned int settingsOld[] = {0,5,4,0,0};
short menuColours[] = {_BLUE, _BLACK, _BLACK, _BLACK, _BLACK};

unsigned int settingsMax[] = {1, 9, 9, 1, 1};
unsigned int numMenuItems = sizeof(settings)/sizeof(int);
volatile unsigned int gameMode 		= GAME_AI;
volatile unsigned int gameModeOld 	= GAME_AI;
int n = 0;
volatile unsigned int *slider_ptr = (unsigned int *)0xFF200040;
unsigned int last_slider;

void setMenu(unsigned int _menuSelector, unsigned int _setting){
	menuSelectorOld = menuSelector;
	settingsOld[_menuSelector] = settings[_menuSelector];

	menuSelector = _menuSelector;
	settings[_menuSelector] = _setting;
}

void menuMove(unsigned int direction){
	unsigned int i;
	char str_txt[30];
	enableInputs(0);


	for (i = 0; i<numMenuItems; i++){
		settingsOld[i] = settings[i];
		menuColours[i] = _BLACK;
	}

	menuSelectorOld = menuSelector;

	if (direction == _DOWN){
		if (menuSelector == 4){ menuSelector = 0; } else menuSelector++;

	} else if (direction == _UP){
		if (menuSelector == 0){ menuSelector = 4; } else menuSelector--;

	} else if (direction == _LEFT){
		if (settings[menuSelector] == 0) { settings[menuSelector] = settingsMax[menuSelector]; } else settings[menuSelector]--;

	} else if (direction == _RIGHT){
		if (settings[menuSelector] == settingsMax[menuSelector]) { settings[menuSelector] = 0; } else settings[menuSelector]++;

	}




	if (menuSelector != menuSelectorOld){
		menuColours[menuSelector] = _BLUE;
		pongSprites_renderBall(50, (240+(int)25*menuSelectorOld), _WHITE); ResetWDT();
		pongSprites_renderBall(50, (240+(int)25*menuSelector), _WHITE); ResetWDT();

		// OPTIONS Screen
		pongSprites_writeText(100, 20, 	LARGE, "* *OPTIONS* *", _RED); ResetWDT();
		pongSprites_writeText(75, 65, 	LARGE, "<MULTIPLAYER? ", menuColours[0]); ResetWDT();
		pongSprites_writeText(75, 90, 	LARGE, "<DIFFICULTY > ", menuColours[1]); ResetWDT();
		pongSprites_writeText(75, 115, 	LARGE, "<VOLUME > ", menuColours[2]); ResetWDT();
		pongSprites_writeText(75, 140, 	LARGE, "xx RESET! xx ", menuColours[3]); ResetWDT();
		pongSprites_writeText(75, 165, 	LARGE, ">>>START<<< ", menuColours[4]); ResetWDT();
	}


	if (menuSelector == 0){
		if (settings[0] == 1){
			pongSprites_writeText(240, 65, 1, "NO!", _WHITE); ResetWDT();
			pongSprites_writeText(240, 65, 1, "YES!", _MAGENTA); ResetWDT();
			gameMode = GAME;
		} else {
			pongSprites_writeText(240, 65, 1, "YES!", _WHITE); ResetWDT();
			pongSprites_writeText(240, 65, 1, "NO!", _MAGENTA); ResetWDT();
			gameMode = GAME_AI;
		}
	}

	if ((menuSelector == 1) && (settings[menuSelector] != settingsOld[menuSelector])){
		sprintf(str_txt, " %d ", settingsOld[1]);
		pongSprites_writeText(242, 90, LARGE, str_txt, _WHITE); ResetWDT();
		sprintf(str_txt, " %d ", settings[1]);
		pongSprites_writeText(242, 90, LARGE, str_txt, _MAGENTA); ResetWDT();

		pongSprites_changePaddleSize(settings[1]);
	}

	if ((menuSelector == 2) && (settings[menuSelector] != settingsOld[menuSelector])){
		sprintf(str_txt, " %d ", settingsOld[2]);
		pongSprites_writeText(242, 115, LARGE, str_txt, _WHITE); ResetWDT();
		sprintf(str_txt, " %d ", settings[2]);
		pongSprites_writeText(242, 115, LARGE, str_txt, _MAGENTA); ResetWDT();

		if (settings[2] != 0){
			enableSound(1);
			setVolume(settings[2]);
		} else {
			enableSound(0);
		}



	}

	if (menuSelector == 3){
		if (settings[3] == 1){
			settings[3] = 0;
			pongEngine_resetScore(0);
		}
	}

	if (menuSelector == 4){
		if (settings[4] == 1){
			settings[4] = 0;
			if (gameModeOld != gameMode){
				pongEngine_resetScore(0);
			}

			pongSprites_renderRectangle(50-8, 50+8, 71-8, 180, _WHITE);
			for (i = 50; i < 260; i++){
				pongSprites_renderBall(i, 	(240+(int)25*menuSelector), _WHITE); ResetWDT();
				pongSprites_renderBall(i+1, (240+(int)25*menuSelector), _WHITE); ResetWDT();
			}
			setInputMode(gameMode);
		}
	}

	usleep(150000);
	emptyFIFO();
	ResetWDT();
	enableInputs(1);
}

// Setting up the Screen
void startScreen(){
	// Filling the background of the Introduction screen with color
	Displays_fillColour(_CYAN);
	setInputMode(MENUS);


	pongSprites_writeText(50, 120, 1, "DE1-SoC: ARCADE", 0xF800);
	pongSprites_writeText(60, 150, 1, "ELEC 5620M", 0xF800);
	pongSprites_writeText(60, 170, 1, "~A.Krishna", 0xF800);
	Displays_forceRefresh();
	ResetWDT();

	startSound();
	usleep(1000000); ResetWDT();
	usleep(1000000); ResetWDT();
	last_slider = *slider_ptr;
}

void gameMenu(){
	unsigned int i;
	char str_txt[30];

	resetRand();
	setInputMode(MENUS);
	gameModeOld = gameMode;
	SDisplay_clearAll();


	menuSelector = 0; menuSelectorOld = 0;
	for (i = 0; i<numMenuItems; i++){
		menuColours[i] = _BLACK;
	}
	menuColours[0] = _BLUE;


	Displays_fillColour(_WHITE);



	pongSprites_renderBall(50, 81/*+25*menuSelector*/, _WHITE); ResetWDT();
	pongSprites_writeText(100, 20, 	LARGE, "* *OPTIONS* *", _RED); ResetWDT();
	pongSprites_writeText(75, 65, 	LARGE, "<MULTIPLAYER? ", menuColours[0]); ResetWDT();
	pongSprites_writeText(75, 90, 	LARGE, "<DIFFICULTY > ", menuColours[1]); ResetWDT();
	pongSprites_writeText(75, 115, 	LARGE, "<VOLUME > ", menuColours[2]); ResetWDT();
	pongSprites_writeText(75, 140, 	LARGE, "xx RESET! xx ", menuColours[3]); ResetWDT();
	pongSprites_writeText(75, 165, 	LARGE, ">>>START<<< ", menuColours[4]); ResetWDT();

	// Options on the second screen with adjustments
	if (settings[0] == 0){
		pongSprites_writeText(240, 65, LARGE, "NO!", _MAGENTA); ResetWDT();
	} else {
		pongSprites_writeText(240, 65, LARGE, "YES!", _MAGENTA); ResetWDT();
	}

	sprintf(str_txt, " %d ", settings[1]);
	pongSprites_writeText(242, 90, LARGE, str_txt, _MAGENTA); ResetWDT();

	sprintf(str_txt, " %d ", settings[2]);
	pongSprites_writeText(242, 115, LARGE, str_txt, _MAGENTA); ResetWDT();

	ResetWDT();
	Displays_Refresh();
	enableInputs(1);
	while(getInputMode() == MENUS){
		if ((menuSelector != menuSelectorOld) || (settings[menuSelector] != settingsOld[menuSelector])){
			if (settings[2] != settingsOld[2]){
				Sound(G4, 50);
			}
			menuSelectorOld = menuSelector;
			for (i = 0; i<numMenuItems; i++){
				settingsOld[i] = settings[i];
				menuColours[i] = _BLACK;
			}
		}
	ResetWDT();
	}
	last_slider = *slider_ptr;
	Displays_clearScreen();
}

void testScreen_AI( void ){
	int dir;
	int vel;
	int *arr;
	Displays_clearScreen();
	setInputMode(GAME_AI);
    pongEngine_init();
	ResetWDT();
	pongEngine_createBall();


	Displays_forceRefresh(); pongEngine_refreshScore();
	n = 0;
	while (getInputMode() == GAME_AI){
		ResetWDT();
		Displays_forceRefresh();

		if (n < 1) {

					n++;
					dir = pongPhysics_serve ();
					vel = 2;
			}

		if ((pongEngine_getBallLocation_x() <= 50 + 15) && (pongEngine_getBallLocation_x() >= 50 + 10))   {

			if ((pongEngine_getBallLocation_y() <= pongEngine_getPaddleY (1) + 30 + 15) && (pongEngine_getBallLocation_y() >= pongEngine_getPaddleY (1) - 30 - 15)) {

			paddleBeep();
		    arr = pongPhysics_paddleCollision(vel,dir,1);
		    dir = arr[0];
		    vel = arr[1];

			}

		} else if ((pongEngine_getBallLocation_x() >= 270 - 15) && (pongEngine_getBallLocation_x() <= 270 - 10))  { // -10

			if ((pongEngine_getBallLocation_y() <= pongEngine_getPaddleY (2) + 30 + 15) && (pongEngine_getBallLocation_y() >= pongEngine_getPaddleY (2) - 30 - 15))  {

			paddleBeep();
			arr = pongPhysics_paddleCollision(vel,dir,2);
			dir = arr[0];
			vel = arr[1];


			}
		}


		if ( pongEngine_getBallLocation_y() <= 23 + 20  ) {
			enableInputs(0);
			paddleBeep();
			enableInputs(1);

			dir = pongPhysics_borderCollision(vel, dir);


		} else if ( pongEngine_getBallLocation_y() >= 230 - 10){
			enableInputs(0);
			ballOutBeep();
			enableInputs(1);

			dir = pongPhysics_borderCollision(vel, dir);
		}




		if ( pongEngine_getBallLocation_y() > pongEngine_getPaddleY(2)+10){

			pongEngine_paddleMove(2, UP, 2);

		} else if ( pongEngine_getBallLocation_y() < pongEngine_getPaddleY(2)-10){

			pongEngine_paddleMove(2, DOWN, 	2);
		}

		pongEngine_moveBall(dir, vel);

		if (*slider_ptr != last_slider)	{

			setInputMode(MENUS);
			last_slider = *slider_ptr;
		}

		// Function for adding the point

		if ( pongEngine_getBallLocation_x() <= 10  ) {
				pongEngine_destroyBall();
				Displays_forceRefresh();
				enableInputs(0);
				paddleBeep();
				enableInputs(1);
				pongEngine_resetPaddles();
				pongEngine_resetBallLoc();
				pongEngine_createBall();
				pongEngine_paddleCreate(1);
				pongEngine_paddleCreate(2);
				pongEngine_moveBall(1, 0);
				pongEngine_moveBall(0, 0);
				Displays_forceRefresh(); pongEngine_refreshScore();
				n = 0;
				pongEngine_addPoint(2);
		} else if ( pongEngine_getBallLocation_x() >= 320 - 10){
			pongEngine_destroyBall();
			enableInputs(0);
			paddleBeep();
			enableInputs(1);
			pongEngine_resetPaddles();
			pongEngine_resetBallLoc();
			pongEngine_createBall();
			pongEngine_paddleCreate(1);
			pongEngine_paddleCreate(2);
			pongEngine_moveBall(1, 0);
			pongEngine_moveBall(0, 0);
			Displays_forceRefresh(); pongEngine_refreshScore();
			n = 0;
			pongEngine_addPoint(1);


		}
	}
Displays_clearScreen();
}

void testScreen( void ){
	int dir = 0;
	int vel;
	int* arr;

	// Setting up the Input Mode
	Displays_clearScreen();
	setInputMode(GAME);

	// GameEngine is Initialised
	pongEngine_init();
	ResetWDT();
	pongEngine_createBall();
	Displays_forceRefresh(); pongEngine_refreshScore();
	n = 0;
	while (getInputMode() == GAME){
		ResetWDT();
		Displays_forceRefresh();

		if (n < 1) {
					n++;
					dir = pongPhysics_serve ();
					vel = 3;
			}

		if ((pongEngine_getBallLocation_x() <= 50 + 15) && (pongEngine_getBallLocation_x() >= 50 + 10))   {

			if ((pongEngine_getBallLocation_y() <= pongEngine_getPaddleY (1) + 30) && (pongEngine_getBallLocation_y() >= pongEngine_getPaddleY (1) - 30)) {

			paddleBeep();
		    arr = pongPhysics_paddleCollision(vel,dir,1);
		    dir = arr[0];
		    vel = arr[1];

			}
		} else if ((pongEngine_getBallLocation_x() >= 270 - 15) && (pongEngine_getBallLocation_x() <= 270 - 10))  { // -10

			if ((pongEngine_getBallLocation_y() <= pongEngine_getPaddleY (2) + 30) && (pongEngine_getBallLocation_y() >= pongEngine_getPaddleY (2) - 30))  {

			paddleBeep();
			arr = pongPhysics_paddleCollision(vel,dir,2);
			dir = arr[0];
			vel = arr[1];

			}
		}

		// Recording the collsions on the racket
		if ( pongEngine_getBallLocation_y() <= 23 + 20  ) {
			enableInputs(0);
			paddleBeep();
			enableInputs(1);

			dir = pongPhysics_borderCollision(vel, dir);


		} else if ( pongEngine_getBallLocation_y() >= 230 - 10){
			enableInputs(0);
			ballOutBeep();
			enableInputs(1);

			dir = pongPhysics_borderCollision(vel, dir);
		}


		if ( pongEngine_getBallLocation_x() <= 10  ) {
			pongEngine_destroyBall();
			Displays_forceRefresh();
			enableInputs(0);
			paddleBeep();
			enableInputs(1);
			pongEngine_resetPaddles();
			pongEngine_resetBallLoc();
			pongEngine_createBall();
			pongEngine_paddleCreate(1);
			pongEngine_paddleCreate(2);
			pongEngine_moveBall(1, 0);
			pongEngine_moveBall(0, 0);
			Displays_forceRefresh(); pongEngine_refreshScore();
			n = 0;
			pongEngine_addPoint(2);
		} else if ( pongEngine_getBallLocation_x() >= 320 - 10){
			pongEngine_destroyBall();
			enableInputs(0);
			paddleBeep();
			enableInputs(1);
			pongEngine_resetPaddles();
			pongEngine_resetBallLoc();
			pongEngine_createBall();
			pongEngine_paddleCreate(1);
			pongEngine_paddleCreate(2);
			pongEngine_moveBall(1, 0);
			pongEngine_moveBall(0, 0);
			Displays_forceRefresh(); pongEngine_refreshScore();
			n = 0;
			pongEngine_addPoint(1);
		}

		pongEngine_moveBall(dir, vel);

		if (*slider_ptr != last_slider){
			setInputMode(MENUS);
			last_slider = *slider_ptr;
		}
	}
	Displays_clearScreen();
}

