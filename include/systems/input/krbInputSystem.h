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
* @file   krbInputSystem.h
* @author Nathan Harris
* @date   13 December 2014
* @brief  Takes care of input stuff.
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbInputSystem_h
#define krbInputSystem_h

/*****************************************************************************
*****************************************************************************/

#include "..\krbSystem.h"

#include "OIS\OISEvents.h"
#include "OIS\OISInputManager.h"
#include "OIS\OISKeyboard.h"
#include "OIS\OISMouse.h"

/*****************************************************************************
*****************************************************************************/

namespace Ogre 
{
  class RenderWindow;
}

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class InputSystem final : public System, 
  public OIS::MouseListener, public OIS::KeyListener
{
public:
  InputSystem(Config* config, Logger* log, Timer* timer, 
    Ogre::RenderWindow* win);
  ~InputSystem();

  void start(void);
  void cycle(void);
  void stop(void);

  void setRenderWindow(Ogre::RenderWindow* window);
  void setWindowExtents(int width, int height);

  bool keyDown(const OIS::KeyCode& key);
  bool modDown(const OIS::Keyboard::Modifier& mod);

  bool mouseMoved(const OIS::MouseEvent& evt);
  bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID);
  bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID);

  bool keyPressed(const OIS::KeyEvent& evt);
  bool keyReleased(const OIS::KeyEvent& evt);

  OIS::Keyboard*        getKeyboard();
  OIS::Mouse*           getMouse();

private:
  Ogre::RenderWindow*   pWindow;
  OIS::InputManager*    pInputMgr;
  OIS::Mouse*           pMouse;
  OIS::Keyboard*        pKeyboard;
  unsigned long         hWnd;
};

/*****************************************************************************
*****************************************************************************/

} // namepsace Kerberos
#endif // krbInputSystem_h

/***]EOF[*********************************************************************/