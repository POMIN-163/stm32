#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void){
    while(1){
        u8 t;
        u8 len;
        u16 times=0;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        delay_init(168);
        uart_init(115200);
        led_Init();
        while(1)
        {
            if(USART_RX_STA & 0x8000)
            {
                len=USART_RX_STA&0x3fff;
                printf("\r\nContent:\r\n");
                for(t=0;t<len;t++)
                {
                    USART_SendData(USART1, USART_RX_BUF[t]);
                    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
                }
                printf("\r\n\r\n");
                USART_RX_STA=0;
            }else
            {
                times++;
                if(times%5000==0)
                {
                    printf("POMIN\r\n\r\n\r\n");
                }
                if(times%200==0)printf("\r\n");
                GPIO_SetBits(GPIOF, GPIO_Pin_9);
                delay_ms(10);
            }
        }
    }
}
