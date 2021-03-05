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
int status;
float datos[7];
char *buffer;
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

    __delay_ms(1000);
    I2C_Master_Init(100000); // 100kHz
    UARTInit(9600, 1);
    GY_init();


    while (1) {

         GY_Read(datos);


    
        buffer = ftoa(datos[0], status);
        UARTSendString(buffer, 6); //solo 5 cifras se envian

        buffer = ftoa(datos[1], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[2], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[3], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[4], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);
        buffer = ftoa(datos[5], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        buffer = ftoa(datos[6], status);
        UARTSendString(" ", 10);
        UARTSendString(buffer, 6);

        UARTSendChar('\n');
        

//        PORTAbits.RA0 = ~PORTAbits.RA0; // Blink LED     
//        GY_Read(datos);
//
//        sprintf(buf, "Ax = %d    ", devolver[0]); // lo del porcentaje indica que se debe imprimir como decimal 
//        UARTSendString(buf);
//
//        sprintf(buf, " Ay = %d    ", devolver[1]);
//        UARTSendString(buf);
//
//        sprintf(buf, " Az = %d    ", devolver[2]);
//        UARTSendString(buf);
//
//        sprintf(buf, " T = %d  ", devolver[3]);
//        UARTSendString(buf);
//
//        sprintf(buf, " Gx = %d    ", devolver[4]);
//        UARTSendString(buf);
//
//        sprintf(buf, " Gy = %d    ", devolver[5]);
//        UARTSendString(buf);
//
//        sprintf(buf, " Gz = %d\r\n", devolver[6]);
//        UARTSendString(buf);
        
//        I2C_Start(0xD0);
//        I2C_Master_Write(0x6B);
//        I2C_Master_Stop();
//        I2C_Start(0xD1);
        
       
//        prueba = I2C_Read(0);
//        sprintf(buf, "prueba %d ", prueba);
//        UARTSendString(buf);
//        I2C_Master_Stop();
//        __delay_ms(50);




    }


    return;
}

void Setup(void) {

    TRISA = 0;
    PORTA = 0;
   // TRISC = 0;
    PORTC = 0;
    ANSEL = 0;
    ANSELH = 0;

    return;
}
