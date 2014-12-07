#pragma once

#ifndef krbTimer_H
#define krbTimer_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbTimer.h
//  UPDATED : 12/04/2014
//
///////////////////////////////////////////////////////////////////////////////

#include <chrono>

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class Timer {
  typedef std::chrono::high_resolution_clock high_resolution_clock;
  typedef std::chrono::microseconds microsec;
  typedef std::chrono::milliseconds millisec;
  typedef std::chrono::milliseconds millisecClock;

public:
  Timer(bool run);

  struct Time {
    double millisec;
    unsigned int second;
    unsigned int minute;
    unsigned int hour;
    unsigned int day;
  } Time;

  void reset(void);
  void runClock(double rate);
  void toggleClockPause();

  double getMicroseconds() { return double(elapsedMicrosec().count()); }
  double getMilliseconds() { return double(elapsedMillisec().count()); }
  double getMillisecClock() { return double(elapsedMillisecClock().count()); }

private:
  high_resolution_clock::time_point _start;
  microsec elapsedMicrosec() const;
  millisec elapsedMillisec() const;

  high_resolution_clock::time_point _startClock;
  millisec elapsedMillisecClock() const;

  bool bIsPaused;
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif