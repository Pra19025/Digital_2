
#ifndef DISPLAY7_H
#define	DISPLAY7_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

uint8_t tabla7(uint8_t entrada);
void multiplexor(void);
uint8_t NibbleH(uint8_t ValorADC);
uint8_t NibbleL(uint8_t ValorADC);

#endif	/* DISPLAY7_H */

