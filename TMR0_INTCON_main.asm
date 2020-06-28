; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR    
; PIC16F877A Configuration Bit Settings
; Assembly source line config statements

#include "p16f877a.inc"

; CONFIG
; __config 0x3F39
 __CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _BOREN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _CP_OFF

 
RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program
IRQ	CODE	0X04
	GOTO	IRQ_ROUTINE

; TODO ADD INTERRUPTS HERE IF USED

MAIN_PROG CODE                      ; let linker place main program

 #DEFINE    CONTA	    0X20
 #DEFINE    CONTA2	    0X21
 #DEFINE    LED_RED_1	    PORTC,0
 #DEFINE    LED_GREEN_1	    PORTC,1
 #DEFINE    LED_RED_2	    PORTC,3
 #DEFINE    LED_GREEN_2	    PORTC,4
 
START
     
    BSF	    STATUS,RP0
    BCF	    STATUS,RP1
    CLRF    TRISC
    MOVLW   b'00000111'
    MOVWF   OPTION_REG
    BCF	    STATUS,RP0
    BCF	    STATUS,RP1
    MOVLW   b'10100000'	;modificado
    MOVWF   INTCON
    CLRF    PORTC
    CLRF    CONTA
    CLRF    CONTA2
    MOVLW   .65
    MOVWF   TMR0
    
LOOP_1:
    CALL    viaEspera
    MOVF    CONTA2,W
    XORLW   .3
    BTFSS   STATUS,Z
    GOTO    LOOP_1
    CLRF    CONTA2

LOOP_2:
    CALL    viaAncha
    MOVF    CONTA2,W
    SUBLW   .24
    BTFSC   STATUS,C
    GOTO    LOOP_2
    CLRF    CONTA2
    
LOOP_3:
    CALL    viaEspera
    MOVF    CONTA2,W
    XORLW   .3
    BTFSS   STATUS,Z
    GOTO    LOOP_3
    CLRF    CONTA2

LOOP_4:    
    CALL    viaAngosta
    MOVF    CONTA2,W
    SUBLW   .16
    BTFSC   STATUS,C
    GOTO    LOOP_4
    CLRF    CONTA2
    GOTO    LOOP_1
    
viaEspera:
    BSF	    LED_RED_1
    BSF	    LED_GREEN_1
    BSF	    LED_RED_2
    BSF	    LED_GREEN_2
    RETURN

viaAncha:
    BCF	    LED_RED_1
    BSF	    LED_GREEN_1
    BSF	    LED_RED_2
    BCF	    LED_GREEN_2
    RETURN

viaAngosta:
    BSF	    LED_RED_1
    BCF	    LED_GREEN_1
    BCF	    LED_RED_2
    BSF	    LED_GREEN_2
    RETURN

IRQ_ROUTINE:
    BCF	    INTCON,TMR0IF
    MOVLW   .61
    MOVWF   TMR0
    INCF    CONTA
    MOVF    CONTA,W
    XORLW   .10
    BTFSS   STATUS,Z
    RETFIE
    INCF    CONTA2
    CLRF    CONTA
    RETFIE

    END