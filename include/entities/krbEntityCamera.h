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
\file   krbEntityCamera.h
\author Nathan Harris
\date   14 December 2014
\brief  A camera entity. Duh.
\details
  Need to write some stuff. Me so lazy.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityCamera_h
#define krbEntityCamera_h

/*****************************************************************************
*****************************************************************************/

#include "krbEntity.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre
{
  class Camera;
  class Euler;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class EntityCamera : public Entity
{
public:
  EntityCamera(std::string name, Ogre::SceneManager* sceneMgr, 
    Ogre::Viewport* vp, bool pitchLim);
  ~EntityCamera();

  void update();

  void setActive(Ogre::Viewport* vp);
  void setActive(Ogre::Viewport* vp, bool autoAR);

  void orientCamera(int pitch, int yaw, float factor);

  void lookAt(Vector3 target);
  void lookAt(float x, float y, float z);

  void positionCamera(Vector3 pos);
  void positionCamera(float x, float y, float z);

  void moveCamAbscissa(float speed);
  void moveCamOrdinate(float speed);
  void moveCamApplicate(float speed);

  Ogre::Camera* getOgreCam();

protected:
  bool                  bPitchLimit;
  Ogre::Camera*         pOgreCam;
  Ogre::Viewport*       pOgreVP;
  Ogre::Euler*          pCamEuler;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbEntityCamera_h

/***]EOF[*********************************************************************/