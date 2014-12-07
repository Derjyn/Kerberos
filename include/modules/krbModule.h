#pragma once

#ifndef krbModule_H
#define krbModule_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModule.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbLogger.h"
#include "krbTimer.h"

#include "INIReader.h"

#include "OgreSingleton.h"

///////////////////////////////////////////////////////////////////////////////

class INIReader;


///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

class Logger;
class Timer;

///////////////////////////////////////////////////////////////////////////////

class Module {
public:
  virtual ~Module() {
    bAdded = false;
    bAlive = false;
  };

  // GETTERS
  std::string getModuleName() { return strName; }
  bool isAdded() { return bAdded; }
  bool isAlive() { return bAlive; }

protected:
  virtual void init(void) = 0;
  virtual void update(void) = 0;
  virtual void halt(void) = 0;

  void setConfig(INIReader* config) { pConfig = config; }
  void setLogger(Logger* log)       { pLogger = log; }
  void setCoreTimer(Timer* timer)   { pCoreTimer = timer; }
  void setName(std::string name)    { strName = name; }
  void setAdded(bool added)         { bAdded = added; }
  void setAlive(bool alive)         { bAlive = alive; }

  INIReader*    pConfig;
  Logger*       pLogger;
  Timer*        pCoreTimer;
  std::string   strName;
  bool          bAdded;
  bool          bAlive;
};

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif