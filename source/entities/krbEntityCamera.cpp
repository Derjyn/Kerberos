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

#include "entities\krbEntityCamera.h"

#include "Ogre3D\OgreCamera.h"
#include "Ogre3D\OgreEuler.h"
#include "Ogre3D\OgreViewport.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

EntityCamera::EntityCamera(std::string name, Ogre::SceneManager* sceneMgr, 
  Ogre::Viewport* vp, bool pitchLim)
{
  strName     = name;
  pSceneMgr   = sceneMgr;
  pOgreVP     = vp;
  bPitchLimit = pitchLim;

  pOgreCam = pSceneMgr->createCamera(strName);
  pOgreCam->setNearClipDistance(0.01f);
  pOgreCam->setAutoAspectRatio(true);

  pNode = pSceneMgr->getRootSceneNode()->createChildSceneNode(
    "NODE_" + strName);
  pNode->attachObject(pOgreCam);

  pCamEuler = new Ogre::Euler();  
}

EntityCamera::~EntityCamera()
{
  pNode->detachAllObjects();

  delete pOgreCam;
  delete pNode;
}

/*****************************************************************************
*****************************************************************************/

void EntityCamera::update()
{
}

/*****************************************************************************
*****************************************************************************/

void EntityCamera::orientCamera(int pitch, int yaw, float factor)
{
  pCamEuler->normalise();

  if (bPitchLimit)
  {
    pCamEuler->limitPitch(Ogre::Degree(85));
  }

  pCamEuler->pitch(Ogre::Radian(-pitch * factor));
  pCamEuler->yaw(Ogre::Radian(-yaw * factor));
  pCamEuler->setRoll(Ogre::Degree(0));

  pNode->setOrientation(pCamEuler->toQuaternion());
}

void EntityCamera::positionCamera(Vector3 pos)
{
  pNode->setPosition(toOgre(pos));
}
void EntityCamera::positionCamera(float x, float y, float z)
{
  pNode->setPosition(x, y, z);
}
void EntityCamera::moveCamAbscissa(float speed)
{
  pNode->setPosition(
    pNode->getPosition() + (pCamEuler->forward() * speed));
}
void EntityCamera::moveCamOrdinate(float speed)
{
  pNode->setPosition(
    pNode->getPosition() + (pCamEuler->up() * speed));
}
void EntityCamera::moveCamApplicate(float speed)
{
  pNode->setPosition(
    pNode->getPosition() + (pCamEuler->left() * speed));
}

/*****************************************************************************
*****************************************************************************/

void EntityCamera::lookAt(Vector3 target)
{
  pCamEuler->normalise();

  pCamEuler->direction(toOgre(target) - pNode->getPosition());
  pCamEuler->setRoll(Ogre::Degree(0));
  pNode->setOrientation(pCamEuler->toQuaternion());
}

void EntityCamera::lookAt(float x, float y, float z)
{
  pCamEuler->normalise();

  pCamEuler->direction(Ogre::Vector3(x, y, z) - pNode->getPosition());
  pNode->setOrientation(pCamEuler->toQuaternion());
}

/*****************************************************************************
*****************************************************************************/

void EntityCamera::setActive(Ogre::Viewport* vp)
{
  vp->setCamera(pOgreCam);
  pOgreCam->setAutoAspectRatio(true);
}

void EntityCamera::setActive(Ogre::Viewport* vp, bool autoAR)
{
  vp->setCamera(pOgreCam);
  pOgreCam->setAutoAspectRatio(autoAR);
}

/*****************************************************************************
*****************************************************************************/

Ogre::Camera* EntityCamera::getOgreCam()
{
  return pOgreCam;
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/