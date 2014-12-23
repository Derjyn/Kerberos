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
* @date   23 December 2014
* @brief  Physics system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemPhysics_h
#define krbSystemPhysics_h

/*****************************************************************************
*****************************************************************************/

#define CUSTOM_PHYS_CONF  // COMMENT OUT TO BRING BULLET DOWN TO DEFAULTS

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

#ifdef CUSTOM_PHYS_CONF
#include "Bullet/BulletDynamics/ConstraintSolver/btContactSolverInfo.h"
#include "Bullet/BulletCollision/BroadphaseCollision/btDispatcher.h"
#endif

/*****************************************************************************
*****************************************************************************/

class btBroadphaseInterface;
class btCollisionDispatcher;
class btDefaultCollisionConfiguration;
class btDynamicsWorld;
class btSequentialImpulseConstraintSolver;
class btRigidBody;

namespace BtOgre
{
  class DebugDrawer;
}

namespace Ogre
{
  class SceneManager;
  class SceneNode;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Physics system
//
class SystemPhysics final : public System
{
public:
  SystemPhysics(Config* config, Logger* log);
  ~SystemPhysics();

  void init();
  void cycle(float delta, float rate, bool paused);
  void halt();

  void connectOgre(Ogre::SceneManager* sceneMgr);
  void toggleDebug();

  btDynamicsWorld*      getBulletWorld();
  float                 getPhysicsRate();

protected:
  bool    b_DebugOn;
  float   f_PhysicsRate;
  int     i_PhysicsSteps;

  Ogre::SceneManager*   m_SceneMgr;
  Ogre::SceneNode*      m_WorldNode;

  btDynamicsWorld*      m_BulletWorld;
  BtOgre::DebugDrawer*  m_BulletDrawer;

  btBroadphaseInterface* m_Broadphase;
  btCollisionDispatcher* m_Dispatcher;
  btDefaultCollisionConfiguration* m_CollisionConfig;
  btSequentialImpulseConstraintSolver* m_Solver;

  btRigidBody*          m_PlaneRB;

#ifdef CUSTOM_PHYS_CONF
  btContactSolverInfo   m_SolverInfo;
  btDispatcherInfo      m_DispInfo;
#endif

private:
  void parseConfig();
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSystemPhysics_h

/***]EOF[*********************************************************************/