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
* @file   krbBrain.cpp
* @author Nathan Harris
* @date   23 December 2014
* @brief  The central nervous system of Kerberos
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "Kerberos.h"

#include "Ogre3D/OgreWindowEventUtilities.h"

#include <iostream>
#include <sstream>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Brain::Brain()
{
  stringstream ss_ver;
  ss_ver << 
  KRB_VERSION_MAJOR << "." <<
  KRB_VERSION_MINOR << "." <<
  KRB_VERSION_PATCH << "." <<
  KRB_VERSION_ALPHA << " (" << KRB_VERSION_NAME ")";
  str_Version = ss_ver.str();

  m_Clock       = new Clock(false);

  m_SysAI       = nullptr;
  m_SysInput    = nullptr;
  m_SysNetwork  = nullptr;
  m_SysPhysics  = nullptr;
  m_SysRender   = nullptr;
  m_SysScript   = nullptr;
  m_SysSound    = nullptr;
  m_SysWorld    = nullptr;

  b_Alive       = false;
  d_Accumulator = 0.0;
  d_Counter     = 0.0;
  d_DeltaTime   = 0.0;
  d_LogicRate   = 0.0;
  d_CurrentTime = 0.0;
  d_NewTime     = 0.0;
  d_TickCount   = 0.0;
}

Brain::~Brain()
{
  b_Alive = false;

  delete m_Log;
  delete m_Config;
  delete m_Clock;
}

/*****************************************************************************
*****************************************************************************/

void Brain::init()
{
  m_Config = new Config("./Kerberos.kcp");
  parseConfig();
  
  m_Log = new Logger(str_LogFile, 0, str_Version);  

  b_Alive = true;

  addSystems();

  // PERHAPS DO THINGS BEFORE INITIALIZING SYSTEMS

  initSystems();
}

/*****************************************************************************
*****************************************************************************/

void Brain::cycle()
{
  createLab();

  m_Clock->reset();
  m_SysWorld->resetClock();  // KEEP AN EYE ON THIS- SHOULD BE TIED TO SCENE 
                             // INIT IN GAME SCOPE

  while (b_Alive)
  {
    Ogre::WindowEventUtilities::messagePump();

    d_NewTime = m_Clock->msex();
    d_DeltaTime = d_NewTime - d_CurrentTime;

    if (d_DeltaTime <= 0.0)
    {
      continue;
    }

    d_CurrentTime = d_NewTime;
    d_Accumulator += d_DeltaTime;

    while (d_Accumulator >= d_LogicRate)
    {
      m_SysScript->cycle();
      m_SysInput->cycle();      
      m_SysWorld->cycle();

      m_SysPhysics->cycle(
        d_DeltaTime,
        m_SysWorld->getWorldRate(),
        m_SysWorld->isPaused());
      m_SysAI->cycle();
      m_SysSound->cycle();
      m_SysGUI->cycle();      
      m_SysNetwork->cycle(); 

      cycleLab();

      d_Counter += d_LogicRate;
      d_Accumulator -= d_LogicRate;

      d_TickCount++;
    }

    m_SysRender->cycle();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::halt()
{
  haltSystems();

  // PERHAPS DO THINGS BEFORE DESTROYING SYSTEMS 

  destroySystems();

  // LOG SOME STATISTICS
  m_Log->logSection("STATISTICS");
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Brain time: " + m_Clock->msexString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("World time: " + m_SysWorld->getTimeString()));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic ticks: " + toString(d_TickCount)));
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
    ("Logic RPS: " + toString(d_TickCount / (m_Clock->msex() / 1000.0))));

  m_Log->closeLog();
}

/*****************************************************************************
*****************************************************************************/

void Brain::parseConfig()
{
  str_LogFile = m_Config->getString("BRAIN", "LogFile");
  d_LogicRate = 1000.0 / m_Config->getFloat("BRAIN", "LogicRate");
}

/*****************************************************************************
*****************************************************************************/

