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
* @date   28 December 2014
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
#include "utility/krbMath.h"

#include "systems/gui/krbUI_GUI.h"

#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

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
//class MenuListener
//{
//public:
//	virtual void MenuExit() = 0;
//};
//
//class Menu
//{
//public:
//	Menu(string name, string atlas, string bgImage, Vector2 dimensions,
//    GUI* gui, Ogre::Viewport* viewport);
//
//	void setListener(MenuListener* listener) { m_Listener = listener; };
//
//	void setVisible(bool value);
//	bool isVisible() { return b_isVisible; };
//	
//	bool mouseDown(unsigned int x, unsigned int y, OIS::MouseButtonID id);
//	bool mouseUp(unsigned int x, unsigned int y, OIS::MouseButtonID id);
//	void mouseMoved(unsigned int x, unsigned int y);
//
//private:
//	bool isOver(Ogre::Vector2 pos, GUI::Button *button);
//
//  string              str_Name;
//
//	Gorilla::Screen*	  m_Screen;
//	Gorilla::Layer*		  m_Layer;
//	Gorilla::Rectangle* m_Background;
//	//GUI::Button*			  m_Exit;
//
//	Ogre::Vector2		    m_vPosition;
//	Ogre::Vector2		    m_vSize;
//	Ogre::Vector2		    m_vButtonOffset;
//	Ogre::Vector2		    m_vButtonSize;
//
//	MenuListener*	      m_Listener;
//
//	bool				        b_isVisible;
//};

/*****************************************************************************
*****************************************************************************/

//
//! \brief GUI system, utilizing Gorilla
//
class SystemGUI final : 
  public System, 
  public Ogre::Singleton<SystemGUI>,
  public Ogre::FrameListener, 
  public OIS::KeyListener, public OIS::MouseListener, 
  public Monkey::Callback
{
public:
  SystemGUI(Config* config, Logger* log);
  ~SystemGUI();

  static SystemGUI& getSingleton();
  static SystemGUI* getSingletonPtr();

  void init();
  void cycle();
  void halt();

  UI_GUI* createGUI(string name, bool visible);

  // GETTERS
  Gorilla::Silverback* getSilverback();
  UI_GUI* getGUI(string name);

  bool keyPressed(const OIS::KeyEvent &e);
  bool keyReleased(const OIS::KeyEvent &e);
  bool mouseMoved(const OIS::MouseEvent &arg);
  bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
  void parseConfig();  

  Ogre::OverlaySystem*  m_OverlaySystem;
  Ogre::SceneManager*   m_SceneManager;
  Ogre::Viewport*       m_Viewport;

protected:
  Gorilla::Silverback*  m_Silverback;

  map<string, UI_GUI*> map_GUI;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbSSystemGUI_h

/***]EOF[*********************************************************************/