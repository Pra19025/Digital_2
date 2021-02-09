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
#define _XTAL_FREQ 4000000

//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
char buf[10];
char buf2[10];
char buf3[10];
uint8_t varADC1 = 0;
uint8_t varADC2 = 0;
uint8_t bandera = 0;
float convertir;
float convertir2;
char lectura;
uint8_t control;
uint8_t varUART = 0;
uint8_t UARTstring;


//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup(void);
char intToString(uint8_t value);
char decimalASCII(uint8_t lectura);

//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {



}

void main(void) {
    Setup();
    UARTInit(9600, 1);
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


            ADIF = 0;
            ADCON0bits.GO = 1;

        }


        convertir = 0;
        convertir2 = 0;

        convertir = (varADC1 / (float) 255)*5;
        
        Lcd_Set_Cursor(2, 1);
        Lcd_Write_String(buf);
        
        UARTSendString(buf, 3);
        
        convertir2 = (varADC2 / (float) 255)*5;
        convert(buf2, convertir2, 2);
        Lcd_Set_Cursor(2, 8);
        Lcd_Write_String(buf2);
        UARTSendString(buf2, 6);

        Lcd_Set_Cursor(2, 15);
        Lcd_Write_String(UARTstring);
        __delay_ms(20);


        // UARTSendString(buf, 6);


        if (UARTDataReady()) {
            char entrada = UARTReadChar();
            if (entrada == '+') {
                varUART++;
            } else if (entrada == '-') {
                if (varUART == 0) {
                    varUART = 0;
                } else {
                    varUART--;
                }
            }


            Lcd_Set_Cursor(2, 15);
            UARTstring = intToString(varUART);


        }



    }

    return;
}

void Setup(void) {

    TRISA = 255;
    TRISD = 0;
    TRISC = 0;
    TRISB = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;


    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTB = 0;

    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1;
    ANSELbits.ANS1 = 1;


}

char decimalASCII(uint8_t lectura){
    float convertir = (lectura/255)*5;    //debido a que se leen 8 bits, 255 es el máximo
    char cadena[5];
    uint8_t entero = convertir;
    
    cadena[0] = entero + 48; //debido a que el 48 es la posición del 0 en ascii
    cadena[1] = '.';
    
    convertir = (convertir - entero); //debido a que convertir es float, y entero es entero, solo van a quedar los decimales después de esta operación en valor
    convertir = convertir*10;
    entero = convertir;
    cadena[2] = entero + 48;
    
    convertir -= entero;
    convertir = convertir *10;
    
    entero = convertir;
    cadena[3] = entero + 48;
    cadena[4] = '\0';
    return cadena;
}

char* intToString(uint8_t value) {
    char valor[4];

    uint8_t entero = value / 100; // numero de centenas 
    valor[0] = entero + 48;

    value = value-(100 * entero); // se quitan las decenas

    valor[1] = value / 10 + 48; // decenas
    valor[2] = value % 10 + 48; // el resto
    valor[3] = '\0'; //caracter nulo

    return valor;


}
