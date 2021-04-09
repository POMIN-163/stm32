#include "breath.h"

#define BREATH_PORT GPIOF
#define BREATH_PIN GPIO_PIN_9
#define BREATH_IO GPIOF, GPIO_PIN_9

#define BREATH_CLK TIM14               // 定时器号
#define BREATH_CHx CH1                 // 定时器通道号
#define BREATH_CLK_Handler BREATH_CLK##_Handler
#define BREATH_PWM_Handler BREATH_CLK##_##BREATH_CHx##Handler

TIM_HandleTypeDef  BREATH_CLK_Handler;  // 呼吸灯定时器句柄
TIM_OC_InitTypeDef BREATH_PWM_Handler;  // 呼吸灯定时器 PWM 通道句柄

static uint32_t duty = 250;
static uint8_t dir = 0;

void breathLedInit(void) {
    BREATH_CLK_Handler.Instance = BREATH_CLK;
    BREATH_CLK_Handler.Init.Period = 500;
    BREATH_CLK_Handler.Init.Prescaler = 840;
    BREATH_CLK_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    BREATH_CLK_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&BREATH_CLK_Handler);
    BREATH_PWM_Handler.OCMode = TIM_OCMODE_PWM1;
    BREATH_PWM_Handler.Pulse = duty;
    BREATH_PWM_Handler.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&BREATH_CLK_Handler, &BREATH_PWM_Handler, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&BREATH_CLK_Handler, TIM_CHANNEL_1);
    /*
    HAL_TIM_PWM_Init();
    HAL_TIM_PWM_MspInit
    gpioAFConf(GPIOF, GPIO_Pin_9, GPIO_High_Speed, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_AF_TIM14);
    timPwmConf(TIM14, 840, 500, TIM_CounterMode_Up, TIM_CKD_DIV1,
           OC1, TIM_OCMode_PWM1, TIM_OutputState_Enable, TIM_OCPolarity_Low);
    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
    nvicIRQConf(TIM8_TRG_COM_TIM14_IRQn, 0x01, 0x03);
    */
}
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == BREATH_CLK) {
    }
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == BREATH_CLK) {
        GPIO_InitTypeDef BREATH_Init_Struct;
        __HAL_RCC_TIM14_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        BREATH_Init_Struct.Pin = BREATH_PIN;
        BREATH_Init_Struct.Pull = GPIO_PULLUP;
        BREATH_Init_Struct.Speed = GPIO_SPEED_HIGH;
        BREATH_Init_Struct.Mode = GPIO_MODE_AF_PP;
        BREATH_Init_Struct.Alternate = GPIO_AF9_TIM14;
        HAL_GPIO_Init(BREATH_PORT, &BREATH_Init_Struct);
    }
}
/*
void TIM8_TRG_COM_TIM14_IRQHandler(void) {
    if(TIM_GetITStatus(TIM14, TIM_IT_Update) == SET) {
        if(duty > 300) dir = 0;
        if(duty < 5) dir = 1;
        if(dir) duty++;
        else duty--;
        TIM_SetCompare1(TIM14,duty);	          // 修改比较值，修改占空比
    }
    TIM_ClearITPendingBit(TIM14, TIM_IT_Update);  //清除中断标志位
}
*/
