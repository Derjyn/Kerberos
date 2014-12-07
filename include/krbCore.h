#pragma once

#ifndef krbCore_H
#define krbCore_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbCore.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "OgreSingleton.h"

///////////////////////////////////////////////////////////////////////////////

class INIReader;

namespace Gorilla {
  class Layer;
  class Rectangle;
  class Screen;
}

namespace Ogre {
  class Root;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class Logger;
class Timer;

class System;
class SystemFactory;
class SystemAudio;
class SystemGUI;
class SystemInput;
class SystemPhysics;
class SystemRender;
class SystemScript;
class SystemWorld;

class Module;
class ModuleFactory;
class ModuleCamera;
class ModuleDebug;

///////////////////////////////////////////////////////////////////////////////

class Core : public Ogre::Singleton<Core> {
public:
  Core();
  static Core &singleton(void);
  static Core *singletonPtr(void);

  // FUNCTIONS
  void init();
  void update(void);
  void halt(void);

  // GETTERS
  INIReader *getINI(void) { return pConfig; }
  Logger *getLogger(void) { return pLogger; }
  Timer *getTimer(void) { return pTimer; }

  double getLogicTicks(void) { return dLogicTicks; }
  double getLogicTPS(void);

private:
  void loadResources(void);

  void primeSystems(void);
  void haltSystems(void);

  void primeModules(void);
  void removeModules(void);

  void initDebug(void);
  void createHUD(void);
  void updateHUD(void);

  void handleInput(void);
  void handleLogic(void);

protected:
  float fInputCounter;
  float fInputRate;
  bool bIsActive;

  INIReader *pConfig;
  Logger *pLogger;
  Timer *pTimer;

  // SYSTEMS
  SystemFactory *pSysFactory;
  SystemAudio *pSysAudio;
  SystemGUI *pSysGUI;
  SystemInput *pSysInput;
  SystemPhysics *pSysPhysics;
  SystemRender *pSysRender;
  SystemScript *pSysScript;
  SystemWorld *pSysWorld;

  // MODULES
  ModuleFactory *pModFactory;
  ModuleCamera *pModCamera;
  ModuleDebug *pModDebug;

  Ogre::Root *pRoot;

  // CORE TIME
  double dDeltaTime;
  double dAccumulator;
  double dCurrentTime;
  double dNewTime;

  // LOGIC CYCLE
  double dTimePerLogicTick, dLogicTimePassed;
  double dLogicTicks;
  std::string strLogicTicks;

  // BASIC HUD
  Gorilla::Screen *pScreenHUD;
  Gorilla::Layer *pLayerHUD;
  Gorilla::Layer *pLayerCursor;
  Gorilla::Rectangle *pRectCursor;

  // "DEMO" TIME
  unsigned int iDemoTime;
};

// EOF ////////////////////////////////////////////////////////////////////////
}
#endif