///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemRender.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "systems\krbSystemRender.h"

#include "OgreMaterialManager.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreSceneNode.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::SystemRender* Ogre::Singleton<Kerberos::SystemRender>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

SystemRender::SystemRender() {
  setName("RENDER SYSTEM");
}

SystemRender& SystemRender::singleton(void) { return (*msSingleton); }
SystemRender* SystemRender::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void SystemRender::init(void) {
  pRoot = Ogre::Root::getSingletonPtr();

  addPlugins();
  setConfigOptions();
  createWindow();
}

///////////////////////////////////////////////////////////////////////////////

void SystemRender::halt(void) {  
}

///////////////////////////////////////////////////////////////////////////////

void SystemRender::render(void) {
  pRoot->renderOneFrame();
}

///////////////////////////////////////////////////////////////////////////////

void SystemRender::addPlugins(void) {
  // LOAD THE OPENGL RENDER SYSTEM, AND SET IT
  pRoot->loadPlugin("RenderSystem_GL");
  pRenderer = pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
  pRoot->setRenderSystem(pRenderer);
  pRoot->initialise(false);

  // LOAD OTHER PLUGINS
  pRoot->loadPlugin("Plugin_OctreeSceneManager");
}

///////////////////////////////////////////////////////////////////////////////
// CREATE A RENDER WINDOW, AND SET UP A DEFAULT SCENE

void SystemRender::createWindow(void) {
  // CREATE WINDOW
  pWindow = pRoot->createRenderWindow(
    strWinTitle,
    iScreenW, iScreenH, bFullscreen,
    &plWindowOpts);
  pWindow->getCustomAttribute("WINDOW", &hWnd);

  // CREATE SCENE MANAGER
  pSceneMgr = pRoot->createSceneManager(Ogre::ST_GENERIC);
  pSceneMgr->getRootSceneNode()->setPosition(0, 0, 0);
  
  // CREATE CAMERA
  pCamera = pSceneMgr->createCamera("CAMERA_DEFAULT");
  pCamera->setNearClipDistance(2);
  pCameraNode = pSceneMgr->createSceneNode("NODE_CAMERA");
  pCameraNode->attachObject(pCamera);
  pCameraNode->setPosition(0, 0, 0);

  // CREATE VIEWPORT
  pViewport = pWindow->addViewport(pCamera);
  iViewportW = pViewport->getActualWidth();
  iViewportH = pViewport->getActualHeight();
  pViewport->setBackgroundColour(cvViewportBG);

  // SET CAMERA ASPECT RATIO
  pCamera->setAspectRatio(float(iViewportW / iViewportH)); 
}

///////////////////////////////////////////////////////////////////////////////
// SET QUALITY OPTIONS

void SystemRender::setConfigOptions(void) {
  strWinTitle = pConfig->Get("Core", "Title", "Kerberos");

  strResoltuion = pConfig->Get(
    "Video", "ScreenW", "720") + "x" + pConfig->Get("Render", "ScreenH", "480");
  plWindowOpts["resolution"] = strResoltuion;
  iScreenW = pConfig->GetINT("Render", "ScreenW", 720);
  iScreenH = pConfig->GetINT("Render", "ScreenH", 480);

  bFullscreen = pConfig->GetBoolean("Render", "Fullscreen", false);  
  plWindowOpts["fullscreen"] = pConfig->Get("Render", "Fullscreen", "false");
  plWindowOpts["vsync"] = pConfig->Get("Render", "VSync", "false");
  plWindowOpts["FSAA"] = pConfig->Get("Render", "FSAA", "0");
  plWindowOpts["border"] = pConfig->Get("Render", "Border", "resize");

  int texFilter = pConfig->GetINT("Render", "Filtering", 0);
  switch (texFilter) {
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
      pConfig->GetINT("Render", "AnisoLevel", 4));
    break;
  }

  cvViewportBG = Ogre::ColourValue(
    pConfig->GetFloat("Render", "MatteRed", 0),
    pConfig->GetFloat("Render", "MatteGreen", 0),
    pConfig->GetFloat("Render", "MatteBlue", 0));
}

///////////////////////////////////////////////////////////////////////////////

Ogre::RenderSystem* SystemRender::getRenderer() {
  return pRenderer;
}

///////////////////////////////////////////////////////////////////////////////

Ogre::SceneManager* SystemRender::getSceneManager() {
  return pSceneMgr;
}

///////////////////////////////////////////////////////////////////////////////

Ogre::RenderWindow* SystemRender::getWindow() {
  return pWindow;
}

///////////////////////////////////////////////////////////////////////////////

Ogre::Viewport* SystemRender::getViewport() {
  return pViewport;
}

///////////////////////////////////////////////////////////////////////////////

Ogre::Camera* SystemRender::getCamera() {
  return pCamera;
}

///////////////////////////////////////////////////////////////////////////////

Ogre::SceneNode* SystemRender::getCameraNode() {
  return pCameraNode;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////