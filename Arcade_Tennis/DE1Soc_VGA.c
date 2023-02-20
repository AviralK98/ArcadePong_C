/*
 * DE1Soc_VGA.c
 *
 *  Created on: 12 May 2022
 *      Author: Aviral
 */
#include "DE1SoC_VGA.h"

short vga_address = 0x0;
short vga_charaddr = 0x0;
volatile int pixel_buffer_start;

//Initialising the  addresses of VGA
void VGA_init(short vgaPixelBuffer_address, short vgaCharBuffer_address){
	volatile int * pixel_ctrl_ptr = (int *) 0xFF203020;
	*(pixel_ctrl_ptr + 1) = 0xC8000000;
	pixel_buffer_start = *pixel_ctrl_ptr;
	*(pixel_ctrl_ptr + 1) = 0xC0000000;
	vga_address = vgaPixelBuffer_address;
	vga_charaddr = vgaCharBuffer_address;

	VGA_clearScreen();
}

// Clearing the Screen
void VGA_clearScreen(){
	  int x, y;
	  for (x = 0; x < 320; x++) {
	    for (y = 0; y < 240; y++) {

	    	VGA_drawPixel(x,y,0x0000);
		}
	  }
}
// Assigning particular colour to the particular pixel.
void VGA_drawPixel(int x, int y, short colour){
	volatile short *vga_addr=(volatile short*)(0xC8000000 + (y<<10) + (x<<1));
	*vga_addr=colour;
}
// Filling the background
void VGA_fillColour(short colour){
	  int x, y;
	  for (x = 0; x < 320; x++) {
	    for (y = 0; y < 240; y++) {
	    	//set all pixels to colour
	    	VGA_drawPixel(x,y,colour);
		}
	  }
}


