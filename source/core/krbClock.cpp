/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*                                                                              *
*******************************************************************************/

/**
* @file   krbClock.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  Tick, tock...
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "core/krbClock.h"

#include <sstream>

using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Clock::Clock(bool run)
{
  if (run) 
  {
    reset();
    resetClock();
  }

  Hand.msexCount    = 0;
  Hand.millisecond  = 0;
  Hand.second       = 0;
  Hand.minute       = 0;
  Hand.hour         = 0;
}

Clock::~Clock()
{
}

/*****************************************************************************
*****************************************************************************/

Clock::millisec Clock::elapsed() const
{
  return std::chrono::duration_cast<millisec>(hrc::now() - _start);
}

void Clock::reset()
{
  _start = hrc::now();
}

string Clock::msexString()
{
  std::stringstream ss;
  ss << msex() << "ms";

  return ss.str();
}

/*****************************************************************************
*****************************************************************************/

void Clock::resetClock()
{
  _startClock = hrcClock::now();
}

Clock::millisecClock Clock::elapsedClock() const
{
  return std::chrono::duration_cast<millisecClock>(hrcClock::now() - _startClock);
}

void Clock::tick(double rate)
{
  Hand.millisecond = msexClock();

  if (Hand.millisecond >= 1000.0)
  {
    Hand.second++;
    Hand.msexCount += msexClock();
    Hand.millisecond = 0;
    resetClock();

    if (Hand.second >= 60.0)
    {
      Hand.minute++;
      Hand.second = 0;
      resetClock();

      if (Hand.minute >= 60.0)
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

string Clock::clockString()
{
  std::stringstream ss;
  ss <<
    Hand.hour         << "hrs " <<
    Hand.minute       << "min " <<
    Hand.second       << "sec " <<
    Hand.millisecond  << "ms ";

  return ss.str();
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/