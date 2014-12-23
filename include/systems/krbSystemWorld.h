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
* @file   krbSystemWorld.h
* @author Nathan Harris
* @date   23 December 2014
* @brief  World system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemWorld_h
#define krbSystemWorld_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"
#include "utility/krbMath.h"

#include "entities/krbEntityCamera.h"
#include "entities/krbEntityLight.h"
#include "entities/krbEntityMesh.h"
#include "entities/krbEntityPhysicsDynamic.h"
#include "entities/krbEntityPhysicsStatic.h"

/*****************************************************************************
*****************************************************************************/

class btDynamicsWorld;

namespace Ogre
{
  class ManualObject;
  class SceneManager;
  class SceneNode;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief World system. Tracks world time, the enviornment, and entities
//
class SystemWorld final : public System
{
public:
  SystemWorld(Config* config, Logger* log);
  ~SystemWorld();

  void init();
  void cycle();
  void halt();

  void connectOgre(Ogre::SceneManager* sceneMgr, Ogre::Viewport* viewport);
  void connectBullet(btDynamicsWorld* world);

  void resetClock();
  void pauseWorld();

  void createGrid();
  void toggleGrid();

  // ENVIRONMENT
  void setAmbient(Color color);
  void setFog(Color color, float density, float start, float end);
  void setEnvironment(Color baseColor, 
    float fogDensity, float fogStart, float fogEnd);

  // ENTITIES
  EntityCamera*   addCamera(string name);
  EntityLight*    addLight(string name, EntityLight::LightType type);
  EntityMesh*     addMesh(string name, string mesh, float scale);

  EntityPhysicsDynamic* addDynamic(string name, string mesh, 
  int maxAge, float mass, Vector3 pos);

  EntityPhysicsStatic* addStatic(string name, string mesh, 
  int maxAge, Vector3 pos);

  // SETTERS //////////////////////////////////////////////////////////////////
  void setWorldRate(float rate);

  // GETTERS //////////////////////////////////////////////////////////////////
  float       getWorldRate();
  float       getWorldTimeRate();
  TimeVector  getTimeVector();
  string      getTimeString();
  bool        isPaused();
  int         getEntityCount();

protected:
  float       f_WorldRate;
  float       f_WorldTimeRate;
  TimeVector  vec_Time;
  bool        b_WorldPaused;

  Color       env_Color;

  btDynamicsWorld*      m_BulletWorld;

  Ogre::SceneManager*   m_SceneMgr;
  Ogre::SceneNode*      m_WorldNode;
  Ogre::Viewport*       m_OgreVP;

  Clock*    ent_Clock;
  float     ent_Pulse;
  int       i_EntityCount;

  float     f_GridExtent;
  float     f_GridScale;
  bool      b_GridVisible;
  Ogre::ManualObject* m_Grid;

  vector<Entity*>           vec_Entities;
  vector<Entity*>::iterator vit_Entities;

private:
  void parseConfig();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemWorld_h

/***]EOF[*********************************************************************/