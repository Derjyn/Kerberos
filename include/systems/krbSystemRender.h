#pragma once

#ifndef krbSystemRender_H
#define krbSystemRender_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemRender.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbSystem.h"

#include "OgreColourValue.h"
#include "OgreCommon.h"

///////////////////////////////////////////////////////////////////////////////
// PRE-DECLARE SOME CLASSES

class INIReader;

namespace Ogre {
  class Camera;
  class RenderSystem;
  class RenderWindow;
  class Root;
  class SceneManager;
  class SceneNode;
  class Viewport;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class SystemRender : public System, public Ogre::Singleton<SystemRender> {
public:
  SystemRender();
  static SystemRender &singleton(void);
  static SystemRender *singletonPtr(void);

  void render(void);

  // GETTERS
  Ogre::Camera *getCamera(void);
  Ogre::SceneNode *getCameraNode(void);
  Ogre::RenderSystem *getRenderer(void);
  Ogre::RenderWindow *getWindow(void);
  Ogre::SceneManager *getSceneManager(void);
  Ogre::Viewport *getViewport(void);

private:
  friend class SystemFactory;

protected:
  void init(void);
  void halt(void);

  void addPlugins(void);
  void createWindow(void);
  void setConfigOptions(void);

  Ogre::Camera *pCamera;
  Ogre::SceneNode *pCameraNode;
  Ogre::Root *pRoot;
  Ogre::RenderSystem *pRenderer;
  Ogre::RenderWindow *pWindow;
  Ogre::SceneManager *pSceneMgr;
  Ogre::Viewport *pViewport;

  unsigned long hWnd;
  std::string strWinTitle;
  unsigned short iScreenW, iScreenH;
  unsigned short iViewportW, iViewportH;
  std::string strResoltuion;
  bool bFullscreen;
  Ogre::NameValuePairList plWindowOpts;
  Ogre::ColourValue cvViewportBG;
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif