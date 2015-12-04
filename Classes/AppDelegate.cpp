#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "CommonMacro.h"
#include "WeMeLogo/WeMeLogoScene.h"
#include "MainMenu/MainMenuScene.h"
#include "MainMap/MainMapScene.h"
#include "PlayGame/PlayGameScene.h"
#include "PlayGame/CandyManager.h"
#include "Loading/LoadingScene.h"
#include "CCLuaEngine.h"
#include "Loading/MMLog.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include "vld.h" 
#endif

using namespace CocosDenshion;

USING_NS_CC;


bool drawBgAgain = false;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
	CCScriptEngineManager::purgeSharedManager(); 

	ActionManager::purgeActionManager();
	UIHelper::purgeUIHelper();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
}

#include "PlayGame/CandyInterludeAction.h"
bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCSize designSize = CCSizeMake(TARGET_SCREEN_WIDTH,  TARGET_SCREEN_HEIGHT);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height,/*kResolutionExactFit*/ kResolutionFixedWidth);	
    // turn on display FPS
#ifdef WIN32
  //pDirector->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60.0f);
 
#if WIN32
	//init Lua For every stage Info
	CCLuaEngine* pEngine  = CCLuaEngine::defaultEngine();
	CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
	CandyMapData::initLoadLuaFile();
	MainMap::initMapLuaFile();

#endif

#ifdef DEMO_FOR_TELECOM
	//CCScene *pScene = Loading::scene(CANDY_SCENCE_MAIN_MAP);
#else

//	CCScene *pScene = MMlog::LogScene();

	CCScene *pScene = Loading::scene(CANDY_SCENCE_DOWNLOAD);

#endif

	pDirector->runWithScene(pScene);

    return true;

}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	// ÉúÃüĞÅÏ¢
	CCLog( "AppDelegate::applicationWillEnterForeground" );
//	if ( !CommonData::m_isBuyLife )
		MsgMgr::sendAddSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
	drawBgAgain = true;

}
