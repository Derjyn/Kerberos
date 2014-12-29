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
* @file   krbEntityPhysicsDynamic.cpp
* @author Nathan Harris
* @date   26 December 2014
* @brief  Dynamic physics entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityPhysicsDynamic.h"
#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"

#include "Ogre3D/OgreEntity.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityPhysicsDynamic::EntityPhysicsDynamic(string name, string mesh, float mass,
    int maxAge, float createTime, Vector3 position)
{
  str_Name      = name;
  f_Age         = 0;
  i_MaxAge      = maxAge;
  f_CreateTime  = createTime;
  f_MassKg      = mass;
  ent_Position  = position;
  m_SceneMgr    = SystemRender::getSingletonPtr()->getSceneManager();
  m_PhysWorld   = SystemPhysics::getSingletonPtr()->getPhysWorld();

  // CREATE MESH
  m_SceneMgr->createEntity(str_Name, mesh);

  // ATTACH TO NODE
  m_SceneMgr->getRootSceneNode()->createChildSceneNode(
    "NODE_" + str_Name, toOgre(ent_Position));
  m_SceneMgr->getSceneNode("NODE_" + str_Name)->attachObject
    (m_SceneMgr->getEntity(str_Name));

  // CREATE RIGID BODY STATE
  ent_State = new BtOgre::RigidBodyState(
    m_SceneMgr->getSceneNode("NODE_" + str_Name));

  // CONVERT TO BULLET CONVEX SHAPE
  BtOgre::StaticMeshToShapeConverter converter(
    m_SceneMgr->getEntity(str_Name));
  ent_HullConvex = converter.createConvex();

  // CALCULATE INERTIA
  btVector3 vec_Intertia;
  ent_HullConvex->calculateLocalInertia(f_MassKg, vec_Intertia);

  // CREATE BULLET RIGID BODY AND ADD TO WORLD
  ent_Body = new btRigidBody(f_MassKg, ent_State, ent_HullConvex, vec_Intertia);
  ent_Body->setFriction(Ogre::Math::RangeRandom(0.52f, 0.54f));
  ent_Body->setRestitution(Ogre::Math::RangeRandom(0.26f, 0.27f));
  m_PhysWorld->addRigidBody(ent_Body);
}

/*****************************************************************************
*****************************************************************************/

EntityPhysicsDynamic::~EntityPhysicsDynamic()
{
  m_PhysWorld->removeRigidBody(ent_Body);
  delete ent_Body;
  delete ent_HullConvex;
  delete ent_State;

  ent_Node->detachAllObjects();
  delete ent_Node;
  delete ent_Mesh;
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/