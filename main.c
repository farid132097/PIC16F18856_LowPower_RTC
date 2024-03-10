
/*
 * File:   main.c
 * Author: faridul45219
 * PIC18856 Test
 * Created on March 10, 2024, 4:07 PM
 */

#define  _XTAL_FREQ 32000000UL
#include <stdio.h>
#include <stdlib.h>
#include "configbits.h"
#include "uart.h"
#include "sleep.h"
#include "wdt.h"

volatile uint16_t val=0;

void main(void) {
    
    UART_Init(115200);
    
    T0CON1 = (4<<5); //LFINT
    T0CON1|= (1<<4); //ASYNC
    T0CON1|= (7<<0); //Scale 128
    T0CON0 = (1<<7); //T0EN
    PIR0  &=~(1<<5); //TMR0IF
    PIE0  |= (1<<5); //TMR0IE
    INTCON|= (1<<6); //PEIE
    INTCON|= (1<<7); //GIE
    VREGCON|=(1<<1); //LPM
    FVRCON = 0;      //FVR OFF
    
    while(1){
        
        UART_Transmit_Number_NL(val);
        NOP();
        NOP();
        NOP();
        SLEEP();
    }
    
    return;
}

void interrupt ISRs(void){
    UART_ISR_Routine();
    if(PIR0 & (1<<5)){
        PIR0 &=~(1<<5);
        val++;
    }
}
