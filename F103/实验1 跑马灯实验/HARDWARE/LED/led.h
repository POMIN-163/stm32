#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED PCout(13)
#define DIO PBout(9)
#define RCLK PBout(8)
#define SCLK PBout(7)

void LED_GPIO_Config(void);
void SMG_GPIO_Config(void);
void SMG_OUT(unsigned char X);
void SMG_Display(unsigned int x);
		 				    
#endif
