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
#include "entities\krbEntityCamera.h"

#include "Ogre3D\OgreResourceGroupManager.h"
#include "Ogre3D\OgreWindowEventUtilities.h"

#include "Gorilla\Gorilla.h"

#include "Bullet\LinearMath\btScalar.h" //! \bug Include for version. Bleh.

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

Core::Core()
{
  // INITIALIZE CONFIG AND TIMER
  pConfig = new Config("Config.kpf");
  pTimer = new Timer(false);

  // SETUP LOGGING
  pLog = new Logger(
    pConfig->getString("CORE", "LogFile"),
    pConfig->getString("CORE", "LogTitle"),
    pConfig->getInt("CORE", "LogLevel"));

  //! \todo Move the version stuff elsewhere
  // LOG KERBEROS VERSION
  std::stringstream ssKRBVer;
  ssKRBVer << 
    KRB_VERSION_MAJOR << "." <<
    KRB_VERSION_MINOR << "." <<
    KRB_VERSION_PATCH <<
    " (" << KRB_VERSION_NAME ")";
  strVersion = ssKRBVer.str();

  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE,
    "Kerberos version : " + strVersion);

  // LOG OGRE VERSION
  std::stringstream ssOgreVer;
  ssOgreVer << 
    OGRE_VERSION_MAJOR << "." <<
    OGRE_VERSION_MINOR << "." <<
    OGRE_VERSION_PATCH <<
    " (" << OGRE_VERSION_NAME ")";
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, 
    "Ogre version : " + ssOgreVer.str());

  // LOG OIS VERSION
  std::stringstream ssOISVer;
  ssOISVer <<
    OIS_VERSION_MAJOR << "." <<
    OIS_VERSION_MINOR << "." <<
    OIS_VERSION_PATCH;
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, 
    "OIS version : " + ssOISVer.str());

  // LOG BULLET VERSION
  std::stringstream ssBulletVer;
  ssBulletVer << BT_BULLET_VERSION;
  std::string ssBullet = ssBulletVer.str();
  std::string::iterator it;
  it = ssBullet.insert(ssBullet.begin() + 1, '.');
  it = ssBullet.insert(ssBullet.begin() + 3, '.');
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE,
    "Bullet version : " + ssBullet);

  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Loaded config : " +
    pConfig->getFileName());

  // SETUP VARIABLES
  dAccumulator  = 0.0;
  dCounter      = 0.0;
  dDeltaTime    = 0.0;
  dNewTime      = 0.0;
  dCurrentTime  = 0.0;
  dTimeLimit    = 0.0;
  iTickCount    = 0;

  bActive       = false;
}

Core::~Core()
{
  delete pLog;
  delete pTimer;
  delete pConfig;  

}

/*****************************************************************************
*****************************************************************************/

void Core::start()
{
  pLog->logSection("STARTUP");
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Core starting");

  // CREATE OGRE ROOT AND LOG INFO
  pOgre = new Ogre::Root("", "", pConfig->getString("RENDER", "LogFile"));
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Set Ogre log to: " +
    pConfig->getString("RENDER", "LogFile"));

  // CREATE RESOURCE MANAGER AND LOAD RESOURCES
  pResMgr = Ogre::ResourceGroupManager::getSingletonPtr();
  loadResources();

  // INIT RENDER SYSTEM
  pSysRender = new RenderSystem(pConfig, pLog, pTimer, pOgre);
  pSysRender->start();

  // INIT INPUT SYSTEM
  pSysInput = new InputSystem(pConfig, pLog, pTimer, pSysRender->getWindow());
  pSysInput->start();

  // INIT GUI SYSTEM
  pSysGUI = new GUISystem(pConfig, pLog, pTimer, pSysRender->getViewport());
  pSysGUI->start();

  // INIT PHYSICS SYSTEM
  pSysPhysics = new PhysicsSystem(
    pConfig, pLog, pTimer, pSysRender->getSceneManager());
  pSysPhysics->start();

  // INIT THE WORLD SYSTEM
  pSysWorld = new WorldSystem(pConfig, pLog, pTimer, 
    pSysRender->getSceneManager(), 
    pSysPhysics->getBulletWorld(),
    pSysRender->getViewport());
  pSysWorld->start();

  // INIT AI SYSTEM
  pSysAI = new AISystem(pConfig, pLog, pTimer);
  pSysAI->start();

  // INIT SOUND SYSTEM
  pSysSound = new SoundSystem(pConfig, pLog, pTimer);
  pSysSound->start();

  // SETUP SOME CORE VARIABLES
  dTickRate = 1000.0 / pConfig->getInt("CORE", "TickRate");
  dLogicRate = 1.0 / dTickRate;
  dTimeLimit = pConfig->getInt("CORE", "TimeLimit") * 1000.0;

  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Core startup complete");

  // TEMP: CREATE A DEMO SCENE
  createDemo();

  // STARTUP DONE, WE'RE LIVE
  bActive = true;
}

