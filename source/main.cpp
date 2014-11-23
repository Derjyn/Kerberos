///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Kerberos.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// VARIABLES

bool isActive = false;

krbCore* pCore;
krbInputSystem* pInputSys;
krbRenderSystem* pRenderSys;


///////////////////////////////////////////////////////////////////////////////////////////////////
// INIT

void Init()
{
	new krbCore();
	pCore = krbCore::getPointer();	
	pCore->Init(30, true, 120);

	pRenderSys = krbRenderSystem::getPointer();
	pInputSys = krbInputSystem::getPointer();

	isActive = true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// CYCLE

void Cycle()
{
	if(pInputSys->KeyDown(OIS::KC_ESCAPE))
	{
		isActive = false;
	}
	
	pCore->Cycle();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// EXIT

void Exit()
{
	if(isActive)
	{
		isActive = false;
	}	

	pCore->Halt();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN ENTRY POINT

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Init();	

	while(isActive && (pCore->getMilliseconds() < 10001)) {
		Cycle();
	}

	Exit();

	return 0;
}


// EOF ////////////////////////////////////////////////////////////////////////////////////////////