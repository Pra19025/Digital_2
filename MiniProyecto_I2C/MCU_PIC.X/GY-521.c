/*
 * File:   GY-521.c
 * Author: Noel Prado
 *
 * Created on 25 de febrero de 2021, 05:21 PM
 */

//librería para el acélerometro

#include <xc.h>
#include "GY-521.h"
#include "I2C.h"
#include <stdint.h>
#include "UART.h"

void GY_init(void) {
    //la mera direccion es 0xD0
    //0xD1 para leer 
    //0xD0 para escribir

    // frecuencia de revision de datos (sample rate)
    I2C_Master_Start();
    I2C_Master_Write(0x19); //SMPLRT_DIV
    I2C_Master_Write(0x07);
    I2C_Master_Stop();

    // fuente del reloj
    I2C_Master_Start();
    I2C_Master_Write(0x6B); //PWR_MGMT
    I2C_Master_Write(0x01);
    I2C_Master_Stop();

    // Configuracion como tal
    I2C_Master_Start();
    I2C_Master_Write(0x1A); // direccion del CONFIG
    I2C_Master_Write(0x00);
    I2C_Master_Stop();

    // Configuracion del acelerómetro
    I2C_Master_Start();
    I2C_Master_Write(0x1C);
    I2C_Master_Write(0x00); //+-2g
    I2C_Master_Stop();

    // Configuración del  giroscopio 
    I2C_Master_Start();
    I2C_Master_Write(0x1B); //direccion de gyro_config
    I2C_Master_Write(0x18); // +-2000
    I2C_Master_Stop();


    return;
}

void GY_Read(void) {
    int Ax, Ay, Az, Gx, Gy, Gz, T;
    int Axenvio, Ayenvio, Azenvio, Gxenvio, Gyenvio, Gzenvio, Tenvio; 
    
    I2C_Master_Start();
    I2C_Master_Write(0x3C);
    I2C_Master_Stop();
    I2C_Master_Start(); //para leer
    
    I2C_Master_Write(0xD1);
    I2C_Master_Write(0x3B);
    Ax = (int) I2C_Master_Read(0) << 8;
    
    I2C_Master_Write(0x3C);
    Ax |= (int) I2C_Master_Read(0);
//    
//    Ay = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
//    Az = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
//    T = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
//    Gx = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
//    Gy = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
//    Gz = ((int) I2C_Master_Read(0) << 8) | (int) I2C_Master_Read(0);
    I2C_Master_Stop();
    
//    Axenvio = intToString(Ax);
//    Ayenvio = intToString(Ax);
//    Azenvio = intToString(Ax);
//    Gxenvio = intToString(Ax);
//    Gyenvio = intToString(Ax);
//    Gzenvio = intToString(Ax);
//    Tenvio = intToString(Ax);
//    
//    UARTSendString(Axenvio);
//    UARTSendString(Ayenvio);
//    UARTSendString(Azenvio);
//    UARTSendString(Gxenvio);
//    UARTSendString(Gyenvio);
//    UARTSendString(Gzenvio);
//    UARTSendString(Tenvio);
//        
//    
    return;

}

//char* intToString(uint8_t value) {
//    char valor[4];
//
//    uint8_t entero = value / 100; // solo se dejan las centenas
//    valor[0] = entero + 48;
//
//    value = value - (100 * entero); // se quitan las centenas
//
//    valor[1] = value / 10 + 48; // se dejan las decenas
//    valor[2] = value % 10 + 48; // quedan solo las unidades 
//    valor[3] = '\0'; // final
//
//    return valor;   //se regresa la cadena, es decir un string
//
//
//}
