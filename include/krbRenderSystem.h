#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "krbCore.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

class krbRenderSystem : public Ogre::Singleton<krbRenderSystem>
{
public:
    krbRenderSystem();
	static krbRenderSystem& getInstance(void);
    static krbRenderSystem* getPointer(void);
 
	// FUNCTIONS
	void Init(bool capFPS, float fRate);
	void Render();
	void Halt();

	// VARIABLES
	Ogre::RenderWindow* mWindow;
	size_t windowHnd;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCameraBase;
	Ogre::Viewport* mViewport;
	Ogre::Real mViewportX, mViewportY, mViewportRatio;

	Ogre::Real fRenderTimePassed;
	int iRenderTicks;
	Ogre::Real fTimePerRenderTick;

	bool bCapFPS;

	krbCore* pCore;
};

// EOF ////////////////////////////////////////////////////////////////////////////////////////////