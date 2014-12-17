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
* @date   17 December 2014
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

#include <sstream>
#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

#define KRB_CONSOLE

#define KRB_VERSION_MAJOR 0
#define KRB_VERSION_MINOR 0
#define KRB_VERSION_PATCH 0
#define KRB_VERSION_ALPHA 4
#define KRB_VERSION_NAME "Conceptus"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{
  class Brain;
  class Config;
  class Logger;
  class Timer;

  class SystemAI;
  class SystemInput;
  class SystemNetwork;
  class SystemPhysics;
  class SystemRender;
  class SystemScript;
  class SystemSound;
  class SystemWorld;
}

/*****************************************************************************
*****************************************************************************/

#include "core/krbBrain.h"
#include "core/krbClock.h"
#include "core/krbConfig.h"
#include "core/krbLogger.h"

#include "systems/krbSystemAI.h"
#include "systems/krbSystemInput.h"
#include "systems/krbSystemNetwork.h"
#include "systems/krbSystemPhysics.h"
#include "systems/krbSystemRender.h"
#include "systems/krbSystemScript.h"
#include "systems/krbSystemSound.h"
#include "systems/krbSystemWorld.h"

#include "utility/krbConverter.h"
#include "utility/krbMath.h"
#include "utility/krbUtility.h"

/*****************************************************************************
*****************************************************************************/

#endif // Kerberos_h

/***]EOF[*********************************************************************/