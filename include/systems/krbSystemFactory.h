#pragma once

#ifndef krbSystemFactory_H
#define krbSystemFactory_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemFactory.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "systems\krbSystemAudio.h"
#include "systems\krbSystemGUI.h"
#include "systems\krbSystemInput.h"
#include "systems\krbSystemPhysics.h"
#include "systems\krbSystemRender.h"
#include "systems\krbSystemScript.h"
#include "systems\krbSystemWorld.h"

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class SystemFactory {
public:
  SystemFactory(Logger* logger, Timer* coreTimer, INIReader* config) {
    pConfig = config;
    pCoreTimer = coreTimer;
    pLogger = logger;
  }

  typedef enum SysList {
    SYSTEM_AUDIO,
    SYSTEM_GUI,
    SYSTEM_INPUT,
    SYSTEM_PHYSICS,
    SYSTEM_RENDER,
    SYSTEM_SCRIPT,
    SYSTEM_WORLD
  } SysList;

///////////////////////////////////////////////////////////////////////////////

  bool isAdded(const SysList &system) {
    switch (system) {
    case SYSTEM_AUDIO:
      return pSysAudio->bAdded;
      break;
    case SYSTEM_GUI:
      return pSysGUI->bAdded;
      break;
    case SYSTEM_INPUT:
      return pSysInput->bAdded;
      break;
    case SYSTEM_PHYSICS:
      return pSysPhysics->bAdded;
      break;
    case SYSTEM_RENDER:
      return pSysRender->bAdded;
      break;
    case SYSTEM_SCRIPT:
      return pSysScript->bAdded;
      break;
    case SYSTEM_WORLD:
      return pSysWorld->bAdded;
      break;
    default:
      return false;
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  bool isAlive(const SysList &system) {
    switch (system) {
    case SYSTEM_AUDIO:
      return pSysAudio->bAlive;
      break;
    case SYSTEM_GUI: 
      return pSysGUI->bAlive;
      break;
    case SYSTEM_INPUT:
      return pSysInput->bAlive;
      break;
    case SYSTEM_PHYSICS:
      return pSysPhysics->bAlive;
      break;
    case SYSTEM_RENDER:
      return pSysRender->bAlive;
      break;
    case SYSTEM_SCRIPT:
      return pSysScript->bAlive;
      break;
    case SYSTEM_WORLD:
      return pSysWorld->bAlive;
      break;
    default:
      return false;
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  System* addSystem(const SysList &system) {
    switch (system) {
    case SYSTEM_AUDIO:
      pSysAudio = new SystemAudio();
      pSysAudio->setConfig(pConfig);
      pSysAudio->setLogger(pLogger);
      pSysAudio->setCoreTimer(pCoreTimer);
      pSysAudio->setAdded(true);
      logAdd(pSysAudio->getSystemName());
      return pSysAudio;
      break;
    case SYSTEM_GUI:
      pSysGUI = new SystemGUI();
      pSysGUI->setConfig(pConfig);
      pSysGUI->setLogger(pLogger);
      pSysGUI->setCoreTimer(pCoreTimer);
      pSysGUI->setAdded(true);
      logAdd(pSysGUI->getSystemName());
      return pSysGUI;
      break;
    case SYSTEM_INPUT:
      pSysInput = new SystemInput();
      pSysInput->setConfig(pConfig);
      pSysInput->setLogger(pLogger);
      pSysInput->setCoreTimer(pCoreTimer);
      pSysInput->setAdded(true);
      logAdd(pSysInput->getSystemName());
      return pSysInput;
      break;
    case SYSTEM_PHYSICS:
      pSysPhysics = new SystemPhysics();
      pSysPhysics->setConfig(pConfig);
      pSysPhysics->setLogger(pLogger);
      pSysPhysics->setCoreTimer(pCoreTimer);
      pSysPhysics->setAdded(true);
      logAdd(pSysPhysics->getSystemName());
      return pSysPhysics;
      break;
    case SYSTEM_RENDER:
      pSysRender = new SystemRender();
      pSysRender->setConfig(pConfig);
      pSysRender->setLogger(pLogger);
      pSysRender->setAdded(true);
      pSysRender->setCoreTimer(pCoreTimer);
      logAdd(pSysRender->getSystemName());
      return pSysRender;
      break;
    case SYSTEM_SCRIPT:
      pSysScript = new SystemScript();
      pSysScript->setConfig(pConfig);
      pSysScript->setLogger(pLogger);
      pSysScript->setAdded(true);
      pSysScript->setCoreTimer(pCoreTimer);
      logAdd(pSysScript->getSystemName());
      return pSysScript;
      break;
    case SYSTEM_WORLD:
      pSysWorld = new SystemWorld();
      pSysWorld->setConfig(pConfig);
      pSysWorld->setLogger(pLogger);
      pSysWorld->setAdded(true);
      pSysWorld->setCoreTimer(pCoreTimer);
      logAdd(pSysWorld->getSystemName());
      return pSysWorld;
      break;
    default:
      return nullptr;
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  SystemAudio* getSysAudio() { return pSysAudio; }
  SystemGUI* getSysGUI() { return pSysGUI; }
  SystemInput* getSysInput() { return pSysInput; }
  SystemPhysics* getSysPhysics() { return pSysPhysics; }
  SystemRender* getSysRender() { return pSysRender; }
  SystemScript* getSysScript() { return pSysScript; }
  SystemWorld* getSysWorld() { return pSysWorld; }

///////////////////////////////////////////////////////////////////////////////

  void initSystem(const SysList &system) {
    switch (system) {
    case SYSTEM_AUDIO:
      pSysAudio->init();
      pSysAudio->setAlive(true);
      logInit(pSysAudio->getSystemName());
      break;
    case SYSTEM_GUI:
      pSysGUI->init();
      pSysGUI->setAlive(true);
      logInit(pSysGUI->getSystemName());
      break;
    case SYSTEM_INPUT:
      pSysInput->init();
      pSysInput->setAlive(true);
      logInit(pSysInput->getSystemName());
      break;
    case SYSTEM_PHYSICS:
      pSysPhysics->init();
      pSysPhysics->setAlive(true);
      logInit(pSysPhysics->getSystemName());
      break;
    case SYSTEM_RENDER:
      pSysRender->init();
      pSysRender->setAlive(true);
      logInit(pSysRender->getSystemName());
      break;
    case SYSTEM_SCRIPT:
      pSysScript->init();
      pSysScript->setAlive(true);
      logInit(pSysScript->getSystemName());
      break;
    case SYSTEM_WORLD:
      pSysWorld->init();
      pSysWorld->setAlive(true);
      logInit(pSysWorld->getSystemName());
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  void haltSystem(const SysList &system) {
    std::string tmp = "";
    switch (system) {
    case SYSTEM_AUDIO:
      pSysAudio->halt();
      tmp = pSysAudio->getSystemName();
      delete pSysAudio;
      logHalt(tmp);
      break;
    case SYSTEM_GUI:
      pSysGUI->halt();
      tmp = pSysGUI->getSystemName();
      delete pSysGUI;
      logHalt(tmp);
      break;
    case SYSTEM_INPUT:
      pSysInput->halt();
      tmp = pSysInput->getSystemName();
      delete pSysInput;
      logHalt(tmp);
      break;
    case SYSTEM_PHYSICS:
      pSysPhysics->halt();
      tmp = pSysPhysics->getSystemName();
      delete pSysPhysics;
      logHalt(tmp);
      break;
    case SYSTEM_RENDER:
      pSysRender->halt();
      tmp = pSysRender->getSystemName();
      delete pSysRender;
      logHalt(tmp);
      break;
    case SYSTEM_SCRIPT:
      pSysScript->halt();
      tmp = pSysScript->getSystemName();
      delete pSysScript;
      logHalt(tmp);
      break;
    case SYSTEM_WORLD:
      pSysWorld->halt();
      tmp = pSysWorld->getSystemName();
      delete pSysWorld;
      logHalt(tmp);
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

private:
  Logger        *pLogger;
  INIReader     *pConfig;
  Timer         *pCoreTimer;

  void logAdd(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_SYSTEM,
      "ADDED " + name);
  }
  void logInit(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_SYSTEM,
      "INITIALIZED " + name);
  }
  void logHalt(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_SYSTEM,
      "HALTED AND DESTROYED " + name);
  }

protected:
  SystemAudio       *pSysAudio;
  SystemGUI         *pSysGUI;
  SystemInput       *pSysInput;
  SystemPhysics     *pSysPhysics;
  SystemRender      *pSysRender;
  SystemScript      *pSysScript;
  SystemWorld       *pSysWorld;
};

// EOF ////////////////////////////////////////////////////////////////////////

}

#endif