/*
 * ChargerFsm.cpp
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#include "Charger.h"
#include "IChargerAdapter.h"
#include "ChargerFsm.h"

ChargerFsm::ChargerFsm(Charger* charger)
: m_charger(charger)
, m_prevState(Charger::ECS_NOTCONNECTED)
, m_currState(Charger::ECS_NOTCONNECTED)
{ }

ChargerFsm::~ChargerFsm()
{ }

bool ChargerFsm::isGuardNotConnected()
{
  bool isGuard = false;
  if ((0 != m_charger) && (0 != m_charger->adapter()))
  {
    // PWR_ON# = 1 && LIPO# = 1 => Charger supply not sufficient -> usb not connected
    isGuard = (!m_charger->adapter()->isUsbPwrOn() && !m_charger->adapter()->isLiPoChrg());
  }
  return isGuard;
}

bool ChargerFsm::isGuardCharging()
{
  bool isGuard = false;
  if ((0 != m_charger) && (0 != m_charger->adapter()))
  {
    bool isUsbPwrOn = m_charger->adapter()->isUsbPwrOn();
    bool isLiPoChrg = m_charger->adapter()->isLiPoChrg();
    // PWR_ON# = 0 && LIPO# = 0 => Charging, either trickle charging (if batt voltage < 2.9V, to avoid damaging the battery) or constant charging
    isGuard = (isUsbPwrOn && isLiPoChrg);
  }
  return isGuard;
}

bool ChargerFsm::isGuardStandby()
{
  bool isGuard = false;
  if ((0 != m_charger) && (0 != m_charger->adapter()))
  {
    bool isUsbPwrOn = m_charger->adapter()->isUsbPwrOn();
    bool isLiPoChrg = m_charger->adapter()->isLiPoChrg();
    // PWR_ON# = 0 && LIPO# = 1 => Charger Powered, battery full, charger idle and not charging
    isGuard = (isUsbPwrOn && !isLiPoChrg);
  }
  return isGuard;
}

void ChargerFsm::evaluateStatus()
{
  m_prevState = m_currState;
  m_currState = checkChargingState();
  if (m_currState != m_prevState)
  {
    if ((0 != m_charger) && (0 != m_charger->adapter()))
    {
      m_charger->notifyChargerStateChange(m_prevState, m_currState);
      m_charger->adapter()->notifyChargerStateChange(m_prevState, m_currState);
    }
  }
}

Charger::eChargerState ChargerFsm::checkChargingState()
{
  Charger::eChargerState cs = Charger::ECS_NOTCONNECTED;
  if (isGuardCharging())
  {
    cs = Charger::ECS_CHARGING;
  }
  else if (isGuardStandby())
  {
    cs = Charger::ECS_STANDBY;
  }
  else
  {
    cs = Charger::ECS_NOTCONNECTED;
  }
  return cs;
}

bool ChargerFsm::isUsbConnected()
{
  return (Charger::ECS_NOTCONNECTED != m_currState);
}

Charger::eChargerState ChargerFsm::getPreviousState()
{
  return m_prevState;
}

Charger::eChargerState ChargerFsm::getCurrentState()
{
  return m_currState;
}
