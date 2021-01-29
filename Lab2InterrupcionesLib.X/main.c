/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 25 de enero de 2021, 02:13 PM
 */


#include <xc.h>
#include <stdint.h>
#include "ADC.h"

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



#define pot PORTCbits.RA0
#define b1 PORTCbits.RA1
#define b2 PORTCbits.RA2

//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
volatile uint8_t varADC;
uint8_t varBoton1;
//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {

    if (ADIF == 1) {

        varADC = ADRESH;
        PORTD = varADC;
        ADIF = 0;
        ADCON0bits.GO = 1;

    }

    if (INTCONbits.RBIF == 1) {

        if (PORTBbits.RB0 == 1) {
            PORTA++;
        }


        if (PORTBbits.RB1 == 1) {
            PORTA--;
        }

        INTCONbits.RBIF = 0;

    }


}

void main(void) {

    Setup();
    configADC();
    canalADC(5);

    static uint8_t tabla[] = {0b01110111,
        0b01000001,
        0b00111011,
        0b01101011,
        0b01001101,
        0b01101110,
        0b01111110,
        0b01000011,
        0b01111111,
        0b01101111,
        0b01101111,
        0b01101111,
        0b01101111,
        0b01101111,
        0b01101111,
        0b01101111};


    //**********************************************************************************************************************************************
    // Loop principal
    //**********************************************************************************************************************************************

    while (1) {



    }

    return;
}

void Setup(void) { //configuracion 




    ANSEL = 0;
    ANSELH = 0;
    ANSELHbits.ANS12 = 1;

    TRISA = 0; //salida para los leds
    TRISB = 1; //entradas de los botones, solo para eso se usa el puerto
    TRISC = 0; // 7 segmentos
    TRISD = 0; // multiplexado
    TRISEbits.TRISE0 = 1; //entrada adc ansel 5

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    OPTION_REGbits.nRBPU = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1; //se habilita ISR para los botones

    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 0;



}
