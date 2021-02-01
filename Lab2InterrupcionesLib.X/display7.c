/*
 * File:   display7.c
 * Author: Noel Prado
 *
 * Created on 29 de enero de 2021, 10:19 AM
 */


#include <xc.h>
#include "display7.h"
#include <stdint.h>

uint8_t tabla7(uint8_t entrada) {

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
        0b01011111,
        0b01111100,
        0b00110110,
        0b01111001,
        0b00111110,
        0b00011110};



    return tabla[entrada];
}

void multiplexor(void) {
    OPTION_REG = 0x86;
    TMR0 = 61;
    INTCON = 0xA0;
}

uint8_t NibbleH(uint8_t ValorADC) {

    uint8_t NibbleH = (ValorADC & 0b00001111);
 

    return NibbleH;

}

uint8_t NibbleL(uint8_t ValorADC) {

    uint8_t aux = ValorADC ;
    aux = (aux >> 4);
    uint8_t NibbleL = (aux & 0b00001111);
    //hay que hacer un swapf
    

    return NibbleL;

}