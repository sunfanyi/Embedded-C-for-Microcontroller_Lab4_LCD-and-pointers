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
    
    unsigned char score = 0;
    unsigned char player_pos = 0xC0 + 1;  // position at the second row
    unsigned char block_pos = 0XC0 + 15;  // position at the end of the second row
    unsigned char player[] = {  // person character
        0b00000,
        0b10101,
        0b01110,
        0b00100,
        0b00100,
        0b01010,
        0b01010,
        0b00000  // cursor position
    };
    unsigned char block[] = {  // obstacle character
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b00000,  // cursor position
    };
	LCD_create_character(player,0);
    LCD_create_character(block,1);
    
    LCD_update_screen(player_pos, block_pos, score);
    
    while(1){
        Sleep();
        if (T0CON0bits.T0OUT) {  // when waking from timer interrupt
            Timer0_restart(score);
            if (--block_pos < 0xC0) {  // when out of screen
                block_pos = 0xC0 + 15;  // new block coming
                score++;
            }
            LCD_sendbyte(1,0);  // clear display
            __delay_ms(2);
            LCD_update_screen(player_pos, block_pos, score);
        } else {  // when waking from comparator interrupt
            player_pos = LCD_jump(player, block, player_pos, block_pos, score);
        }
        if (player_pos == block_pos) {
            LCD_game_over();
            score = 0;
        }
    }
}

