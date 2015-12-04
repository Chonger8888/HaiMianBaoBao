#include "LoadingScene.h"
#include "../MainMap/MainMapScene.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../PlayGame/PlayGameScene.h"
#include "../PlayGame/CandyManager.h"
#include "../CppCallJava/CppCallJava.h"
#include "../MsgMgr/HeadDownMgr.h"
#include "../PlayGame/CandyRouletteStory.h"
#include "../Login/UILogin.h"
#include "../CommonData/CommonData.h"

//#define USE_CANDY_BG

#define LOADING_IMG						"Image/Loading/loading.png"
#define LOADING_TIPS_IMG				"Image/Loading/loadingTips.png"
#define LOADING_CONTENT_IMG				"Image/Loading/loadingContent.png"
#define LOADING_BACKGROUND_IMG			"Image/Loading/loadingBg.png"


#define REPLACE_SCENCE_FADE_TIME			0.3f
#define FINISH_FADE_FRAME					(int)(REPLACE_SCENCE_FADE_TIME * 60 +10)

Loading * Loading::m_loading = NULL;
candyScenceType Loading::scenceType = CANDY_SCENCE_DOWNLOAD;

CCScene* Loading::scene(candyScenceType type)
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		Loading::scenceType = type;
		Loading *layer;
		layer = Loading::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
		Loading::m_loading = layer;


	} while (0);

	return scene;
}

void Loading::onEnter()
{
	CCLayer::onEnter();
	CCSize designSize = CCSizeMake(TARGET_SCREEN_WIDTH,  TARGET_SCREEN_HEIGHT);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height,kResolutionFixedWidth);	
}

void Loading::onEnterTransitionDidFinish( void )
{
	if (CANDY_SCENCE_PLAY_GAME == scenceType  )
	{
		initPlayGameRes();
	}		
	else if(CANDY_SCENCE_DOWNLOAD ==  scenceType )
	{	
#ifdef CANDY_VERSIONS_FOR_SINGLE
		CommonData::getBackgroundState();
		CommonData::getSoundEffectState();
		initMainMapRes();
		CandyMapData::initLoadLuaFile();
		MainMap::initMapLuaFile();

		if ( !CommonData::isFirstInstall() )
		{
			CommonData::setBackgroundState( true );
			CommonData::setSoundEffectState( true );
		}


		for (int i = AnalyseJson::logOnMsg.stageInfo.size()+1; i <= 225; i++)
		{
			UserStageInfoStr stageInfoStr;

			stageInfoStr.level = i;
			stageInfoStr.score = 0;
			AnalyseJson::logOnMsg.stageInfo.push_back(stageInfoStr);
		}

#else
		if ( 1/*CppCallJava::isNetworkOk()*/ )
		{
			CCLog( "Loading::onEnterTransitionDidFinish isNetworkOk" );
			//　获取平台数据
//			CppCallJava::getPlatfromInfo();
//			AnalyseJson::getCandPicPath();


			//单机修改
			AnalyseJson::setLogOnMsg();
			CommonData::initConfigInfo();

#if defined(DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)

			if ( !CommonData::isFirstInstall() )
			{
				CommonData::setBackgroundState( true );
				CommonData::setSoundEffectState( true );
			}
			Loading::m_loading->HttpGetHeadImgAsyn();
#else
			Loading::m_loading->HttpGetMyInfoAsyn( ret );
#endif

			//MsgMgr::sendUpdataGameMsg( atoi( AnalyseJson::logOnMsg.baseInfo.updataver.c_str() ) );
			//单机修改

			//SoundOutLogin();
		}
		else
		{
			showWidget( LOGINUI_WIDGET_TYPE_HINT );
		}
#endif
	}
}

void Loading::replaceScence(candyScenceType type)
{
	CCScene *pScene;
	Loading::scenceType = type;

	if(type == CANDY_SCENCE_MAIN_MAP && CommonData::m_isLoadedMapRes)
	{
		pScene = MainMap::scene( false );
		CCDirector::sharedDirector()->replaceScene( pScene );
	}
	else if(type == CANDY_SCENCE_PLAY_GAME && CommonData::m_isLoadedGameRes )
	{
		pScene = PlayGame::scene();
		CCTransitionCrossFade* reScene = CCTransitionCrossFade::create(REPLACE_SCENCE_FADE_TIME,pScene);
		CCDirector::sharedDirector()->replaceScene( pScene );
	}
	else
	{
		pScene = Loading::scene(type);
		CCTransitionCrossFade* reScene = CCTransitionCrossFade::create(REPLACE_SCENCE_FADE_TIME,pScene);
		CCDirector::sharedDirector()->replaceScene( reScene );
	}
}    

#include "CCLuaEngine.h"
bool Loading::init(void)
{
	if ( !CCLayer::init() )
		return false;

#ifdef CANDY_STATISITICAL_DATA
	/*if ( CANDY_SCENCE_DOWNLOAD == Loading::scenceType )
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_9, "");

	if(CANDY_SCENCE_MAIN_MAP == Loading::scenceType &&  CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=5)
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_46, (char*)CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString());

	if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType && 0 == CommonData::getMaxLevel() )	
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_56 );	
	else if(CANDY_SCENCE_PLAY_GAME == Loading::scenceType && 1 == CommonData::getMaxLevel() )
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_72 );
	else if(CANDY_SCENCE_PLAY_GAME == Loading::scenceType && 2 == CommonData::getMaxLevel() )
	AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_82 );*/

	if(Loading::scenceType == CANDY_SCENCE_PLAY_GAME)
	{
		/*if ( 10 >= CommonData::getMaxLevel() ) 
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_12, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());*/
	
		//新用户记录点
		if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
		{
			AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1006);
		}
	}

#endif
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;
	
	#ifdef USE_CANDY_BG
		CCSprite *bg;
		int bgImgNum = (CandyManager::currentLevel-1)/15 +1;
		bg = CCSprite::create(CCString::createWithFormat("Image/CandyGame/Background/Bg%d.jpg",bgImgNum)->getCString());
		bg->setAnchorPoint(ccp(0,0));
		bg->setPosition(ccp(0,0));

		CCSprite *bgTips= CCSprite::create(LOADING_TIPS_IMG);
		bgTips->setPosition(ccp(360,fixedScreenHeight*0.5f));
		bg->addChild(bgTips);
	#else
		CCScale9Sprite *bg;
		bg = CCScale9Sprite::create( LOADING_BACKGROUND_IMG );
		bg->setContentSize(CCSizeMake(TARGET_SCREEN_WIDTH, fixedScreenHeight));
		bg->setAnchorPoint(ccp(0,0));
		bg->setZOrder(9);

		CCSprite *content= CCSprite::create(LOADING_CONTENT_IMG);
		//ShaderSprite *content= ShaderSprite::create(LOADING_CONTENT_IMG);
		content->setPosition(ccp(360,fixedScreenHeight*0.5f));
		bg->addChild(content);

		CCSprite *content1= CCSprite::create("Image/CandyGame/Others/stageClearTips.png");
		//ShaderSprite *content= ShaderSprite::create(LOADING_CONTENT_IMG);
		content1->setPosition(ccp(360,fixedScreenHeight*0.8f));
		content1->setScale(0.7f);
		bg->addChild(content1);
		
		CCSprite *tips= CCSprite::create(LOADING_TIPS_IMG);
		tips->setPosition(ccp(360,fixedScreenHeight*0.5f -300));
		bg->addChild(tips);

		m_pLabelPercent = NULL;
		m_pLabelPercent = CCLabelTTF::create("0%","Arial",30); 
		m_pLabelPercent->setPosition(ccp(360,fixedScreenHeight*0.5f -350));
		m_pLabelPercent->setZOrder( 10 );
		addChild(m_pLabelPercent);

		if ( CANDY_SCENCE_DOWNLOAD == Loading::scenceType )
		{
			m_pLabelPercent->setString(CommonData::GetString( "app_loading_str" ).c_str());
		}

	#endif
	addChild(bg);
	bg->setTag(100);

	CCLog( "Loading ==> init " );
	return true;
}

void Loading::HttpGetMyInfoAsyn(bool state)
{
	if ( state )
	{
		AnalyseJson::logOnMsg;

		//单机修改
		//MsgMgr::sendGetFriendInfoMsg();
		//单机修改
	}

	CCLog( "Cocos HttpGetMyInfoAsyn==> state: [%d]", state );
}

