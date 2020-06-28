/*
 * File:   main.c
 * Author: jonathan Guerrero
 *
 * Created on 27 de junio de 2020, 05:59 PM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
/*
#define     LED_RED_1       PORTC,0;
#define     LED_GREEN_1     PORTC,1;
#define     LED_BLUE_1      PORTC,2;
#define     LED_RED_2       PORTC,3;
#define     LED_GREEN_2     PORTC,4;
#define     LED_BLUE_2      PORTC,5;
 */


static  int conta;
static  int conta2;

void __interrupt() tcint (void){
    if (INTCONbits.T0IE && INTCONbits.T0IF)
    {
        conta++;
        INTCONbits.T0IF=0;
        TMR0=62;
        if(conta==10)
        {
            conta2++;
            conta = 0;
        }
    }
}
    
void viaEspera()
{
    PORTCbits.RC0   =   1;
    PORTCbits.RC1   =   1;
    PORTCbits.RC3   =   1;
    PORTCbits.RC4   =   1;
}

void viaAncha()
{
    PORTCbits.RC0   =   0;
    PORTCbits.RC1   =   1;
    PORTCbits.RC3   =   1;
    PORTCbits.RC4   =   0;
}

void viaAngosta()
{
    PORTCbits.RC0   =   1;
    PORTCbits.RC1   =   0;
    PORTCbits.RC3   =   0;
    PORTCbits.RC4   =   1;
}
void main(void) {
    TRISC   =   0;
    OPTION_REG  =   0X07;
    INTCON      =   0XA0;
    
    while(1)
    {
        conta2 = 0;
        TMR0    =   61;
        while(conta2 < 2)
        {
            viaEspera();
        }
        conta2 = 0;
        TMR0    =   61;
        while(conta2 < 28)
        {
            viaAncha();
        }
        conta2 = 0;
        TMR0    =   61;
        while(conta2 < 2)
        {
            viaEspera();
        }
        conta2 = 0;
        TMR0    =   61;
        while(conta2< 20)
        {
            viaAngosta();
        }
    }
    
    return;
}
