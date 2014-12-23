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
* @file   krbSystemPhysics.cpp
* @author Nathan Harris
* @date   23 December 2014
* @brief  Physics system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemPhysics.h"
#include "core/krbConfig.h"
#include "core/krbClock.h"
#include "core/krbLogger.h"

#include "BtOgre/BtOgreGP.h"
#include "BtOgre/BtOgrePG.h"

#include "Ogre3D/OgreSceneManager.h"
#include "Ogre3D/OgreSceneNode.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

SystemPhysics::SystemPhysics(Config* config, Logger* log)
{
  str_Name  = "Physics";
  m_Config  = config;
  m_Log     = log;
  b_DebugOn = false;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gravity check good!");
}

SystemPhysics::~SystemPhysics()
{
  delete m_BulletDrawer;
  delete m_BulletWorld;

  delete m_Solver;
  delete m_Dispatcher;
  delete m_Broadphase;
  delete m_CollisionConfig;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Don't cry to me, if you fall.");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::init()
{
  parseConfig();

  // BULLET SETUP
  m_Broadphase      = new btDbvtBroadphase();
  m_CollisionConfig = new btDefaultCollisionConfiguration();
  m_Dispatcher      = new btCollisionDispatcher(m_CollisionConfig);
  m_Solver          = new btSequentialImpulseConstraintSolver();

  m_BulletWorld = new btDiscreteDynamicsWorld(
    m_Dispatcher, m_Broadphase, m_Solver, m_CollisionConfig);
  m_BulletWorld->setGravity(btVector3(0, -9.80712f, 0));

/*****************************************************************************/
#ifdef CUSTOM_PHYS_CONF
  // SET SOME SOLVER OPTIONS
  m_SolverInfo = m_BulletWorld->getSolverInfo();
  m_SolverInfo.m_solverMode = SOLVER_USE_WARMSTARTING | SOLVER_SIMD;
  m_SolverInfo.m_numIterations = 8; // LOWER IS FASTER/LESS ACCURATE (DEFAULT: 10)
  //m_SolverInfo.m_splitImpulse = true;
  //m_SolverInfo.m_splitImpulsePenetrationThreshold = -0.03f;
  //m_SolverInfo.m_timeStep = f_PhysicsRate;
  //m_SolverInfo.m_restitution = 0.6f;

  // SET SOME DISPATCHER OPTIONS
  m_DispInfo = m_BulletWorld->getDispatchInfo();
  //m_DispInfo.m_useConvexConservativeDistanceUtil = true;
  //m_DispInfo.m_convexConservativeDistanceThreshold = 0.01;
#endif
/*****************************************************************************/

  // DEBUG DRAWER SETUP  
  m_BulletDrawer = new BtOgre::DebugDrawer(m_WorldNode, m_BulletWorld);
  m_BulletWorld->setDebugDrawer(m_BulletDrawer);
  m_BulletDrawer->setDebugMode(true);

  // CREATE AN INFINITE COLLISION PLANE FOR THE GROUND
  /*
  btStaticPlaneShape* plane_Shape = 
    new btStaticPlaneShape(btVector3(0, 1, 0), 0);

  btRigidBody::btRigidBodyConstructionInfo plane_Properties(
    0, 
    new btDefaultMotionState(), 
    plane_Shape, 
    btVector3(0, 0, 0));

  m_PlaneRB = new btRigidBody(plane_Properties);
  m_PlaneRB->setFriction(5.0f);
  m_PlaneRB->setRestitution(0.f);

  // UNCOMMENT TO ADD INFINITE COLLISION PLANE TO WORLD
  m_BulletWorld->addRigidBody(m_PlaneRB);
  */

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::cycle(float delta, float rate, bool paused)
{
  if (!paused)
  {
    m_BulletWorld->stepSimulation(
      delta, i_PhysicsSteps, f_PhysicsRate * rate);    
  }

  m_BulletWorld->synchronizeMotionStates();

  m_BulletDrawer->step();

  if (b_DebugOn)
  {
    m_BulletWorld->debugDrawWorld();
  }
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::parseConfig()
{
  i_PhysicsSteps  = m_Config->getInt("PHYSICS", "PhysicsSteps");
  f_PhysicsRate   = (1.0f / m_Config->getFloat("PHYSICS", "PhysicsRPS")) / i_PhysicsSteps;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::connectOgre(Ogre::SceneManager* sceneMgr)
{
  m_SceneMgr  = sceneMgr;
  m_WorldNode = m_SceneMgr->getSceneNode("WORLD_NODE");
}

/*****************************************************************************
*****************************************************************************/

void SystemPhysics::toggleDebug()
{
  b_DebugOn = !b_DebugOn;

  if (b_DebugOn)
  {
    m_BulletDrawer->setDebugMode(1);
  }
  else
  {
    m_BulletDrawer->setDebugMode(0);
  }  
}

/*****************************************************************************
*****************************************************************************/

btDynamicsWorld* SystemPhysics::getBulletWorld()
{
  return m_BulletWorld;
}

float SystemPhysics::getPhysicsRate()
{
  return f_PhysicsRate;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/