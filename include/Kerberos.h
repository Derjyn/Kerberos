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
* @date   13 December 2014
* @brief  Wrangles up Kerberos for consumption
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef Kerberos_h
#define Kerberos_h

/*****************************************************************************
*****************************************************************************/

#include "KerberosPrereqs.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{
  class Core;
  class Config;
  class Logger;
  class Timer;

  class AISystem;
  class GUISystem;
  class InputSystem;
  class PhysicsSystem;
  class RenderSystem;
  class SoundSystem;
  class WorldSystem;
}

/*****************************************************************************
*****************************************************************************/

#include "core\krbCore.h"
#include "core\krbConfig.h"
#include "core\krbLogger.h"
#include "core\krbTimer.h"

#include "systems\ai\krbAISystem.h"
#include "systems\gui\krbGUISystem.h"
#include "systems\input\krbInputSystem.h"
#include "systems\physics\krbPhysicsSystem.h"
#include "systems\render\krbRenderSystem.h"
#include "systems\sound\krbSoundSystem.h"
#include "systems\world\krbWorldSystem.h"

/*****************************************************************************
*****************************************************************************/

#endif // Kerberos_h

/***]EOF[*********************************************************************/