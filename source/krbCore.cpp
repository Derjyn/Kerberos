///////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Kerberos.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

template<> krbCore* Ogre::Singleton<krbCore>::msSingleton = 0;

krbCore::krbCore() {
	new krbRenderSystem();
	pRenderSys = krbRenderSystem::getPointer();

	new krbInputSystem();
	pInputSys = krbInputSystem::getPointer();
}

krbCore& krbCore::getInstance(void)
{  
    assert(msSingleton); 
	return (*msSingleton);  
}
krbCore* krbCore::getPointer(void)
{
    return msSingleton;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// INIT SYSTEM

void krbCore::Init(float logicRate, bool capFPS, float fpsCap) 
{
	fTotalTime = 0;

	strTotalTime = "";
	strTotalLogicTicks = "";
	strTotalRenderTicks = "";

	fLogicTimePassed = 0;
	iLogicTicks = 0;
	fTimePerLogicTick = 1000 / logicRate;

	mRoot = new Ogre::Root("plugins.cfg", "config.cfg", "kerberos.log");

	if(!mRoot->restoreConfig())
	{
		if(!mRoot->showConfigDialog())
		{
			Halt();
		}      
    }
	
	mTimer = new Ogre::Timer();
	mTimer->reset();

	pRenderSys->Init(capFPS, 1000 / fpsCap);
	pInputSys->Init();	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// CYCLE

void krbCore::Cycle()
{
	LogicCycle();
	RenderCycle();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// LOGIC CYCLE

void krbCore::LogicCycle()
{
	if((fLogicTimePassed + fTimePerLogicTick) < mTimer->getMilliseconds())
	{
		pInputSys->CaptureInput();

		// DEMO
		fRanR = Ogre::Math::RangeRandom(0.0, 1.0);
		fRanG = Ogre::Math::RangeRandom(0.0, 1.0);
		fRanB = Ogre::Math::RangeRandom(0.0, 1.0);
		pRenderSys->mViewport->setBackgroundColour(Ogre::ColourValue(fRanR, fRanG, fRanB));

		iLogicTicks++;
		fLogicTimePassed += fTimePerLogicTick;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// RENDER CYCLE

void krbCore::RenderCycle()
{
	pRenderSys->Render();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// HALT

void krbCore::Halt()
{
	fTotalTime = mTimer->getMilliseconds();

	strTotalTime = Ogre::StringConverter::toString(fTotalTime / 1000);
	strTotalLogicTicks = Ogre::StringConverter::toString(iLogicTicks);
	strTotalRenderTicks = Ogre::StringConverter::toString(pRenderSys->iRenderTicks);

	pInputSys->Halt();
	pRenderSys->Halt();

	Ogre::LogManager::getSingleton().logMessage("////////////////////////////////////////////");
	Ogre::LogManager::getSingleton().logMessage("//");
	Ogre::LogManager::getSingleton().logMessage("// PROGRAM EXIT");
	Ogre::LogManager::getSingleton().logMessage("// TOTAL TIME: " + strTotalTime + " SECONDS");
	Ogre::LogManager::getSingleton().logMessage("// TOTAL LOGIC TICKS: " + strTotalLogicTicks + " TICKS");	
	Ogre::LogManager::getSingleton().logMessage("// TOTAL RENDER TICKS: " + strTotalRenderTicks + " TICKS");
	Ogre::LogManager::getSingleton().logMessage("//");
	Ogre::LogManager::getSingleton().logMessage("////////////////////////////////////////////");

	mRoot->shutdown();
	delete mRoot;
}

// EOF ////////////////////////////////////////////////////////////////////////////////////////////