#pragma once

#ifndef krbSystemInput_H
#define krbSystemInput_H

///////////////////////////////////////////////////////////////////////////////
//
//  FILE    : krbSystemInput.h
//  UPDATED : 12/04/2014
//
///////////////////////////////////////////////////////////////////////////////

#include "krbSystem.h"

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISKeyboard.h"
#include "OISMouse.h"

#include "OgreSingleton.h"

///////////////////////////////////////////////////////////////////////////////

namespace Ogre {
  class RenderWindow;
}

///////////////////////////////////////////////////////////////////////////////

namespace Kerberos {

///////////////////////////////////////////////////////////////////////////////

 class SystemInput : public System, 
   public OIS::MouseListener, public OIS::KeyListener,
   public Ogre::Singleton<SystemInput> {
public:
  SystemInput();
  static SystemInput &singleton(void);
  static SystemInput *singletonPtr(void);

  void capture(void);

  bool isKeyReleased(OIS::KeyCode key);

  // SETTERS
  void setWindow(Ogre::RenderWindow *win);
  void setWindowExtents(int width, int height);

  // GETTERS
  OIS::Keyboard* getKeyboard(void);
  OIS::Mouse* getMouse(void);

  bool mouseMoved(const OIS::MouseEvent &evt);
  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);

  bool keyPressed(const OIS::KeyEvent &evt);
  bool keyReleased(const OIS::KeyEvent &evt);

private:
  friend class SystemFactory;

  OIS::InputManager *pOIS;
  OIS::Mouse *pMouse;
  OIS::Keyboard *pKeyboard;
  unsigned long hWnd;

protected:
  void init(void);
  void halt(void);
};

// EOF ////////////////////////////////////////////////////////////////////////

}
#endif