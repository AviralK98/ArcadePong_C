/* Source code for the game engine
 * tennisEngine.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#include "tennisEngine.h"


struct ballPathInst{int x;int y;};
int ballPathInstCounter = 0;
int ballCurrentPosPath = 0;
struct ballPathInst BallPath[1000];
int ballAngle = 361;
short ballColour = 0xFFFF; // Colour of the ball
int ballX = centre_x;
int ballY = centre_y;
int ballMinX = 8;
int ballMaxX = 312;
int ballMinY = 23;
int ballMaxY = 232;
int paddleMinY = 50;
int paddleMaxY = 210;
int paddle1Y = centre_y;
int paddle1X = 50;
int paddle2Y = centre_y;
int paddle2X = 270;
int paddle1Colour = 0xFFFF;
int paddle2Colour = 0xFFFF;
int player1Score = 0;
int player2Score = 0;

// Function to Initialise the game
void pongEngine_init(){
	int topAdjust = 15;
	Displays_clearScreen();
	pongEngine_resetPaddles();
	pongEngine_resetBallLoc();

	pongEngine_paddleCreate(1);
	pongEngine_paddleCreate(2);



	pongSprites_renderRectangle(320,0, topAdjust, 0, (0x1F << 11));
	paddleMinY = pongSprites_getPaddleSizeY()/2;
	paddleMaxY = 240-paddleMinY;

	pongEngine_paddleSetYLimits(paddleMaxY, paddleMinY+topAdjust+1);
}



void pongEngine_resetScore(unsigned int _Refresh){
	player1Score = 0;
	player2Score = 0;
	if (_Refresh != 0){
		pongEngine_refreshScore(); //refresh score
	}
}
void pongEngine_addPoint(int player){

	if(player == 1){
		player1Score++;
	}
	if(player == 2){
		player2Score++;
	}

	pongEngine_refreshScore();
}

void pongEngine_refreshScore(){

	char playerscorech[6];

	int P1number0, P1number1, P2number0, P2number1;


	player1Score = player1Score %100;
	player2Score = player2Score %100;

	P1number0 = player1Score/10;
	P1number1 = player1Score % 10;
	P2number0 = player2Score/10;
	P2number1 = player2Score % 10;

	SDisplay_PNum(player1Score,2);
	SDisplay_PNum(player2Score,0);

	playerscorech[0] = P1number0 + '0';
	playerscorech[1] = P1number1 + '0';
	playerscorech[2] = ' ';
	playerscorech[3] = P2number0 + '0';
	playerscorech[4] = P2number1 + '0';
	playerscorech[5] = '\0';

	pongSprites_renderRectangle(centre_x - 30,centre_x+ 30 , 17, 17+14, 0x00);

	pongSprites_writeText(centre_x - 28, 17, 1, playerscorech, 0xFFFF);

}


// Function for the ball movement
void pongEngine_moveBall(int angle, int speed){
	ResetWDT();
	pongEngine_destroyBall();

	if(ballX < ballMinX){
		ballX = ballMinX;
		ballCurrentPosPath = ballCurrentPosPath-speed;
	}
	if(ballX > ballMaxX){
		ballX = ballMaxX;
		ballCurrentPosPath = ballCurrentPosPath-speed;
	}
	if(ballY < ballMinY){
		ballY = ballMinY;
		ballCurrentPosPath = ballCurrentPosPath-speed;
	}
	if(ballY > ballMaxY){
		ballY = ballMaxY;
		ballCurrentPosPath = ballCurrentPosPath-speed;
	}

	if(angle == ballAngle){

		if(ballCurrentPosPath > ballPathInstCounter){
			ballCurrentPosPath = ballPathInstCounter;
		}

		ballX = BallPath[ballCurrentPosPath].x;
		ballY = BallPath[ballCurrentPosPath].y;
		pongSprites_renderBall(ballX, ballY, ballColour);
		ResetWDT();

		ballCurrentPosPath = ballCurrentPosPath+speed;
	}

	else{
		ballAngle = angle;
		ResetWDT();

		pongEngine_calcBallPathInst(angle);

		ballX = BallPath[ballCurrentPosPath].x;
		ballY = BallPath[ballCurrentPosPath].y;
		pongSprites_renderBall(ballX, ballY, ballColour);

		ballCurrentPosPath = ballCurrentPosPath+speed;
	}
}
// Resetting th ball location
void pongEngine_resetBallLoc( void ){

	ballX = centre_x;
	ballY = centre_y;
}

void pongEngine_setBallLocation(int x, int y){
	pongEngine_destroyBall();
	ResetWDT();
	ballX = x;
	ballY = y;
	pongEngine_calcBallPathInst(ballAngle);
	pongSprites_renderBall(ballX, ballY, ballColour);
	ballCurrentPosPath++;
}

int pongEngine_getBallAngle(void){
	return ballAngle;
}

int pongEngine_getBallLocation_x(void){
	return ballX;
}

int pongEngine_getBallLocation_y(void){
	return ballY;
}

void pongEngine_createBall(void){
	pongSprites_renderBall(ballX, ballY, ballColour);
}

void pongEngine_destroyBall(void){
	pongSprites_renderBall(ballX, ballY, 0x0000);
}

void pongEngine_calcBallPathInst(int angle){
	int x;
	int newangle;
	int foundAngle = 0;
	int angleX;
	int angleY;

	if(angle == 0){
		foundAngle = 1;
		angleX = 0;
		angleY = ballY;
	}
	if(angle == 90){
		foundAngle = 1;
		angleX = ballX;
		angleY = 0;
	}
	if(angle == 180){
		foundAngle = 1;
		angleX = 320;
		angleY = ballY;
	}
	if(angle == 270){
		foundAngle = 1;
		angleX = ballX;
		angleY = 240;
	}

	if(foundAngle == 0){
		for(x = 0; x<240; x++){
			newangle = pongEngine_calcAngle(ballX,ballY,0,x);
			if(newangle == angle){
				foundAngle = 1;
				angleX = 0;
				angleY = x;
			}
		}
	}
	if(foundAngle == 0){
		for(x = 0; x<240; x++){
			newangle = pongEngine_calcAngle(ballX,ballY,320,x);
			if(newangle == angle){
				foundAngle = 1;
				angleX = 320;
				angleY = x;
			}
		}
	}
	if(foundAngle == 0){
		for(x = 0; x<320; x++){
			newangle = pongEngine_calcAngle(ballX,ballY,x,0);
			if(newangle == angle){
				foundAngle = 1;
				angleX = x;
				angleY = 0;
			}
		}
	}
	if(foundAngle == 0){
		for(x = 0; x<320; x++){
			newangle = pongEngine_calcAngle(ballX,ballY,x,240); //calculate angle
			if(newangle == angle){
				foundAngle = 1;
				angleX = x;
				angleY = 240;
			}
		}
	}

	pongEngine_genBallPathInst(ballX, ballY, angleX, angleY);
}


void pongEngine_genBallPathInst(int x1, int y1, int x2, int y2){int dx =  abs (x2 - x1);
	int dy = -abs (y2 - y1);

	int error = dx + dy;
	int error2;

	int sy;
	int sx;
	ballPathInstCounter = 0;
	ballCurrentPosPath = 0;
	if(x1<x2){
		sx = 1;
	}
	else{
		sx = -1;
	}

	if(y1<y2){
		sy = 1;
	}
	else{
		sy = -1;
	}

	while(1){

		BallPath[ballPathInstCounter].x = x1;
		BallPath[ballPathInstCounter].y = y1;
		ballPathInstCounter++;
		if (x1 == x2 && y1 == y2){ break;}
		error2 = 2 * error;

		if (error2 >= dy) {
			error += dy;
			x1 += sx;
		}

		if (error2 <= dx) {
			error += dx;
			y1 += sy;
		}
  }
}

// Function to calculate the collisoin angle
int pongEngine_calcAngle(int x1, int y1, int x2, int y2){

	double diff_y = y1 - y2;
	double diff_x = x1 - x2;

	double angle = atan2(diff_y, diff_x);

	float ang_d = angle * 180/PI;

	int ang_dint = ang_d;

	return ang_dint;
}


void pongEngine_paddleSetYLimits(int maxy, int miny){
	paddleMinY = miny+15;
	paddleMaxY = maxy;
}

void pongEngine_paddleSetYLocation(int player, int y){
	pongEngine_paddleDestroy(player);

	if(y>paddleMaxY){
		y = paddleMaxY;
	}
	if(y<paddleMinY){
		y = paddleMinY;
	}

	if(player == 1){
		paddle1Y = y;
		pongSprites_renderPaddle(paddle1X, y, paddle1Colour);
	}
	if(player == 2){
		paddle2Y = y;
		pongSprites_renderPaddle(paddle2X, y, paddle2Colour);
	}
}

// Function to set the location of the rackets
void pongEngine_paddleSetXLocation(int player, int x){
	pongEngine_paddleDestroy(player);

	if(player == 1){
		paddle1X = x;
		pongSprites_renderPaddle(x, paddle1Y, paddle1Colour);
	}
	if(player == 2){
		paddle2X = x;
		pongSprites_renderPaddle(x, paddle1Y, paddle2Colour);
	}
}
// Fucntion to interact with the paddle
void pongEngine_paddleMove(int player, int direction, int speed){

	int moveto;

	if(player == 1){

		if(direction == UP){
			moveto = paddle1Y+speed;
			pongEngine_paddleSetYLocation(1, moveto);
		}
		if(direction == DOWN){
			moveto = paddle1Y-speed;
			pongEngine_paddleSetYLocation(1, moveto);
		}
	}

	if(player == 2){

		if(direction == UP){
			moveto = paddle2Y+speed;
			pongEngine_paddleSetYLocation(2, moveto);
		}
		if(direction == DOWN){
			moveto = paddle2Y-speed;
			pongEngine_paddleSetYLocation(2, moveto);
		}
	}
}
// Function to initialise the racket back to the original position
void pongEngine_paddleCreate(int player){

	if(player == 1){
		pongSprites_renderPaddle(paddle1X, paddle1Y, paddle1Colour);
	}
	if(player == 2){
		pongSprites_renderPaddle(paddle2X, paddle2Y, paddle2Colour);
	}
}

void pongEngine_paddleDestroy(int player){

	if(player == 1){
		pongSprites_renderPaddle(paddle1X, paddle1Y, 0x0000);
	}
	if(player == 2){
		pongSprites_renderPaddle(paddle2X, paddle2Y, 0x0000);
	}
}

void pongEngine_resetPaddles(){
	pongEngine_paddleDestroy(1);
	pongEngine_paddleDestroy(2);
	pongEngine_paddleSetYLocation(1, centre_y);
	pongEngine_paddleSetYLocation(2, centre_y);
}

unsigned int pongEngine_getPaddleY(unsigned int paddle){
	if (paddle == 1){
		return paddle1Y;
	} else {
		return paddle2Y;
	}
}

