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
* @date   01 January 2015
* @brief  Kerberos laboratory
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbLab_h
#define krbLab_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Kerberos.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

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

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class Lab
{
public:
  Lab(Config* config, Clock* brainClock, Logger* log);
  ~Lab();

  void init();
  void cycle(float delta);
  void halt();

  bool isAlive();

protected:
  // CORE STUFF ///////////////////////////////////////////////////////////////
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
  Logger*         m_Log;
  
  string          str_Version;

  // LAB RELATED THINGS ///////////////////////////////////////////////////////
  bool            b_Alive;
  float           f_TimeLimit;
  float           f_WorldRateTemp;
  float           f_InputDelay;
  float           f_ButtonDelay;
  unsigned int    i_ScreenShots;
  
  // LAB UI ///////////////////////////////////////////////////////////////////
  void createLabUI();

  Clock*                ui_Clock;
  Clock*                ui_InputClock;

  UI_GUI*               ui_Base;
  Config*               ui_Properties;
  UI_Screen*            ui_ScreenLab;

  UI_Layer*             ui_LayerDebug;
  UI_Rectangle*         ui_bgDebugHeader;
  UI_Rectangle*         ui_bgDebugInfo;
  UI_Caption*           ui_CaptionDebugTitle;
  UI_Text*              ui_TextDebugInfo;

  // MENUS ////////////////////////////////////////////////////////////////////
  float menuW;
  float menuH;
  float menuCntX;
  float menuCntY;
  float buttonW;
  float buttonH;
  float buttonPosX;
  float buttonPosY;

  UI_Layer*             ui_LayerMenuHelp;
  UI_Rectangle*         ui_bgMenuHelp;
  UI_Button*            ui_BtnBackHelp;

  UI_Layer*             ui_LayerMenuOptions;
  UI_Rectangle*         ui_bgMenuOptions;
  UI_Button*            ui_BtnBackOptions;

  UI_Layer*             ui_LayerMenuPause;
  UI_Rectangle*         ui_bgMenuPause;
  UI_Button*            ui_BtnHelp;
  UI_Button*            ui_BtnOptions;
  UI_Button*            ui_BtnExit;

  UI_Layer*             ui_LayerCursor;
  UI_Rectangle*         ui_Cursor;

  bool                  b_DebugMode;
  bool                  b_MenuMode;

  // LAB LEVEL AND ACTION /////////////////////////////////////////////////////
  void createEntities();
  void animateLights();

  Color           clr_LabEnv;
  Vector3         vec_LabFog;

  EntityCamera*   m_LabCamera;
  float           f_CamSpeed;
  float           f_CamSpeedFast;

  EntityLight*    m_LabLightA;
  EntityLight*    m_LabLightB;
  EntityLight*    m_LabLightC;
  EntityLight*    m_LabLightD;
  Clock*          lt_Clock;
  Color           lt_Color;
  float           lt_Range;
  float           lt_Const;
  float           lt_Linear;
  float           lt_Quad;
  float           lt_Delay;

  bool            lt_MoveIn;

  int             i_JunkCount;
  int             i_MaxJunk;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbBrain_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\