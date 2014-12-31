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
* @file   krbLab.cpp
* @author Nathan Harris
* @date   30 December 2014
* @brief  Kerberos test-lab
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "krbLab.h"
#include "Kerberos.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Lab::Lab(Config* config, Clock* brainClock, Logger* log)
{
  m_Config      = config;
  m_BrainClock  = brainClock;
  m_Log         = log;
  b_Alive       = false;

  m_SysGUI      = nullptr;
  m_SysInput    = nullptr;
  m_SysPhysics  = nullptr;
  m_SysRender   = nullptr;
  m_SysWorld    = nullptr;
}

Lab::~Lab()
{
}

/*****************************************************************************
*****************************************************************************/

bool Lab::isAlive()
{
  return b_Alive;
}

/*****************************************************************************
*****************************************************************************/

void Lab::init()
{
  parseConfig();
  m_LabClock = new Clock(false);

  // GRAB POINTERS TO ALL SYSTEMS
  m_SysScript   = SystemScript::getSingletonPtr();
  m_SysRender   = SystemRender::getSingletonPtr();
  m_SysInput    = SystemInput::getSingletonPtr();
  m_SysPhysics  = SystemPhysics::getSingletonPtr();
  m_SysWorld    = SystemWorld::getSingletonPtr();
  m_SysSound    = SystemSound::getSingletonPtr();
  m_SysGUI      = SystemGUI::getSingletonPtr();
  m_SysAI       = SystemAI::getSingletonPtr();
  m_SysNetwork  = SystemNetwork::getSingletonPtr();

  // LIGHTS
  m_LabLightRed = m_SysWorld->addEntityLight(
    "LAB_LIGHT_RED", Vector3(0, 0, 0));
  m_LabLightRed->setPosition(Vector3(0, 3.f, 2.5f));
  m_LabLightRed->setDiffuseColor(Color(1.f, 0, 0));

  m_LabLightGreen = m_SysWorld->addEntityLight(
    "LAB_LIGHT_GREEN", Vector3(0, 0, 0));
  m_LabLightGreen->setPosition(Vector3(-5.f, 3, 0));
  m_LabLightGreen->setDiffuseColor(Color(0, 1.f, 0));

  m_LabLightBlue = m_SysWorld->addEntityLight(
    "LAB_LIGHT_BLUE", Vector3(0, 0, 0));
  m_LabLightBlue->setPosition(Vector3(0, 3.f, -2.5f));
  m_LabLightBlue->setDiffuseColor(Color(0, 0, 1.f));

  // CAMERA
  m_LabCamera = m_SysWorld->addEntityCamera(
    "LAB_CAM", Vector3(10, 10, 10));
  m_LabCamera->setViewport(m_SysRender->getViewport());
  m_LabCamera->setActive();
  m_LabCamera->lookAt(Vector3(0, 0, 0));

  // ENVIRONMENT
  m_SysWorld->createGrid();

  m_SysWorld->createPlane(Vector2(
    m_Config->getFloat("WORLD", "ExtentW"),
    m_Config->getFloat("WORLD", "ExtentH")), 
    m_Config->getFloat("WORLD", "WorldScale"));

  m_SysWorld->setAmbient(clr_LabEnv);
  m_SysWorld->setFog(
    clr_LabEnv, 
    m_Config->getFloat("LAB", "FogType"),
    vec_LabFog.x, vec_LabFog.y, vec_LabFog.z);

  // PARTICLE STUFF
  //ent_PESnow = m_SysWorld->addParticleEmitter("red_snow");
  //ent_PESnow->start();

  // SETUP BASIC GUI
  m_GUI = m_SysGUI->createGUI("GUI_DEBUG", false);
  m_ScreenDebug = m_GUI->createScreen("SCREEN_DEBUG", "gui_lab");
  m_LayerStats = m_ScreenDebug->createLayer("LAYER_DEBUG");

  // GUI CAPTION
  m_Caption = m_LayerStats->createCaption(7, 16, 16, 
    "Kerberos Engine v" + getVersionString());
  m_Caption->fixedWidth(true);
  m_CaptionBG = m_LayerStats->createRectangle(10, 10, 325, 20);
  m_CaptionBG->background_colour(Ogre::ColourValue(0.3, 0.1, 0.1, 0.8));

  // GUI TEXT - STATS AND SUCH
  m_TextDebug = m_LayerStats->createMarkupText(7, 16, 46, "");
  m_DebugBG = m_LayerStats->createRectangle(10, 40, 325, 140);
  m_DebugBG->background_colour(Ogre::ColourValue(0.1, 0.1, 0.1, 0.8));

  // BASIC MENU
  float f_MenuH, f_MenuW;
  f_MenuH = 256;
  f_MenuW = 256;
  m_MenuPause = m_GUI->createMenu("MENU_PAUSE", "gui_lab", "menu_pause", Vector2(f_MenuH, f_MenuW));

  // CREATE AN EXIT BUTTON
  float f_ButtonH, f_ButtonW, f_ButtonCntrX, f_ButtonCntrY;
  f_ButtonH = 16;
  f_ButtonW = 128;
  f_ButtonCntrX = (m_MenuPause->getScreen()->getWidth() / 2) - (f_ButtonW / 2);
  f_ButtonCntrY = (m_MenuPause->getScreen()->getHeight() / 2) - (f_ButtonH / 2);

  m_BtnExit = m_GUI->createButton("BUTTON_EXIT", m_MenuPause->getLayer(),
    "btn_exit_base", "btn_exit_hover", 
    Vector2(f_ButtonCntrX, f_ButtonCntrY + 96), Vector2(f_ButtonW, f_ButtonH),
    m_SysInput->getMouse());

  // CREATE A CAPTION
  float f_CaptionH, f_CaptionW, f_CaptionCntrX, f_CaptionCntrY;
  f_CaptionH = 16;
  f_CaptionW = 256;
  f_CaptionCntrX = 
    (m_MenuPause->getScreen()->getWidth() / 2) - (f_CaptionW / 2);
  f_CaptionCntrY = 
    (m_MenuPause->getScreen()->getHeight() / 2) - (f_CaptionH / 2);

  m_CaptionPause = m_MenuPause->getLayer()->createCaption(7, 0, 0, 
    "Kerberos Engine v" + getVersionString());
  m_Caption->width(m_MenuPause->getDimensions().x);
  m_CaptionPause->left(f_CaptionCntrX + 3);
  m_CaptionPause->top(f_CaptionCntrY + 148);
  m_CaptionPause->fixedWidth(true);

  // UI CURSOR
  b_CursorMode = false;
  m_LayerCursor = m_MenuPause->getScreen()->createLayer();
  m_CursorBG = m_LayerCursor->createRectangle(
    Ogre::Vector2(0, 0), 
    Ogre::Vector2(16, 16));
  m_CursorBG->background_image("cursor");

  i_ScreenShots = 0;
  i_JunkCount = 0;

  m_SysWorld->toggleEntityBillboards();

  b_Alive = true;
  
  m_LabClock->reset();
}