void Loading::HttpGetFriendListAsyn(bool state)
{
	HeadDownMgr::Instance()->addHeadUrlToList(
		AnalyseJson::logOnMsg.baseInfo.id,
		AnalyseJson::logOnMsg.baseInfo.headPicUrl,
		PIC_TYPE_MYHEAD);
	HeadDownMgr::Instance()->startDownLoadPic();

	CCLog( "Cocos HttpGetFriendListAsyn==> state: [%d]", state );
}

void Loading::HttpGetHeadImgAsyn(void)
{
	CCScene *pScene = NULL;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	if ( CANDY_SCENCE_DOWNLOAD == Loading::scenceType )
	{
		CCLuaEngine* pEngine  = CCLuaEngine::defaultEngine();
		CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
		CandyMapData::initLoadLuaFile();
		MainMap::initMapLuaFile();
	}
#endif

//	CppCallJava::verifyLuas( AnalyseJson::logOnMsg.baseInfo.id, AnalyseJson::logOnMsg.stageInfo.size() );
	m_pLabelPercent->setString( CommonData::GetString( "app_loadlun_str" ).c_str());

	MsgMgr::sendGetChitchatSt();

	//单机修改
	//MsgMgr::sendGetFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id );
	//MsgMgr::sendGetWorldFriendForGuestMsg();

	MsgMgr::sendGetSystemTask( AnalyseJson::logOnMsg.baseInfo.id );

// 	HeadDownMgr::Instance()->addHeadUrlToList(
// 		AnalyseJson::logOnMsg.baseInfo.id,
// 		AnalyseJson::logOnMsg.baseInfo.headPicUrl,
// 		PIC_TYPE_MYHEAD);
// 	HeadDownMgr::Instance()->startDownLoadPic();

#ifdef CANDY_STATISITICAL_DATA
	//CppCallJava::sendRegeditOrLogin( 0 , AnalyseJson::logOnMsg.baseInfo.id);
	//char* id = (char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.id)->getCString();
	//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4003 );
#endif
	//单机修改

	initMainMapRes();
}

void Loading::initInterludeRes(void)
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/CandyInterludeAnim/NewProject.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/CandyIntereAnim2/guochang.ExportJson");
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/CandyIntereAnim2/tuzi.ExportJson");
}

void Loading::initPlayGameRes(void)
{
	if ( CommonData::m_isLoadedGameRes )
		return;
	CandyParticle::initCandyParticle();
	
#ifndef CLOSE_ARMATURE

 	
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RabbitAnim/RabbitShakehand/NewProject/RabbitShake01.ExportJson");
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RabbitAnim/RabbitShakehand/NewProject/RabbitShake02.ExportJson");
//	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RabbitAnim/RabbitRun/pb.ExportJson");
//  	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RabbitAnim/Rabbitwin/yingle.ExportJson");
//  	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RabbitAnim/Rabbitwin/shibaile.ExportJson");
 
 	//抽奖轮盘
  	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Rabbit/NewProject/NewProject.ExportJson");
  	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Rabbit/NewProject/NewProject1.ExportJson");
 
	//轮盘新人物
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/huipanzi/huipanzi.ExportJson");
	//神灯
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/guanzi/guanzi.ExportJson");
	//新手指引
//	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/Teach/NewTeeachAnim/xszy.ExportJson");

	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/qidong/qidong.ExportJson");

 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Audience/Audience01.ExportJson");
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Audience/Audience02.ExportJson");
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Audience/Audience03.ExportJson");
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Audience/Audience04.ExportJson");
 	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Image/CandyGame/RouletteAnim/Audience/Audience05.ExportJson");


#endif

	// 加载大图片特殊处理
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_GAME_ELEMENT, this, callfuncO_selector(Loading::loadingGameCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_GAME_BARRIER_TOP, this, callfuncO_selector(Loading::loadingGameCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_GAME_BARRIER_BOTTOM, this, callfuncO_selector(Loading::loadingGameCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_GAME_UI_LAYOUT, this, callfuncO_selector(Loading::loadingGameCallBack));  
//	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_GAME_UI_LAYOUT1, this, callfuncO_selector(Loading::loadingGameCallBack));  


	CommonData::m_isLoadedGameRes = true;
}
void Loading::initMainMapRes(void)
{	
	m_pLabelPercent->setString("0%");

	if ( CommonData::m_isLoadedMapRes )
		return;

	// 加载大图片特殊处理
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_MAINMAPUI0, this, callfuncO_selector(Loading::loadingMapCallBack));  
/*	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_MAINMAPUI1, this, callfuncO_selector(Loading::loadingMapCallBack));  */
	//CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_MAINMAPUI2, this, callfuncO_selector(Loading::loadingMapCallBack));  
	//CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_GEMEFF, this, callfuncO_selector(Loading::loadingMapCallBack));  

	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING1, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING2, this, callfuncO_selector(Loading::loadingMapCallBack));  
// 	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING3, this, callfuncO_selector(Loading::loadingMapCallBack));  
// 	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING4, this, callfuncO_selector(Loading::loadingMapCallBack));  
// 	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING5, this, callfuncO_selector(Loading::loadingMapCallBack));  
	//CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_COMMOND_SETTING6, this, callfuncO_selector(Loading::loadingMapCallBack));  

	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_LOGIN_LOGINUI1, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANDY_IMG_LOGIN_LOGINUI2, this, callfuncO_selector(Loading::loadingMapCallBack)); 

	/*CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP1, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP2, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP3, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP4, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP5, this, callfuncO_selector(Loading::loadingMapCallBack));  
	CCTextureCache::sharedTextureCache()->addImageAsync(CANY_IMG_MAP_BIGMAP6, this, callfuncO_selector(Loading::loadingMapCallBack)); */ 	

	CommonData::m_isLoadedMapRes = true;
}

