/*
 * Charger.cpp
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#include "SpinTimer.h"
#include "ChargerFsm.h"
#include "IChargerAdapter.h"
#include "Charger.h"

const uint32_t Charger::s_evalTimeIntervalMillis = 250;
const uint32_t Charger::s_evalTimeIntervalMillisCharging = Charger::s_evalTimeIntervalMillis;
const uint32_t Charger::s_evalTimeIntervalMillisActive   = Charger::s_evalTimeIntervalMillis * 16;

//-----------------------------------------------------------------------------

class ChargerStateEvalTimerAdapter : public SpinTimerAdapter
{
private:
  Charger* m_charger;
public:
  ChargerStateEvalTimerAdapter(Charger* charger)
  : m_charger(charger)
  { }

  void timeExpired()
  {
    if (0 != m_charger)
    {
      m_charger->evaluateStatus();
    }
  }
};

//-----------------------------------------------------------------------------

Charger::Charger(IChargerAdapter* adapter)
: m_adapter(adapter)
, m_fsm(new ChargerFsm(this))
, m_evalTimer(new SpinTimer(new ChargerStateEvalTimerAdapter(this), SpinTimer::IS_RECURRING, Charger::s_evalTimeIntervalMillisActive))
{ }

Charger::~Charger()
{
  delete m_fsm;
  m_fsm = 0;
}

void Charger::assignAdapter(IChargerAdapter* adapter)
{
  m_adapter = adapter;
}

IChargerAdapter* Charger::adapter()
{
  return m_adapter;
}

void Charger::evaluateStatus()
{
  if (0 != m_fsm)
  {
    m_fsm->evaluateStatus();
  }
}

bool Charger::isUsbConnected()
{
  bool isUsbConnected = false;
  if (0 != m_fsm)
  {
    isUsbConnected = m_fsm->isUsbConnected();
  }
  return isUsbConnected;
}

Charger::eChargerState Charger::getPreviousState()
{
  eChargerState state = ECS_NOTCONNECTED;
  if (0 != m_fsm)
  {
    state = m_fsm->getPreviousState();
  }
  return state;
}

Charger::eChargerState Charger::getCurrentState()
{
  eChargerState state = ECS_NOTCONNECTED;
  if (0 != m_fsm)
  {
    state = m_fsm->getCurrentState();
  }
  return state;
}

void Charger::notifyChargerStateChange(Charger::eChargerState prevState, Charger::eChargerState currState)
{
  uint32_t evalTimeMillis = s_evalTimeIntervalMillisActive;
  if (isUsbConnected())
  {
    evalTimeMillis = s_evalTimeIntervalMillisCharging;
  }
  m_evalTimer->cancelTimer();
  m_evalTimer->startTimer(evalTimeMillis);
}
