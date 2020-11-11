/*
 * Charger.h
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#ifndef CHARGER_H_
#define CHARGER_H_

#include "inttypes.h"

class Charger;
class ChargerFsm;
class IChargerAdapter;
class SpinTimer;

//-----------------------------------------------------------------------------

class Charger
{
  friend class ChargerFsm;

public:
  Charger(IChargerAdapter* adapter = 0);
  virtual ~Charger();

  void assignAdapter(IChargerAdapter* adapter);
  IChargerAdapter* adapter();

  void evaluateStatus();

  bool isUsbConnected();

  typedef enum
  {
    ECS_NOTCONNECTED = 0,
    ECS_CHARGING     = 1,
    ECS_STANDBY      = 2
  }
  eChargerState;

  eChargerState getPreviousState();
  eChargerState getCurrentState();

protected:
  void notifyChargerStateChange(Charger::eChargerState prevState, Charger::eChargerState currState);

private:
  IChargerAdapter* m_adapter;
  ChargerFsm* m_fsm;
  SpinTimer* m_evalTimer;
  const static uint32_t s_evalTimeIntervalMillis;
  const static uint32_t s_evalTimeIntervalMillisCharging;
  const static uint32_t s_evalTimeIntervalMillisActive;

private: // forbidden default functions
  Charger& operator = (const Charger& src); // assignment operator
  Charger(const Charger& src);              // copy constructor
};

//-----------------------------------------------------------------------------

#endif /* CHARGER_H_ */
