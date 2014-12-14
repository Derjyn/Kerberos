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

#include "core\krbLogger.h"

#include "systems\render\krbRenderSystem.h"

#include "Ogre3D\OgreColourValue.h"
#include "Ogre3D\OgreRoot.h"
#include "Ogre3D\OgreRenderWindow.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

RenderSystem::RenderSystem(Config* config, Logger* log, Timer* timer, 
  Ogre::Root* ogre)
{
  setName("Render system");

  pConfig = config;
  pLog    = log;
  pTimer  = timer;
  pOgre   = ogre;

  logCreation();
}

RenderSystem::~RenderSystem()
{
  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void RenderSystem::start()
{
  // LOAD THE OPENGL RENDER SYSTEM, AND SET IT
  pOgre->loadPlugin("RenderSystem_GL");
  pRenderer = pOgre->getRenderSystemByName("OpenGL Rendering Subsystem");
  pOgre->setRenderSystem(pRenderer);
  pOgre->initialise(false);

  // LOAD OTHER PLUGINS
  pOgre->loadPlugin("Plugin_OctreeSceneManager");

  // NAB SOME PROPERTIES
  strWinTitle = pConfig->getString("RENDER", "WinTitle");
  iScreenW = pConfig->getInt("RENDER", "ScreenWidth");
  iScreenH = pConfig->getInt("RENDER", "ScreenHeight");
  strResoltuion = Ogre::StringConverter::toString(iScreenW) +
    "x" + Ogre::StringConverter::toString(iScreenH);
  bFullscreen = pConfig->getBool("RENDER", "Fullscreen");

  Ogre::NameValuePairList plWindowOpts;
  plWindowOpts["fullscreen"] = pConfig->getBool("RENDER", "Fullscreen");
  plWindowOpts["vsync"] = pConfig->getBool("RENDER", "VSync");
  plWindowOpts["FSAA"] = pConfig->getInt("RENDER", "FSAA");
  plWindowOpts["border"] = pConfig->getString("RENDER", "WinBorder");

  int texFilter = pConfig->getInt("RENDER", "Filtering");
  switch (texFilter) 
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
      pConfig->getInt("RENDER", "Anisotropy"));
    break;
  }

  pViewportBG = toOgre(pConfig->getColor("RENDER", "MatteColor"));

  // CREATE WINDOW
  pWindow = pOgre->createRenderWindow(
    strWinTitle, 
    iScreenW, iScreenH, 
    bFullscreen, 
    &plWindowOpts);

  pWindow->getCustomAttribute("WINDOW", &hWnd);

  // CREATE SCENE MANAGER
  pSceneMgr = pOgre->createSceneManager(Ogre::ST_GENERIC);
  pSceneMgr->getRootSceneNode()->setPosition(0, 0, 0);

  // CREATE DEFAULT CAMERA
  pCam = pSceneMgr->createCamera("CAM_SCENE");
  pCam->setNearClipDistance(0.01);
  pCamNode = pSceneMgr->createSceneNode("NODE_CAM_SCENE");
  pCamNode->attachObject(pCam);
  pCamNode->setPosition(100, 100, 100);
  pCam->lookAt(Ogre::Vector3(0, 0, 0));
  pCam->setAutoAspectRatio(true);

  // CREATE VIEWPORT
  pViewport = pWindow->addViewport(pCam);
  pViewport->setBackgroundColour(pViewportBG);

  logStart(); 
}

/*****************************************************************************
*****************************************************************************/

void RenderSystem::cycle()
{
  pOgre->renderOneFrame();
}

/*****************************************************************************
*****************************************************************************/

void RenderSystem::stop()
{
  // \bug Error on destruction
  //pSceneMgr->clearScene();
  //delete pCam;

  //pWindow->removeAllViewports();  
  //pWindow->destroy();

  logStop();
}

/*****************************************************************************
*****************************************************************************/

Ogre::RenderSystem* RenderSystem::getRenderer()
{ 
  return pRenderer; 
}

Ogre::SceneManager* RenderSystem::getSceneManager() 
{ 
  return pSceneMgr; 
}

Ogre::RenderWindow* RenderSystem::getWindow()
{ 
  return pWindow; 
}

Ogre::Viewport* RenderSystem::getViewport()
{ 
  return pViewport; 
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/