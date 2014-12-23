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
* @file   krbEntityPhysicsStatic.cpp
* @author Nathan Harris
* @date   22 December 2014
* @brief  Static physics entity. Good for solid scene meshes.
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityPhysicsStatic.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityPhysicsStatic::EntityPhysicsStatic(string name, string mesh,
    int maxAge, float createTime, Vector3 position,
    Ogre::SceneManager* sceneMgr, btDynamicsWorld* world)
{
  str_Name      = name;
  f_Age         = 0;
  i_MaxAge      = maxAge;
  f_CreateTime  = createTime;
  f_MassKg      = 0;
  ent_Position  = position;
  m_SceneMgr    = sceneMgr;
  m_BulletWorld = world;

  // Create Ogre entity.
  ent_Mesh = m_SceneMgr->createEntity(str_Name, mesh);

  // Convert to shape (and set some options).
  BtOgre::StaticMeshToShapeConverter converter(ent_Mesh);
  ent_ShapeTrimesh = converter.createTrimesh();

  // Calculate intertia. Need to experiment with this.
  btVector3 inertia;
  ent_ShapeTrimesh->calculateLocalInertia(f_MassKg, inertia);

  // Create node and attach mesh.
  ent_Node = m_SceneMgr->getRootSceneNode()->createChildSceneNode(
    "NODE_" + str_Name, toOgre(ent_Position));
  ent_Node->attachObject(ent_Mesh);

  // Connect Ogre node to Bullet.
  ent_State = new BtOgre::RigidBodyState(ent_Node);

  // Create rigid body and add it to the physics world.
  ent_Body = new btRigidBody(f_MassKg, ent_State, ent_ShapeTrimesh, inertia);  
  m_BulletWorld->addRigidBody(ent_Body);
}

/*****************************************************************************
*****************************************************************************/

EntityPhysicsStatic::~EntityPhysicsStatic()
{
  m_BulletWorld->removeRigidBody(ent_Body);
  delete ent_Body;
  delete ent_ShapeTrimesh;
  delete ent_State;

  ent_Node->detachAllObjects();
  delete ent_Mesh;
  delete ent_Node;
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/