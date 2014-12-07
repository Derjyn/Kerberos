///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemWorld.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbCore.h"

#include "systems\krbSystemRender.h"
#include "systems\krbSystemWorld.h"

#include "modules\krbModuleCamera.h"

#include "OgreEntity.h"
#include "OgreMeshManager.h"
#include "OgreSceneManager.h"
#include "OgreStringConverter.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::SystemWorld* Ogre::Singleton<Kerberos::SystemWorld>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

SystemWorld::SystemWorld() {
  setName("SYSTEM WORLD");

  dWorldTicks = 0;

  pSysRender = SystemRender::getSingletonPtr();
}

SystemWorld& SystemWorld::singleton(void) { return (*msSingleton); }
SystemWorld* SystemWorld::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::init(void) { 
  pSceneMgr = pSysRender->getSceneManager();

  dWorldRate = pConfig->GetReal("World", "WorldRate", 10.0);

  pWorldTimer = new Timer(false);  
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::halt(void) {
  delete pWorldTimer;
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::advanceTime(void) {
  pWorldTimer->runClock(dWorldRate);
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::resetTimer(void) {
  pWorldTimer->reset();
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::createWorld(void) {
  pModCamera = ModuleCamera::singletonPtr();

  pWorldNode = pSceneMgr->getRootSceneNode()->createChildSceneNode("NODE_WORLD");
  pWorldNode->setPosition(0, 0, 0);

  Ogre::MeshManager::getSingleton().createPlane(
    "MESH_FLOOR", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    Ogre::Plane(Ogre::Vector3::UNIT_Y, -1),
    4096, 4096, 8, 8, true, 1, 8, 8, Ogre::Vector3::UNIT_Z);

  Ogre::Entity* entFloor = pSceneMgr->createEntity("ENT_FLOOT", "MESH_FLOOR");
  entFloor->setMaterialName("demo/floor_grid_512");
  entFloor->setCastShadows(false);

  pFloorNode = pWorldNode->createChildSceneNode("NODE_FLOOR");
  pFloorNode->attachObject(entFloor);
  pFloorNode->setPosition(0, 0, 0);  

  pSysRender->getCameraNode()->setPosition(2048, 512, 2048);
  pSysRender->getCamera()->lookAt(0, 0, 0);

  pSceneMgr->setAmbientLight(Ogre::ColourValue(0.65, 0.65, 0.67));

  pModCamera->createCamera("WORLD", pWorldNode, 1024, 512, 1024);
  //pModCamera->activateCamera("WORLD", pSysRender->getViewport());
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::setSceneManager(Ogre::SceneManager* sceneMgr) {
  pSceneMgr = sceneMgr;
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::setTimeRate(double rate) {
  dWorldRate = rate;
}

///////////////////////////////////////////////////////////////////////////////

void SystemWorld::resetTimeRate(void) {
  dWorldRate = pConfig->GetReal("World", "WorldRate", 10.0);
}

///////////////////////////////////////////////////////////////////////////////

double SystemWorld::getWorldMillisec(void) {
  return pWorldTimer->getMilliseconds() * dWorldRate;
}

///////////////////////////////////////////////////////////////////////////////

double SystemWorld::getWorldTPS(void) {
  return getWorldMillisec() / pWorldTimer->getMilliseconds();
}

///////////////////////////////////////////////////////////////////////////////

std::string SystemWorld::getWorldTimeString(void) {
  return 
    std::to_string(pWorldTimer->Time.day) + " days " +
    std::to_string(pWorldTimer->Time.hour) + "hrs " +
    std::to_string(pWorldTimer->Time.minute) + "min " +
    std::to_string(pWorldTimer->Time.second) + "sec";
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////