/*****************************************************************************
*****************************************************************************/

void Core::cycle()
{
  pTimer->resetClock();
  pTimer->resetTimer();

  while (bActive)
  {
    Ogre::WindowEventUtilities::messagePump();

    dNewTime = pTimer->timerElapsed();
    dDeltaTime = dNewTime - dCurrentTime;

    if (dDeltaTime <= 0.0)
    {
      continue;
    }

    dCurrentTime = dNewTime;
    dAccumulator += dDeltaTime;

    while (dAccumulator >= dTickRate)
    {
      pTimer->cycle(1.0f);

      // 1. UPDATE GAME/DEMO
      updateDemo();                   
      // 2. USER INTERACTION
      pSysInput->cycle();
      // 3. WORLD RESPONSE AND EVENTS
      pSysWorld->cycle(); 
      // 4. PHYSICS DYNAMICS
      pSysPhysics->cycle(dDeltaTime, pSysWorld->getTimeRate());
      // 5. SOUND EVENTS
      pSysSound->cycle();
      // 6. AI LOGIC AND REACTIONS
      pSysAI->cycle();
      // 7. GUI UPDATES
      pSysGUI->cycle();               

      dCounter += dTickRate;
      dAccumulator -= dTickRate;      

      iTickCount++;
    }

    const double dAlpha = dAccumulator / dTickRate;

    // 8. RENDER IT.
    pSysRender->cycle();              
  }
}

/*****************************************************************************
*****************************************************************************/

void Core::stop()
{
  std::string tempClock = pTimer->getClockString();
  std::string tempTick = toString(iTickCount);
  std::string tempEnts = toString(pSysWorld->getTotalEntities());
  std::string tempFPS = toString(pSysRender->getWindow()->getAverageFPS());

  pLog->logSection("SHUTDOWN");
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Core stopping");

  // STOP SYSTEMS
  pSysSound->stop();
  delete pSysSound;
  pSysAI->stop();
  delete pSysAI;
  pSysWorld->stop();
  delete pSysWorld;
  pSysPhysics->stop();
  delete pSysPhysics;
  pSysGUI->stop();
  delete pSysGUI;
  pSysInput->stop();
  delete pSysInput;
  pSysRender->stop();
  delete pSysRender;

  //delete pOgre; // \bug Error on destruction

  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, 
    "Core shutdown complete");

  // LOG SOME STATS
  pLog->logSection("STATS");
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_STAT, 
    "Time total: " + tempClock);
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_STAT, 
    "Ticks: " + tempTick);
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_STAT, 
    "Entities created: " + tempEnts);
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_STAT,
    "Average FPS: " + tempFPS);

  pLog->closeLog();
}

/*****************************************************************************
*****************************************************************************/

void Core::loadResources()
{
  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, "Loading resources...");  
  
  pResMgr->addResourceLocation("assets/scripts", "FileSystem", "SCRIPTS");
  pResMgr->addResourceLocation("assets/gui", "FileSystem", "GUI");
  pResMgr->addResourceLocation("assets/textures", "FileSystem", "TEXTURES");
  pResMgr->addResourceLocation("assets/materials", "FileSystem", "MATERIALS");
  pResMgr->addResourceLocation("assets/meshes", "FileSystem", "MESHES");

  pResMgr->initialiseAllResourceGroups();

  pLog->logMessage(pLog->LOG_INFO, pLog->MSG_CORE, 
    "Resources loaded and initialized");
}

/*****************************************************************************
*****************************************************************************/

void Core::toggleDebug()
{
  pDebugLayer->setVisible(!pDebugLayer->isVisible());
  pSysPhysics->toggleDebug();
}

