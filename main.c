// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include <stdio.h>
#include "LCD.h"
//#include "ADC.h"
#include "comparator.h"
#include "interrupts.h"
#include "timers.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) {
    LCD_Init(); //Initialise LCD
//    ADC_init();
    Comp1_init();
    Interrupts_init();
    Timer0_init();
    
    unsigned char player_pos = 2;
    
//	unsigned int ADC_val;
//    char buf[0]; //create buffer address using an array
    unsigned char obstacle[] = {
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00011111,
        0b00000000,
    };
	
    LCD_disp_customised(obstacle,0,player_pos);
    TRISDbits.TRISD7 = 0;
    while(1){
        Sleep();
        if (T0CON0bits.T0OUT) {  // when waking from timer interrupt
            Timer0_restart();
            player_pos = 1;
            LCD_disp_customised(obstacle,0,player_pos);
        } else {  // when waking from comparator interrupt
            player_pos = 1;
            LCD_disp_customised(obstacle,0,player_pos);
        }
//        ADC_val = ADC_getval(); //Read ADC voltage from LDR and place in variable
//        ADC2String(buf, ADC_val); //give buffer address and ACD reading to function for processing
//        __delay_ms(300); //delay 300ms for display
    }
}

