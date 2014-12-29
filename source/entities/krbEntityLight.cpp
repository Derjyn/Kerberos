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
* @file   krbEntityLight.cpp
* @author Nathan Harris
* @date   22 December 2014
* @brief  Camera entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntityLight.h"

#include "Ogre3D/OgreCamera.h"
#include "Ogre3D/OgreViewport.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityLight::EntityLight(string name, LightType type, 
  Ogre::SceneManager* scenemgr)
{
  str_Name    = name;
  m_SceneMgr  = scenemgr;
  m_WorldNode = m_SceneMgr->getRootSceneNode();

  // CREATE LIGHT
  m_Light = m_SceneMgr->createLight(name);
  switch (type)
  {
    case(EntityLight::LightType::LT_POINT) :
      m_Light->setType(Ogre::Light::LT_POINT);
      lt_Type = LightType::LT_POINT;
      break;
    case(EntityLight::LightType::LT_SPOT) :
      m_Light->setType(Ogre::Light::LT_SPOTLIGHT);
      lt_Type = LightType::LT_SPOT;
      break;
    case(EntityLight::LightType::LT_DIR) :
      m_Light->setType(Ogre::Light::LT_DIRECTIONAL);
      lt_Type = LightType::LT_DIR;
      break;
  }

  ent_Node = m_WorldNode->createChildSceneNode("NODE_" + str_Name);
  ent_Node->attachObject(m_Light);
  ent_Node->setOrientation(ent_Euler);

  f_Speed = 0;
}

EntityLight::~EntityLight()
{
}

/*****************************************************************************
*****************************************************************************/

void EntityLight::setColor(Color diffuse)
{
  m_Light->setDiffuseColour(
    Ogre::ColourValue(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

  m_Light->setSpecularColour(Ogre::ColourValue(0,0,0,0));
}
void EntityLight::setColor(Color diffuse, Color specular)
{
  m_Light->setDiffuseColour(
    Ogre::ColourValue(diffuse.r, diffuse.g, diffuse.b, diffuse.a));

  m_Light->setSpecularColour(
    Ogre::ColourValue(specular.r, specular.g, specular.b, specular.a));
}

void EntityLight::setAttenuation(float range)
{
  if (lt_Type == LightType::LT_POINT)
  {
    m_Light->setAttenuation(
      range, 1.0f, 4.5f / range, 75.0f / (range * range));
  }
}

void EntityLight::setDirection(Vector3 direction)
{
  if (lt_Type == LightType::LT_DIR || lt_Type == LightType::LT_SPOT)
  {
    m_Light->setDirection(toOgre(direction));
  }
}
void EntityLight::setDirection(float x, float y, float z)
{
  if (lt_Type == LightType::LT_DIR || lt_Type == LightType::LT_SPOT)
  {
    m_Light->setDirection(Ogre::Vector3(x,y,z));
  }
}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos

/***]EOF[*********************************************************************/