void Loading::loadingMapCallBack( CCObject *obj )
{
	static int m_nNumberOfLoadedSprites = CANDY_RES_FORMAP_NUM + CANDY_RES_FORCOMMOND_NUM - 1;

	m_nNumberOfLoadedSprites--;
	char tmp[10];  
	
	sprintf(tmp,"%d%%",(int)(100 - ((float)m_nNumberOfLoadedSprites / (CANDY_RES_FORMAP_NUM + CANDY_RES_FORCOMMOND_NUM - 1)) * 100));  
	m_pLabelPercent->setString(tmp);//重设标签的内容 

	if ( 0 == m_nNumberOfLoadedSprites )
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANY_PLIST_MAP_MAINMAPUI0);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANY_PLIST_MAP_MAINMAPUI1);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANY_PLIST_MAP_MAINMAPUI2);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANY_PLIST_MAP_GEMEFF);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING1);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING2);
// 		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING3);
// 		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING4);
// 		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING5);
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_COMMOND_SETTING6);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_LOGIN_LOGINUI1);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_LOGIN_LOGINUI2);


		//this->removeChild(m_nNumberOfLoadedSprites, true); 

		//　数据加载完后进入主界面
		scenceType = CANDY_SCENCE_MAIN_MAP;
		CCScene *pScene = NULL;
		pScene = MainMap::scene(false);
		CCTransitionCrossFade* reScene = CCTransitionCrossFade::create(REPLACE_SCENCE_FADE_TIME,pScene);
		CCDirector::sharedDirector()->replaceScene(reScene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
#endif

	}		
}

void Loading::loadingGameCallBack( CCObject *obj )
{
	static int m_nNumberOfLoaded = CANDY_RES_FORGAME_NUM;
	m_nNumberOfLoaded --;

	char tmp[10];  
	sprintf(tmp,"%d%%",(int)(100 - ((float)m_nNumberOfLoaded / (CANDY_RES_FORGAME_NUM - 1)) * 100));  
	m_pLabelPercent->setString(tmp);//重设标签的内容 

	if ( 0 == m_nNumberOfLoaded )
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_GAME_ELEMENT);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_GAME_BARRIER_TOP);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_GAME_BARRIER_BOTTOM);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_GAME_UI_LAYOUT);
	//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(CANDY_PLIST_GAME_UI_LAYOUT1);

		CCScene *pScene = NULL;
		pScene = PlayGame::scene();
		CCTransitionCrossFade* reScene = CCTransitionCrossFade::create(REPLACE_SCENCE_FADE_TIME,pScene);
		CCDirector::sharedDirector()->replaceScene( reScene );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
