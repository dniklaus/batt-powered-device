/*
 * MyIndicatorLedAdapter.h
 *
 *  Created on: 13.09.2019
 *      Author: dniklaus
 */

#ifndef MYINDICATORLEDADAPTER_H_
#define MYINDICATORLEDADAPTER_H_

#include "stm32f4xx.h"
#include <IndicatorLed.h>

class MyIndicatorLedAdapter: public IndicatorLedAdapter
{
public:
  MyIndicatorLedAdapter(short int indicatorLedPin = c_LED_Pin, const GPIO_TypeDef* indicatorLedPort = c_LED_GPIO_Port);
  virtual ~MyIndicatorLedAdapter();

  void initLedPin();
  void setLedoff();
  void setLedOn();
  void toggleLed();

private:
  short int m_indicatorLedPin;
  const GPIO_TypeDef* m_indicatorLedPort;
  const static short int     c_LED_Pin;
  const static GPIO_TypeDef* c_LED_GPIO_Port;

private: // forbidden default functions
  MyIndicatorLedAdapter& operator = (const MyIndicatorLedAdapter& src); // assignment operator
  MyIndicatorLedAdapter(const MyIndicatorLedAdapter& src);              // copy constructor
};

#endif /* MYINDICATORLEDADAPTER_H_ */
