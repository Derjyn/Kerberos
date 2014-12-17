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
* @file   krbClock.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Tick, tock...
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbClock_h
#define krbClock_h

/*****************************************************************************
*****************************************************************************/

#include <chrono>
#include <string>

using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Handles all things timing related in Kerberos
//
class Clock
{
  typedef std::chrono::high_resolution_clock hrc;
  typedef std::chrono::milliseconds millisec;

  typedef std::chrono::high_resolution_clock hrcClock;
  typedef std::chrono::milliseconds millisecClock;

public:
  Clock(bool run);
  ~Clock();

  // BASE TIMER
  void reset();
  double msex() { return double(elapsed().count()); }
  string msexString();

  // CLOCK TIMER
  void tick(double rate);
  void resetClock();
  double msexClock() { return double(elapsedClock().count()); }
  string clockString();

  struct Hand
  {
    double msexCount;
    double millisecond;
    double second;
    double minute;
    double hour;
  } Hand;

private:
  hrc::time_point _start;
  millisec elapsed() const;

  hrcClock::time_point _startClock;
  millisecClock elapsedClock() const;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbClock_h

/***]EOF[*********************************************************************/