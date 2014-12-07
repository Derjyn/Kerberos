#pragma once

#ifndef Kerberos_H
#define Kerberos_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : Kerberos.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "INIReader.h"

#include "Gorilla.h"

///////////////////////////////////////////////////////////////////////////////
// CLASS FORWARD DECLARATIONS

namespace Kerberos {
  class Core;
  class Logger;
  class Timer;

  class SystemAudio;
  class SystemGUI;
  class SystemInput;
  class SystemPhysics;
  class SystemRender;
  class SystemScript;
  class SystemWorld;

  class ModuleCamera;
  class ModuleDebug;
}

// KERBEROS INCLUDES
#include "krbCore.h"
#include "krbLogger.h"
#include "krbTimer.h"

#include "systems\krbSystemFactory.h"
#include "systems\krbSystemGUI.h"
#include "systems\krbSystemInput.h"
#include "systems\krbSystemPhysics.h"
#include "systems\krbSystemRender.h"
#include "systems\krbSystemScript.h"
#include "systems\krbSystemWorld.h"

#include "modules\krbModuleFactory.h"
#include "modules\krbModuleCamera.h"
#include "modules\krbModuleDebug.h"

// EOF ////////////////////////////////////////////////////////////////////////

#endif