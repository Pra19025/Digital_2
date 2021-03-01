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
uint8_t bandera = 0;
int Ax = 0;
//      Ay, Az, Gx, Gy, Gz, T;
int Axenvio, Ayenvio, Azenvio, Gxenvio, Gyenvio, Gzenvio, Tenvio;
//***********************************************************************************************************************************************
// Prototipos de funciones
//**********************************************************************************************************************************************
void Setup(void);
char *intToString(uint8_t value);
//**************************************************************
// Vector de interrupción
//**************************************************************

void __interrupt() ISR(void) {


}

void main(void) {
    Setup();

    //la mera direccion es 0xD0
    //0xD1 para leer 
    //0xD0 para escribir

    // frecuencia de revision de datos (sample rate)
    I2C_Start(0xD0);
    I2C_Master_Write(0x19); //SMPLRT_DIV
    I2C_Master_Write(0x07);
    I2C_Master_Stop();

    // fuente del reloj
    I2C_Start(0xD0);
    I2C_Master_Write(0x6B); //PWR_MGMT
    I2C_Master_Write(0x01);
    I2C_Master_Stop();

    // Configuracion como tal
    I2C_Start(0xD0);
    I2C_Master_Write(0x1A); // direccion del CONFIG
    I2C_Master_Write(0x00);
    I2C_Master_Stop();

    // Configuracion del acelerómetro
    I2C_Start(0xD0);
    I2C_Master_Write(0x1C);
    I2C_Master_Write(0x00); //+-2g
    I2C_Master_Stop();

    // Configuración del  giroscopio 
    I2C_Start(0xD0);
    I2C_Master_Write(0x1B); //direccion de gyro_config
    I2C_Master_Write(0x18); // +-2000
    I2C_Master_Stop();


    while (1) {

        PORTAbits.RA0 = ~PORTAbits.RA0; // Blink LED     
        //GY_Read();
        __delay_ms(50);

//
//
//        I2C_Start(0xD0);
//        I2C_Master_Write(0x3B); //es la direccion del ax out H
//        I2C_Master_Stop();
//        I2C_Start(0xD1); //para leer
//
//
//        Ax = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//
//        I2C_Master_Stop();
//
//        Axenvio = intToString(Ax);
//                Ayenvio = intToString(Ax);
//                Azenvio = intToString(Ax);
//                Gxenvio = intToString(Ax);
//                Gyenvio = intToString(Ax);
//                Gzenvio = intToString(Ax);
//                Tenvio = intToString(Ax);
//
//        UARTSendString(Axenvio);
       UARTSendString("hola");
//        //        UARTSendString(Ayenvio);
//        //        UARTSendString(Azenvio);
//        //        UARTSendString(Gxenvio);
//        //        UARTSendString(Gyenvio);
//        //        UARTSendString(Gzenvio);
//        //        UARTSendString(Tenvio);

    }


    return;
}

void Setup(void) {

    I2C_Master_Init(100000); // 100kHz
    UARTInit(9600, 1);
    TRISA = 0;
    PORTA = 0;
    ANSEL = 0;
    ANSELH = 0;



    //    GY_init();



    return;
}

char* intToString(uint8_t value) {
    char valor[4];

    uint8_t entero = value / 100; // solo se dejan las centenas
    valor[0] = entero + 48;

    value = value - (100 * entero); // se quitan las centenas

    valor[1] = value / 10 + 48; // se dejan las decenas
    valor[2] = value % 10 + 48; // quedan solo las unidades 
    valor[3] = '\0'; // final

    return valor; //se regresa la cadena, es decir un string


}
