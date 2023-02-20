/*
 * tennisSound.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#include "../DE1SoC_WM8731/DE1SoC_WM8731.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include "../HPS_IRQ/HPS_IRQ.h"
#ifndef TENNISSOUND_H_
#define TENNISSOUND_H_

// COnstant Sampling rate
#define F_SAMPLE 48000.0

// Initialising the sound driver
void pongSound_Init( void );
void Sound(int _freq, float _duration);void enableSound(unsigned int _onoff);

// function to set the volume
void setVolume(unsigned int _volume);void toggleSound( void );
// Sin wave modulation for the sound engine.
float lookupSin(unsigned int degree);

// Toggling the sounds
void startSound( void );

void paddleBeep( void );

void ballOutBeep( void );
#endif /* TENNISSOUND_H_ */
