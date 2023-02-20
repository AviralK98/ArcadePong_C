/* For creating game physics
 * tennisPhysics.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISPHYSICS_H_
#define TENNISPHYSICS_H_



#include <cmath>
#include <stdlib.h>
#include "tennisSprites.h"
#include "tennisEngine.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../tennisDisplay/tennisDisplay.h"

// Initialising the global variables
int pongPhysics_borderCollision (int speed, int angle);
int pongPhysics_serve (void);
int* pongPhysics_paddleCollision (int speed, int angle, int player);
void resetRand( void );



#endif /* TENNISPHYSICS_H_ */
