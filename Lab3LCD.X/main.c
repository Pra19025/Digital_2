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


//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************

uint8_t varADC1 = 0;
uint8_t varADC2 = 0;
uint8_t bandera = 0;
float convertir = 0.00;
uint8_t *resultado;
char buf[20];
int status;

//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {

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

}

void main(void) {
    Setup();
   
    Lcd_Init();
    Lcd_Clear();
    
    configADC();
    canalADC(0);

    
    while (1) {


        //__delay_ms(2);
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("S1");
        Lcd_Set_Cursor(1, 8);
        Lcd_Write_String("S2");
        Lcd_Set_Cursor(1, 15);
        Lcd_Write_String("S3");
        
        convertir = (varADC1/255)*5;
       //ftoa(convertir,2,buf);
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(buf);
        
        Lcd_Set_Cursor(2,8);
        Lcd_Write_String(varADC2);
        
  


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

    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1;
    ANSELbits.ANS1 = 1;


}