void Core::createDemo()
{
  pInputTimer = new Timer(true);
  iInputDelay = 250;

  // CREATE A REFERENCE GRID
  pSysWorld->createGrid(
    "WORLD_GRID", 4.0f, 250,  // REF: GONNA SCALE EVERYTHING 4X FOR BULLET
    Color(0.2f, 0.2f, 0.2f, 1.0f), 
    Color(0.f, 0.f, 0.f, 1.0f),
    Color(0.f, 0.f, 0.f, 0.f));

  pDebugScreen = pSysGUI->createScreen(
    pSysRender->getViewport(), "debug", "SCREEN_DEBUG");
  pDebugLayer = pSysGUI->createLayer(pDebugScreen, "LAYER_DEBUG");
  pDebugLayer->setVisible(false);

  // CAPTION
  pDebugCaption = pDebugLayer->createCaption(7, 16, 16,
    "Kerberos Engine - Version " + strVersion);
  pDebugCaption->fixedWidth(true);
  pDebugCaptionBG = pDebugLayer->createRectangle(10, 10, 320, 20);
  pDebugCaptionBG->background_colour(toOgre(Color(0.45f, 0.1f, 0.1f, 0.9f)));

  // STATS AND SUCH
  pDebugText = pDebugLayer->createMarkupText(7, 16, 46, "");
  pDebugText->background(Ogre::ColourValue::ZERO);
  pDebugTextBG = pDebugLayer->createRectangle(10, 40, 320, 140);
  pDebugTextBG->background_colour(toOgre(Color(0.f, 0.f, 0.f, 0.8f)));

  // CURSOR
  pCursorLayer = pSysGUI->createLayer(pDebugScreen, "LAYER_CURSOR");
  pCursorLayer->setVisible(false);
  pCursorRect = pCursorLayer->createRectangle(0, 0, 16, 16);
  pCursorRect->background_image("cursor");
  
  // CREATE A CAMERA
  pDemoCam = pSysWorld->addCamera("DEMO", true);
  pDemoCam->positionCamera(100, 100, 100);
  pDemoCam->lookAt(0, 0, 0);  
  pDemoCam->setActive(pSysRender->getViewport());
}

void Core::updateDemo()
{  
  // TIME LIMIT
  if (dTimeLimit > 0)
  {
    if (pTimer->timerElapsed() > dTimeLimit)
    {
      bActive = false;
    }
  }

  // CAMERA - MOVE ABOUT IF CURSOR ISN'T ACTIVE
  if (!pCursorLayer->isVisible())
  {
    pDemoCam->orientCamera(
      pSysInput->getMouse()->getMouseState().Y.rel,
      pSysInput->getMouse()->getMouseState().X.rel,
      0.001f);

    if (pSysInput->keyDown(OIS::KC_W)) { pDemoCam->moveCamAbscissa(0.5f); }
    if (pSysInput->keyDown(OIS::KC_S)) { pDemoCam->moveCamAbscissa(-0.5f); }
    if (pSysInput->keyDown(OIS::KC_A)) { pDemoCam->moveCamApplicate(0.5f); }
    if (pSysInput->keyDown(OIS::KC_D)) { pDemoCam->moveCamApplicate(-0.5f); }
    if (pSysInput->keyDown(OIS::KC_Q)) { pDemoCam->moveCamOrdinate(0.5f); }
    if (pSysInput->keyDown(OIS::KC_E)) { pDemoCam->moveCamOrdinate(-0.5f); }
  }

  // INPUT
  if (pSysInput->keyDown(OIS::KC_ESCAPE))
  {
    bActive = false;
  }
  if (pInputTimer->timerElapsed() > iInputDelay && 
    pSysInput->keyDown(OIS::KC_GRAVE))
  {
    toggleDebug();
    pInputTimer->resetTimer();
  }
  if (pInputTimer->timerElapsed() > iInputDelay && 
    pSysInput->keyDown(OIS::KC_TAB))
  {
    pCursorLayer->setVisible(!pCursorLayer->isVisible());
    pInputTimer->resetTimer();
  }

  if (pSysInput->keyDown(OIS::KC_P))
  {
    pSysWorld->deleteCamera("DUMMY");
  }

  // UPDATE CURSOR, IF VISIBLE
  if (pCursorLayer->isVisible())
  {
    pCursorRect->position(
      pSysInput->getMouse()->getMouseState().X.abs,
      pSysInput->getMouse()->getMouseState().Y.abs);
  }

  // UPDATE DEBUG UI

  if (pDebugLayer->isVisible())
  {
    pDebugText->text(
      "Time : " + pTimer->getClockString() +
      "\n" +
      "World time : " + pSysWorld->getTimeString() +
      "\n" +
      "Ticks : " + toString(iTickCount) +
      "\n" +
      "Entities : " + toString(pSysWorld->getTotalEntities()) +
      "\n" +
      "Position : " + toString(pDemoCam->getPosition()) +
      "\n" +
      "FPS : " + toString(pSysRender->getWindow()->getLastFPS(), 1) +
      "\n" +
      "Batches : " + Ogre::StringConverter::toString(pSysRender->getWindow()->getBatchCount())
    );
  }
}

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos

/***]EOF[*********************************************************************/