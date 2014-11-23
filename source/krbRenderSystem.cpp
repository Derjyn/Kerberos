///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "krbRenderSystem.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

template<> krbRenderSystem* Ogre::Singleton<krbRenderSystem>::msSingleton = 0;

krbRenderSystem::krbRenderSystem() {
	pCore = krbCore::getPointer();
}

krbRenderSystem& krbRenderSystem::getInstance(void)
{  
    assert(msSingleton); 
	return (*msSingleton);  
}
krbRenderSystem* krbRenderSystem::getPointer(void)
{
    return msSingleton;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// INIT SYSTEM

void krbRenderSystem::Init(bool capFPS, float fRate) 
{	
	bCapFPS = capFPS;
	fTimePerRenderTick = fRate;
	fRenderTimePassed = 0;
	iRenderTicks = 0;

	mWindow = pCore->mRoot->initialise(true, "Kerberos");
	windowHnd = 0;
 	mWindow->getCustomAttribute("WINDOW", &windowHnd);

	mSceneMgr = pCore->mRoot->createSceneManager(Ogre::ST_GENERIC);

	mCameraBase = mSceneMgr->createCamera("CameraBase");
	mCameraBase->setPosition(Ogre::Vector3(0,0,500));
	mCameraBase->lookAt(Ogre::Vector3(0,0,-300));
	mCameraBase->setNearClipDistance(5);

	mViewport = mWindow->addViewport(mCameraBase);
	mViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
 
	mViewportX = Ogre::Real(mViewport->getActualWidth());
	mViewportY = Ogre::Real(mViewport->getActualHeight());
	mViewportRatio = mViewportX / mViewportY;
	mCameraBase->setAspectRatio(mViewportRatio);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// RENDER

void krbRenderSystem::Render()
{
	if(bCapFPS) {
		if((fRenderTimePassed + fTimePerRenderTick) < pCore->getMilliseconds())
		{
			Ogre::WindowEventUtilities::messagePump();
			pCore->mRoot->renderOneFrame();

			iRenderTicks++;
			fRenderTimePassed += fTimePerRenderTick;
		}
	} else {
		Ogre::WindowEventUtilities::messagePump();
		pCore->mRoot->renderOneFrame();

		iRenderTicks++;
		fRenderTimePassed += fTimePerRenderTick;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// HALT

void krbRenderSystem::Halt()
{
	mWindow->removeViewport(mViewport->getZOrder());
	mSceneMgr->destroyCamera(mCameraBase);
	pCore->mRoot->destroySceneManager(mSceneMgr);
	mWindow->destroy();
}

// EOF ////////////////////////////////////////////////////////////////////////////////////////////