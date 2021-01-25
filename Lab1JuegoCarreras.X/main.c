/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 20 de enero de 2021, 11:06 AM
 */


#include <xc.h>

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
int bandera;    //para verificar que el boton de inicio de carrera ha sido presionado
int j1; //contadores para cuantas veces han apachado los jugadores los botones
int j2;
#define LEDR PORTCbits.RC5
#define LEDA PORTCbits.RC6
#define LEDV PORTCbits.RC7
#define b0 PORTCbits.RC0
#define b1 PORTCbits.RC1
#define b2 PORTCbits.RC2


#define _XTAL_FREQ 4000000

//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);
void semaforo(void);


//**********************************************************************************************************************************************
// Ciclo principal
//**********************************************************************************************************************************************

void main(void) {
    Setup();
    bandera = 0;

    //**********************************************************************************************************************************************
    // Loop principal
    //**********************************************************************************************************************************************

    while (1) {

        if (b0 == 1) {
            __delay_ms(15); // antirebote para el botón, se implementa de igual manera para los otros 2
            if (b0 == 0) {
                PORTCbits.RC3 = 0;  //se colocan en 0 los leds que indican el ganador
                PORTCbits.RC4 = 0;
                j1 = 0;                         //se colocan en 0 los contadores cada vez que se presiona el inicio de carrera
                j2 = 0;
                semaforo();

                bandera = 1;    //se prende la bandera despues de ejecutar la secuencia del semaforo
            }
        }

        if (bandera == 1) { //si la bandera esta prendida se pueden presionar los botones

            if (b1 == 1) {
                __delay_ms(15); 
                if (b1 == 0) {
                    j1++;   //cada vez que el jugador presiona en botón se incrementa esta variable. 
                    if (PORTA == 0) {
                        PORTA++;
                    } else {
                        PORTA = (PORTA << 1); //se utiliza el rotate to right para hacer el contador de decadas
                    }
                }
            }

            if (j1 == 8) { //si el jugador llega a 8, ha ganado, se prende el led que lo indica
                PORTCbits.RC3 = 1;
            }

            if (b2 == 1) { //funciona de igual manera que el otro boton
                __delay_ms(15);
                if (b2 == 0) {
                    j2++;
                    if (PORTB == 0) {
                        PORTB++;

                    } else {
                        PORTB = (PORTB << 1);
                    }
                }
            }


            if (j2 == 8) {
                PORTCbits.RC4 = 1;
            }

            if (j1 == 8 | j2 == 8) {    //si alguno de los jugadores llega a 8, se prende la bandera, y se limpian los puertos

                bandera = 0;
                PORTA = 0;
                PORTB = 0;
            }



        }
    }
    return;
}
//**********************************************************************************************************************************************
// Funciones
//**********************************************************************************************************************************************

void Setup(void) { //configuracion 
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;

    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 0;

    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISA = 0;
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;

    TRISB = 0;

}

void semaforo(void) { 

    //rutina que simula el semaforo
    LEDR = 1;
    __delay_ms(250);// se prenden los leds del semaforo con un delay entre si
    LEDR = 0;//el delay se hace mas corto que lo que deberia ser debido a que proteus tarda mas en procesarlo
    LEDA = 1;
    __delay_ms(250);
    LEDA = 0;
    LEDV = 1;
    __delay_ms(250);
    LEDV = 0;

}
