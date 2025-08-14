#include "lpc24xx.h"
#include "play_tone.h"
#include "light_sensor.h" // For physical ladder

#include "initialise_board.h"
 
// Each note has three parts:
// Duration, Pitch, Volume

// Duration is 'unitless' and is scaled by the 'rate' value in main.c
// Pitch is the period of the note, in useconds.
// Volume is from 0 to 0x3FF, off to fully on.


// OFF is designed to sound unpleasant if silence is not implemented
// in the user's code.
 
#define OFF		100

#define C4 		3831
#define CS4 	3610
#define D4 		3401
#define DS4 	3215
#define E4 		3030
#define F4 		2857
#define FS4 	2725
#define G4 		2551
#define GS4 	2410
#define A4 		2272
#define AS4 	2146
#define B4 		2024

#define C5 		C4/2
#define CS5 	CS4/2
#define D5 		D4/2
#define DS5 	DS4/2
#define E5 		E4/2
#define F5 		F4/2
#define FS5 	FS4/2
#define G5 		G4/2
#define GS5 	GS4/2
#define A5 		A4/2
#define AS5 	AS4/2
#define B5 		B4/2

#define C6 		C5/2
#define CS6 	CS5/2
#define D6 		D5/2
#define DS6 	DS5/2
#define E6 		E5/2
#define F6 		F5/2
#define FS6 	FS5/2
#define G6 		G5/2
#define GS6 	GS5/2
#define A6 		A5/2
#define AS6 	AS5/2
#define B6 		B5/2

#define C3 		C4*2
#define CS3 	CS4*2
#define D3 		D4*2
#define DS3 	DS4*2
#define E3 		E4*2
#define F3 		F4*2
#define FS3 	FS4*2
#define G3 		G4*2
#define GS3 	GS4*2
#define A3 		A4*2
#define AS3 	AS4*2
#define B3 		B4*2

// Define a shortened "We Wish You a Merry Christmas" song
struct tone christmas_intro[] = {
	{4, D5, 0x300},  // "We"
	{4, G5, 0x300},  // "wish"
	{2, G5, 0x300},  // "you"
	{2, A5, 0x300},  // "a"
	{2, G5, 0x300},  // "Merry"
	{2, FS5, 0x300},
	{4, E5, 0x300},  // "Christmas"
	{4, E5, 0x300},
	{4, E5, 0x300},  // "We"
	{4, A5, 0x300},  // "wish"
	{2, A5, 0x300},  // "you"
	{2, B5, 0x300},	 // "a"
	{2, A5, 0x300},	 // "Merry"
	{2, G5, 0x300},
	{4, FS5, 0x300},  // "Christmas"
	{4, D5, 0x300},
	{4, D5, 0x300},  // "We"
	{4, B5, 0x300},  // "wish"
	{2, B5, 0x300},  // "you"
	{2, C6, 0x300},	 // "a"
	{2, B5, 0x300},	 // "Merry"
	{2, A5, 0x300},
	{4, G5, 0x300},  // "Christmas"
	{4, E5, 0x300},
	{2, D5, 0x300},	 // "and"
	{2, D5, 0x300},	 // "a"
	{4, E5, 0x300},	 // "Happy"
	{4, A5, 0x300},
	{4, FS5, 0x300},	 // "New"
	{8, G5, 0x300},	 // "Year"
};

// Number of notes in intro
int intro_length = sizeof(christmas_intro)/sizeof(christmas_intro[0]);

// Map pitch to number of LEDs (0–8)
int pitch_to_led(int period) {
	if(period <= C6) return 8;
	else if(period <= B5) return 7;
	else if(period <= A5) return 6;
	else if(period <= G5) return 5;
	else if(period <= F5) return 4;
	else if(period <= E5) return 3;
	else if(period <= D5) return 2;
	else return 1;
}

// Play intro sequence and light physical LED ladder
void play_christmas_intro() {
	int leds_on;
	int i;
	for(i=0; i<intro_length; i++) {
		struct tone t = christmas_intro[i];

		// Play note
		play_tone(t.duration * 52000, t.pitch, t.volume); // scale duration as needed

		// Update LED ladder
		leds_on = pitch_to_led(t.pitch);
		displayLadder(leds_on, 1); // function to light physical LEDs
	}

	displayLadder(0, 1);
}
