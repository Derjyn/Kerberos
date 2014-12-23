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
* @file   krbBrain.h
* @author Nathan Harris
* @date   23 December 2014
*
* @details 
*  Brain is the central core of Kerberos responsible for overseeing all the 
*  systems that build up the engine. The main loop, timing, and general
*  wizardry is handled by Brain.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbBrain_h
#define krbBrain_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"
#include "utility/krbMath.h"

#include "Ogre3D/OgreRectangle2D.h"
#include "Ogre3D/OgreTextureManager.h"

#include <map>
#include <vector>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace FMOD
{
  class Channel;
  class Sound;
}

namespace Gorilla
{
  class Caption;
  class Layer;
  class MarkupText;
  class Rectangle;
  class Screen;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

class Clock;
class Config;
class Logger;

class SystemAI;
class SystemGUI;
class SystemInput;
class SystemNetwork;
class SystemPhysics;
class SystemRender;
class SystemScript;
class SystemSound;
class SystemWorld;

class EntityCamera;
class EntityLight;
class EntityMesh;
class EntityPhysicsDynamic;
class EntityPhysicsStatic;

/*****************************************************************************
*****************************************************************************/

//
//! \brief The central nervous system of Kerberos
//
class Brain
{
public:
  Brain();
  ~Brain();

  void init();
  void cycle();
  void halt();

  string          getVersion()    { return str_Version; }
  Clock*          getClock()      { return m_Clock; }
  Config*         getConfig()     { return m_Config; }
  Logger*         getLogger()     { return m_Log; }

  SystemAI*       getSysAI()      { return m_SysAI; }
  SystemGUI*      getSysGUI()     { return m_SysGUI; }
  SystemInput*    getSysInput()   { return m_SysInput; }
  SystemNetwork*  getSysNetwork() { return m_SysNetwork; }
  SystemPhysics*  getSysPhysics() { return m_SysPhysics; }
  SystemRender*   getSysRender()  { return m_SysRender; }
  SystemScript*   getSysScript()  { return m_SysScript; }
  SystemSound*    getSysSound()   { return m_SysSound; }
  SystemWorld*    getSysWorld()   { return m_SysWorld; }

protected:
  Clock*          m_Clock;
  Config*         m_Config;
  Logger*         m_Log;

  SystemAI*       m_SysAI;
  SystemGUI*      m_SysGUI;
  SystemInput*    m_SysInput;
  SystemNetwork*  m_SysNetwork;
  SystemPhysics*  m_SysPhysics;
  SystemRender*   m_SysRender;
  SystemScript*   m_SysScript;
  SystemSound*    m_SysSound;
  SystemWorld*    m_SysWorld;

  bool            b_Alive;
  string          str_Version;
  string          str_LogFile;  

private:
  void parseConfig();
  void addSystems();
  void initSystems();
  void haltSystems();
  void destroySystems();

  // TIMER JUNK
  double d_Accumulator;
  double d_Counter;
  double d_DeltaTime;
  double d_LogicRate;
  double d_CurrentTime;
  double d_NewTime;
  double d_TickCount;

  vector<System*> vec_Sys;
  map<string, System*> map_Sys;

  // THIS'LL BE SCRIPT BASED OR SOME SUCH... DOESN'T BELONG IN THE BRAIN
  void createLab();
  void cycleLab();
  void handleLabInput();
  void updateDebug();

  float           f_DemoTime;
  float           f_WorldRateTemp;
  float           f_InputDelay;   
  unsigned int    i_ScreenShots;

  // LAB LEVEL AND ACTION
  Color           clr_LabEnv;
  Vector3         vec_LabFog;
  EntityCamera*   m_LabCamera;
  float           f_CamSpeed;
  EntityLight*    m_LabLight;

  // HUD
  Gorilla::Screen*      m_Screen;
  Gorilla::Layer*       m_Layer;
  Gorilla::Caption*     m_Caption;
  Gorilla::Rectangle*   m_CaptionBG;
  Gorilla::MarkupText*  m_DebugText;
  Gorilla::Rectangle*   m_DebugBG;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbBrain_h

/***]EOF[*********************************************************************/