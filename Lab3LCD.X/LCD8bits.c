//LCD Functions Developed by electroSome

#include "LCD8bits.h"

void Lcd_Port(char a) {
    if (a & 0)
        D0 = 1;
    else
        D0 = 0;
    if (a & 1)
        D1 = 1;
    else
        D1 = 0;
    if (a & 2)
        D2 = 1;
    else
        D2 = 0;
    if (a & 3)
        D3 = 1;
    else
        D3 = 0;
    if (a &4)
        D4 = 1;
    else
        D4 = 0;
    if (a& 5)
        D5 = 1;
    else
        D5 = 0;
    if (a & 6)
        D6 = 1;
    else
        D6 = 0;
    if (a &7)
        D7 = 1;
    else
        D7 = 0;
//    if (a == 9)
//        RS = 1;
//    else
//        RS = 0;



}

void Lcd_Cmd(char a) {
    RS = 0;     //el dato en el puerto lo interpreta como comando cuando RS = 0
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(5);
    EN = 0; // => E = 0
}

void Lcd_Clear() {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
}

void Lcd_Init() {
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0b00111111);
    __delay_ms(5);
    Lcd_Cmd(0b00111111);
    __delay_us(150);
    Lcd_Cmd(0b00111111);
    /////////////////////////////////////////////////////
    Lcd_Cmd(0b00111000);
    Lcd_Cmd(0b00001000);
    Lcd_Cmd(0b00000001);
    Lcd_Cmd(0b00000111);  //en esta tengo duda de los últimos dos bits. 

}

void Lcd_Write_Char(char a) {
    char  y;
    y = a;
    RS = 1; // => RS = 1
    Lcd_Port(y); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left() {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

