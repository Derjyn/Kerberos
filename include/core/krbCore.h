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
\file   krbCore.h
\author Nathan Harris
\date   14 December 2014
\brief  The heartbeat of Kerberos
\details
  The core takes care of all the Kerberos systems and low-level functionality
  required to make things run happily.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbCore_h
#define krbCore_h

/*****************************************************************************
*****************************************************************************/

#include "..\KerberosPrereqs.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre
{
  class Root;
  class ResourceGroupManager;
}

namespace Gorilla
{
  class Caption;
  class Layer;
  class MarkupText;
  class Rectangle;
  class Screen;
  class ScreenRenderable;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

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

class EntityCamera;

/*****************************************************************************
*****************************************************************************/

class Core
{
public:
  Core();
  ~Core();

  void start();
  void cycle();
  void stop();

  void toggleDebug();
  void createDemo(); //! \todo Move this out of Core
  void updateDemo(); //! \todo Move this out of Core

private:
  void loadResources();

protected:
  // VARIABLES
  bool                    bActive;

  // TIMER JUNK
  double                  dAccumulator;
  double                  dCounter;
  double                  dDeltaTime;
  double                  dTickRate;
  double                  dLogicRate;
  double                  dNewTime;
  double                  dCurrentTime;
  double                  dTimeLimit;
  unsigned int            iTickCount;

  // CORE THINGS
  Config*                 pConfig;
  Logger*                 pLog;
  Timer*                  pTimer;
  std::string             strVersion;

  // SYSTEMS
  AISystem*               pSysAI;
  GUISystem*              pSysGUI;
  InputSystem*            pSysInput;
  PhysicsSystem*          pSysPhysics;
  RenderSystem*           pSysRender;
  SoundSystem*            pSysSound;
  WorldSystem*            pSysWorld;

  // OGRE BITS
  Ogre::Root* pOgre;
  Ogre::ResourceGroupManager* pResMgr;

  // DEMO STUFF 
  //! \todo Move this out of Core
  Timer*                  pInputTimer;
  int                     iInputDelay;
  Gorilla::ScreenRenderable* pDebugScreen3D;
  Gorilla::Screen*        pDebugScreen;
  Gorilla::Rectangle*     pDebugCaptionBG;
  Gorilla::Rectangle*     pDebugTextBG;
  Gorilla::Layer*         pDebugLayer;
  Gorilla::Caption*       pDebugCaption;
  Gorilla::MarkupText*    pDebugText;
  Gorilla::Layer*         pCursorLayer;
  Gorilla::Rectangle*     pCursorRect;  
  bool                    bCursorActive;
  EntityCamera*           pDemoCam;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbCore_h

/***]EOF[*********************************************************************/