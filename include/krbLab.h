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
* @file   krbLab.h
* @author Nathan Harris
* @date   28 December 2014
* @brief  Kerberos test-lab
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbLab_h
#define krbLab_h

/*****************************************************************************
*****************************************************************************/

#include "Kerberos.h"

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

namespace ParticleUniverse
{
  class ParticleSystem;
  class PhysicsActor;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class Lab
{
public:
  Lab(Config* config, Clock* brainClock);
  ~Lab();

  void init();
  void cycle(float delta);
  void halt();

  bool isAlive();

protected:
  void parseConfig();
  void handleInput();

  SystemAI*       m_SysAI;
  SystemGUI*      m_SysGUI;
  SystemInput*    m_SysInput;
  SystemNetwork*  m_SysNetwork;
  SystemPhysics*  m_SysPhysics;
  SystemRender*   m_SysRender;
  SystemScript*   m_SysScript;
  SystemSound*    m_SysSound;
  SystemWorld*    m_SysWorld;

  Clock*          m_LabClock;
  Clock*          m_BrainClock;
  Config*         m_Config;

  bool            b_Alive;
  float           f_TimeLimit;
  float           f_WorldRateTemp;
  float           f_InputDelay;
  unsigned int    i_ScreenShots;

  // USER INTERFACE
  UI_GUI*               m_GUI;
  UI_Menu*              m_MenuPause;
  Gorilla::Caption*     m_CaptionPause;
  UI_Button*            m_BtnExit;

  UI_Screen*            m_ScreenBase;
  Gorilla::Layer*       m_LayerCursor;
  Gorilla::Rectangle*   m_CursorBG;
  bool                  b_CursorMode;

  UI_Screen*            m_ScreenDebug;
  Gorilla::Layer*       m_LayerStats;
  Gorilla::Caption*     m_Caption;
  Gorilla::Rectangle*   m_CaptionBG;
  Gorilla::MarkupText*  m_TextDebug;
  Gorilla::Rectangle*   m_DebugBG;

  // LAB LEVEL AND ACTION
  Color           clr_LabEnv;
  Vector3         vec_LabFog;
  EntityCamera*   m_LabCamera;
  float           f_CamSpeed;
  float           f_CamSpeedFast;
  EntityLight*    m_LabLight;

  EntityParticleEmitter* ent_PESnow;

  int             i_JunkCount;
  int             i_MaxJunk;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbBrain_h

/***]EOF[*********************************************************************/