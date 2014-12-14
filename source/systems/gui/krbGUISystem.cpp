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

/**
* @file   krbGUISystem.cpp
* @author Nathan Harris
* @date   13 December 2014
* @brief  Handles GUI related functions.
*/

/*****************************************************************************
*****************************************************************************/

#include "core\krbLogger.h"

#include "systems\gui\krbGUISystem.h"

#include "Gorilla\Gorilla.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

GUISystem::GUISystem(Config* config, Logger* log, Timer* timer, 
  Ogre::Viewport* vp)
{
  setName("GUI system");

  pConfig = config;
  pLog = log;
  pTimer = timer;
  pViewport = vp;

  logCreation();
}

GUISystem::~GUISystem()
{
  delete pSilverback;

  logDestruction();
}

/*****************************************************************************
*****************************************************************************/

void GUISystem::start()
{
  pSilverback = new Gorilla::Silverback();

  logStart();
}

void GUISystem::cycle()
{
}

void GUISystem::stop()
{
  logStop();
}

/*****************************************************************************
*****************************************************************************/

bool GUISystem::hasAtlas(std::string name) 
{
  for (unsigned int i = 0; i < vAtlas.size(); i++) 
  {
    if (vAtlas[i] == name) 
    {
      return true;
    }
  }

  return false;
}

/*****************************************************************************
*****************************************************************************/

void GUISystem::loadAtlas(std::string name) 
{
  pSilverback->loadAtlas(name);
  vAtlas.push_back(name);
}

/*****************************************************************************
*****************************************************************************/

Gorilla::Screen* GUISystem::createScreen(
  Ogre::Viewport* vp, std::string atlas, std::string name)
{
  Screen* scr = new Screen();
  if (!hasAtlas(atlas)) 
  {
    loadAtlas(atlas);
  }

  if (mScreens[name] == nullptr) 
  {
    scr->screen = pSilverback->createScreen(vp, atlas);
    mScreens[name] = scr;
  }

  return scr->screen;
}

Gorilla::Layer* GUISystem::createLayer(std::string screen, std::string layer)
{
  Gorilla::Layer* lyr = getLayer(screen, layer);

  if (lyr != nullptr) 
  {
    return lyr;
  }

  if (getScreen(screen) != nullptr) 
  {
    mScreens[screen]->layers[layer] = 
      getScreen(screen)->createLayer(mScreens[screen]->layers.size());
    return mScreens[screen]->layers[layer];
  }

  return nullptr;
}

Gorilla::Layer* GUISystem::createLayer(Gorilla::Screen* screen, std::string layer)
{
  Gorilla::Layer* lyr = getLayer(screen, layer);

  if (lyr != nullptr) 
  {
    return lyr;
  }

  std::map<std::string, Screen*>::iterator i;
  for (i = mScreens.begin(); i != mScreens.end(); i++) 
  {
    if (i->second->screen == screen) 
    {
      i->second->layers[layer] = 
        i->second->screen->createLayer(i->second->layers.size());

      return i->second->layers[layer];
    }
  }

  return nullptr;
}

/*****************************************************************************
*****************************************************************************/

Gorilla::Silverback* GUISystem::getSilverback()
{
  return pSilverback;
}

Gorilla::Screen* GUISystem::getScreen(std::string name)
{
  if (mScreens[name] != nullptr) 
  {
    return mScreens[name]->screen;
  }

  return nullptr;
}

Gorilla::Layer* GUISystem::getLayer(std::string screen, std::string layer)
{
  if (mScreens[screen] != nullptr) 
  {
    return mScreens[screen]->layers[layer];
  }

  return nullptr;
}

Gorilla::Layer* GUISystem::getLayer(Gorilla::Screen* screen, std::string layer)
{
  std::map<std::string, Screen*>::iterator i;

  for (i = mScreens.begin(); i != mScreens.end(); i++) 
  {
    return getLayer(i->first, layer);
  }

  return nullptr;
}

/*****************************************************************************
*****************************************************************************/

}       // namepsace Kerberos

/***]EOF[*********************************************************************/