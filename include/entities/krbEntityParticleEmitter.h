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
* @file   krbEntityParticleEmitter.h
* @author Nathan Harris
* @date   26 December 2014
* @brief  Particle emitter entity
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbEntityParticleEmitter_h
#define krbEntityParticleEmitter_h

/*****************************************************************************
*****************************************************************************/

#include "entities/krbEntity.h"

/*****************************************************************************
*****************************************************************************/

namespace ParticleUniverse
{
  class ParticleSystem;
  class ParticleSystemManager;
}

namespace NxOgre
{
  class Scene;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief Particle emitter entity
//
class EntityParticleEmitter : public Entity
{
public:
  EntityParticleEmitter(string name, Ogre::SceneManager* scenemgr);
  ~EntityParticleEmitter();

  void start();
  void stop();
  void togglePause();

  void setTimeScale(float scale);

  ParticleUniverse::ParticleSystem* getPUSystem();

protected:
  ParticleUniverse::ParticleSystemManager*  m_PUSysMgr;
  ParticleUniverse::ParticleSystem*         m_PUSystem;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbEntityParticleEmitter_h

/***]EOF[*********************************************************************/