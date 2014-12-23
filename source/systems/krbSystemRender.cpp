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
* @file   krbSystemRender.cpp
* @author Nathan Harris
* @date   23 December 2014
* @brief  Rendering system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemRender.h"
#include "core/krbConfig.h"
#include "core/krbClock.h"
#include "core/krbLogger.h"

#include "Ogre3D/OgreMaterialManager.h"
#include "Ogre3D/OgreRenderWindow.h"
#include "Ogre3D/OgreResourceGroupManager.h"
#include "Ogre3D/OgreRoot.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemRender::SystemRender(Config* config, Logger* log)
{
  str_Name    = "Render";
  m_Config    = config;
  m_Log       = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Ready to render!");
}

SystemRender::~SystemRender()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": No more visuals for you!");
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::init()
{
  parseConfig();

  // CREATE OGRE ROOT AND SET LOG
  m_Ogre = new Ogre::Root("", "", str_OgreLog);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Ogre root created");

  // INIT OGRE RENDER SYSTEM, SET SOME OPTIONS
  m_Ogre->loadPlugin("RenderSystem_GL");
  m_Renderer = m_Ogre->getRenderSystemByName("OpenGL Rendering Subsystem");
  m_Ogre->setRenderSystem(m_Renderer);
  m_Ogre->initialise(false);

  // LOAD OTHER PLUGINS
  m_Ogre->loadPlugin("Plugin_OctreeSceneManager");
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Plugins loaded");

  // CREATE WINDOW
  m_Window = m_Ogre->createRenderWindow(
    str_WinTitle, i_ScreenW, i_ScreenH, b_Fullscreen, &pl_WindowOpts);
  m_Window->getCustomAttribute("WINDOW", &hWnd);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Window created");

  // CREATE SCENE MANAGER
  m_SceneMgr = m_Ogre->createSceneManager(Ogre::ST_GENERIC);
  m_SceneMgr->getRootSceneNode()->setPosition(0, 0, 0);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": SceneManager created");

  // CREATE DEFAULT CAMERA
  m_Cam = m_SceneMgr->createCamera("CAM_SCENE");
  m_Cam->setNearClipDistance(0.01);
  m_CamNode = m_SceneMgr->createSceneNode("NODE_CAM_DEFAULT");
  m_CamNode->attachObject(m_Cam);
  m_CamNode->setPosition(40, 40, 40);
  m_Cam->lookAt(Ogre::Vector3(0, 0, 0));
  m_Cam->setAutoAspectRatio(true);
  m_CamActive = m_Cam;
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Default camera created");

  // CREATE VIEWPORT
  m_Viewport = m_Window->addViewport(m_Cam);
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Default viewport created");

  // SET TEXTURE FILTERING OPTIONS
  switch (i_TexFilter)
  {
  case 0:
    Ogre::MaterialManager::getSingletonPtr()->setDefaultTextureFiltering(
      Ogre::TextureFilterOptions::TFO_NONE);
    break;
  case 1:
    Ogre::MaterialManager::getSingletonPtr()->setDefaultTextureFiltering(
      Ogre::TextureFilterOptions::TFO_BILINEAR);
    break;
  case 2:
    Ogre::MaterialManager::getSingletonPtr()->setDefaultTextureFiltering(
      Ogre::TextureFilterOptions::TFO_TRILINEAR);
    break;
  case 3:
    Ogre::MaterialManager::getSingletonPtr()->setDefaultTextureFiltering(
      Ogre::TextureFilterOptions::TFO_ANISOTROPIC);

    Ogre::MaterialManager::getSingletonPtr()->setDefaultAnisotropy(
      m_Config->getInt("RENDER", "Anisotropy"));
    break;
  }

  m_ResMgr = Ogre::ResourceGroupManager::getSingletonPtr();
  m_MatMgr = Ogre::MaterialManager::getSingletonPtr();
  m_TexMgr = Ogre::TextureManager::getSingletonPtr();

  loadResources();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::cycle()
{
  m_Ogre->renderOneFrame();
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::halt()
{
  //m_SceneMgr->clearScene(); //! \bug Causes error on shutdown

  delete m_Cam;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Scene cleared");

  m_Window->removeAllViewports();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Viewports removed");

  m_Window->destroy();
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Window destroyed");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::parseConfig()
{
  str_OgreLog     = m_Config->getString("RENDER", "OgreLog");
  str_WinTitle    = m_Config->getString("RENDER", "WinTitle");
  b_Fullscreen    = m_Config->getBool("RENDER", "Fullscreen");
  i_TexFilter     = m_Config->getInt("RENDER", "Filtering");  
  i_ScreenW       = m_Config->getInt("RENDER", "ScreenWidth");
  i_ScreenH       = m_Config->getInt("RENDER", "ScreenHeight");
  str_Resolution  = toString(i_ScreenW) + "x" + toString(i_ScreenH);

  pl_WindowOpts["fullscreen"] = m_Config->getBool("RENDER", "Fullscreen");
  pl_WindowOpts["vsync"]      = m_Config->getString("RENDER", "VSync");
  pl_WindowOpts["FSAA"]       = m_Config->getString("RENDER", "FSAA");
  pl_WindowOpts["border"]     = m_Config->getString("RENDER", "WinBorder");

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::loadResources()
{
  // GUI RESOURCES
  m_ResMgr->addResourceLocation("data/gui",
    "FileSystem", "GUI");

  // SHADERS
  m_ResMgr->addResourceLocation("data/shaders",
    "FileSystem", "SHADERS");

  // TEXTURE DATA
  m_ResMgr->addResourceLocation("data/textures",
    "FileSystem", "TEXTURES");

  // MATERIAL SCRIPTS
  m_ResMgr->addResourceLocation("data/materials",
    "FileSystem", "MATERIALS");
  m_ResMgr->addResourceLocation("data/materials/core",
    "FileSystem", "MATERIALS");

  // MESH DATA
  m_ResMgr->addResourceLocation("data/meshes",
    "FileSystem", "MESHES");

  // ENTITY PROPERTIES/SCRIPTS
  m_ResMgr->addResourceLocation("data/entities",
    "FileSystem", "ENTITIES");

  // FIRE UP OUR RESOURCE GROUPS
  m_ResMgr->initialiseAllResourceGroups();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM, 
    "Resources loaded and initialized");  
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::setActiveCam(Ogre::Camera* camera)
{
  m_CamActive = camera;
}

/*****************************************************************************
*****************************************************************************/

bool SystemRender::frameStarted(const Ogre::FrameEvent& evt)
{
  f_LastFrameTime = evt.timeSinceLastFrame;

  return true;
}
bool SystemRender::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  return true;
}
bool SystemRender::frameEnded(const Ogre::FrameEvent& evt)
{
  return true;
}

/*****************************************************************************
*****************************************************************************/

void SystemRender::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
}

 void SystemRender::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
}

/*****************************************************************************
*****************************************************************************/

Ogre::RenderSystem* SystemRender::getRenderer() { return m_Renderer; }
Ogre::RenderWindow* SystemRender::getWindow() { return m_Window; }
Ogre::Viewport*     SystemRender::getViewport() { return m_Viewport; }
Ogre::SceneManager* SystemRender::getSceneManager() { return m_SceneMgr; }

int SystemRender::getWindowWidth() { return i_ScreenW; }
int SystemRender::getWindowHeight() { return i_ScreenH; }
float SystemRender::getAspectRatio() { return i_ScreenW / i_ScreenH; }
float SystemRender::getLastFrameTime() { return f_LastFrameTime; }

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/