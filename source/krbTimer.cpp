///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbTimer.cpp
//  UPDATED : 12/04/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbTimer.h"

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

Timer::Timer(bool run) {
  if (run) {
    reset();
  }

  Time.millisec = 0;
  Time.second = 0;
  Time.minute = 0;
  Time.hour = 0;
  Time.day = 0;

  bIsPaused = false;
}

///////////////////////////////////////////////////////////////////////////////

void Timer::reset(void) {
  _start = high_resolution_clock::now();
  _startClock = high_resolution_clock::now();
}

///////////////////////////////////////////////////////////////////////////////

Timer::microsec Timer::elapsedMicrosec() const {
  return std::chrono::duration_cast<microsec>(
    high_resolution_clock::now() - _start);
}

Timer::millisec Timer::elapsedMillisec() const {
  return std::chrono::duration_cast<millisec>(
    high_resolution_clock::now() - _start);
}

Timer::millisec Timer::elapsedMillisecClock() const {
  return std::chrono::duration_cast<millisecClock>(
    high_resolution_clock::now() - _startClock);
}

///////////////////////////////////////////////////////////////////////////////

void Timer::runClock(double rate) {
  if (!bIsPaused) {
    Time.millisec = elapsedMillisecClock().count() * rate;

    if (Time.millisec >= 1000.0) {
      _startClock = high_resolution_clock::now();

      Time.second++;

      if (Time.second >= 60) {
        _startClock = high_resolution_clock::now();

        Time.second = 0;
        Time.minute++;

        if (Time.minute >= 60) {
          _startClock = high_resolution_clock::now();

          Time.minute = 0;
          Time.hour++;

          if (Time.hour >= 24) {
            _startClock = high_resolution_clock::now();

            Time.hour = 0;
            Time.day++;
          }
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void Timer::toggleClockPause() {
  bIsPaused = !bIsPaused;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////