/*******************************************************************************
*                                                                              *
* Copyright (C) 2014 Nathan Harris                                             *
*                                                                              *
* This file is part of Kerberos.                                               *
*                                                                              *
*   Kerberos is free software. Enjoy it, modify it, contribute to it.          *
*   For sales inqueries, see <http://www.omglasergunspewpewpew.com/>           *
*                                                                              *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public           *
*   License along with Box.  If not, see <http://www.gnu.org/licenses/>.       *
*                                                                              *
*******************************************************************************/

/**
* @file   Kerberos.cpp
* @author Nathan Harris
* @date   13 December 2014
* @brief  Main application entry point
*/

/*****************************************************************************
*****************************************************************************/

#include "Kerberos.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

/*****************************************************************************
*****************************************************************************/

Kerberos::Core* pCore = new Kerberos::Core();

/*****************************************************************************
*****************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    pCore->start();
    pCore->cycle();
    pCore->stop();

    delete pCore;
}

/***]EOF[*********************************************************************/