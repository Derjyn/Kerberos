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
* @file   krbUI_Text.h
* @author Nathan Harris
* @date   01 January 2015
* @brief  Text UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbUI_Text_h
#define krbUI_Text_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "utility/krbConverter.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Text
{
public:
  UI_Text(string name, unsigned int glyphIndex, 
    Vector2 position, Vector2 dimensions,
    string text,
    Gorilla::Layer* layer)
  {
    str_Name    = name;
    _layer      = layer;
    _position   = position;

    _text = _layer->createMarkupText(glyphIndex, position.x, position.y, text);
    _text->size(dimensions.x, dimensions.y);
  }  

  ~UI_Text()
  {
    _layer->destroyMarkupText(_text);
  }  

  // SETTERS //////////////////////////////////////////////////////////////////
  void setSize(float width, float height)
  {
    _text->size(width, height);
  }

  void setPosition(Vector2 position)
  {
    _text->left(position.x);
    _text->top(position.y);

    _position = position;
  }

  void setText(string text)
  {
    _text->text(text);
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  Gorilla::MarkupText* getText() { return _text; }

  float getWidth()      { return _text->width(); }
  float getHeight()     { return _text->height(); }

protected:
  string                str_Name;
  bool                  b_Visible;

  Gorilla::Layer*       _layer;
  Gorilla::MarkupText*  _text;

  Vector2               _position;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_Screen_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
