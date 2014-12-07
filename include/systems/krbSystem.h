#pragma once

#ifndef krbSystem_H
#define krbSystem_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystem.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbLogger.h"
#include "krbTimer.h"

#include "INIReader.h"

#include "OgreSingleton.h"

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class System {
public:
  virtual ~System() {
    bAdded = false;
    bAlive = false;
  };

  // GETTERS
  std::string getSystemName() { return strName; }
  bool isAdded() { return bAdded; }
  bool isAlive() { return bAlive; }

protected:
  virtual void init(void) = 0;
  virtual void halt(void) = 0;

  void setConfig(INIReader* config) { pConfig = config; }
  void setLogger(Logger* log) { pLogger = log; }
  void setCoreTimer(Timer *coreTimer) { pCoreTimer = coreTimer; }
  void setName(std::string name) { strName = name; }
  void setAdded(bool added) { bAdded = added; }
  void setAlive(bool alive) { bAlive = alive; }

  INIReader     *pConfig;
  Logger        *pLogger;
  Timer         *pCoreTimer;
  std::string   strName;
  bool          bAdded;
  bool          bAlive;
};

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif