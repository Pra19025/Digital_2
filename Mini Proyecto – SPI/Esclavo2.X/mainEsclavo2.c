/*
 * File:   mainEsclavo2.c
 * Author: Noel Prado
 *
 * Created on 11 de febrero de 2021, 09:11 AM
 */
#include <xc.h>
#include <stdint.h>
#include "SPI.h"

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

//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
volatile uint8_t contador = 0;
uint8_t debounce1;
uint8_t debounce2;

//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {
    
    if (INTCONbits.RBIF == 1) {

        INTCONbits.RBIF = 0;

        if (PORTBbits.RB1 == 1) { //si se presionar RB1 se disminuye el valor del puerto A
            debounce2++;
            if (debounce2 > 1) { //algoritmo del antirrebote, se usa valor de 1 debido a que la simulación no funciona bien con otros valores
                debounce2 = 0;
                PORTD--;
                contador--;

            }
        }

        if (PORTBbits.RB0 == 1) { //si se presiona RB0 aumenta el puerto A
            debounce1++;
            if (debounce1 > 1) {
                debounce1 = 0;
                PORTD++;
                contador++;
            }
        }
    }
}

void main(void) {
    Setup();
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) {

    }

    return;
}

void Setup(void) { //configuracion 

    ANSEL = 0;
    ANSELH = 0;

    TRISD = 0;
    PORTA = 0;
    TRISB = 255;
    PORTB = 0;
    PORTD = 0;

    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;

    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.RBIF = 0;
}