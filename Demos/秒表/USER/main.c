#include "stm8l15x.h"
int main( void )
{
GPIO_Init(GPIOA,GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Slow);
  return 0;
}
