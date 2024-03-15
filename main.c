
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

void ADC_Enable_FVR(void){
    FVRCON=(1<<7)|(0x02<<0);
    while((FVRCON & (1<<6))==0);
}

void ADC_Disable_FVR(void){
    FVRCON=0;
}

void ADC_Init(void){
    if(ADREF!=0){
        ADREF=0;
    }
    if(ADCLK!=63){
        ADCLK=63;
    }
    if(ADACQ!=4){
        ADACQ=4;
    }
    if(ADPRE!=0){
        ADPRE=0;
    }
    if(ADCAP!=1){
        ADCAP=1;
    }
    if(ADCON0!=0x84){
        ADCON0=0x84;
    }
    if(ADCON1!=0){
        ADCON1=0;
    }
}

void ADC_Disable(void){
    ADCON0=0;
}

uint16_t ADC_Read(uint8_t channel){
    ADPCH=channel;
    ADCON0|=(1<<0);
    while(ADCON0 & (1<<0));
    return ADRES;
}

uint16_t ADC_Read_VDD(void){
    ADC_Enable_FVR();
    ADC_Init();
    ADC_Read(0x3F);
    uint32_t temp=ADC_Read(0x3F);
    ADC_Disable();
    ADC_Disable_FVR();
    uint32_t mul_const=2097152;
    mul_const/=temp;
    return (uint16_t)mul_const;
}

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
    
    TRISB&=~(1<<7);
    ANSELB&=~(1<<7);
    LATB&=~(1<<7);
    
    while(1){
        
        LATB|=(1<<7);
        UART_Transmit_Number_NL(ADC_Read_VDD());
        NOP();
        NOP();
        NOP();
        LATB&=~(1<<7);
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
