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
    UARTInit(9600, 1); //se inicia comunicación UART
    //    la mera direccion es 0xD0
    //    0xD1 para leer 
    //    0xD0 para escribir
    I2C_Start(0XD0);
    I2C_Master_Write(0x6B); // PWR_MGMT
    I2C_Master_Write(0x01); //se escoge el reloj del giroscopio 8MHz  
    I2C_Master_Stop();

    //dato que se envia, pero no hace nada realmente
    //pero funciona
    I2C_Start(0XD0);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();

    //  Sample rate 1kHZ
    I2C_Start(0XD0);
    I2C_Master_Write(0x19);
    I2C_Master_Write(0x08);
    I2C_Master_Stop();

    //CONFIG
 I2C_Start(0XD0);
    I2C_Master_Write(0x1A);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();
    //Configuracion del giroscopio
 I2C_Start(0XD0);
    I2C_Master_Write(0x1B);
    I2C_Master_Write(0x00); //+- 250 
    I2C_Master_Stop();
    //configuracion del acelerómetro
     I2C_Start(0XD0);
    I2C_Master_Write(0x1C);
    I2C_Master_Write(0x00); //+-2g  
    I2C_Master_Stop();


    // PWR_MGMT2
    I2C_Start(0X68);
    I2C_Master_Write(0x6C);
    I2C_Master_Write(0x00); //encendido 
    I2C_Master_Stop();

    return;

}

void GY_read(void) {
    float final[7];
    char* impresion;
    char val[14]; // final temporales
    int almacenar1[7]; // para almacenar1 final leídos 
    I2C_Start(0xD0);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_Write(0x3B);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(0xD1);

    for (int i = 0; i < 13; i++) val[i] = I2C_Read(0);
    val[13] = I2C_Read(1);
    I2C_Master_Stop();

    almacenar1[0] = ((int) val[0] << 8) | ((int) val[1]);
    almacenar1[1] = ((int) val[2] << 8) | ((int) val[3]);
    almacenar1[2] = ((int) val[4] << 8) | ((int) val[5]);
    almacenar1[3] = ((int) val[6] << 8) | ((int) val[7]);
    almacenar1[4] = ((int) val[8] << 8) | ((int) val[9]);
    almacenar1[5] = ((int) val[10] << 8) | ((int) val[11]);
    almacenar1[6] = ((int) val[12] << 8) | ((int) val[13]);

    //los val por los que se multiplican fueron obtenidos de 
https://deepbluembedded.com/mpu6050-with-microchip-pic-accelerometer-gyroscope-interfacing-with-pic/
    //al multiplicar por estos val lo que era raw data se convierte en final interpretables. 
    final[0] = ((float) almacenar1[0]) * 0.0005982; //Ax
    final[1] = ((float) almacenar1[1]) * 0.0005982; //Ay
    final[2] = ((float) almacenar1[2]) * 0.0005982; // Az
    final[3] = ((float) almacenar1[3]) / 340 + 36.53;
    final[4] = ((float) almacenar1[4]) * 0.00763; //velocidad angular en x, y z 
    final[5] = ((float) almacenar1[5]) * 0.00763;
    final[6] = ((float) almacenar1[6]) * 0.00763;

    //ftoa permite convertir un número a texto, se usa para poder mandarlo por uart
    impresion = ftoa(final[0], 2); //se guarda en un char con cantidad indefinida de final el float 
    UARTSendString(impresion, 6); //se manda el valor de la aceleración en x por uart, el valor ya fue convertido a decimal por ftoa
    // en las siguientes lineas se hace lo mismo pero para las diferentes cosas que lee el sensor
    impresion = ftoa(final[1], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);

    impresion = ftoa(final[2], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);

    impresion = ftoa(final[3], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);

    impresion = ftoa(final[4], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);
    impresion = ftoa(final[5], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);

    impresion = ftoa(final[6], 2);
    UARTSendString(" ", 10);
    UARTSendString(impresion, 6);

    UARTSendChar('\n');

    return;
}
