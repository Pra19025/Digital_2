/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 25 de febrero de 2021, 06:58 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"
#include "UART.h"
#include "GY-521.h"

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000

//**********************************************************************************************************************************************
// Variables
//***********************************************************************************************************************************************
char* buffer;
int status;
float datos[7];
char entrada;
//***********************************************************************************************************************************************
// Prototipos de funciones
//**********************************************************************************************************************************************
void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {

    if (PIR1bits.RCIF) {
        entrada = RCREG;
        if (entrada == 'A') {
            PORTAbits.RA0 = 1;
        }
        if (entrada == 'B') {
            PORTAbits.RA0 = 0;
        }
        if (entrada == 'C') {
            PORTAbits.RA0 = 1;
        }
        if (entrada == 'D') {
            PORTAbits.RA0 = 0;
        }
    }
}

void main(void) {
    __delay_ms(1000);
    Setup();
    I2C_Master_Init();
    UARTInit(9600, 1);
    GY_init();



    while (1) {
        GY_read(datos);


        buffer = ftoa(datos[0], status);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[1], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[2], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[3], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[4], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);
        buffer = ftoa(datos[5], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[6], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        UARTSendChar('\n');

    }
    return;
}

void Setup(void) {

    ANSEL = 0;
    TRISA = 0;
    PORTA = 0;

    // configuracion de la interrupcion 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1; // se activa
    return;

}

