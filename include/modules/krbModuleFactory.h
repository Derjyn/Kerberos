#pragma once

#ifndef krbModuleFactory_H
#define krbModuleFactory_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModuleFactory.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "modules\krbModuleCamera.h"
#include "modules\krbModuleDebug.h"

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class ModuleFactory {
public:
  ModuleFactory(Logger *logger, Timer *coreTimer, INIReader *config) {    
    pLogger = logger;
    pCoreTimer = coreTimer;
    pConfig = config;
  }

  typedef enum ModList {
    MODULE_CAMERA,
    MODULE_DEBUG
  } ModList;

///////////////////////////////////////////////////////////////////////////////

  Module *addModule(const ModList &module) {
    switch (module) {
    case MODULE_CAMERA:
      pModCamera = new ModuleCamera();
      pModCamera->setConfig(pConfig);
      pModCamera->setLogger(pLogger);
      pModCamera->setCoreTimer(pCoreTimer);
      pModCamera->setAdded(true);
      logAdd(pModCamera->getModuleName());
      return pModCamera;
      break;
    case MODULE_DEBUG:
      pModDebug = new ModuleDebug();
      pModDebug->setConfig(pConfig);
      pModDebug->setLogger(pLogger);
      pModDebug->setCoreTimer(pCoreTimer);
      pModDebug->setAdded(true);
      logAdd(pModDebug->getModuleName());
      return pModDebug;
      break;
    default:
      return nullptr;
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  ModuleCamera* getModCamera() { return pModCamera; }
  ModuleDebug* getModDebug() { return pModDebug; }

///////////////////////////////////////////////////////////////////////////////

  void initModule(const ModList &module) {
    switch (module) {
    case MODULE_CAMERA:
      pModCamera->init();
      pModCamera->setAlive(true);
      logInit(pModCamera->getModuleName());
      break;
    case MODULE_DEBUG:
      pModDebug->init();
      pModDebug->setAlive(true);
      logInit(pModDebug->getModuleName());
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  void updateModule(const ModList &module) {
    switch (module) {
    case MODULE_CAMERA:
      pModCamera->update();
      break;
    case MODULE_DEBUG:
      pModDebug->update();
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

  void removeModule(const ModList &module) {
    std::string tmp = "";
    switch (module) {
    case MODULE_CAMERA:
      pModCamera->halt();
      tmp = pModCamera->getModuleName();
      delete pModCamera;
      logRemove(tmp);
      break;
    case MODULE_DEBUG:
      pModDebug->halt();
      tmp = pModDebug->getModuleName();
      delete pModDebug;
      logRemove(tmp);
      break;
    }
  }

///////////////////////////////////////////////////////////////////////////////

private:
  Logger *pLogger;
  INIReader *pConfig;
  Timer *pCoreTimer;

  void logAdd(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_MODULE,
      "ADDED " + name);
  }
  void logInit(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_MODULE,
      "INITIALIZED " + name);
  }
  void logRemove(const std::string &name) {
    pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_MODULE,
      "REMOVED AND DESTROYED " + name);
  }

protected:
  ModuleCamera *pModCamera;
  ModuleDebug *pModDebug;
};

// EOF ////////////////////////////////////////////////////////////////////////

}

#endif