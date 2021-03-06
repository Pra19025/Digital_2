/*
 * File:   GY-521.c
 * Author: Noel Prado
 *
 * Created on 25 de febrero de 2021, 06:27 PM
 */

#include "I2C.h"
#include "UART.h"
#include "GY-521.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void GY_init() {

    I2C_Master_Init(); //se inicia el i2c
    UARTInit(9600, 1); //se inicia comunicaci�n UART
    //    la mera direccion es 0xD0
    //    0xD1 para leer 
    //    0xD0 para escribir
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x6B); // PWR_MGMT
    I2C_Master_Write(0x01); //se escoge el reloj del giroscopio 8MHz  
    I2C_Master_Stop();

    //dato que se envia, pero no hace nada realmente
    //pero funciona
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();

    //  Sample rate 1kHZ
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x19);
    I2C_Master_Write(0x08);
    I2C_Master_Stop();

    //CONFIG
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x1A);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();
    //Configuracion del giroscopio
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x1B);
    I2C_Master_Write(0x00); //+- 250 
    I2C_Master_Stop();
    //configuracion del aceler�metro
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x1C);
    I2C_Master_Write(0x00); //+-2g  
    I2C_Master_Stop();


    // PWR_MGMT2
    I2C_Master_Start();
    I2C_Master_Write(0x68);
    I2C_Master_Write(0x6C);
    I2C_Master_Write(0x00); //encendido 
    I2C_Master_Stop();

    return;

}

void GY_read(void) {
    float datos[7];
    char* buf;
    int entero = 2; //para tener solo dos decimales
    char valores[14]; // datos temporales
    int guardar[7]; // para guardar datos le�dos 
    I2C_Start(0xD0);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_Write(0x3B);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(0xD1);

    for (int i = 0; i < 13; i++) valores[i] = I2C_Read(0);
    valores[13] = I2C_Read(1);
    I2C_Master_Stop();

    guardar[0] = ((int) valores[0] << 8) | ((int) valores[1]);
    guardar[1] = ((int) valores[2] << 8) | ((int) valores[3]);
    guardar[2] = ((int) valores[4] << 8) | ((int) valores[5]);
    guardar[3] = ((int) valores[6] << 8) | ((int) valores[7]);
    guardar[4] = ((int) valores[8] << 8) | ((int) valores[9]);
    guardar[5] = ((int) valores[10] << 8) | ((int) valores[11]);
    guardar[6] = ((int) valores[12] << 8) | ((int) valores[13]);

    //los valores por los que se multiplican fueron obtenidos de 
https://deepbluembedded.com/mpu6050-with-microchip-pic-accelerometer-gyroscope-interfacing-with-pic/
    //al multiplicar por estos valores lo que era raw data se convierte en datos interpretables. 
    datos[0] = ((float) guardar[0]) * 0.0005982; //Ax
    datos[1] = ((float) guardar[1]) * 0.0005982; //Ay
    datos[2] = ((float) guardar[2]) * 0.0005982; // Az
    datos[3] = ((float) guardar[3]) / 340 + 36.53;
    datos[4] = ((float) guardar[4]) * 0.00763; //velocidad angular en x, y z 
    datos[5] = ((float) guardar[5]) * 0.00763;
    datos[6] = ((float) guardar[6]) * 0.00763;

    //ftoa permite convertir un n�mero a texto, se usa para poder mandarlo por uart
    buf = ftoa(datos[0], entero); //se guarda en un char con cantidad indefinida de datos el float 
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

    return;
}
