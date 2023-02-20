/* Header File for Initialising the screen.
 * tennisScreens.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISSCREENS_H_
#define TENNISSCREENS_H_

#include "../tennisInputs/tennisInputs.h"
#include "../tennisSound/tennisSound.h"
#include "../tennisSound/notes.h"
#include "../tennisEngine/pongSprites.h"
#include "../tennisDisplay/tennisDisplay.h"
#include "../DE1SoC_SevenSeg/sevenSeg.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../HPS_usleep/HPS_usleep.h"
#include "../tennisEngine/tennisPhysics.h"
#include <stdio.h>
#include <stdbool.h>

#define _BLACK   (0x0000)
#define _WHITE   (0xFFFF)
#define _RED     (0xF800)
#define _GREEN   (0x07C0)
#define _BLUE    (0x001F)
#define _YELLOW  (_RED | _GREEN)
#define _CYAN    (_GREEN | _BLUE)
#define _MAGENTA (_BLUE | _RED)

void menuMove(unsigned int direction);void setMenu(unsigned int _menuSelector, unsigned int _setting);
void startScreen( void );void testScreen( void );
void testScreen_AI( void );void gameMenu( void );

#endif /* TENNISSCREENS_H_ */
