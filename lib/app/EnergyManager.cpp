/*
 * EnergyManager.cpp
 *
 *  Created on: 13.06.2019
 *      Author: dniklaus
 */

#include "main.h"
// #include "Timer.h"
#include "EnergyManager.h"

EnergyManager::EnergyManager()
{ }

EnergyManager::~EnergyManager()
{ }

void EnergyManager::enterMcuStopMode(uint32_t stopTimeMillis)
{
  //if debugging:
#ifdef DEBUG
//  delayAndSchedule(stopTimeMillis);
   HAL_Delay(stopTimeMillis);
  return;
#endif
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  //__HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_HSI); //was hsi
//  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);

//  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, stopTimeMillis * 2, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

  HAL_SuspendTick();

  /* Enter Stop Mode */
//  HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFE);
  ////////////////
  // STOP MODE
  ////////////////
  /* Disable Wakeup Counter */
  HAL_ResumeTick();

  // adjust stopped tick counter to get continuous time base
  uint32_t adjustTickCounterAfterStop = stopTimeMillis;
  while (adjustTickCounterAfterStop > 0)
  {
    HAL_IncTick();
    --adjustTickCounterAfterStop;
  }

//  HAL_RTCEx_DeactivateWakeUpTimer (&hrtc);

  /* Configures system clock after wake-up from STOP: enable HSE, PLL and select
   PLL as system clock source (HSE and PLL are disabled in STOP mode) */
//  SystemClock_Config();

  //MX_GPIO_Init();
  //MX_SPI1_Init();
}
