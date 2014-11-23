///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "krbInputSystem.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

template<> krbInputSystem* Ogre::Singleton<krbInputSystem>::msSingleton = 0;

krbInputSystem::krbInputSystem() {
	pRenderSys = krbRenderSystem::getPointer();
}
krbInputSystem::~krbInputSystem() {}

krbInputSystem& krbInputSystem::getInstance(void)
{  
    assert(msSingleton); 
	return (*msSingleton);  
}
krbInputSystem* krbInputSystem::getPointer(void)
{
    return msSingleton;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// INIT SYSTEM

void krbInputSystem::Init() 
{
	mInputMgr = OIS::InputManager::createInputSystem(pRenderSys->windowHnd);
 	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// RENDER

void krbInputSystem::CaptureInput()
{
	mKeyboard->capture();
}

// KEY DOWN
bool krbInputSystem::KeyDown(OIS::KeyCode key)
{
	if(mKeyboard->isKeyDown(key))
	{
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// HALT

void krbInputSystem::Halt()
{
	mInputMgr->destroyInputObject(mKeyboard);
 	mInputMgr->destroyInputSystem(mInputMgr);
 	mInputMgr = 0;
}

// EOF ////////////////////////////////////////////////////////////////////////////////////////////