/*****************************************************************************
*****************************************************************************/

void Lab::cycle(float delta)
{
  if (f_TimeLimit > 0 && m_BrainClock->msex() >= f_TimeLimit)
  {
    b_Alive = false;
  }

  handleInput();

  if (m_MenuPause->isVisible() && b_CursorMode)
  {
    m_CursorBG->position(Ogre::Vector2(
      m_SysInput->getMouse()->getMouseState().X.abs,
      m_SysInput->getMouse()->getMouseState().Y.abs));

    m_BtnExit->isOver();

    if (m_BtnExit->mouseDown(OIS::MB_Left))
    {
      b_Alive = false;
    }
  }

  if (m_ScreenDebug->isVisible())
  {
    m_TextDebug->text(
      "Time : " + m_BrainClock->msexString() +
      "\n" +
      "World time: " + m_SysWorld->getTimeString() +
      "\n" +
      "World rate: " + toString(m_SysWorld->getWorldRate(), 6) +
      "\n" +
      "FPS : " + toString(m_SysRender->getWindow()->getLastFPS(), 1) +
      "\n" +
      "Batches : " + Ogre::StringConverter::toString(
      m_SysRender->getWindow()->getBatchCount()) +
      "\n"
      //"Yaw: " + toString(m_LabCamera->getYawPitch().x) +
      //"\n" +
      //"Pitch: " + toString(m_LabCamera->getYawPitch().y) +
      //"\n"
      //"Junk count : " + toString(i_JunkCount)
      );
  }
}

/*****************************************************************************
*****************************************************************************/

void Lab::halt()
{
}

/*****************************************************************************
*****************************************************************************/

void Lab::parseConfig()
{
  f_InputDelay      = 250.0f;
  f_WorldRateTemp   = 1.0f;  
  f_TimeLimit       = m_Config->getFloat("LAB", "TimeLimit");
  f_CamSpeed        = m_Config->getFloat("LAB", "CamSpeed");
  f_CamSpeedFast    = m_Config->getFloat("LAB", "CamSpeedFast");

  clr_LabEnv = m_Config->getColor("LAB", "EnvColor");
  vec_LabFog = Vector3(
    m_Config->getFloat("LAB", "FogDensity"),
    m_Config->getFloat("LAB", "FogStart"),
    m_Config->getFloat("LAB", "FogEnd"));
}

/*****************************************************************************
*****************************************************************************/

