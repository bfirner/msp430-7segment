# msp430-7segment
Just a header file and some example code to help you use a 7 segment display with the MSP430.

Just include the 7segment.h file to get started. The assumed pin assignments are listed in the header file. If you change them, be sure to change which segments belong to which ports as well.

Use the code in Examples/test_pins.c to verify that your pins are set up correctly. This example code uses the external crystal oscillator as the clock source for TimerA0 (used to switch from one digit to another), so if you do not have an external crystal switch to a different clock source.
