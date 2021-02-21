#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
#include "stm32f4xx_adc.h"
#include "stm32f4xx_crc.h"
#include "stm32f4xx_dbgmcu.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_flash.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_iwdg.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_sdio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_wwdg.h"
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

#if defined (STM32F429_439xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_ltdc.h"
#include "stm32f4xx_sai.h"
#endif /* STM32F429_439xx */

#if defined (STM32F427_437xx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma2d.h"
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_sai.h"
#endif /* STM32F427_437xx */

#if defined (STM32F40_41xxx)
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rng.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_fsmc.h"
#endif /* STM32F40_41xxx */

#if defined (STM32F411xE)
#include "stm32f4xx_flash_ramfunc.h"
#endif /* STM32F411xE */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* If an external clock source is used, then the value of the following define
   should be set to the value of the external clock source, else, if no external
   clock is used, keep this define commented */
/*#define I2S_EXTERNAL_CLOCK_VAL   12288000 */ /* Value of the external clock in Hz */


/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */



// 一些宏
#ifndef true
    #define true 1
#endif
#ifndef false
    #define false 0
#endif
#define _NULL_ ((void *)0)

#define USE_SHELL         true  // 启用 littleShell
#define USE_ELOG          true  // 启用 easyLogger
#define USE_CM_BACKTRACE  true  // 启用致命错误拦截

#if true == USE_ELOG
    #define printLog(format, ...)  log_a(format, ##__VA_ARGS__)
    #define printDbg(format, ...)  log_d(format, ##__VA_ARGS__)
    #define printErr(format, ...)  log_e(format, ##__VA_ARGS__)
    #define printInfo(format, ...) log_i(format, ##__VA_ARGS__)
#endif
// 计算和其他
#include "stdio.h"
#include "sort.h"
#include "fun.h"

// 一些类型
typedef void (*Func)(void);
// 一些公开的变量、函数
extern volatile uint32_t gTime0;
extern volatile uint32_t gTime1;

extern void nvicIRQConf(uint8_t NVIC_IRQCh, uint8_t NVIC_Rob_Rriority, uint8_t NVIC_Son_Priority);
extern void sysDelayUS(uint32_t us);
extern void sysDelayMS(uint32_t ms);
extern uint8_t passwordOK;


#endif /* __STM32F4xx_CONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
