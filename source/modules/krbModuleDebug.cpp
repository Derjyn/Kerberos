///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbModuleDebug.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbCore.h"

#include "systems\krbSystemGUI.h"
#include "systems\krbSystemRender.h"
#include "systems\krbSystemWorld.h"

#include "modules\krbModuleDebug.h"
#include "modules\krbModuleCamera.h"

#include "Gorilla.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::ModuleDebug* Ogre::Singleton<Kerberos::ModuleDebug>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

ModuleDebug::ModuleDebug() {
  setName("DEBUG MODULE");

  bDebugToggle = false;

  fAlphaMod   = 0;
  fFadeDelta  = 0;
  dCurrTime   = 0;
}

ModuleDebug& ModuleDebug::singleton(void) { return (*msSingleton); }
ModuleDebug* ModuleDebug::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void ModuleDebug::init() {
  pSysGUI = SystemGUI::getSingletonPtr();
  pSysRender = SystemRender::getSingletonPtr();
  pSysWorld = SystemWorld::getSingletonPtr();

  pWorldTimer = pSysWorld->getWorldTimer();

  pModCamera = ModuleCamera::singletonPtr();
}

///////////////////////////////////////////////////////////////////////////////

void ModuleDebug::halt(void) {
}

///////////////////////////////////////////////////////////////////////////////

void ModuleDebug::update(void) {
  if (bDebugToggle) {
    std::stringstream ssCoreTime;
    ssCoreTime << "CORE TIME     : " <<
      pCoreTimer->Time.day << " days " << pCoreTimer->Time.hour << "hrs " <<
      pCoreTimer->Time.minute << "min " << pCoreTimer->Time.second << "sec ";
    pDebugCaptionCoreTime->text(ssCoreTime.str());

    std::stringstream ssWorldTime;
    ssWorldTime << "WORLD TIME    : " << 
      pSysWorld->getWorldTimeString();
    pDebugCaptionWorldTime->text(ssWorldTime.str());

    std::stringstream ssWorldRPS;
    ssWorldRPS << "WORLD RPS     : " << 
      pSysWorld->getWorldTPS();
    pDebugCaptionWorldRPS->text(ssWorldRPS.str());

    std::stringstream ssTickCount;
    ssTickCount << "TICK COUNT    : " <<
      int(Core::getSingletonPtr()->getLogicTicks());
    pDebugCaptionTickCount->text(ssTickCount.str());

    std::stringstream ssTickRate;
    ssTickRate << "TICK RATE     : " <<
      Core::getSingletonPtr()->getLogicTPS();
    pDebugCaptionTickRate->text(ssTickRate.str());

    std::stringstream ssCurFps;
    ssCurFps << "FPS CURRENT   : " << 
      pSysRender->getWindow()->getLastFPS();
    pDebugCaptionCurFPS->text(ssCurFps.str());

    std::stringstream ssAvgFps;
    ssAvgFps << "FPS AVERAGE   : " << 
      pSysRender->getWindow()->getAverageFPS();
    pDebugCaptionAvgFPS->text(ssAvgFps.str());

    std::stringstream ssBatchCnt;
    ssBatchCnt << "BATCH COUNT   : " << 
      pSysRender->getRenderer()->_getBatchCount();
    pDebugCaptionBatchCount->text(ssBatchCnt.str());

    pDebugCaptionActiveCamera->text(
      "ACITVE CAMERA : " + pModCamera->getActiveCameraName());
  }

  fadeDebugGUI();
}

///////////////////////////////////////////////////////////////////////////////
// CREATE A (BASIC) DEBUG GUI

void ModuleDebug::createDebugGUI(void) {
  pDebugScreen = pSysGUI->createScreen(
    pSysRender->getViewport(), "debug", "SCREEN_DEBUG");

  pDebugLayerHeader = pSysGUI->createLayer(
    "SCREEN_DEBUG", "LAYER_DEBUG");

  pDebugCaptionTitle = pDebugLayerHeader->createCaption(
    7, 10, 10, "Kerberos Engine Concept");

  pDebugCaptionCoreTime = pDebugLayerHeader->createCaption(
    7, 10, 30, "CORE TIME     : ");
  pDebugCaptionWorldTime = pDebugLayerHeader->createCaption(
    7, 10, 40, "WORLD TIME    : ");
  pDebugCaptionWorldRPS = pDebugLayerHeader->createCaption(
    7, 10, 50, "WORLD RPS     : ");

  pDebugCaptionTickCount = pDebugLayerHeader->createCaption(
    7, 10, 70, "TICK COUNT    : ");
  pDebugCaptionTickRate = pDebugLayerHeader->createCaption(
    7, 10, 80, "TICK RATE     : ");
  pDebugCaptionCurFPS = pDebugLayerHeader->createCaption(
    7, 10, 90, "FPS CURRENT   : ");
  pDebugCaptionAvgFPS = pDebugLayerHeader->createCaption(
    7, 10, 100, "FPS AVERAGE  : ");
  pDebugCaptionBatchCount = pDebugLayerHeader->createCaption(
    7, 10, 110, "BATCH COUNT  : ");

  pDebugCaptionActiveCamera = pDebugLayerHeader->createCaption(
    7, 10, 130, "ACTIVE CAMERA: ");

  pDebugCaptionTitle->fixedWidth(true);
  pDebugCaptionCoreTime->fixedWidth(true);
  pDebugCaptionWorldTime->fixedWidth(true);
  pDebugCaptionWorldRPS->fixedWidth(true);
  pDebugCaptionTickCount->fixedWidth(true);
  pDebugCaptionTickRate->fixedWidth(true);
  pDebugCaptionCurFPS->fixedWidth(true);
  pDebugCaptionAvgFPS->fixedWidth(true);
  pDebugCaptionBatchCount->fixedWidth(true);
  pDebugCaptionActiveCamera->fixedWidth(true);

  pDebugLayerHeader->setAlphaModifier(fAlphaMod);
}

///////////////////////////////////////////////////////////////////////////////

void ModuleDebug::toggleDebugGUI(void) {
  bDebugToggle = !bDebugToggle;
}

///////////////////////////////////////////////////////////////////////////////

void ModuleDebug::fadeDebugGUI(void) {
  double newTime = pCoreTimer->getMilliseconds();
  fFadeDelta = newTime - dCurrTime;

  if (bDebugToggle) {
    if (pDebugLayerHeader->getAlphaModifier() < 1.0) {
      fAlphaMod += fFadeDelta / 250;
      pDebugLayerHeader->setAlphaModifier(fAlphaMod);
    }
  }
  else {
    if (pDebugLayerHeader->getAlphaModifier() > 0.0) {
      fAlphaMod -= fFadeDelta / 300;
      pDebugLayerHeader->setAlphaModifier(fAlphaMod);
    }
  }

  dCurrTime = newTime;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////