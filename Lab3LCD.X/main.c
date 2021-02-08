/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 4 de febrero de 2021, 09:29 AM
 */


#include <xc.h>
#include <stdint.h>
#include "LCD8bits.h"
#include "ADC.h"
#include "UART.h"


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
#define _XTAL_FREQ 8000000

//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
char buf[10];
char buf2[10];
uint8_t varADC1 = 0;
uint8_t varADC2 = 0;
uint8_t bandera = 0;
float convertir;
float convertir2;
char lectura;
uint8_t control;


//**********************************************************************************************************************************************
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
    UARTInit(9600, 0);
    Lcd_Init();
    Lcd_Clear();

    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("S1");
    Lcd_Set_Cursor(1, 8);
    Lcd_Write_String("S2");
    Lcd_Set_Cursor(1, 15);
    Lcd_Write_String("S3");

    configADC();
    canalADC(0);


    while (1) {

        if (ADIF == 1) {


            if (bandera == 0) {
                varADC1 = ADRESH;
                canalADC(1);
                bandera++;
            } else {
                varADC2 = ADRESH;
                canalADC(0);
                bandera = 0;
            }
            PORTB = varADC1;

            ADIF = 0;
            ADCON0bits.GO = 1;

        }


        convertir = 0;
        convertir2 = 0;

        convertir = (varADC1 / (float) 255)*5;
        convert(buf, convertir, 2);

        convertir2 = (varADC2 / (float) 255)*5;
        convert(buf2, convertir2, 2);

        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(buf);

        Lcd_Set_Cursor(2, 8);
        Lcd_Write_String(buf2);
        __delay_ms(20);


        //        lectura = UARTReadChar();
        //        if (lectura == 0x2b) {
        //            control++;
        //        }
        //        if (lectura == 0x2d) {
        //            control--;
        //        }




    }

    return;
}

void Setup(void) {

    TRISA = 255;
    TRISD = 0;
    TRISC = 0;
    TRISB = 0;


    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTB = 0;

    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1;
    ANSELbits.ANS1 = 1;


}