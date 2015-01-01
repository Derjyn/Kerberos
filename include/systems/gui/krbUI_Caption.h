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
* @file   krbUI_Caption.h
* @author Nathan Harris
* @date   01 January 2015
* @brief  Caption UI element
*
* @details
*  Coming soon to a code file near you...
*/

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#pragma once

#ifndef krbUI_Caption_h
#define krbUI_Caption_h

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

#include "utility/krbConverter.h"

#include "Gorilla/Gorilla.h"
#include "Monkey/Monkey.h"

#include <string>
using namespace std;

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

namespace Kerberos {

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

class UI_Caption
{
public:
  UI_Caption(const string& name, unsigned int glyphIndex, 
    Vector2 position, Vector2 dimensions,
    const string& text,
    bool fixedWidth,
    Gorilla::Layer* layer)
  {
    str_Name    = name;
    _layer      = layer;
    _position   = position;

    _caption = _layer->createCaption(glyphIndex, position.x, position.y, text);
    _caption->size(dimensions.x, dimensions.y);
    _caption->fixedWidth(fixedWidth);
  }  

  ~UI_Caption()
  {
    _layer->destroyCaption(_caption);
  }  

  // SETTERS //////////////////////////////////////////////////////////////////
  void setSize(float width, float height)
  {
    _caption->size(width, height);
  }

  void setPosition(Vector2 position)
  {
    _caption->left(position.x);
    _caption->top(position.y);

    _position = position;
  }

  void setCaption(const string& caption)
  {
    _caption->text(caption);
  }

  // GETTERS //////////////////////////////////////////////////////////////////
  Gorilla::Caption* getCaption() { return _caption; }

  float getWidth()      { return _caption->width(); }
  float getHeight()     { return _caption->height(); }

protected:
  string                str_Name;
  bool                  b_Visible;

  Gorilla::Layer*       _layer;
  Gorilla::Caption*     _caption;

  Vector2               _position;
};

///^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\

} // namespace Kerberos
#endif // krbGUI_Screen_h

///^]EOF[^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\^\
