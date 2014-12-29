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
* @file   krbEntityCamera.cpp
* @author Nathan Harris
* @date   21 December 2014
* @brief  Camera entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityCamera.h"

#include "Ogre3D/OgreCamera.h"
#include "Ogre3D/OgreViewport.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityCamera::EntityCamera(string name, Ogre::SceneManager* scenemgr)
{
  str_Name    = name;
  m_SceneMgr  = scenemgr;
  m_WorldNode = m_SceneMgr->getRootSceneNode();

  m_Camera = m_SceneMgr->createCamera(name);
  m_Camera->setAutoAspectRatio(true);
  m_Camera->setNearClipDistance(0.1f);

  ent_Node = m_WorldNode->createChildSceneNode("NODE_" + str_Name);
  ent_Node->attachObject(m_Camera);
  ent_Node->setOrientation(ent_Euler);

  f_Speed = 0;
}

EntityCamera::~EntityCamera()
{
}

/*****************************************************************************
*****************************************************************************/

void EntityCamera::activate(Ogre::Viewport* viewport)
{
  m_Viewport = viewport;
  m_Viewport->setCamera(m_Camera);
}

/*****************************************************************************
*****************************************************************************/

Vector3 EntityCamera::getPosition()
{
  return Vector3(
    ent_Node->getPosition().x,
    ent_Node->getPosition().y,
    ent_Node->getPosition().z);
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/