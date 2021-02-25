
#include <xc.h>
#include "I2C.h"
#include "MPU6050.h"

#include "UART.h"  // for debugging serial terminal
#include <stdio.h>

//-------------[ MPU6050 Routines ]------------------
//---------------------------------------------------

void MPU6050_Init()
{
  // Power-Up Delay & I2C_Init
  __delay_ms(100);
  I2C_Master_Init(100000);
 
  // Setting The Sample (Data) Rate
  I2C_Start(0xD0);
  I2C_Master_Write(SMPLRT_DIV);
  I2C_Master_Write(0x07);
  I2C_Master_Stop();
 
  // Setting The Clock Source
  I2C_Start(0xD0);
  I2C_Master_Write(PWR_MGMT_1);
  I2C_Master_Write(0x01);
  I2C_Master_Stop();
 
  // Configure The DLPF
  I2C_Start(0xD0);
  I2C_Master_Write(CONFIG);
  I2C_Master_Write(0x00);
  I2C_Master_Stop();
 
  // Configure The ACCEL (FSR= +-2g)
  I2C_Start(0xD0);
  I2C_Master_Write(ACCEL_CONFIG);
  I2C_Master_Write(0x00);
  I2C_Master_Stop();
 
  // Configure The GYRO (FSR= +-2000d/s)
  I2C_Start(0xD0);
  I2C_Master_Write(GYRO_CONFIG);
  I2C_Master_Write(0x18);
  I2C_Master_Stop();
 
  // Enable Data Ready Interrupts
  I2C_Start(0xD0);
  I2C_Master_Write(INT_ENABLE);
  I2C_Master_Write(0x01);
  I2C_Master_Stop();
}

void MPU6050_Read()
{
  char buffer[40];
  int Ax,Ay,Az,T,Gx,Gy,Gz;
  // Prepare For Reading, Starting From ACCEL_XOUT_H
  I2C_Start(0xD0);
  I2C_Master_Write(ACCEL_XOUT_H);
  I2C_Master_Stop();
  I2C_Start(0xD1);
  Ax = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  Ay = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  Az = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  T  = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  Gx = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  Gy = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(0);
  Gz = ((int)I2C_Master_Read(0)<<8) | (int)I2C_Master_Read(1);
  I2C_Master_Stop();
 
  sprintf(buffer,"Ax = %d    ",Ax);
  UARTSendString(buffer);
 
  sprintf(buffer," Ay = %d    ",Ay);
  UARTSendString(buffer);
 
  sprintf(buffer," Az = %d    ",Az);
  UARTSendString(buffer);
 
  sprintf(buffer," T = %d  ",T);
  UARTSendString(buffer);
 
  sprintf(buffer," Gx = %d    ",Gx);
  UARTSendString(buffer);
 
  sprintf(buffer," Gy = %d    ",Gy);
  UARTSendString(buffer);
 
  sprintf(buffer," Gz = %d\r\n",Gz);
  UARTSendString(buffer);
}