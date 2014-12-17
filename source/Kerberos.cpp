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
* @file   Kerberos.cpp
* @author Nathan Harris
* @date   16 December 2014
* @brief  Kerberos main entry point
*
* @description
*  Coming soon to a code file near you...
*/

/*****************************************************************************
*****************************************************************************/

#include "Kerberos.h"

/*****************************************************************************
*****************************************************************************/

Kerberos::Brain* m_Brain = new Kerberos::Brain();

/*****************************************************************************
*****************************************************************************/

#ifdef KRB_CONSOLE
  #include <tchar.h>
#else
  #define WIN32_LEAN_AND_MEAN
  #include "windows.h"
#endif

/*****************************************************************************
*****************************************************************************/

#ifdef KRB_CONSOLE
int wmain(int argc, _TCHAR* argv[])
{
  std::cout << "Kerberos Engine v0.0.0.1 (Conceptus)";
  std::cout << std::endl << std::endl;

  m_Brain->init();
  m_Brain->cycle();
  m_Brain->halt();

  std::cout << std::endl;

  printf( "Press enter to exit..." );
	getchar();
  return 0;
}
#else
int CALLBACK WinMain(
  HINSTANCE hInstance, 
  HINSTANCE hPrevInstance, 
  LPSTR lpCmdLine, 
  int nCmdShow)
{
  return 0;
}
#endif

/***]EOF[*********************************************************************/