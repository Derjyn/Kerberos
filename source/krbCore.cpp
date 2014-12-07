///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbCore.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbCore.h"

#include "systems\krbSystemFactory.h"
#include "modules\krbModuleFactory.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::Core* Ogre::Singleton<Kerberos::Core>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

Core::Core() {
  pTimer = new Timer(false);
  pConfig = new INIReader("Kerberos.ini");
  pLogger = new Logger(pTimer);

  pLogger->CreateLog(
    pConfig->Get("Core", "LogFile", "debug/Kerberos.log"),
    pConfig->Get("Core", "LogTitle", "Kerberos Debug Log"),
    pConfig->GetINT("Core", "LogLevel", 0));

  dDeltaTime = 0;
  dAccumulator = 0;
  dCurrentTime = 0;
  dNewTime = 0;

  dTimePerLogicTick = 0;
  dLogicTicks = 0;

  fInputCounter = 250.0;
  fInputRate = 1000.0 / pConfig->GetReal("Input", "InputRate", 4.0);

  iDemoTime = 1000 * pConfig->GetInteger("Core", "DemoTime", 10);

  bIsActive = false;
}

Core& Core::singleton(void) { return (*msSingleton); }
Core* Core::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////
// INIT SYSTEM

void Core::init(void) {
  // SETUP TIMES AND SUCH
  dTimePerLogicTick = 1000.0 / pConfig->GetReal("Core", "LogicRate", 20.0);  
  
  pLogger->LogSection("KERBEROS INITIALIZATION");
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "ENGINE INITIALIZING");

  // INITIALIZE OGRE ROOT AND LOAD RESOURCES
  pRoot = new Ogre::Root("", "",
    pConfig->Get("Render", "OgreLogFile", "debug/Ogre.log"));
  loadResources();

  // ADD AND INIT SYSTEMS
  pSysFactory = new SystemFactory(pLogger, pTimer, pConfig);
  primeSystems();

  // ADD AND INIT MODULES
  pModFactory = new ModuleFactory(pLogger, pTimer, pConfig);
  primeModules();

  // CREATE DEBUG UI AND HUD 
  initDebug();
  createHUD();

  // CREATE WORLD
  pSysWorld->createWorld();

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "ENGINE INITIALIZED"); 

  bIsActive = true;

  pTimer->reset();
  pSysWorld->resetTimer();
}

///////////////////////////////////////////////////////////////////////////////
// LOAD RESOURCES

void Core::loadResources(void) {
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "LOADING RESOURCES");

  Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(
    "assets/gui", "FileSystem", "GUI");
  Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(
    "assets/textures", "FileSystem", "TEXTURES");
  Ogre::ResourceGroupManager::getSingletonPtr()->addResourceLocation(
    "assets/materials", "FileSystem", "MATERIALS");

  Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "RESOURCES LOADED");
}

///////////////////////////////////////////////////////////////////////////////
// PRIME SYSTEMS

void Core::primeSystems(void) {
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "PRIMING SYSTEMS");

  pSysRender = dynamic_cast<SystemRender*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_RENDER));
  pSysFactory->initSystem(pSysFactory->SYSTEM_RENDER);

  pSysScript = dynamic_cast<SystemScript*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_SCRIPT));
  pSysFactory->initSystem(pSysFactory->SYSTEM_SCRIPT);

  pSysInput = dynamic_cast<SystemInput*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_INPUT));
  pSysInput->setWindow(pSysRender->getWindow());
  pSysFactory->initSystem(pSysFactory->SYSTEM_INPUT);

  pSysAudio = dynamic_cast<SystemAudio*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_AUDIO));
  pSysFactory->initSystem(pSysFactory->SYSTEM_AUDIO);

  pSysGUI = dynamic_cast<SystemGUI*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_GUI));
  pSysFactory->initSystem(pSysFactory->SYSTEM_GUI);

  pSysWorld = dynamic_cast<SystemWorld*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_WORLD));
  pSysFactory->initSystem(pSysFactory->SYSTEM_WORLD);

  pSysPhysics = dynamic_cast<SystemPhysics*>(
    pSysFactory->addSystem(pSysFactory->SYSTEM_PHYSICS));
  pSysFactory->initSystem(pSysFactory->SYSTEM_PHYSICS);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "SYSTEMS PRIMED");
}

