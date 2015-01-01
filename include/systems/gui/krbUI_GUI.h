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
* @date   01 January 2015
* @brief  Base GUI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbGUI_GUI_h
#define krbGUI_GUI_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "core/krbConfig.h"

#include "systems/gui/krbUI_Screen.h"
#include "systems/gui/krbUI_Layer.h"
#include "systems/gui/krbUI_Rectangle.h"
#include "systems/gui/krbUI_Button.h"
#include "systems/gui/krbUI_Caption.h"
#include "systems/gui/krbUI_Text.h"

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_GUI
{
public:
  UI_GUI::UI_GUI(const string& name, bool visible, 
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

  // SCREEN ///////////////////////////////////////////////////////////////////
  UI_Screen* createScreen(const string& name, const string& atlas, bool visible)
  {
    UI_Screen* _screen = new UI_Screen(name, atlas, visible, 
      m_Viewport, m_Silverback);

    if (map_Screen[name] == nullptr)
    {
      map_Screen[name] = _screen;
    }

    return _screen;
  }

  // LAYER ////////////////////////////////////////////////////////////////////
  UI_Layer* createLayer(const string& name, bool visible, unsigned int index,
    UI_Screen* screen)
  {
    UI_Layer* _layer = new UI_Layer(name, visible, index, screen->getScreen());

    if (map_Layer[name] == nullptr)
    {
      map_Layer[name] = _layer;
    }

    return _layer;
  }

  // RECTANGLE ////////////////////////////////////////////////////////////////
  UI_Rectangle* createRectangle(const string& name, const string& bgImg, 
    Vector2 position, Vector2 dimensions, 
    UI_Layer* layer)
  {
    UI_Rectangle* _rectangle = new UI_Rectangle(name, bgImg,
      position, dimensions, layer->getLayer());

    if (map_Rectangle[name] == nullptr)
    {
      map_Rectangle[name] = _rectangle;
    }

    return _rectangle;
  }

  UI_Rectangle* createRectangle(const string& name, Color bgColor, 
    Vector2 position, Vector2 dimensions, 
    UI_Layer* layer)
  {
    UI_Rectangle* _rectangle = new UI_Rectangle(name, bgColor,
      position, dimensions, layer->getLayer());

    if (map_Rectangle[name] == nullptr)
    {
      map_Rectangle[name] = _rectangle;
    }

    return _rectangle;
  }

  // BUTTON ///////////////////////////////////////////////////////////////////
  UI_Button* createButton(const string& name, 
    const string& imgBase, const string& imgHover,
    Vector2 position, Vector2 dimensions,
    UI_Layer* layer, OIS::Mouse* mouse)
  {
    UI_Button* _button = new UI_Button(name, layer->getLayer(),
      imgBase, imgHover, position, dimensions, mouse);

    if (map_Button[name] == nullptr)
    {
      map_Button[name] = _button;
    }

    return _button;
  }

  // CAPTION //////////////////////////////////////////////////////////////////
  UI_Caption* createCaption(const string& name, unsigned int glyphIndex,
    Vector2 position, Vector2 dimensions,
    const string& text,
    bool fixedWidth,
    UI_Layer* layer)
  {
    UI_Caption* _caption = new UI_Caption(name, glyphIndex,
      position, dimensions, text, fixedWidth, layer->getLayer());

    if (map_Caption[name] == nullptr)
    {
      map_Caption[name] = _caption;
    }

    return _caption;
  }

  // TEXT /////////////////////////////////////////////////////////////////////
  UI_Text* createText(const string& name, unsigned int glyphIndex,
    Vector2 position, Vector2 dimensions,
    const string& text,
    UI_Layer* layer)
  {
    UI_Text* _text = new UI_Text(name, glyphIndex,
      position, dimensions, text, layer->getLayer());

    if (map_Text[name] == nullptr)
    {
      map_Text[name] = _text;
    }

    return _text;
  }

  // TOGGLE ELEMENTS //////////////////////////////////////////////////////////
  void toggleGUI()
  {
    b_Visible = !b_Visible;

    map<string, UI_Screen*>::iterator i;
    for (i = map_Screen.begin(); i != map_Screen.end(); i++) 
    {
      i->second->toggleVisible();
    }
  }
  void toggleScreen(string name)
  {
    if (map_Screen[name] != nullptr) 
    {
      map_Screen[name]->toggleVisible();
    }
  }
  void toggleLayer(string name)
  {
    if (map_Layer[name] != nullptr) 
    {
      map_Layer[name]->toggleVisible();
    }
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  string getName()    { return str_Name; }
  bool isVisible()    { return b_Visible; }

  UI_Screen* getScreen(string name)
  {
    if (map_Screen[name] != nullptr) 
    {
      return map_Screen[name];
    }
  }
  UI_Layer* getLayer(string name)
  {
    if (map_Layer[name] != nullptr) 
    {
      return map_Layer[name];
    }
  }
  UI_Rectangle* getRectangle(string name)
  {
    if (map_Rectangle[name] != nullptr) 
    {
      return map_Rectangle[name];
    }
  }
  UI_Button* getButton(string name)
  {
    if (map_Button[name] != nullptr) 
    {
      return map_Button[name];
    }
  }
  UI_Caption* getCaption(string name)
  {
    if (map_Caption[name] != nullptr) 
    {
      return map_Caption[name];
    }
  }
  UI_Text* getText(string name)
  {
    if (map_Text[name] != nullptr) 
    {
      return map_Text[name];
    }
  }

protected:
  string    str_Name;
  bool      b_Visible;

  Ogre::Viewport*         m_Viewport;
  Gorilla::Silverback*    m_Silverback;

private:
  map<string, UI_Screen*>     map_Screen;
  map<string, UI_Layer*>      map_Layer;
  map<string, UI_Rectangle*>  map_Rectangle;
  map<string, UI_Button*>     map_Button;
  map<string, UI_Caption*>    map_Caption;
  map<string, UI_Text*>       map_Text;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_GUI_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\