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
* @file   krbSystemGUI.h
* @author Nathan Harris
* @date   17 December 2014
* @brief  GUI system
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbSystemGUI_h
#define krbSystemGUI_h

/*****************************************************************************
*****************************************************************************/

#include "systems/krbSystem.h"

#include "Gorilla/Gorilla.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Ogre
{
  class OverlaySystem;
  class SceneManager;
  class Viewport;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

//
//! \brief GUI system, utilizing Gorilla
//
class SystemGUI final : public System
{
public:
  SystemGUI(Config* config, Logger* log);
  ~SystemGUI();

  void init();
  void cycle();
  void halt();

  void connectOgre(Ogre::Viewport* viewport);

  void loadAtlas(string name);
  bool hasAtlas(string name);

  Gorilla::Screen* createScreen(
    string screen, string atlas, Ogre::Viewport* vp);

  Gorilla::ScreenRenderable* createWorldScreen(
    string screen, string atlas, Ogre::Viewport* vp);

  Gorilla::Layer* createLayer(string layer, string screen);
  Gorilla::Layer* createLayer(string layer, Gorilla::Screen* screen);

  // SETTERS

  // GETTERS
  Gorilla::Silverback* getSilverback();
  Gorilla::Screen* getScreen(string layer);
  Gorilla::Layer* getLayer(string layer, string screen);
  Gorilla::Layer* getLayer(string layer, Gorilla::Screen* screen);

private:
  void parseConfig();

  typedef struct Screen 
  {
    Gorilla::Screen* screen;
    map<string, Gorilla::Layer*> layers;
  } Screen;

  Ogre::OverlaySystem*  m_OverlaySystem;
  Ogre::SceneManager*   m_SceneManager;
  Ogre::Viewport*       m_Viewport;

protected:
  Gorilla::Silverback*  m_Silverback;
  vector<string>        vec_Atlas;
  map<string, Screen*>  map_Screens;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSSystemGUI_h

/***]EOF[*********************************************************************/