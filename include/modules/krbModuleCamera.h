#pragma once

#ifndef krbModuleCamera_H
#define krbModuleCamera_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModuleCamera.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include ".\modules\krbModule.h"

///////////////////////////////////////////////////////////////////////////////

namespace Ogre {
  class Camera;
  class SceneManager;
  class SceneNode;
  class Viewport;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

class SystemRender;
class SystemWorld;

///////////////////////////////////////////////////////////////////////////////

class ModuleCamera : public Module, public Ogre::Singleton<ModuleCamera> {
public:
  ModuleCamera();
  static ModuleCamera& singleton(void);
  static ModuleCamera* singletonPtr(void);

  void createCamera(std::string name, Ogre::SceneNode *node, 
    float posX, float posY, float posZ);
  void activateCamera(std::string name, Ogre::Viewport *viewport);
  void positionCamera(std::string name, float posX, float posY, float posZ);

  // GETTERS
  Ogre::Camera *getCamera(std::string name);
  std::string getActiveCameraName(void);

private:
  friend class ModuleFactory;

protected:
  void init(void);
  void update(void);
  void halt(void);

  SystemRender          *pSysRender;
  SystemWorld           *pSysWorld;

  Ogre::SceneManager    *pSceneMgr;

  std::string           strActiveCameraName;
};

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif