/*
 * IChargerAdapter.h
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#ifndef ICHARGERADAPTER_H_
#define ICHARGERADAPTER_H_

#include "Charger.h"

class IChargerAdapter
{
public:
  virtual bool isUsbPwrOn() = 0;
  virtual bool isLiPoChrg() = 0;

  virtual void notifyChargerStateChange(Charger::eChargerState prevState, Charger::eChargerState currState) { }

  virtual ~IChargerAdapter() { }

protected:
  IChargerAdapter() { }

private: // forbidden default functions
  IChargerAdapter& operator = (const IChargerAdapter& src); // assignment operator
  IChargerAdapter(const IChargerAdapter& src);              // copy constructor
};

#endif /* ICHARGERADAPTER_H_ */
