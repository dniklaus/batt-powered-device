/*
 * IndicatorLed.h
 *
 *  Created on: 07.06.2019
 *      Author: dniklaus
 */

#ifndef INDICATORLED_H_
#define INDICATORLED_H_

#include "stm32f4xx.h"

#ifdef __cplusplus

//-----------------------------------------------------------------------------

class IndicatorLed;

/**
 * Abstract LED indicator adapter.
 * Implementation for the specific technology and platform controls the
 * \ul initialisation of the LED pin
 * \ul status of the LED
 */
class IndicatorLedAdapter
{
private:
  IndicatorLed* m_indicatorLed;

public:
  virtual ~IndicatorLedAdapter() { }

  /**
   * Attach this adapter's owner object to this adapter.
   * @param indicatorLed Pointer to the owner of this adapter.
   */
  void attachIndicatorLed(IndicatorLed* indicatorLed)
  {
    m_indicatorLed = indicatorLed;
  }

  /**
   * Get the owner object of this adapter.
   * @return IndicatorLed Pointer to the owner of this adapter.
   */
  IndicatorLed* indicatorLed()
  {
    return m_indicatorLed;
  }

  /**
   * Initialize indicator LED pin.
   * Abstract, to be implemented according to the specific technology and platform.
   */
  virtual void initLedPin() = 0;

  /**
   * Set Indicator LED off.
   * Abstract, to be implemented according to the specific technology and platform.
   */
  virtual void setLedoff() = 0;

  /**
   * Set Indicator LED on.
   * Abstract, to be implemented according to the specific technology and platform.
   */
  virtual void setLedOn() = 0;

  /**
   * Toggle indicator LED.
   * Abstract, to be implemented according to the specific technology and platform.
   */
  virtual void toggleLed() = 0;

protected:
  IndicatorLedAdapter()
  : m_indicatorLed(0)
  { }
};

//-----------------------------------------------------------------------------

class SpinTimer;

class IndicatorLed
{
public:
  IndicatorLed(IndicatorLedAdapter* indicatorLedAdapter = 0);
  virtual ~IndicatorLed();

  /**
   * Assign Indicator LED Adapter Implementation.
   * @param indicatorLedAdapter Pointer to the Indicator LED Adapter object.
   */
  void assignAdapter(IndicatorLedAdapter* indicatorLedAdapter);

  /**
   * Get the Indicator LED Adapter object.
   * @return IndicatorLedAdapter Pointer to the Indicator LED Adapter object.
   */
  IndicatorLedAdapter* adapter();

  /**
   * Set Indicator LED on.
   * Switch off blinking if it was running.
   */
  void off();

  /**
   * Set Indicator LED off.
   * Switch off blinking if it was running.
   */
  void on();

  /**
   * Start Indicator LED blinking with the specified blink time.
   * @param blinkTimeMillis blink time in [ms], default: s_blinkTimeMillis (250 ms)
   */
  void blink(uint32_t blinkTimeMillis = s_blinkTimeMillis);

  void init();

public:
  const static unsigned long s_blinkTimeMillis;
  const static unsigned long s_blinkTimeMillisCharging;
  const static unsigned long s_blinkTimeMillisActive;;


private:
  SpinTimer* m_blinkTimer;
  IndicatorLedAdapter* m_adapter;

private: // forbidden default functions
  IndicatorLed& operator = (const IndicatorLed& src); // assignment operator
  IndicatorLed(const IndicatorLed& src);              // copy constructor
};

#else
typedef struct IndicatorLed IndicatorLed;
#endif

#endif /* INDICATORLED_H_ */
