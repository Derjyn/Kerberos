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

/**
\file   krbTimer.h
\author Nathan Harris
\date   13 December 2014
\brief  Tick, tock
\details
  The timer in Kerberos is utilizing the chrono high resolution timer.
  It can be polled for the time passed in milliseconds, but also includes
  a handy "clock" or "hand" that, if cycled, keeps track of seconds, minutes,
  and hours like a normal clock.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbTimer_h
#define krbTimer_h

/*****************************************************************************
*****************************************************************************/

#include <chrono>
#include <string>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class Timer
{
  typedef std::chrono::high_resolution_clock timerHRC;
  typedef std::chrono::milliseconds timerMS;

  typedef std::chrono::milliseconds clockMS;
  typedef std::chrono::high_resolution_clock clockHRC;

public:
  Timer(bool run);
  ~Timer();

  void cycle(float rate);

  void reset();
  void resetTimer();
  void resetClock();

  double timerElapsed() { return double(elapsedTimer().count()); }  
  double clockElapsed() { return double(elapsedClock().count()); }

  std::string getClockString();

  struct Hand
  {
    double millisecond;
    int second;
    int minute;
    int hour;
  } Hand;

private:
  timerHRC::time_point _startTimer;
  timerMS elapsedTimer() const;

  clockHRC::time_point _startClock;
  clockMS elapsedClock() const;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbTimer_h

/***]EOF[*********************************************************************/