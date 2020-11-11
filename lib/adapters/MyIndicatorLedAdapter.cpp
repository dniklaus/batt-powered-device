/*
 * MyIndicatorLedAdapter.cpp
 *
 *  Created on: 13.09.2019
 *      Author: dniklaus
 */

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <MyIndicatorLedAdapter.h>

const short int MyIndicatorLedAdapter::c_LED_Pin             = LD2_Pin;
const GPIO_TypeDef* MyIndicatorLedAdapter::c_LED_GPIO_Port   = LD2_GPIO_Port;

MyIndicatorLedAdapter::MyIndicatorLedAdapter(short int indicatorLedPin /* = c_LED_Pin */, const GPIO_TypeDef* indicatorLedPort /* = c_LED_GPIO_Port*/)
: IndicatorLedAdapter()
, m_indicatorLedPin(indicatorLedPin)
, m_indicatorLedPort(indicatorLedPort)
{ }

MyIndicatorLedAdapter::~MyIndicatorLedAdapter()
{ }

void MyIndicatorLedAdapter::initLedPin()
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = m_indicatorLedPin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(const_cast<GPIO_TypeDef*>(m_indicatorLedPort), &GPIO_InitStruct);
  HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(m_indicatorLedPort), m_indicatorLedPin, GPIO_PinState::GPIO_PIN_SET);
}

void MyIndicatorLedAdapter::setLedoff()
{
  HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(m_indicatorLedPort), m_indicatorLedPin, GPIO_PinState::GPIO_PIN_RESET);
}

void MyIndicatorLedAdapter::setLedOn()
{
  HAL_GPIO_WritePin(const_cast<GPIO_TypeDef*>(m_indicatorLedPort), m_indicatorLedPin, GPIO_PinState::GPIO_PIN_SET);
}

void MyIndicatorLedAdapter::toggleLed()
{
  HAL_GPIO_TogglePin(const_cast<GPIO_TypeDef*>(m_indicatorLedPort), m_indicatorLedPin);
}

