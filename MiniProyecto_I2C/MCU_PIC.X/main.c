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
char* buf;
int entero;
float datos[7];
char entrada;
//***********************************************************************************************************************************************
// Prototipos de funciones
//**********************************************************************************************************************************************
void Setup(void);

//**************************************************************
// Vector de interrupci�n
//**************************************************************

void __interrupt() ISR(void) {
//se utiliza la interrupci�n para las luces piloto, seg�n la entrada se prende o apagan leds 
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
    Setup();    //se colocan condiciones iniciales
    I2C_Master_Init();  //se inicia el i2c
    UARTInit(9600, 1);//se inicia comunicaci�n UART
    GY_init();  //se mandan las direcciones para comunicarse y configurar el sensor



    while (1) {
        GY_read(datos); //esta funci�n permite leer los datos qeu el sensor i2c manda

        //ftoa permite convertir un n�mero a texto, se usa para poder mandarlo por uart
        buf = ftoa(datos[0], entero);   //se guarda en un char con cantidad indefinida de datos el float 
        UARTSendString(buf, 6); //se manda el valor de la aceleraci�n en x por uart, el valor ya fue convertido a decimal por ftoa
        // en las siguientes lineas se hace lo mismo pero para las diferentes cosas que lee el sensor
        buf = ftoa(datos[1], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);

        buf = ftoa(datos[2], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);

        buf = ftoa(datos[3], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);

        buf = ftoa(datos[4], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);
        buf = ftoa(datos[5], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);

        buf = ftoa(datos[6], entero);
        UARTSendString(" ", 10);
        UARTSendString(buf, 6);

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
    PIE1bits.RCIE = 1; // se activa la de recibir 
    //se usan interrupciones para las luces piloto
    return;

}

