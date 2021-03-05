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
    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6B); // power managment 1 
    I2C_Master_Write(0x01); //giroscopio en x referencia  
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x00); //  Sample rate
    I2C_Master_Stop();


    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x19); //  Sample rate
    I2C_Master_Write(0x08); //1 khz de muestreo
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1A); //CONFIG
    I2C_Master_Write(0x00); //externo deshabilitado, y frecuencia int 8khz 
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1B); //gyro conf
    I2C_Master_Write(0x00); //+- 250 grados/s self test of
    I2C_Master_Stop();

    I2C_Master_Start();
    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x1C); // accel conf 
    I2C_Master_Write(0x00); //+-2g y self test of 
    I2C_Master_Stop();



    I2C_Master_Start();
    I2C_Master_Write(0x68); //direccion del mpu6050 para escritura,
    I2C_Master_Write(0x6C); // power managment 2 
    I2C_Master_Write(0x00); //se enciende  
    I2C_Master_Stop();

    
    
//  // fuente del reloj
//    I2C_Start(0xD0);
//    I2C_Master_Write(0x6B); //PWR_MGMT  
//    I2C_Master_Write(0x01); //se escoge el reloj del giroscopio 8MHz
//    I2C_Master_Stop();
//    
//    I2C_Master_Start();
//    I2C_Master_Write(0xD0); //direccion del mpu6050 para escritura,
//    I2C_Master_Write(0x00); //  Sample rate
//    I2C_Master_Stop();
//    
//    //     frecuencia de revision de datos (sample rate)
//    I2C_Start(0xD0);
//    I2C_Master_Write(0x19); //SMPLRT_DIV
//    I2C_Master_Write(0x07);
//    I2C_Master_Stop();
//
//  
//
//    // Configuracion del  DLPF
//    I2C_Start(0xD0);
//    I2C_Master_Write(0x1A); //config
//    I2C_Master_Write(0x00);
//    I2C_Master_Stop();
//
//    // Configuracion del acelerómetro
//    I2C_Start(0xD0);
//    I2C_Master_Write(0x1C);
//    I2C_Master_Write(0x00); //+-2g
//    I2C_Master_Stop();
//    // Configuración del  giroscopio 
//    I2C_Start(0xD0);
//    I2C_Master_Write(0x1B); //direccion de gyro_config
//    I2C_Master_Write(0x00); // +-250
//    I2C_Master_Stop();
//
////    I2C_Start(0xD0);
////    I2C_Master_Write(0x38);
////    I2C_Master_Write(0x01);
////    I2C_Master_Stop();




    return;
}

void GY_Read(float* datos) {

//
//    int Ax, Ay, Az, Gx, Gy, Gz, T;
//
//    char valores[14];
//
//
//    I2C_Start(0xD0);
//    while (SSPCON2bits.ACKSTAT);
//    I2C_Master_Write(0x3B); //es la direccion del ax out H
//    //I2C_Master_Stop();
//    while (SSPCON2bits.ACKSTAT);
//    I2C_Master_RepeatedStart();
//   // I2C_Start(0xD1); //para leer
//    I2C_Master_Write(0xD1);
//    //        Ax = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        Ay = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        Az = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        T = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        Gx = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        Gy = ((int) I2C_Read(0) << 8) | (int) I2C_Read(0);
//    //        Gz = ((int) I2C_Read(0) << 8) | (int) I2C_Read(1);
//
//    for (int i = 0; i < 13; i++) valores[i] = I2C_Read(0);
//    valores[13] = I2C_Read(1);
//    I2C_Master_Stop();
//
//    devolver[0] = ((int) valores[0] << 8) | ((int) valores[1]);
//    devolver[1] = ((int) valores[2] << 8) | ((int) valores[3]);
//    devolver[2] = ((int) valores[4] << 8) | ((int) valores[5]);
//    devolver[3] = ((int) valores[6] << 8) | ((int) valores[7]);
//    devolver[4] = ((int) valores[8] << 8) | ((int) valores[9]);
//    devolver[5] = ((int) valores[10] << 8) | ((int) valores[11]);
//    devolver[6] = ((int) valores[12] << 8) | ((int) valores[13]);
//
//__delay_ms(50);

 char valores[14];//valores temporales
    int guardar[7]; // arreglo donde se van a guardar los datos 
    I2C_Start(0xD0);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_Write(0x3B);
    while (SSPCON2bits.ACKSTAT);
    I2C_Master_RepeatedStart();
    I2C_Master_Write(0xD1);
    for (int i = 0; i < 13; i++) valores[i] = I2C_Read(0);
    valores[13] = I2C_Read(1);
    I2C_Master_Stop();
    //        //-------------------------
    //        
    guardar[0] = ((int) valores[0] << 8) | ((int) valores[1]);
    guardar[1] = ((int) valores[2] << 8) | ((int) valores[3]);
    guardar[2] = ((int) valores[4] << 8) | ((int) valores[5]);
    guardar[3] = ((int) valores[6] << 8) | ((int) valores[7]);
    guardar[4] = ((int) valores[8] << 8) | ((int) valores[9]);
    guardar[5] = ((int) valores[10] << 8) | ((int) valores[11]);
    guardar[6] = ((int) valores[12] << 8) | ((int) valores[13]);
    
    datos[0] = ((float) guardar[0]) * 0.0005982; //aceleracion en m/s^2
    datos[1] = ((float) guardar[1]) * 0.0005982; //aceleracion en m/s^2
    datos[2] = ((float) guardar[2]) * 0.0005982; //aceleracion en m/s^2
    datos[3] = ((float) guardar[3])/340 + 36.53;
    datos[4] = ((float) guardar[4]) * 0.00763; //grados/s
    datos[5] = ((float) guardar[5]) * 0.00763; //grados/s
    datos[6] = ((float) guardar[6]) * 0.00763; //grados/s
    

    return;

}

