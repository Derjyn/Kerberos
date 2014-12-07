#pragma once

#ifndef krbModuleDebug_H
#define krbModuleDebug_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModuleDebug.h
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbModule.h"

///////////////////////////////////////////////////////////////////////////////

namespace Gorilla {
  class Caption;
  class Layer;
  class Rectangle;
  class Screen;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

class Timer;

class SystemGUI;
class SystemRender;
class SystemWorld;

class ModuleCamera;

///////////////////////////////////////////////////////////////////////////////

class ModuleDebug : public Module, public Ogre::Singleton<ModuleDebug> {
public:
  ModuleDebug();
  static ModuleDebug &singleton(void);
  static ModuleDebug *singletonPtr(void);

  void createDebugGUI(void);
  void toggleDebugGUI(void);
  void fadeDebugGUI(void);

  bool isDebugOn(void) { return bDebugToggle; }

private:
  friend class ModuleFactory;

  bool bDebugToggle;
  float fAlphaMod;
  float fFadeDelta;
  double dCurrTime;

protected:
  void init(void);
  void update(void);
  void halt(void);

  Timer *pWorldTimer;

  SystemGUI *pSysGUI;
  SystemRender *pSysRender;
  SystemWorld *pSysWorld;

  ModuleCamera *pModCamera;

  // DEBUG GUI
  Gorilla::Screen *pDebugScreen;
  Gorilla::Layer *pDebugLayerHeader;
  Gorilla::Caption *pDebugCaptionTitle;
  Gorilla::Caption *pDebugCaptionCoreTime;
  Gorilla::Caption *pDebugCaptionWorldTime;
  Gorilla::Caption *pDebugCaptionWorldRPS;
  Gorilla::Caption *pDebugCaptionTickCount;
  Gorilla::Caption *pDebugCaptionTickRate;
  Gorilla::Caption *pDebugCaptionAvgFPS;
  Gorilla::Caption *pDebugCaptionCurFPS;
  Gorilla::Caption *pDebugCaptionBatchCount;
  Gorilla::Caption *pDebugCaptionActiveCamera;
};

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////

#endif