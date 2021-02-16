/*
 * File:   mainMaestro.c
 * Author: Noel Prado
 *
 * Created on 11 de febrero de 2021, 10:18 AM
 */


#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "UART.h"
#include "LCD.h"

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

#define _XTAL_FREQ 40000000
//**********************************************************************************************************************************************
// Variables 
//***********************************************************************************************************************************************

uint8_t valorADC;
uint8_t ADCenvio;

    
//***********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);
char *decimalASCII(uint8_t lectura);
//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {


}

void main(void) {
    Setup();

    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
        __delay_ms(5);
    //UARTInit(9600, 1); //se van a usar 9600 baudios
//    Lcd_Init();
//    Lcd_Clear();
//    __delay_ms(5);
//    Lcd_Set_Cursor(1, 1);
//    Lcd_Write_String("S1");
//    Lcd_Set_Cursor(1, 8);
//    Lcd_Write_String("S2");
//    Lcd_Set_Cursor(1, 15);
//    Lcd_Write_String("S3");


    while (1) {
        // Primer PIC (ADC)
        PORTAbits.RA0 = 0; //selección del esclavo

        spiWrite(PORTB);    
        PORTD = spiRead();
        //valorADC = spiRead();   //se lee lo que envia el esclavo, que en este caso es el pic que tiene el ADC
       __delay_ms(15);
//        ADCenvio = decimalASCII(valorADC);  //la señal que se va aenviar a la LCD, se convierte a ASCII
//        Lcd_Set_Cursor(2, 1);   //se coloca el cursor en posicion
//        Lcd_Write_String(ADCenvio); // Se escribe en la LCD la variable del ADC
        //UARTSendString(ADCenvio, 6);
      
        PORTAbits.RA0 = 1; //deselecciono el esclavo



//        __delay_ms(10);
//        //Segundo PIC (contador)
//        PORTAbits.RA1 = 0;
//
//        PORTAbits.RA1 = 1;
//
//
//        //Tercer PIC (Sensor de temperatura)
//        PORTAbits.RA2 = 0;
//
//        PORTAbits.RA2 = 1;





    }


    return;
}

void Setup(void) {
    TRISA = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0;
    TRISB = 0;
    TRISD = 0;
    PORTC = 0;
    PORTB = 0;
    PORTD = 0;
     
    PORTA = 255;
    //configuracion para la comunicacion serial sincrona
}


char* decimalASCII(uint8_t lectura) {
    float convertir3 = (lectura / (float) 51); //debido a que se leen 8 bits, 255 es el máximo
    char cadena[5];
    uint8_t entero = convertir3;

    cadena[0] = entero + 48; //48 es la posicion 0 en ascii
    cadena[1] = '.';

    convertir3 = (convertir3 - entero); //debido a que convertir es float, y entero es entero, solo van a quedar los decimales después de esta operación en valor
    convertir3 *= 10;
    entero = convertir3;
    cadena[2] = entero + 48;

    convertir3 -= entero;
    convertir3 *= 10;

    entero = convertir3;
    cadena[3] = entero + 48;
    cadena[4] = '\0';
    return cadena;
}

