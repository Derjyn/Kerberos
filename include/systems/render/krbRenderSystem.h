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
* @file   krbRenderSystem.h
* @author Nathan Harris
* @date   13 December 2014
* @brief  Hands out the eye candy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbRenderSystem_h
#define krbRenderSystem_h

/*****************************************************************************
*****************************************************************************/

#include "..\krbSystem.h"

#include "Ogre3D\OgreCommon.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre 
{
  class Camera;
  class ColourValue;
  class RenderSystem;
  class RenderWindow;
  class Root;
  class SceneManager;
  class SceneNode;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

class Config;

/*****************************************************************************
*****************************************************************************/

class RenderSystem final : public System
{
public:
  RenderSystem(Config* config, Logger* log, Timer* timer, Ogre::Root* ogre);
  ~RenderSystem();

  void start(void);
  void cycle(void);
  void stop(void);

  // GETTERS
  Ogre::RenderSystem*     getRenderer(void);
  Ogre::RenderWindow*     getWindow(void);
  Ogre::Viewport*         getViewport(void);
  Ogre::SceneManager*     getSceneManager(void);
  float                   getAspectRatio(void);

private:
  std::string             strWinTitle;
  unsigned short          iScreenW, iScreenH;
  unsigned short          iViewportW, iViewportH;
  float                   fAspectRatio;
  std::string             strResoltuion;
  bool                    bFullscreen; 

protected:
  Ogre::Root*             pOgre;
  Ogre::RenderSystem*     pRenderer;
  unsigned long           hWnd;
  Ogre::RenderWindow*     pWindow;
  Ogre::Viewport*         pViewport;
  Ogre::ColourValue       pViewportBG;
  Ogre::SceneManager*     pSceneMgr;
  Ogre::Camera*           pCam;
  Ogre::SceneNode*        pCamNode;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbRendersystem_h

/***]EOF[*********************************************************************/