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
\file   krbSystem.h
\author Nathan Harris
\date   14 December 2014
\brief  Abstract base class for systems
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystem_h
#define krbSystem_h

/*****************************************************************************
*****************************************************************************/

#include "core\krbConfig.h"
#include "core\krbLogger.h"
#include "core\krbTimer.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class System
{
public:
  System() {}
  virtual ~System() {}

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void cycle() {}

  std::string getName() { return strName; }

protected:
  void setName(std::string name)  { strName = name; }
  void setConfig(Config* cfg)     { pConfig = cfg; }
  void setLog(Logger* log)        { pLog = log; }
  void setTimer(Timer* timer)     { pTimer = timer; }

  // COMMON LOG MESSAGES
  void logCreation()
  {
    pLog->logMessage(pLog->LOG_INFO, pLog->MSG_SYSTEM, strName + " created");
  }
  void logDestruction()
  {
    pLog->logMessage(pLog->LOG_INFO, pLog->MSG_SYSTEM, strName + " destroyed");
  }
  void logStart()
  {
    pLog->logMessage(pLog->LOG_INFO, pLog->MSG_SYSTEM, strName + " started");
  }
  void logStop()
  {
    pLog->logMessage(pLog->LOG_INFO, pLog->MSG_SYSTEM, strName + " stopped");
  }

  std::string strName;

  Config*     pConfig;
  Logger*     pLog;
  Timer*      pTimer;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystem_h

/***]EOF[*********************************************************************/