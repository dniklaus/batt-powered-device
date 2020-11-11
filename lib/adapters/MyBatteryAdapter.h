/*
 * MyBatteryAdapter.h
 *
 *  Created on: 13.06.2019
 *      Author: dniklaus
 */

#ifndef MYBATTERYADAPTER_H_
#define MYBATTERYADAPTER_H_

#include <Battery.h>

class MyBatteryAdapter: public BatteryAdapter
{
public:
  MyBatteryAdapter();
  virtual ~MyBatteryAdapter();

  unsigned int readRawBattSenseValue();

  void notifyBattVoltageOk();
  void notifyBattVoltageBelowWarnThreshold() { }
  void notifyBattVoltageBelowStopThreshold() { }
  void notifyBattVoltageBelowShutdownThreshold();

  static const BatteryThresholdConfig s_battCfg;
  static const uint32_t s_batteryStopRecheckInterval;

private: // forbidden default functions
  MyBatteryAdapter& operator = (const MyBatteryAdapter& src); // assignment operator
  MyBatteryAdapter(const MyBatteryAdapter& src);              // copy constructor
};

#endif /* MYBATTERYADAPTER_H_ */
