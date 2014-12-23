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
* @file   krbEntityCamera.h
* @author Nathan Harris
* @date   21 December 2014
* @brief  Camera entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityCamera_h
#define krbEntityCamera_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntity.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre
{
  class Camera;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Camera entity
//
class EntityCamera : public Entity
{
public:
  EntityCamera(string name, Ogre::SceneManager* scenemgr);
  ~EntityCamera();

  void activate(Ogre::Viewport* viewport);

  Ogre::Camera* getOgreCam() { return m_Camera; }
  Vector3 getPosition();

protected:
  Ogre::Camera*       m_Camera;
  Ogre::Viewport*     m_Viewport;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityCamera_h

/***]EOF[*********************************************************************/