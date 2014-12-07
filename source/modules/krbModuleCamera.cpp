///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModuleCamera.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "modules\krbModuleCamera.h"

#include "systems\krbSystemRender.h"
#include "systems\krbSystemWorld.h"

#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreViewport.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::ModuleCamera* Ogre::Singleton<Kerberos::ModuleCamera>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

ModuleCamera::ModuleCamera() {
  setName("CAMERA MODULE");

  strActiveCameraName = "";
}

ModuleCamera& ModuleCamera::singleton(void) { return (*msSingleton); }
ModuleCamera* ModuleCamera::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::init() {
  pSysRender = SystemRender::getSingletonPtr();
  pSysWorld = SystemWorld::getSingletonPtr();

  pSceneMgr = pSysRender->getSceneManager();
}

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::halt(void) {
}

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::update(void) {  
}

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::createCamera(std::string name, Ogre::SceneNode *node, 
  float posX, float posY, float posZ) {
  pSceneMgr->createCamera("CAMERA_" + name);
  node->createChildSceneNode("NODE_CAMERA_" + name);
  
  pSceneMgr->getSceneNode("NODE_CAMERA_" + name)->attachObject(
    pSceneMgr->getCamera("CAMERA_" + name));

  pSceneMgr->getSceneNode("NODE_CAMERA_" + name)->setPosition(
    posX, posY, posZ);

  pSceneMgr->getCamera("CAMERA_" + name)->lookAt(0, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::activateCamera(std::string name, Ogre::Viewport *viewport) {
  viewport->setCamera(pSceneMgr->getCamera("CAMERA_" + name));

  pSceneMgr->getCamera("CAMERA_" + name)->setAspectRatio(
    viewport->getActualWidth() / viewport->getActualWidth());

  strActiveCameraName = "CAMERA_" + name + "(NODE_CAMERA_" + name + ")";
}

///////////////////////////////////////////////////////////////////////////////

void ModuleCamera::positionCamera(std::string name,
  float posX, float posY, float posZ) {
  pSceneMgr->getSceneNode("NODE_CAMERA_" + name)->setPosition(
    posX, posY, posZ);
}

///////////////////////////////////////////////////////////////////////////////

Ogre::Camera *ModuleCamera::getCamera(std::string name) {
  return pSceneMgr->getCamera("CAMERA_" + name);
}

///////////////////////////////////////////////////////////////////////////////

std::string ModuleCamera::getActiveCameraName(void) {
  return strActiveCameraName;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////
