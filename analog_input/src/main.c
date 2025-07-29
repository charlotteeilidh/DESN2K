#include "lpc24xx.h"

void setupADC(void);
int readADC(void);

int main(void) {
	int result;
	
	setupADC();

	//Loop forever, reading ADC channel AD0.2
	while (1) {
		result = readADC(); // for LEDs I'll need to make use of 'result'!!!
	}		
}

// Initialize any required registers for the ADC functionality here
void setupADC(void) {
	int input;
	int	clk_div;
	
	PCONP = 0x01 << 12; // to power on PCAD (A/D converter)
	PINSEL1 = 0x01 << 18; // ADC input (AD0.2)

	
	input = 0x01 << 2; // (to set AD0.2 (input) HI)
	clk_div = 0x0F << 8;

	AD0CR = input | clk_div;
}

// Function to sample and return ADC channel AD0.2
// NOTE: You must setup the entire ADC Control Register before EVERY sample.
int readADC(void) {
	setupADC(); // do i need this?
	
	return (AD0DR2 >> 6) & 0x3FF; // (0x3FF to keep bits 9:0);
}
