/*
 * MyChargerAdapter.h
 *
 *  Created on: 24.06.2019
 *      Author: dniklaus
 */

#ifndef MYCHARGERADAPTER_H_
#define MYCHARGERADAPTER_H_

#include "IChargerAdapter.h"

class MyChargerAdapter: public IChargerAdapter
{
public:
  MyChargerAdapter();
  virtual ~MyChargerAdapter();

  bool isUsbPwrOn();
  bool isLiPoChrg();

  void notifyChargerStateChange(Charger::eChargerState prevState, Charger::eChargerState currState);

private: // forbidden default functions
  MyChargerAdapter& operator = (const MyChargerAdapter& src); // assignment operator
  MyChargerAdapter(const MyChargerAdapter& src);              // copy constructor
};

#endif /* MYCHARGERADAPTER_H_ */
