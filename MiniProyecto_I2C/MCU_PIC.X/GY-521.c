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
#include <stdio.h>

void GY_init(void) {
    //    la mera direccion es 0xD0
    //    0xD1 para leer 
    //    0xD0 para escribir
    //
    //     frecuencia de revision de datos (sample rate)
    // fuente del reloj
    I2C_Start(0xD0);
    I2C_Master_Write(0x6B); //PWR_MGMT  
    I2C_Master_Write(0x01); //se escoge el reloj del giroscopio 8MHz
    I2C_Master_Stop();

    I2C_Start(0xD0);
    I2C_Master_Write(0x19); //SMPLRT_DIV
    I2C_Master_Write(0x08);
    I2C_Master_Stop();

    // digital low pass filterx
    I2C_Start(0xD0);
    I2C_Master_Write(0x1A); // direccion del CONFIG
    I2C_Master_Write(0x00); //no es necesario sincronizar
    I2C_Master_Stop();

    // Configuración del  giroscopio 
    I2C_Start(0xD0);
    I2C_Master_Write(0x1B); //direccion de gyro_config
    I2C_Master_Write(0x18); // +-2000
    I2C_Master_Stop();

    // Configuracion del acelerómetro
    I2C_Start(0xD0);
    I2C_Master_Write(0x1C);
    I2C_Master_Write(0x00); //+-2g
    I2C_Master_Stop();

    //deshabilitar interrupciones 
    I2C_Start(0xD0);
    I2C_Master_Write(0x38);
    I2C_Master_Write(0x00);
    I2C_Master_Stop();

    return;
}

void GY_Read(void) {


    int Ax, Ay, Az, Gx, Gy, Gz, T;
    char buf[50];
    char valores[14];

    I2C_Start(0xD0);
    I2C_Master_Write(0x3B); //es la direccion del ax out H
    //I2C_Master_Stop();
    I2C_Master_RepeatedStart();
    // I2C_Start(0xD1); //para leer
    I2C_Master_Write(0xD1);
    //        Ax = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        Ay = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        Az = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        T = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        Gx = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        Gy = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
    //        Gz = ((int) I2C_Read(0) << 8) | (int) I2C_Read(1);

    for (int i = 0; i < 13; i++) valores[i] = I2C_Read(0);
    valores[13] = I2C_Read(1);
    I2C_Master_Stop();

    Ax = ((int) valores[0] << 8) | ((int) valores[1]);
    Ay = ((int) valores[2] << 8) | ((int) valores[3]);
    Az = ((int) valores[4] << 8) | ((int) valores[5]);
    T = ((int) valores[6] << 8) | ((int) valores[7]);
    Gx = ((int) valores[8] << 8) | ((int) valores[9]);
    Gy = ((int) valores[10] << 8) | ((int) valores[11]);
    Gz = ((int) valores[12] << 8) | ((int) valores[13]);



    sprintf(buf, "Ax = %d    ", Ax); // lo del porcentaje indica que se debe imprimir como decimal 
    UARTSendString(buf);

    sprintf(buf, " Ay = %d    ", Ay);
    UARTSendString(buf);

    sprintf(buf, " Az = %d    ", Az);
    UARTSendString(buf);

    sprintf(buf, " T = %d  ", T);
    UARTSendString(buf);

    sprintf(buf, " Gx = %d    ", Gx);
    UARTSendString(buf);

    sprintf(buf, " Gy = %d    ", Gy);
    UARTSendString(buf);

    sprintf(buf, " Gz = %d\r\n", Gz);
    UARTSendString(buf);


    return;

}

