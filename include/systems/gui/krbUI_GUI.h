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
* @file   krbUI_GUI.h
* @author Nathan Harris
* @date   28 December 2014
* @brief  Base GUI element
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbGUI_GUI_h
#define krbGUI_GUI_h

/*****************************************************************************
*****************************************************************************/

#include "systems/gui/krbUI_Screen.h"
#include "systems/gui/krbUI_Menu.h"
#include "systems/gui/krbUI_Button.h"

#include "Ogre3D/OgreViewport.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class UI_GUI
{
public:
  UI_GUI::UI_GUI(string name, bool visible, 
    Ogre::Viewport* viewport, Gorilla::Silverback* silverback)
  {
    str_Name      = name;
    b_Visible     = visible;
    m_Viewport    = viewport;
    m_Silverback  = silverback;
  }

  UI_GUI::~UI_GUI()
  {
  }

  UI_Screen* createScreen(string name, string atlas)
  {
    UI_Screen* screen = new UI_Screen(name, atlas, b_Visible, 
      m_Viewport, m_Silverback);

    if (map_Screen[name] == nullptr)
    {
      map_Screen[name] = screen;
    }

    return screen;
  }

  UI_Menu* createMenu(string name, string atlas, string background,
    Vector2 dimensions)
  {
    UI_Menu* menu = new UI_Menu(name, atlas, background, b_Visible, dimensions,
      m_Viewport, m_Silverback);

    if (map_Menu[name] == nullptr) 
    {
      map_Menu[name] = menu;
    }

    return menu;
  }
  UI_Menu* createMenu(string name, string atlas, string background,
    Vector2 position, Vector2 dimensions)
  {
    UI_Menu* menu = new UI_Menu(name, atlas, background,
      b_Visible, position, dimensions, m_Viewport, m_Silverback);

    if (map_Menu[name] == nullptr) 
    {
      map_Menu[name] = menu;
    }

    return menu;
  }

  UI_Button* createButton(string name, Gorilla::Layer* layer,
    string baseImg, string hoverImg,
    Vector2 position, Vector2 dimensions,
     OIS::Mouse* mouse)
  {
    UI_Button* button = new UI_Button(name, layer,
      baseImg, hoverImg,
      position, dimensions,
      mouse);

    if (map_Button[name] == nullptr) 
    {
      map_Button[name] = button;
    }

    return button;
  }

  void toggleGUI()
  {
    b_Visible = !b_Visible;

    map<string, UI_Screen*>::iterator i;
    for (i = map_Screen.begin(); i != map_Screen.end(); i++) 
    {
      i->second->toggleVisible();
    }

    map<string, UI_Menu*>::iterator j;
    for (j = map_Menu.begin(); j != map_Menu.end(); j++) 
    {
      j->second->toggleVisible();
    }
  }

  // GETTERS
  string getName() { return str_Name; }
  bool isVisible() { return b_Visible; }

protected:
  string                    str_Name;
  bool                      b_Visible;
  Ogre::Viewport*           m_Viewport;

private:
  friend class UI_Menu;
  friend class UI_Screen;

  Gorilla::Silverback*      m_Silverback;
  map<string, UI_Menu*>     map_Menu;
  map<string, UI_Screen*>   map_Screen;
  map<string, UI_Button*>   map_Button;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbGUI_GUI_h

/***]EOF[*********************************************************************/