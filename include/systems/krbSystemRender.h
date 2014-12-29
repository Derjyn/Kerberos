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
* @date   26 December 2014
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
#include "utility/krbConverter.h"
#include "utility/krbMath.h"

#include "Ogre3D/OgreCommon.h"
#include "Ogre3D/OgreFrameListener.h"
#include "Ogre3D/OgreHardwarePixelBuffer.h"
#include "Ogre3D/OgreMaterial.h"
#include "Ogre3D/OgreRenderTargetListener.h"
#include "Ogre3D/OgreTexture.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Ogre 
{
  class Camera;
  class MaterialManager;
  class Rectangle2D;
  class RenderSystem;
  class RenderTexture;
  class RenderWindow;
  class ResourceGroupManager;
  class Root;
  class SceneManager;
  class SceneNode;
  class TextureManager;
  class Viewport;
}

namespace ParticleUniverse
{
  class ParticleSystemManager;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

class Config;
class Logger;

/*****************************************************************************
*****************************************************************************/

//
//! \brief Render system, utilizing Ogre
//
class SystemRender final : 
  public System, 
  public Ogre::FrameListener,
  public Ogre::RenderTargetListener, 
  public Ogre::Singleton<SystemRender>
{
public:
  SystemRender(Config* config, Logger* log);
  ~SystemRender();

  static SystemRender& getSingleton();
  static SystemRender* getSingletonPtr();

  void init();
  void cycle(float delta);
  void halt();

  void loadResources();

  void setActiveCam(Ogre::Camera* camera);

  // GETTERS
  Ogre::RenderSystem*     getRenderer();
  Ogre::RenderWindow*     getWindow();
  Ogre::Viewport*         getViewport();
  Ogre::SceneManager*     getSceneManager();
  int                     getWindowWidth();
  int                     getWindowHeight();
  float                   getAspectRatio();
  float                   getLastFrameTime();

protected:
  Ogre::Root*             m_Ogre;
  Ogre::RenderSystem*     m_Renderer;
  unsigned long           hWnd;
  Ogre::RenderWindow*     m_Window;
  int                     i_ScreenW, i_ScreenH;
  Ogre::Viewport*         m_Viewport;
  Ogre::SceneManager*     m_SceneMgr;
  Ogre::Camera*           m_Cam;
  Ogre::Camera*           m_CamActive;
  Ogre::SceneNode*        m_CamNode;
  float                   f_LastFrameTime;

  Ogre::MaterialManager*        m_MatMgr;
  Ogre::TextureManager*         m_TexMgr;
  Ogre::ResourceGroupManager*   m_ResMgr;

  ParticleUniverse::ParticleSystemManager*  m_PUSysMgr;

  virtual bool frameStarted(const Ogre::FrameEvent& evt);
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
  virtual bool frameEnded(const Ogre::FrameEvent& evt);

  virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
  virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

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

  // WORKING TOWARDS A GBUFFER FOR DEFERRED RENDERING
  Ogre::Rectangle2D*		  rtt_Screen;
  Ogre::SceneNode*			  rtt_ScreenNode;
  Ogre::TexturePtr			  rtt_Texture;
  Ogre::RenderTexture*	  rtt_RenderTexture;
  Ogre::MaterialPtr			  rtt_Material;
  Ogre::Technique*			  rtt_Technique;
	Ogre::Viewport*         rtt_Viewport;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemRender_h

/***]EOF[*********************************************************************/