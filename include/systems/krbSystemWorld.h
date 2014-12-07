#pragma once

#ifndef krbSystemWorld_H
#define krbSystemWorld_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemWorld.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbSystem.h"

///////////////////////////////////////////////////////////////////////////////

class INIReader;

namespace Ogre {
  class Entity;
  class SceneManager;
  class SceneNode;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class Timer;
class ModuleCamera;

///////////////////////////////////////////////////////////////////////////////

class SystemWorld : public System, public Ogre::Singleton<SystemWorld> {
public:
  SystemWorld();
  static SystemWorld &singleton(void);
  static SystemWorld *singletonPtr(void);

  void advanceTime(void);
  void resetTimer(void);
  void createWorld(void);

  // SETTERS
  void setSceneManager(Ogre::SceneManager *sceneMgr);
  void setTimeRate(double rate);
  void resetTimeRate(void);

  // GETTERS
  Timer *getWorldTimer(void) { return pWorldTimer; }
  double getWorldMillisec(void);
  double getWorldTPS(void);
  std::string getWorldTimeString(void);
  Ogre::SceneNode *getWorldNode(void) { return pWorldNode; }

private:
  friend class SystemFactory;

  Timer *pWorldTimer;
  double dWorldRate;
  double dWorldTicks;

  Ogre::SceneManager *pSceneMgr;
  Ogre::SceneNode *pRootNode;
  Ogre::SceneNode *pWorldNode;
  Ogre::SceneNode *pFloorNode;

  SystemRender *pSysRender;

  ModuleCamera* pModCamera;

protected:
  void init(void);
  void halt(void);
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif