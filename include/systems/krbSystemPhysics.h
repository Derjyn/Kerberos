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
* @file   krbSystemPhysics.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Physics system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemPhysics_h
#define krbSystemPhysics_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"
#include "utility/krbMath.h"

#include "BtOgre/BtOgrePG.h"
#include "BtOgre/BtOgreGP.h"
#include "BtOgre/BtOgreExtras.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Ogre
{
  class SceneManager;
  class SceneNode;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief Physics system
//
class SystemPhysics final : 
  public System, 
  public Ogre::Singleton<SystemPhysics>
{
public:
  SystemPhysics(Config* config, Logger* log);
  ~SystemPhysics();

  static SystemPhysics& getSingleton();
  static SystemPhysics* getSingletonPtr();

  void init();
  void cycle(float delta, float rate, bool paused);
  void halt();

  void toggleDebug();

  void createBody(string name, string mesh, Vector3 pos);

  float getPhysicsRate();
  btDynamicsWorld* getPhysWorld() { return m_PhysWorld; }

protected:
  bool    b_DebugOn;
  bool    b_InfinitePlane;
  float   f_PhysicsRate;
  int     i_PhysicsSteps;
  float   f_Gravity;

  Ogre::SceneManager*     m_SceneMgr;
  Ogre::SceneNode*        m_WorldNode;

  btDynamicsWorld*        m_PhysWorld;
  BtOgre::DebugDrawer*    m_PhysDebug;

  btDbvtBroadphase*                     m_PhysBroadphase;
	btDefaultCollisionConfiguration*      m_PhysCollisionConfig;
	btCollisionDispatcher*                m_PhysDispatcher;
	btSequentialImpulseConstraintSolver*  m_PhysSolver;

private:
  void parseConfig();
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemPhysics_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\