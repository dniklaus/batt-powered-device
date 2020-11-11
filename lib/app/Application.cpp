/*
 * Application.cpp
 *
 *  Created on: 07.06.2019
 *      Author: dniklaus
 */

#include "main.h"
#include "SpinTimer.h"
#include "UptimeInfo.h"
#include "IndicatorLed.h"
#include "Battery.h"
#include "Charger.h"
#include "MyIndicatorLedAdapter.h"
#include "MyBatteryAdapter.h"
#include "MyChargerAdapter.h"
#include "STM32UptimeInfoAdapter.h"
#include "Application.h"

Application* Application::s_instance = 0;

Application::Application()
: m_indicatorLed(new IndicatorLed(new MyIndicatorLedAdapter()))
, m_battery(new Battery(new MyBatteryAdapter(), MyBatteryAdapter::s_battCfg))
, m_charger(new Charger(new MyChargerAdapter()))
{ }

Application::~Application()
{
  delete m_charger->adapter();
  delete m_charger;
  m_charger = 0;

  delete m_battery->adapter();
  delete m_battery;
  m_battery = 0;

  delete m_indicatorLed->adapter();
  delete m_indicatorLed;
  m_indicatorLed = 0;
}

Application* Application::Instance()
{
  if (0 == s_instance)
  {
    s_instance = new Application();
  }
  return s_instance;
}

void Application::setup()
{
  m_indicatorLed->init();
}

IndicatorLed* Application::indicatorLed()
{
  return m_indicatorLed;
}

Battery* Application::battery()
{
  return m_battery;
}

Charger* Application::charger()
{
  return m_charger;
}

//-----------------------------------------------------------------------------

void setupApplication()
{
  UptimeInfo::Instance()->setAdapter(new STM32UptimeInfoAdapter());
  Application::Instance()->setup();
}

void loopApplication()
{
  scheduleTimers();
}

