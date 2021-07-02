#include "SysTick.h"
/******************************************************************************/
/* DEFINITION OF TYPES                                                        */
/******************************************************************************/

static __IO uint32_t __systemTickTimmingDelay = 0;
static __IO uint32_t __systemTickCount  = 0;
static __IO uint32_t __systemTickTimeout  = 0;
/**
  * @brief  The function inits SysTick modules
  * @param  None
  * @retval None
  */
void SysTick_Configuration(void)
{ 
  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 100000)) //1000000:us 1000:ms
  { 
    /* Capture error */
    NVIC_SystemReset();
  }
}
/**
  * @brief  System Tick hardware interrupt event.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  /* used for delay */
  if (__systemTickTimmingDelay != 0)
  {
    /* Decre __systemTickTimmingDelay by one */
    __systemTickTimmingDelay--;
  }
}

/**
  * @brief  Delay in milisecond
  * @param  None
  * @retval None
  */
__IO void SysTick_Delay10Us(uint32_t nTime)
{
  __systemTickTimmingDelay = nTime;
  while(__systemTickTimmingDelay != 0);
}
/**
  * @brief  Delay in milisecond
  * @param  None
  * @retval None
  */
__IO void SysTick_DelayMs(uint32_t nTime)
{
  SysTick_Delay10Us(nTime*100);
}
/**
  * @brief  Get current value from SySTick
  * @param  None
  * @retval None
  */
uint32_t SysTick_GetTickCount(void)
{
  return __systemTickCount;
}

/**
  * @brief  Start one Timeout in milisecond
  * @param  None
  * @retval None
  */
void SysTick_StartTimeout(uint32_t nTime)
{
  __systemTickTimeout = nTime;
}

/**
  * @brief  Start one timeout in milisecond
  * @param  None
  * @retval None
  */
BOOLEAN SysTick_IsReachTimeout(void)
{
  return (__systemTickTimeout == 0);
}
