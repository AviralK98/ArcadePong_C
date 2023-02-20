/* For bitmapping and displaying the text
 * tennisSprites.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISSPRITES_H_
#define TENNISSPRITES_H_

#include "../tennisDisplay/tennisDisplay.h"
#include "tennisEngine.h"
#include "../BasicFont/BasicFont.h"
#include <string.h>

#define SMALL 0
#define LARGE 1
// Initialising the bitmapping
void pongSprites_renderRectangle(int x1,int x2, int y1, int y2, int colour);
void pongSprites_changePaddleSize(unsigned int size);
unsigned int pongSprites_getPaddleSizeY( void );
void pongSprites_initBall( void );
void pongSprites_renderPaddle(int x, int y, short colour);
void pongSprites_renderBall(int x, int y, short colour);
void pongSprites_writeText(int x, int y, int size, char *text, short colour);


#endif /* TENNISSPRITES_H_ */
