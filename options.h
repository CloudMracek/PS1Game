/* This is a options file which serves the purpose of 
changing common variables like screen resolution */

#pragma once

#define LOAD_FONT
//#define DEBUG_VERTEX_ORDER

// The functions required to access memory cards are missing from Lameguy's
// PSn00bSDK master branch.
//#define USE_MEMORY_CARD

#define OT_LEN			4096
#define PACKET_LEN		16384

#define SCREEN_XRES		320
#define SCREEN_YRES		240

#define CENTERX			(SCREEN_XRES / 2)
#define CENTERY			(SCREEN_YRES / 2)
