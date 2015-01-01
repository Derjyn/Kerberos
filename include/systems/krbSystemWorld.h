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
* @date   01 January 2015
* @brief  World system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemWorld_h
#define krbSystemWorld_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"
#include "utility/krbMath.h"

#include "entities/krbEntityCamera.h"
#include "entities/krbEntityLight.h"
#include "entities/krbEntityMesh.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Ogre
{
  class ManualObject;
  class SceneManager;
  class SceneNode;
  class Viewport;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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

  void createEntityBBS();
  void toggleEntityBillboards();

  // ENVIRONMENT
  void setAmbient(Color color);
  void setFog(Color color, int type, float density, float start, float end);
  void setEnvironment(Color baseColor, Vector3 fogSettings);

  // ENTITIES
  EntityCamera* addEntityCamera(string name, Vector3 position);
  //EntityCamera* addEntityCamera(string name, Vector3 position, Vector3 direction);
  EntityLight* addEntityLight(string name, Vector3 position);
  //EntityMesh* addMesh(string name, string mesh, float scale);

  // SETTERS //////////////////////////////////////////////////////////////////
  void                  setWorldRate(float rate);

  // GETTERS //////////////////////////////////////////////////////////////////
  bool                  isPaused();
  float                 getWorldRate();
  float                 getWorldTimeRate();
  TimeVector            getTimeVector();
  string                getTimeString();
  int                   getEntityCount();
  Ogre::SceneNode*      getWorldNode() { return m_WorldNode; }

protected:
  float                 f_WorldScale;
  float                 f_WorldRate;
  float                 f_WorldRateTemp;
  float                 f_WorldTimeRate;
  TimeVector            vec_Time;
  bool                  b_WorldPaused;

  Color                 env_Color;

  Ogre::SceneManager*   m_SceneMgr;
  Ogre::SceneNode*      m_WorldNode;
  Ogre::Viewport*       m_OgreVP;

  Clock*                ent_Clock;
  float                 ent_Pulse;

  float                 f_GridExtent;
  float                 f_GridScale;
  bool                  b_GridVisible;
  Ogre::ManualObject*   m_Grid;

  int                   i_EntityCount;
  int                   i_EmitterCount;

  Ogre::BillboardSet*   bbs_Basic;
  Ogre::BillboardSet*   bbs_Cameras;
  Ogre::BillboardSet*   bbs_Lights;
  Ogre::BillboardSet*   bbs_Emitters;
  Ogre::BillboardSet*   bbs_Meshes;
  Ogre::BillboardSet*   bbs_Sounds;
  bool                  b_EntityBillboardsOn;

private:
  void parseConfig();
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemWorld_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\