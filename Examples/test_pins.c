/*
 * Example code to use a 4 character 7-segment display
 */

#include <msp430.h> 

#include "7segment.h"


int digit = 0;
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timerA(void) {
	//Have each display character display its number (1, 2, 3, or 4)
	switch(digit) {
	case 0:
		digit = 1;
		ALLOFF;
		CHAR1DISABLE;
		CHAR4ENABLE;
		FOUR;
		break;
	case 1:
		digit = 2;
		ALLOFF;
		CHAR4DISABLE;
		CHAR3ENABLE;
	    THREE;
		break;
	case 2:
		digit = 3;
		ALLOFF;
		CHAR3DISABLE;
		CHAR2ENABLE;
	    TWO;
		break;
	case 3:
		ALLOFF;
		CHAR2DISABLE;
		CHAR1ENABLE;
	    ONE;
		//Set the digit back to 0
	default:
		digit = 0;
	}

	//Just stay in low power sleep
	//LPM3_EXIT;
}


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    //Set up pins for low power and the crystal oscillator
	const unsigned char XIN = BIT6;
	const unsigned char XOUT = BIT7;

    P1DIR = 0xFF;
    P1OUT = 0x00;

	P2DIR = ~XIN;
	P2OUT = 0;
	P2SEL = XIN | XOUT;

	//Turn off all of the display characters to start
    CHAR1DISABLE;
    CHAR2DISABLE;
    CHAR3DISABLE;
    CHAR4DISABLE;

	//Set up the crystal oscillator as the clock
	//ACLK divider is 0
	BCSCTL1 |= DIVA_0;
	//12.5pF cap for the crystal oscillator
	BCSCTL3 |= XCAP_3;
	//Select VLO
	//BCSCTL3 |= LFXT1S_2;

	//Set to mode 1 (count up to TACCR0), divide by 8, input is ACLK, interrupt enabled
	TA0CTL = MC_1 | TASSEL_1 | ID_3;
	//Trigger 4000 times per second
	TACCR0 = 1;
	TACCTL0 |= CCIE;
	__enable_interrupt();

	//Enter LPM3 and stay there forever
	LPM3;

	return 0;
}
