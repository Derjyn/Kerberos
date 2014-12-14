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
\file   krbWorldSystem.h
\author Nathan Harris
\date   14 December 2014
\brief  Handles world phenomenon such as weather, and wrangles entitities
\details
  The world system functions as a control center for adding items to
  the simulated world, and also cycles virtual time and other phenomenon
  like weather.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbWorldSystem_h
#define krbWorldSystem_h

/*****************************************************************************
*****************************************************************************/

#include "..\krbSystem.h"
#include "..\..\KerberosUtility.h"

#include <map>

/*****************************************************************************
*****************************************************************************/

class btDynamicsWorld;

namespace Ogre
{
  class ColourValue;
  class ManualObject;
  class SceneManager;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

class Entity;
class EntityDynamic;
class EntityCamera;

/*****************************************************************************
*****************************************************************************/

class WorldSystem final : public System
{
public:
  WorldSystem(Config* config, Logger* log, Timer* timer, 
    Ogre::SceneManager* sceneMgr, btDynamicsWorld* bulletWorld,
    Ogre::Viewport* vp);
  ~WorldSystem();

  void start();
  void cycle();
  void stop();

  void createGrid(std::string name, float scale, int steps, 
    Color lineColor, Color baseColor, Color centerColor);

  // CAMERAS
  EntityCamera* addCamera(std::string name, bool pitchLim);
  Entity* getCamera(std::string name);
  void deleteCamera(std::string name);

  // GETTERS
  float getTimeRate() { return fWorldTimeRate; }
  std::string getTimeString() { return pWorldTimer->getClockString(); }
  int getTotalEntities() { return iTotalEntity; }
  int getTotalCameras() { return iTotalCamera; }
  int getTotalDynamics() { return iTotalDynamic; }
  Ogre::ManualObject* getGrid(std::string name);
  
protected:
  float                 fWorldTimeRate;
  Timer*                pWorldTimer;

  btDynamicsWorld*      pBulletWorld;
  Ogre::SceneManager*   pSceneMgr;
  Ogre::Viewport*       pOgreVP;

  unsigned int          iTotalEntity;
  unsigned int          iTotalDynamic;
  unsigned int          iTotalCamera;

  std::vector<Entity*>        vecEntity;
  std::vector<EntityDynamic*> vecEntDynamic;
  std::vector<EntityCamera*>  vecEntCamera;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbWorldSystem_h

/***]EOF[*********************************************************************/