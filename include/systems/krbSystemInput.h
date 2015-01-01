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
* @file   krbSystemInput.h
* @author Nathan Harris
* @date   31 December 2014
* @brief  Input system
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbSystemInput_h
#define krbSystemInput_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "systems/krbSystem.h"

#include "OIS/OISEvents.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Ogre 
{
  class RenderWindow;
}

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

//
//! \brief Input system, utilizing OIS
//
class SystemInput final : 
  public System, 
  public OIS::MouseListener, 
  public OIS::KeyListener, 
  public Ogre::Singleton<SystemInput>
{
public:
  SystemInput(Config* config, Logger* log);
  ~SystemInput();

  static SystemInput& getSingleton();
  static SystemInput* getSingletonPtr();

  void init();
  void cycle();
  void halt();

  void setWindowExtents(int width, int height);

  bool mouseMoved(const OIS::MouseEvent& evt);
  bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID);
  bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID);

  bool keyDown(const OIS::KeyCode& key);
  bool modDown(const OIS::Keyboard::Modifier& mod);
  bool keyPressed(const OIS::KeyEvent& evt);
  bool keyReleased(const OIS::KeyEvent& evt);

  OIS::Keyboard* getKeyboard();
  OIS::Mouse* getMouse();

private:
  void parseConfig();

  Ogre::RenderWindow*   m_Window;
  OIS::InputManager*    m_InputMgr;
  OIS::Mouse*           m_Mouse;
  OIS::Keyboard*        m_Keyboard;
  unsigned long         hWnd;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbSystemInput_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\