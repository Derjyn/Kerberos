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
#include "systems\world\krbWorldSystem.h"
#include "entities\krbEntityCamera.h"

#include "Ogre3D\OgreManualObject.h"
#include "Ogre3D\OgreSceneManager.h"
#include "Ogre3D\OgreViewport.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

WorldSystem::WorldSystem(Config* config, Logger* log, Timer* timer,
  Ogre::SceneManager* sceneMgr, btDynamicsWorld* bulletWorld,
  Ogre::Viewport* vp)
{
  setName("World system");  

  pConfig         = config;
  pLog            = log;
  pTimer          = timer;
  pWorldTimer = new Timer(false);
  pSceneMgr       = sceneMgr;
  pBulletWorld    = bulletWorld;
  pOgreVP         = vp;

  fWorldTimeRate  = 20.0f;

  iTotalEntity    = 0;
  iTotalCamera    = 0;
  iTotalDynamic   = 0;

  logCreation();
}

WorldSystem::~WorldSystem()
{
  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void WorldSystem::start()
{
  pWorldTimer->resetTimer();
  pWorldTimer->resetClock();
  
  logStart();
}

void WorldSystem::cycle()
{
  pWorldTimer->cycle(fWorldTimeRate);

  for (unsigned i = 0; i < vecEntity.size(); ++i)
  {
    vecEntity[i]->update();
  }
}

void WorldSystem::stop()
{
  for (unsigned i = 0; i < vecEntity.size(); ++i)
  {
    delete vecEntity[i];
    vecEntity.erase(vecEntity.begin() + i);
    --i;
  }

  logStop();
}

/*****************************************************************************
*****************************************************************************/
// GRID

void WorldSystem::createGrid(std::string name, float scale, int steps, 
  Color lineColor, Color baseColor, Color centerColor)
{
  Ogre::ManualObject* grid = new Ogre::ManualObject(name);

  grid->begin("grid", Ogre::RenderOperation::OT_LINE_LIST);

  Ogre::Real res = scale;
  unsigned int count = steps;
  unsigned int halfCount = count / 2;
  Ogre::Real full = (res * count);
  Ogre::Real half = full / 2;
  Ogre::Real y = 0;
  Ogre::ColourValue c;

  for (unsigned i = 0; i < count + 1; i++)
  {
    if (i == halfCount)
    {
      c = toOgre(centerColor); // \todo Fix this so it plays with Bullet
    }
    else
    {
      c = toOgre(lineColor);
    }

    grid->position(-half, y, -half + (res * i));
    grid->colour(toOgre(baseColor));
    grid->position(0, y, -half + (res * i));
    grid->colour(c);
    grid->position(0, y, -half + (res * i));
    grid->colour(c);
    grid->position(half, y, -half + (res * i));
    grid->colour(toOgre(baseColor));

    if (i == halfCount)
    {
      c = toOgre(centerColor); // \todo Fix this so it plays with Bullet
    }
    else
    {
      c = toOgre(lineColor);
    }

    grid->position(-half + (res * i), y, -half);
    grid->colour(toOgre(baseColor));
    grid->position(-half + (res * i), y, 0);
    grid->colour(c);
    grid->position(-half + (res * i), y, 0);
    grid->colour(c);
    grid->position(-half + (res * i), y, half);
    grid->colour(toOgre(baseColor));
  }

  grid->end();
  pSceneMgr->getRootSceneNode()->attachObject(grid);
}

Ogre::ManualObject* WorldSystem::getGrid(std::string name)
{
  return pSceneMgr->getManualObject(name);
}

/*****************************************************************************
*****************************************************************************/
// CAMERAS

EntityCamera* WorldSystem::addCamera(std::string name, bool pitchLim)
{
  EntityCamera* cam = new EntityCamera("ENT_CAM_" + name, 
    pSceneMgr, pOgreVP, pitchLim);

  vecEntity.push_back(cam);

  ++iTotalEntity;
  ++iTotalCamera;

  return cam;
}

Entity* WorldSystem::getCamera(std::string name)
{  
  for (unsigned i = 0; i < vecEntity.size(); ++i)
  {
    if ("ENT_CAM_" + name == vecEntity[i]->getName())
    {
      return vecEntity[i];
    }
  }

  return nullptr;
}

void WorldSystem::deleteCamera(std::string name)
{
  for (unsigned i = 0; i < vecEntity.size(); ++i)
  {
    if ("ENT_CAM_" + name == vecEntity[i]->getName())
    {
      delete vecEntity[i];
      vecEntity.erase(vecEntity.begin() + i);
      --i;

      --iTotalEntity;
      --iTotalCamera;
    }
  }
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/