///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemGUI.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "systems/krbSystemGUI.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::SystemGUI* Ogre::Singleton<Kerberos::SystemGUI>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

SystemGUI::SystemGUI() {
  setName("SYSTEM GUI");
}

SystemGUI& SystemGUI::singleton(void) { return (*msSingleton); }
SystemGUI* SystemGUI::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void SystemGUI::init(void) {
  pSilverback = new Gorilla::Silverback();
}

///////////////////////////////////////////////////////////////////////////////

void SystemGUI::halt(void) {
  delete pSilverback;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Silverback* SystemGUI::getSilverback() {
  return pSilverback;
}

///////////////////////////////////////////////////////////////////////////////

bool SystemGUI::hasAtlas(std::string name) {
  for (unsigned int i = 0; i < vAtlas.size(); i++) {
    if (vAtlas[i] == name) {
      return true;
    }
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////

void SystemGUI::loadAtlas(std::string name) {
  pSilverback->loadAtlas(name);
  vAtlas.push_back(name);
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Screen *SystemGUI::createScreen(
  Ogre::Viewport *vp, std::string atlas, std::string name) {
  Screen *scr = new Screen();
  if (!hasAtlas(atlas)) {
    loadAtlas(atlas);
  }

  if (mScreens[name] == nullptr) {
    scr->screen = pSilverback->createScreen(vp, atlas);
    mScreens[name] = scr;
  }

  return scr->screen;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Layer *SystemGUI::createLayer(
  std::string screen, std::string layer) {
  Gorilla::Layer* lyr = getLayer(screen, layer);

  if (lyr != nullptr) {
    return lyr;
  }

  if (getScreen(screen) != nullptr) {
    mScreens[screen]->layers[layer] = getScreen(screen)->createLayer(mScreens[screen]->layers.size());
    return mScreens[screen]->layers[layer];
  }
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Layer *SystemGUI::createLayer(
  Gorilla::Screen *screen, std::string layer) {
  Gorilla::Layer *lyr = getLayer(screen, layer);

  if (lyr != nullptr) {
    return lyr;
  }

  std::map<std::string, Screen*>::iterator i;
  for (i = mScreens.begin(); i != mScreens.end(); i++) {
    if (i->second->screen == screen) {
      i->second->layers[layer] = i->second->screen->createLayer(i->second->layers.size());
      return i->second->layers[layer];
    }
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Screen *SystemGUI::getScreen(std::string name) {
  if (mScreens[name] != nullptr) {
    return mScreens[name]->screen;
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Layer *SystemGUI::getLayer(std::string screen, std::string layer) {
  if (mScreens[screen] != nullptr) {
    return mScreens[screen]->layers[layer];
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

Gorilla::Layer *SystemGUI::getLayer(Gorilla::Screen *screen, std::string layer) {
  std::map<std::string, Screen*>::iterator i;

  for (i = mScreens.begin(); i != mScreens.end(); i++) {
    return getLayer(i->first, layer);
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////