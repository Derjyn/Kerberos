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
* @file   krbEntityLight.h
* @author Nathan Harris
* @date   22 December 2014
* @brief  Light entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityLight_h
#define krbEntityLight_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntity.h"
#include "utility/krbMath.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre
{
  class Light;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Light entity
//
class EntityLight : public Entity
{
public:
  typedef enum
  {
    LT_POINT,
    LT_SPOT,
    LT_DIR
  } LightType;

  EntityLight(string name, LightType type, Ogre::SceneManager* scenemgr);
  ~EntityLight();

  void setColor(Color diffuse);
  void setColor(Color diffuse, Color specular);
  void setAttenuation(float range);
  void setDirection(Vector3 direction);
  void setDirection(float x, float y, float z);

protected:
  Ogre::Light*       m_Light;
  LightType          lt_Type;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityLight_h

/***]EOF[*********************************************************************/