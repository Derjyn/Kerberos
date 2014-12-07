#pragma once

#ifndef krbSystemGUI_H
#define krbSystemGUI_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemGUI.h
//  UPDATED : 12/04/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbSystem.h"

#include "Gorilla.h"

///////////////////////////////////////////////////////////////////////////////

namespace Gorilla {
  class Layer; 
  class Rectangle;
  class Screen;
  class Silverback;
}

///////////////////////////////////////////////////////////////////////////////

namespace Ogre {
  class OverlaySystem;
  class SceneManager;
  class Viewport;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

class SystemGUI : public System, public Ogre::Singleton<SystemGUI> {
public:
  SystemGUI();
  static SystemGUI &singleton(void);
  static SystemGUI *singletonPtr(void);

  void loadAtlas(std::string name);
  bool hasAtlas(std::string name);

  Gorilla::Screen *createScreen(Ogre::Viewport* vp, std::string atlas, std::string name);
  Gorilla::Layer *createLayer(std::string screen, std::string layer);
  Gorilla::Layer *createLayer(Gorilla::Screen* Screen, std::string layer);

  // GETTERS
  Gorilla::Silverback *getSilverback();
  Gorilla::Screen *getScreen(std::string name);
  Gorilla::Layer *getLayer(std::string screen, std::string layer);
  Gorilla::Layer *getLayer(Gorilla::Screen* screen, std::string layer);

private:
  friend class SystemFactory;

  typedef struct Screen {
    Gorilla::Screen *screen;
    std::map<std::string, Gorilla::Layer*> layers;
  } Screen;

  typedef struct Button {
    Gorilla::Rectangle* background;
    std::string baseImage;
    std::string hoverImage;

  public:
    void hover(bool value) {
      if (value) {
        background->background_image(hoverImage);
      }
      else {
        background->background_image(baseImage);
      }
    };
  } Button;

  Ogre::OverlaySystem *pOverlaySystem;
  Ogre::SceneManager *pSceneManager;
  Ogre::Viewport *pViewport;

protected:
  void init(void);
  void halt(void);

  Gorilla::Silverback *pSilverback;
  std::vector<std::string> vAtlas;
  std::map<std::string, Screen*> mScreens;
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif