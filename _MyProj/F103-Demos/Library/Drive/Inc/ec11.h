#ifndef __EC11_H
#define __EC11_H
#include "system.h"

#define EC11A GPIOA, GPIO_Pin_0
#define EC11B GPIOA, GPIO_Pin_1

#define EC11_A PAin(0)
#define EC11_B PAin(1)

void ec11Init(void);
void ec11Scan(uint8_t *msg);
void ec11Run(void);

#endif

