/* Source code file for game sound.
 * tennisSound.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */


#include "tennisSound.h"
#include "notes.h"

volatile unsigned int SoundOn = 1;

// Declaring Local Variables
volatile int sound = 1;
int freq = 1000;
float duration = 1;
volatile unsigned VOLUME = 4;

// Declaring the Pointers
volatile unsigned char* fifospace_ptr;
volatile unsigned int*  audio_left_ptr;
volatile unsigned int*  audio_right_ptr;
volatile unsigned int* HPS_timer_ptr = (unsigned int *) 0xFFC08000;
double phase = 0.0;
double inc   = 0.0;
// Amplitude initialisation
double baseampl  = 0.0;
signed int audio_sample = 0;
void timerISR(HPSIRQSource interruptID, bool isInit, void* initParams) {
    if (!isInit) {
        volatile unsigned int * HPS_timer_ptr = (unsigned int *) 0xFFC08000;
        HPS_timer_ptr[3];
        // Toggling the sound
        sound = 0;
    }
    //Resetting the  watchdog timer.
    HPS_ResetWatchdog();
}



void pongSound_Init(){

	// Initialsing the Audio Codec

	WM8731_initialise(0xFF203040);
}

void Sound(int _freq, float _duration){

	if (SoundOn){
		freq = _freq; duration = _duration;
		sound = 1;


		HPS_timer_ptr[2] = 0;
		// Setting the time period
		HPS_timer_ptr[0] = duration * 100000;
		HPS_timer_ptr[2] = 0x03;
		HPS_IRQ_registerHandler(IRQ_TIMER_L4SP_0, timerISR);
		HPS_ResetWatchdog();
		WM8731_clearFIFO(true,true);
		fifospace_ptr = WM8731_getFIFOSpacePtr();
		audio_left_ptr = WM8731_getLeftFIFOPtr();
		audio_right_ptr = WM8731_getRightFIFOPtr();
		inc   = ((float) freq) * 360.0 / F_SAMPLE;
		baseampl  = 8388608.0;
		phase = 0.0;

		while(sound == 1){

			if ((fifospace_ptr[2] > 0) && (fifospace_ptr[3] > 0)) {

				phase = phase + inc;

				while (phase >= 360.0) {
					phase = phase - 360.0;
				}

				audio_sample = (signed int)( (1<<VOLUME)*baseampl * lookupSin((int) phase) );
				*audio_left_ptr = audio_sample;
				*audio_right_ptr = audio_sample;
			}
			ResetWDT();
		}
		//  ISR Timer Reset
		HPS_timer_ptr[2] = 0x02;

		HPS_ResetWatchdog();
	}
}

void enableSound(unsigned int _onoff){
	SoundOn = _onoff;
}

void toggleSound(){
	if (SoundOn == 1) { SoundOn = 0; } else SoundOn = 1;
}

void setVolume(unsigned int _volume){
	VOLUME = _volume;
}

// Initialising the sound values
void startSound(){
	unsigned int i;
	unsigned int sequence[] = {C4, D4, E4, F4, G4, 0, G4};
	unsigned int durations[] = {200, 200, 200, 200, 500, 200, 500};
	for (i=0; i<=6; i++){
		Sound(sequence[i], durations[i]);
		ResetWDT();
	}
}
void paddleBeep(){
	Sound(B4, 100);
}

void ballOutBeep(){
	Sound(B3, 100);
}
float lookupSin(unsigned int degree){

	static unsigned int lookup[91] = { 0, 1745, 3490, 5234, 6976, 8716, 10453, 12187, 13917,
						15643, 17365, 19081, 20791, 22495, 24192, 25882, 27564,
						29237, 30902, 32557, 34202, 35837, 37461, 39073, 40674,
						42262, 43837, 45399, 46947, 48481, 50000, 51504, 52992,
						54464, 55919, 57358, 58779, 60182, 61566, 62932, 64279,
						65606, 66913, 68200, 69466, 70711, 71934, 73135, 74314,
						75471, 76604, 77715, 78801, 79864, 80902, 81915, 82904,
						83867, 84805, 85717, 86603, 87462, 88295, 89101, 89879,
						90631, 91355, 92050, 92718, 93358, 93969, 94552, 95106,
						95630, 96126, 96593, 97030, 97437, 97815, 98163, 98481,
						98769, 99027, 99255, 99452, 99619, 99756, 99863, 99939,
						99985, 100000 };
	if (degree <= 90){
		return (float) lookup[degree]/100000;
	}
	else if ((degree > 90) && (degree <= 180)){
		return (float) lookup[180-degree]/100000;
	}
	else if ((degree > 180) && (degree <= 270)){
		return (float) -lookup[degree-180]/100000;
	}
	else if ((degree > 270) && (degree <= 360)){
		return (float) -lookup[360-degree]/100000;
	} else return 0;
}
