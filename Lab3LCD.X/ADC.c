/*
 * File:   ADC.c
 * Author: Noel Prado
 *
 * Created on 26 de enero de 2021, 05:53 PM
 */


#include <xc.h>
#include "ADC.h"
#include "stdint.h"

void canalADC(uint8_t canal) {
    //segun el canal seleccionado se colocan los respectivos bits 
    if (canal == 0) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;

    }

    if (canal == 1) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;

    }


    if (canal == 2) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 0;

    }


    if (canal == 3) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 1;

    }


    if (canal == 4) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;

    }


    if (canal == 5) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;

    }


    if (canal == 6) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 0;

    }


    if (canal == 7) {
        ADCON0bits.CHS3 = 0;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 1;

    }


    if (canal == 8) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;

    }

    if (canal == 9) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;

    }

    if (canal == 10) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 0;

    }


    if (canal == 11) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 0;
        ADCON0bits.CHS1 = 1;
        ADCON0bits.CHS0 = 1;

    }


    if (canal == 12) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;

    }


    if (canal == 13) {
        ADCON0bits.CHS3 = 1;
        ADCON0bits.CHS2 = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;

    }
    //se inicia la conversion siempre despues de seleccionar un canal
    ADCON0bits.GO = 1;
    return;
}

void configADC(void) {

    ADCON0bits.ADCS0 = 1; //FOSC / 8
    ADCON0bits.ADCS1 = 0;

    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;

    ADCON1bits.ADFM = 0;
//se activan interrupciones y se configuran
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    //se prende ADC
    ADCON0bits.ADON = 1;
}
