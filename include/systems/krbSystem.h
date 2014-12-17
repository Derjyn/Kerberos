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
* @file   krbSystem.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Base class for systems
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystem_h
#define krbSystem_h

/*****************************************************************************
*****************************************************************************/

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

class Config;
class Clock;
class Logger;

/*****************************************************************************
*****************************************************************************/

class System
{
public:
  virtual ~System() = 0;

  virtual void init()   = 0;
  virtual void cycle()  = 0;
  virtual void halt()   = 0;

  string getName() { return str_Name; }

protected:
  string        str_Name;

  Config*       m_Config;
  Clock*        m_Clock;
  Logger*       m_Log;
};

inline System::~System() {}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystem_h

/***]EOF[*********************************************************************/