/*
 * File:   GY-521.c
 * Author: Noel Prado
 *
 * Created on 25 de febrero de 2021, 06:27 PM
 */


#include "GY-521.h"


void GY_init() {
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
//configuracion del acelerómetro
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

void GY_read(float* datos) {
    char valores[14];// datos temporales
    int guardar[7]; // para guardar datos leídos 
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
