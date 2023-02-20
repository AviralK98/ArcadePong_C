/* For creating the game engine
 * tennisEngine.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISENGINE_H_
#define TENNISENGINE_H_

#include <stdlib.h>
#include <cmath>
#include "tennisSprites.h"
#include "../DE1SoC_SevenSeg/sevenSeg.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../tennisDisplay/tennisDisplay.h"
#define PI 3.14159265359
#define centre_x 160
#define centre_y 120
#define UP 0
#define DOWN 1


// Globally defined

void pongEngine_init( void );
// Locally defined
void pongEngine_moveBall(int angle, int speed);
void pongEngine_createBall(void);
void pongEngine_destroyBall(void);
void pongEngine_setBallLocation(int x, int y);
int pongEngine_getBallAngle(void);
int pongEngine_getBallLocation_x(void);
int pongEngine_getBallLocation_y(void);
void pongEngine_resetBallLoc( void );

// For racket
void pongEngine_paddleMove(int player, int direction, int speed);
void pongEngine_paddleSetYLimits(int maxy, int miny);
void pongEngine_paddleSetYLocation(int player, int y);
void pongEngine_paddleSetXLocation(int player, int x);
void pongEngine_paddleCreate(int player);
void pongEngine_paddleDestroy(int player);
unsigned int pongEngine_getPaddleY(unsigned int paddle);

// Initialising the score
void pongEngine_addPoint(int player);
void pongEngine_resetScore( unsigned int _Refresh );

// Recording the score of the player.
void pongEngine_refreshScore( void );
void pongEngine_resetPaddles( void );


// For Local Use.
int pongEngine_calcAngle(int x1, int y1, int x2, int y2);
void pongEngine_calcBallPathInst(int angle);
void pongEngine_genBallPathInst(int x1, int y1, int x2, int y2);

// Recording the score of the player.
void pongEngine_refreshScore( void );
void pongEngine_resetPaddles( void );



#endif /* TENNISENGINE_H_ */
