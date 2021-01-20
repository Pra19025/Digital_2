/*
 * File:   main.c
 * Author: Noel Prado
 *
 * Created on 20 de enero de 2021, 11:06 AM
 */


#include <xc.h>

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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


//**********************************************************************************************************************************************
// Variables 
//**********************************************************************************************************************************************
int variable;


//**********************************************************************************************************************************************
// Prototipos de funciones 
//**********************************************************************************************************************************************

void Setup (void);
void delay (char n);


//**********************************************************************************************************************************************
// Ciclo principal
//**********************************************************************************************************************************************


void main(void) {
    Setup();
    variable = 0;
    


//**********************************************************************************************************************************************
// Loop principal
//**********************************************************************************************************************************************
    
    while(1){
        
        if(PORTCbits.RC0 == 1){
            
            PORTCbits.RC5 = 1;
            delay(15);
            PORTCbits.RC5 = 0;
            PORTCbits.RC6 = 1;
            delay(15);
            PORTCbits.RC6 = 0;
            PORTCbits.RC7 = 1;
            delay(15);
            PORTCbits.RC7 = 0;
            
        } 
        
        if(PORTCbits.RC1 == 1){
            delay(5);
            if(PORTCbits.RC1 == 0){
                PORTA++;
            }
            
            
        }
        
        
       
        
    }
    
    
    return;
}

//**********************************************************************************************************************************************
// Funciones
//**********************************************************************************************************************************************


void Setup(void) {
    PORTA = 0; 
    PORTB = 0;
    PORTCbits.RC0 = 1;
    PORTCbits.RC1 = 1;
    PORTCbits.RC2 = 1;
    
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 0;
    
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISA = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    TRISB= 0;
    
}


void delay (char n){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<255; j++) {
           
    }
    }
}