void Brain::addSystems()
{
  m_Log->logSection("SYSTEMS PRIME");

  // ADD SCRIPT SYSTEM
  m_SysScript = new SystemScript(m_Config, m_Log);
  vec_Sys.push_back(m_SysScript);
  map_Sys[m_SysScript->getName()] = m_SysScript;

  // ADD RENDER SYSTEM
  m_SysRender = new SystemRender(m_Config, m_Log);
  vec_Sys.push_back(m_SysRender);
  map_Sys[m_SysRender->getName()] = m_SysRender;

  // ADD INPUT SYSTEM
  m_SysInput = new SystemInput(m_Config, m_Log);
  vec_Sys.push_back(m_SysInput);
  map_Sys[m_SysInput->getName()] = m_SysInput;

  // ADD GUI SYSTEM
  m_SysGUI = new SystemGUI(m_Config, m_Log);
  vec_Sys.push_back(m_SysGUI);
  map_Sys[m_SysGUI->getName()] = m_SysGUI;

  // ADD WORLD SYSTEM
  m_SysWorld = new SystemWorld(m_Config, m_Log);
  vec_Sys.push_back(m_SysWorld);
  map_Sys[m_SysWorld->getName()] = m_SysWorld;

  // ADD PHYSICS SYSTEM
  m_SysPhysics = new SystemPhysics(m_Config, m_Log);
  vec_Sys.push_back(m_SysPhysics);
  map_Sys[m_SysPhysics->getName()] = m_SysPhysics;

  // ADD SOUND SYSTEM
  m_SysSound = new SystemSound(m_Config, m_Log);
  vec_Sys.push_back(m_SysSound);
  map_Sys[m_SysSound->getName()] = m_SysSound;

  // ADD AI SYSTEM
  m_SysAI = new SystemAI(m_Config, m_Log);
  vec_Sys.push_back(m_SysAI);
  map_Sys[m_SysAI->getName()] = m_SysAI;

  // ADD NETWORK SYSTEM
  m_SysNetwork = new SystemNetwork(m_Config, m_Log);
  vec_Sys.push_back(m_SysNetwork);
  map_Sys[m_SysNetwork->getName()] = m_SysNetwork;

  vector<System*>::iterator vec_SysIT = vec_Sys.begin();
  for(; vec_SysIT != vec_Sys.end(); ++vec_SysIT)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      "Touching system: " + (*vec_SysIT)->getName());
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::initSystems()
{
  m_Log->logSection("SYSTEMS INIT");

  // INIT SCRIPT SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysScript->getName()));
  m_SysScript->init();

  // INIT RENDER SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysRender->getName()));
  m_SysRender->init();

  // INIT INPUT SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysInput->getName()));
  m_SysInput->setWindow(m_SysRender->getWindow());  // GRAB OGRE WINDOW
  m_SysInput->init();

  // INIT GUI SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysInput->getName()));
  m_SysGUI->connectOgre(m_SysRender->getViewport());  // GRAB INITIAL VIEWPORT
  m_SysGUI->init();

  // INIT WORLD SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysWorld->getName()));
  m_SysWorld->connectOgre(
    m_SysRender->getSceneManager(), m_SysRender->getViewport()); // GRAB SCENE MANAGER AND VP
  m_SysWorld->init();

  // INIT PHYSICS SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysPhysics->getName()));
  m_SysPhysics->connectOgre(m_SysRender->getSceneManager());  // GRAB OGRE SCENE MANAGER
  m_SysPhysics->init();
  m_SysWorld->connectBullet(m_SysPhysics->getBulletWorld()); // GRAB BULLET WORLD

  // INIT SOUND SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysSound->getName()));
  m_SysSound->init();

  // INIT AI SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysAI->getName()));
  m_SysAI->init();

  // INIT NETWORK SYSTEM
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Initializing system: " + m_SysNetwork->getName()));
  m_SysNetwork->init();
}

/*****************************************************************************
*****************************************************************************/

void Brain::haltSystems()
{
  m_Log->logSection("SYSTEMS HALT");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for(; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Halting system: " + (*rit)->getName()));

    (*rit)->halt();
  }
}

/*****************************************************************************
*****************************************************************************/

void Brain::destroySystems()
{
  m_Log->logSection("SYSTEMS DESTROY");

  vector<System*>::reverse_iterator rit = vec_Sys.rbegin();
  for(; rit != vec_Sys.rend(); ++rit)
  {
    m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_BRAIN,
      ("Destroying system: " + (*rit)->getName()));

    delete (*rit);
  }
}

/*****************************************************************************
*****************************************************************************/

// ~KERBEROS LAB~
// THIS SHOULD BE MOVED OUT INTO A "GAME" OR DEMO, BUT FOR NOW
// TESTING WILL BE DONE IN THE BRAIN HERE AT THE END. IDEALLY
// ACTUAL APPLICATION DESIGN WILL BE DONE WITH TOOLS AND
// SCRIPTING.

void Brain::createLab()
{
  // PARSE CONFIG OPTIONS FOR LAB DEMO
  f_InputDelay      = 250.0f;
  f_WorldRateTemp   = 1.0f;  
  f_DemoTime        = m_Config->getFloat("LAB", "TimeLimit");
  f_CamSpeed        = m_Config->getFloat("LAB", "CamSpeed");

  // ENVIRONMENT
  clr_LabEnv = m_Config->getColor("LAB", "EnvColor");
  vec_LabFog = m_Config->getVec3("LAB", "FogSetting");

  m_SysWorld->setEnvironment(Color(
    clr_LabEnv.r, 
    clr_LabEnv.g, 
    clr_LabEnv.b), 
    vec_LabFog.x,
    vec_LabFog.y,
    vec_LabFog.z);

  // LIGHT
  m_LabLight = m_SysWorld->addLight("LIGHT_LAB", EntityLight::LT_DIR);
  m_LabLight->setMaxAge(0);
  m_LabLight->position(1000, 1000, 1000);
  m_LabLight->setDirection(0.1f, -1.f, 0.1f);

  // CAMERA
  m_LabCamera = m_SysWorld->addCamera("CAM_LAB");
  m_LabCamera->setMaxAge(0);
  m_LabCamera->position(0, 20, -30);
  m_LabCamera->lookAt(0, 10, 0);
  m_LabCamera->activate(m_SysRender->getViewport());
  m_SysRender->setActiveCam(m_LabCamera->getOgreCam());

  // SETUP BASIC GUI
  m_Screen = m_SysGUI->createScreen("SCREEN_DEBUG", "debug",
    m_SysRender->getViewport());
  m_Layer = m_SysGUI->createLayer("LAYER_DEBUG", m_Screen);
  m_Layer->setVisible(false);

  // GUI CAPTION
  m_Caption = m_Layer->createCaption(7, 16, 16,
    "Kerberos Engine - Version " + str_Version);
  m_Caption->fixedWidth(true);
  m_CaptionBG = m_Layer->createRectangle(10, 10, 325, 20);
  m_CaptionBG->background_colour(Ogre::ColourValue(0.3, 0.1, 0.1, 0.8));

  // GUI TEXT - STATS AND SUCH
  m_DebugText = m_Layer->createMarkupText(7, 16, 46, "");
  m_DebugBG = m_Layer->createRectangle(10, 40, 325, 140);
  m_DebugBG->background_colour(Ogre::ColourValue(0.1, 0.1, 0.1, 0.8));

  i_ScreenShots = 0;
}