void Lab::handleInput()
{
  // PAUSE
  if (m_SysInput->keyDown(OIS::KC_ESCAPE) && m_LabClock->msex() >= f_InputDelay)
  {
    m_SysWorld->pauseWorld();
    m_MenuPause->toggleVisible();

    b_CursorMode = !b_CursorMode;

    m_LabClock->reset();
  }

  if (!b_CursorMode)
  {
    m_LabCamera->setOrientation(
      -m_SysInput->getMouse()->getMouseState().X.rel,
      -m_SysInput->getMouse()->getMouseState().Y.rel,
      0.001f);
  }

  if (!m_SysWorld->isPaused())
  {
    if (m_SysInput->getKeyboard()->isModifierDown(OIS::Keyboard::Shift))
    {
      if (m_SysInput->keyDown(OIS::KC_W))
      {
        m_LabCamera->moveApplicate(f_CamSpeedFast);
      }

      if (m_SysInput->keyDown(OIS::KC_S))
      {
        m_LabCamera->moveApplicate(-f_CamSpeedFast);
      }

      if (m_SysInput->keyDown(OIS::KC_A))
      {
        m_LabCamera->moveAbscissa(f_CamSpeedFast);
      }

      if (m_SysInput->keyDown(OIS::KC_D))
      {
        m_LabCamera->moveAbscissa(-f_CamSpeedFast);
      }

      if (m_SysInput->keyDown(OIS::KC_Q))
      {
        m_LabCamera->moveOrdinate(f_CamSpeedFast);
      }

      if (m_SysInput->keyDown(OIS::KC_E))
      {
        m_LabCamera->moveOrdinate(-f_CamSpeedFast);
      }
    }
    else
    {
      if (m_SysInput->keyDown(OIS::KC_W))
      {
        m_LabCamera->moveApplicate(f_CamSpeed);
      }

      if (m_SysInput->keyDown(OIS::KC_S))
      {
        m_LabCamera->moveApplicate(-f_CamSpeed);
      }

      if (m_SysInput->keyDown(OIS::KC_A))
      {
        m_LabCamera->moveAbscissa(f_CamSpeed);
      }

      if (m_SysInput->keyDown(OIS::KC_D))
      {
        m_LabCamera->moveAbscissa(-f_CamSpeed);
      }

      if (m_SysInput->keyDown(OIS::KC_Q))
      {
        m_LabCamera->moveOrdinate(f_CamSpeed);
      }

      if (m_SysInput->keyDown(OIS::KC_E))
      {
        m_LabCamera->moveOrdinate(-f_CamSpeed);
      }
    }
  }

  // DEBUG
  if (m_SysInput->keyDown(OIS::KC_GRAVE) && m_LabClock->msex() >= f_InputDelay)
  {
    m_ScreenDebug->toggleVisible();
    m_SysWorld->toggleGrid();
    m_SysWorld->toggleEntityBillboards();

    m_LabClock->reset();
  }
  if (m_SysInput->keyDown(OIS::KC_P) && m_LabClock->msex() >= f_InputDelay)
  {
    m_SysPhysics->toggleDebug();

    m_LabClock->reset();
  }

  // SCREENSHOT
  if (m_SysInput->keyDown(OIS::KC_SYSRQ) && m_LabClock->msex() >= f_InputDelay)
  {
    Ogre::StringStream ss;
    ss << "screenshot_" << ++i_ScreenShots << ".png";
    m_SysRender->getWindow()->writeContentsToFile(ss.str());

    m_LabClock->reset();
  }
  
  // SPAWN SOME JUNK
  //if (m_SysInput->keyDown(OIS::KC_SPACE) && m_LabClock->msex() >= f_InputDelay)
  //{
  //  m_SysWorld->addDynamic(
  //    "EPD_CUBE_" + to_string(i_JunkCount), 
  //    "lab_cube_red.mesh",
  //    0, Vector3(0, 10, 0));

  //  i_JunkCount++;

  //  m_LabClock->reset();
  //}

  // CHANGE WORLD RATE
  if (!m_SysWorld->isPaused())
  {
    if (m_SysInput->keyDown(OIS::KC_1) && m_LabClock->msex() >= f_InputDelay)
    {
      m_SysWorld->setWorldRate(1.0f);

      m_LabClock->reset();
    }
    if (m_SysInput->keyDown(OIS::KC_2) && m_LabClock->msex() >= f_InputDelay)
    {
      m_SysWorld->setWorldRate(0.25f);

      m_LabClock->reset();
    }
    if (m_SysInput->keyDown(OIS::KC_3) && m_LabClock->msex() >= f_InputDelay)
    {
      m_SysWorld->setWorldRate(0.1f);

      m_LabClock->reset();
    }
    if (m_SysInput->keyDown(OIS::KC_4) && m_LabClock->msex() >= f_InputDelay)
    {
      m_SysWorld->setWorldRate(0.01f);

      m_LabClock->reset();
    }
  }
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/