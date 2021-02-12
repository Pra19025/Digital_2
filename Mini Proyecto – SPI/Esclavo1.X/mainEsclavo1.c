/*
 * File:   mainEsclavo1.c
 * Author: Noel Prado
 *
 * Created on 11 de febrero de 2021, 08:51 AM
 */


#include <xc.h>
#include <stdint.h>
#include "ADC.h"
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

#define _XTAL_FREQ 4000000
//**********************************************************************************************************************************************
// Variables 
//*************************************************************************************************************************************************
uint8_t varADC;


//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {

    if (ADIF == 1) {
        __delay_ms(1);
        varADC = ADRESH; //guardar valor de la lectura del adc en variable para comparacion y para 7 segmentos

        ADIF = 0;
        ADCON0bits.GO = 1;

    }
    
    if(SSPIF == 1){
        PORTD = spiRead();
        spiWrite(PORTB);
        SSPIF = 0;
        
    }


}

void main(void) {
    Setup();
    configADC();
    canalADC(0);
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while(1){
        
        PORTB = varADC;
    }
    
    return;
}


void Setup(void){
    
    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1;
    
    TRISA = 1;
    TRISB = 0;
    
    PORTB = 0;
    
    PORTA = 0;
    
    
    
}