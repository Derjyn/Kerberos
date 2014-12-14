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
\file   krbPhysicsSystem.h
\author Nathan Harris
\date   13 December 2014
\brief  Makes things go clunk and boom and stuff!
\details
  The physics system utilizes Bullet. Much work to do to really make this
  shine. Currently using BtOgre as an interface from Bullet -> Ogre, but
  this may change...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbPhysicsSystem_h
#define krbPhysicsSystem_h

/*****************************************************************************
*****************************************************************************/

#include "..\krbSystem.h"

#include "Ogre3D\OgreSceneManager.h"

#include "BtOgre\BtOgreGP.h"
#include "BtOgre\BtOgrePG.h"

#include "Bullet\BulletCollision\CollisionDispatch\btGhostObject.h"
#include "Bullet\LinearMath\btAlignedObjectArray.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class PhysicsSystem final : public System
{
public:
  PhysicsSystem(Config* config, Logger* log, Timer* timer, 
    Ogre::SceneManager* sceneMgr);
  ~PhysicsSystem();

  void start(void);
  void cycle(double delta, double rate);
  void stop(void);

  void toggleDebug();

  btDynamicsWorld* getBulletWorld();

protected:
  bool bDebugOn;

  Ogre::SceneManager* pSceneMgr;
  btDynamicsWorld* pBulletWorld;
  BtOgre::DebugDrawer* pBulletDrawer;

  btBroadphaseInterface* pBroadphase;
  btDefaultCollisionConfiguration* pCollisionConfig;
  btCollisionDispatcher* pDispatcher;
  btSequentialImpulseConstraintSolver* pSolver;
  btAlignedObjectArray<btCollisionShape*> collisionShapes;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbPhysicsSystem_h

/***]EOF[*********************************************************************/