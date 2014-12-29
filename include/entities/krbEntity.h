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
* @file   krbEntity.h
* @author Nathan Harris
* @date   25 December 2014
* @brief  Base class for entities
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntity_h
#define krbEntity_h

/*****************************************************************************
*****************************************************************************/

#include "utility/krbConverter.h"
#include "utility/krbMath.h"

#include "Ogre3D/OgreEuler.h"
#include "Ogre3D/OgreSceneManager.h"
#include "Ogre3D/OgreSceneNode.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Base class for entities
//
class Entity
{
public:
  virtual ~Entity() = 0;

  virtual void position(float x, float y, float z)
  {
     ent_Node->setPosition(x, y, z);
  }

  virtual void lookAt(float x, float y, float z)
  {
    ent_Euler.direction(Ogre::Vector3(x, y, z) - ent_Node->getPosition());
    ent_Node->setOrientation(ent_Euler);
  }

  virtual void lookAt(Ogre::Vector3 target)
  {
    ent_Euler.direction(target - ent_Node->getPosition());
    ent_Node->setOrientation(ent_Euler);
  }

  virtual void orient(int pitch, int yaw, float factor)
  {
    ent_Euler.yaw(Ogre::Radian(-yaw * factor));
    ent_Euler.pitch(Ogre::Radian(-pitch * factor));
    ent_Euler.setRoll(Ogre::Degree(0));
    ent_Node->setOrientation(ent_Euler);
  }

  virtual void moveAbscissa(float speed)
  {
    f_Speed = speed;
    ent_Node->translate(ent_Euler.forward() * speed);
  }

  virtual void moveApplicate(float speed)
  {
    f_Speed = speed;
    ent_Node->translate(ent_Euler.left() * speed);
  }

  virtual void moveOrdinate(float speed)
  {
    f_Speed = speed;
    ent_Node->translate(ent_Euler.up() * speed);
  }

  // SETTERS //////////////////////////////////////////////////////////////////

  virtual void setMaxAge(int age)
  {
    i_MaxAge = age;
  }

  virtual void setTimeScale(float scale)
  {
    f_TimeScale = scale;
  }

  // GETTERS //////////////////////////////////////////////////////////////////

  inline string getName() 
  { 
    return str_Name; 
  }

  inline float getAge(float currTime) 
  { 
    f_Age = currTime - f_CreateTime;
    return f_Age; 
  }

  inline int getMaxAge() 
  { 
    return i_MaxAge; 
  }

  inline Ogre::Euler getEuler() 
  { 
    return ent_Euler; 
  }

  inline Vector3 getPosition()
  {
    ent_Position = Vector3(
      ent_Node->getPosition().x,
      ent_Node->getPosition().y,
      ent_Node->getPosition().z);

    return ent_Position;
  }

protected:
  string                  str_Name;
  float                   f_Age;
  float                   f_CreateTime;
  unsigned int            i_MaxAge;
  float                   f_Speed;
  float                   f_TimeScale;

  Ogre::SceneManager*     m_SceneMgr;
  Ogre::SceneNode*        m_WorldNode;
  Ogre::SceneNode*        ent_Node;
  Ogre::Euler             ent_Euler;
  Vector3                 ent_Position;
};

inline Entity::~Entity() {}

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntity_h

/***]EOF[*********************************************************************/