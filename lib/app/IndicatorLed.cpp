/*
 * IndicatorLed.cpp
 *
 *  Created on: 07.06.2019
 *      Author: dniklaus
 */


//#include "main.h"
//#include "stm32l432xx.h"
//#include "stm32l4xx_hal_gpio.h"
#include "SpinTimer.h"
#include "IndicatorLed.h"

const unsigned long IndicatorLed::s_blinkTimeMillis = 250;
const unsigned long IndicatorLed::s_blinkTimeMillisCharging = IndicatorLed::s_blinkTimeMillis;     // fast blink
const unsigned long IndicatorLed::s_blinkTimeMillisActive   = IndicatorLed::s_blinkTimeMillis * 4; // slow blink rate

//-----------------------------------------------------------------------------

class BlinkTimerAdapter : public SpinTimerAdapter
{
private:
  IndicatorLed* m_indicatorLed;

public:
  BlinkTimerAdapter(IndicatorLed* indicatorLed)
  : m_indicatorLed(indicatorLed)
  { }

  void timeExpired()
  {
    if (0 != m_indicatorLed)
    {
      IndicatorLedAdapter* indicatorLedAdapter = m_indicatorLed->adapter();
      if (0 != indicatorLedAdapter)
      {
        indicatorLedAdapter->toggleLed();
      }
    }
  }
};

//-----------------------------------------------------------------------------

IndicatorLed::IndicatorLed(IndicatorLedAdapter* indicatorLedAdapter /* = 0 */)
: m_blinkTimer(new SpinTimer(new BlinkTimerAdapter(this), SpinTimer::IS_RECURRING))
, m_adapter(indicatorLedAdapter)
{
  if (0 != m_adapter)
  {
    m_adapter->attachIndicatorLed(this);
  }
}

IndicatorLed::~IndicatorLed()
{
  delete m_blinkTimer;
  m_blinkTimer = 0;
}

void IndicatorLed::assignAdapter(IndicatorLedAdapter* indicatorLedAdapter)
{
  m_adapter = indicatorLedAdapter;
  if (0 != m_adapter)
  {
    m_adapter->attachIndicatorLed(this);
  }
}

IndicatorLedAdapter* IndicatorLed::adapter()
{
  return m_adapter;
}

void IndicatorLed::init()
{
  blink();
}

void IndicatorLed::off()
{
  m_blinkTimer->cancelTimer();
  if (0 != adapter())
  {
    adapter()->setLedoff();
  }
}

void IndicatorLed::on()
{
  m_blinkTimer->cancelTimer();
  if (0 != adapter())
  {
    adapter()->setLedOn();
  }
}

void IndicatorLed::blink(uint32_t blinkTimeMillis /* = s_blinkTimeMillis*/)
{
  m_blinkTimer->cancelTimer();
  if (0 != adapter())
  {
    adapter()->toggleLed();
  }
  m_blinkTimer->startTimer(blinkTimeMillis);
}

