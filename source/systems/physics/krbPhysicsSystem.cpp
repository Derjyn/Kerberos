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

#include "systems\physics\krbPhysicsSystem.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

PhysicsSystem::PhysicsSystem(Config* config, Logger* log, Timer* timer,
  Ogre::SceneManager* sceneMgr)
{
  setName("Physics system");

  pConfig = config;
  pLog = log;
  pTimer = timer;
  pSceneMgr = sceneMgr;
  bDebugOn = false;

  logCreation();
}

//\todo More cleanup stuff
PhysicsSystem::~PhysicsSystem()
{
  delete pBulletDrawer;
  delete pBulletWorld;

  delete pSolver;
  delete pDispatcher;
  delete pBroadphase;
  delete pCollisionConfig;

  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void PhysicsSystem::start()
{
  // BULLET SETUP
  pCollisionConfig = new btDefaultCollisionConfiguration();
  pDispatcher = new btCollisionDispatcher(pCollisionConfig);
  pBroadphase = new btDbvtBroadphase();

  pSolver = new btSequentialImpulseConstraintSolver();

  pBulletWorld = new btDiscreteDynamicsWorld(
    pDispatcher, pBroadphase, pSolver, pCollisionConfig);

  // SET SOME BULLET WORLD OPTIONS
  pBulletWorld->getSolverInfo().m_solverMode = 
    SOLVER_USE_WARMSTARTING | SOLVER_SIMD;
  pBulletWorld->setGravity(btVector3(0, -9.80712, 0));

  // DEBUG DRAWER SETUP
  pBulletDrawer = new BtOgre::DebugDrawer(
    pSceneMgr->getRootSceneNode(), pBulletWorld);
  pBulletWorld->setDebugDrawer(pBulletDrawer);
  pBulletDrawer->setDebugMode(false);

  // CREATE AN INFINITE COLLISION PLANE FOR THE GROUND
  pBulletWorld->addRigidBody(new btRigidBody(
    btRigidBody::btRigidBodyConstructionInfo(0,
    new btDefaultMotionState(),
    new btStaticPlaneShape(btVector3(0, 1, 0), 0))));

  logStart();
}

void PhysicsSystem::cycle(double delta, double rate)
{
  pBulletWorld->stepSimulation(delta, 5, rate);
  pBulletWorld->synchronizeMotionStates();  
  pBulletDrawer->step();

  if (bDebugOn)
  {    
    pBulletWorld->debugDrawWorld();
  }  
}

void PhysicsSystem::stop()
{
  logStop();
}

/*****************************************************************************
*****************************************************************************/

void PhysicsSystem::toggleDebug()
{
  bDebugOn = !bDebugOn;

  if (bDebugOn)
  {
    pBulletDrawer->setDebugMode(1);
  }
  else
  {
    pBulletDrawer->setDebugMode(0);
  }
  
}

/*****************************************************************************
*****************************************************************************/

btDynamicsWorld* PhysicsSystem::getBulletWorld()
{
  return pBulletWorld;
}

/*****************************************************************************
*****************************************************************************/

}       // namepsace Kerberos

/***]EOF[*********************************************************************/