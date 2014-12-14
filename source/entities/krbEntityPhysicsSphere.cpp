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

#include "entities\krbEntityPhysicsSphere.h"

#include <malloc.h>

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityPhysicsSphere::EntityPhysicsSphere(
  std::string name, int state, Ogre::Vector3 position,
  float radius, float mass, float friction, float restitution,
  float linDamp, float rotDamp, float rollFrict, 
  btDynamicsWorld* bulletWorld, Ogre::SceneManager* sceneMgr)
{
  strName       = "ENT_PHYS_SPHERE_" + name;
  pBulletWorld  = bulletWorld;
  pSceneMgr     = sceneMgr;

  // CREATE SCENE NODE AND SET POSITION
  pNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(
    "NODE_" + strName);
  pNode->setPosition(position.x, position.y, position.z);

  // CREATE THE SPHERE SHAPE
  objShape = new btSphereShape(radius);
  btVector3 inertia(0, 0, 0);
  objShape->calculateLocalInertia(mass, inertia);

  // CREATE A RIGID BODY STATE
  objState = new BtOgre::RigidBodyState(pNode);

  // CONSTRUCT RIGID BODY
  btRigidBody::btRigidBodyConstructionInfo objRBCI(
    mass, objState, objShape, inertia);
  objBody = new btRigidBody(objRBCI);

  // SET SOME OPTIONS  
  objBody->setFriction(friction);
  objBody->setRestitution(restitution);
  objBody->setDamping(linDamp, rotDamp);
  objBody->setActivationState(state);
  objBody->setRollingFriction(rollFrict);

  // ADD IT TO THE WORLD
  pBulletWorld->addRigidBody(objBody);
}

EntityPhysicsSphere::~EntityPhysicsSphere()
{
  // \bug Issue when World system cleans up entities...
  pBulletWorld->removeRigidBody(objBody);
  delete objBody->getMotionState();
  delete objBody;
  delete objShape;
}

/*****************************************************************************
*****************************************************************************/

void EntityPhysicsSphere::update()
{
}

/*****************************************************************************
*****************************************************************************/

btSphereShape* EntityPhysicsSphere::getShape()
{
  return objShape;
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/