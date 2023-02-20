/* For creating header files for the driver display for the game
 * tennisDisplay.h
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */

#ifndef TENNISDISPLAY_H
#define TENNISDISPLAY_H

#include "../DE1Soc_LT24/DE1Soc_LT24.h"
#include "../DE1Soc_VGA/DE1Soc_VGA.h"
#include "../HPS_Watchdog/HPS_Watchdog.h"
#include <string.h>

#define NOFRAMEBUFFER 0
#define SOFTWAREFB 1
#define SOFTWAREQUADFB 2
#define SOFTWAREOCTOFB 3
#define HARDWAREFB 4
#define FASTFB 5

// Variables defined for Displaying the new Screen

void DisplaysLocal_singleRefresh( void );
void DisplaysLocal_quadRefresh( void );
void DisplaysLocal_octoRefresh( void );

// These functions can be used outside of the scope of this file since they use global variables.

void Displays_init(volatile int vga_PixelAddress, unsigned volatile int vga_CharacterAddress, unsigned volatile int lcd_pio_base, unsigned volatile int lcd_hw_base);
void Displays_drawPixel(int x, int y, short colour);
void Displays_frameSkip(int skipamount);
void Displays_clearScreen( void );
void Displays_Refresh( void );
void Displays_forceRefresh( void );
void Displays_setPixel(int x, int y, short colour);
void Displays_setWindow(int minx, int miny, int maxx, int maxy);
short Displays_getPixel(int x, int y);
void Displays_mode(int mode);
void Displays_fillColour(short colour);
void Displays_mode(int mode);




#endif

