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
* @date   28 December 2014
* @brief  Screen UI element
*
* @details
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#pragma once

#ifndef krbGUI_Screen_h
#define krbGUI_Screen_h

/*****************************************************************************
*****************************************************************************/

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

/*****************************************************************************
*****************************************************************************/

namespace Kerberos {

/*****************************************************************************
*****************************************************************************/

class UI_Screen
{
public:
  UI_Screen(string name, string atlas, bool visible, 
    Ogre::Viewport* vp, Gorilla::Silverback* silverback)
  {
    str_Name = "SCREEN_" + name;
    b_Visible = visible;
    m_Viewport = vp;
    m_Silverback = silverback;

    if (!hasAtlas(atlas)) 
    {
      loadAtlas(atlas);
    }

    m_Screen = m_Silverback->createScreen(m_Viewport, atlas);

    m_Screen->setVisible(b_Visible);
  }

  ~UI_Screen()
  {
  }

  void loadAtlas(string name) 
  {
    m_Silverback->loadAtlas(name);
    vec_Atlas.push_back(name);
  }

  bool hasAtlas(string name) 
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
      m_Screen->show();
    }
    else
    {
      m_Screen->hide();
    }
  }

  Gorilla::Layer* createLayer(string name)
  {
    Gorilla::Layer* layer = m_Screen->createLayer(map_Layer.size());

    if (layer != nullptr)
    {
      return layer;
    }

    if (map_Layer[name] == nullptr)
    {
      map_Layer[name] = layer;

      return map_Layer[name];
    }

    return nullptr;
  }

  void toggleLayer(string name)
  {
    if (map_Layer[name] != nullptr) 
    {
      if (map_Layer[name]->isVisible())
      {
        map_Layer[name]->hide();
      }
      else
      {
        map_Layer[name]->show();
      }
    }
  }

  // GETTERS
  bool isVisible() { return b_Visible; }
  Gorilla::Screen* getGorillaScreen() { return m_Screen; }
  Gorilla::Layer* getLayer(string name) 
  { 
    return map_Layer[name];
  }

protected:
  string                str_Name;
  bool                  b_Visible;

  Ogre::Viewport*       m_Viewport;
  Gorilla::Silverback*  m_Silverback;
  Gorilla::Screen*      m_Screen;

  vector<string> vec_Atlas;
  map<string, Gorilla::Layer*> map_Layer;

private:
  friend class UI_GUI;
};

/*****************************************************************************
*****************************************************************************/

} // namespace Kerberos
#endif // krbGUI_Screen_h

/***]EOF[*********************************************************************/
