///////////////////////////////////////////////////////////////////////////////////////////////////
// CORE VARIABLES

bool isActive = false;

Ogre::Timer mTimer;
Ogre::Real fTotalTime;
Ogre::String strTotalTime;

Ogre::Real fUpdateTimePassed = 0;
int iUpdateTicks = 0;
Ogre::Real fTimePerUpdateTick = 1000 / 60;
Ogre::String strTotalUpdateTicks;

Ogre::Real fLogicTimePassed = 0;
int iLogicTicks = 0;
Ogre::Real fTimePerLogicTick = 1000 / 10;
Ogre::String strTotalLogicTicks;


///////////////////////////////////////////////////////////////////////////////////////////////////
// OGRE & OIS

Ogre::Root* mRoot = 0; 
Ogre::RenderWindow* mWindow = 0;
Ogre::SceneManager* mSceneMgr = 0;
Ogre::Camera* mCameraBase = 0;
Ogre::Viewport* mViewport = 0;

Ogre::Real mViewportX, mViewportY, mViewportRatio;

OIS::InputManager* mInputMgr;
OIS::Keyboard* mKeyboard;

float fRanR, fRanG, fRanB;


///////////////////////////////////////////////////////////////////////////////////////////////////
// INIT

bool Init()
{
	mRoot = new Ogre::Root("plugins.cfg", "config.cfg", "kerberos.log");

	if(!mRoot->restoreConfig())
	{
		if(!mRoot->showConfigDialog())
		{
			return 0;
		}      
    }

	mWindow = mRoot->initialise(true, "Kerberos");
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

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

	size_t windowHnd = 0;
 	mWindow->getCustomAttribute("WINDOW", &windowHnd);
 	mInputMgr = OIS::InputManager::createInputSystem(windowHnd);
 	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));

	mTimer.reset();

	isActive = true;

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RENDER

bool Render()
{
	Ogre::WindowEventUtilities::messagePump();

	mRoot->renderOneFrame();

	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// HANDLE INPUT

bool HandleInput()
{
	mKeyboard->capture();

	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		isActive = false;
	}

	if(mKeyboard->isKeyDown(OIS::KC_SPACE))
	{
		mViewport->setBackgroundColour(Ogre::ColourValue(fRanR, fRanG, fRanB));
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// HANDLE LOGIC

bool HandleLogic()
{
	if((fLogicTimePassed + fTimePerLogicTick) < mTimer.getMilliseconds())
	{
		fRanR = Ogre::Math::RangeRandom(0.0, 1.0);
		fRanG = Ogre::Math::RangeRandom(0.0, 1.0);
		fRanB = Ogre::Math::RangeRandom(0.0, 1.0);

		iLogicTicks++;

		fLogicTimePassed += fTimePerLogicTick;
	}

	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// HANDLE UPDATE

bool HandleUpdate()
{
	if((fUpdateTimePassed + fTimePerUpdateTick) < mTimer.getMilliseconds())
	{
		HandleInput();

		iUpdateTicks++;

        fUpdateTimePassed += fTimePerUpdateTick;
	}

	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// UPDATE

bool Run()
{
	fTotalTime = float(mTimer.getMilliseconds());

	Render();
	HandleLogic();
	HandleUpdate();	

	return 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// EXIT

void Exit()
{
	if(isActive)
	{
		isActive = false;
	}

	strTotalTime = Ogre::StringConverter::toString(fTotalTime / 1000);
	strTotalLogicTicks = Ogre::StringConverter::toString(iLogicTicks);
	strTotalUpdateTicks = Ogre::StringConverter::toString(iUpdateTicks);

	Ogre::LogManager::getSingleton().logMessage("////////////////////////////////////////////");
	Ogre::LogManager::getSingleton().logMessage("//");
	Ogre::LogManager::getSingleton().logMessage("// PROGRAM EXIT");
	Ogre::LogManager::getSingleton().logMessage("// TOTAL TIME: " + strTotalTime + " SECONDS");
	Ogre::LogManager::getSingleton().logMessage("// TOTAL LOGIC TICKS: " + strTotalLogicTicks + " TICKS");	
	Ogre::LogManager::getSingleton().logMessage("// TOTAL UPDATE TICKS: " + strTotalUpdateTicks + " TICKS");
	Ogre::LogManager::getSingleton().logMessage("//");
	Ogre::LogManager::getSingleton().logMessage("////////////////////////////////////////////");

	mInputMgr->destroyInputObject(mKeyboard);
 	mInputMgr->destroyInputSystem(mInputMgr);
 	mInputMgr = 0;

	mWindow->removeViewport(mViewport->getZOrder());
	mSceneMgr->destroyCamera(mCameraBase);
	mRoot->destroySceneManager(mSceneMgr);
	mWindow->destroy();
	mRoot->shutdown();	

	delete mRoot;	
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN ENTRY POINT

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Init();	

	while(isActive) {
		Run();
	}

	Exit();

	return 0;
}


// EOF ////////////////////////////////////////////////////////////////////////////////////////////