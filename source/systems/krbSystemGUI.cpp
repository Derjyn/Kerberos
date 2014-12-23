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
* @file   krbSystemGUI.cpp
* @author Nathan Harris
* @date   17 December 2014
* @brief  GUI system
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystemGUI.h"
#include "core/krbConfig.h"
#include "core/krbClock.h"
#include "core/krbLogger.h"

#include "Gorilla/Gorilla.h"

/*****************************************************************************
*****************************************************************************/

namespace Kerberos
{

/*****************************************************************************
*****************************************************************************/

SystemGUI::SystemGUI(Config* config, Logger* log)
{
  str_Name  = "GUI";
  m_Config  = config;
  m_Log     = log;

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gorillas just came outta the mist :O");
}

SystemGUI::~SystemGUI()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Gorillas went back into the mist...");
}

/*****************************************************************************
*****************************************************************************/

void SystemGUI::init()
{
  m_Silverback = new Gorilla::Silverback();

  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Initialized :)");
}

void SystemGUI::cycle()
{
}

void SystemGUI::halt()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Halted :)");
}

/*****************************************************************************
*****************************************************************************/

void SystemGUI::parseConfig()
{
  m_Log->logMessage(m_Log->LVL_INFO, m_Log->MSG_SYSTEM,
    str_Name + ": Config parsed");
}

/*****************************************************************************
*****************************************************************************/

void SystemGUI::loadAtlas(string name) 
{
  m_Silverback->loadAtlas(name);
  vec_Atlas.push_back(name);
}

/*****************************************************************************
*****************************************************************************/

bool SystemGUI::hasAtlas(string name) 
{
  for (unsigned int i = 0; i < vec_Atlas.size(); i++) 
  {
    if (vec_Atlas[i] == name) 
    {
      return true;
    }
  }

  return false;
}

/*****************************************************************************
*****************************************************************************/

Gorilla::Screen* SystemGUI::createScreen(string name, string atlas, 
  Ogre::Viewport* vp)
{
  Screen* scr = new Screen();
  if (!hasAtlas(atlas)) 
  {
    loadAtlas(atlas);
  }

  if (map_Screens[name] == nullptr) 
  {
    scr->screen = m_Silverback->createScreen(vp, atlas);
    map_Screens[name] = scr;
  }

  return scr->screen;
}

Gorilla::Layer* SystemGUI::createLayer(std::string layer, std::string screen)
{
  Gorilla::Layer* lyr = getLayer(layer, screen);

  if (lyr != nullptr) 
  {
    return lyr;
  }

  if (getScreen(screen) != nullptr) 
  {
    map_Screens[screen]->layers[layer] = 
      getScreen(screen)->createLayer(map_Screens[screen]->layers.size());

    return map_Screens[screen]->layers[layer];
  }

  return nullptr;
}

Gorilla::Layer* SystemGUI::createLayer(string layer, Gorilla::Screen* screen)
{
  Gorilla::Layer* lyr = getLayer(layer, screen);

  if (lyr != nullptr) 
  {
    return lyr;
  }

  map<string, Screen*>::iterator i;
  for (i = map_Screens.begin(); i != map_Screens.end(); i++) 
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

Gorilla::Silverback* SystemGUI::getSilverback()
{
  return m_Silverback;
}

Gorilla::Screen* SystemGUI::getScreen(string name)
{
  if (map_Screens[name] != nullptr) 
  {
    return map_Screens[name]->screen;
  }

  return nullptr;
}

Gorilla::Layer* SystemGUI::getLayer(string layer, string screen)
{
  if (map_Screens[screen] != nullptr) 
  {
    return map_Screens[screen]->layers[layer];
  }

  return nullptr;
}

Gorilla::Layer* SystemGUI::getLayer(std::string layer, Gorilla::Screen* screen)
{
  map<std::string, Screen*>::iterator i;

  for (i = map_Screens.begin(); i != map_Screens.end(); i++) 
  {
    return getLayer(layer, i->first);
  }

  return nullptr;
}

/*****************************************************************************
*****************************************************************************/

void SystemGUI::connectOgre(Ogre::Viewport* viewport)
{
  m_Viewport = viewport;
}

/*****************************************************************************
*****************************************************************************/

}

/***]EOF[*********************************************************************/