#include "lpc24xx.h"
#include "lcd_hw.h"
#include "lcd_grph.h"
#include "font5x7.h"

#define LADDER_X_START 225
#define LADDER_WIDTH   10
#define LADDER_LED_HEIGHT 25
#define LADDER_Y_START 20
#define LADDER_SPACING 3

void displayVirtualLadder(int adcValue, int scale) {
	int i;
	int numLit = (adcValue * 8) / scale;  // scale 0–1023 ? 0–8 LEDs

	for (i = 0; i < 8; i++) {
			int y0 = LADDER_Y_START + (7 - i) * (LADDER_LED_HEIGHT + LADDER_SPACING);
			int y1 = y0 + LADDER_LED_HEIGHT;

			if (i < numLit) {
					// Lit LED (green)
					lcd_fillRect(LADDER_X_START, y0, LADDER_X_START + LADDER_WIDTH, y1, GREEN);
			} else {
					// Unlit LED (dark gray)
					lcd_fillRect(LADDER_X_START, y0, LADDER_X_START + LADDER_WIDTH, y1, DARK_GRAY);
			}
	}
}
