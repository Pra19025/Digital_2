/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 25 de enero de 2021, 02:13 PM
 */


#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "display7.h"

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
uint8_t debounce1;
uint8_t debounce2;
uint8_t Nibble1;
uint8_t Nibble2;
uint8_t var1 = 0;

//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {

    if (ADIF == 1) {    

        varADC = ADRESH;    //guardar valor de la lectura del adc en variable para comparacion y para 7 segmentos

        ADIF = 0;
        ADCON0bits.GO = 1;

    }

    if (INTCONbits.RBIF == 1) {

        INTCONbits.RBIF = 0;

        if (PORTBbits.RB1 == 1) {   //si se presionar RB1 se disminuye el valor del puerto A
            debounce2++;
            if (debounce2 > 1) {    //algoritmo del antirrebote, se usa valor de 1 debido a que la simulación no funciona bien con otros valores
                debounce2 = 0;
                PORTA--;


                var1--;

            }
        }

        if (PORTBbits.RB0 == 1) {  //si se presiona RB0 aumenta el puerto A
            debounce1++;
            if (debounce1 > 1) {
                debounce1 = 0;
                PORTA++;
                var1++; //variable de control para comparacion con el valor del ADC y poder prender alarma
            }
        }



    }

    if (INTCONbits.TMR0IF == 1) {
        INTCONbits.TMR0IF = 0;
        TMR0 = 61;  //TMR=  configurado para 25ms 
        PORTC = 0;
        Nibble1 = NibbleL(varADC);  //se usan funciones de la libreria del display7
        Nibble2 = NibbleH(varADC);

        if (PORTD == 2) {   //para la multiplexación se varía el valor del puerto D entre 0 y 2 mediante rotación. 
            PORTD = 0;


        }
        if (PORTD == 0) {
            PORTD++;

            PORTC = tabla7(Nibble2);


        } else {
            PORTD = (PORTD << 1);

            PORTC = tabla7(Nibble1);

        }


    }



}

void main(void) {
    //se configura todo a través de sus fuciones
    Setup();
    multiplexor();
    configADC();
    canalADC(5);




    //**********************************************************************************************************************************************
    // Loop principal
    //**********************************************************************************************************************************************

    while (1) {

        if (var1 == varADC) {   //comparacion para la alarma
            PORTEbits.RE1 = 1;

        } else {
            PORTEbits.RE1 = 0;
        }






    }

    return;
}

void Setup(void) { //configuracion 

    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS5 = 1;

    TRISA = 0; //salida para los leds
    TRISB = 255; //entradas de los botones, solo para eso se usa el puerto
    TRISC = 0; // 7 segmentos
    TRISD = 0; // multiplexado
    TRISEbits.TRISE0 = 1; //entrada adc ansel 5
    TRISEbits.TRISE1 = 0;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1; //se habilita ISR para los botones

    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.RBIF = 0;


}
