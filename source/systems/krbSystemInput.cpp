///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemInput.cpp
//  UPDATED : 12/07/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "systems\krbSystemInput.h"

#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"

///////////////////////////////////////////////////////////////////////////////

template<> Kerberos::SystemInput* Ogre::Singleton<Kerberos::SystemInput>::msSingleton = 0;

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

SystemInput::SystemInput() {
  setName("SYSTEM INPUT");
}

SystemInput& SystemInput::singleton(void) { return (*msSingleton); }
SystemInput* SystemInput::singletonPtr(void) { return msSingleton; }

///////////////////////////////////////////////////////////////////////////////

void SystemInput::init(void) {
  OIS::ParamList pl;
  pl.insert(OIS::ParamList::value_type(
    "WINDOW", Ogre::StringConverter::toString(hWnd)));

  pOIS = OIS::InputManager::createInputSystem(pl);

  pKeyboard = static_cast<OIS::Keyboard*>(
    pOIS->createInputObject(OIS::OISKeyboard, true));
  pKeyboard->setEventCallback(this);

  pMouse = static_cast<OIS::Mouse*>(
    pOIS->createInputObject(OIS::OISMouse, true));
  pMouse->setEventCallback(this);
}

///////////////////////////////////////////////////////////////////////////////

void SystemInput::halt(void) {
  if (pMouse) {
    pOIS->destroyInputObject(pMouse);
  }
  if (pKeyboard) {
    pOIS->destroyInputObject(pKeyboard);
  }

  OIS::InputManager::destroyInputSystem(pOIS);
}

///////////////////////////////////////////////////////////////////////////////

void SystemInput::capture(void) {
  pMouse->capture();
  pKeyboard->capture();
}

///////////////////////////////////////////////////////////////////////////////

bool SystemInput::isKeyReleased(OIS::KeyCode key) {
  return pKeyboard->isKeyDown(key);
}

///////////////////////////////////////////////////////////////////////////////

void SystemInput::setWindow(Ogre::RenderWindow* win) {
  win->getCustomAttribute("WINDOW", &hWnd);
}

///////////////////////////////////////////////////////////////////////////////

void  SystemInput::setWindowExtents(int width, int height) {
  const OIS::MouseState &ms = pMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

///////////////////////////////////////////////////////////////////////////////

OIS::Keyboard* SystemInput::getKeyboard(void) {
  return pKeyboard;
}
OIS::Mouse* SystemInput::getMouse(void) {
  return pMouse;
}

///////////////////////////////////////////////////////////////////////////////

bool SystemInput::mouseMoved(const OIS::MouseEvent &evt) {
  return true;
}

bool SystemInput::mousePressed(
  const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
  return true;
}

bool SystemInput::mouseReleased(
  const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
  return true;
}

///////////////////////////////////////////////////////////////////////////////

bool SystemInput::keyPressed(const OIS::KeyEvent &evt) {
  return true;
}

bool SystemInput::keyReleased(const OIS::KeyEvent &evt) {
  return true;
}

///////////////////////////////////////////////////////////////////////////////

}

// EOF ////////////////////////////////////////////////////////////////////////