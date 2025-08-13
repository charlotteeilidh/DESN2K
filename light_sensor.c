#include "lpc24xx.h"
#include "light_sensor.h"

// Initialize any required registers for the ADC functionality here
void setupADC(void) {
	// power ON ADC
	PCONP |= 0x1 << 12;
	// configure ADC using ADCR
	AD0CR = 0x00200F02; // START 26:24 initialised to 000, AD01
	//AD0CR = 0x00200F04; // AD02
	
	// Connect ADO.1 and set input (light sensor)
	PINSEL1 &= ~(0x3 << 16);
	PINSEL1 |= 0x1 << 16;
	FIO0DIR &= ~(0x1 << 24);
	
	// Connect ADO.2 and set input (potentiometer)
	//PINSEL1 &= ~(0x3 << 18);
	//PINSEL1 |= 0x1 << 18;
	//FIO0DIR &= ~(0x1 << 25);
}

// Function to sample and return ADC channel AD0.1
// NOTE: You must setup the entire ADC Control Register before EVERY sample.
int readADC(void) {
	int result;
	int mask = 0x3FF;
	
	setupADC();
	AD0CR |= (0x01 << 24); // configures START bits to 001 (start immediately)
	
	while ((AD0DR1 >> 31) != 0x01);
	result = ((AD0DR1 >> 6) & mask);
	
	//while ((AD0DR2 >> 31) != 0x01);
	//result = ((AD0DR2 >> 6) & mask);
	
	return result;
}

void displayADC(int val) {
	char str[10];
	sprintf(str, "value: %d", val);
	lcd_putString(10,10,str);
}

void setupLadder(void) {
	// LEDs
	FIO2DIR |= 0xFF << 1;
	FIO0DIR |= 0x01 << 22;
	// enable
	FIO0SET |= 0x01 << 22;
}

void displayLadder(int val, int scale) {
	int i;
	double level = val / scale * 8;

	FIO2CLR |= 0xFF << 1;
	for (i = 1; (double)i <= level; i++) {
		FIO2SET = (0x1 << i);
	}
}