/*****************************************************************************
*****************************************************************************/

void Brain::cycleLab()
{
  if (f_DemoTime > 0)
  {
    if (m_Clock->msex() >= f_DemoTime)
    {
      b_Alive = false;
    }
  }

  handleLabInput();
  updateDebug();
}

/*****************************************************************************
*****************************************************************************/

void Brain::handleLabInput()
{
  if (m_SysInput->keyDown(OIS::KC_ESCAPE))
  {
    b_Alive = false;
  }

  if (m_SysInput->keyDown(OIS::KC_W)) { m_LabCamera->moveAbscissa(f_CamSpeed);  }
  if (m_SysInput->keyDown(OIS::KC_S)) { m_LabCamera->moveAbscissa(-f_CamSpeed); }
  if (m_SysInput->keyDown(OIS::KC_A)) { m_LabCamera->moveApplicate(f_CamSpeed); }
  if (m_SysInput->keyDown(OIS::KC_D)) { m_LabCamera->moveApplicate(-f_CamSpeed);}
  if (m_SysInput->keyDown(OIS::KC_Q)) { m_LabCamera->moveOrdinate(f_CamSpeed);  }
  if (m_SysInput->keyDown(OIS::KC_E)) { m_LabCamera->moveOrdinate(-f_CamSpeed); }

  m_LabCamera->orient(
    m_SysInput->getMouse()->getMouseState().Y.rel,
    m_SysInput->getMouse()->getMouseState().X.rel,
    0.0007f);
  
  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_F1))
  {
    m_SysPhysics->toggleDebug();
    m_SysWorld->toggleGrid();
    m_Layer->setVisible(!m_Layer->isVisible());

    f_InputDelay = 300;
  }

  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_SYSRQ))
  {
    Ogre::StringStream ss;
    ss << "screenshot_" << ++i_ScreenShots << ".png";
    m_SysRender->getWindow()->writeContentsToFile(ss.str());

    f_InputDelay = 500;
  }

  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_1))
  {
    if (!m_SysWorld->isPaused())
    {
      m_SysWorld->setWorldRate(1.0f);
      f_WorldRateTemp = 1.0f;

      f_InputDelay = 300;
    }
  }
  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_2))
  {
    if (!m_SysWorld->isPaused())
    {
      m_SysWorld->setWorldRate(0.2f);
      f_WorldRateTemp = 0.2f;

      f_InputDelay = 300;
    }
  }
  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_3))
  {
    if (!m_SysWorld->isPaused())
    {
      m_SysWorld->setWorldRate(0.1f);
      f_WorldRateTemp = 0.1f;

      f_InputDelay = 300;
    }
  }
  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_4))
  {
    if (!m_SysWorld->isPaused())
    {
      m_SysWorld->setWorldRate(0.01f);
      f_WorldRateTemp = 0.01f;

      f_InputDelay = 300;
    }
  }
  if (f_InputDelay <= 0 && m_SysInput->keyDown(OIS::KC_5))
  {
    m_SysWorld->pauseWorld();
    
    if (m_SysWorld->isPaused())
    {
      m_SysWorld->setWorldRate(0.0f);
    }
    else
    {
      m_SysWorld->setWorldRate(f_WorldRateTemp);
    }

    f_InputDelay = 300;
  }

  f_InputDelay -= d_DeltaTime;
}

/*****************************************************************************
*****************************************************************************/

void Brain::updateDebug()
{
  m_DebugText->text(
    "Time : " + m_Clock->msexString() +
    "\n" +
    "World time: " + m_SysWorld->getTimeString() +
    "\n" +
    "World rate: " + toString(m_SysWorld->getWorldRate()) +
    "\n" +
    "Ticks : " + toString(d_TickCount) +
    "\n" +
    "FPS : " + toString(m_SysRender->getWindow()->getLastFPS(), 1) +
    "\n" +
    "Batches : " + Ogre::StringConverter::toString(
    m_SysRender->getWindow()->getBatchCount())
  );
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/