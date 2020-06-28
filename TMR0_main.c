/*
 * File:   main.c
 * Author: jonat
 *
 * Created on 22 de junio de 2020, 07:54 PM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>

static  int CONTA1;
static  int CONTA2;

void noPasoVia (void)
{
        PORTCbits.RC0   =   1;
        PORTCbits.RC1   =   1;
        PORTCbits.RC3   =   1;
        PORTCbits.RC4   =   1;
}

void pasoViaGrande(void)
{
        PORTCbits.RC0   =   1;
        PORTCbits.RC1   =   0;
        PORTCbits.RC3   =   0;
        PORTCbits.RC4   =   1;        
}

void pasoViaAngosta(void)
{
    PORTCbits.RC0   =   0;
    PORTCbits.RC1   =   1;
    PORTCbits.RC3   =   1;
    PORTCbits.RC4   =   0;    
}

void retardo15s()
{    
    CONTA2  =   27;
    TMR0    =   0;
    
    while (CONTA2 > 0)     
    {
        CONTA2 = CONTA2 - 1;
        CONTA1 = 9;
        while (CONTA1 >= 0)
        {
            CONTA1 = CONTA1 - 1;
            //CONFIGURACION OPTION_REG
            /*OPTION_REGbits.INTEDG = 0;
            OPTION_REGbits.T0CS =   0;
            OPTION_REGbits.T0SE =   0;
            OPTION_REGbits.PSA  =   0;
            OPTION_REGbits.PS   =   7;
             * */
            OPTION_REG  =   0X07;
            TMR0    =   0;
            while(TMR0 <= 194)
            {
                (TMR0);
            }
        }
    }
}    

void retardo10s()
{    
    CONTA2  =   18;
    TMR0    =   0;
    
    while (CONTA2 > 0)     
    {
        CONTA2 = CONTA2 - 1;
        CONTA1 = 9;
        while (CONTA1 > 0)
        {
            CONTA1 = CONTA1 - 1;
            //CONFIGURACION OPTION_REG
            /*OPTION_REGbits.INTEDG = 0;
            OPTION_REGbits.T0CS =   0;
            OPTION_REGbits.T0SE =   0;
            OPTION_REGbits.PSA  =   0;
            OPTION_REGbits.PS   =   7;
             * */
            OPTION_REG  =   0X07;
            TMR0    =   0;
            while(TMR0 <= 194)
            {
                (TMR0);
            }
        }
    }
}    

void retardo1500mS()
{    
    CONTA2  =   3;
    TMR0    =   0;
    
    while (CONTA2 >= 0)     
    {
        CONTA2 = CONTA2 - 1;
        CONTA1 = 9;
        while (CONTA1 > 0)
        {
            CONTA1 = CONTA1 - 1;
            //CONFIGURACION OPTION_REG
            /*OPTION_REGbits.INTEDG = 0;
            OPTION_REGbits.T0CS =   0;
            OPTION_REGbits.T0SE =   0;
            OPTION_REGbits.PSA  =   0;
            OPTION_REGbits.PS   =   7;
             * */
            OPTION_REG  =   0X07;
            TMR0    =   0;
            while(TMR0 <= 194)
            {
                (TMR0);
            }
        }
    }
}    

void main(void) { 
    
    TRISC   =   0;      //puerto c como salida
    while(1){
        noPasoVia();
        retardo1500mS();
        pasoViaGrande();
        retardo15s();
        noPasoVia();
        retardo1500mS();
        pasoViaAngosta();
        retardo10s();        
    }
    return;
}