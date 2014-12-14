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
* @file   krbGUISystem.h
* @author Nathan Harris
* @date   13 December 2014
* @brief  Handles GUI related functions.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbGUISystem_h
#define krbGUISystem_h

/*****************************************************************************
*****************************************************************************/

#include "..\krbSystem.h"

#include <string>
#include <map>
#include <vector>

/*****************************************************************************
*****************************************************************************/

namespace Ogre 
{
  class OverlaySystem;
  class SceneManager;
  class Viewport;
}

namespace Gorilla
{
  class Caption;
  class Layer;
  class MarkupText;
  class Screen;
  class Silverback;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class GUISystem final : public System
{
public:
  GUISystem(Config* config, Logger* log, Timer* timer, Ogre::Viewport* vp);
  ~GUISystem();

  void start(void);
  void cycle(void);
  void stop(void);

  void loadAtlas(std::string name);
  bool hasAtlas(std::string name);

  Gorilla::Screen* createScreen(Ogre::Viewport* vp, std::string atlas, std::string name);
  Gorilla::Layer* createLayer(std::string screen, std::string layer);
  Gorilla::Layer* createLayer(Gorilla::Screen* Screen, std::string layer);

  // GETTERS
  Gorilla::Silverback* getSilverback();
  Gorilla::Screen* getScreen(std::string name);
  Gorilla::Layer* getLayer(std::string screen, std::string layer);
  Gorilla::Layer* getLayer(Gorilla::Screen* screen, std::string layer);

private:
  typedef struct Screen 
  {
    Gorilla::Screen* screen;
    std::map<std::string, Gorilla::Layer*> layers;
  } Screen;

  Ogre::OverlaySystem* pOverlaySystem;
  Ogre::SceneManager* pSceneManager;
  Ogre::Viewport* pViewport;

protected:
  Gorilla::Silverback* pSilverback;
  std::vector<std::string> vAtlas;
  std::map<std::string, Screen*> mScreens;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbGUISystem_h

/***]EOF[*********************************************************************/