
#ifndef GY-521_H
#define	GY-521_H

#include <xc.h>
#include <stdint.h>
#include "I2C.h"
/**
 * configura el sensor para su correcto funcionamiento
 */
void GY_init(void);
void GY_read(float*);

#endif	/* MPU_6050_H */