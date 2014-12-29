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
* @file   Kerberos.h
* @author Nathan Harris
* @date   28 December 2014
* @brief  Wrangles up Kerberos for consumption
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef Kerberos_h
#define Kerberos_h

/*****************************************************************************
*****************************************************************************/

#include <string>
#include <sstream>
using namespace std;

/*****************************************************************************
*****************************************************************************/

#define KRB_VERSION_MAJOR 0
#define KRB_VERSION_MINOR 0
#define KRB_VERSION_PATCH 1
#define KRB_VERSION_ALPHA 5
#define KRB_VERSION_NAME "Conceptus"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{
  class Brain;
  class Config;
  class Logger;
  class Timer;

  class System;
  class SystemAI;
  class SystemGUI;
  class SystemInput;
  class SystemNetwork;
  class SystemPhysics;
  class SystemRender;
  class SystemScript;
  class SystemSound;
  class SystemWorld;

  class Entity;
  class EntityCamera;
  class EntityLight;
  class EntityMesh;
  class EntityParticleEmitter;
  class EntityPhysicsDynamic;
  class EntityPhysicsStatic;

  class GUI;

  inline string getVersionString()
  {
    stringstream ss_ver;
    ss_ver << 
    KRB_VERSION_MAJOR << "." <<
    KRB_VERSION_MINOR << "." <<
    KRB_VERSION_PATCH << "." <<
    KRB_VERSION_ALPHA << " (" << KRB_VERSION_NAME ")";
    return ss_ver.str();
  }
}

/*****************************************************************************
*****************************************************************************/

#include "core/krbBrain.h"
#include "core/krbClock.h"
#include "core/krbConfig.h"
#include "core/krbLogger.h"

#include "systems/krbSystem.h"
#include "systems/krbSystemAI.h"
#include "systems/krbSystemGUI.h"
#include "systems/krbSystemInput.h"
#include "systems/krbSystemNetwork.h"
#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"
#include "systems/krbSystemScript.h"
#include "systems/krbSystemSound.h"
#include "systems/krbSystemWorld.h"

#include "entities/krbEntity.h"
#include "entities/krbEntityCamera.h"
#include "entities/krbEntityLight.h"
#include "entities/krbEntityMesh.h"
#include "entities/krbEntityParticleEmitter.h"
#include "entities/krbEntityPhysics.h"
#include "entities/krbEntityPhysicsDynamic.h"
#include "entities/krbEntityPhysicsStatic.h"

#include "utility/krbConverter.h"
#include "utility/krbMath.h"
#include "utility/krbUtility.h"

/*****************************************************************************
*****************************************************************************/

#endif // Kerberos_h

/***]EOF[*********************************************************************/