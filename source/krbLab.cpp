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
* @date   01 January 2015
* @brief  Kerberos laboratory
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "krbLab.h"
#include "Kerberos.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

Lab::Lab(Config* config, Clock* brainClock, Logger* log)
{
  m_Config      = config;
  m_BrainClock  = brainClock;
  m_Log         = log;
  b_Alive       = false;
  str_Version   = "Kerberos Engine v" + getVersionString();
  i_ScreenShots = 0;
  i_JunkCount   = 0;

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
}

Lab::~Lab()
{
  delete m_LabCamera;

  delete m_LabLightA;
  delete m_LabLightB;
  delete m_LabLightC;
  delete m_LabLightD;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

bool Lab::isAlive()
{
  return b_Alive;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::init()
{
  parseConfig();

  m_LabClock = new Clock(false);

  // ENVIRONMENT
  m_SysWorld->createGrid();

  m_Log->logMessage(Logger::LVL_INFO, Logger::MSG_LAB,
    "World grid created");

  m_SysWorld->createPlane(Vector2(
    m_Config->getFloat("WORLD", "ExtentW"),m_Config->getFloat("WORLD", "ExtentH")));

  m_Log->logMessage(Logger::LVL_INFO, Logger::MSG_LAB,
    "World plane created");

  m_SysWorld->setAmbient(clr_LabEnv);
  m_SysWorld->setFog(
    clr_LabEnv, 
    m_Config->getFloat("LAB", "FogType"),
    vec_LabFog.x, vec_LabFog.y, vec_LabFog.z);

  m_Log->logMessage(Logger::LVL_INFO, Logger::MSG_LAB,
    "Environment lighting and fog set up");  

  createEntities();
  createLabUI();

  b_Alive = true;
  
  m_LabClock->reset();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::cycle(float delta)
{
  if (f_TimeLimit > 0 && m_BrainClock->msex() >= f_TimeLimit)
  {
    b_Alive = false;
  }

  handleInput(); 

  animateLights();

  if (ui_LayerDebug->isVisible())
  {    
    ui_TextDebugInfo->setText(
      "Time : " + m_BrainClock->msexString() +
      "\n" +
      "World time: " + m_SysWorld->getTimeString() +
      "\n" +
      "World rate: " + toString(m_SysWorld->getWorldRate(), 6) +
      "\n" +
      "FPS : " + toString(m_SysRender->getWindow()->getLastFPS(), 1) +
      "\n" +
      "Batches : " + Ogre::StringConverter::toString(
      m_SysRender->getWindow()->getBatchCount()));
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::halt()
{
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::parseConfig()
{
  f_WorldRateTemp   = 1.0f;  
  f_TimeLimit       = m_Config->getFloat("LAB", "TimeLimit");
  f_CamSpeed        = m_Config->getFloat("LAB", "CamSpeed");
  f_CamSpeedFast    = m_Config->getFloat("LAB", "CamSpeedFast");

  clr_LabEnv = m_Config->getColor("LAB", "EnvColor");
  vec_LabFog = Vector3(
    m_Config->getFloat("LAB", "FogDensity"),
    m_Config->getFloat("LAB", "FogStart"),
    m_Config->getFloat("LAB", "FogEnd"));

  f_ButtonDelay     = 300.0f;
  f_InputDelay      = 300.0f;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::createEntities()
{
  // LIGHTS ///////////////////////////////////////////////////////////////////
  lt_Clock = new Clock(true);
  lt_Color  = m_Config->getColor("LAB", "LightColor");
  lt_Range  = m_Config->getFloat("LAB", "LightRange");
  lt_Const  = m_Config->getFloat("LAB", "LightConstant");
  lt_Linear = m_Config->getFloat("LAB", "LightLinear");
  lt_Quad   = m_Config->getFloat("LAB", "LightQuad");

  m_LabLightA = m_SysWorld->addEntityLight(
    "LAB_LIGHT_A", Vector3(0, 10.f, 10.f));
  m_LabLightA->setAttenuation(lt_Range, lt_Const, lt_Linear, lt_Quad);
  m_LabLightA->setDiffuseColor(lt_Color);

  m_LabLightB = m_SysWorld->addEntityLight(
    "LAB_LIGHT_B", Vector3(0, 10.f, -10.f));
  m_LabLightB->setAttenuation(lt_Range, lt_Const, lt_Linear, lt_Quad);
  m_LabLightB->setDiffuseColor(lt_Color);

  m_LabLightC = m_SysWorld->addEntityLight(
    "LAB_LIGHT_C", Vector3(10.f, 10.f, 0));
  m_LabLightC->setAttenuation(lt_Range, lt_Const, lt_Linear, lt_Quad);
  m_LabLightC->setDiffuseColor(lt_Color);

  m_LabLightD = m_SysWorld->addEntityLight(
    "LAB_LIGHT_D", Vector3(-10.f, 10.f, 0));
  m_LabLightD->setAttenuation(lt_Range, lt_Const, lt_Linear, lt_Quad);
  m_LabLightD->setDiffuseColor(lt_Color);

  lt_MoveIn = false;

  m_Log->logMessage(Logger::LVL_INFO, Logger::MSG_LAB,
    "Lights created");

  // CAMERA ///////////////////////////////////////////////////////////////////
  m_LabCamera = m_SysWorld->addEntityCamera("LAB_CAM", Vector3(10, 10, 10));
  m_LabCamera->setViewport(m_SysRender->getViewport());
  m_LabCamera->setActive();
  m_LabCamera->lookAt(Vector3(0, 0, 0));

  m_Log->logMessage(Logger::LVL_INFO, Logger::MSG_LAB,
    "Camera created");

  // TOGGLE BILLBOARDS OFF
  m_SysWorld->toggleEntityBillboards();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::createLabUI()
{
  ui_Clock = new Clock(false);
  ui_InputClock = new Clock(false);

  b_MenuMode = false;
  b_DebugMode = false;  

  // CORE GUI AND SCREEN //////////////////////////////////////////////////////
  ui_Base = m_SysGUI->createGUI("GUI_LAB", true);

  ui_ScreenLab = ui_Base->createScreen("SCREEN_LAB", "gui_lab", true);

  float screenW = ui_ScreenLab->getWidth();
  float screenH = ui_ScreenLab->getHeight();

  // DEBUG LAYER //////////////////////////////////////////////////////////////
  ui_LayerDebug = ui_Base->createLayer("LAYER_DEBUG", false, 1, ui_ScreenLab);

  float debugHeaderW = 300;
  float debugHeaderH = 25;
  float debugHeaderX = 10;
  float debugHeaderY = 10;

  ui_bgDebugHeader = ui_Base->createRectangle("BG_DEBUG_HEADER", 
    Color(0.4, 0.1, 0.1, 0.66), 
    Vector2(debugHeaderX, debugHeaderY), 
    Vector2(debugHeaderW, debugHeaderH), 
    ui_LayerDebug);

  ui_CaptionDebugTitle = ui_Base->createCaption("CAPTION_DEBUG_TITLE", 10,
    Vector2(debugHeaderX + 10, debugHeaderY + 10),
    Vector2(debugHeaderW - 10, debugHeaderH - 10),
    str_Version, true,
    ui_LayerDebug);

  float debugInfoW = 300;
  float debugInfoH = 200;
  float debugInfoX = 10;
  float debugInfoY = 45;

  ui_bgDebugInfo = ui_Base->createRectangle("BG_DEBUG_INFO", 
    Color(0.2, 0.2, 0.2, 0.66), 
    Vector2(debugInfoX, debugInfoY), 
    Vector2(debugInfoW, debugInfoH),
    ui_LayerDebug);

  ui_TextDebugInfo = ui_Base->createText("TEXT_DEBUG_INFO", 10,
    Vector2(debugInfoX + 10, debugInfoY + 10),
    Vector2(debugInfoW - 10, debugInfoH - 10),
    "DEBUG INFO",
    ui_LayerDebug);

  // HELP MENU LAYER //////////////////////////////////////////////////////////
  ui_LayerMenuHelp = ui_Base->createLayer(
    "LAYER_MENU_HELP", false, 2, ui_ScreenLab);

  menuW = 256;
  menuH = 256;
  menuCntX = findElemCenter(screenW, menuW);
  menuCntY = findElemCenter(screenH, menuH);

  ui_bgMenuHelp = ui_Base->createRectangle(
    "BG_MENU_HELP", 
    "menu_help", 
    Vector2(menuCntX, menuCntY),
    Vector2(menuW, menuH), 
    ui_LayerMenuHelp);

  buttonW = 128;
  buttonH = 16;
  buttonPosX = findElemCenter(screenW, buttonW);
  buttonPosY = (screenH / 2) + ((menuH / 2) - (buttonH * 2));

  ui_BtnBackHelp = ui_Base->createButton("BUTTON_BACK_HELP",
    "btn_back_base", "btn_back_hover",
    Vector2(buttonPosX, buttonPosY),
    Vector2(buttonW, buttonH),
    ui_LayerMenuHelp,
    m_SysInput->getMouse());

  // OPTIONS MENU LAYER ///////////////////////////////////////////////////////
  ui_LayerMenuOptions = ui_Base->createLayer(
    "LAYER_MENU_OPTIONS", false, 2, ui_ScreenLab);

  menuW = 256;
  menuH = 256;
  menuCntX = findElemCenter(screenW, menuW);
  menuCntY = findElemCenter(screenH, menuH);

  ui_bgMenuOptions = ui_Base->createRectangle(
    "BG_MENU_OPTIONS", 
    "menu_options", 
    Vector2(menuCntX, menuCntY),
    Vector2(menuW, menuH), 
    ui_LayerMenuOptions);

  buttonW = 128;
  buttonH = 16;
  buttonPosX = findElemCenter(screenW, buttonW);
  buttonPosY = (screenH / 2) + ((menuH / 2) - (buttonH * 2));

  ui_BtnBackOptions = ui_Base->createButton("BUTTON_BACK_OPTIONS",
    "btn_back_base", "btn_back_hover",
    Vector2(buttonPosX, buttonPosY),
    Vector2(buttonW, buttonH),
    ui_LayerMenuOptions,
    m_SysInput->getMouse());

  // PAUSE MENU LAYER /////////////////////////////////////////////////////////
  ui_LayerMenuPause = ui_Base->createLayer(
    "LAYER_MENU_PAUSE", false, 2, ui_ScreenLab);

  menuW = 256;
  menuH = 256;
  menuCntX = findElemCenter(screenW, menuW);
  menuCntY = findElemCenter(screenH, menuH);

  ui_bgMenuPause = ui_Base->createRectangle(
    "BG_MENU_PAUSE", 
    "menu_pause", 
    Vector2(menuCntX, menuCntY),
    Vector2(menuW, menuH), 
    ui_LayerMenuPause);

  buttonW = 128;
  buttonH = 16;
  buttonPosX = findElemCenter(screenW, buttonW);
  buttonPosY = (screenH / 2) + ((menuH / 2) - (buttonH * 2));

  ui_BtnHelp = ui_Base->createButton("BUTTON_HELP",
    "btn_help_base", "btn_help_hover",
    Vector2(buttonPosX, buttonPosY - (buttonH * 4)),
    Vector2(buttonW, buttonH),
    ui_LayerMenuPause,
    m_SysInput->getMouse());

  ui_BtnOptions = ui_Base->createButton("BUTTON_OPTIONS",
    "btn_options_base", "btn_options_hover",
    Vector2(buttonPosX, buttonPosY - (buttonH * 2)),
    Vector2(buttonW, buttonH),
    ui_LayerMenuPause,
    m_SysInput->getMouse());

  ui_BtnExit = ui_Base->createButton("BUTTON_EXIT",
    "btn_exit_base", "btn_exit_hover",
    Vector2(buttonPosX, buttonPosY),
    Vector2(buttonW, buttonH),
    ui_LayerMenuPause,
    m_SysInput->getMouse());

  // CURSOR LAYER /////////////////////////////////////////////////////////////
  ui_LayerCursor = ui_Base->createLayer("LAYER_CURSOR", false, 15, 
    ui_ScreenLab);
  ui_Cursor = ui_Base->createRectangle("LAB_CURSOR", "cursor",
    Vector2(0, 0), Vector2(16, 16), 
    ui_LayerCursor);

  ui_Clock->reset();
  ui_InputClock->reset();
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::animateLights()
{
  float speed = 0.015f * m_SysWorld->getWorldRate();

  if (!lt_MoveIn)
  {
    m_LabLightA->setPosition(Vector3(
      m_LabLightA->getPosition().x,
      m_LabLightA->getPosition().y,
      m_LabLightA->getPosition().z + speed));

    m_LabLightB->setPosition(Vector3(
      m_LabLightB->getPosition().x,
      m_LabLightB->getPosition().y,
      m_LabLightB->getPosition().z - speed));

    m_LabLightC->setPosition(Vector3(
      m_LabLightC->getPosition().x + speed,
      m_LabLightC->getPosition().y,
      m_LabLightC->getPosition().z));

    m_LabLightD->setPosition(Vector3(
      m_LabLightD->getPosition().x - speed,
      m_LabLightD->getPosition().y,
      m_LabLightD->getPosition().z));

    if (m_LabLightC->getPosition().x >= 25.0f)
    {
      lt_MoveIn = true;
    }
  }
  else
  {
    m_LabLightA->setPosition(Vector3(
      m_LabLightA->getPosition().x,
      m_LabLightA->getPosition().y,
      m_LabLightA->getPosition().z - speed));

    m_LabLightB->setPosition(Vector3(
      m_LabLightB->getPosition().x,
      m_LabLightB->getPosition().y,
      m_LabLightB->getPosition().z + speed));

    m_LabLightC->setPosition(Vector3(
      m_LabLightC->getPosition().x - speed,
      m_LabLightC->getPosition().y,
      m_LabLightC->getPosition().z));

    m_LabLightD->setPosition(Vector3(
      m_LabLightD->getPosition().x + speed,
      m_LabLightD->getPosition().y,
      m_LabLightD->getPosition().z));

    if (m_LabLightC->getPosition().x <= 5.0f)
    {
      lt_MoveIn = false;
    }
  }
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

void Lab::handleInput()
{
  // MOUSE ////////////////////////////////////////////////////////////////////
  if (!b_MenuMode)
  {
    m_LabCamera->setOrientation(
      -m_SysInput->getMouse()->getMouseState().X.rel,
      -m_SysInput->getMouse()->getMouseState().Y.rel,
      0.001f);
  }

  if (ui_LayerCursor->isVisible() && b_MenuMode)
  {
    ui_Cursor->setPosition(Vector2(
      m_SysInput->getMouse()->getMouseState().X.abs,
      m_SysInput->getMouse()->getMouseState().Y.abs));

    if (ui_BtnHelp->mouseDown(OIS::MB_Left) && ui_InputClock->msex() >= f_ButtonDelay)
    {
      ui_LayerMenuHelp->show();
      ui_LayerMenuOptions->hide();
      ui_LayerMenuPause->hide();

      ui_InputClock->reset();
    }
    if (ui_BtnBackHelp->mouseDown(OIS::MB_Left) && ui_InputClock->msex() >= f_ButtonDelay)
    {
      ui_LayerMenuHelp->hide();
      ui_LayerMenuOptions->hide();
      ui_LayerMenuPause->show();

      ui_InputClock->reset();
    }

    if (ui_BtnOptions->mouseDown(OIS::MB_Left) && ui_InputClock->msex() >= f_ButtonDelay) 
    {
      ui_LayerMenuOptions->show();
      ui_LayerMenuHelp->hide();
      ui_LayerMenuPause->hide();

      ui_InputClock->reset();
    }
    if (ui_BtnBackOptions->mouseDown(OIS::MB_Left) && ui_InputClock->msex() >= f_ButtonDelay)
    {
      ui_LayerMenuHelp->hide();
      ui_LayerMenuOptions->hide();
      ui_LayerMenuPause->show();

      ui_InputClock->reset();
    }

    if (ui_BtnExit->mouseDown(OIS::MB_Left) && ui_InputClock->msex() >= f_ButtonDelay)
    { 
      b_Alive = false; 
    }
  }

  // PAUSE ////////////////////////////////////////////////////////////////////
  if (m_SysInput->keyDown(OIS::KC_ESCAPE) && m_LabClock->msex() >= f_InputDelay)
  {
    m_SysWorld->pauseWorld();

    b_MenuMode = !b_MenuMode;

    ui_LayerCursor->toggleVisible();
    ui_LayerMenuPause->toggleVisible();

    if (ui_LayerMenuHelp->isVisible()) 
    { 
      ui_LayerMenuHelp->hide(); 
    }
    if (ui_LayerMenuOptions->isVisible()) 
    { 
      ui_LayerMenuOptions->hide(); 
    }

    m_LabClock->reset();
  }

  // DEBUG ////////////////////////////////////////////////////////////////////
  if (m_SysInput->keyDown(OIS::KC_GRAVE) && m_LabClock->msex() >= f_InputDelay)
  {
    b_DebugMode = !b_DebugMode;
    ui_LayerDebug->toggleVisible();

    m_SysWorld->toggleGrid();
    m_SysWorld->toggleEntityBillboards();

    m_LabClock->reset();
  }

  if (m_SysInput->keyDown(OIS::KC_P) && m_LabClock->msex() >= f_InputDelay)
  {
    m_SysPhysics->toggleDebug();

    m_LabClock->reset();
  }

  // SCREENSHOT ///////////////////////////////////////////////////////////////
  if (m_SysInput->keyDown(OIS::KC_SYSRQ) && m_LabClock->msex() >= f_InputDelay)
  {
    Ogre::StringStream ss;
    ss << "screenshot_" << ++i_ScreenShots << ".png";
    m_SysRender->getWindow()->writeContentsToFile(ss.str());

    m_LabClock->reset();
  }

  // MOVEMENT /////////////////////////////////////////////////////////////////
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

  // CHANGE WORLD RATE ////////////////////////////////////////////////////////
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

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

}

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\