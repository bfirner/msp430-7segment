/*
 * 7segment.h
 * Register settings for a 4 digit 7-segment display, with optional
 * decimal point as an 8th segment. Currently the pin locations
 * are #defines, but as a TODO I will see if I can simplify this
 * with some template metaprogramming.
 *
 *  Created on: Mar 11, 2015
 *      Author: Bernhard Firner
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

//Mapping from the output pins to the segments on the display
/*
 * P1.0 - E
 * P1.1 - D
 * P1.2 - DP (decimal point)
 * P1.3 - C
 * P1.4 - G
 * P1.5 - Digit 4 Enable (when pulled low)
 * P1.6 - B
 * P1.7 - Digit 3 Enable (when pulled low)
 * P2.0 - Digit 2 Enable (when pulled low)
 * P2.1 - F
 * P2.2 - A
 * P2.3 - Digit 1 Enable (when pulled low)
 */

/*
 * The digits look like this:
 *
 *   _A__
 * F|    |B
 *  |_G__|
 * E|    |C
 *  |____|
 *    D
 *
 *    0 is ABCDEF
 *    1 is B|C
 *    2 is ABDEG
 *    3 is ABCDG
 *    4 is BCFG
 *    5 is ACDFG
 *    6 is ABCDEG
 *    7 is ABC
 *    8 is ABCDEFG
 *    9 is ABCFG
 */

//A is P2.2, B is P1.6, C is P1.3, D is P1.1, E is P1.0
#define SEGA BIT2
#define SEGB BIT6
#define SEGC BIT3
#define SEGD BIT1
#define SEGE BIT0
//F is P2.1, G is P1.4
#define SEGF BIT1
#define SEGG BIT4

//Turn on the segments to display different numbers
#define ZERO P1OUT |= SEGB | SEGC | SEGD | SEGE; P2OUT |= SEGA | SEGF;
#define ONE P1OUT |= SEGB | SEGC;
#define TWO P1OUT |= SEGB | SEGD | SEGE | SEGG; P2OUT |= SEGA;
#define THREE P1OUT |= SEGB | SEGC | SEGD | SEGG; P2OUT |= SEGA;
#define FOUR P1OUT |= SEGB | SEGC | SEGG; P2OUT |= SEGF;

//Turn off all of the segments
#define ALLOFF P2OUT &= ~(SEGA|SEGF); P1OUT &= ~(SEGB|SEGC|SEGD|SEGE|SEGG);

//Enable or disable one of the four 7-segment displays
//1 is the far left and 4 is the far right
#define CHAR4ENABLE P1OUT &= ~BIT5
#define CHAR4DISABLE P1OUT |= BIT5

#define CHAR3ENABLE P1OUT &= ~BIT7
#define CHAR3DISABLE P1OUT |= BIT7

#define CHAR2ENABLE P2OUT &= ~BIT0
#define CHAR2DISABLE P2OUT |= BIT0

#define CHAR1ENABLE P2OUT &= ~BIT3
#define CHAR1DISABLE P2OUT |= BIT3

#endif /* SEVENSEGMENT_H_ */