#endif
	}
}

void Loading::showWidget( LoginWidgetType type )
{
	Layout* widget = NULL;

	switch( type )
	{
	case LOGINUI_WIDGET_TYPE_HINT:
		{
			widget = CommonWidgt::getSuccessUI( WIDGET_TYPE_LOADING, PROMPT_TYPE_NETERR );
		}
		break;

	case LOGINUI_WIDGET_TYPE_UPDATA:
		{
			widget = CommonWidgt::getUpdataGameUI( WIDGET_TYPE_LOADING );
		}
		break;

	default:
		break;
	}

	if ( widget )
	{
		getWidgetUILayer()->addWidget( widget ) ;


		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
		widget->setPosition( ccp(0,0) );

		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->setPosition( ccp (currentScreenWidth/2, currentScreenHeight/2));
		pImgDlg->setScale( 0.1f );
		pImgDlg->setVisible( true );
		pImgDlg->stopAllActions();

		CCActionInterval* pScale2 = CCScaleTo::create(0.24f, 1.08f, 1.08f);
		CCActionInterval * fadeout = CCFadeIn::create(0.24f); 
		CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale2,NULL);
		CCActionInterval* pScale3 = CCScaleTo::create(0.17f, 0.95f, 0.95f);
		CCActionInterval* pScale4 = CCScaleTo::create(0.17f, 1.02f, 1.02f);
		CCActionInterval* pScale5 = CCScaleTo::create(0.17f, 1.0f, 1.0f);
		pImgDlg->runAction( CCSequence::create(
			/*spawn1,*/
			spawn,
			pScale3,
			pScale4,
			pScale5,
			NULL
			));
	}
}

UILayer* Loading::getWidgetUILayer(void)
{
	if(! widgetUiLayer)
	{
		widgetUiLayer = UILayer::create();
		widgetUiLayer->setZOrder( 11 );
		this->addChild(widgetUiLayer);
	}
	return widgetUiLayer;
}

Loading::Loading( void ):
widgetUiLayer(NULL)
{

}

void Loading::UPdataBtnBtnCallback(CCObject* pSender)
{

	Layout* widget = CommonWidgt::getUpdataGameUI( WIDGET_TYPE_LOADING );
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>( widget->getChildByName( "m_img_dlg" ) );

	CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
	CCActionInterval * fadeout = CCFadeOut::create(0.2f);
	CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
	CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);

	pImgDlg->runAction(CCSequence::create(
		pScale,
		spawn,
		NULL)
		);
}

void Loading::NetworkErrBtnCallback( void )
{
	// 跳转到设置界面

		Layout* widget = CommonWidgt::getSuccessUI(WIDGET_TYPE_LOADING, PROMPT_TYPE_NETERR);
		UIImageView* pImgDlg = dynamic_cast<UIImageView*>( widget->getChildByName( "m_img_dlg" ) );

		CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
		CCActionInterval * fadeout = CCFadeOut::create(0.2f);
		CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
		CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);

		CCCallFuncND * funcall= CCCallFuncND::create(widget, callfuncND_selector(Loading::FunNDActionCallback), (void*)1);
		pImgDlg->runAction(CCSequence::create(
			pScale,
			spawn,
			funcall,
			NULL)
			);
	
}

void Loading::SoundOutLogin( void )
{
	//单机修改

	//　检测新老用户
	//MsgMgr::SendSoundOutLogin( AnalyseJson::logOnMsg.baseInfo.idx.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str() );

	//单机修改
}

void Loading::FunNDActionCallback( CCNode* sender, void* data )
{
	int tag = (int)data;
	CommonWidgt::releaseWidgt();

	//　获取平台数据
	//CppCallJava::getPlatfromInfo();
	//AnalyseJson::getCandPicPath();

	SoundOutLogin();
}

void Loading::onExit()
{
	CCLayer::onExit();

	removeChild(m_pLabelPercent);
// 	CommonWidgt::releaseWidgt();	
// 
// 	//CCArmatureDataManager::purge();
// 	CCSSceneReader::sharedSceneReader()->purgeSceneReader();
// 	//cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
// 	//cocos2d::extension::UIHelper::instance()->purgeUIHelper();
}
