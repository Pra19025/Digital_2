/*
 * File:   mainMaestro.c
 * Author: Noel Prado
 *
 * Created on 23 de febrero de 2021, 10:18 AM
 */


#include <xc.h>
#include <stdint.h>
#include "I2C.h"
#include "UART.h"
#include "GY-521.h"
#include <stdio.h>
#include <stdlib.h>

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


//***********************************************************************************************************************************************
// Prototipos de funciones
//**********************************************************************************************************************************************
void Setup(void);
//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {


}

void main(void) {
    Setup();

    //la mera direccion es 0xD0
    //0xD1 para leer 
    //0xD0 para escribir
    __delay_ms(100);
    I2C_Master_Init(100000); // 100kHz
    // frecuencia de revision de datos (sample rate)

    GY_init();


    while (1) {

        PORTAbits.RA0 = ~PORTAbits.RA0; // Blink LED     
        GY_Read();
        __delay_ms(500);




    }


    return;
}

void Setup(void) {

    UARTInit(9600, 1);


    TRISA = 0;
    PORTA = 0;
    TRISC = 0;
    PORTC = 0;
    ANSEL = 0;
    ANSELH = 0;






    return;
}