///////////////////////////////////////////////////////////////////////////////
// PRIME MODULES

void Core::primeModules(void) {
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "PRIMING MODULES");

  pModCamera = dynamic_cast<ModuleCamera*>(
    pModFactory->addModule(pModFactory->MODULE_CAMERA));
  pModFactory->initModule(pModFactory->MODULE_CAMERA);

  pModDebug = dynamic_cast<ModuleDebug*>(
    pModFactory->addModule(pModFactory->MODULE_DEBUG));
  pModFactory->initModule(pModFactory->MODULE_DEBUG);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "MODULES PRIMED");
}

///////////////////////////////////////////////////////////////////////////////

void Core::initDebug(void) {
  pModDebug->createDebugGUI();
}

///////////////////////////////////////////////////////////////////////////////
// CREATE A (BASIC) HUD

void Core::createHUD(void) {
  pScreenHUD = pSysGUI->createScreen(
    pSysRender->getViewport(), "debug", "SCREEN_HUD");

  pLayerHUD = pSysGUI->createLayer("SCREEN_HUD", "LAYER_HUD");
  pLayerCursor = pSysGUI->createLayer("SCREEN_HUD", "LAYER_CURSOR");

  pSysInput->setWindowExtents(
    pSysRender->getWindow()->getWidth(),
    pSysRender->getWindow()->getHeight());

  pRectCursor = pLayerCursor->createRectangle(64, 64, 16, 16);
  pRectCursor->background_image("cursor");
  pLayerCursor->hide();
}

///////////////////////////////////////////////////////////////////////////////
// UPDATE

void Core::update(void) {
  while (bIsActive) {
    Ogre::WindowEventUtilities::messagePump();

    dNewTime = pTimer->getMilliseconds();
    dDeltaTime = dNewTime - dCurrentTime;

    if (dDeltaTime <= 0.0) {
      continue;
    }

    dCurrentTime = dNewTime;
    dAccumulator += dDeltaTime;

    while (dAccumulator >= dTimePerLogicTick) {
      handleLogic();

      dAccumulator -= dTimePerLogicTick;
    }

    pSysRender->render();
  }
}

///////////////////////////////////////////////////////////////////////////////
// HANDLE LOGIC CYCLE

void Core::handleLogic(void) {
  if (iDemoTime != 0) {
    if (pTimer->getMilliseconds() >= iDemoTime) {
      bIsActive = false;
    }
  }

  if (pSysRender->getWindow()->isClosed()) {
    bIsActive = false;
  }

  handleInput();

  pModFactory->updateModule(pModFactory->MODULE_CAMERA);
  pModFactory->updateModule(pModFactory->MODULE_DEBUG);

  updateHUD();

  pTimer->runClock(1.0);
  pSysWorld->advanceTime();

  dLogicTicks++;
}

///////////////////////////////////////////////////////////////////////////////
// GET LOGIC TPS

double Core::getLogicTPS(void) {
  return dLogicTicks / (pTimer->getMilliseconds() / 1000.0);
}

///////////////////////////////////////////////////////////////////////////////
// HANDLE INPUT

void Core::handleInput(void) {
  if (fInputCounter < 0.0f && pSysInput->isKeyReleased(OIS::KC_ESCAPE)) {
    bIsActive = false;
  } 
  else if (fInputCounter < 0.0f && pSysInput->isKeyReleased(OIS::KC_SPACE)) {
    pSysWorld->getWorldTimer()->toggleClockPause();

    fInputCounter = 500.0f;
  }
  else if (fInputCounter < 0.0f && pSysInput->isKeyReleased(OIS::KC_GRAVE)) {
    pModDebug->toggleDebugGUI();

    fInputCounter = 500.0f;
  }
  else if (fInputCounter < 0.0f && pSysInput->isKeyReleased(OIS::KC_1)) {
    pModCamera->activateCamera("DEFAULT", pSysRender->getViewport());

    fInputCounter = 500.0f;
  }
  else if (fInputCounter < 0.0f && pSysInput->isKeyReleased(OIS::KC_2)) {
    pModCamera->activateCamera("WORLD", pSysRender->getViewport());

    fInputCounter = 500.0f;
  }

  pSysInput->capture();

  fInputCounter -= fInputRate;
}


