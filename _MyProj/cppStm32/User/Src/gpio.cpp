#include "gpio.hpp"

pFun EXTI_Handle[16];
void *handleparm[16];

void _GPIO_Pin_Config(
    GPIO_TypeDef* gpiox, uint32_t gpio_pin_x, GPIOMode_TypeDef gpio_mode,
	GPIOSpeed_TypeDef gpio_speed, GPIOOType_TypeDef gpio_otype, GPIOPuPd_TypeDef gpio_pupd
) {
	switch ((uint32_t)gpiox)
	{
	case GPIOA_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; break;
	case GPIOB_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; break;
	case GPIOC_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; break;
	case GPIOD_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; break;
	case GPIOE_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; break;
	case GPIOF_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; break;
	case GPIOG_BASE: RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; break;
	default:
		break;
	}
    GPIO_InitTypeDef Temp={gpio_pin_x, gpio_mode, gpio_speed, gpio_otype, gpio_pupd};
    GPIO_Init(gpiox, &Temp);
}
void GPIO::H(void) {
	gpio->BSRRL = pin; // GPIO_SetBits(gpiox, gpio_pin_x);
	status = 1;
}
void GPIO::L(void) {
	gpio->BSRRH = pin; // GPIO_ResetBits(gpiox, gpio_pin_x);
	status = 0;
}
// 默认上拉, 快速, 推挽
OutPort::OutPort() {
	return;
}
OutPort::OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_UP);
}
OutPort::OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, GPIO_PuPd_UP);
}
OutPort::OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, gpio_pupd);
}
OutPort::OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, gpio_pupd);
	if(status) GPIO::H();
	else GPIO::L();
}
OutPort::~OutPort() {
	return;
}
// 默认上拉, 快速, 推挽
LED::LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_UP);
}
LED::LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, GPIO_PuPd_UP);
}
LED::LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, gpio_pupd);
}
LED::LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_OUT, gpio_speed, GPIO_OType_PP, gpio_pupd);
	if(status) GPIO::H();
	else GPIO::L();
}
void LED::ON() {
	GPIO::L();
}
void LED::OFF() {
	GPIO::H();
}
void LED::Toggle() {
	if(status) gpio->BSRRL = pin;
	else gpio->BSRRH = pin;
}
// 默认快速, 上拉
InputPort::InputPort() {
	return;
}
InputPort::InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_IN, GPIO_Fast_Speed, GPIO_OType_OD, GPIO_PuPd_UP);
}
InputPort::InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_IN, gpio_speed, GPIO_OType_OD, GPIO_PuPd_UP);
}
InputPort::InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_IN, gpio_speed, GPIO_OType_OD, gpio_pupd);
}
InputPort::InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status) {
	gpio = gpiox; pin = gpio_pin_x;
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_IN, gpio_speed, GPIO_OType_OD, gpio_pupd);
	if(status) GPIO::H();
	else GPIO::L();
}
/*
InputPort::InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOPuPd_TypeDef gpio_pupd, uint32_t mEXTITrigger, void(*handle)) {
	uint8_t EXTI_PinSource;
	int8_t  EXTI_IQRn;
	gpio = gpiox;
	pin = gpio_pin_x;
	// GPIO_Pin_x 转换到 GPIO_PinSourcex
	for (uint8_t i = 0; i < 16; i++) {
		if ((gpio_pin_x >> i) & 0x1) {
			EXTI_PinSource = i;
			break;
		}
	}
	EXTI_Line = EXTI_PinSource;
	switch (EXTI_PinSource)
	{
	case 0:EXTI_IQRn = EXTI0_IRQn; break;
	case 1:EXTI_IQRn = EXTI1_IRQn; break;
	case 2:EXTI_IQRn = EXTI2_IRQn; break;
	case 3:EXTI_IQRn = EXTI3_IRQn; break;
	case 4:EXTI_IQRn = EXTI4_IRQn; break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:EXTI_IQRn = EXTI9_5_IRQn; break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:EXTI_IQRn = EXTI15_10_IRQn; break;
	default:
		break;
	}
	_GPIO_Pin_Config(gpiox, gpio_pin_x, GPIO_Mode_IN, GPIO_High_Speed, GPIO_OType_OD, gpio_pupd);
	HAL_NVIC_SetPriority((IRQn_Type)EXTI_IQRn, 3, 0);
	HAL_NVIC_EnableIRQ((IRQn_Type)EXTI_IQRn);
	EXTI_Handle[EXTI_Line] = (pFun)handle;
};
uint32_t InputPort::ReadData() {
	return gpio->IDR;
}
InputPort::~InputPort() {
	return;
}
*/
/*
@arg GPIO_AF_RTC_50Hz : Connect RTC_50Hz pin to AF0(default after reset)
*            @arg GPIO_AF_MCO : Connect MCO pin(MCO1 and MCO2) to AF0(default after reset)
*            @arg GPIO_AF_TAMPER : Connect TAMPER pins(TAMPER_1 and TAMPER_2) to AF0(default after reset)
*            @arg GPIO_AF_SWJ : Connect SWJ pins(SWD and JTAG)to AF0(default after reset)
*            @arg GPIO_AF_TRACE : Connect TRACE pins to AF0(default after reset)
*            @arg GPIO_AF_TIM1 : Connect TIM1 pins to AF1
*            @arg GPIO_AF_TIM2 : Connect TIM2 pins to AF1
*            @arg GPIO_AF_TIM3 : Connect TIM3 pins to AF2
*            @arg GPIO_AF_TIM4 : Connect TIM4 pins to AF2
*            @arg GPIO_AF_TIM5 : Connect TIM5 pins to AF2
*            @arg GPIO_AF_TIM8 : Connect TIM8 pins to AF3
*            @arg GPIO_AF_TIM9 : Connect TIM9 pins to AF3
*            @arg GPIO_AF_TIM10 : Connect TIM10 pins to AF3
*            @arg GPIO_AF_TIM11 : Connect TIM11 pins to AF3
*            @arg GPIO_AF_I2C1 : Connect I2C1 pins to AF4
*            @arg GPIO_AF_I2C2 : Connect I2C2 pins to AF4
*            @arg GPIO_AF_I2C3 : Connect I2C3 pins to AF4
*            @arg GPIO_AF_SPI1 : Connect SPI1 pins to AF5
*            @arg GPIO_AF_SPI2 : Connect SPI2 / I2S2 pins to AF5
*            @arg GPIO_AF_SPI4 : Connect SPI4 pins to AF5
*            @arg GPIO_AF_SPI5 : Connect SPI5 pins to AF5
*            @arg GPIO_AF_SPI6 : Connect SPI6 pins to AF5
*            @arg GPIO_AF_SAI1 : Connect SAI1 pins to AF6 for STM32F42xxx / 43xxx devices.
*            @arg GPIO_AF_SPI3 : Connect SPI3 / I2S3 pins to AF6
*            @arg GPIO_AF_I2S3ext : Connect I2S3ext pins to AF7
*            @arg GPIO_AF_USART1 : Connect USART1 pins to AF7
*            @arg GPIO_AF_USART2 : Connect USART2 pins to AF7
*            @arg GPIO_AF_USART3 : Connect USART3 pins to AF7
*            @arg GPIO_AF_UART4 : Connect UART4 pins to AF8
*            @arg GPIO_AF_UART5 : Connect UART5 pins to AF8
*            @arg GPIO_AF_USART6 : Connect USART6 pins to AF8
*            @arg GPIO_AF_UART7 : Connect UART7 pins to AF8
*            @arg GPIO_AF_UART8 : Connect UART8 pins to AF8
*            @arg GPIO_AF_CAN1 : Connect CAN1 pins to AF9
*            @arg GPIO_AF_CAN2 : Connect CAN2 pins to AF9
*            @arg GPIO_AF_TIM12 : Connect TIM12 pins to AF9
*            @arg GPIO_AF_TIM13 : Connect TIM13 pins to AF9
*            @arg GPIO_AF_TIM14 : Connect TIM14 pins to AF9
*            @arg GPIO_AF_OTG_FS : Connect OTG_FS pins to AF10
*            @arg GPIO_AF_OTG_HS : Connect OTG_HS pins to AF10
*            @arg GPIO_AF_ETH : Connect ETHERNET pins to AF11
*            @arg GPIO_AF_FSMC : Connect FSMC pins to AF12
*            @arg GPIO_AF_FMC : Connect FMC pins to AF12 for STM32F42xxx / 43xxx devices.
*            @arg GPIO_AF_OTG_HS_FS : Connect OTG HS(configured in FS) pins to AF12
*            @arg GPIO_AF_SDIO : Connect SDIO pins to AF12
*            @arg GPIO_AF_DCMI : Connect DCMI pins to AF13
*            @arg GPIO_AF_LTDC : Connect LTDC pins to AF14 for STM32F429xx / 439xx devices.
*            @arg GPIO_AF_EVENTOUT : Connect EVENTOUT pins to AF15
*/

/*
AFOutput::AFOutput(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, uint8_t mGPIO_AF)
{
	PORT = gpiox;
	GPIO_PIN = gpio_pin_x;
	uint8_t GPIO_PinSource;
	_GPIO_Pin_Config(PORT, GPIO_PIN, GPIO_MODE_AF_PP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_PULLUP, mGPIO_AF);
	for (uint8_t i = 0; i < 16; i++)
	{
		if ((gpio_pin_x >> i) & 0x1)
		{
			GPIO_PinSource = i;
			break;
		}
	}
}
AFOutput::~AFOutput()
{

}

void EXTI0_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0))
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
		if (EXTI_Handle[0] != NULL)
		{
			EXTI_Handle[0](handleparm[0]);
		}
	}
}

void EXTI1_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1))
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
		if (EXTI_Handle[1] != NULL)
		{
			EXTI_Handle[1](handleparm[1]);
		}
	}
}

void EXTI2_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2))
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
		if (EXTI_Handle[2] != NULL)
		{
			EXTI_Handle[2](handleparm[2]);
		}
	}
}
*/
