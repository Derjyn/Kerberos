/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*                                                                              *
*******************************************************************************/

/**
* @file   krbSystemRender.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  Rendering system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemRender_h
#define krbSystemRender_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

#include "Ogre3D/OgreCommon.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Ogre 
{
  class Camera;
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
class Logger;

/*****************************************************************************
*****************************************************************************/

class SystemRender final : public System
{
public:
  SystemRender(Config* config, Logger* log);
  ~SystemRender();

  void init();
  void cycle();
  void halt();

  Ogre::RenderSystem*     getRenderer();
  Ogre::RenderWindow*     getWindow();
  Ogre::Viewport*         getViewport();
  Ogre::SceneManager*     getSceneManager();
  int                     getWindowWidth();
  int                     getWindowHeight();
  float                   getAspectRatio();

protected:
  Ogre::Root*             m_Ogre;
  Ogre::RenderSystem*     m_Renderer;
  unsigned long           hWnd;
  Ogre::RenderWindow*     m_Window;
  int                     i_ScreenW, i_ScreenH;
  Ogre::Viewport*         m_Viewport;
  Ogre::SceneManager*     m_SceneMgr;
  Ogre::Camera*           m_Cam;
  Ogre::SceneNode*        m_CamNode;

private:
  void parseConfig();

  Ogre::NameValuePairList pl_WindowOpts;
  string                  str_OgreLog;
  string                  str_WinTitle;
  unsigned short          i_ViewportW, i_ViewportH;
  float                   f_AspectRatio;
  string                  str_Resolution;
  bool                    b_Fullscreen;
  int                     i_TexFilter;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemRender_h

/***]EOF[*********************************************************************/