///////////////////////////////////////////////////////////////////////////////
// UPDATE HUD

void Core::updateHUD(void) {
  if (pModDebug->isDebugOn()) {
    pLayerCursor->show();

    pRectCursor->position(
      pSysInput->getMouse()->getMouseState().X.abs,
      pSysInput->getMouse()->getMouseState().Y.abs);
  }
  else {
    pLayerCursor->hide();
  }
}

///////////////////////////////////////////////////////////////////////////////
// REMOVE MODULES

void Core::removeModules(void) {
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "REMOVING MODULES");

  pModFactory->removeModule(pModFactory->MODULE_DEBUG);
  pModFactory->removeModule(pModFactory->MODULE_CAMERA);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "MODULES REMOVED");
}

///////////////////////////////////////////////////////////////////////////////
// HALT SYSTEMS

void Core::haltSystems(void) {
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "HALTING SYSTEMS");

  pSysFactory->haltSystem(pSysFactory->SYSTEM_PHYSICS);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_WORLD);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_GUI);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_AUDIO);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_INPUT);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_SCRIPT);
  pSysFactory->haltSystem(pSysFactory->SYSTEM_RENDER);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "SYSTEMS HALTED");
}

///////////////////////////////////////////////////////////////////////////////
// HALT

void Core::halt(void) {
  bIsActive = false;

  pLogger->LogSection("KERBEROS SHUTDOWN");
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "ENGINE HALTING");

  // SHUT EVERYTHING DOWN
  removeModules();

  std::string tmpWorldTime = pSysWorld->getWorldTimeString();
  double dWorldRPS = pSysWorld->getWorldTPS();
  std::string tmpBestFPS = Ogre::StringConverter::toString(
    pSysRender->getWindow()->getBestFPS());
  std::string tmpWorstFPS = Ogre::StringConverter::toString(
    pSysRender->getWindow()->getWorstFPS());
  std::string tmpAvgFPS = Ogre::StringConverter::toString(
    pSysRender->getWindow()->getAverageFPS());

  haltSystems();

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_CORE,
    "ENGINE HALTED");

  // LOG SOME STATS
  pLogger->LogSection("KERBEROS STATISTICS");

  std::string tempString;

  tempString = std::to_string(pTimer->Time.day) + " days ";
  tempString += std::to_string(pTimer->Time.hour) + "hrs ";
  tempString += std::to_string(pTimer->Time.minute) + "min ";
  tempString += std::to_string(pTimer->Time.second) + "sec ";
  tempString += std::to_string(int(pTimer->Time.millisec)) + "ms";
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "TOTAL TIME: " + tempString);

  tempString = std::to_string(int(dLogicTicks));
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "TOTAL LOGIC TICKS: " + tempString + " TICKS");
  double dLogicRPS = dLogicTicks / (pTimer->getMilliseconds() / 1000);
  tempString = Ogre::StringConverter::toString(dLogicRPS);
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "LOGIC RPS (AVERAGE): " + tempString);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "WORLD TIME: " + tmpWorldTime);
  tempString = Ogre::StringConverter::toString(dWorldRPS);
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "WORLD RPS (AVERAGE): " + tempString);

  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "FPS AVERAGE: " + tmpAvgFPS);
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "FPS BEST: " + tmpBestFPS);
  pLogger->LogMessage(pLogger->LOG_INFO, pLogger->MSG_STAT,
    "FPS WORST: " + tmpWorstFPS);

  pLogger->CloseLog();

  delete pRoot;
  delete pTimer;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////