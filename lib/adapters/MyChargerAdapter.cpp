/*
 * MyChargerAdapter.cpp
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#include "main.h"
#include "Application.h"
#include "IndicatorLed.h"
#include "MyChargerAdapter.h"

MyChargerAdapter::MyChargerAdapter()
{ }

MyChargerAdapter::~MyChargerAdapter()
{ }

bool MyChargerAdapter::isUsbPwrOn()
{
  int usb_pwron_n = 0; // HAL_GPIO_ReadPin(USB_PWRON__GPIO_Port, USB_PWRON__Pin);
  return (0 == usb_pwron_n);
}

bool MyChargerAdapter::isLiPoChrg()
{
  int lipo_chrg_n = 0; // HAL_GPIO_ReadPin(LIPO_CHRG__GPIO_Port, LIPO_CHRG__Pin);
  return (0 == lipo_chrg_n);
}

void MyChargerAdapter::notifyChargerStateChange(Charger::eChargerState prevState, Charger::eChargerState currState)
{
  uint32_t blinkTimeMillis = IndicatorLed::s_blinkTimeMillisCharging;
  if (Charger::ECS_NOTCONNECTED == currState)
  {
    blinkTimeMillis = IndicatorLed::s_blinkTimeMillisActive;
  }
  Application::Instance()->indicatorLed()->blink(blinkTimeMillis);
}
