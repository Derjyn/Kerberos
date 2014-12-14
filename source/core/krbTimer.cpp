/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*   For sales inqueries, see <http://www.omglasergunspewpewpew.com/>           *
*                                                                              *
*******************************************************************************/

#include "core\krbTimer.h"

#include <sstream>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Timer::Timer(bool run)
{
  if (run) 
  {
    resetTimer();
    resetClock();
  }

  Hand.millisecond = 0;
  Hand.second = 0;
  Hand.minute = 0;
  Hand.hour = 0;
}

Timer::~Timer()
{
}

/*****************************************************************************
*****************************************************************************/

void Timer::cycle(float rate)
{
  Hand.millisecond = clockElapsed() * rate;

  if (Hand.millisecond >= 1000.0)
  {
    Hand.second++;

    Hand.millisecond = 0;
    resetClock();

    if (Hand.second >= 60)
    {
      Hand.minute++;

      Hand.second = 0;
      resetClock();
      
      if (Hand.minute >= 60)
      {
        Hand.hour++;

        Hand.minute = 0;
        resetClock();
      }
    }
  }
}

/*****************************************************************************
*****************************************************************************/
void Timer::reset()
{
  resetTimer();
  resetClock();
}

void Timer::resetTimer() 
{
  _startTimer = timerHRC::now();
}

void Timer::resetClock()
{
  _startClock = clockHRC::now();
}

/*****************************************************************************
*****************************************************************************/

Timer::timerMS Timer::elapsedTimer() const
{
  return std::chrono::duration_cast<timerMS>(timerHRC::now() - _startTimer);
}

Timer::clockMS Timer::elapsedClock() const
{
  return std::chrono::duration_cast<clockMS>(clockHRC::now() - _startClock);
}

/*****************************************************************************
*****************************************************************************/

std::string Timer::getClockString()
{
  std::stringstream ss;
  ss <<
    Hand.hour << "hrs " <<
    Hand.minute << "min " <<
    Hand.second << "sec " <<
    Hand.millisecond << "ms";

  return ss.str();
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/