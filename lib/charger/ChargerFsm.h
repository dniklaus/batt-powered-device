/*
 * ChargerFsm.h
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#ifndef CHARGERFSM_H_
#define CHARGERFSM_H_

#include "Charger.h"

class ChargerFsm
{
public:
  ChargerFsm(Charger* charger);
  virtual ~ChargerFsm();

  bool isGuardNotConnected();
  bool isGuardCharging();
  bool isGuardStandby();

  Charger* charger();

  void evaluateStatus();

  bool isUsbConnected();

  Charger::eChargerState getPreviousState();
  Charger::eChargerState getCurrentState();

private:
  Charger::eChargerState checkChargingState();

private:
  Charger* m_charger;
  Charger::eChargerState m_prevState;
  Charger::eChargerState m_currState;

private: // forbidden default functions
  ChargerFsm();
  ChargerFsm& operator = (const ChargerFsm& src); // assignment operator
  ChargerFsm(const ChargerFsm& src);              // copy constructor
};

#endif /* CHARGERFSM_H_ */
