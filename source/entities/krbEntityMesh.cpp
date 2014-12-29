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
* @file   krbEntityMesh.cpp
* @author Nathan Harris
* @date   21 December 2014
* @brief  Mesh entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityMesh.h"

#include "Ogre3D/OgreEntity.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityMesh::EntityMesh(string name, string mesh, float scale, 
  Ogre::SceneManager* scenemgr)
{
  str_Name    = name;
  m_SceneMgr  = scenemgr;
  m_WorldNode = m_SceneMgr->getRootSceneNode();

  ent_Mesh = m_SceneMgr->createEntity(name, mesh);

  ent_Node = m_WorldNode->createChildSceneNode("NODE_" + str_Name);
  ent_Node->attachObject(ent_Mesh);
  ent_Node->scale(scale, scale, scale);
  ent_Node->setOrientation(ent_Euler);

  f_Speed = 0;
}

EntityMesh::~EntityMesh()
{
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/