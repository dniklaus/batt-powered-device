/*
 * EnergyManager.h
 *
 *  Created on: 13.06.2019
 *      Author: dniklaus
 */

#ifndef ENERGYMANAGER_H_
#define ENERGYMANAGER_H_

class EnergyManager
{
public:
  EnergyManager();
  virtual ~EnergyManager();

  static void enterMcuStopMode(uint32_t stopTimeMillis);

private: // forbidden default functions
  EnergyManager& operator = (const EnergyManager& src); // assignment operator
  EnergyManager(const EnergyManager& src);              // copy constructor
};

#endif /* ENERGYMANAGER_H_ */
