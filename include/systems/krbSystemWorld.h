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
* @date   28 December 2014
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
#include "entities/krbEntityParticleEmitter.h"
#include "entities/krbEntityPhysicsDynamic.h"
#include "entities/krbEntityPhysicsStatic.h"

/*****************************************************************************
*****************************************************************************/

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
class SystemWorld final : 
  public System, 
  public Ogre::Singleton<SystemWorld>
{
public:
  SystemWorld(Config* config, Logger* log);
  ~SystemWorld();

  static SystemWorld& getSingleton();
  static SystemWorld* getSingletonPtr();

  void init();
  void cycle();
  void halt();

  void resetClock();
  void pauseWorld();

  void createGrid();
  void toggleGrid();
  void createPlane(Vector2 extent);

  // ENVIRONMENT
  void setAmbient(Color color);
  void setFog(Color color, float density, float start, float end);
  void setEnvironment(Color baseColor, Vector3 fogSettings);

  // ENTITIES
  EntityCamera*           addCamera(string name);
  EntityLight*            addLight(string name, EntityLight::LightType type);
  EntityMesh*             addMesh(string name, string mesh, float scale);
  EntityPhysicsStatic*    addStatic(string name, string mesh, int maxAge, Vector3 pos);
  EntityPhysicsDynamic*   addDynamic(string name, string mesh, int maxAge, Vector3 pos);
  EntityParticleEmitter*  addParticleEmitter(string name);

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
  float       f_WorldRateTemp;
  float       f_WorldTimeRate;
  TimeVector  vec_Time;
  bool        b_WorldPaused;

  Color       env_Color;

  Ogre::SceneManager*   m_SceneMgr;
  Ogre::SceneNode*      m_WorldNode;
  Ogre::Viewport*       m_OgreVP;

  Clock*    ent_Clock;
  float     ent_Pulse;

  float     f_GridExtent;
  float     f_GridScale;
  bool      b_GridVisible;
  Ogre::ManualObject* m_Grid;

  int       i_EntityCount;
  int       i_EmitterCount;

  vector<Entity*> vec_Entities;
  vector<Entity*>::iterator vit_Entities;

  vector<EntityParticleEmitter*> vec_Emitters;
  vector<EntityParticleEmitter*>::iterator vit_Emitters;

private:
  void parseConfig();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemWorld_h

/***]EOF[*********************************************************************/