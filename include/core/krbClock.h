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
* @date   25 December 2014
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

public:
  Clock(bool run);
  ~Clock();

  // BASE TIMER
  void reset();
  double msex() { return double(elapsed().count()); }
  string msexString();

private:
  hrc::time_point _start;
  millisec elapsed() const;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbClock_h

/***]EOF[*********************************************************************/