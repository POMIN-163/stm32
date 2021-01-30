#ifndef __GPIO_HPP
#define __GPIO_HPP
#include "stm32f4xx.h"

typedef void(*pFun)(void*);

class GPIO
{
public:
	GPIO_TypeDef* gpio;
	uint16_t pin;
	bool status;
	void H(void);
	void L(void);
private:
protected:
};
class OutPort : public GPIO
{
public:
	OutPort();
	OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x);
	OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed);
	OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd);
	OutPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status);
	~OutPort();
private:
protected:
};
class LED : public OutPort
{
public:
	LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x);
	LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed);
	LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd);
	LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status);
	void ON();
	void OFF();
	void Toggle();
private:
protected:
};
class InputPort : public GPIO
{
public:
  InputPort();
	InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x);
	InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed);
	InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd);
	InputPort(GPIO_TypeDef* gpiox, uint16_t gpio_pin_x, GPIOSpeed_TypeDef gpio_speed, GPIOPuPd_TypeDef gpio_pupd, bool status);
	uint32_t ReadData();
	~InputPort();

private:
	GPIO_TypeDef* PORT;
	uint32_t GPIO_PIN;
	uint8_t EXTI_Line;
};
/*
class button : InputPort
{
public:
	button(GPIO_TypeDef* mPORT, uint32_t mGPIO_PIN, EXTITrigger_TypeDef mEXTITrigger, void(*handle), void *arg) : InputPort();
	~button : InputPort();

private:

};
*/
/*
class AFOutput : GPIO
{
public:
	AFOutput(GPIO_TypeDef* mPORT, uint16_t mGPIO_PIN, uint8_t mGPIO_AF);
	AFOutput(GPIO_TypeDef* mPORT, uint16_t mGPIO_PIN, uint32_t GPIO_Speed , uint32_t GPIO_PuPd, uint8_t mGPIO_AF);
	~AFOutput();

private:
	GPIO_TypeDef* PORT;
	uint16_t GPIO_PIN;
};
*/
extern "C"
{
	void EXTI0_IRQHandler(void);
	void EXTI1_IRQHandler(void);
	void EXTI2_IRQHandler(void);
	void EXTI3_IRQHandler(void);
	void EXTI4_IRQHandler(void);
	void EXTI9_5_IRQHandler(void);
	void EXTI15_10_IRQHandler(void);
}

#endif

