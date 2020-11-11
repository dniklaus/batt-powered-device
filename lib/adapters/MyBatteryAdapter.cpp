/*
 * MyBatteryAdapter.cpp
 *
 *  Created on: 13.06.2019
 *      Author: dniklaus
 */

#include "main.h"
#include "stdio.h"
#include "EnergyManager.h"
#include "Battery.h"
#include "Application.h"
#include "IndicatorLed.h"
#include "Charger.h"
#include "MyBatteryAdapter.h"

const BatteryThresholdConfig MyBatteryAdapter::s_battCfg = { 3.30, // BATT_WARN_THRSHD [V]
                                                             3.20, // BATT_STOP_THRSHD [V]
                                                             3.10, // BATT_SHUT_THRSHD [V]
                                                             0.03  // BATT_HYST        [V]
                                                           };
const uint32_t s_batteryStopRecheckIntervalMillis = 3000;


MyBatteryAdapter::MyBatteryAdapter()
: BatteryAdapter()
{ }

MyBatteryAdapter::~MyBatteryAdapter()
{ }

unsigned int MyBatteryAdapter::readRawBattSenseValue()
{
  #define VBATPIN A5
  unsigned int rawBattSenseValue = battery()->adapter()->getVAdcFullrange();

//  HAL_GPIO_WritePin(FETE_G_GPIO_Port, FETE_G_Pin, GPIO_PIN_RESET); // fet close -> measurement possible

  EnergyManager::enterMcuStopMode(5); // R202 (10k) and C205 (100n) act as an RC-element with a timeconstant tau=1ms -> wait for 5*tau to allow the capacitor to charge fully to Vbatt

//  HAL_ADC_Start(&hadc1);

//  if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
//  {
//    rawBattSenseValue = HAL_ADC_GetValue(&hadc1);
//  }

//  HAL_ADC_Stop(&hadc1);
//  HAL_GPIO_WritePin(FETE_G_GPIO_Port, FETE_G_Pin, GPIO_PIN_SET); // hight z -> fet open -> no current, no measurement

  return rawBattSenseValue;
}

void MyBatteryAdapter::notifyBattVoltageOk()
{
  printf("BattVoltage is above WarnThreshold");
  // Voltage above BATT_WARN_THRSHD
  Application::Instance()->indicatorLed()->on();
}

void MyBatteryAdapter::notifyBattVoltageBelowShutdownThreshold()
{
  Application::Instance()->indicatorLed()->off();
  printf("BattVoltage is below ShutdownThreshold");
  // powerDown();
  EnergyManager::enterMcuStopMode(s_batteryStopRecheckIntervalMillis);
  // powerUp();
  battery()->evaluateBatteryStateAsync();
  Application::Instance()->charger()->evaluateStatus();
}
