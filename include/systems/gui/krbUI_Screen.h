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
* @file   krbUI_Screen.h
* @author Nathan Harris
* @date   01 January 2015
* @brief  Screen UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbGUI_Screen_h
#define krbGUI_Screen_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Screen
{
public:
  UI_Screen(const string& name, const string& atlas, bool visible, 
    Ogre::Viewport* vp, Gorilla::Silverback* silverback)
  {
    str_Name    = name;
    b_Visible   = visible;
    _viewport   = vp;
    _silverback = silverback;

    if (!hasAtlas(atlas)) 
    {
      loadAtlas(atlas);
    }

    _screen = _silverback->createScreen(_viewport, atlas);

    _screen->setVisible(b_Visible);
  }

  ~UI_Screen()
  {
    _silverback->destroyScreen(_screen);
  }

  void loadAtlas(const string& name) 
  {
    _silverback->loadAtlas(name);
    vec_Atlas.push_back(name);
  }

  bool hasAtlas(const string& name) 
  {
    for (unsigned int i = 0; i < vec_Atlas.size(); i++) 
    {
      if (vec_Atlas[i] == name) 
      {
        return true;
      }
    }

    return false;
  }

  void toggleVisible()
  {
    b_Visible = !b_Visible;

    if (b_Visible)
    {
      _screen->show();
    }
    else
    {
      _screen->hide();
    }
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  Gorilla::Screen* getScreen() { return _screen; }  

  bool isVisible()      { return b_Visible; }
  float getWidth()      { return _screen->getWidth();  }
  float getHeight()     { return _screen->getHeight(); }

protected:
  string  str_Name;
  bool    b_Visible;

  Ogre::Viewport*       _viewport;
  Gorilla::Silverback*  _silverback;
  Gorilla::Screen*      _screen;

  vector<string> vec_Atlas;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_Screen_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
