#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
    PIE2bits.C1IE = 1;  // enable Comparator 1 Interrupt Enable bit (Peripheral Interrupt Enable Register 2)
    INTCONbits.GIEL = 1;  // turn on peripheral interrupts
    PIE0bits.TMR0IE = 1;  // turn on timer interrupt
    INTCONbits.GIE = 1;  // turn on global interrupts 
}


/************************************
 * High priority interrvoid Interrupts_init(void)
************************************/
void __interrupt(high_priority) HighISR()
{
    // comparator interrupt
    if (PIR2bits.C1IF) {
        PIR2bits.C1IF = 0;  // clear the flag
    }
    // Timer0 interrupt
    if (PIR0bits.TMR0IF) {
        PIR0bits.TMR0IF = 0;  // clear the flag
    }
}