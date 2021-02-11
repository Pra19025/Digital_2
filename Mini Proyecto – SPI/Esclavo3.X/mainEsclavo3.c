/*
 * File:   mainEsclavo3.c
 * Author: Noel Prado
 *
 * Created on 11 de febrero de 2021, 09:55 AM
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

//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
volatile uint8_t varADC;

//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {
    if (ADIF == 1) {

        varADC = ADRESH; //guardar valor de la lectura del adc en variable para comparacion y para 7 segmentos

        ADIF = 0;
        ADCON0bits.GO = 1;

    }

}

void main(void) {
    Setup();
    configADC();
    canalADC(0);

    while (1) {
        //el rango del LM35 es de -55 a 150 por lo que hay 205 posible valores 
        //realmente varADC vale 0 en el 0 grados. 
        //Cada 2 grados equivalen a 1 bit. 
        // con los 150 grados varADC vale 77
        PORTC = varADC;
        if (varADC <= 12) {
            PORTB = 0;
            PORTBbits.RB2 = 1;

        }

        if ((varADC <= 18) & (varADC >= 13)) {
            PORTB = 0;
            PORTBbits.RB1 = 1;
        }

        if (varADC >= 19) {
            PORTB = 0;
            PORTBbits.RB0 = 1;
        }
    }
    return;
}

void Setup(void) {

    ANSEL = 0;
    ANSELH = 0;

    ANSELbits.ANS0 = 1;

    TRISA = 1;
    TRISB = 0;
    TRISC = 0;

    PORTA = 0;
    PORTB = 0;


}
