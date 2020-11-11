/*
 * Application.h
 *
 *  Created on: 07.06.2019
 *      Author: dniklaus
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#ifdef __cplusplus

class IndicatorLed;
class Battery;
class Charger;

class Application
{
public:
  virtual ~Application();
  static Application* Instance();

  void setup();

  /**
   * Access the Indicator Led object.
   * @return Pointer to the IndicatorLed object.
   */
  IndicatorLed* indicatorLed();

  /**
   * Access the Battery object.
   * @return Pointer to the Battery object.
   */
  Battery* battery();

  /**
   * Access the Charger object.
   * @return Pointer to the Charger object.
   */
  Charger* charger();

private:
  Application();

private:
  IndicatorLed* m_indicatorLed;
  Battery* m_battery;
  Charger* m_charger;
  static Application* s_instance;
};

#endif


#ifdef __cplusplus
extern "C" {
#endif
extern void setupApplication();
extern void loopApplication();
#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_H_ */
