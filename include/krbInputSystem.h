#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "krbCore.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

class krbInputSystem : public Ogre::Singleton<krbInputSystem>
{
public:
    krbInputSystem();
	~krbInputSystem();

	static krbInputSystem& getInstance(void);
    static krbInputSystem* getPointer(void);
 
	// FUNCTIONS
	void Init();
	void CaptureInput();
	bool KeyDown(OIS::KeyCode key);
	void Halt();

	OIS::InputManager* mInputMgr;
	OIS::Keyboard* mKeyboard;

	krbRenderSystem* pRenderSys;
};

// EOF ////////////////////////////////////////////////////////////////////////////////////////////