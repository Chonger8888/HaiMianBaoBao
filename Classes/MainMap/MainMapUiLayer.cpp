#include "MainMapUiLayer.h"
#include "../PlayGame/PlayGameScene.h"
#include "../PlayGame/CandyManager.h"
#include "../Loading/LoadingScene.h"
#include "../MainMap/MainMapScene.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../CppCallJava/CppCallJava.h"
#include "../PlayGame/CandyRouletteStory.h"
#include "TollgatePage.h"
#include "PlayGame/CandyRouletteNew.h"

#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
#include "platform\third_party\win32\iconv\iconv.h" 
#pragma comment(lib,"libiconv.lib") 
#endif 
#include "ClippingTouchLayer.h"
#include "CandyPay\CandyPay.h"

using namespace CocosDenshion;
USING_NS_CC;


// Image Path
#define LOADING_PATH_IMGP	 		"Image/MainMapUi/m_loading.png"
#define TIPCO_PATH_IMGP				"Image/MainMapUi/m_img_msgtip.png"
#define TOOLSICO_PATH_IMGP			"Image/MainMapUi/Tools/m_img_toolPBG.png"
#define TOOLS_PATH_IMGN	 			"Image/MainMapUi/noticeico_N.png"
#define TOOLS_PATH_IMGP	 			"Image/MainMapUi/noticeico_P.png"


#define MSG_IMG_NOTHING 			"Image/MainMapUi/m_str_nothing.png"
#define MSG_STR_NOPROPMSG	 		"Image/MainMapUi/m_str_noporpmsg.png"
#define MSG_STR_NONOTIC 			"Image/MainMapUi/m_str_nonotic.png"
#define MSG_STR_NOMSG	 			"Image/MainMapUi/m_str_nomsg.png"
#define MSG_STR_NOFRIEND	 		"Image/MainMapUi/m_str_nofriend.png"

// Map ui Exportjson file for cocostudio!
#define MAP_EXPORTJSON_PATH_FOR_MAPTOOLBAR			"Image/MainMapUi/MainMapUi/MapToolbarUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_BUYLIFE				"Image/MainMapUi/MainMapUi/BuyGameLifeUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_FRIEND_LIST			"Image/MainMapUi/MainMapUi/FriendListUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_NOFRIEND_LIST		"Image/MainMapUi/MainMapUi/NoFriendListUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_SEACHFRIEND			"Image/MainMapUi/MainMapUi/SeachFriendUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_MESSAGE_LIST		"Image/MainMapUi/MainMapUi/MessageListUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_REMINDER			"Image/MainMapUi/MainMapUi/ReminderUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_SUCCEEDUI_BOX		"Image/MainMapUi/Tools/SucceedUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_CLIAIM_SUCCEED		"Image/MainMapUi/MainMapUi/ClaimSucUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_FEEDBACK			"Image/MainMapUi/MainMapUi/FeedbackUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_LACKLIFE			"Image/MainMapUi/MainMapUi/LifeLackUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_NOTICE				"Image/MainMapUi/MainMapUi/NoticeUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_CHANGEINFO			"Image/MainMapUi/Tools/ChangeInfoUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_GETHERSTAR			"Image/MainMapUi/MainMapUi/GetherStarUI.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_KNAPSACK			"Image/MainMapUi/MainMapUi/KnapsackUI.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_MAINTASK			"Image/MainMapUi/MainMapUi/MainTaskUI.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_DAILYTASK			"Image/MainMapUi/MainMapUi/DaytodayUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_TASK				"Image/MainMapUi/MainMapUi/CandyTaskUI.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_MYINFORMAT			"Image/MainMapUi/MainMapUi/MyInformatUi.ExportJson"
#define MAP_EXPORTJSON_PATH_FOR_REWARDVIP			"Image/MainMapUi/MainMapUi/RewardUI.ExportJson"

// The json will remove
#define FRIEND_INFO_LAYOUT_FILE			"Image/MainMapUi/MainMapUi/SingleFriendInfoUi.ExportJson"
#define CLIAMLIFE_LAYOUT_FILE			"Image/MainMapUi/MainMapUi/CliamlifeUi.ExportJson"


//　Define map data
#define CCCA(x)   (x->copy()->autorelease())
#define LEVEL_ENTRY_CCCP		(ccp(720.0f,0.0f))   // 右侧进入
//#define LEVEL_QUIT_CCCP		(ccp(720+420.0f,CCDirector::sharedDirector()->getWinSize().height/2))   // 左侧退出
#define LEVEL_QUIT_CCCP		(ccp(CCDirector::sharedDirector()->getWinSize().width/2  , CCDirector::sharedDirector()->getWinSize().height + CCDirector::sharedDirector()->getWinSize().height/2 ))   // 顶部侧退出
#define LEVEL_LENTRY_CCCP		(ccp(-720.0f,0.0f))   // 左侧退出

#define  PIC_HEAD_H		110
#define  PIC_HEAD_W		110

#if defined(DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
#define	LILE_MAX_NUM	5		// 生命值最大个数
#else
#define	LILE_MAX_NUM	10		// 生命值最大个数
#endif

/*UTF8转为GB2312*/
std::string u2a(const char *inbuf);

/*GB2312转为UTF8*/
std::string a2u(const char *inbuf);

#define TAG_TOLLGATE_VIEW	1988
#define TAG_LEVEL_LAYER		1989

MainMapUiLayer * MainMapUiLayer::m_mainmapuilayer = NULL;



MainMapUiLayer::MainMapUiLayer():
m_lifeTime(NULL),
m_BuyPrompt(NULL),
m_FntPrompt(NULL),
	m_FntUnlockPrompt(NULL),
	widgetUiLayer(NULL),
	rewardlayout(NULL),
	//LifeListLayout(NULL),
	friendInfoLayout(NULL),
	friendListLayout (NULL),
	noFriendListLayout(NULL),
	messageListLayout(NULL),
	LevelInfoLayout(NULL),
	m_loadArmature(NULL),
	m_ploading(NULL),
	reminderLayout(NULL),
	succeeddlgLayout(NULL),
	levelLayout(NULL),
	cliamsucLayout(NULL),
	feedbacklayout(NULL),
	LackLifelayout(NULL),
	CliamLifelayout(NULL),
	changeinfoLayout(NULL),
	gembuyLayout(NULL),
	seachfriendLayout(NULL),
	getherStarLayout(NULL),
	knapsackLayout(NULL),
	mainTasklayout(NULL),
	mapToolbarlayout(NULL),
	dailyTaskExtralayout(NULL),
	tasklayout(NULL),
	myInformatlayout(NULL),
	m_pMsgTip(NULL),
	//m_friendBut(NULL),
	//m_MessageBut(NULL),
	m_gameLifeBut(NULL),
	m_messageListBut(NULL),
	m_friendListBut(NULL),
	//m_wemeChatBut(NULL),
	m_GetherStarBut(NULL),
	m_KnapsacBut(NULL),
	m_mainTaskBut(NULL),
	m_gameShopBut(NULL),
	// m_pSeachEditBox(NULL),
	m_pEditBox(NULL),
	noticeLayout(NULL),
	m_toolsT(NULL),
	//m_pGemNum(NULL),
	//chatMsgNumBg(NULL),
	m_pAddLifeTips(NULL),
	m_pFullLifeTips(NULL),
	m_ClaimLifeNum(0),
	m_isKey(false),
	m_isEnableKey(true),
	m_AsynFlag(false),
	m_isNetMessage(false),
	m_isNetHistoryMsg(false),
	m_isNetNofriendMsg(false),
	m_isShowMessage(false),
	mDelayBackKey(true)
	,tollgaetPageview(NULL)
	,levelSelectLayer(NULL)
{

}
MainMapUiLayer::~MainMapUiLayer()
{

}

bool MainMapUiLayer::init(void)
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_mainmapuilayer = this;

	scheduleUpdate();
	this->schedule(schedule_selector(MainMapUiLayer::updateLife), 1.0f);
	setKeypadEnabled(true);

	initMapMenu();
	SwitchPageViewAndLevelLayer();

	

	if (  GAME_STATE_SUCCEE_NEXT == MainMap::m_GameState || GAME_STATE_SUCCEE == MainMap::m_GameState  )
		this->schedule( schedule_selector(MainMapUiLayer::updataWorldRankedNumber), 0.05f, kCCRepeatForever, 0 );

	//　download head ico
	std::list<UserFriendInfoStr>::iterator p;
	int len = 0;
	len = AnalyseJson::friendInfoMsg.friendInfo.size();
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();
	for ( int i = 0; i<len; i++, p++)
	{
		CCLog("MainMapUiLayer::init ==> ID:%d  IDX:%s",p->id, p->idx.c_str() );
		HeadDownMgr::Instance()->addHeadUrlToList(
			p->id,
			p->headPicUr,
			PIC_TYPE_FRIEND );
	}
	HeadDownMgr::Instance()->startDownLoadPic();

	CommonData::getMyMessage();

	// set Panel TouchEnabled
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	m_pPanel = UIPanel::create();
	m_pPanel->setSize( CCSizeMake(currentScreenWidth,currentScreenHeight ));
	m_pPanel->setColor( ccc3(150,150,150));
	m_pPanel->setPosition( ccp(0,0) );
	m_pPanel->setZOrder( 1 );
	m_pPanel->setBackGroundColorType( LAYOUT_COLOR_SOLID );
	m_pPanel->setBackGroundColor( ccc3(0,0,0) );
	m_pPanel->setBackGroundColorOpacity( 128 );
	m_pPanel->setVisible( false );
	getWidgetUILayer()->addWidget( m_pPanel );

	//Layout* nTemp = getPropBuyLayout( 33 );
	if ((MainMap::getPassStageNum() - 1 <= CandyManager::currentLevel)&&( GAME_STATE_SUCCEE_NEXT == MainMap::m_GameState || GAME_STATE_SUCCEE == MainMap::m_GameState))
	{
		m_pPanel->setTouchEnabled( true );
	}

	// 最大关卡为1时自动弹出
	if ( 1 ==  MainMap::getPassStageNum() )
	{
		this->scheduleOnce(schedule_selector(MainMapUiLayer::FirstLevelInfoDelay), 1.0f );		
	}
	
	return true;
}

void MainMapUiLayer::onEnter(void)
{
	CCLayer::onEnter();
	if (CommonData::m_isShowChoujiang)
	{
		CommonData::m_isShowChoujiang = false;
		showMapWidget(MAP_WIDGET_ROULETTE_DLG);
	}
	if (CommonData::m_isShowBuyLife)
	{
		CommonData::m_isShowBuyLife = false;
		//showMapWidget(MAP_WIDGET_LACKLIFE_DLG);
		//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

	}
}

void MainMapUiLayer::onExit(void)
{
	CCLayer::onExit();

	if ( rewardlayout )
	{
		rewardlayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( rewardlayout );
	}
	/*if ( LifeListLayout )
	{
		LifeListLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( LifeListLayout );
	}*/

	if ( friendInfoLayout )
	{
		friendInfoLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( friendInfoLayout );
	}

	if ( friendListLayout)
	{
		friendListLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( friendListLayout );
	}

	if ( noFriendListLayout )
	{
		noFriendListLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( noFriendListLayout );
	}

	if ( messageListLayout )
	{
		messageListLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( messageListLayout );
	}

	if ( LevelInfoLayout )
	{
		LevelInfoLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( LevelInfoLayout );
	}

	if ( cliamsucLayout )
	{
		cliamsucLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( cliamsucLayout );
	}

	if ( feedbacklayout )
	{
		feedbacklayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( feedbacklayout );
	}

	if ( mapToolbarlayout )
	{
		mapToolbarlayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( mapToolbarlayout );
	}

	if ( LackLifelayout )
	{
		LackLifelayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( LackLifelayout );
	}

	// 	if ( CliamLifelayout )
	// 	{
	// 		CliamLifelayout->removeAllChildrenAndCleanUp(true);
	// 		CC_SAFE_RELEASE_NULL( CliamLifelayout );
	// 	}

	if ( noticeLayout )
	{
		noticeLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( noticeLayout );
	}

	if ( changeinfoLayout )
	{
		changeinfoLayout->removeAllChildrenAndCleanUp(true);
		getWidgetUILayer()->removeWidget( changeinfoLayout );
	}

	if ( seachfriendLayout )
	{
		seachfriendLayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( seachfriendLayout );
	}

	if ( knapsackLayout )
	{
		knapsackLayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( knapsackLayout );
		CC_SAFE_RELEASE_NULL( knapsackLayout );
	}

	if ( getherStarLayout )
	{
		getherStarLayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( getherStarLayout );
		//CC_SAFE_RELEASE_NULL( getherStarLayout );
	}

	if ( mainTasklayout )
	{
		mainTasklayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( mainTasklayout );
		//CC_SAFE_RELEASE_NULL( getherStarLayout );
	}
	if ( dailyTaskExtralayout )
	{
		dailyTaskExtralayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( dailyTaskExtralayout );
		//CC_SAFE_RELEASE_NULL( getherStarLayout );
	}

	if ( tasklayout )
	{
		tasklayout->removeAllChildrenAndCleanUp( true );
		getWidgetUILayer()->removeWidget( tasklayout );
	}


	CandyStageIntro::releaseLayout();
	CommonWidgt::releaseWidgt();
	CommonData::ReleaseXml();

	//	CCArmatureDataManager::purge();
	CCSSceneReader::sharedSceneReader()->purgeSceneReader();
	//	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
	//	cocos2d::extension::UIHelper::instance()->purgeUIHelper();
}

// 修改首次登录时关卡信息弹出延时 
void MainMapUiLayer::FirstLevelInfoDelay(float t)
{
	//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LEVEL_INFO, 1 );
}

void MainMapUiLayer::setAsynFlag(bool state)
{
	m_AsynFlag = state;
	CCLog( "MainMapUiLayer::setAsynFlag  %d",  m_AsynFlag);
}

void MainMapUiLayer::sendInviteNofriendmsg(void)
{
	std::string nofriendStr;

	std::list<UserNoFriendIdxStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.nofriend_idx.begin();

	for (int i = 0; i< (int)AnalyseJson::friendInfoMsg.nofriend_idx.size(); i++)
	{
		nofriendStr.append(p->idx.c_str());
		nofriendStr.append("|");
		p++;
	}

	MsgMgr::sendFilterNoFriend( (char *)AnalyseJson::friendInfoMsg.myIdx.c_str(), (char *)nofriendStr.c_str());
}

void MainMapUiLayer::update(float time)
{
	if(CommonData::m_buyGemState && 0 == CommonData::m_buytype)
	{
		CommonData::m_buyGemState = false;
		MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
	}

	if ( CommonData::m_mapLayerBuyFinish )
	{
		CommonData::m_mapLayerBuyFinish = 0;
		MainMapUiLayer::m_mainmapuilayer->refreshLifeUI();
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

		return;
	}

	if ( CommonData::m_unLockAllLevel )
	{
		CommonData::m_unLockAllLevel = 0;
		CommonData::unLockAllTheLevel();
		CCNotificationCenter::sharedNotificationCenter()->postNotification(unlockAllLvl,NULL);
	}
	if ( CommonData::m_isFirstEnterGame )
	{
		CommonData::m_isFirstEnterGame = 0;
		if (!CommonData::m_isPlayNewUserAction && CommonData::getMaxLevel() < 1)
		{
			//发送消息，第一次进入游戏
			CCNotificationCenter::sharedNotificationCenter()->postNotification(IntoGameLvl1,NULL);
		}
	}
	if ( CommonData::m_isExitGame )
	{
		CommonData::m_isExitGame = 0;

		HeadDownMgr::Destroy();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
		CCTextureCache::sharedTextureCache()->removeUnusedTextures();

		CCArmatureDataManager::purge();
		CCSSceneReader::sharedSceneReader()->purgeSceneReader();
		cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
		cocos2d::extension::UIHelper::instance()->purgeUIHelper();
		CCHttpClient::getInstance()->destroyInstance();

		CCDirector::sharedDirector()->end();
	}

	if ( m_isShowMessage )
	{
		m_isShowMessage = false;
		MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_SUCCEEDUI_DLG, PROMPT_TYPE_SUBMITSUC);
	}

	// 购买生命成功
	if ( CommonData::m_buyState) 
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
		CCLog( "MainMapUiLayer::CommonData::m_buyState");
		CommonData::m_buyState = false;
	}
	else if ( CommonData::m_isBuyLife )
	{
		CommonData::m_isBuyLife = false;
		MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
		updataLackLifeUi();
	}

	if ( AnalyseJson::logOnMsg.baseInfo.Chitchat )
		updateChatMsgNum();
	if( !m_AsynFlag )
		return;

	CCLog( "MainMapUiLayer::update");
	MainMapUiLayer::m_mainmapuilayer->onNetEvent( HTTP_NETENENT_GETNOFRIENDINFO );
	m_AsynFlag = false;
}

void MainMapUiLayer::updateLife(float dt)
{
	if(CommonData::m_LastLifeNum != AnalyseJson::logOnMsg.lifeInfo.lifeNum)
	{
		CommonData::m_LastLifeNum = AnalyseJson::logOnMsg.lifeInfo.lifeNum;
	}
}

void MainMapUiLayer::updateChatMsgNum(void)
{	

}

void MainMapUiLayer::onNetEvent(int state)
{
#ifdef CANDY_VERSIONS_FOR_SINGLE
	return;
#endif
	CCSize size;
	CCLog( "MainMapUiLayer==>onNetEvent  state:%d", state);
	switch ( state )
	{
	case HTTP_NETENTNT_GETMYWORLDRANKED:
		{
			/*UILabelBMFont* pMyWorldRanked = dynamic_cast<UILabelBMFont*>(mapToolbarlayout->getChildByName("FntAtlasMyRank")); 

			if ( pMyWorldRanked )
				pMyWorldRanked->setText( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.myWorldRanked )->getCString() );*/
		}
		break;

	case HTTP_NETENTNT_GETMYALLMESSAGE:
		{
			HttpGetMyMessageAsyn();
		}
		break;
	case HTTP_NETENTNT_UNLOCKMAINTASK:
		{
			std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
			for (; item!=AnalyseJson::taskTable.mainTask.end(); item++)
			{
				if (item->taskid == AnalyseJson::taskTable.buytaskid )
				{
					item->lockstate = 0;
					AnalyseJson::taskTable.buytaskid = 0;
				}
			}
			MainMapUiLayer::m_mainmapuilayer->addMainTaskToList();

		}
		break;
	case HTTP_NETENTNT_GETFRIENDLIST:
		{
			if ( MainMapUiLayer::m_mainmapuilayer && MainMapUiLayer::m_mainmapuilayer->friendListLayout )
				MainMapUiLayer::m_mainmapuilayer->addFriendtoList();
		}
		break;
	case HTTP_NETENTNT_BUYFRIENDLIMIT:
		{
			showBuyPrompt(1);
			if ( m_mainmapuilayer->friendListLayout )
			{
				UILabelAtlas* pMaxFriendNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->friendListLayout->getChildByName( "FriendMaxNum" ));
				pMaxFriendNum->setStringValue( CCString::createWithFormat("%d", AnalyseJson::friendInfoMsg.friendMaxNum )->getCString() );
			}
		}
		break;
	case HTTP_NETENTNT_GEMBUYVIP:
		{
			QuitMapWidgetCallback();

			showBuyPrompt(1);
			setDailyTask();
			MainMap::m_mainmap->setVipHead();
		}
		break;
	case HTTP_NETEVENT_LOGON:
		break;
	case HTTP_NETENENT_LEVELSCORE:
		break;
	case HTTP_NETENENT_GETFRIENDINFO:
		break;
	case HTTP_NETENENT_ALLACCEPTHANDSEL:	//全部接受别人赠送的生命及道具
		break;

	case HTTP_NETENENT_FILTERNOFRIEND://过滤邀请第三方好友信息
		{
			string nofriendStr;

			std::list<UserFilterIdxStr>::iterator p;
			p = AnalyseJson::filterFriend.FilterIdx.begin();

			for (int i = 0; i< (int)AnalyseJson::filterFriend.FilterIdx.size(); i++)
			{
				nofriendStr.append(p->idx.c_str());
				nofriendStr.append("|");
				p++;
			}

			MsgMgr::send3PartyGetNoFriendInfoMsg( (char *)nofriendStr.c_str() );
		}
		break;

	case HTTP_NETENENT_GETNOFRIENDINFO:  //	获取非好友的详细信息
		{
			AnalyseJson::nofriendInfoMsg.nofriend;

			std::list<UserNoFriendInfoStr>::iterator p;
			int len = 0;
			len = AnalyseJson::nofriendInfoMsg.nofriend.size();
			p = AnalyseJson::nofriendInfoMsg.nofriend.begin();
			for ( int i = 0; i<len; i++, p++)
			{

				HeadDownMgr::Instance()->addHeadUrlToList(
					p->id,
					p->headPicUr,
					PIC_TYPE_FRIEND );
				CCLog( "onNetEvent  addHeadUrlToList idx:%s",  p->idx.c_str() );
			}
			HeadDownMgr::Instance()->startDownLoadPic();

			m_isNetNofriendMsg = true;
			addNofriendtoList();
		}

		break;

	case HTTP_NETENENT_GETLIFEPRICE:	//获取生命基本属性信息
		HttpGetLifePriceAsyn();
		break;

	case HTTP_NETENTNT_GEMBUYLIFE:
	case HTTP_NETENENT_BUYLIFE:	//购买生命
		HttpBuyLifeAsyn();
		break;

	case HTTP_NETENENT_HANDSELLIFE:	//赠送生命
		HttpHandselLife();
		break;

	case HTTP_NETENENT_GETHANDSELLIFE: //获得赠送生命的消息
		HttpGetHandselLifeAsyn();
		break;

	case HTTP_NETENTNT_INVITEFRIENDMSG:
		m_isNetMessage = true;
		HttpGetInviteFriendmsgAsyn();
		break;

	case HTTP_NETENENT_ACCEPTLIFE:	//读取赠送用户生命消息
		{
			UILabelAtlas* pCandyMoneyLabel = dynamic_cast<UILabelAtlas*>( mapToolbarlayout->getChildByName("NumberCandyCandy") );
			if ( pCandyMoneyLabel )
				pCandyMoneyLabel->setStringValue( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString() );
			//HttpAcceptLife();
		}
		break;

	case HTTP_NETENENT_CONSUMELIFE: //消耗生命
		HttpGetConsumeLifeAsyn();
		break;

	case HTTP_NETENENT_REMOVESYSLIFE:	//删除系统赠送生命
		break;

	case HTTP_NETENENT_ADDSYSLIFE:	//添加系统赠送生命
		HttpGetAddSysLifeAsyn();
		break;

	case HTTP_NETENENT_GETPROPINFO:	//获取游戏道具属性信息
		break;

	case HTTP_NETENENT_BUYPROP:	//购买道具
		break;

	case HTTP_NETENENT_HANDSELPROP:	//赠送道具
		HttpHandselPropAsyn();
		break;

	case HTTP_NETENENT_GETHANDSELPROP:	//获得赠送道具的消息
		HttpGetHandselPropAsyn();
		break;

	case HTTP_NETENENT_CLAIMPROP:	//索要道具
		HttpClaimPropAsyn();
		break;

	case HTTP_NETENENT_GETCLAIMEDPROP:		//获得索要道具的消息
		m_isNetMessage = true;
		HttpGetClaimedPropAsyn();
		break;

	case HTTP_NETENENT_CONSUMEPROP:	//消耗道具
		break;

	case HTTP_NETENENT_GETUSERPROP:	//通过用户ID和道具ID获取用户道具信息
		break;

	case HTTP_NETENENT_GETCHATRECORD:	//通过用户ID获取用户道具历史消息
		m_isNetHistoryMsg = true;
		HttpGetChatRecordAsyn();
		break;

	case HTTP_NETENTNT_GETNOTICEMSG:
		{
			UIScrollView* pScroll = dynamic_cast<UIScrollView*>(m_mainmapuilayer->noticeLayout->getChildByName( "noticelist" ));

			UITextArea* pNotice = (UITextArea*)pScroll->getChildByName("noticetext");

			UIImageView* pNoNotice = NULL;
			pNoNotice = (UIImageView*)pScroll->getChildByName( "nonoticeico" );
			setLoading( false );
			if ( -1 == AnalyseJson::noticeStr.state)
			{
				if ( !pNoNotice )
				{
					pNoNotice = UIImageView::create();
					pNoNotice->setName("nonoticeico");
					pNoNotice->setTexture( MSG_IMG_NOTHING );
					pNoNotice->setPosition(ccp( 275,350 ));
					pScroll->addChild( pNoNotice );

					UIImageView* pStrMsg = UIImageView::create();
					pNoNotice->addChild( pStrMsg );
					pStrMsg->setTexture( MSG_STR_NONOTIC );
					pStrMsg->setVisible( true );
					pStrMsg->setPosition(ccp(0,-150 ));
				}
				pNotice->setText("");
				pNoNotice->setVisible( true );
			}
			else
			{
				//pNotice->setTextAreaSize()
				pNotice->setText( AnalyseJson::noticeStr.noticeDate.c_str());
				size = pNotice->getSize();

				if (pScroll->getSize().height < size.height)
				{
					pScroll->setInnerContainerSize(size);
					pNotice->setPosition( ccp(0, size.height));
				}
				else
				{
					pScroll->setInnerContainerSize(CCSizeMake(550,600));
					pNotice->setPosition( ccp(0, pScroll->getSize().height));
				}

				//size = CCSizeMake(0,0)	
				pScroll->setTouchEnabled( true );
				if (pNoNotice)
					pNoNotice->setVisible( false );
			}
		}
		break;

	case HTTP_NETENTNT_SEACHFRIENDRESULT:
		{
			setLoading( false );
			addSeachFriendTolist();
		}
		break;
	}
}

#define CCCA(x) (x->copy()->autorelease())
void MainMapUiLayer::initMapMenu(void)
{
#if defined( CANDY_VERSIONS_FOR_SINGLE ) 
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

	mapToolbarlayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_MAPTOOLBAR));
	getWidgetUILayer()->addWidget((mapToolbarlayout));
	
	UIImageView* maplayout = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("map_layout"));
	maplayout->setPosition(ccp(0,currentScreenHeight));

	// 设置
	m_pTools = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnSetting"));
	m_pTools->setTouchEnabled( true );
	m_pTools->setTag( TAG_SETTIONG_TOOLSMENU_TIEM );
	m_pTools->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	m_pTools->setPosition(ccp(0,currentScreenHeight));
	m_pTools->isEffects( true );

#else

	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;
	float nDelayTime1 = 0.08f;
	float nDelayTime2 = 0.041f;

	mapToolbarlayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_MAPTOOLBAR));
	mapToolbarlayout->setTouchEnabled(true);
	getWidgetUILayer()->addWidget((mapToolbarlayout));

	UIImageView* maplayout = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("map_layout"));
	maplayout->setPosition(ccp(0,currentScreenHeight));

	m_toolsT = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("map_topIco"));
	m_toolsT->setTouchEnabled( true );

	UIImageView* pTimeShow = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("showtimebg"));
	pTimeShow->setTouchEnabled( true );
	pTimeShow->setTag( TAG_BUYLIFE_TOOLSMENU_ITEM );
	pTimeShow->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); 

	m_pAddLifeTips = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("addlife_tips"));
	m_pAddLifeTips->setTouchEnabled( true );
	m_pAddLifeTips->setTag( TAG_BUYLIFE_TOOLSMENU_ITEM );
	m_pAddLifeTips->setVisible( false );
	m_pAddLifeTips->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); 

	m_pFullLifeTips = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("lifefull"));

	// 生命
	m_gameLifeBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("lifebtn"));
	m_gameLifeBut->setTouchEnabled( true );
	m_gameLifeBut->setTag( TAG_BUYLIFE_TOOLSMENU_ITEM );
	m_gameLifeBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); 
	m_gameLifeBut->isEffects( true, nDelayTime1+nDelayTime2 );

	CCNode* particle = CandyParticle::displayCandyParticle(CANDY_MAP_ACTIVE_LOVELIFE, ccp(0,-15));
	particle->setZOrder( 10 );
	m_gameLifeBut->getRenderer()->addChild( particle );

	//糖果币
	UIImageView* candyIco = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ShowCandyMoney"));
	candyIco->setTouchEnabled(true);
	candyIco->addReleaseEvent(this,coco_releaseselector(MainMapUiLayer::ShowRoulete));

	

	// 宝石
	//m_pGemNum = dynamic_cast<UILabelAtlas*>(mapToolbarlayout->getChildByName("gemnumstr"));
	//m_pGemNum->setStringValue((char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.gemNum)->getCString());

	//UIButton* GamegemBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("gembtn"));
	//GamegemBut->setVisible(false);
	/*GamegemBut->setTouchEnabled( true );
	GamegemBut->setScale( 1.2f );
	GamegemBut->setTag( TAG_BUYGEM_TOOLSMENU_ITEM );		
	GamegemBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); */

	//UIImageView* Gamegembg = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("showgembg"));
	//Gamegembg->setVisible(false);
	//Gamegembg->setTag( TAG_BUYGEM_TOOLSMENU_ITEM );		
	//Gamegembg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); 

	// 用户生命个数
	const char *nlifenum = CCString::createWithFormat("%d",  AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();//itoa(AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	m_plifeNum = dynamic_cast<UILabelAtlas*>(mapToolbarlayout->getChildByName("lifenum"));
	m_plifeNum->setStringValue( nlifenum );

	// 倒计时
	m_lifeTime = dynamic_cast<UILabelAtlas*>(mapToolbarlayout->getChildByName("LabelAtlasLifeTime"));
	m_lifeTime->setVisible( false );
//	this->schedule(schedule_selector(MainMapUiLayer::UpdataCountDown), 1, kCCRepeatForever, 0);
	//runGemAnimation();

	//　糖果币数量
	UILabelAtlas* pCandyMoneyLabel = dynamic_cast<UILabelAtlas*>( mapToolbarlayout->getChildByName("NumberCandyCandy") );
	pCandyMoneyLabel->setStringValue( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString() );
	//转盘
	UIButton* zhuanpanBtn = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnZhuanpan"));
	zhuanpanBtn->setTouchEnabled(true);
	zhuanpanBtn->setTag( TAG_ROULETTE_TOOLSMENU_ITEM );
	zhuanpanBtn->isEffects(true);
	zhuanpanBtn->addReleaseEvent(this,coco_releaseselector(MainMapUiLayer::toolsMenuCallback));

	//m_friendBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnFriend")); 
	//m_MessageBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnMessages")); 
	//m_GetherStarBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnGetherStar")); 
	//m_mainTaskBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnMainTask")); 

	//任务
	/*UIButton* pBtnTask = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnTask" ));
	UIButton* pBtnNotice = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnNotice" ));
	UIButton* pBtnSignIn = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "btnSiginIn" ));

	pBtnTask->setNormalTexture( "res_mapmenu/BtnTaskN.png", UI_TEX_TYPE_PLIST );
	pBtnTask->isEffects( true );
	pBtnTask->setTag( TAG_TASK_TOOLSMENU_ITEM );
	pBtnTask->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	pBtnTask->setTouchEnabled( true );

	if ( AnalyseJson::unLockConfig.starTask > CommonData::getMaxLevel() )
		pBtnTask->setNormalTexture( "res_mapmenu/BtnTaskD.png", UI_TEX_TYPE_PLIST );*/
	


	// 背包
	/*UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));
	pBtnMyInformat->setTag( TAG_KNAPSACK_TOOLSMENU_TIEM );
	pBtnMyInformat->isEffects( true,nDelayTime1+nDelayTime2*3 );
	pBtnMyInformat->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));*/

	//　任务可领取提示
	/*UIImageView* pImgNewTaskStr = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ImgNewTaskStr"));
	pImgNewTaskStr->setVisible( false );
	if ( getTaskLetRewardStatus() )
	{
		createDownImgPrompt( pBtnTask->getPosition(), pBtnTask->getName() );
		pImgNewTaskStr->setVisible( true );
	}

	pBtnNotice->setVisible( false );*/
	
	//　签到
	//pBtnSignIn->setTag( TAG_SIGNIN_TOOLSMENU_ITEM );		
	//pBtnSignIn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback)); 
	//pBtnSignIn->isEffects( true );

	// 好友list
	// 消息list
	//m_friendBut->isEffects( true,nDelayTime1+nDelayTime2*3 );
	//m_MessageBut->isEffects( true,nDelayTime1+nDelayTime2*3 );


	//m_friendBut->setTouchEnable( true );
	//m_friendBut->setTag( TAG_FRIENDLIST_TOOLSMENU_TIEM  );
	//m_friendBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	//m_friendBut->setNormalTexture( "res_mapmenu/BtnFriendN.png", UI_TEX_TYPE_PLIST );

	/*UIImageView* pImgNewFriendStr = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ImgNewFriendStr"));
	pImgNewFriendStr->setVisible( false );*/

	if ( AnalyseJson::unLockConfig.friendFun <= CommonData::getMaxLevel() )
	{
		//m_MessageBut->setVisible( true );
		//m_MessageBut->setTouchEnable( true );
		//m_MessageBut->setTag( TAG_MESSAGELIST_TOLLSMENU_TIEM  );
		//m_MessageBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	}
	else
	{
		//m_friendBut->setNormalTexture( "res_mapmenu/BtnFriendD.png", UI_TEX_TYPE_PLIST );

		//m_MessageBut->setVisible( false );
		//m_MessageBut->setTouchEnabled( false );
	}
	
	// 聊天
	/*m_wemeChatBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btn_wemechat")); 
	m_wemeChatBut->setTouchEnable( true );
	m_wemeChatBut->setTag( TAG_WEMECHCAT_TOOLSMENU_ITEM  );
	m_wemeChatBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	m_wemeChatBut->isEffects( true,nDelayTime1+nDelayTime2*4 );*/

	// 设置
	m_pTools = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnSetting"));

	m_pTools->setTouchEnabled( true );
	m_pTools->setTag( TAG_SETTIONG_TOOLSMENU_TIEM );
	m_pTools->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	m_pTools->isEffects(true,nDelayTime1+nDelayTime2*5  );

	//返回到pageview
	m_BackPageviewBtn = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("BtnSetting_0"));
	m_BackPageviewBtn->setTouchEnabled( false );
	m_BackPageviewBtn->setVisible(false);
	m_BackPageviewBtn->setTag( TAG_BACK_TO_PAGEVIEW_ITEM );
	m_BackPageviewBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BackTopageview));
	m_BackPageviewBtn->isEffects(true,nDelayTime1+nDelayTime2*5  );

	// 游戏商城
	m_gameShopBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnGameShop")); 
	m_gameShopBut->setTouchEnable( true );
	m_gameShopBut->setTag( TAG_GAMESHOP_TOOLSEMNU_TIEM  );
	m_gameShopBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	m_gameShopBut->isEffects( true,nDelayTime1+nDelayTime2*8 );

	// VIP
	UIButton* m_gameVIPBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnGameVip")); 
	m_gameVIPBut->setVisible(false);
	//m_gameVIPBut->setTouchEnable( true );
	//m_gameVIPBut->setTag( TAG_VIP_TOOLSEMNU_TIEM  );
	//m_gameVIPBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	//m_gameVIPBut->isEffects( true );


	// 活动礼包
	UIButton* m_gameGiftBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnGameGift")); 
	if(CommonData::m_GiftIDBuyNow != 0  )
	{
		m_gameGiftBut->setTouchEnable( true );
		m_gameGiftBut->setTag( TAG_ACTIVEGIFT_TOOLSMENU_ITEM  );
		m_gameGiftBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
		m_gameGiftBut->isEffects(true);
// 		m_gameGiftBut->runAction(CCRepeatForever::create( CCSequence::create(
// 			CCSpawn::create(CCTintTo::create(0.5, 255, 255, 220), CCScaleTo::create( 0.5f, 1.2f), NULL), 
// 			CCSpawn::create(CCTintTo ::create(0.5, 220, 180, 107), CCScaleTo::create( 0.5f, 1.0f), NULL), 
// 			NULL) ));
	}
	else if(CommonData::m_GiftIDBuyNow == 0)
	{
		m_gameGiftBut->setVisible(false);
		m_gameGiftBut->setTouchEnable( false );
	}

	// 世界排名
	//UIButton* worldRankBtn = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("btnGameRank")); 
	//worldRankBtn->setTouchEnable( true );
	//worldRankBtn->setTag( TAG_WORLDRANK_TOOLSMENU_ITEM  );
	//worldRankBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));
	//worldRankBtn->isEffects( true,nDelayTime1+nDelayTime2*8 );

	/*UILabelBMFont* pMyWorldRanked = dynamic_cast<UILabelBMFont*>(mapToolbarlayout->getChildByName("FntAtlasMyRank")); 
	pMyWorldRanked->setText( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.myWorldRanked )->getCString() );*/

	//chatMsgNumBg = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("chattip"));

	//m_messagetips = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("messagetips"));
	//m_messagetips->setVisible( false );

	// 四九游显示用户ID
	UILabel* userId = dynamic_cast<UILabel*>(mapToolbarlayout->getChildByName("LabeluserID"));
	userId->setVisible( false );



#endif

}


void MainMapUiLayer::toolsMenuCallback(CCObject*pSender)
{
	UIButton* pMenuBtn = (UIButton*)pSender;
	int index = pMenuBtn->getTag();

	if ( TAG_WEMECHCAT_TOOLSMENU_ITEM !=  index) pMenuBtn->setTouchEnabled( false );
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	// 移除有箭头的提示
	char pTagname[20];
	sprintf(pTagname, "%sprompt", pMenuBtn->getName() );
	UIImageView* pPrompt = (UIImageView*)pMenuBtn->getParent()->getChildByName( pTagname );
	if ( pPrompt ) pPrompt->removeFromParent();

	switch(index)
	{
	case TAG_ROULETTE_TOOLSMENU_ITEM:
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_ROULETTE_DLG );
		}
		break;
	case TAG_SIGNIN_TOOLSMENU_ITEM:
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_SIGNIN , 0);
		}
		break;

	case TAG_ACTIVEGIFT_TOOLSMENU_ITEM:
		{
			int currentId = CommonData::m_GiftIDBuyNow;

			if(currentId == 4)
			{
				CommonData::m_buytype = GameGift_Level1;
			}
			else if(currentId == 5)
			{
				CommonData::m_buytype = GameGift_Level2;
			}
			else if(currentId == 6)
			{
				CommonData::m_buytype = GameGift_Level3;
			}
			//新版支付
			MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PAY_DLG,CommonData::m_buytype);
		//	CandyPay::getInstance()->RequestCandyOrder(CommonData::m_buytype);
		//	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_GIFT_DLG , 0);
		}
		break;

	case TAG_BUYLIFE_TOOLSMENU_ITEM:
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );
		//	CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_LIFE);

			MsgMgr::sendGetLifePriceMsg();
		}
		break;

	case TAG_BUYGEM_TOOLSMENU_ITEM:
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_BUYGEM_LIST );
		}
		break;

	case TAG_WEMECHCAT_TOOLSMENU_ITEM:
		{
#ifdef CANDY_STATISITICAL_DATA	
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_41, "");
#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
			AnalyseJson::logOnMsg.baseInfo.Chitchat = 0;
#endif
			if ( 1 == AnalyseJson::logOnMsg.baseInfo.Chitchat )
			{
			}
			else
			{
				m_mainmapuilayer->showMapWidget(MAP_WIDGET_SUCCEEDUI_DLG, PROMPT_TYPE_CHITNOOPEN);
			}
		}
		break;
	case TAG_NOTICE_TOOLSMENU_ITEM:
		{
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_43, "");
#endif
			showMapWidget( MAP_WIDGET_NOTICE_DLG );
			m_isKey = true;
		}
		break;

	case TAG_FEEDBACK_TOOLSMENU_TIEM:
		{
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_42, "");
#endif
			m_mainmapuilayer->showMapWidget(MAP_WIDGET_FEEDBACK_DLG);
		}
		break;

	case TAG_SETTIONG_TOOLSMENU_TIEM:
		{
			showMapWidget( MAP_WIDGET_SYSTEMTOOLS_DLG );
			m_isKey = true;
		}
		break;
	
	case TAG_FRIENDLIST_TOOLSMENU_TIEM:
		{
			if ( AnalyseJson::unLockConfig.friendFun > CommonData::getMaxLevel() )
			{
				pMenuBtn->setTouchEnabled( true );
				showUnlockPrompt(PROMPT_TYPE_UNLOCK_FRIEND, pMenuBtn->getParent()->convertToWorldSpace(pMenuBtn->getPosition()) );				
			
			}
			else
				m_mainmapuilayer->showMapWidget(MAP_WIDGET_FRIEND_LIST);
		}
		break;

	case TAG_MESSAGELIST_TOLLSMENU_TIEM:
		{
			/*if ( m_messagetips )
			{
				if ( m_messagetips->isVisible())
				{
					pMenuBtn->stopAllActions();
					pMenuBtn->isEffects(true);
					m_messagetips->setVisible( false );
				}
			}*/

			m_mainmapuilayer->showMapWidget(MAP_WIDGET_MESSAGE_LIST);
		}
		break;

	case TAG_NOFRIENDLIST_TOOLSMENU_TIEM:
		{
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_SEACHFRIEND );
		}
		break;

	case TAG_GETHERSTAR_TOOLSMENU_TIME:
		{
			m_mainmapuilayer->m_GetherStarBut->stopAllActions();
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_GETHERSTAR );
		}
		break;

	case TAG_KNAPSACK_TOOLSMENU_TIEM:
		{
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_KNAPSACK );
		}
		break;

	case TAG_MAINTASK_TOOLSEMNU_TIEM:
		{
			pMenuBtn->stopAllActions();
			pMenuBtn->isEffects(true);
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_MAINTASK );
		}
		break;

	case TAG_GAMESHOP_TOOLSEMNU_TIEM:
		{
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_SHOP_DLG );
		}
		break;

	case TAG_VIP_TOOLSEMNU_TIEM:
		{
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_VIP_DLG );
		}
		break;
	case TAG_WORLDRANK_TOOLSMENU_ITEM:
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_RANK_DLG );
		}
		break;
	case TAG_TASK_TOOLSMENU_ITEM:
		{
			if ( AnalyseJson::unLockConfig.starTask > CommonData::getMaxLevel() )
			{
				pMenuBtn->setTouchEnabled( true );
				showUnlockPrompt(PROMPT_TYPE_UNLOCK_STARTASK, pMenuBtn->getParent()->convertToWorldSpace(pMenuBtn->getPosition()) );
			}
			else
			{
				m_mainmapuilayer->showMapWidget( MAP_WIDGET_TASK );
			}
		}
		break;

	case TAG_MYINFORMAT_TOOLSMENU_ITEM:
		{
			m_mainmapuilayer->showMapWidget( MAP_WIDGET_MYINFORMAT );
		}
		break;

	case TAG_DAILYTASK_GETCANDY_TOOLSMENU_TIEM:
	case TAG_DAILYTASK_TARGETLEVEL_TOOLSMENU_TIEM:
		{
			int nTaskid = (int)pMenuBtn->data;

			std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
			for(; item != AnalyseJson::taskTable.dailyTask.end(); item++)
			{
				if (nTaskid == item->taskid)
				{
					if ( item->isVipTask&& 0 == AnalyseJson::logOnMsg.baseInfo.isVip )
					{
						QuitMapWidgetCallback();
						showMapWidget( MAP_WIDGET_VIP_DLG );
					}
					// 未完成  显示说明
					else if ( item->targer > item->complete )
					{
						showMapWidget(MAP_WIDGET_DAILYTASK_EXTRA, item->type );
					}
					// 已完成 领取任务 播放效果
					else
					{
						UIButton* GamegemBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("gembtn"));
						CCPoint tem1 = pMenuBtn->getParent()->convertToWorldSpace(pMenuBtn->getPosition());
						CCPoint tem0 = GamegemBut->getParent()->convertToWorldSpace( GamegemBut->getPosition() );
						CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/buyItem/map_gamico.png")->getCString() );

						if(pPropIco != NULL)
						{
							pPropIco->setScale(1.6f);
							pPropIco->setPosition( tem1 );
							getWidgetUILayer()->addChild(pPropIco,232);

							pPropIco->runAction(CCSequence::create(	
								CCSpawn::create(
								getEffectBezierAction(tem1, tem0),
								CCScaleTo::create(1.2f, 0.2f),
								NULL),
								CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::DailyTaskActionCallBack), (void*)item->taskid),
								NULL
								));
						}

#ifdef CANDY_STATISITICAL_DATA
						//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4014, CCString::createWithFormat("%d", CandyManager::currentLevel)->getCString() );
#endif
					}
					break;
				}
			}

		}
		break;
	default:
		break;
	}
}

UILayer* MainMapUiLayer::getWidgetUILayer(void)
{
	if(!m_mainmapuilayer->widgetUiLayer)
	{
		m_mainmapuilayer->widgetUiLayer = UILayer::create();
		this->addChild(m_mainmapuilayer->widgetUiLayer);
	}
	return m_mainmapuilayer->widgetUiLayer;
}

void MainMapUiLayer::removeWidgetUILayer(void)
{
	if(widgetUiLayer)
	{
		widgetUiLayer->removeFromParent();
		widgetUiLayer = NULL;
	}
}

// 
void MainMapUiLayer::showLevelInfo(int level)
{
	m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );

	if ( m_mainmapuilayer->m_pPanel )
	{
		m_mainmapuilayer->m_pPanel->setVisible( true );
		m_mainmapuilayer->m_pPanel->setTouchEnabled( true );
	}
	m_mainmapuilayer->showMapWidget(MAP_WIDGET_LEVEL_INFO, level );

}

void MainMapUiLayer::showPropInfoBuy(const int propid)
{
	m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );

	if ( CommonData::checkGoodsPriceEnough( propid ) )
	{
		CommonData::directBuyGoods( propid );
	}
	else
	{
		QuitMapWidgetCallback();
		m_mainmapuilayer->showMapWidget(MAP_WIDGET_PROPBUY_DLG, propid );
	}
}

void MainMapUiLayer::showMapWidget(MapWidgetType type, int para,int para1)
{
	Layout* widget = NULL;	
	WidgetNode nWidgetNode;
	m_CurWidgetType = type;
	setLoading( false );

	switch(type)
	{
	case MAP_WIDGET_SIGNIN:
		{
			//widget = getSignInUILayout();	//签到，精简版本去掉
		}
		break;

	case MAP_WIDGET_BUYGEM_LIST:
		{
			//widget = getBuyGemLayer();		//宝石购买，精简版本去掉
		}
		break;

	case MAP_WIDGET_CHANGEINFO_DLG:
		{
			widget = getChangeInfoLayout();
		}
		break;

	case MAP_WIDGET_BUYLIFE_LIST:
		{
			widget = getBuyLifeListLayout();
		}
		break;

	case MAP_WIDGET_FRIEND_INFO:
		{
			//widget = getFriendInfoLayout();	//好友信息，精简版本去掉
		}
		break;
	case MAP_WIDGET_REWARDVIPUI:
		{
			widget = getRewardUILayout();
		}
		break;

	case MAP_WIDGET_FRIEND_LIST:
		{
			//widget = getFriendListLayout();	//好友列表，精简版本去掉
		}
		break;

	case  MAP_WIDGET_NOFRIEND_LIST:
		{
			//widget = getInviteFriendListLayout();	//邀请好友，精简版本去掉
		}
		break;

	case MAP_WIDGET_MESSAGE_LIST:
		{
			//widget = getMessageListLayout();		//消息，精简版本去掉
		}
		break;

	case MAP_WIDGET_LEVEL_INFO:
		{
			/*CommonData::m_resetPropState = true;
			widget = getLevelInfoLayout(para);*/
		}
		break;

	case MAP_WIDGET_SUCCEEDUI_DLG:
		{
			widget = getSucceedDlgUilayout( para ,para1);
		}
		break;

	case  MAP_WIDGET_PROPCLIAORHEANDLE_DLG:
		{
			widget = getPropDlgLayout( para, para1 );
		}
		break;

	case  MAP_WIDGET_HELP_DLG:
		{
			widget = getHelpUiLayout();
		}
		break;

	case  MAP_WIDGET_SYSTEMTOOLS_DLG:
		{
			widget = getSystemToolsLayout();
		}
		break;

	case  MAP_WIDGET_FEEDBACK_DLG:
		{
			widget = getFeedbackLayout();
		}
		break;

	case  MAP_WIDGET_LACKLIFE_DLG:
		{
			widget = getLackLifeLayout();
		}
		break;

	case  MAP_WIDGET_CLAIMLIFE_DLG:
		{
			widget = getCliamLifeLayout();
		}
		break;

	case MAP_WIDGET_PROPBUY_DLG:
		{
			widget = getPropBuyLayout( para );
		}
		break;

	case MAP_WIDGET_NOTICE_DLG:
		{
			widget = getNoticeLayout();
		}
		break;

	case MAP_WIDGET_SEACHFRIEND:
		{
			//widget = getSeachfriendLayer();	//搜索好友，精简版本去掉
		}
		break;
	case MAP_WIDGET_SURFRIEND_DLG:
		{
			widget = getSurpassFriendLayout();
		}
		break;
	case MAP_WIDGET_GETHERSTAR:
		{
			widget = getGetherStarTaskLayout();
		}
		break;

	case MAP_WIDGET_KNAPSACK:
		{
			//widget = getKnapsackLayout();		//背包，精简版本去掉
		}
		break;
	case MAP_WIDGET_SHOP_DLG:
		{
			widget = getGameShopLayout();
		}
		break;
	case MAP_WIDGET_VIP_DLG:
		{
			//widget = getGameVipLayout();
		}
		break;
	case MAP_WIDGET_RANK_DLG:
		{
			//widget = getGameRankLayout();		//排名，精简版本去掉
		}
		break;

	case MAP_WIDGET_GIFT_DLG:
		{
			widget = getGameGiftLayout(para);
		}
		break;

	case MAP_WIDGET_UNLOCKLEVEL_DLG:
		{
			widget = getGameUnlockLevelLayout(para);
		}
		break;

	case MAP_WIDGET_MAINTASK:
		{
			widget = getMainTaskLayout();
		}
		break;

	case MAP_WIDGET_DAILYTASK_EXTRA:
		{
			widget = getDailyTaskExtraLayout(para);
		}
		break;
	case MAP_WIDGET_REMINDNETWORK:
		{
			widget = CommonWidgt::getSuccessUI( WIDGET_TYPE_MAP, PROMPT_TYPE_REMINDNETWORK );
		}
		break;

	case MAP_WIDGET_MYINFORMAT:
		{
			widget = getMyInformatLayout();
		}
		break;
		
	case MAP_WIDGET_TASK:
		{
			widget = getTaskLayout();
		}
		break;
	case MAP_WIDGET_ROULETTE_DLG:
		{
			widget = getGameRouletteLayout();
		}
		break;
	case MAP_WIDGET_PAY_DLG:
		{
			widget = CommonWidgt::getGamePayWidgetUI(WIDGET_TYPE_MAP,para);
			//CommonData::gamePay( para );
			//return;
		}
		break;
	default:
		break;
	}

	// Save Current widget data to widget list!
	nWidgetNode.widget = widget;
	nWidgetNode.type = type;
	if (widget)
	{
		m_mainmapuilayer->widgetList.push_front( nWidgetNode );
	}
	
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

	CCSize ctntSize;
	if(widget)
	{	
		widget->setVisible( true );
		//widget->setTouchEnabled( true );
		if ( MAP_WIDGET_LEVEL_INFO == type )
		{
			/*CCPoint desPos;
			if(CommonData::getMaxLevel() < 20)
			{
				desPos = ccp(currentScreenWidth/2, currentScreenHeight/2 );
			}
			else
			{
				desPos = ccp(currentScreenWidth/2, currentScreenHeight/2 + 100);
			}
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "Content" ));
			pImgDlg->setPosition( ccp(size.width/2,size.height+size.height) );
			pImgDlg->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_ENTRY, desPos),
				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::UpdateFriendRank)),
				NULL)
				);
			widget->setPosition(ccp(0,0));*/
		}
		else if (MAP_WIDGET_REMINDNETWORK == type)
		{
			widget->setPosition(ccp(0,0));
		}

		else if (MAP_WIDGET_SUCCEEDUI_DLG == type 
			|| MAP_WIDGET_PROPCLIAORHEANDLE_DLG == type )
		{
			widget->setPosition( ccp(0,0) );

			UIWidget* pImgDlg = dynamic_cast<UIWidget*>(widget->getChildByName( "m_img_dlg" ));
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
				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::WidgitrunAction)),
				NULL
				));
		}
		else if(MAP_WIDGET_SURFRIEND_DLG == type)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
			pImgDlg->setPosition( ccp(size.width/2,size.height+size.height) );

			pImgDlg->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_ENTRY, ccp(currentScreenWidth/2, currentScreenHeight/2 + 100)),
				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::WidgitrunAction)),
				NULL)
				);
			widget->setPosition(ccp(0,0));
		}
		else if(MAP_WIDGET_SHOP_DLG == type)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
 			pImgDlg->setPosition( ccp(size.width*0.5,size.height*1.5) );
			pImgDlg->setVisible( true );
 			CCActionInterval * fadeout = CCFadeIn::create(0.01f); 
 			pImgDlg->runAction(CCSequence::create(
 				fadeout,
 				getMoveAction(MAP_DLG_ENTRY, ccp(size.width*0.5,size.height*0.5)),
 				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::WidgitrunAction)),
 				NULL)
 				);

			widget->setPosition(ccp(0,0));

		}
		else if(MAP_WIDGET_VIP_DLG == type)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "content_1" ));
			pImgDlg->setPosition( ccp(size.width/2,size.height+size.height) );
			pImgDlg->setVisible( true );
			pImgDlg->setScale( 1.0f );

			pImgDlg->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_ENTRY, ccp(currentScreenWidth/2, fixedScreenHeight/2-70)),
				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::WidgitrunAction)),
				NULL)
				);
			widget->setPosition(ccp(0,0));
		}
		else if(MAP_WIDGET_PAY_DLG == type)
		{
			widget->setPosition(ccp(0,0));

		}
		else
		{
			UIWidget* pImgDlg = dynamic_cast<UIWidget*>(widget->getChildByName( "m_img_dlg" ));
			pImgDlg->setPosition( /*ccp(720+720/2, currentScreenHeight/2)*/LEVEL_QUIT_CCCP );
			pImgDlg->setScale( 1.0f );
			pImgDlg->setVisible( true );
			CCActionInterval * fadeout = CCFadeIn::create(0.01f); 

			pImgDlg->runAction(CCSequence::create(
				fadeout,
				getMoveAction(MAP_DLG_ENTRY, ccp(currentScreenWidth/2, currentScreenHeight/2 - 30)),
				CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::WidgitrunAction)),
				NULL)
				);

			widget->setPosition(ccp(0,0));
		}
		// set action
		if (widget->isVisible())
		{
			getWidgetUILayer()->addWidget((widget));
		}
		if ( MainMap::m_mainmap )
			MainMap::m_mainmap->HideMapUi();
	}
	
}

void MainMapUiLayer::QuitMapWidget(MapWidgetType nexttype)
{
	setLoading( false );
	if ( m_mainmapuilayer->widgetList.empty() )
		return;

	std::list<WidgetNode>::iterator tem =  m_mainmapuilayer->widgetList.begin();
	//tem --;

	switch ( tem->type )
	{
	case MAP_WIDGET_LEVEL_INFO:
		{
			tem->widget->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_QUIT, /*ccp(720+420.0f,0.0f)*/ccp(0.0f,CCDirector::sharedDirector()->getWinSize().height + CCDirector::sharedDirector()->getWinSize().height/2) ),
				CCCallFuncND::create(tem->widget, callfuncND_selector(MainMapUiLayer::QuitMapWidgetCallback), (void*)nexttype),
				NULL)
				);
		}
		break;
	case MAP_WIDGET_VIP_DLG:
		{
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(tem->widget->getChildByName( "content_1" ));
			pImgDlg->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_QUIT,ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height * 2) ),
				CCCallFuncND::create(tem->widget, callfuncND_selector(MainMapUiLayer::QuitMapWidgetCallback), (void*)nexttype),
				NULL)
				);

		}
		break;

	case MAP_WIDGET_SHOP_DLG:
		{
 			UIImageView* pPanel = dynamic_cast<UIImageView*>(tem->widget->getChildByName( "m_img_dlg" ));
 			pPanel->runAction(CCSequence::create(
 				getMoveAction(MAP_DLG_QUIT,ccp(CCDirector::sharedDirector()->getWinSize().width*0.5,CCDirector::sharedDirector()->getWinSize().height * 1.5) ),
 				CCCallFuncND::create(tem->widget, callfuncND_selector(MainMapUiLayer::QuitMapWidgetCallback), (void*)nexttype),
 				NULL)
 				);
		}
		break;
	case MAP_WIDGET_PAY_DLG:
		{
			//tem->widget->setPosition( LEVEL_QUIT_CCCP );
			QuitMapWidgetCallback();
		}
		break;

	case MAP_WIDGET_RANK_DLG:
	case MAP_WIDGET_UNLOCKLEVEL_DLG:
	case MAP_WIDGET_GIFT_DLG:
	case MAP_WIDGET_BUYGEM_LIST:
	case MAP_WIDGET_FRIEND_INFO:
	case MAP_WIDGET_FRIEND_LIST:
	case MAP_WIDGET_NOFRIEND_LIST:
	case MAP_WIDGET_MESSAGE_LIST:
	case MAP_WIDGET_HELP_DLG:
	case MAP_WIDGET_FEEDBACK_DLG:
	case MAP_WIDGET_CLAIMLIFE_DLG:
	case MAP_WIDGET_LACKLIFE_DLG:
	case MAP_WIDGET_NOTICE_DLG:
	case MAP_WIDGET_BUYLIFE_LIST:
	case MAP_WIDGET_SEACHFRIEND:
	case MAP_WIDGET_SYSTEMTOOLS_DLG:
	case MAP_WIDGET_CHANGEINFO_DLG:
	case MAP_WIDGET_KNAPSACK:
	case MAP_WIDGET_MAINTASK:
	case MAP_WIDGET_DAILYTASK_EXTRA:
	case MAP_WIDGET_GETHERSTAR:
	case MAP_WIDGET_TASK:
	case MAP_WIDGET_MYINFORMAT:
	case MAP_WIDGET_REWARDVIPUI:
	case MAP_WIDGET_SIGNIN:
	case MAP_WIDGET_SURFRIEND_DLG:
	case MAP_WIDGET_ROULETTE_DLG:
		{
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(tem->widget->getChildByName( "m_img_dlg" ));

			pImgDlg->runAction(CCSequence::create(
				getMoveAction(MAP_DLG_QUIT, LEVEL_QUIT_CCCP/*LEVEL_QUIT_CCCP*/),
				CCCallFuncND::create(tem->widget, callfuncND_selector(MainMapUiLayer::QuitMapWidgetCallback), (void*)nexttype),
				NULL)
				);
		}
		break;

	case MAP_WIDGET_PROPBUY_DLG:
		{
			QuitMapWidgetCallback();

			CCLog("MainMapUiLayer::QuitMapWidget m_buyState[%d]", CommonData::m_buyState);
			if ( CommonData::m_buyState )
			{
				CommonData::m_buyState = false;
				MainMapUiLayer::m_mainmapuilayer->showBuyPrompt(1);
				//showMapWidget(MAP_WIDGET_SUCCEEDUI_DLG ,PROMPT_TYPE_BUYSUC);
			}
			else
			{
				//showMapWidget( MAP_WIDGET_LEVEL_INFO, CandyManager::currentLevel );
			}
		}

		break;
	case MAP_WIDGET_REMINDNETWORK:
	case MAP_WIDGET_SUCCEEDUI_DLG:
	case MAP_WIDGET_PROPCLIAORHEANDLE_DLG:
		{

			if ( MAP_WIDGET_SUCCEEDUI_DLG == tem->type && PROMPT_TYPE_BUYSUC == CommonWidgt::SuccessWidgetLayout->sucType )
			{
				QuitMapWidgetCallback();
				//showMapWidget( MAP_WIDGET_LEVEL_INFO, CandyManager::currentLevel );
			}
			else
			{
				UIImageView* pImgDlg = dynamic_cast<UIImageView*>(tem->widget->getChildByName( "m_img_dlg" ));

				CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
				CCActionInterval * fadeout = CCFadeOut::create(0.2f);
				CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
				CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);

				pImgDlg->runAction(CCSequence::create(
					pScale,
					spawn,
					CCCallFuncND::create(tem->widget, callfuncND_selector(MainMapUiLayer::QuitMapWidgetCallback), (void*)nexttype),
					NULL)
					);
			}
		}
		break;
	}
}

void MainMapUiLayer::QuitMapWidgetCallback(CCNode* node /*= NULL*/, void* data /*= NULL*/)
{
	int type = (int)data;

	if ( m_mainmapuilayer->widgetList.empty() )
	{	
		return;
	}

	std::list<WidgetNode>::iterator tem = m_mainmapuilayer->widgetList.begin();
	//tem--;
	if((*tem).type == MAP_WIDGET_GIFT_DLG || (*tem).type == MAP_WIDGET_PAY_DLG)
	{
		if (!CommonData::m_isPlayNewUserAction && CommonData::getMaxLevel() < 1)
		{
			//发送消息，第一次进入游戏
			CCNotificationCenter::sharedNotificationCenter()->postNotification(IntoGameLvl1,NULL);
		}
	}
	tem->widget->setPosition( ccp(0, 1280.0f+50) );
	m_mainmapuilayer->m_pPanel->setVisible( false );
	m_mainmapuilayer->m_pPanel->setTouchEnabled( false );
	m_mainmapuilayer->widgetList.erase( tem );


	if ( MAP_WIDGET_NULL != type)
		showMapWidget( (MapWidgetType)type );
	else
		MainMap::m_mainmap->DisplayMapUi();

	//发送消息，显示新用户指引
	CCNotificationCenter::sharedNotificationCenter()->postNotification(ShowOrHideLayer,NULL);
}  


void MainMapUiLayer::QuitMapWidgetDirect(void)
{
	if ( m_mainmapuilayer->widgetList.empty() )
		return;

	std::list<WidgetNode>::iterator tem = m_mainmapuilayer->widgetList.end();
	tem--;

	if ( tem->widget->isVisible() )
	{
		tem->widget->setVisible( false );
		tem->widget->setTouchEnabled( false );
		tem->widget->setPosition( LEVEL_QUIT_CCCP );

		m_mainmapuilayer->m_pPanel->setVisible( false );
		m_mainmapuilayer->m_pPanel->setTouchEnabled( false );
		m_mainmapuilayer->widgetList.erase( tem );

	}

	MainMap::m_mainmap->DisplayMapUi();

}  

Layout* MainMapUiLayer::GetReminderlayout(int type)
{
	if ( !reminderLayout )
	{
		reminderLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_REMINDER));
		reminderLayout->retain();
		reminderLayout->setZOrder( 4 );
		reminderLayout->setTouchEnabled(true);
	}

	UIImageView* pTip_Title = dynamic_cast<UIImageView*>(reminderLayout->getChildByName("m_img_tip_title"));
	UIImageView* pTip_Text = dynamic_cast<UIImageView*>(reminderLayout->getChildByName("m_img_tip_text"));
	UIImageView* pTip_ButText = dynamic_cast<UIImageView*>(reminderLayout->getChildByName("m_img_tip_buttitle"));
	UIButton *pExitBut = dynamic_cast<UIButton*>(reminderLayout->getChildByName("m_btu_exit"));
	UIButton *pTip_But = dynamic_cast<UIButton*>(reminderLayout->getChildByName("m_but_tip"));
	pTip_But->isEffects( true );
	pTip_But->setTag( type );

	if ( TIPMSG_TYPE_PROPINSUF == type )
	{
		pTip_Title->setTexture( "Image/MainMapUi/m_img_proplack.png" );
		pTip_Text->setTexture( "Image/MainMapUi/m_str_propgiveerr.png" );
		pTip_ButText->setTexture( "Image/MainMapUi/m_butstr_buy.png" );
		pTip_But->addReleaseEvent(  this, coco_releaseselector(MainMapUiLayer::ReminderLifeCB) );
		pExitBut->setVisible( true );
		pExitBut->setTouchEnabled(true);
		pExitBut->addReleaseEvent(  this, coco_releaseselector(MainMapUiLayer::ReminderExitCB) );
	}
	else if ( TIPMSG_TYPE_LIFEINSUF == type)
	{
		pTip_Title->setTexture( "Image/MainMapUi/m_str_Tips2_title.png" );
		pTip_Text->setTexture( "Image/MainMapUi/m_str_Tips2_text.png" );
		pTip_ButText->setTexture( "Image/MainMapUi/m_but_Tips2_.png" );
		pTip_But->addReleaseEvent( this, coco_releaseselector(MainMapUiLayer::ReminderLifeCB));
	}
	else if ( TIPMSG_TYPE_LIFELACK == type)
	{
		pTip_Title->setTexture( "Image/MainMapUi/NoLife.png" );
		pTip_Text->setTexture( "Image/MainMapUi/NoLifeTips.png" );
		pTip_ButText->setTexture( "Image/MainMapUi/ReturnMap.png" );
		pTip_But->addReleaseEvent( this, coco_releaseselector(MainMapUiLayer::ReminderLifeCB));
	}
	else if (TIPMSG_TYPE_WEMECHITCHAT == type )
	{
		pTip_Title->setTexture( "Image/MainMapUi/m_img_chiterr.png" );
		pTip_Text->setTexture( "Image/MainMapUi/m_img_chitchatstr.png" );
		pTip_ButText->setTexture( "Image/MainMapUi/m_butstr_sur.png" );
		pTip_But->addReleaseEvent( this, coco_releaseselector(MainMapUiLayer::ReminderLifeCB));
	}

	return reminderLayout;
}

Layout* MainMapUiLayer::getSucceedDlgUilayout( int sucType, int data)
{
	if ( PROMPT_TYPE_BUYSUC == sucType )
		CommonData::m_buyState = false;

	Layout* pLayout = CommonWidgt::getSuccessUI( WIDGET_TYPE_MAP, sucType, data );
	pLayout->setZOrder( 5 );
	return pLayout;
}

Layout* MainMapUiLayer::getPropDlgLayout(int propid, int dlgtype)
{
	if ( !m_mainmapuilayer->cliamsucLayout )
	{
		m_mainmapuilayer->cliamsucLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_CLIAIM_SUCCEED));
		m_mainmapuilayer->cliamsucLayout->retain();
	}

	m_mainmapuilayer->cliamsucLayout->setZOrder( 6 );
	m_mainmapuilayer->cliamsucLayout->setTouchEnable(true);

	float nDelayTime1 = 0.18f ;//+ 0.08f;
	float nDelayTime2 = 0.081f;

	UIButton *ButNext = dynamic_cast<UIButton*>(m_mainmapuilayer->cliamsucLayout->getChildByName("m_but_next"));
	ButNext->setTouchEnable(true);
	ButNext->setTag( dlgtype );
	ButNext->isEffects( true,nDelayTime1 );
	ButNext->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::CliamLifeSurCB));

	UIButton *ButNotic = dynamic_cast<UIButton*>(m_mainmapuilayer->cliamsucLayout->getChildByName("m_but_notic"));
	ButNotic->setTouchEnable(true);
	ButNotic->setTag( dlgtype );
	ButNotic->isEffects( true,nDelayTime1+nDelayTime2*2 );
	ButNotic->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::CliamLifeSurCB));

	UIImageView *pPropIco = dynamic_cast<UIImageView*>(m_mainmapuilayer->cliamsucLayout->getChildByName("m_img_proppic"));
	UIImageView *pTitle = dynamic_cast<UIImageView*>(m_mainmapuilayer->cliamsucLayout->getChildByName("m_img_tip_title"));

	if ( DLG_TYPE_CLAIMEPROP == dlgtype)
	{
		char *pPropPic = (char *)CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", propid)->getCString();
		pPropIco->setTexture( pPropPic );
		pTitle->setTexture( "Image/MainMapUi/m_str_propcliamsuc.png" );
	}
	else if ( DLG_TYPE_HANDSELPROP == dlgtype)
	{
		char *pPropPic = (char *)CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", propid)->getCString();
		pPropIco->setTexture( pPropPic );
		pTitle->setTexture( "Image/MainMapUi/m_str_propgivesuc.png" );
	}
	else if ( DLG_TYPE_CLAIMLIFE == dlgtype)
	{
		pPropIco->setTexture( "Image/MainMapUi/m_img_love.png" );
		pTitle->setTexture( "Image/MainMapUi/m_str_lovecliamsuc.png" );
	}
	else if ( DLG_TYPE_HANDSELLIFE == dlgtype)
	{
		pPropIco->setTexture( "Image/MainMapUi/m_img_love.png" );
		pTitle->setTexture( "Image/MainMapUi/m_str_lifegivesuc.png" );
	}

	return m_mainmapuilayer->cliamsucLayout;
}

Layout* MainMapUiLayer::getSystemToolsLayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getSystemToolsUI( WIDGET_TYPE_MAP );

	return pLayout;
}
Layout* MainMapUiLayer::getSurpassFriendLayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getSurpassFriendUI(  );

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}
Layout* MainMapUiLayer::getGameShopLayout(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameShopUI( WIDGET_TYPE_MAP );

	return pLayout;
}

Layout* MainMapUiLayer::getGameVipLayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameVipUI( WIDGET_TYPE_MAP );

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}

Layout* MainMapUiLayer::getGameRankLayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameRankWidgetUI( WIDGET_TYPE_MAP );

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}

Layout* MainMapUiLayer::getGameUnlockLevelLayout(int level)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameUnlockLevelUI( WIDGET_TYPE_MAP ,level);

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}

Layout* MainMapUiLayer::getGameGiftLayout(int type )
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameGiftUI( WIDGET_TYPE_MAP ,type);

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}
Layout* MainMapUiLayer::getLevelInfoLayout(int level)
{
	/*m_mainmapuilayer->levelLayout = CandyStageIntro::getLayout(STAGE_INTRO_MAIN_MAP, level);
	m_mainmapuilayer->levelLayout->setTouchEnabled( true );
	m_mainmapuilayer->levelLayout->setZOrder(4);

#ifdef CANDY_STATISITICAL_DATA
	if(CommonData::getMaxLevel() < CandyManager::currentLevel && CandyManager::currentLevel<=10)
	{
		char* pLevel = (char*)CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString();
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_14, pLevel);
	}
#endif
	if ( !m_mainmapuilayer->levelLayout )
		return NULL;
	else
		return m_mainmapuilayer->levelLayout;*/
	return NULL;
}

Layout* MainMapUiLayer::getHelpUiLayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getHelpUI( WIDGET_TYPE_MAP );

	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}

Layout* MainMapUiLayer::getSignInUILayout(void)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getSignInUI();
	
	return pLayout;
}



Layout* MainMapUiLayer::getRewardUILayout(void)
{
	if(!m_mainmapuilayer->rewardlayout)
	{                                                      
		m_mainmapuilayer->rewardlayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_REWARDVIP));
		m_mainmapuilayer->rewardlayout->autorelease();
		m_mainmapuilayer->rewardlayout->retain();

	}
	m_mainmapuilayer->rewardlayout->setZOrder( 2 );
	m_mainmapuilayer->rewardlayout->setTouchEnable(true);


	float nDelayTime1 = 0.48f ;
	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->rewardlayout->getChildByName("m_btu_exit"));
	closeButton->setTag( 1 );
	closeButton->setTouchEnable( true );
	closeButton->isEffects( true,nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackForRewardUI));
	
	UIButton *rewardBtn = dynamic_cast<UIButton*>(m_mainmapuilayer->rewardlayout->getChildByName("m_btn_reward"));
	rewardBtn->setTag( 2 );
	rewardBtn->setTouchEnable( true );
	rewardBtn->isEffects( true,nDelayTime1 );
	rewardBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackForRewardUI));


	return m_mainmapuilayer->rewardlayout;
}

Layout* MainMapUiLayer::getBuyLifeListLayout(void)
{
	//if(!m_mainmapuilayer->LifeListLayout)
	//{                                                      
	//	m_mainmapuilayer->LifeListLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_BUYLIFE));
	//	m_mainmapuilayer->LifeListLayout->autorelease();
	//	m_mainmapuilayer->LifeListLayout->retain();

	//	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	//	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	//	cocos2d::extension::UIPanel *currPanel = dynamic_cast<UIPanel*>(m_mainmapuilayer->LifeListLayout->getChildByName( "Panel" ));
	//	currPanel->setSize(CCSizeMake(currentScreenWidth, currentScreenHeight));
	//	currPanel->setTouchEnable( true );

	//}
	//m_mainmapuilayer->LifeListLayout->setZOrder( 2 );
	//m_mainmapuilayer->LifeListLayout->setTouchEnable(true);

	//float nDelayTime1 = 0.48f ;//+ 0.08f;
	//float nDelayTime2 = 0.041f;
	//UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->LifeListLayout->getChildByName("m_btu_exit"));
	//closeButton->setTouchEnable( true );
	//closeButton->isEffects( true,nDelayTime1 );
	//closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::BtnCallBackCloseBuyLife));

	//addLifetoList();

	return NULL;
}

Layout* MainMapUiLayer::getFriendInfoLayout(void)
{
	if(!friendInfoLayout)
	{
		friendInfoLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(FRIEND_INFO_LAYOUT_FILE));
		friendInfoLayout->autorelease();
		friendInfoLayout->retain();

	}
	friendInfoLayout->setZOrder( 2 );
	friendInfoLayout->setTouchEnable(true);

	float nDelayTime1 = 0.28f;
	float nDelayTime2 = 0.021f;
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	cocos2d::extension::UIPanel *currPanel = dynamic_cast<UIPanel*>(friendInfoLayout->getChildByName( "Panel" ));

	currPanel->setSize(CCSizeMake(currentScreenWidth, currentScreenHeight));
	currPanel->setTouchEnable( true );

	UIButton *closeButton = dynamic_cast<UIButton*>(friendInfoLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnable(true);
	closeButton->isEffects( true ,nDelayTime1);
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::BtnCallBackCloseFriendInfo));

	// 道具按钮
	for (int i = 1; i<=6; i++)
	{
		for( int j = 1; j<=2; j++)
		{
			char *pPropBut= (char *)CCString::createWithFormat("m_btn_%d_%d", i, j)->getCString();
			UIButton *PropButton = dynamic_cast<UIButton*>(friendInfoLayout->getChildByName( pPropBut ));
			PropButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::friendPropButCB));
			PropButton->isEffects( true, nDelayTime1+(i-1)*3*nDelayTime2);
		}

		char *pPropbgstr= (char *)CCString::createWithFormat("propbg%d", i)->getCString();
		UIImageView *pPropbg = dynamic_cast<UIImageView*>(friendInfoLayout->getChildByName( pPropbgstr ));
		pPropbg->isEffects( true, nDelayTime1+(i-1)*3*nDelayTime2, false );
	}

	std::list<UserFriendInfoStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();

	for (int i = 0; i < (int)(AnalyseJson::friendInfoMsg.friendInfo.size()); i++)
	{
		if (p->id == m_CurSelFriendItem)
		{
			break;
		}
		p++;
	}

	UpdataPropNum();

	UILabel *pFriendName = dynamic_cast<UILabel*>(friendInfoLayout->getChildByName("m_lab_friendname"));
	pFriendName->setText( p->nickName.c_str() );

	UIImageView *pSexBg = dynamic_cast<UIImageView*>(friendInfoLayout->getChildByName("m_img_sexbg"));
	if ( 1 == p->gender )
		pSexBg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
	else
		pSexBg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

	return friendInfoLayout;
}

Layout* MainMapUiLayer::getInviteFriendListLayout(void)
{
	if ( !m_mainmapuilayer->noFriendListLayout )
	{
		m_mainmapuilayer->noFriendListLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_NOFRIEND_LIST));
		m_mainmapuilayer->noFriendListLayout->autorelease();
		m_mainmapuilayer->noFriendListLayout->retain();

		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
		cocos2d::extension::UIPanel *currPanel = dynamic_cast<UIPanel*>(m_mainmapuilayer->noFriendListLayout->getChildByName( "Panel" ));
		currPanel->setSize(CCSizeMake(currentScreenWidth, currentScreenHeight));
		currPanel->setTouchEnable( true );

	}
	m_mainmapuilayer->noFriendListLayout->setZOrder( 3 );
	m_mainmapuilayer->noFriendListLayout->setTouchEnabled(true);

	float nDelayTime1 = 0.18f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->noFriendListLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnable(true);
	closeButton->setTag(0);
	closeButton->isEffects( true ,nDelayTime1);
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::ButCallBackInviteFriendList));

	UIButton *pnextpagbtn = dynamic_cast<UIButton*>(m_mainmapuilayer->noFriendListLayout->getChildByName("m_btn_nextpag"));
	pnextpagbtn->setTouchEnable(true);
	pnextpagbtn->setTag(1);
	pnextpagbtn->isEffects( true, nDelayTime1 + nDelayTime2 );
	pnextpagbtn->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::ButCallBackInviteFriendList));

	addNofriendtoList();

	return m_mainmapuilayer->noFriendListLayout;
}
Layout* MainMapUiLayer::getFriendListLayout(void)
{
	if(!m_mainmapuilayer->friendListLayout)
	{
		m_mainmapuilayer->friendListLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_FRIEND_LIST));
		m_mainmapuilayer->friendListLayout->autorelease();
		m_mainmapuilayer->friendListLayout->retain();

		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
		cocos2d::extension::UIPanel *currPanel = dynamic_cast<UIPanel*>(m_mainmapuilayer->friendListLayout->getChildByName( "Panel" ));
		currPanel->setSize(CCSizeMake(currentScreenWidth, currentScreenHeight));
		currPanel->setTouchEnable( true );
	}

	m_mainmapuilayer->friendListLayout->setZOrder( 2 );
	m_mainmapuilayer->friendListLayout->setTouchEnabled(true);

	int nFriendNum = AnalyseJson::friendInfoMsg.friendInfo.size();
	nFriendNum = ( nFriendNum >= AnalyseJson::friendInfoMsg.friendMaxNum )? AnalyseJson::friendInfoMsg.friendMaxNum : nFriendNum;

	UIImageView* pFriendbg = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "ImageView_5850" ));
	pFriendbg->setVisible( false );

	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->friendListLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnable(true);
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::BtnCallBackCloseFriendList));
	closeButton->isEffects( true ,nDelayTime1 );


	//推荐好友
	UIButton* pInviteFriendBut = dynamic_cast<UIButton*>(m_mainmapuilayer->friendListLayout->getChildByName("m_btn_yqfriend"));
	pInviteFriendBut->setTouchEnable(true);
	pInviteFriendBut->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::ButCallBackInviteFriend));
	pInviteFriendBut->isEffects( true ,nDelayTime1+nDelayTime2);

	// 查找好友
	UIButton* pSeachFriendBut = dynamic_cast<UIButton*>(m_mainmapuilayer->friendListLayout->getChildByName("btn_seachfriend"));
	pSeachFriendBut->setTouchEnable(true);
	pSeachFriendBut->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::ButCallBackSeachFriend));
	pSeachFriendBut->isEffects( true ,nDelayTime1+nDelayTime2);
	//pSeachFriendBut->setVisible( false );

	UIImageView* pnothing = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "img_nothing" ));
	UIImageView* pnofriendstr = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "str_nofriendtips" ));
	pnothing->setVisible( false );
	pnofriendstr->setVisible( false );

	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->friendListLayout->getChildByName( "m_sv_friendlist" ));
	AnalyseJson::friendInfoMsg.friendInfo.clear();
	pFriendlistView->removeAllChildrenAndCleanUp( true );

	return m_mainmapuilayer->friendListLayout;
}

Layout* MainMapUiLayer::getMessageListLayout(void)
{
	if(!m_mainmapuilayer->messageListLayout)
	{
		m_mainmapuilayer->messageListLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_MESSAGE_LIST));
		m_mainmapuilayer->messageListLayout->autorelease();
		m_mainmapuilayer->messageListLayout->retain();

		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
		cocos2d::extension::UIPanel *currPanel = dynamic_cast<UIPanel*>(m_mainmapuilayer->messageListLayout->getChildByName( "Panel" ));
		currPanel->setSize(CCSizeMake(currentScreenWidth, currentScreenHeight));
		currPanel->setTouchEnable( true );

	}
	m_mainmapuilayer->messageListLayout->setZOrder( 2 );
	m_mainmapuilayer->messageListLayout->setTouchEnable(true);

	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->messageListLayout->getChildByName("m_btu_exit"));
	closeButton->setTag( 0 );
	closeButton->setTouchEnabled(true);
	closeButton->isEffects( true ,nDelayTime1 );
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::messageListCloseCallBack));

	UIButton *CleanButton = dynamic_cast<UIButton*>(m_mainmapuilayer->messageListLayout->getChildByName("ButDelMsg"));
	CleanButton->setTag( 1 );
	CleanButton->setTouchEnabled(true);
	CleanButton->isEffects( true ,nDelayTime1 );
	CleanButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::messageListCloseCallBack));

	UIScrollView* pMessagelistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	pMessagelistView->removeAllChildrenAndCleanUp( true );
	m_mainmapuilayer->m_messagelist.clear();

	UILabelAtlas* pLabelAcceptLife = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->messageListLayout->getChildByName( "LabelAcceptLife" ));
	pLabelAcceptLife->setStringValue( CCString::createWithFormat("%d", AnalyseJson::getHandselMsg.heardLimit)->getCString() );

	return m_mainmapuilayer->messageListLayout;
}

Layout* MainMapUiLayer::getFeedbackLayout(void)
{
	if ( !m_mainmapuilayer->feedbacklayout )
	{
		m_mainmapuilayer->feedbacklayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_FEEDBACK));
		m_mainmapuilayer->feedbacklayout->autorelease();
		m_mainmapuilayer->feedbacklayout->retain();

		Layout* layout = dynamic_cast<Layout*>(m_mainmapuilayer->feedbacklayout->getChildByName("inputfeedback"));
		UINodeContainer* nodeContainer = UINodeContainer::create();
		nodeContainer->setPosition(ccp(layout->getContentSize().width / 2, layout->getContentSize().height / 2));

		CCSize editBoxSize = layout->getContentSize();
		m_pEditBox = CCEditBox::create(CCSizeMake(500, 260), CCScale9Sprite::create("Image/MainMapUi/editboxBG.png"));
		//email_editBox->setFontName("SongTypeFont");
		m_pEditBox->setTag( EDITBOX_TYPE_FEEDBACK );
		m_pEditBox->setFontSize(20);
		m_pEditBox->setMaxLength( 200 );
		m_pEditBox->setTouchPriority( -1 );
		m_pEditBox->setFontColor(ccc3(216, 141, 70));
		m_pEditBox->setPlaceholderFontColor(ccc3(216, 141, 70/*0,0,0*/));
		m_pEditBox->setPlaceHolder( m_feedbackstr.c_str());
		m_pEditBox->setInputMode(kEditBoxInputModeSingleLine);
		m_pEditBox->setDelegate(this); 
		m_pEditBox->setReturnType(kKeyboardReturnTypeDone);  
		nodeContainer->addCCNode(m_pEditBox);

		UITextArea* pTextArea = dynamic_cast<UITextArea*>(m_mainmapuilayer->feedbacklayout->getChildByName("feedback_text"));
		pTextArea->setText( m_feedbackstr.c_str() );
		pTextArea->setFontSize( 30 );

		layout->addChild( nodeContainer );
	}
	m_mainmapuilayer->feedbacklayout->setZOrder( 5 );
	m_mainmapuilayer->feedbacklayout->setTouchEnable(true);

	m_feedbackstr.clear();
	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->feedbacklayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::CloseCallBack)); 

	UIButton *pFeedbackButton = dynamic_cast<UIButton*>(m_mainmapuilayer->feedbacklayout->getChildByName("m_btu_feedback"));
	pFeedbackButton->setTouchEnabled(true);
	pFeedbackButton->isEffects( true,nDelayTime1+nDelayTime2 );
	pFeedbackButton->addReleaseEvent( getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::feedbackbutCallBack));
	//pFeedbackButton->disable(true);

	return m_mainmapuilayer->feedbacklayout;
}

Layout* MainMapUiLayer::getLackLifeLayout(void)
{
	return NULL;
	if ( !m_mainmapuilayer->LackLifelayout )
	{
		m_mainmapuilayer->LackLifelayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_LACKLIFE));
		m_mainmapuilayer->LackLifelayout->autorelease();
		m_mainmapuilayer->LackLifelayout->retain();
	}
	m_mainmapuilayer->LackLifelayout->setZOrder( 2 );
	m_mainmapuilayer->LackLifelayout->setTouchEnabled(true);

	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->LackLifelayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::LackLifeUiButCallBack));

	UIButton *buylifeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->LackLifelayout->getChildByName("m_btn_buylife"));
	buylifeButton->setTouchEnabled(true);
	buylifeButton->setTag( 1 );
	buylifeButton->isEffects( true, nDelayTime1+nDelayTime2 );
	buylifeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::LackLifeUiButCallBack));

	//描述
	UILabel* descArea = dynamic_cast<UILabel*>(m_mainmapuilayer->LackLifelayout->getChildByName("TextArea_15263"));
	descArea->setText(CommonData::GetString("BuyLifeDesc").c_str());

	updataLackLifeUi();




	return m_mainmapuilayer->LackLifelayout;
}

void MainMapUiLayer::updataLackLifeUi(void)
{
	UIImageView *pFullLife = dynamic_cast<UIImageView*>(m_mainmapuilayer->LackLifelayout->getChildByName("fulllifepreson"));
	UIPanel *pLackLife = dynamic_cast<UIPanel*>(m_mainmapuilayer->LackLifelayout->getChildByName("lacklifepreson"));
	UIButton *buylifeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->LackLifelayout->getChildByName("m_btn_buylife"));
	pFullLife->setVisible( false );
	pLackLife->setVisible( true );
	buylifeButton->setTouchEnabled( true );

	/*if ( AnalyseJson::logOnMsg.lifeInfo.lifeNum >= MOBILE_GOURD_LIFENUM )
	{
		pFullLife->setVisible( true );
		pLackLife->setVisible( false );
		buylifeButton->setTouchEnabled( false );
	}
	else
	{
		pFullLife->setVisible( false );
		pLackLife->setVisible( true );
		buylifeButton->setTouchEnabled( true );
	}*/
}

Layout* MainMapUiLayer::getCliamLifeLayout(void)
{
	if ( !m_mainmapuilayer->CliamLifelayout )
	{
		m_mainmapuilayer->CliamLifelayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CLIAMLIFE_LAYOUT_FILE));
		m_mainmapuilayer->CliamLifelayout->autorelease();
		m_mainmapuilayer->CliamLifelayout->retain();
	}
	m_mainmapuilayer->CliamLifelayout->setZOrder( 2 );
	m_mainmapuilayer->CliamLifelayout->setTouchEnabled(true);

	m_ClaimLifeNum = 0;
	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->CliamLifelayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::CliamLifeUiButCallBack));

	UIButton *CliamButton = dynamic_cast<UIButton*>(m_mainmapuilayer->CliamLifelayout->getChildByName("m_btn_invite"));
	CliamButton->setTouchEnabled(true);
	CliamButton->setTag( 1 );
	CliamButton->isEffects( true, nDelayTime1+nDelayTime2 );
	CliamButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::CliamLifeUiButCallBack));

	UILabelAtlas* pMaxCliamNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->CliamLifelayout->getChildByName("label_2"));
	pMaxCliamNum->setStringValue( "5" );

	return m_mainmapuilayer->CliamLifelayout;
}

Layout* MainMapUiLayer::getPropBuyLayout(int propid)
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getPropInfoUI( WIDGET_TYPE_MAP, propid );
	if ( !pLayout )
		return NULL;
	else
		return pLayout;
}

Layout* MainMapUiLayer::getChangeInfoLayout(void)
{
	if ( !m_mainmapuilayer->changeinfoLayout)
	{
		m_mainmapuilayer->changeinfoLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_CHANGEINFO));
		m_mainmapuilayer->changeinfoLayout->autorelease();
		m_mainmapuilayer->changeinfoLayout->retain();

		UIImageView *psexSel1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->changeinfoLayout->getChildByName("selsexboy"));
		UIImageView *psexSel2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->changeinfoLayout->getChildByName("selsexgirl"));

		if ( 0 == AnalyseJson::logOnMsg.baseInfo.gender)
		{
			psexSel1->setTouchEnabled(true);
			psexSel2->setTouchEnabled(false);

			psexSel1->setVisible(true);
			psexSel2->setVisible(false);
		}
		else
		{
			psexSel1->setTouchEnabled(false);
			psexSel2->setTouchEnabled(true);
			psexSel1->setVisible(false);
			psexSel2->setVisible(true);
		}

		UIImageView* layout = dynamic_cast<UIImageView*>(changeinfoLayout->getChildByName("selectnamebg"));
		UINodeContainer* nodeContainer = UINodeContainer::create();
		nodeContainer->setPosition(ccp(0,0));

		CCSize editBoxSize = layout->getContentSize();
		m_pEditBox = CCEditBox::create(CCSizeMake(344, 79), CCScale9Sprite::create("Image/MainMapUi/editboxBG.png"));
		m_pEditBox->setFontSize(20);
		m_pEditBox->setTag(EDITBOX_TYPE_CHANGERINFO);
		m_pEditBox->setMaxLength( 10 );
		m_pEditBox->setTouchPriority( -1 );
		m_pEditBox->setFontColor(ccc3(216, 141, 70));
		m_pEditBox->setPlaceholderFontColor(ccc3(216, 141, 70/*0,0,0*/));
		m_pEditBox->setPlaceHolder( "");
		m_pEditBox->setInputMode(kEditBoxInputModeSingleLine);
		m_pEditBox->setDelegate(this); 
		m_pEditBox->setReturnType(kKeyboardReturnTypeDone);  
		nodeContainer->addCCNode(m_pEditBox);

		layout->addChild( nodeContainer );

		////
		UIImageView* layout_qq = dynamic_cast<UIImageView*>(changeinfoLayout->getChildByName("selectqqbg"));
		UINodeContainer* nodeContainer_qq = UINodeContainer::create();
		nodeContainer_qq->setPosition(ccp(0,0));

		CCSize editBoxSize_q = layout_qq->getContentSize();
		m_pEditBox = CCEditBox::create(CCSizeMake(344, 79), CCScale9Sprite::create("Image/MainMapUi/editboxBG.png"));
		m_pEditBox->setFontSize(20);
		m_pEditBox->setTag(EDITBOX_TYPE_QQINFO);
		m_pEditBox->setMaxLength( 10 );
		m_pEditBox->setTouchPriority( -1 );
		m_pEditBox->setFontColor(ccc3(216, 141, 70));
		m_pEditBox->setPlaceholderFontColor(ccc3(216, 141, 70/*0,0,0*/));
		m_pEditBox->setPlaceHolder( "");
		m_pEditBox->setInputMode(kEditBoxInputModePhoneNumber);
		m_pEditBox->setDelegate(this); 
		m_pEditBox->setReturnType(kKeyboardReturnTypeDone);  
		nodeContainer_qq->addCCNode(m_pEditBox);

		layout_qq->addChild( nodeContainer_qq );
	}

	m_mainmapuilayer->changeinfoLayout->setZOrder( 2 );
	m_mainmapuilayer->changeinfoLayout->setTouchEnabled(true);

	UIImageView* pSexboy = dynamic_cast<UIImageView*>(changeinfoLayout->getChildByName("selsexboy"));
	UIImageView* pSexgirl = dynamic_cast<UIImageView*>(changeinfoLayout->getChildByName("selsexgirl"));
	pSexboy->setTag(SEX_BOY_BUT);
	pSexgirl->setTag(SEX_GIRL_BUT);
	pSexboy->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::SexBtnCallBack));
	pSexgirl->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::SexBtnCallBack));

	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->changeinfoLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::ChangeInfoButCallBack));


	UIButton *SubmitButton = dynamic_cast<UIButton*>(m_mainmapuilayer->changeinfoLayout->getChildByName("m_btu_submit"));
	SubmitButton->setVisible(false);
	SubmitButton->setTouchEnabled(false);
	SubmitButton->setTag( 1 );
	SubmitButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::ChangeInfoButCallBack));
	SubmitButton->active();


	UIButton *SubmitButton_Pay = dynamic_cast<UIButton*>(m_mainmapuilayer->changeinfoLayout->getChildByName("m_btu_submit_pay"));
	SubmitButton_Pay->setVisible(false);
	SubmitButton_Pay->setTouchEnabled(false);
	SubmitButton_Pay->setTag( 1 );
	SubmitButton_Pay->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::ChangeInfoButCallBack));
	SubmitButton_Pay->active();

	if( AnalyseJson::logOnMsg.baseInfo.avatar_upd_times !=0)
	{
		SubmitButton_Pay->setVisible(true);
		SubmitButton_Pay->setTouchEnabled(true);
		SubmitButton_Pay->isEffects( true, nDelayTime1 + nDelayTime2*2 );


		std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
		for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
		{
			if(CANDY_PROP_OUT_HEAD == p->id)
				break;
		}
		if (atoi(p->candyprice.c_str()) > AnalyseJson::logOnMsg.baseInfo.candyNum)
		{
			SubmitButton_Pay->disable();
		}
		UILabel *pPrice = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("price_label"));
		pPrice->setText(p->candyprice.c_str());

	}
	else
	{
		SubmitButton->setVisible(true);
		SubmitButton->setTouchEnabled(true);
		SubmitButton->isEffects( true, nDelayTime1 + nDelayTime2*2 );

	}


	

	UILabel* pNiceName = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("inputnickname"));
	pNiceName->setScale( 0.7f );
	pNiceName->setText(AnalyseJson::logOnMsg.baseInfo.nickName.c_str());

	UILabel* pQQ = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("inputqq"));
	pQQ->setScale( 0.7f );
	if(AnalyseJson::logOnMsg.baseInfo.qq.size() != 0)
	{
		pQQ->setText(AnalyseJson::logOnMsg.baseInfo.qq.c_str());
	}
	else
	{
		pQQ->setText("");
	}
	UIImageView *pHead = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->changeinfoLayout->getChildByName("selectheadico_1"));
	char* headname = (char*)CCString::createWithFormat("%s%d.png", AnalyseJson::CandPicPath,AnalyseJson::logOnMsg.baseInfo.id)->getCString();
	if(!CCFileUtils::sharedFileUtils()->isFileExist(headname))
	{
		std::string headPath = CommonData::getHeadPathForUrl( AnalyseJson::logOnMsg.baseInfo.headPicUrl);
		pHead->setTexture(headPath.c_str());
	}
	else
	{
		pHead->setTexture(headname);
	}
	pHead->setTouchEnabled(true);
	pHead->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::uploadHead));

	return m_mainmapuilayer->changeinfoLayout;
}


Layout* MainMapUiLayer::getGetherStarTaskLayout( void )
{
	if ( !m_mainmapuilayer->getherStarLayout )
	{
		m_mainmapuilayer->getherStarLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_GETHERSTAR));
		m_mainmapuilayer->getherStarLayout->autorelease();
		m_mainmapuilayer->getherStarLayout->retain();
	}

	m_mainmapuilayer->getherStarLayout->setZOrder( 5 );
	m_mainmapuilayer->getherStarLayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->getherStarLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::getherStarBtnCallBack));

	UIButton *RewardsButton = dynamic_cast<UIButton*>(m_mainmapuilayer->getherStarLayout->getChildByName("btnRewardProp"));
	RewardsButton->setTouchEnabled(true);
	RewardsButton->setTag( 1 );
	RewardsButton->isEffects( true, nDelayTime1+nDelayTime2 );
	RewardsButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::getherStarBtnCallBack));

	UIImageView* pBtnRewardStr = dynamic_cast<UIImageView*>(m_mainmapuilayer->getherStarLayout->getChildByName( "ImageView_8134" ));
	UIImageView* pImgPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->getherStarLayout->getChildByName( "ImgPropBg" ));
	UIImageView* pImgNoTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->getherStarLayout->getChildByName( "ImgNoTask" ));


	if ( !AnalyseJson::taskTable.startTask.empty() ) 
	{
		pImgPropBg->setVisible( true );
		pImgNoTask->setVisible( false );

		std::list<SystemStarStarTask>::iterator item = AnalyseJson::taskTable.startTask.begin();

		if (AnalyseJson::taskTable.curstarnum - item->consumenum >= item->maxnum)	
			RewardsButton->active( true ); 
		else 
			RewardsButton->disable( true );


		pBtnRewardStr->setTouchEnabled( false );
		UIImageView* pPropIco = dynamic_cast<UIImageView*>(m_mainmapuilayer->getherStarLayout->getChildByName( "ImgPropid" ));
		pPropIco->setTexture( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", item->propid)->getCString() );
		pPropIco->setVisible( true );

		UILabelBMFont* pPropName = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->getherStarLayout->getChildByName( "TitleProp" ));
		char* pSPropName = (char*)CCString::createWithFormat("app_prop%d_title", item->propid)->getCString();
		pPropName->setText( CommonData::GetString(pSPropName).c_str() );

		UILabelAtlas* pCurStarNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->getherStarLayout->getChildByName("AtlasCurGetherNum"));
		pCurStarNum->setStringValue( CCString::createWithFormat("%d", AnalyseJson::taskTable.curstarnum - item->consumenum )->getCString() );

		UILabelAtlas* pMaxGeter = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->getherStarLayout->getChildByName("AtlasMaxGeter"));
		pMaxGeter->setStringValue( CCString::createWithFormat("%d", item->maxnum )->getCString() );

		UILabelAtlas* pAtlasPropNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->getherStarLayout->getChildByName("AtlasPropNum"));
		pAtlasPropNum->setStringValue( CCString::createWithFormat("%d", item->propnum )->getCString() );

	}
	else
	{
		pImgPropBg->setVisible( false );
		pImgNoTask->setVisible( true );
		RewardsButton->disable( true );
	}

	return m_mainmapuilayer->getherStarLayout;
}

void MainMapUiLayer::getherStarBtnCallBack(CCObject* pSender)
{
	PlayEffect(MUSIC_ITEM_BUTTON_E);
	UIButton* pBtn = (UIButton*)pSender;
	pBtn->setTouchEnabled( true );
	int tag = pBtn->getTag();

	pBtn->setTouchEnabled( false );
	if ( 0 == tag )
	{
		QuitMapWidget();
	}
	else if ( 1 == tag )
	{
		QuitMapWidget();
		if ( AnalyseJson::taskTable.startTask.empty() ) return;

		std::list<SystemStarStarTask>::iterator taskitem = AnalyseJson::taskTable.startTask.begin();

		// 道具奖励处理 
		std::list<UserPropInfoStr>::iterator propitem= AnalyseJson::logOnMsg.propInfo.begin();
		for (; propitem != AnalyseJson::logOnMsg.propInfo.end(); propitem++ )
		{
			if ( propitem->id == taskitem->propid ) { propitem->num += taskitem->propnum; break; }
		}

		//UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));
		//UIImageView* pUIPropIco = dynamic_cast<UIImageView*>(pBtn->getParent()->getChildByName( "ImgPropIco" ));
		//pUIPropIco->setVisible( false );

		//CCPoint tem1 = pUIPropIco->getParent()->convertToWorldSpace(pUIPropIco->getPosition());
		//CCPoint tem0 = pBtnMyInformat->getParent()->convertToWorldSpace( pBtnMyInformat->getPosition() );
		//CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", propitem->id)->getCString() );

		//if(pPropIco != NULL)
		//{
		//	pPropIco->setScale(1.6f);
		//	pPropIco->setPosition( tem1 );
		//	getWidgetUILayer()->addChild(pPropIco,232);

		//	pPropIco->runAction(CCSequence::create(	
		//		CCSpawn::create(
		//		getEffectBezierAction(tem1, ccpAdd( tem0, ccp(0, 0) )),
		//		CCScaleTo::create(1.2f, 0.2f),
		//		NULL),
		//		CCCallFuncN::create(this, callfuncN_selector(MainMapUiLayer::TaskRewardActionCallBack)),
		//		NULL
		//		));
		//	//setKnapsackAction( 1.2f );
		//}

		MsgMgr::sendGetRewardTask( AnalyseJson::logOnMsg.baseInfo.id , taskitem->taskid, AnalyseJson::taskTable.curstarnum - taskitem->consumenum );
	}
}

void MainMapUiLayer::TaskRewardActionCallBack(CCNode* pSende)
{
	//pSende->removeFromParent();
	//UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));

	//if ( pBtnMyInformat )
	//{
	//	CCPoint pos = pBtnMyInformat->getParent()->convertToWorldSpace(pBtnMyInformat->getPosition());
	//	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccpAdd( pos, ccp(0, 90) ), this);
	//}
	////　重新回到上一页
	//setTaskLable( 2 );
}

void MainMapUiLayer::DailyTaskActionCallBack(CCNode* pSende, void* data)
{
	pSende->removeFromParent();

	int ntaskid = (int)data;
	int nRewardGemNum = 0;

	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for (; item!=AnalyseJson::taskTable.dailyTask.end(); item++)
	{
		if( ntaskid == item->taskid )
		{
			nRewardGemNum = item->gemnum;
			item->status = 1;
			break;
		}
	}

	//// 播放特效 添加宝石
	//UIButton* GamegemBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("gembtn"));
	//if ( GamegemBut )
	//{
	//	CCPoint pos = GamegemBut->getParent()->convertToWorldSpace(GamegemBut->getPosition());
	//	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y), this);

	//	AnalyseJson::logOnMsg.baseInfo.gemNum += nRewardGemNum;
	//	m_pGemNum->setStringValue((char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.gemNum)->getCString());

	//	MsgMgr::sendGetRewardTask( AnalyseJson::logOnMsg.baseInfo.id ,ntaskid, 0 );

	//}
	setTaskLable( 3 );

	// 第一次领取日常任务后 弹出VIP
// 	if ( !AnalyseJson::logOnMsg.baseInfo.isVip )
// 	{
// 		m_mainmapuilayer->QuitMapWidgetCallback();
// 		showMapWidget( MAP_WIDGET_VIP_DLG );
// 		m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_VIPTASK );
// 	}
}

Layout* MainMapUiLayer::getKnapsackLayout( void )
{
	if ( !m_mainmapuilayer->knapsackLayout )
	{
		m_mainmapuilayer->knapsackLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_KNAPSACK));

		m_mainmapuilayer->knapsackLayout->retain();

	}
	m_mainmapuilayer->knapsackLayout->setZOrder( 2 );
	m_mainmapuilayer->knapsackLayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->knapsackLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::knapsackBtnCallBack));

	std::list<UserPropInfoStr>::iterator p  = AnalyseJson::logOnMsg.propInfo.begin();
	int j = 0;
	for (unsigned int i = 0; i < AnalyseJson::logOnMsg.propInfo.size(); i++)
	{
		// 32 为头像道具
		if ( 0 < p->num && 32 != p->id)
		{
			j++;

			UIImageView* pPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->knapsackLayout->getChildByName( CCString::createWithFormat( "ImgPropBg_%d", j)->getCString() ));
			pPropBg->setTouchEnabled(true);
			pPropBg->setTag( p->id );
			pPropBg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::knapsackBtnCallBack));
			pPropBg->removeAllChildren();

			UIImageView* pPropIco = UIImageView::create();
			pPropIco->setPosition( ccp(0, -5) );
			pPropIco->setTexture( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", p->id)->getCString() );
			pPropIco->setVisible( true );
			pPropBg->addChild( pPropIco );

			UIImageView* pPropNumBg = UIImageView::create();
			pPropNumBg->setTexture( "Image/MainMapUi/m_imgbg_propnum.png" );
			pPropNumBg->setVisible( true );
			pPropNumBg->setPosition( ccp(30 , -40) );
			pPropBg->addChild( pPropNumBg );

			UILabelBMFont *socreLabel = UILabelBMFont::create();
			socreLabel->setFntFile( "fonts/Score3/font.fnt" );
			socreLabel->setText( CCString::createWithFormat("%d",p->num)->getCString() );
			socreLabel->setScale( 0.7f );
			socreLabel->setAnchorPoint( ccp(0.5f, 0.5f) );
			socreLabel->setPosition( ccp(0,-8));
			pPropNumBg->addChild( socreLabel );
			// 			UILabelAtlas* pPropNum = UILabelAtlas::create();
			// 			pPropNum->setProperty("0" , "Image/MainMapUi/Tools/res_win/RankStr.png",28, 31, "0"); 
			// 			pPropNum->setStringValue( CCString::createWithFormat("%d",  p->num)->getCString() ); 
			// 			pPropNum->setVisible( true );
			// 			pPropNumBg->addChild( pPropNum );


		}

		p++;
	}

	UIImageView* pSelectK = dynamic_cast<UIImageView*>(m_mainmapuilayer->knapsackLayout->getChildByName( "ImgSeletK" ));
	UILabelBMFont* pPropExpain = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->knapsackLayout->getChildByName( "FntPropexpain" ));
	UILabelBMFont* pPropExpain1 = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->knapsackLayout->getChildByName( "FntPropexpain1" ));
	if ( j == 0 )
	{
		pPropExpain->setVisible( false );
		pPropExpain1->setVisible( false );
		pSelectK->setVisible( false );
	}
	else
	{
		UIImageView* pPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->knapsackLayout->getChildByName( "ImgPropBg_1" ));
		if ( 32 != pPropBg->getTag())
		{
			pSelectK->setPosition( ccp(pPropBg->getPosition().x, pPropBg->getPosition().y - 10) );
			pPropExpain->setText(CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain1_forknapsack", pPropBg->getTag() )->getCString()).c_str());
			pPropExpain1->setText( CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain2_forknapsack", pPropBg->getTag() )->getCString()).c_str());
		}

	}


	return m_mainmapuilayer->knapsackLayout;
}

void MainMapUiLayer::knapsackBtnCallBack(CCObject* pSender)
{
	UIWidget* pItem = (UIWidget*)pSender;
	int tag = pItem->getTag();

	if ( 0 == tag )
	{
		PlayEffect(MUSIC_ITEM_BUTTON_E);
		pItem->setTouchEnabled( false );
		QuitMapWidget();
	}
	else
	{
		UILabelBMFont* pPropExpain = dynamic_cast<UILabelBMFont*>(pItem->getParent()->getChildByName( "FntPropexpain" ));
		pPropExpain->setText( CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain1_forknapsack", tag )->getCString()).c_str());

		UILabelBMFont* pPropExpain1 = dynamic_cast<UILabelBMFont*>(pItem->getParent()->getChildByName( "FntPropexpain1" ));
		pPropExpain1->setText( CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain2_forknapsack", tag )->getCString()).c_str());

		UIImageView* pSelectK = dynamic_cast<UIImageView*>(pItem->getParent()->getChildByName( "ImgSeletK" ));
		pSelectK->setPosition( ccp(pItem->getPosition().x, pItem->getPosition().y - 6) );
	}

}

Layout* MainMapUiLayer::getMainTaskLayout(void)
{
	if ( !m_mainmapuilayer->mainTasklayout )
	{
		m_mainmapuilayer->mainTasklayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_MAINTASK));
		m_mainmapuilayer->mainTasklayout->autorelease();
		m_mainmapuilayer->mainTasklayout->retain();
	}

	m_mainmapuilayer->mainTasklayout->setZOrder( 5 );
	m_mainmapuilayer->mainTasklayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->mainTasklayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::mainTaskBtnCallBack));

	char* pMyGemNum = (char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.gemNum )->getCString();
	UILabelAtlas *pMyGemLab = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->mainTasklayout->getChildByName("LabelMyGemNum"));
	pMyGemLab->setStringValue( pMyGemNum );

//	addMainTaskToList();

	return m_mainmapuilayer->mainTasklayout;
}


Layout* MainMapUiLayer::getTaskLayout(void)
{
	if ( !m_mainmapuilayer->tasklayout )
	{
		m_mainmapuilayer->tasklayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_TASK));
		m_mainmapuilayer->tasklayout->autorelease();
		m_mainmapuilayer->tasklayout->retain();
	}

	m_mainmapuilayer->tasklayout->setZOrder( 5 );
	m_mainmapuilayer->tasklayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackTask));

	UIImageView* pLable1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable1P"));		//　星星任务
	UIImageView* pLable2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable2P"));		//　主线任务
	UIImageView* pLable3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable3P"));		//　日常任务

	UIImageView* pLableTitle1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("LableTitle1"));		//　星星任务
	UIImageView* pLableTitle2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("LableTitle2"));		//　主线任务
	UIImageView* pLableTitle3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("LableTitle3"));		//　日常任务

	pLableTitle1->setTexture( "res_task/labelStarTask.png", UI_TEX_TYPE_PLIST );
	pLableTitle2->setTexture( "res_task/LabelCandyTask.png", UI_TEX_TYPE_PLIST );
	pLableTitle3->setTexture( "res_task/LabelDailyTask.png", UI_TEX_TYPE_PLIST );


	pLableTitle1->setVisible( true );
	pLableTitle2->setVisible( true );
	pLableTitle3->setVisible( true );

	pLable1->setTouchEnabled( true );
	pLable2->setTouchEnabled( true );
	pLable3->setTouchEnabled( true );

	pLable1->setTag( 1 );
	pLable2->setTag( 2 );
	pLable3->setTag( 3 );

	pLable1->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackTask));
	pLable2->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackTask));
	pLable3->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackTask));


	//　判断是否解锁星星任务
// 	if ( AnalyseJson::unLockConfig.starTask >= MainMap::m_mainmap->getPassStageNum() )
// 	{
// 		pLable1->setTouchEnabled( false );
// 		pLableTitle1->setTexture( "res_task/LabelCandyTaskD.png", UI_TEX_TYPE_PLIST );
// 	}

	//　判断是否解锁主线任务
	if ( AnalyseJson::unLockConfig.mainTask >= MainMap::m_mainmap->getPassStageNum() )
	{
		pLableTitle2->setTexture( "res_task/LabelCandyTaskD.png", UI_TEX_TYPE_PLIST );
	}

	//　判断是否解锁日常任务
	if ( AnalyseJson::unLockConfig.dailyTask >= MainMap::m_mainmap->getPassStageNum() )
	{
		pLableTitle3->setTexture( "res_task/LabelDailyTaskD.png", UI_TEX_TYPE_PLIST );
	}

	// 设置当前显示的任务标签
	int nMaxLevel = CommonData::getMaxLevel();
	if ( nMaxLevel >= AnalyseJson::unLockConfig.starTask && nMaxLevel < AnalyseJson::unLockConfig.mainTask  )
		setTaskLable( 1 );
	else if ( nMaxLevel >= AnalyseJson::unLockConfig.mainTask && nMaxLevel < AnalyseJson::unLockConfig.dailyTask  )
		setTaskLable( 2 );
	else
		setTaskLable( 3 );



	return m_mainmapuilayer->tasklayout;
}

void MainMapUiLayer::setTaskLable( int index )
{

	UIPanel* pPanelLable1 = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName("PanelLable1"));
	UIPanel* pPanelLable2 = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName("PanelLable2"));
	UIPanel* pPanelLable3 = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName("PanelLable3"));
	
	UIImageView* pLableSel = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable1N"));

	UIScrollView* plistView1 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->tasklayout->getChildByName( "ScrollList1" ));
	plistView1->removeAllChildrenAndCleanUp( true );

	UIScrollView* plistView2 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->tasklayout->getChildByName( "ScrollList2" ));
	plistView2->removeAllChildrenAndCleanUp( true );

	CCPoint nOriginPos = ccp( -298, -339 );
	CCPoint nMoveTo = ccp( 1000, -339 );
	switch ( index )
	{
	case 1:
		{
			UIImageView* pLable1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable1P"));
			pLableSel->runAction( CCMoveTo::create( 0.05f, ccp(pLable1->getPosition().x, pLableSel->getPosition().y)));

			pPanelLable1->setVisible( true );
			pPanelLable2->setVisible( false );
			pPanelLable3->setVisible( false );

			pPanelLable1->setPosition( nOriginPos );
			pPanelLable2->setPosition( nMoveTo );
			pPanelLable3->setPosition( nMoveTo );

			InitTaskLable1();
		}
		break;

	case 2:
		{
			UIImageView* pLable2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable2P"));
			pLableSel->runAction( CCMoveTo::create( 0.05f, ccp(pLable2->getPosition().x, pLableSel->getPosition().y)));

			UIImageView* pImageMainTaskItem = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImageMainTaskItem"));
			pImageMainTaskItem->setTouchEnabled( false );

			pPanelLable1->setVisible( false );
			pPanelLable2->setVisible( true );
			pPanelLable3->setVisible( false );

			pPanelLable1->setPosition( nMoveTo );
			pPanelLable2->setPosition( nOriginPos );
			pPanelLable3->setPosition( nMoveTo );

			InitTaskLable2();
		}
		break;

	case 3:
		{
			if (AnalyseJson::taskTable.dailyTask.size()>0)
			{
				this->schedule( schedule_selector(MainMapUiLayer::updataTaskDownTime), 1, kCCRepeatForever, 0 );
			}

			UIImageView* pLable3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable3P"));
			pLableSel->runAction( CCMoveTo::create( 0.05f, ccp(pLable3->getPosition().x, pLableSel->getPosition().y)));
			pPanelLable1->setVisible( false );
			pPanelLable2->setVisible( false );
			pPanelLable3->setVisible( true );

			pPanelLable1->setPosition( nMoveTo );
			pPanelLable2->setPosition( nMoveTo );
			pPanelLable3->setPosition( nOriginPos );
			InitTaskLable3();
		}
		break;
	}
}

void MainMapUiLayer::InitTaskLable1( void )
{
	//　日常任务
	UIButton *RewardsButton = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName("btnRewardProp"));
	RewardsButton->setTouchEnabled(true);
	RewardsButton->setTag( 1 );
	RewardsButton->isEffects( true );
	RewardsButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::getherStarBtnCallBack));

	UIImageView* pImgPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImgPropBg" ));
	UIImageView* pImgNoTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImgNoTask" ));


	if ( !AnalyseJson::taskTable.startTask.empty() ) 
	{
		pImgPropBg->setVisible( true );
		pImgNoTask->setVisible( false );

		std::list<SystemStarStarTask>::iterator item = AnalyseJson::taskTable.startTask.begin();

		if (AnalyseJson::taskTable.curstarnum - item->consumenum >= item->maxnum)	
		{
			RewardsButton->active( true ); 
			UIImageView* pImgTitle = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImageView_8134_0" ));
			pImgTitle->setTouchEnabled( false );
		}
 		else 
 			RewardsButton->disable( true );


		UIImageView* pPropIco = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImgPropIco" ));
		pPropIco->setTexture( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", item->propid)->getCString() );
		pPropIco->setVisible( true );

		UILabelBMFont* pPropName = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "TitleProp" ));
		char* pSPropName = (char*)CCString::createWithFormat("app_prop%d_title", item->propid)->getCString();
		pPropName->setText( CommonData::GetString(pSPropName).c_str() );

		UILoadingBar* pLoadbarStarTask = dynamic_cast<UILoadingBar*>(m_mainmapuilayer->tasklayout->getChildByName("LoadingBarStarTask"));
		pLoadbarStarTask->setPercent( 100.0f * (AnalyseJson::taskTable.curstarnum - item->consumenum)/item->maxnum );

		UILabel* pLabelLoad = dynamic_cast<UILabel*>(m_mainmapuilayer->tasklayout->getChildByName("LabelLoading"));
		pLabelLoad->setText( CCString::createWithFormat("%d/%d",AnalyseJson::taskTable.curstarnum - item->consumenum  , item->maxnum )->getCString() );

		UILabel* pLabelLoad1 = dynamic_cast<UILabel*>(m_mainmapuilayer->tasklayout->getChildByName("LabelLoading1"));
		pLabelLoad1->setText( CCString::createWithFormat("%d/%d",AnalyseJson::taskTable.curstarnum - item->consumenum  , item->maxnum )->getCString() );

		UILabelAtlas* pAtlasPropNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->tasklayout->getChildByName("AtlasPropNum"));
		pAtlasPropNum->setStringValue( CCString::createWithFormat("%d", item->propnum )->getCString() );

	}
	else
	{
		pImgPropBg->setVisible( false );
		pImgNoTask->setVisible( true );
		RewardsButton->disable( true );
	}
}

void MainMapUiLayer::InitTaskLable2( void )
{
	addMainTaskToList();

	UIPanel* pPanelTaskInfo = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName( "PanelTaskInfo" ));
	pPanelTaskInfo->setVisible( false );
	pPanelTaskInfo->setTouchEnabled( false );

	//　设置领取按钮不可点
	UIButton* pBtnRewardProp = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName( "btnRewardProp_0" ));
	pBtnRewardProp->setTouchEnabled( false );

}

void MainMapUiLayer::InitTaskLable3( void )
{
	addEveryDayTaskToList();

	UIPanel* pPanelTaskInfo = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName( "PanelTaskInfo_0" ));
	pPanelTaskInfo->setVisible( false );
	pPanelTaskInfo->setTouchEnabled( false );

	UIImageView* pBtnTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImageStarTaskItem" ));
	pBtnTask->setTouchEnabled( false );

	UIButton* pBtnRewardProp = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName( "btnRewardProp_0_0" ));
	pBtnRewardProp->setTouchEnabled( false );
}

void MainMapUiLayer::setMainTaskInfo(int taskid)
{
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();

	do 
	{
		if ( item->taskid != taskid )
		{
			item++;
			continue;;
		}	

		UIPanel* pPanelTaskInfo = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName( "PanelTaskInfo" ));
		pPanelTaskInfo->setVisible( true );
		pPanelTaskInfo->setTouchEnabled( true );

		UIImageView* pBtnTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImageMainTaskItem" ));
		pBtnTask->setTouchEnabled( true );
		pBtnTask->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMainTaskInfo));

		UIImageView* pPropIco = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImgPropIco_0" ));
		pPropIco->setTexture( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", item->propid)->getCString() );
		pPropIco->setVisible( true );

		UILabelBMFont* pLabelTaskInfoMainTask = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "LabelTaskInfoMainTask" ));
		pLabelTaskInfoMainTask->setText( item->explain.c_str() );

		UILabelBMFont* pPropName = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "TitleProp_0" ));
		char* pSPropName = (char*)CCString::createWithFormat("app_prop%d_title", item->propid)->getCString();
		pPropName->setText( CommonData::GetString(pSPropName).c_str() );

		UILabelAtlas* pAtlasPropNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->tasklayout->getChildByName("AtlasPropNum_0"));
		pAtlasPropNum->setStringValue( CCString::createWithFormat("%d", item->propnum )->getCString() );

		UIButton* pBtnRewardProp = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName( "btnRewardProp_0" ));
		pBtnRewardProp->setTouchEnabled( true );
		pBtnRewardProp->isEffects( true );
		pBtnRewardProp->data = (void*)taskid;
		pBtnRewardProp->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMainTaskRewar));

		char* pSPropExpain = (char*)CCString::createWithFormat( "app_prop%d_expain1_forknapsack", item->propid)->getCString();
		char* pSPropExpain1 = (char*)CCString::createWithFormat( "app_prop%d_expain2_forknapsack", item->propid)->getCString();
		UILabelBMFont* pPropExpain = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "FntPropexpain_0" ));
		UILabelBMFont* pPropExpain_0 = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "FntPropexpain1_0" ));
		pPropExpain->setText( CommonData::GetString(pSPropExpain).c_str());
		pPropExpain_0->setText( CommonData::GetString(pSPropExpain1).c_str());

		if ( item->targer > CommonData::getMaxLevel() )
			pBtnRewardProp->disable( true );

		break;
	} while (item!=AnalyseJson::taskTable.mainTask.end());

}

Layout* MainMapUiLayer::getMyInformatLayout(void)
{
	if ( !m_mainmapuilayer->myInformatlayout )
	{
		m_mainmapuilayer->myInformatlayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile( MAP_EXPORTJSON_PATH_FOR_MYINFORMAT ));
		m_mainmapuilayer->myInformatlayout->autorelease();
		m_mainmapuilayer->myInformatlayout->retain();

		initChangeInfoLayout();
	}

	m_mainmapuilayer->myInformatlayout->setZOrder( 5 );
	m_mainmapuilayer->myInformatlayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->myInformatlayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMyInformat));

	UIImageView* pLable1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable1P"));
	UIImageView* pLable2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable2P"));

	pLable1->setTouchEnabled( true );
	pLable2->setTouchEnabled( true );

	pLable1->setTag( 1 );
	pLable2->setTag( 2 );

	pLable1->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMyInformat));
	pLable2->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMyInformat));

	setMyInformatLable( 1 );

	return m_mainmapuilayer->myInformatlayout;
}



#define MAP_BUTTON_PROP_N		"Image/MainMapUi/Prop/propBtnN.png"
#define MAP_BUTTON_PROP_P		"Image/MainMapUi/Prop/propBtnP.png"
void MainMapUiLayer::addMainTaskToList(void)
{
	if ( !m_mainmapuilayer->tasklayout )
		return;

	UIScrollView* plistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->tasklayout->getChildByName( "ScrollList1" ));
	CCSize scrollSize = plistView->getContentSize();
	plistView->removeAllChildrenAndCleanUp( true );
	int nListLen = AnalyseJson::taskTable.mainTask.size();
	CCSize itemPoint;

	AnalyseJson::friendInfoMsg.friendInfo.sort(Cmpare());
	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nListLen * 140 ;

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	plistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	plistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 140/2;

	int nOffset = 0;
	bool isCurTask = false;
	for (int i = 0; i<nListLen; i++)
	{
		// m_friendlist

		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setName(  CCString::createWithFormat("item%d", item->taskid)->getCString() );
		pItemImg->setScale9Size( CCSizeMake(600, 134));
		pItemImg->setVisible( true );
		pItemImg->setPosition(ccp(ClipWidth / 2, butMPointY));
		pItemImg->setTouchEnabled( true );
		pItemImg->setTag( item->taskid );
		pItemImg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMainTaskItem));
		plistView->addChild( pItemImg );
		butMPointY -= ( 140 );

		UIImageView* pItemBgL = UIImageView::create();
		pItemBgL->setTexture( "res_task/ListItemBg1.png", UI_TEX_TYPE_PLIST );
		pItemBgL->setAnchorPoint( ccp(1.0f, 0.5f) );
		pItemImg->addChild( pItemBgL );

		UIImageView* pItemBgR = UIImageView::create();
		pItemBgR->setTexture( "res_task/ListItemBg1.png", UI_TEX_TYPE_PLIST );
		pItemBgR->setAnchorPoint( ccp(0.0f, 0.5f) );
		pItemBgR->setFlipX( true );
		pItemImg->addChild( pItemBgR );

		UILabelBMFont* pTaskTitle = UILabelBMFont::create();

		if ( 1 == item->lockstate )
			pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt3/font.fnt" );
		else
			pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt2/font.fnt" );
		
		pTaskTitle->setText(  item->explain.c_str() );
		pTaskTitle->setPosition( ccp(0, 10));
		pItemImg->addChild( pTaskTitle );


// 		UITextButton* pBtnItem = UITextButton::create();
// 		pBtnItem->setNormalTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setPressedTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setDisabledTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setTouchEnabled( true );
// 		pBtnItem->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMainTaskItem));
// 		pBtnItem->setScale9Enable( true );
// 		pBtnItem->setScale9Size( CCSizeMake(550, 120));
// 		pBtnItem->setTag( item->taskid );
// 		pBtnItem->setName(  CCString::createWithFormat("item%d", item->taskid)->getCString() );
// 		pBtnItem->setPosition(ccp(0,0));
// 
// 		pBtnItem->setFontSize( 50 );
// 		pBtnItem->setFontName("黑体");
// 		pBtnItem->setTextColor( 0,0,0 );
// 		pBtnItem->setText( item->explain.c_str() );
// 		pItemImg->addChild( pBtnItem );

		//　用来定位当前滚动列表的位置　
		if ( 0 == item->lockstate && 0 == item->status )
		{
			if ( !isCurTask ) isCurTask = true;
		}

		if ( !isCurTask ) nOffset += 1;

		// 未解锁
		if ( 1 == item->lockstate )
		{
			//pBtnItem->setTextColor( 255, 255, 255 );
			//pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt3/font.fnt" );

			pItemBgL->setTexture( "res_task/ListItemBg2.png", UI_TEX_TYPE_PLIST );
			pItemBgR->setTexture( "res_task/ListItemBg2.png", UI_TEX_TYPE_PLIST );
			pItemBgR->setFlipX( true );

			//　VIP锁
			UIImageView* pTaskLockL = UIImageView::create();
			pTaskLockL->setTexture( "res_task/ImgTasklock.png", UI_TEX_TYPE_PLIST );
			pTaskLockL->setPosition( ccp(-200, 20));
			pTaskLockL->setScale( 0.8f );
			pTaskLockL->setName( "taskLockL" );
			pItemImg->addChild( pTaskLockL );

			UIImageView* psign3 = UIImageView::create();
			psign3->setTexture( "Image/MainMapUi/buyItem/map_gamico.png" );
			psign3->setName( "gemico" );
			psign3->setZOrder( 500 );
			psign3->setScale( 0.6f );
			psign3->setPosition(ccp( -30, -60));
			pTaskLockL->addChild( psign3 );

			UILabelBMFont *pLockprice = UILabelBMFont::create();
			pLockprice->setFntFile( "fonts/YellowFnt/font.fnt" );
			pLockprice->setText( CCString::createWithFormat("%d", item->lockConsumeGem)->getCString() );
			pLockprice->setScale( 0.4f );
			pLockprice->setZOrder( 500 );
			pLockprice->setName( "lockprice" );
			pLockprice->setPosition( ccp(10, -65));
			pTaskLockL->addChild( pLockprice );

			// 已完成
			if ( item->targer <= MainMap::getPassStageNum() )
			{
			}			
			// 未完成
			else 
			{		
			}
		}
		// 已解锁
		else if ( 0 == item->lockstate )
		{

			// 已领取
			if ( 1 == item->status )
			{
				pItemBgL->setTexture( "res_task/ListItemBg2.png", UI_TEX_TYPE_PLIST );
				pItemBgR->setTexture( "res_task/ListItemBg2.png", UI_TEX_TYPE_PLIST );
				pItemBgR->setFlipX( true );

				UILabelBMFont* pTaskTitle = UILabelBMFont::create();
				pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt1/font.fnt" );
				pTaskTitle->setText(  CommonData::GetString( "app_finishtask_str" ).c_str() );
				pTaskTitle->setPosition( ccp(0, -30));
				pItemImg->addChild( pTaskTitle );

// 				UIImageView* pTaskOver = UIImageView::create();
// 				pTaskOver->setTexture( "Image/MainMapUi/TaskRes/ImgTaskFinish.png" );
// 				pTaskOver->setScale( 0.9f );
// 				pTaskOver->setRotation( -18 );
// 				pTaskOver->setPosition(ccp(-130, 0));
// 				pItemImg->addChild( pTaskOver);

			}
			// 未领取
			else if ( 0 == item->status )
			{
				//pBtnItem->setTextColor( 0,255,0 );

				UILabelBMFont* pTaskTitle = UILabelBMFont::create();
				pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt1/font.fnt" );
				pTaskTitle->setText(  CommonData::GetString( "app_chliktaskexp_str" ).c_str() );
				pTaskTitle->setPosition( ccp(0, -30));
				pItemImg->addChild( pTaskTitle );

				// 已完成
				if ( item->targer <= MainMap::getPassStageNum()-1 )
				{					
				}
				// 未完成
				else
				{
				}
			}
		}
#if 0
		UIImageView* pItem0Img = UIImageView::create();
		pItem0Img->setTexture( "Image/MainMapUi/TaskRes/ImgTaskItemBg.png" );
		pItem0Img->setAnchorPoint( ccp(1.0f, 0.5f));
		pItem0Img->setFlipX( true );
		pItem0Img->setTouchEnable( true );
		pItem0Img->setTag( item->taskid );
		pItem0Img->setPosition(ccp(0,0));
		pItem0Img->setTouchEnabled(true);
		pItem0Img->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::mainTaskBtnCallBack));
		pItemImg->addChild( pItem0Img );


		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setVisible( true );
		pDivideline->setPosition(ccp(40, -80));
		pItemImg->addChild( pDivideline);

		pItemImg->setPosition(ccp(pItem0Img->getSize().width, butMPointY));
		plistView->addChild( pItemImg );


		//　用来定位当前滚动列表的位置　
		if ( 0 == item->lockstate && 0 == item->status )
		{
			if ( !isCurTask ) isCurTask = true;
		}

		if ( !isCurTask ) nOffset += 1;

		UIImageView* pItem1Img = UIImageView::create();
		pItem1Img->setTexture( "Image/MainMapUi/TaskRes/ImgTaskItemBg.png" );
		pItem1Img->setAnchorPoint( ccp(0.0f, 0.5f));
		pItem1Img->setTouchEnable( true );
		pItem1Img->setName( "item1");
		pItem1Img->setPosition(ccp(0, 0));
		pItem1Img->setTag( item->taskid );
		pItem1Img->setTouchEnabled(true);
		pItem1Img->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::mainTaskBtnCallBack));
		pItemImg->addChild( pItem1Img);

		UIButton* pPropBtn = UIButton::create();
		pPropBtn->setNormalTexture( MAP_BUTTON_PROP_N );
		pPropBtn->setPressedTexture( MAP_BUTTON_PROP_P );
		pPropBtn->setDisabledTexture ( MAP_BUTTON_PROP_P );
		pPropBtn->setName("propbtn");
		pPropBtn->setPosition(ccp(310 , -45.0f));
		pPropBtn->setAnchorPoint( ccp(0.5f ,0.0f) );
		pPropBtn->setTag( item->taskid );
		pPropBtn->setTouchEnabled(true);
		pPropBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::mainTaskBtnCallBack));
		pItemImg->addChild( pPropBtn );

		char* pPropTag = (char*)CCString::createWithFormat("propico%d", item->propid )->getCString();
		char* pPropName = (char*)CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", item->propid )->getCString();
		UIImageView* pPropIco = UIImageView::create();
		pPropIco->setName( pPropTag );
		pPropIco->setTexture( pPropName );
		pPropIco->setPosition(ccp(0, 45));
		pPropBtn->addChild( pPropIco);

		// 未解锁
		if ( 1 == item->lockstate )
		{

			UILabel* pTaskTitle = UILabel::create();
			pTaskTitle->setPosition( ccp(0, 0) );
			pTaskTitle->setColor( ccc3(255,255,255));
			pTaskTitle->setFontSize( 45 );
			pTaskTitle->setFontName("黑体");
			pTaskTitle->setName("taskTitle");
			pTaskTitle->setText( (const char *)item->explain.c_str() );
			pTaskTitle->setVisible( true );
			pItemImg->addChild( pTaskTitle );	

			UIImageView* pLackL = UIImageView::create();
			pLackL->setTexture( "Image/MainMapUi/TaskRes/ImgTaskLack.png" );
			pLackL->setName( "lockl" );
			pLackL->setAnchorPoint( ccp(1.0f, 0.5f));
			pLackL->setPosition(ccp(0,-40));
			pItemImg->addChild( pLackL);

			UIImageView* pLackR = UIImageView::create();
			pLackR->setTexture( "Image/MainMapUi/TaskRes/ImgTaskLack.png" );
			pLackR->setName( "lockr" );
			pLackR->setFlipX( true );
			pLackR->setZOrder(0);
			pLackR->setAnchorPoint( ccp(0.0f, 0.5f));
			pLackR->setPosition(ccp(0,0));
			pLackL->addChild( pLackR);

			UIImageView* psign3 = UIImageView::create();
			psign3->setTexture( "Image/MainMapUi/buyItem/map_gamico.png" );
			psign3->setName( "gemico" );
			psign3->setZOrder( 500 );
			psign3->setScale( 0.6f );
			psign3->setAnchorPoint( ccp(0.0f, 0.5f));
			psign3->setPosition(ccp( 15, -65));
			pLackL->addChild( psign3 );

			UILabelBMFont *pLockprice = UILabelBMFont::create();
			pLockprice->setFntFile( "fonts/YellowFnt/font.fnt" );
			pLockprice->setText( CCString::createWithFormat("%d", item->lockConsumeGem)->getCString() );
			pLockprice->setScale( 0.4f );
			pLockprice->setZOrder( 500 );
			pLockprice->setName( "lockprice" );
			pLockprice->setPosition( ccp(-10, -70));
			pLackL->addChild( pLockprice );


			char* pPropName = (char*)CCString::createWithFormat("Image/MainMapUi/Prop/prop%dP.png", item->propid )->getCString();
			pPropIco->setTexture( pPropName );
			pPropBtn->disable(true);

			// 已完成
			if ( item->targer <= MainMap::getPassStageNum() )
				pPropBtn->runAction( getTaskMsgTipsAction() );
			// 未完成
			else 
				pPropBtn->isEffects( true );

			// 显示奖励个数
			UIImageView* psign = UIImageView::create();
			psign->setTexture( "Image/MainMapUi/m_imgbg_propnum.png" );
			psign->setPosition(ccp(40, 0));
			pPropBtn->addChild( psign );				

			UILabelBMFont *pLabelFntPropNum = UILabelBMFont::create();
			pLabelFntPropNum->setFntFile( "fonts/WhiteFnt/font.fnt" );
			pLabelFntPropNum->setText( CCString::createWithFormat("%d", item->propnum)->getCString() );
			pLabelFntPropNum->setScale( 0.8f );
			pLabelFntPropNum->setPosition( ccp(-2,-7));
			psign->addChild( pLabelFntPropNum );

		}
		// 已解锁
		else if ( 0 == item->lockstate )
		{

			UILabel* pTaskTitle = UILabel::create();
			pTaskTitle->setPosition( ccp(0, 0) );
			pTaskTitle->setColor( ccc3(255,255,255));
			pTaskTitle->setFontSize( 45 );
			pTaskTitle->setFontName("黑体");
			pTaskTitle->setName("taskTitle");
			pTaskTitle->setText( (const char *)item->explain.c_str() );
			pTaskTitle->setVisible( true );
			pItemImg->addChild( pTaskTitle );	

			// 			UILabel* pTaskExplain = UILabel::create();
			// 			pTaskExplain->setPosition( ccp(0, -35) );
			// 			pTaskExplain->setColor( ccc3(255,255,255));
			// 			pTaskExplain->setFontSize( 33 );
			// 			pTaskExplain->setFontName("宋体");
			// 			pTaskExplain->setText( (const char *)item->explain.c_str() );
			// 			pTaskExplain->setVisible( true );
			// 			pItemImg->addChild( pTaskExplain );

			// 已领取
			if ( 1 == item->status )
			{
				pTaskTitle->setColor( ccc3(0,255,0));

				pItem1Img->setTouchEnabled( false );
				pItemImg->setTouchEnabled( false );
				pPropBtn->setTouchEnabled( false );

				UIImageView* pTaskOver = UIImageView::create();
				pTaskOver->setTexture( "Image/MainMapUi/TaskRes/ImgTaskFinish.png" );
				pTaskOver->setRotation( -18 );
				pTaskOver->setPosition(ccp(228, 0));
				pItemImg->addChild( pTaskOver);

				char* pPropName = (char*)CCString::createWithFormat("Image/MainMapUi/Prop/prop%dP.png", item->propid )->getCString();
				pPropIco->setTexture( pPropName );
				pPropBtn->disable(true);
			}
			// 未领取
			else if ( 0 == item->status )
			{
				// 已完成
				if ( item->targer <= MainMap::getPassStageNum()-1 )
					pPropBtn->runAction( getTaskMsgTipsAction() );
				// 未完成
				else
				{
					pPropBtn->disable(true);
					pPropBtn->isEffects(true );
				}

				// 显示奖励个数
				UIImageView* psign = UIImageView::create();
				psign->setTexture( "Image/MainMapUi/m_imgbg_propnum.png" );
				psign->setPosition(ccp(40, 0));
				pPropBtn->addChild( psign );

				UILabelBMFont *pLabelFntPropNum = UILabelBMFont::create();
				pLabelFntPropNum->setFntFile( "fonts/WhiteFnt/font.fnt" );
				pLabelFntPropNum->setText( CCString::createWithFormat("%d", item->propnum)->getCString() );
				pLabelFntPropNum->setScale( 0.8f );
				pLabelFntPropNum->setPosition( ccp(-2,-7));
				psign->addChild( pLabelFntPropNum );

			}

		}

#endif

		item++;
	}
	if ( isCurTask )
	{
		if (ClipHeight > scrollSize.height)
		{
			//nOffset += 1;
			UIWidget *pwidgt = plistView->getInnerContainer();
			CCPoint pos = pwidgt->getPosition();
			CCPoint offsetpos = ccp(0, pos.y + nOffset*(140 + 15));

			if ( offsetpos.y > 0)
				offsetpos.y = 0;
			pwidgt->setPosition(ccp(0, offsetpos.y));

		}
	}
	/*	pwidgt->setPosition(ccp(0, (nOffset) * (140 + 15)));*/


}


void MainMapUiLayer::mainTaskBtnCallBack(CCObject* pSender)
{
	UIWidget* pItem = (UIWidget*)pSender;
	int tag = pItem->getTag();

	char* pItemName =(char*) pItem->getName();

	if ( 0 == tag )
	{
		PlayEffect(MUSIC_ITEM_BUTTON_E);
		pItem->setTouchEnabled( false );
		QuitMapWidget();
		return;
	}

	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();

	for( ; item != AnalyseJson::taskTable.mainTask.end(); item++)
	{
		if ( tag == item->taskid)
		{

			std::string nItemName = CCString::createWithFormat("item%d", item->taskid)->getCString();
			UIImageView* pTempItem = NULL;
			if ( 0 == nItemName.find( pItem->getName() ))
				pTempItem = (UIImageView*)pItem;
			else
				pTempItem = (UIImageView*)pItem->getParent();

			// 未领取 并 已开锁 并 完成指定关卡
			if ( /*string::npos*/1 != item->status && 0 == item->lockstate && (int)AnalyseJson::logOnMsg.stageInfo.size() >= item->targer)
			{				
				// 领取
				UIImageView* pImgItem = (UIImageView*)pSender;
				UIButton* pButProp = (UIButton*)pTempItem->getChildByName("propbtn");
				UILabel* pTaskTitle = (UILabel*)pTempItem->getChildByName("taskTitle");

				pButProp->stopAllActions();
				pButProp->isEffects( true );
				pTaskTitle->setColor( ccc3(0,255,0));

				MsgMgr::sendGetRewardTask( AnalyseJson::logOnMsg.baseInfo.id ,item->taskid, 0 );

				UIImageView* pTaskOver = UIImageView::create();
				pTaskOver->setTexture( "Image/MainMapUi/TaskRes/ImgTaskFinish.png" );
				pTaskOver->setRotation( -18 );
				pTaskOver->setPosition(ccp(228, 0));
				pTaskOver->setScale( 2.0f );


				pTempItem->setTouchEnabled( false );
				pTempItem->addChild( pTaskOver);
				pTaskOver->runAction( CCScaleTo::create(0.2f, 1.0));

				UIImageView* pTempItem1 = (UIImageView*)pTempItem->getChildByName("item1");
				if ( pTempItem1 )
					pTempItem1->setTouchEnabled( false );

				UIButton* pPropBtn = (UIButton*)pTempItem->getChildByName("propbtn");
				if ( pPropBtn )
				{ 
					pPropBtn->removeAllChildren(); 
					pPropBtn->disable(true); 
					pPropBtn->setTouchEnabled( false );

					char* pPropName = (char*)CCString::createWithFormat("Image/MainMapUi/Prop/prop%dP.png", item->propid )->getCString();
					UIImageView* pPropIco = UIImageView::create();
					pPropIco->setName( "propico" );
					pPropIco->setTexture( pPropName );
					pPropIco->setPosition(ccp(0, 45));
					pPropBtn->addChild( pPropIco );

				}

				// 播放领取动作
				char* pPropTag = (char*)CCString::createWithFormat("propico%d", item->propid )->getCString();
				UIImageView* pUIPropIco = (UIImageView*)pTempItem->getChildByName( "propico" );
				//pUIPropIco->setVisible( false );

				CCPoint tem1 = pUIPropIco->getParent()->convertToWorldSpace(pUIPropIco->getPosition());
				CCPoint tem0 = m_KnapsacBut->getParent()->convertToWorldSpace( m_KnapsacBut->getPosition() );
				CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", item->propid)->getCString() );

				if(pPropIco != NULL)
				{
					pPropIco->setScale(1.6f);
					pPropIco->setPosition( tem1 );
					getWidgetUILayer()->addChild(pPropIco,232);

					pPropIco->runAction(CCSequence::create(	
						CCSpawn::create(
						getEffectBezierAction(tem1, tem0),
						CCScaleTo::create(1.2f, 0.2f),
						NULL),
						CCCallFuncN::create(this, callfuncN_selector(MainMapUiLayer::TaskRewardActionCallBack)),
						NULL
						));
				}

				// 修改领取状态
				item->status = 1;
				CommonData::changePropNum( (CandyPropType)item->propid, item->propnum );
#ifdef CANDY_STATISITICAL_DATA
				//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4012, CCString::createWithFormat("%d", item->taskid)->getCString(), CCString::createWithFormat("%d", CommonData::getMaxLevel())->getCString() );
#endif
			}
			// 未解锁
			else if ( 1 == item->lockstate )
			{
				if ( AnalyseJson::logOnMsg.baseInfo.gemNum >= item->lockConsumeGem )
				{
					//去解锁
					MsgMgr::sendUnLockTask(AnalyseJson::logOnMsg.baseInfo.id, tag );

					// 修改我的宝石
					AnalyseJson::logOnMsg.baseInfo.gemNum -= item->lockConsumeGem;
					char* pMyGemNum = (char*)CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.gemNum )->getCString();
					UILabelAtlas *pMyGemLab = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->mainTasklayout->getChildByName("LabelMyGemNum"));
					pMyGemLab->setStringValue( pMyGemNum );


					UIImageView* pLockL = (UIImageView*)pTempItem->getChildByName("lockl");
					if ( pLockL ) pLockL->removeFromParent();

					UIImageView* pLockR = (UIImageView*)pTempItem->getChildByName("lockr");
					if ( pLockR ) pLockR->removeFromParent();

					UIImageView* pGemIco = (UIImageView*)pTempItem->getChildByName("gemico");
					if ( pGemIco ) pGemIco->removeFromParent();

					UIImageView* plockprice = (UIImageView*)pTempItem->getChildByName("lockprice");
					if ( plockprice ) plockprice->removeFromParent();

					// 任务按钮
					UIButton* pPropBtn = (UIButton*)pTempItem->getChildByName("propbtn");
					if ( pPropBtn )
					{ 
						pPropBtn->removeAllChildren(); 
						pPropBtn->active(true); 
						pPropBtn->setTouchEnabled( true );

						// 道具ICO
						char* pPropName = (char*)CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", item->propid )->getCString();
						UIImageView* pPropIco = UIImageView::create();
						pPropIco->setName( "propico" );
						pPropIco->setTexture( pPropName );
						pPropIco->setPosition(ccp(0, 45));
						pPropBtn->addChild( pPropIco );

						// 数量背景
						UIImageView* psign = UIImageView::create();
						psign->setTexture( "Image/MainMapUi/m_imgbg_propnum.png" );
						psign->setPosition(ccp(40, -40));
						pPropBtn->addChild( psign );				

						// 道具数量
						UILabelBMFont *pLabelFntPropNum = UILabelBMFont::create();
						pLabelFntPropNum->setFntFile( "fonts/WhiteFnt/font.fnt" );
						pLabelFntPropNum->setText( CCString::createWithFormat("%d", item->propnum)->getCString() );
						pLabelFntPropNum->setScale( 0.8f );
						pLabelFntPropNum->setPosition( ccp(-2,-7));
						psign->addChild( pLabelFntPropNum );

					}

					// 修改解锁状态
					item->lockstate = 0;
#ifdef CANDY_STATISITICAL_DATA
					//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4011, CCString::createWithFormat("%d", item->taskid)->getCString() );
#endif

				}
				else
				{
					// 宝石不够啊 要去买呗
// 					QuitMapWidgetCallback();
// 					showMapWidget( MAP_WIDGET_BUYGEM_LIST );
					AnalyseJson::taskTable.buytaskid = tag;
					buyUnlockMainTask( item->lockConsumeGem );
				}
			}

		}
	}

}

Layout* MainMapUiLayer::getDailyTaskExtraLayout(int tasktype)
{
	if ( !m_mainmapuilayer->dailyTaskExtralayout )
	{
		m_mainmapuilayer->dailyTaskExtralayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_DAILYTASK));
		m_mainmapuilayer->dailyTaskExtralayout->autorelease();
		m_mainmapuilayer->dailyTaskExtralayout->retain();
	}

	m_mainmapuilayer->dailyTaskExtralayout->setZOrder( 5 );
	m_mainmapuilayer->dailyTaskExtralayout->setTouchEnabled(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::mainTaskBtnCallBack));


	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();

	for(; item!=AnalyseJson::taskTable.dailyTask.end(); item++)
	{
		if( tasktype == item->type )
			break;
	}

	UILabelAtlas *pLabelRewardNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelRewardNum"));
	UILabel *pTask1 = dynamic_cast<UILabel*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelTask1"));
	UILabel *pTask2 = dynamic_cast<UILabel*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelTask2"));

	pLabelRewardNum->setStringValue( CCString::createWithFormat("%d", item->gemnum)->getCString() );
	// 糖果收集
	if ( 1 == tasktype )
	{
		pTask1->setVisible( true );
		pTask2->setVisible( false );

		UILabelAtlas *pTargetLabel = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelCandyNum"));
		UIImageView *pCandyId = dynamic_cast<UIImageView*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("ImgCandyIco"));

		pTargetLabel->setStringValue( CCString::createWithFormat("%d", item->targer)->getCString() );
		pCandyId->setTexture( getDailyTexturesBtnBuyId( item->claimid ));
	}
	else if( 2 == tasktype )
	{
		pTask1->setVisible( false );
		pTask2->setVisible( true );

		UILabelAtlas *pTargetlevel = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelLevelNum"));
		UILabelAtlas *pTargetstar = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->dailyTaskExtralayout->getChildByName("LabelStarNum"));

		pTargetlevel->setStringValue( CCString::createWithFormat("%d", item->claimid)->getCString() );
		pTargetstar->setStringValue( CCString::createWithFormat("%d", item->targer)->getCString() );

	}

	return m_mainmapuilayer->dailyTaskExtralayout;
}

void MainMapUiLayer::BtnCallBackTask(CCObject *pSender)
{
	UIWidget* pItem = (UIWidget*)pSender;
	int tag = pItem->getTag();

	char* pItemName =(char*) pItem->getName();

	UIImageView* pLableSel = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgLable1N"));

	switch ( tag )
	{
	case 0:
		{
			/*UIImageView* pImgNewTaskStr = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ImgNewTaskStr"));
			pImgNewTaskStr->setVisible( false );

			PlayEffect(MUSIC_ITEM_BUTTON_E);
			pItem->setTouchEnabled( false );
			QuitMapWidget();*/
		}
		break;

	case 1:
		{
			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			setTaskLable( 1 );
		}
		break;

	case 2:
		{
			if ( AnalyseJson::unLockConfig.mainTask >= MainMap::m_mainmap->getPassStageNum() )
			{
				showUnlockPrompt(PROMPT_TYPE_UNLOCK_MAINTASK, pItem->getParent()->convertToWorldSpace(pItem->getPosition()) );
				break;
			}


			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
			break;

			setTaskLable( 2 );
		}
		break;

	case 3:
		{
			if ( AnalyseJson::unLockConfig.dailyTask >= MainMap::m_mainmap->getPassStageNum() )
			{
				showUnlockPrompt(PROMPT_TYPE_UNLOCK_EVERYDAYTASK, pItem->getParent()->convertToWorldSpace(pItem->getPosition()) );
				break;
			}

			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			setTaskLable( 3 );
		}
		break;
	}

}

void MainMapUiLayer::BtnCallBackMainTaskItem(CCObject *pSender)
{
	UIButton* pBtnItem = (UIButton*)pSender;
	int nTaskid = pBtnItem->getTag();
	
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
	for (; item!=AnalyseJson::taskTable.mainTask.end(); item++ )
	{
		if ( item->taskid == nTaskid )
		{
			break;
		}
	}

	//　未解锁
	if ( 1 == item->lockstate )
	{
		if ( AnalyseJson::logOnMsg.baseInfo.gemNum >= item->lockConsumeGem )
		{
			//去解锁
			MsgMgr::sendUnLockTask(AnalyseJson::logOnMsg.baseInfo.id, nTaskid );

			// 修改我的宝石
			AnalyseJson::logOnMsg.baseInfo.gemNum -= item->lockConsumeGem;

			UIImageView* pLockL = (UIImageView*)pBtnItem->getParent()->getChildByName("taskLockL");
			if ( pLockL ) pLockL->removeFromParent();

			UIImageView* pLockR = (UIImageView*)pBtnItem->getParent()->getChildByName("taskLockR");
			if ( pLockR ) pLockR->removeFromParent();

			item->lockstate = 0;
			item->status = 0;
		}
		else
		{
			AnalyseJson::taskTable.buytaskid = nTaskid;
			buyUnlockMainTask( item->lockConsumeGem );
		}
	}
	//　已领取
	else if (0  == item->status )
	{
		setMainTaskInfo( nTaskid );
	}

}

void MainMapUiLayer::BtnCallBackMainTaskInfo(CCObject *pSender)
{
	setTaskLable( 2 );
}

void MainMapUiLayer::BtnCallBackMainTaskRewar(CCObject *pSender)
{
	UIButton* pBtn = (UIButton*)pSender;
	int nTaskid = (int)pBtn->data;
	int nPropid = 0;

	pBtn->setTouchEnabled( false );

	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
	for ( ; item!=AnalyseJson::taskTable.mainTask.end(); item++ )
	{
		if ( item->taskid == nTaskid )
		{
			nPropid = item->propid;
			break;
		}
	}

	MsgMgr::sendGetRewardTask( AnalyseJson::logOnMsg.baseInfo.id ,nTaskid, 0 );
// 
	// 播放领取动作
	UIImageView* pUIPropIco = (UIImageView*)pBtn->getParent()->getChildByName( "ImgPropIco_0" );

	CCPoint tem1 = pUIPropIco->getParent()->convertToWorldSpace(pUIPropIco->getPosition());

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint tem0 = ccp(winSize.width, -80 );
	CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", nPropid)->getCString() );

	item->status = 1;
	if(pPropIco != NULL)
	{
		pPropIco->setScale(1.6f);
		pPropIco->setPosition( tem1 );
		getWidgetUILayer()->addChild(pPropIco,232);

		pPropIco->runAction(CCSequence::create(	
			CCSpawn::create(
			getEffectBezierAction(tem1, ccpAdd( tem0, ccp(0, 90) )),
			CCScaleTo::create(1.2f, 0.2f),
			NULL),
			CCCallFuncN::create(this, callfuncN_selector(MainMapUiLayer::TaskRewardActionCallBack)),
			NULL
			));

		setKnapsackAction( 1.2f );
	}

}

void MainMapUiLayer::updateHead(float dt)
{
	if(CommonData::m_ModifiedHeadPhoto == true)
	{
		UIImageView *pHead = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->changeinfoLayout->getChildByName("selectheadico_1"));

		char* headname = (char*)CCString::createWithFormat("%s%dtemporary.png", AnalyseJson::CandPicPath,AnalyseJson::logOnMsg.baseInfo.id)->getCString();
		CCLog("updateHead: the headimage is %s",headname);

		CCTextureCache::sharedTextureCache()->removeTextureForKey(headname);  
		pHead->setTexture(headname);
		CommonData::m_ModifiedHeadPhoto = false;
		this->unschedule( schedule_selector(MainMapUiLayer::updateHead) );
	}
}

void MainMapUiLayer::uploadHead(CCObject *pSender)
{
// 	UIImageView *pUploadHead = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->changeinfoLayout->getChildByName("selectheadico_1"));
// 	pUploadHead->setTouchEnabled(false);

	//this->schedule(schedule_selector(MainMapUiLayer::updateHead), 4.0f);
}
void MainMapUiLayer::SexBtnCallBack(CCObject *pSender)
{
	UIImageView* pItemBut = (UIImageView*)pSender;
	int index = pItemBut->getTag();

	switch( index )
	{
	case SEX_BOY_BUT:
		{
			pItemBut->getParent()->getChildByTag(SEX_GIRL_BUT)->setVisible(true);
			pItemBut->getParent()->getChildByTag(SEX_GIRL_BUT)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);
			AnalyseJson::logOnMsg.baseInfo.gender = 1;
		}
		break;
	case SEX_GIRL_BUT:
		{
			pItemBut->getParent()->getChildByTag(SEX_BOY_BUT)->setVisible(true);
			pItemBut->getParent()->getChildByTag(SEX_BOY_BUT)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);
			AnalyseJson::logOnMsg.baseInfo.gender = 0;

		}
		break;
	}
}
Layout* MainMapUiLayer::getSeachfriendLayer(void)
{
	if ( !m_mainmapuilayer->seachfriendLayout )
	{
		m_mainmapuilayer->seachfriendLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile( MAP_EXPORTJSON_PATH_FOR_SEACHFRIEND ));
		m_mainmapuilayer->seachfriendLayout->autorelease();
		m_mainmapuilayer->seachfriendLayout->retain();

	}

	m_mainmapuilayer->seachfriendLayout->setZOrder( 2 );
	m_mainmapuilayer->seachfriendLayout->setTouchEnabled( true );
	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;


	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->seachfriendLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::SeachfriendBtnCB));

	UIButton *seachButton = dynamic_cast<UIButton*>(m_mainmapuilayer->seachfriendLayout->getChildByName("m_btn_seach"));
	seachButton->setTouchEnabled(true);
	seachButton->setTag( 1 );
	//seachButton->isEffects( true, nDelayTime1 );
	seachButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::SeachfriendBtnCB));

	UIScrollView* pListView  = dynamic_cast<UIScrollView*> (m_mainmapuilayer->seachfriendLayout->getChildByName("m_sv_list"));
	pListView->removeAllChildrenAndCleanUp(true);
	AnalyseJson::SeachFriendList.nofriend.clear();

	UITextField* pField = dynamic_cast<UITextField*>(m_mainmapuilayer->seachfriendLayout->getChildByName("Seachinput"));
	pField->setText("");

	UILabel* pNothing = dynamic_cast<UILabel*>(m_mainmapuilayer->seachfriendLayout->getChildByName("LabelNoting"));
	pNothing->setVisible( false );

	UIImageView* pSeachIco  = dynamic_cast<UIImageView*> (m_mainmapuilayer->seachfriendLayout->getChildByName("img_seachico"));
	pSeachIco->setVisible(true);

	return m_mainmapuilayer->seachfriendLayout;
}

Layout* MainMapUiLayer::getNoticeLayout(void)
{
	if ( !m_mainmapuilayer->noticeLayout )
	{
		m_mainmapuilayer->noticeLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(MAP_EXPORTJSON_PATH_FOR_NOTICE));
		m_mainmapuilayer->noticeLayout->autorelease();
		m_mainmapuilayer->noticeLayout->retain();
	}
	m_mainmapuilayer->noticeLayout->setZOrder( 2 );
	m_mainmapuilayer->noticeLayout->setTouchEnabled(true);

	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(m_mainmapuilayer->noticeLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(getWidgetUILayer(), coco_releaseselector(MainMapUiLayer::NoticeUiButCallBack));

	UIScrollView* pScroll = dynamic_cast<UIScrollView*>(m_mainmapuilayer->noticeLayout->getChildByName( "noticelist" ));
	pScroll->setTouchEnabled( true );

	UITextArea* pTextArea = UITextArea::create();
	pTextArea->setName("noticetext");
	pTextArea->setText( "" );
	pTextArea->setTextAreaSize( CCSizeMake( pScroll->getContentSize().width, 0));
	pTextArea->setColor( ccc3(0,0,0));
	pTextArea->setAnchorPoint( ccp(0.0f, 1.0f));
	pTextArea->setPosition( ccp(0, pScroll->getContentSize().height));
	pTextArea->setFontSize( 30 );
	pScroll->addChild( pTextArea );

	MsgMgr::sendGetNoticeData();
	setLoading( true );

	return m_mainmapuilayer->noticeLayout;
}

Layout* MainMapUiLayer::getBuyGemLayer(void)
{
	Layout* layout = NULL;
	layout = CommonWidgt::getBuyGemUI( WIDGET_TYPE_MAP );
	return layout;
}


void MainMapUiLayer::editBoxReturn(cocos2d::extension::CCEditBox * myeditbox)
{

}

void MainMapUiLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
 	int index = editBox->getTag();

	if (EDITBOX_TYPE_CHANGERINFO == index)
		editBox->setText( m_Nicknamestr.c_str() );
	else if (EDITBOX_TYPE_QQINFO == index)
		editBox->setText( m_qqstr.c_str() );
	else if (EDITBOX_TYPE_FEEDBACK == index)
		editBox->setText( m_feedbackstr.c_str() );
	else if (EDITBOX_TYPE_SEACHFRIEND == index )
		editBox->setText( m_seachStr.c_str() );
}

void MainMapUiLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * myeditbox)
{
	int index = myeditbox->getTag();

	if (EDITBOX_TYPE_CHANGERINFO == index)
	{
		myeditbox->setText( "" );
		UILabel* pTextLabel = dynamic_cast<UILabel*>(changeinfoLayout->getChildByName("inputnickname"));
		pTextLabel->setText( m_Nicknamestr.c_str() );
	}
	else if (EDITBOX_TYPE_FEEDBACK == index)
	{
		myeditbox->setText( "" );
		UITextArea* pTextArea = dynamic_cast<UITextArea*>(feedbacklayout->getChildByName("feedback_text"));
		pTextArea->setText( m_feedbackstr.c_str() );
	}
	else if (EDITBOX_TYPE_SEACHFRIEND == index )
	{
		myeditbox->setText( "" );	
		UILabel* pTextLabel = dynamic_cast<UILabel*>(m_mainmapuilayer->seachfriendLayout->getChildByName("s_seachstring"));
		pTextLabel->setText( m_seachStr.c_str() );
	}
	else if (EDITBOX_TYPE_QQINFO == index )
	{
		myeditbox->setText( "" );	
		UILabel* pTextLabel = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("inputqq"));
		pTextLabel->setText( m_qqstr.c_str() );
	}
}

void MainMapUiLayer::editBoxTextChanged(cocos2d::extension::CCEditBox * myeditbox,const std::string&text)
{
	int index = myeditbox->getTag();
	if (EDITBOX_TYPE_CHANGERINFO == index)
	{
		m_Nicknamestr.clear();
		m_Nicknamestr = text;
	}
	else  if (EDITBOX_TYPE_FEEDBACK == index)
	{
		m_feedbackstr.clear();
		m_feedbackstr = text;
	}
	else if (EDITBOX_TYPE_SEACHFRIEND == index )
	{
		m_seachStr.clear();
		m_seachStr = text;		
	}
	else if (EDITBOX_TYPE_QQINFO == index )
	{
		m_qqstr.clear();
		m_qqstr = text;		
	}
}
void MainMapUiLayer::UpdateFriendRank()
{
	MsgMgr::sendGetSingleLevelResultInMap( AnalyseJson::logOnMsg.baseInfo.id, CandyManager::currentLevel );
}

void MainMapUiLayer::WidgitrunAction()
{
	switch( m_CurWidgetType )
	{
	case MAP_WIDGET_FRIEND_LIST:
		{
			setLoading( true );
			//单机修改
			//MsgMgr::sendGetFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id );
			//单机修改
		}
		break;
	case MAP_WIDGET_MESSAGE_LIST:
		{
			setLoading( true );
			CommonData::getMyMessage();
		}
		break;
	case MAP_WIDGET_NOFRIEND_LIST:
		//if ( !m_isNetNofriendMsg )
		//	setLoading( true );
		//sendInviteNofriendmsg();
		break;
	case MAP_WIDGET_SYSTEMTOOLS_DLG:
		m_isEnableKey = true;
		break;
	}
}

void MainMapUiLayer::CliamActionCB()
{
	m_mainmapuilayer->cliamsucLayout->setTouchEnabled( false );
	m_mainmapuilayer->cliamsucLayout->setVisible(false);

	MainMap::m_mainmap->DisplayMapUi();
}

void MainMapUiLayer::InviteFirendClose()
{
	m_mainmapuilayer->noFriendListLayout->setTouchEnabled( false );
	m_mainmapuilayer->noFriendListLayout->setVisible( false );

	MainMap::m_mainmap->DisplayMapUi();
}
void MainMapUiLayer::LevelInfoClose()
{
	m_mainmapuilayer->getWidgetUILayer()->removeWidget(m_mainmapuilayer->LevelInfoLayout);
}

void MainMapUiLayer::feedbackClose()
{
	m_mainmapuilayer->feedbacklayout->setTouchEnabled( false );
	m_mainmapuilayer->feedbacklayout->setVisible(false);
	m_isKey = false;
	MainMap::m_mainmap->DisplayMapUi();
}

void MainMapUiLayer::ReminderClose()
{
	m_mainmapuilayer->reminderLayout->setTouchEnabled( false );
	m_mainmapuilayer->reminderLayout->setVisible(false);
	MainMap::m_mainmap->DisplayMapUi();
}

// 
void MainMapUiLayer::BtnCallBackCloseBuyLife(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	QuitMapWidget();
}
void MainMapUiLayer::BtnCallBackForRewardUI(CCObject *pSender)
{
	UIButton *pBtn = dynamic_cast<UIButton *>(pSender);
	int tag = pBtn->getTag();
	switch(tag)
	{
	case 1:
		PlayEffect( MUSIC_ITEM_BUTTON_E );
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
		break;
	case 2:
		MsgMgr::sendRewardVip(AnalyseJson::logOnMsg.baseInfo.id);
		break;
	}
}
void MainMapUiLayer::updataMyInformtion(char* nickname,int qq)
{
	/*UILabel * pMyName = NULL;

	AnalyseJson::logOnMsg.baseInfo.nickName = nickname;
	AnalyseJson::logOnMsg.baseInfo.qq = CCString::createWithFormat("%d",qq)->getCString();
	pMyName = (UILabel*)MainMap::m_mainmap->m_pHeadbgImg->getChildByName("nickname");

	if ( pMyName )
		pMyName->setText( nickname );*/


	this->runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::UpdataMapHead)),
		NULL)
		);
}
void MainMapUiLayer::UpdataMapHead()
{
	if(MainMap::m_mainmap)
	{
		UIImageView* pMyHead = (UIImageView*)MainMap::m_mainmap->m_pHeadbgImg->getChildByName("myheadico");
		if(pMyHead == NULL)
			return;
		char* headname = (char*)CCString::createWithFormat("%s%d.png", AnalyseJson::CandPicPath,AnalyseJson::logOnMsg.baseInfo.id)->getCString();
		CCTextureCache::sharedTextureCache()->removeTextureForKey(headname);  


		if(!CCFileUtils::sharedFileUtils()->isFileExist(headname))
		{
			std::string headPath = CommonData::getHeadPathForUrl( AnalyseJson::logOnMsg.baseInfo.headPicUrl);
			pMyHead->setTexture(headPath.c_str());
		}
		else
		{
			pMyHead->setTexture(headname);
		}
	}
}

void MainMapUiLayer::UpdataDelayKey(float t)
{
	mDelayBackKey = true;
	this->unschedule( schedule_selector(MainMapUiLayer::UpdataDelayKey) );
}

void MainMapUiLayer::UpdataCountDown(float t)
{
	int nMin = m_CountDown/60;
	int nSec = m_CountDown%60;

	char* tempTime1 = NULL;
	if ( nMin/10 )
		tempTime1 = (char*)CCString::createWithFormat("%d", nMin)->getCString();
	else
		tempTime1 = (char*)CCString::createWithFormat("0%d", nMin)->getCString();

	char* tempTime2 = NULL;
	if ( nSec/10 )
		tempTime2 = (char*)CCString::createWithFormat("%d", nSec)->getCString();
	else
		tempTime2 = (char*)CCString::createWithFormat("0%d", nSec)->getCString();

	const char* pTime = CCString::createWithFormat("%s.%s", tempTime1, tempTime2 )->getCString();
	m_lifeTime->setVisible( true );
	m_lifeTime->setStringValue ( pTime );

	char *c_F1 = (char *)CCString::createWithFormat("%d", m_CountDown/60/10)->getCString();
	char *c_F2 = (char *)CCString::createWithFormat("%d", m_CountDown/60%10)->getCString();
	char *c_S1 = (char *)CCString::createWithFormat("%d", m_CountDown%60/10)->getCString();
	char *c_S2 = (char *)CCString::createWithFormat("%d", m_CountDown%60%10)->getCString();

	m_pAddLifeTips->setVisible( true );
	m_pFullLifeTips->setVisible( false );

	if ( !m_mainmapuilayer->widgetList.empty())
	{
		std::list<WidgetNode>::iterator p = m_mainmapuilayer->widgetList.begin();
		if ( MAP_WIDGET_LACKLIFE_DLG == p->type )
		{
			UILabelAtlas* pLabel1 = dynamic_cast<UILabelAtlas*>(p->widget->getChildByName("label_timefs"));
			UILabelAtlas* pLabel2 = dynamic_cast<UILabelAtlas*>(p->widget->getChildByName("label_timef"));
			UILabelAtlas* pLabel3 = dynamic_cast<UILabelAtlas*>(p->widget->getChildByName("label_timems"));
			UILabelAtlas* pLabel4 = dynamic_cast<UILabelAtlas*>(p->widget->getChildByName("label_timem"));

			pLabel1->setStringValue( c_F1 );
			pLabel2->setStringValue( c_F2 );
			pLabel3->setStringValue( c_S1 );
			pLabel4->setStringValue( c_S2 );

		}
	}

	m_CountDown--; 

	if ( 0 >= m_CountDown )
	{
		MsgMgr::sendAddSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
		this->unschedule( schedule_selector(MainMapUiLayer::UpdataCountDown) );
	}
}

void MainMapUiLayer::UpdateGlobeActionCB(float dt)
{

	UIImageView* pGlobe4 = dynamic_cast<UIImageView*>(globeLayout->getChildByName( "globe1_4_12" ));
	CCPoint PosAction = pGlobe4->getPosition();
	if ( ((PosAction.x >320 + 50)||(PosAction.x < 320 + 150))&& PosAction.y > 0 )
	{
		pGlobe4->setPosition( ccp(360, 0) );

		CCDelayTime *delay = CCDelayTime::create( /*0.25f*/0.25f );
		CCActionInterval* move = CCMoveTo::create(0.7f, PosAction);

		CCActionInterval* move_ease_inout1 = CCEaseElasticInOut::create( (CCActionInterval*)(move->copy()->autorelease()), 0.3f );
		CCActionInterval* move_ease_inout_back1 = move_ease_inout1->reverse();
		CCSequence* seq1 = CCSequence::create(move_ease_inout1, delay, move_ease_inout_back1, CCCA(delay), NULL);
		CCAction* action1 = CCRepeatForever::create(seq1);
		pGlobe4->runAction( action1 );
	}

	// test
	// 	for ( int i = 1; i < 20 ; i++)
	// 	{
	// 		char *StrAction  = (char *)CCString::createWithFormat("globe1_4_%d", i)->getCString();
	// 		UIImageView* pGlobe4 = dynamic_cast<UIImageView*>(globeLayout->getChildByName( StrAction ));
	// 		CCPoint PosAction = /*m_GlobeLay4[i];//*/pGlobe4->getPosition();
	// 		if ( ((PosAction.x >320 + 50)||(PosAction.x < 320 + 150))&& PosAction.y > 0 )
	// 		{
	// 			pGlobe4->setPosition( ccp(360, 0) );
	// 			pGlobe4->setVisible( true );
	// 
	// 			CCDelayTime *delay = CCDelayTime::create( /*0.25f*/0.25f );
	// 			CCActionInterval* move = CCMoveTo::create(0.7f, PosAction);
	// 
	// 			CCActionInterval* move_ease_inout1 = CCEaseElasticInOut::create( (CCActionInterval*)(move->copy()->autorelease()), 0.3f );
	// 			CCActionInterval* move_ease_inout_back1 = move_ease_inout1->reverse();
	// 			CCSequence* seq1 = CCSequence::create(move_ease_inout1, delay, move_ease_inout_back1, CCCA(delay), NULL);
	// 			CCAction* action1 = CCRepeatForever::create(seq1);
	// 			pGlobe4->runAction( action1 );
	// 		}
	// 
	// 		if ( PosAction.x < 0 || PosAction.y < 0)
	// 		{
	// 			//pGlobe4->setPosition( ccp(360, 0) );
	// 			pGlobe4->setVisible( false );
	// 		}
	// 
	// 	}addadfasdf

}

void MainMapUiLayer::updataFriendListTime(float t)
{
	if ( m_mainmapuilayer->friendListLayout )
	{
		std::list<UserFriendInfoStr>::iterator p = AnalyseJson::friendInfoMsg.friendInfo.begin();

		for(int i = 0; i< (int)AnalyseJson::friendInfoMsg.friendInfo.size(); i++, p++)
		{
			unsigned int time = p->countdown_timestamp- (p->cur_timestamp - p->click_timestamp);
			if ( 0 == p->click_timestamp )
				continue;

			char* pHourstr = (char*)CCString::createWithFormat("%dHour", p->id)->getCString();
			UILabelAtlas* pHour = (UILabelAtlas*)m_mainmapuilayer->friendListLayout->getChildByName(pHourstr);
			pHour->setVisible(true);

			char* pMinstr = (char*)CCString::createWithFormat("%dMin", p->id)->getCString();
			UILabelAtlas* pMin = (UILabelAtlas*)m_mainmapuilayer->friendListLayout->getChildByName(pMinstr);
			pMin->setVisible(true);

			char* pSecstr = (char*)CCString::createWithFormat("%dSec", p->id)->getCString();
			UILabelAtlas* pSec = (UILabelAtlas*)m_mainmapuilayer->friendListLayout->getChildByName(pSecstr);
			pSec->setVisible(true);

			char* tagName = (char *)CCString::createWithFormat("%dsign1",  p->id)->getCString();
			UIImageView* sign1 = (UIImageView*)m_mainmapuilayer->friendListLayout->getChildByName(tagName);
			sign1->setVisible(true);

			tagName =(char *)CCString::createWithFormat("%dsign2",  p->id)->getCString();
			UIImageView* sign2 = (UIImageView*)m_mainmapuilayer->friendListLayout->getChildByName(tagName);
			sign2->setVisible(true);

			int hour = getHourForSever(time);
			int minute = getMinuteForSever(hour,time);
			int secoud = getSecoudForSever(hour, minute, time);
			p->cur_timestamp++;

			char* tempTime = NULL;
			if ( hour/10 )
				tempTime = (char*)CCString::createWithFormat("%d", hour)->getCString();
			else
				tempTime = (char*)CCString::createWithFormat("0%d", hour)->getCString();
			pHour->setStringValue(tempTime);


			if ( minute/10 )
				tempTime = (char*)CCString::createWithFormat("%d", minute)->getCString();
			else
				tempTime = (char*)CCString::createWithFormat("0%d", minute)->getCString();
			pMin->setStringValue(tempTime);

			if ( secoud/10 )
				tempTime = (char*)CCString::createWithFormat("%d", secoud)->getCString();
			else
				tempTime = (char*)CCString::createWithFormat("0%d", secoud)->getCString();
			pSec->setStringValue(tempTime);

			// 			char *pHandselLife = (char *)CCString::createWithFormat( "HandselLife%d", p->id )->getCString();
			// 			UIButton* pHandselBtn = (UIButton*)m_mainmapuilayer->friendListLayout->getChildByName(pHandselLife);
			// 
			// 			pHandselBtn->disable(false);
		}
	}
}

void MainMapUiLayer::updataTaskDownTime(float t)
{
	bool nIsTime = false;
	if (MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout && AnalyseJson::taskTable.dailyTask.size())
	{
		UILabelAtlas* pLabelDatiyTimeTask1 = dynamic_cast<UILabelAtlas*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("LabelDatiyTimeTask1"));
		UILabelAtlas* pLabelDatiyTimeTask2 = dynamic_cast<UILabelAtlas*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("LabelDatiyTimeTask2"));

		std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();


		for ( int i = 1; i<=AnalyseJson::taskTable.dailyTask.size(); i++, item++)
		{
			const char* pLabelTagName = CCString::createWithFormat("LabelDatiyTimeTask%d", item->taskid)->getCString();
			UILabelAtlas* pLabelDatiyTimeTask = dynamic_cast<UILabelAtlas*>(MainMapUiLayer::m_mainmapuilayer->tasklayout->getChildByName( pLabelTagName ));
			int hour, minute , secoud ;
			unsigned int time = item->time;

			if ( time > 0)
			{
				hour = getHourForSever(time);
				minute = getMinuteForSever(hour,time);
				secoud = getSecoudForSever(hour, minute, time);

				char* pStrHour = NULL, *pStrminute = NULL, *pStrsecoud = NULL;

				if ( hour/10 )
					pStrHour = (char*)CCString::createWithFormat("%d", hour)->getCString();
				else
					pStrHour = (char*)CCString::createWithFormat("0%d", hour)->getCString();

				if ( minute/10 )
					pStrminute = (char*)CCString::createWithFormat("%d", minute)->getCString();
				else
					pStrminute = (char*)CCString::createWithFormat("0%d", minute)->getCString();

				if ( secoud/10 )
					pStrsecoud = (char*)CCString::createWithFormat("%d", secoud)->getCString();
				else
					pStrsecoud = (char*)CCString::createWithFormat("0%d", secoud)->getCString();

				const char* pTaskTime = CCString::createWithFormat("%s.%s.%s", pStrHour, pStrminute, pStrsecoud)->getCString();
				if (pLabelDatiyTimeTask)
					pLabelDatiyTimeTask->setStringValue(pTaskTime);
				nIsTime= true;
				item->time --;
			}
		}
	}

	if ( !nIsTime)
		this->unschedule( schedule_selector(MainMapUiLayer::updataTaskDownTime) );
}

int MainMapUiLayer::getHourForSever(unsigned int time)
{
	return time / ( 60 *60 );
}

int MainMapUiLayer::getMinuteForSever(int hour, unsigned int time)
{
	return (time - hour*60*60) / 60;
}

int MainMapUiLayer::getSecoudForSever(int hour, int min, unsigned int time)
{
	return time - hour* 60*60 - min *60;
}

// http加载loading界面  
void MainMapUiLayer::setLoading(bool state)
{
	if ( state )
	{
		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

		if ( NULL == m_mainmapuilayer->m_ploading)
		{
			m_mainmapuilayer->m_ploading = UIImageView::create();

			m_mainmapuilayer->m_ploading->setTexture( LOADING_PATH_IMGP );
			m_mainmapuilayer->m_ploading->setZOrder( 180 );
			m_mainmapuilayer->m_ploading->setScale( 0.5f );
			m_mainmapuilayer->m_ploading->setVisible( true );
			m_mainmapuilayer->m_ploading->setPosition( ccp(currentScreenWidth/2, currentScreenHeight/2) );
		}

		getWidgetUILayer()->addWidget( m_mainmapuilayer->m_ploading );
		CCActionInterval* rotate = CCRotateBy::create(1.0f, 360);
		CCActionInterval* rotate1 = CCRotateBy::create(2, 30);
		CCAction* action = CCRepeatForever::create(rotate);
		CCAction* copy = (CCAction*)(action->copy()->autorelease());
		m_mainmapuilayer->m_ploading->runAction( copy );

	}
	else
	{
		if ( m_mainmapuilayer->m_ploading )
		{
			//m_mainmapuilayer->m_ploading->stopAllActions();
			getWidgetUILayer()->removeWidgetAndCleanUp( m_mainmapuilayer->m_ploading ,true);
		}
		m_mainmapuilayer->m_ploading = NULL;
	}

}

void MainMapUiLayer::HttpGetAddSysLifeAsyn(bool state)
{
	char *lifenum = (char*)CCString::createWithFormat( "%d", AnalyseJson::addSysLifeMsg.totalLife )->getCString();
	m_plifeNum->setStringValue( lifenum );
	AnalyseJson::logOnMsg.lifeInfo.lifeNum = AnalyseJson::addSysLifeMsg.totalLife;

	CCLog("MainMapUiLayer::HttpGetAddSysLifeAsyn1 [%d]",AnalyseJson::addSysLifeMsg.flag);
	if ( 1 == AnalyseJson::addSysLifeMsg.flag )
	{
		MsgMgr::sendRemoveSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
		this->unschedule( schedule_selector(MainMapUiLayer::UpdataCountDown) );

		m_pAddLifeTips->setVisible( false );
		m_pFullLifeTips->setVisible( true );

		m_lifeTime->setVisible( false );
	}
	else
	{
		m_CountDown = AnalyseJson::addSysLifeMsg.lifeCountDown;
		this->schedule(schedule_selector(MainMapUiLayer::UpdataCountDown), 1, kCCRepeatForever, 0);
	}
	CCLog("MainMapUiLayer::HttpGetAddSysLifeAsyn2");
}


void MainMapUiLayer::HttpBuyLifeAsyn(bool state)
{
	AnalyseJson::logOnMsg.lifeInfo.lifeNum += AnalyseJson::buyLifeMsg.buyNum;
	char *lifenum = (char*)CCString::createWithFormat( "%d", AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();
	m_plifeNum->setStringValue( lifenum );

	char *Gemnum = (char*)CCString::createWithFormat( "%d", AnalyseJson::logOnMsg.baseInfo.gemNum )->getCString();
	//m_pGemNum->setStringValue( Gemnum );

	if ( 1 == AnalyseJson::buyLifeMsg.flag )
	{
		MsgMgr::sendRemoveSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
		this->unschedule( schedule_selector(MainMapUiLayer::UpdataCountDown) );
		m_pAddLifeTips->setVisible( false );
		m_pFullLifeTips->setVisible( true );
		m_lifeTime->setVisible( false );
	}
	MsgMgr::sendAddSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
}

// 同意索要
void MainMapUiLayer::HttpClaimedPropAcceptAsyn(bool state)
{
	AnalyseJson::acceptClaimedPropMsg;
	UpdataMessageList();
}

// 拒绝索要 
void MainMapUiLayer::HttpClaimedPropRefuseAsyn(bool state)
{
	UpdataMessageList();
}

void MainMapUiLayer::HttpAcceptPropAsyn(bool state)
{
	// 重新刷新消息列表
	UpdataMessageList();
}

// 重新刷新消息列表
void MainMapUiLayer::UpdataMessageList()
{
	AnalyseJson::acceptLifeMsg;
	if ( 1 == AnalyseJson::acceptLifeMsg.flag )
	{
		MsgMgr::sendRemoveSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
		m_pAddLifeTips->setVisible( false );
		m_pFullLifeTips->setVisible( true );
		m_lifeTime->setVisible( false );
	}

	// 
	addMessagetoList();
}

void MainMapUiLayer::UpdataPropNum()
{
	std::list<UserPropInfoStr>::iterator q;
	q = AnalyseJson::logOnMsg.propInfo.begin();

	for (int j = 1; j <= (int)AnalyseJson::logOnMsg.propInfo.size(); j++, q++)
	{
		char *pPropLabel= (char *)CCString::createWithFormat("prop%dnum", j)->getCString();
		UILabelAtlas *pPropNum = dynamic_cast<UILabelAtlas*>(friendInfoLayout->getChildByName(pPropLabel));
		char *pNum= (char *)CCString::createWithFormat("%d", q->num)->getCString();
		pPropNum->setStringValue( pNum );

		if ( 0 >= q->num )
		{
			char *pPropBut= (char *)CCString::createWithFormat("m_btn_%d_2", j)->getCString();
			UIButton *PropButton = dynamic_cast<UIButton*>(friendInfoLayout->getChildByName( pPropBut ));
			PropButton->disable( true );
		}
	}
}

void MainMapUiLayer::HttpGetConsumeLifeAsyn(bool state)
{
	AnalyseJson::consumeLifeMsg;
	char *lifenum = (char*)CCString::createWithFormat( "%d", AnalyseJson::consumeLifeMsg.totalLife )->getCString();
	m_plifeNum->setStringValue( lifenum );

	AnalyseJson::logOnMsg.lifeInfo.lifeNum = AnalyseJson::consumeLifeMsg.totalLife;

	// 生命倒计时
	if (AnalyseJson::consumeLifeMsg.totalLife < LILE_MAX_NUM)
	{
		AnalyseJson::logOnMsg.lifeInfo.lifeCountDown = AnalyseJson::consumeLifeMsg.lifeCountDown;
		m_CountDown = AnalyseJson::consumeLifeMsg.lifeCountDown;
		this->schedule(schedule_selector(MainMapUiLayer::UpdataCountDown), 1, kCCRepeatForever, 0);
		//MsgMgr::sendAddSysLifeMsg( AnalyseJson::friendInfoMsg.myId);
	}
}


void MainMapUiLayer::HttpHandselPropAsyn(bool state)
{
	AnalyseJson::handselPropInfo;
	std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();

	for (int i = 0; i < (int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
	{
		if (p->id == AnalyseJson::handselPropInfo.baseInfo.propId )
		{
			p->num -= AnalyseJson::handselPropInfo.baseInfo.propNum;
			break;
		}
	}

	UpdataPropNum();
}

void MainMapUiLayer::HttpClaimPropAsyn(bool state)
{

}

void MainMapUiLayer::HttpGetLifePriceAsyn(bool state)
{

}

void MainMapUiLayer::HttpAcceptLife(bool state)
{
	AnalyseJson::acceptLifeMsg;
	char *lifenum = (char*)CCString::createWithFormat( "%d", AnalyseJson::acceptLifeMsg.totalLife )->getCString();
	m_plifeNum->setStringValue( lifenum );

	AnalyseJson::logOnMsg.lifeInfo.lifeNum = AnalyseJson::acceptLifeMsg.totalLife;
	if ( 1 == AnalyseJson::acceptLifeMsg.flag)
	{
		this->unschedule( schedule_selector(MainMapUiLayer::UpdataCountDown) );
		m_pAddLifeTips->setVisible( false );
		m_pFullLifeTips->setVisible( true );
		m_lifeTime->setVisible( false );
	}
	addMessagetoList();
}

void MainMapUiLayer::HttpHandselLife(bool state)
{
	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(friendListLayout->getChildByName( "m_sv_friendlist" ));
	char *pHandselLifeBut = (char *)CCString::createWithFormat( "HandselLife%d", AnalyseJson::handselLifeMsg.friendId )->getCString();
	char *pHandselLifeStr = (char *)CCString::createWithFormat( "HandselLifeStr%d",  AnalyseJson::handselLifeMsg.friendId )->getCString();

	UIButton* pHandselFriendBut = dynamic_cast<UIButton*>(pFriendlistView->getChildByName( pHandselLifeBut ));
	pHandselFriendBut->disable( true );

}
// 获得历史消息
void MainMapUiLayer::HttpGetChatRecordAsyn(bool state)
{
	addHistoryMsgtoList();
	CCLog( "MainMapUiLayer HttpGetChatRecordAsyn==> state :[%d]",  state);
}


// 获得赠送道具信息回调
void MainMapUiLayer::HttpGetHandselPropAsyn(bool state)
{
	int nMsgLen = AnalyseJson::handselPropMsg.handselStageProp.size();//getHandselMsg.handselMsg.size();

	std::list<UserGetHandselPropMsg>::iterator p;
	p = AnalyseJson::handselPropMsg.handselStageProp.begin();
	MessageNode node;

	for (int i = 0; i<nMsgLen; i++)
	{
		node.m_orderid = p->handselId;
		node.m_friendid = p->friendId;
		node.m_propid = p->propId;
		node.m_propnum = p->propNum;
		node.m_propname = p->propName;
		node.m_sex = p->gender;
		node.m_isAccept = false;
		node.m_friendname = p->nickName;
		node.m_headurl = p->headPicUrl;
		node.m_time = p->diffTime;
		node.m_type = MESSAGE_TYPE_HANDSEPROP;

		m_mainmapuilayer->m_messagelist.push_back(node);
		p++;
	}

	MsgMgr::sendGetClaimedPropMsg( AnalyseJson::logOnMsg.baseInfo.id );
	CCLog( "MainMapUiLayer HttpGetHandselPropAsyn==> state :[%d]",  state);
}

void MainMapUiLayer::HttpGetMyMessageAsyn( bool state /*= true*/ )
{
	int nMsgLen = 0;

	m_mainmapuilayer->m_messagelist.clear();
	nMsgLen = AnalyseJson::InviteFriendMsgList.nofriend.size();
	std::list<UserNoFriendInfoStr>::iterator item1 = AnalyseJson::InviteFriendMsgList.nofriend.begin();

	for (int i = 0; i<nMsgLen; i++)
	{
		MessageNode node = {0};
		node.m_friendid = item1->id;
		node.m_sex = item1->gender;
		node.m_isAccept = false;
		node.m_friendname = item1->nickName;
		node.m_headurl = item1->headPicUr;
		node.m_adate = item1->adate;
		node.m_type = MESSAGE_TYPE_INVATEFRIEND;
		m_mainmapuilayer->m_messagelist.push_back(node);
		item1++;
	}

	nMsgLen = AnalyseJson::getHandselMsg.handselMsg.size();
	std::list<UserGetHandselMsg>::iterator item = AnalyseJson::getHandselMsg.handselMsg.begin();
	AnalyseJson::handselLifeMsg;

	for (int i = 0; i<nMsgLen; i++)
	{
		MessageNode node;
		node.m_orderid = item->handselId;
		node.m_friendid = item->friendId;
		node.m_propid = item->lifeId;
		node.m_propnum = item->lifeNum;
		node.m_propname = item->lifeName;
		node.m_sex = item->gender;
		node.m_isAccept = false;
		node.m_headurl = item->headPicUrl;
		node.m_friendname = item->nickName;
		node.m_time = item->diff_time;
		node.m_type = MESSAGE_TYPE_HANDSELEFT;
		item++;

		m_mainmapuilayer->m_messagelist.push_back(node);
	}

	if ( m_mainmapuilayer->messageListLayout )
		addMessagetoList();
	
	if ( m_mainmapuilayer->m_messagelist.empty() )
	{
		//m_mainmapuilayer->m_messagetips->setVisible( false );
	}
		
	else
	{	
		static bool nIsShowMsgPropmt = true;
		//m_mainmapuilayer->m_messagetips->setVisible( true );
		//m_mainmapuilayer->m_MessageBut->setVisible( true );
		//m_mainmapuilayer->m_MessageBut->stopAllActions();
		//m_mainmapuilayer->m_MessageBut->runAction( getTaskMsgTipsAction() );	
		if (  getMessagePropmtStatus() && nIsShowMsgPropmt)
		{
			//createLeftImgPrompt(m_mainmapuilayer->m_MessageBut->getPosition(), m_mainmapuilayer->m_MessageBut->getName() );
			nIsShowMsgPropmt = false;
		}
	}

	CCLog( "MainMapUiLayer tInviteFriendmsg==>  msg_len:[%d]",  m_mainmapuilayer->m_messagelist.size());
}

// 获得索要道具信息回
void MainMapUiLayer::HttpGetClaimedPropAsyn(bool state)
{
	int nMsgLen = AnalyseJson::getClaimedPropMsg.msg.size();

	std::list<UserGetClaimedPropMsg>::iterator p;
	p = AnalyseJson::getClaimedPropMsg.msg.begin();
	MessageNode node;

	for (int i = 0; i<nMsgLen; i++)
	{
		node.m_orderid = p->acceptId;
		node.m_friendid = p->friendId;
		node.m_propid = p->propId;
		node.m_propnum = p->propNum;
		node.m_propname = p->propName;
		node.m_sex = p->gender;
		node.m_isAccept = false;
		node.m_friendname = p->nickName;
		node.m_headurl = p->headPicUrl;
		node.m_type = MESSAGE_TYPE_CLAIMEDPROP;
		node.m_time = p->diff_time;
		m_mainmapuilayer->m_messagelist.push_back(node);
		p++;
	}
	if ( m_mainmapuilayer->messageListLayout )
	{
		addMessagetoList();
	}
	CCLog( "MainMapUiLayer HttpGetClaimedPropAsyn==> state :[%d]",  state);
}


void MainMapUiLayer::HttpGetInviteFriendmsgAsyn(bool state )
{
	int nMsgLen = AnalyseJson::InviteFriendMsgList.nofriend.size();

	std::list<UserNoFriendInfoStr>::iterator p = AnalyseJson::InviteFriendMsgList.nofriend.begin();

	for (int i = 0; i<nMsgLen; i++)
	{
		MessageNode node = {0};
		node.m_friendid = p->id;
		node.m_sex = p->gender;
		node.m_isAccept = false;
		node.m_friendname = p->nickName;
		node.m_headurl = p->headPicUr;
		node.m_adate = p->adate;
		node.m_type = MESSAGE_TYPE_INVATEFRIEND;
		m_mainmapuilayer->m_messagelist.push_back(node);
		p++;
	}

	if ( m_mainmapuilayer->messageListLayout )
	{
		addMessagetoList();
	}

	if ( m_mainmapuilayer->m_messagelist.empty() )
	{
		//m_messagetips->setVisible( false );
	}
	else
	{	
		//m_messagetips->setVisible( true );
		//m_MessageBut->stopAllActions();
		//m_MessageBut->runAction( getTaskMsgTipsAction() );	
	}

	CCLog( "MainMapUiLayer tInviteFriendmsg==>  msg_len:[%d]",  m_mainmapuilayer->m_messagelist.size());
}


// 获得赠送生命信息回调
void MainMapUiLayer::HttpGetHandselLifeAsyn(bool state)
{
	int nMsgLen = AnalyseJson::getHandselMsg.handselMsg.size();

	std::list<UserGetHandselMsg>::iterator p;
	p = AnalyseJson::getHandselMsg.handselMsg.begin();
	AnalyseJson::handselLifeMsg;
	MessageNode node;

	for (int i = 0; i<nMsgLen; i++)
	{
		node.m_orderid = p->handselId;
		node.m_friendid = p->friendId;
		node.m_propid = p->lifeId;
		node.m_propnum = p->lifeNum;
		node.m_propname = p->lifeName;
		node.m_sex = p->gender;
		node.m_isAccept = false;
		node.m_headurl = p->headPicUrl;
		node.m_friendname = p->nickName;
		node.m_time = p->diff_time;
		node.m_type = MESSAGE_TYPE_HANDSELEFT;

		p++;

		m_mainmapuilayer->m_messagelist.push_back(node);
	}

	if ( m_mainmapuilayer->messageListLayout )
	{
		addMessagetoList();
	}

	if ( m_mainmapuilayer->m_messagelist.empty() )
	{
		//m_mainmapuilayer->m_messagetips->setVisible( false );
	}
		
	else
	{	
		//m_mainmapuilayer->m_messagetips->setVisible( true );
		//m_mainmapuilayer->m_MessageBut->stopAllActions();
		//m_mainmapuilayer->m_MessageBut->runAction( getTaskMsgTipsAction() );	
	}

	CCLog( "MainMapUiLayer tInviteFriendmsg==>  msg_len:[%d]",  m_mainmapuilayer->m_messagelist.size());
}

void MainMapUiLayer::addNofriendtoList(void)
{
	UIScrollView* pNoFriendlistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->noFriendListLayout->getChildByName( "m_sv_nofriend" ));
	CCSize scrollSize = pNoFriendlistView->getContentSize();
	pNoFriendlistView->removeAllChildrenAndCleanUp(true);
	int nNoFriendLen = AnalyseJson::nofriendInfoMsg.nofriend.size();
	CCSize itemPoint;

	if ( nNoFriendLen >= 5 )
		nNoFriendLen = 5;	

	if ( 0 < nNoFriendLen || m_isNetNofriendMsg )
		setLoading( false );

	UIButton *pnextpagbtn = dynamic_cast<UIButton*>(m_mainmapuilayer->noFriendListLayout->getChildByName("m_btn_nextpag"));
	if ( 0 == nNoFriendLen )
	{
		pnextpagbtn->disable();

		UIImageView* pNoMsg = UIImageView::create();
		pNoFriendlistView->addChild( pNoMsg );
		pNoMsg->setTexture( MSG_IMG_NOTHING );
		pNoMsg->setVisible( true );
		pNoMsg->setPosition(ccp( 300, 323 ));

		UIImageView* pStrMsg = UIImageView::create();
		pNoFriendlistView->addChild( pStrMsg );
		pStrMsg->setTexture( MSG_STR_NOFRIEND );
		pStrMsg->setVisible( true );
		pStrMsg->setPosition(ccp( 300, 178 ));

	}
	else
	{
		pnextpagbtn->active();
	}

	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<UserNoFriendInfoStr>::iterator p;
	p = AnalyseJson::nofriendInfoMsg.nofriend.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nNoFriendLen * ( 116 + 8 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pNoFriendlistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pNoFriendlistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 116/2;

	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;
	CCLog( "addNofriendtoList nNoFriendLen:%d", nNoFriendLen);

	for (int i = 0; i<nNoFriendLen; i++)
	{
		// m_friendlist
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(620, 126));
		pItemImg->setVisible( true );
		pItemImg->setTouchEnabled( true );
		pItemImg->setTag( i );
		pItemImg->setName( p->idx.c_str() );
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 116 + 15 );
		pNoFriendlistView->addChild( pItemImg );


		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setVisible( true );
		pHeadbgImg->setTouchEnable( true );
		pHeadbgImg->setPosition(ccp(-223, 0));
		pItemImg->addChild( pHeadbgImg);

		float nScale = 0;
		std::string headPath = CommonData::getHeadPathForUrl( p->headPicUr );
		UIImageView* pHeadImg = UIImageView::create();
		pHeadImg->setTexture( headPath.c_str() );
		nScale = PIC_HEAD_W/pHeadImg->getSize().width;
		pHeadImg->setScale( nScale );
		pHeadImg->setVisible( true );
		pHeadImg->setPosition(ccp(-223, -5));
		pItemImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setVisible( true );
		pHeadKImg->setScale( 1.1f );
		pHeadKImg->setPosition(ccp(-223, -5));
		pItemImg->addChild( pHeadKImg);

		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(-177, -40));
		pItemImg->addChild( pSexbgImg);

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-130, 0) );
		pName->setColor( ccc3(255,255,255));
		pName->setFontSize(40);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)p->nickName.c_str() );
		pName->setVisible( true );
		pItemImg->addChild( pName );

		UIButton* pAddFriendBtn = UIButton::create();
		pAddFriendBtn->setNormalTexture( "Image/MainMapUi/btn_addfriendN.png" );
		pAddFriendBtn->setPressedTexture( "Image/MainMapUi/btn_addfriendP.png" );
		pAddFriendBtn->setDisabledTexture ( "Image/MainMapUi/btn_addfriendP.png" );
		char *pHandselLifeBut = (char *)CCString::createWithFormat( "addfriend%d", p->id )->getCString();
		pAddFriendBtn->setName( pHandselLifeBut );
		pAddFriendBtn->setTag( INVITEFRIEND_FOR_RECOMMEND );
		pAddFriendBtn->setTouchEnable( true );
		pAddFriendBtn->setVisible( true );
		pAddFriendBtn->isEffects( true, nDelayTime1 + nDelayTime2*i );
		pAddFriendBtn->setPosition(ccp(249, 5));
		pAddFriendBtn->data = (void*)p->id;
		pAddFriendBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::InviteButCallBack)); 
		pItemImg->addChild( pAddFriendBtn );

		if ( (int)AnalyseJson::friendInfoMsg.friendMaxNum <= (int)AnalyseJson::friendInfoMsg.friendInfo.size() )
			pAddFriendBtn->disable(true);


		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setVisible( true );
		pDivideline->setPosition(ccp(0, -63));
		pItemImg->addChild( pDivideline);

		p++;
	}
}

// 添加好友到好友列表
void MainMapUiLayer::addFriendtoList( void )
{
	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->friendListLayout->getChildByName( "m_sv_friendlist" ));
	CCSize scrollSize = pFriendlistView->getContentSize();
	pFriendlistView->removeAllChildrenAndCleanUp( true );
	int nFriendLen = AnalyseJson::friendInfoMsg.friendInfo.size();//m_friendlist.size();
	CCSize itemPoint;

	AnalyseJson::friendInfoMsg.friendInfo.sort(Cmpare());
	// 计算出scrollView的高
	float ClipWidth = 0; 
	float ClipHeight = 0;
	int sex = 0;
	std::list<UserFriendInfoStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();

	ClipWidth = scrollSize.width;
	if ( nFriendLen )
		ClipHeight = ( nFriendLen ) * ( 112 + 20 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pFriendlistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pFriendlistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 112/2-10;


	if ( 0== nFriendLen)
	{
		UIImageView* pnothing = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "img_nothing" ));
		UIImageView* pnofriendstr = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "str_nofriendtips" ));
		pnothing->setVisible( true );
		pnofriendstr->setVisible( true );
	}
	else
	{
		UIImageView* pnothing = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "img_nothing" ));
		UIImageView* pnofriendstr = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendListLayout->getChildByName( "str_nofriendtips" ));
		pnothing->setVisible( false );
		pnofriendstr->setVisible( false );

	}
	setLoading( false );

	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;


	if ( !nFriendLen )
		return;

	for (int i = 0; i<nFriendLen; i++)
	{
		// m_friendlist
		const char* pItemName = CCString::createWithFormat("FriendItem%d", p->id )->getCString();
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setName( pItemName );
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(550, 112));
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 112 + 20 );
		pFriendlistView->addChild( pItemImg );

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setTouchEnable( true );
		pHeadbgImg->setPosition(ccp(-226, 0));
		pHeadbgImg->setTag( p->id );
		pItemImg->addChild( pHeadbgImg);

		float nScale = 0.0f;
		std::string headPath = CommonData::getHeadPathForUrl( p->headPicUr );
		UIImageView* pHeadImg = UIImageView::create();	
		pHeadImg->setTexture( headPath.c_str() );	
		nScale = PIC_HEAD_W/pHeadImg->getSize().width;
		//pHeadImg->setScale( nScale );
		pHeadImg->setPosition(ccp(0, 2));
		pHeadbgImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setPosition(ccp(0, 0));
		pHeadbgImg->addChild( pHeadKImg);

		// vip 皇冠
		if ( 0 != p->isvip )
		{
			UIImageView* pVipImg = UIImageView::create();
			pVipImg->setTexture( "Image/BigMap_1/ImgVipTips.png" );
			pVipImg->setZOrder( 7 );
			pVipImg->setPosition(ccp(0, 55));
			pHeadbgImg->addChild( pVipImg);
		}
		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(44, -37));
		pHeadbgImg->addChild( pSexbgImg);

		UILabel* pNameBg = UILabel::create();
		pNameBg->setPosition( ccp(-146, -19) );
		pNameBg->setColor( ccc3(100,100,100));
		pNameBg->setFontSize(35);
		pNameBg->setAnchorPoint( ccp(0.0f, 0.5f));
		pNameBg->setText( (const char *)p->nickName.c_str() );
		pItemImg->addChild( pNameBg );	

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-147, -18) );
		pName->setColor( ccc3(255,255,255));
		pName->setFontSize(35);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)p->nickName.c_str() );
		pItemImg->addChild( pName );

		UILabel* plevel = UILabel::create();
		std::string levelstr = CommonData::GetString( "app_friendlevel_str" );
		plevel->setPosition( ccp(-145, 24) );
		plevel->setColor( ccc3(107,53,27));
		plevel->setFontSize(30);
		plevel->setAnchorPoint( ccp(0.0f, 0.5f));
		plevel->setText( CCString::createWithFormat( levelstr.c_str(), p->level)->getCString());
		pItemImg->addChild( plevel );

		int offset = 50;

		UIButton* pSloveImg = UIButton::create();
		pSloveImg->setNormalTexture(  "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
		pSloveImg->setPressedTexture(  "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
		pSloveImg->setDisabledTexture (  "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
		char *pHandselLifeBut = (char *)CCString::createWithFormat( "HandselLife%d", p->id )->getCString();
		pSloveImg->setName( pHandselLifeBut );
		pSloveImg->setTag( p->id );
		pSloveImg->setTouchEnable( true );
		pSloveImg->isEffects( true, nDelayTime1 + nDelayTime2*i );
		pSloveImg->setPosition(ccp(249 - offset, 5));
		pSloveImg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackFriendList)); 
		pItemImg->addChild( pSloveImg );

		UIButton* pDelFriendBtn = UIButton::create();
		pDelFriendBtn->setNormalTexture( "Image/MainMapUi/DelFriendBtnN.png" );
		pDelFriendBtn->setPressedTexture( "Image/MainMapUi/DelFriendBtnP.png" );
		pDelFriendBtn->setDisabledTexture ( "Image/MainMapUi/DelFriendBtnP.png" );
		pDelFriendBtn->setName( pHandselLifeBut );
		pDelFriendBtn->setTag( p->id );
		pDelFriendBtn->setTouchEnable( true );
		pDelFriendBtn->isEffects( true, nDelayTime1 + nDelayTime2*i );
		pDelFriendBtn->setPosition(ccp(270 , 25));
		pDelFriendBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackDelFriend)); 
		pItemImg->addChild( pDelFriendBtn );

		// 已赠送
		if ( 0 < p->click_timestamp )
		{
			pSloveImg->disable( true );

			UILabel* pTime = UILabel::create();
			// pTime->setTag( 2*10+i ); //赠送
			char *pHandselLifeStr = (char *)CCString::createWithFormat( "HandselLifeStr%d", p->id )->getCString();
			pSloveImg->setName( pHandselLifeStr );
			pTime->setColor( ccc3(255,255,255));
			pTime->setFontSize(20);
			pTime->setAnchorPoint( ccp(0.5f, 0.5f));
			pTime->setText( CommonData::GetString( "app_handselover_str" ).c_str() );
			//pSloveImg->addChild( pTime );

		}

		UILabelAtlas* ptimeS = UILabelAtlas::create();
		char *tagNum= (char *)CCString::createWithFormat("%dHour",  p->id)->getCString();
		ptimeS->setVisible(false);
		ptimeS->setName( tagNum );
		ptimeS->setProperty("0" , "Image/MainMapUi/buyItem/timestr_lifetime.png",16, 26, "0");  
		ptimeS->setPosition( ccp(192 - offset, -44));
		pItemImg->addChild( ptimeS );

		UILabelAtlas* ptimef = UILabelAtlas::create();
		tagNum= (char *)CCString::createWithFormat("%dMin",  p->id)->getCString();
		ptimef->setVisible(false);
		ptimef->setName( tagNum );
		ptimef->setProperty("0" , "Image/MainMapUi/buyItem/timestr_lifetime.png",16, 26, "0");  
		ptimef->setPosition( ccp(234 - offset, -44));
		pItemImg->addChild( ptimef );

		UILabelAtlas* ptimeM = UILabelAtlas::create();
		tagNum = (char *)CCString::createWithFormat("%dSec",  p->id)->getCString();
		ptimeM->setProperty("0" , "Image/MainMapUi/buyItem/timestr_lifetime.png",16, 26, "0"); 
		ptimeM->setVisible(false);
		ptimeM->setName( tagNum ); 
		ptimeM->setPosition( ccp(276 - offset, -44));
		pItemImg->addChild( ptimeM );

		UIImageView* psign1 = UIImageView::create();
		tagNum = (char *)CCString::createWithFormat("%dsign1",  p->id)->getCString();
		psign1->setTexture( "Image/MainMapUi/buyItem/img_timesign.png" );
		psign1->setName(tagNum);
		psign1->setVisible(false);
		psign1->setPosition(ccp(213 - offset, -44));
		pItemImg->addChild( psign1);

		UIImageView* psign2 = UIImageView::create();
		tagNum = (char *)CCString::createWithFormat("%dsign2",  p->id)->getCString();
		psign2->setTexture( "Image/MainMapUi/buyItem/img_timesign.png" );
		psign2->setName(tagNum);
		psign2->setVisible(false);
		psign2->setPosition(ccp(254 - offset, -44));
		pItemImg->addChild( psign2);

		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setPosition(ccp(0, -62));
		pItemImg->addChild( pDivideline);
		p ++;
	}

	std::list<UserPropInfoStr>::iterator item = AnalyseJson::logOnMsg.specialProp.begin();
	while ( item!=AnalyseJson::logOnMsg.specialProp.end()) 
	{
		if (item->id == CANDY_PROP_FRIEND_LIMIT )
		{
			UIImageView* pItemImg = UIImageView::create();
			pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
			pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
			pFriendlistView->addChild( pItemImg );

			UIImageView* pDivideline = UIImageView::create();
			pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
			pDivideline->setPosition(ccp(0, -62));
			pItemImg->addChild( pDivideline);

			UILabel* pStrBuyFriend = UILabel::create();
			pStrBuyFriend->setColor( ccc3(255,255,255));
			pStrBuyFriend->setFontSize(40);
			//pStrBuyFriend->setFontName("黑体");
			pStrBuyFriend->setPosition( ccp(-150, 0));
			pStrBuyFriend->setText( item->name.c_str() );
			pItemImg->addChild( pStrBuyFriend );

			UILabelAtlas* AtlevelNum1 = UILabelAtlas::create();
			AtlevelNum1->setVisible( true );
			AtlevelNum1->setProperty(item->price.c_str() , "Image/MainMapUi/buyItem/gem_price_str.png",29, 40, "0");  
			AtlevelNum1->setPosition( ccp(50, 0));
			pItemImg->addChild( AtlevelNum1 );

			UIImageView* pGemImg = UIImageView::create();
			pGemImg->setTexture( "Image/MainMapUi/buyItem/map_gamico.png" );
			pGemImg->setPosition( ccp(100 , 0) );
			pItemImg->addChild( pGemImg );

			UIButton* pBuyFriendBtn = UIButton::create();
			pBuyFriendBtn->setNormalTexture( "Image/MainMapUi/BtnAddFriendN.png" );
			pBuyFriendBtn->setPressedTexture( "Image/MainMapUi/BtnAddFriendP.png" );
			pBuyFriendBtn->setDisabledTexture ( "Image/MainMapUi/BtnAddFriendP.png" );
			pBuyFriendBtn->setTouchEnable( true );
			pBuyFriendBtn->isEffects( true );
			pBuyFriendBtn->setPosition(ccp(220 , 0));
			pBuyFriendBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackBuyFriendLimit)); 
			pItemImg->addChild( pBuyFriendBtn );

			UIWidget *pwidgt = pFriendlistView->getInnerContainer();
			CCPoint pos = pwidgt->getPosition();
			pwidgt->setPosition( ccp(0,0));

			break;
		}
		item++;
	}

	schedule( schedule_selector(MainMapUiLayer::updataFriendListTime), 1, kCCRepeatForever, 0 );

}

void MainMapUiLayer::addSeachFriendTolist(void)
{
	UIScrollView* pListView  = dynamic_cast<UIScrollView*> (m_mainmapuilayer->seachfriendLayout->getChildByName("m_sv_list"));
	CCSize scrollSize = pListView->getContentSize();
	pListView->removeAllChildrenAndCleanUp(true);
	int nListLen = AnalyseJson::SeachFriendList.nofriend.size();
	CCSize itemPoint;

	if ( 0 == nListLen )
	{
		UIImageView* pSeachIco  = dynamic_cast<UIImageView*> (m_mainmapuilayer->seachfriendLayout->getChildByName("img_seachico"));
		pSeachIco->setVisible(true);

		UILabel* pNothing = dynamic_cast<UILabel*>(m_mainmapuilayer->seachfriendLayout->getChildByName("LabelNoting"));
		pNothing->setVisible( true );

		CCActionInterval * fadein = CCFadeIn::create(2);
		CCActionInterval * fadeout = CCFadeOut::create(2);
		pNothing->runAction(CCSequence::create(
			CCFadeIn::create(0.2f),
			CCDelayTime::create(1.0f),
			CCFadeOut::create(0.2f),
			NULL));

	}
	else
	{
		UIImageView* pSeachIco  = dynamic_cast<UIImageView*> (m_mainmapuilayer->seachfriendLayout->getChildByName("img_seachico"));
		pSeachIco->setVisible(false);
	}

	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<UserNoFriendInfoStr>::iterator p = AnalyseJson::SeachFriendList.nofriend.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nListLen * ( 116 + 8 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pListView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pListView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 116/2;

	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;
	CCLog( "addNofriendtoList nNoFriendLen:%d", nListLen);

	for (int i = 0; i<nListLen; i++)
	{
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(620, 126));
		pItemImg->setVisible( true );
		pItemImg->setTouchEnabled( true );
		pItemImg->setTag( i );
		pItemImg->setName( p->idx.c_str() );
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 116 + 15 );
		pListView->addChild( pItemImg );

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setVisible( true );
		pHeadbgImg->setTouchEnable( true );
		pHeadbgImg->setPosition(ccp(-223, 0));
		pItemImg->addChild( pHeadbgImg);

		float nScale = 0;
		std::string headPath = CommonData::getHeadPathForUrl( p->headPicUr );
		UIImageView* pHeadImg = UIImageView::create();
		pHeadImg->setTexture( headPath.c_str() );
		nScale = PIC_HEAD_W/pHeadImg->getSize().width;
		//pHeadImg->setScale( nScale );
		pHeadImg->setVisible( true );
		pHeadImg->setPosition(ccp(-223, 0));
		pItemImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setVisible( true );
		pHeadKImg->setPosition(ccp(-223, 0));
		pItemImg->addChild( pHeadKImg);

		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(-177, -40));
		pItemImg->addChild( pSexbgImg);

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-130, 0) );
		pName->setColor( ccc3(255,255,255));
		pName->setFontSize(40);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)p->nickName.c_str() );
		pName->setVisible( true );
		pItemImg->addChild( pName );

		if ( !p->isfriend )
		{
			UIButton* pAddFriendBtn = UIButton::create();
			pAddFriendBtn->setNormalTexture( "Image/MainMapUi/btn_addfriendN.png" );
			pAddFriendBtn->setPressedTexture( "Image/MainMapUi/btn_addfriendP.png" );
			pAddFriendBtn->setDisabledTexture ( "Image/MainMapUi/btn_addfriendP.png" );
			char *pHandselLifeBut = (char *)CCString::createWithFormat( "addfriend%d", p->id )->getCString();
			pAddFriendBtn->setName( pHandselLifeBut );
			pAddFriendBtn->setTag( INVITEFRIEND_FOR_SEACH );
			pAddFriendBtn->setTouchEnable( true );
			pAddFriendBtn->setVisible( true );
			pAddFriendBtn->isEffects( true, nDelayTime1 + nDelayTime2*i );
			pAddFriendBtn->setPosition(ccp(249, 5));
			pAddFriendBtn->data = (void*)p->id;
			pAddFriendBtn->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::InviteButCallBack)); 
			pItemImg->addChild( pAddFriendBtn );

			if ( (int)AnalyseJson::friendInfoMsg.friendMaxNum <= (int)AnalyseJson::friendInfoMsg.friendInfo.size() )
				pAddFriendBtn->disable(true);

		}


		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setVisible( true );
		pDivideline->setPosition(ccp(0, -63));
		pItemImg->addChild( pDivideline);

		p++;
	}
}

void MainMapUiLayer::addFriendtoClaimList(void)
{
	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->CliamLifelayout->getChildByName( "m_sv_friend" ));
	CCSize scrollSize = pFriendlistView->getContentSize();
	pFriendlistView->removeAllChildrenAndCleanUp( true );
	int nFriendLen = AnalyseJson::friendInfoMsg.friendInfo.size();//m_friendlist.size();
	CCSize itemPoint;

	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<UserFriendInfoStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nFriendLen * ( 126 + 15 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pFriendlistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pFriendlistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 126/2;


	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;

	for (int i = 0; i<nFriendLen; i++)
	{
		// m_friendlist
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/m_itembg.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(550, 126));
		pItemImg->setVisible( true );
		pItemImg->setTouchEnabled( true );
		pItemImg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::ItemCallBackCliamList));
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 126 + 15 );
		pFriendlistView->addChild( pItemImg );

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setVisible( true );
		pHeadbgImg->setTouchEnable( true );
		pHeadbgImg->setPosition(ccp(-203, 0));
		pHeadbgImg->setTag( p->id );
		pItemImg->addChild( pHeadbgImg);

		UIImageView* pHeadImg = UIImageView::create();
		float nScale = 0;
		char UrlName[128]= {0};
		HeadDownMgr::getHeadNameForUrl(p->headPicUr, UrlName);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		char *HeadName = (char *)CCString::createWithFormat("%s.png",UrlName)->getCString();
		char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, HeadName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		char *headPath= (char *)CCString::createWithFormat("Image/wemepci/%s.png", UrlName)->getCString();
#endif
		pHeadImg->setTexture( headPath );
		nScale = PIC_HEAD_W/pHeadImg->getSize().width;
		pHeadImg->setScale( nScale );
		pHeadImg->setVisible( true );
		pHeadImg->setPosition(ccp(-203, 0));
		pItemImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/m_img_headK.png" );
		pHeadKImg->setVisible( true );
		pHeadKImg->setPosition(ccp(-203, 0));
		pItemImg->addChild( pHeadKImg);


		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(-157, -47));
		pItemImg->addChild( pSexbgImg);

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-130, 0) );
		pName->setColor( ccc3(0,0,0));
		pName->setFontSize(30);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)p->nickName.c_str() );
		pName->setVisible( true );
		pItemImg->addChild( pName );

		UIImageView* pSelKImg = UIImageView::create();
		pSelKImg->setTexture( "Image/MainMapUi/m_img_selectK.png" );
		pSelKImg->setVisible( true );
		pSelKImg->setPosition(ccp(187, 0));
		pSelKImg->setTag( i );
		pSelKImg->setName( p->idx.c_str() );
		pItemImg->addChild( pSelKImg);

		UIImageView* pSelImg = UIImageView::create();
		pSelImg->setTexture( "Image/MainMapUi/m_img_select.png" );
		pSelImg->setName("Select");
		pSelImg->setPosition(ccp(0, 0));
		pSelImg->setVisible(false);
		pSelKImg->addChild( pSelImg);
		p ++;
	}
}

// 添加消息列表
void MainMapUiLayer::addMessagetoList(void)
{
	UIScrollView* pMessagelistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	CCSize scrollSize = pMessagelistView->getContentSize();
	pMessagelistView->removeAllChildrenAndCleanUp( true );
	int nMessageLen, nNoDispMsg = 0;
	nMessageLen  = m_mainmapuilayer->m_messagelist.size();
	CCSize itemPoint;
	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<MessageNode>::iterator p = m_mainmapuilayer->m_messagelist.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nMessageLen * ( 116 + 15 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pMessagelistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pMessagelistView->setTouchEnabled( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 116/2;

	setLoading( false );
	if ( 0 == nMessageLen )
	{
		UIImageView* pNoMsg = UIImageView::create();
		pNoMsg->setTexture( MSG_IMG_NOTHING );
		pNoMsg->setVisible( true );
		pNoMsg->setPosition(ccp( 300, 380 ));
		pMessagelistView->addChild( pNoMsg );

		UIImageView* pStrMsg = UIImageView::create();
		pStrMsg->setTexture( MSG_STR_NOMSG );
		pStrMsg->setVisible( true );
		pStrMsg->setPosition(ccp( 304, 230 ));
		pMessagelistView->addChild( pStrMsg );

	}

	if ( m_mainmapuilayer->m_messagelist.empty() )
	{
		//m_mainmapuilayer->m_messagetips->setVisible( false );
	}
	else
	{
		//m_mainmapuilayer->m_messagetips->setVisible( true );
	}

	UILabelAtlas* pLabelAcceptLife = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->messageListLayout->getChildByName( "LabelAcceptLife" ));
	pLabelAcceptLife->setStringValue( CCString::createWithFormat("%d", AnalyseJson::getHandselMsg.heardLimit)->getCString() );

	float nDelayTime1 = 0.48f ;//+ 0.08f;
	float nDelayTime2 = 0.082f;
	for (int i = 0; i < nMessageLen; i++)
	{
		// m_messagelist
		const char* pItemName = CCString::createWithFormat("MessageItem%d", p->m_friendid )->getCString();
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setName( pItemName );
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(550, 112));
		pItemImg->setVisible( true );
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 116 + 15 );
		pMessagelistView->addChild( pItemImg );

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setVisible( true );
		pHeadbgImg->setPosition(ccp(-226, 0));
		pHeadbgImg->setTag( p->m_friendid );
		pItemImg->addChild( pHeadbgImg);

		float nScale = 0;
		std::string headPath = CommonData::getHeadPathForUrl( p->m_headurl );
		UIImageView* pHeadImg = UIImageView::create();
		pHeadImg->setTexture( headPath.c_str() );
		nScale = PIC_HEAD_W/pHeadImg->getSize().width;
		pHeadImg->setVisible( true );
		pHeadImg->setPosition(ccp(0,0));
		pHeadbgImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setVisible( true );
		pHeadKImg->setPosition(ccp(0, 0));
		pHeadbgImg->addChild( pHeadKImg);


		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->m_sex )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(44, -37));
		pHeadbgImg->addChild( pSexbgImg);

		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setVisible( true );
		pDivideline->setPosition(ccp(0, -62));
		pItemImg->addChild( pDivideline);

		std::string pMsgStr;
		// 好友邀请
		if ( MESSAGE_TYPE_INVATEFRIEND == p->m_type )
		{
			pMsgStr = CommonData::GetString("app_invitefriend_str");

			UIButton* pBtnAccept = UIButton::create();
			pBtnAccept->setNormalTexture( "Image/MainMapUi/btn_acceptfriendN.png" );
			pBtnAccept->setPressedTexture( "Image/MainMapUi/btn_acceptfriendP.png" );
			pBtnAccept->setDisabledTexture ( "Image/MainMapUi/btn_acceptfriendP.png" );
			pBtnAccept->setTag( MESSAGE_ACCEPT_FRIEND );
			pBtnAccept->setTouchEnable( true );
			pBtnAccept->setVisible( true );
			pBtnAccept->isEffects( true/*, nDelayTime1 + nDelayTime2*i*/ );
			pBtnAccept->setPosition(ccp(249, 5));
			pBtnAccept->data = (void*)p->m_friendid;
			pBtnAccept->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMessageList)); 
			pItemImg->addChild( pBtnAccept );

		}
		// 赠送糖果币
		else if ( MESSAGE_TYPE_HANDSELEFT == p->m_type )
		{
			pMsgStr = CommonData::GetString("app_handsellife_str");

			UIButton* pSloveImg = UIButton::create();
			pSloveImg->setNormalTexture( "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			pSloveImg->setPressedTexture( "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			pSloveImg->setDisabledTexture ( "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			pSloveImg->setTag( MESSAGE_ACCEPT_LIFE );
			pSloveImg->setTouchEnable( true );
			pSloveImg->setVisible( true );
			pSloveImg->isEffects( true/*, nDelayTime1 + nDelayTime2*i*/ );
			pSloveImg->setPosition(ccp(249, 5));
			pSloveImg->data = (void*)p->m_friendid;
			pSloveImg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackMessageList)); 
			pItemImg->addChild( pSloveImg );
		}

		UITextArea* pFriendnameBG = UITextArea::create();
		pFriendnameBG->setAnchorPoint( ccp(0.5f, 0.5f));
		pFriendnameBG->setPosition( ccp(1, -1) );
		pFriendnameBG->setFontSize( 30 );
		pFriendnameBG->setTextHorizontalAlignment( kCCTextAlignmentCenter );
		pFriendnameBG->setTextVerticalAlignment( kCCVerticalTextAlignmentCenter );
		pFriendnameBG->setTextAreaSize( CCSizeMake(300, 100));
		pFriendnameBG->setColor( ccc3(100,100,100));
		pFriendnameBG->setText( CCString::createWithFormat( pMsgStr.c_str(), p->m_friendname.c_str())->getCString());
		pFriendnameBG->setVisible( true );
		pItemImg->addChild( pFriendnameBG );

		UITextArea* pFriendnamd = UITextArea::create();
		pFriendnamd->setAnchorPoint( ccp(0.5f, 0.5f));
		pFriendnamd->setPosition( ccp(0, 0) );
		pFriendnamd->setFontSize( 30 );
		pFriendnamd->setTextHorizontalAlignment( kCCTextAlignmentCenter );
		pFriendnamd->setTextVerticalAlignment( kCCVerticalTextAlignmentCenter );
		pFriendnamd->setTextAreaSize( CCSizeMake(300, 100));
		pFriendnamd->setColor( ccc3(255,255,255));
		pFriendnamd->setText( CCString::createWithFormat( pMsgStr.c_str(), p->m_friendname.c_str())->getCString());
		pFriendnamd->setVisible( true );
		pItemImg->addChild( pFriendnamd );

		p++;

	}
}

void MainMapUiLayer::updataMessageList(CCPoint point)
{
	UIScrollView* pMessagelistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	CCSize scrollSize = pMessagelistView->getContentSize();
	int nMessageLen  = m_mainmapuilayer->m_messagelist.size();
	float ClipWidth, ClipHeight;
	std::list<MessageNode>::iterator tem = m_mainmapuilayer->m_messagelist.begin();
	float butMPointY;

	ClipWidth = scrollSize.width;
	ClipHeight = nMessageLen * ( 116 + 15 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pMessagelistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));

	butMPointY = ClipHeight - 116/2;
	for (; tem != m_mainmapuilayer->m_messagelist.end(); tem++)
	{
		const char* pItemName = CCString::createWithFormat("MessageItem%d", tem->m_friendid )->getCString();
		UIImageView* pItem = (UIImageView*)pMessagelistView->getChildByName( pItemName );
		if ( !pItem )
			continue;
		
		
		pItem->setPosition( ccp(scrollSize.width/2, butMPointY) );
		butMPointY -= ( 116 + 15 );
	}

	if ( 0 == m_mainmapuilayer->m_messagelist.size() )
	{
		UIImageView* pNoMsg = UIImageView::create();
		pNoMsg->setTexture( MSG_IMG_NOTHING );
		pNoMsg->setVisible( true );
		pNoMsg->setPosition(ccp( 300, 380 ));
		pMessagelistView->addChild( pNoMsg );

		UIImageView* pStrMsg = UIImageView::create();
		pStrMsg->setTexture( MSG_STR_NOMSG );
		pStrMsg->setVisible( true );
		pStrMsg->setPosition(ccp( 304, 230 ));
		pMessagelistView->addChild( pStrMsg );

	}

	UIWidget *pwidgt = pMessagelistView->getInnerContainer();
	pwidgt->setPosition( point );

	UILabelAtlas* pLabelAcceptLife = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->messageListLayout->getChildByName( "LabelAcceptLife" ));
	pLabelAcceptLife->setStringValue( CCString::createWithFormat("%d", AnalyseJson::getHandselMsg.heardLimit)->getCString() );

}

void MainMapUiLayer::removeFriendAndUpdataList(int friendid)
{
	UIScrollView* plistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->friendListLayout->getChildByName( "m_sv_friendlist" ));
	CCSize scrollSize = plistView->getContentSize();
	int nlistLen = 0;
	float ClipWidth, ClipHeight;
	std::list<UserFriendInfoStr>::iterator tem;
	float butMPointY;
	CCPoint nCurListPos;
	
	UIWidget *pwidgt = plistView->getInnerContainer();
	nCurListPos = pwidgt->getPosition();

	tem = AnalyseJson::friendInfoMsg.friendInfo.begin();

	for (; tem != AnalyseJson::friendInfoMsg.friendInfo.end(); tem++)
	{
		if (friendid == tem->id)
		{
			const char* pItemName = CCString::createWithFormat("FriendItem%d", tem->id )->getCString();
			UIImageView* pItem = (UIImageView*)plistView->getChildByName( pItemName );
			if ( pItem ) pItem->removeFromParent();

			MsgMgr::sendDelFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id, tem->id );
			AnalyseJson::friendInfoMsg.friendInfo.erase( tem );
			break;
		}
	}


	tem = AnalyseJson::friendInfoMsg.friendInfo.begin();
	nlistLen = AnalyseJson::friendInfoMsg.friendInfo.size();
	ClipWidth = scrollSize.width;

	if ( nlistLen )
		ClipHeight = (nlistLen + 1) * ( 112 + 20 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	plistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));

	butMPointY = ClipHeight - 112/2;
	for (; tem != AnalyseJson::friendInfoMsg.friendInfo.end(); tem++)
	{
		const char* pItemName = CCString::createWithFormat("FriendItem%d", tem->id )->getCString();
		UIImageView* pItem = (UIImageView*)plistView->getChildByName( pItemName );
		if ( !pItem )
			continue;


		pItem->setPosition( ccp(scrollSize.width/2, butMPointY) );
		butMPointY -= ( 112 + 20 );
	}

 	CCPoint pos = pwidgt->getPosition();
 	//pwidgt->setPosition( nCurListPos );

}

// 添加历史消息列表
void MainMapUiLayer::addHistoryMsgtoList(void)
{
	UIScrollView* pMessagelistView = dynamic_cast<UIScrollView*>(messageListLayout->getChildByName( "m_sv_messagelist_2" ));
	CCSize scrollSize = pMessagelistView->getContentSize();
	pMessagelistView->removeAllChildrenAndCleanUp( true );
	int nFriendLen = AnalyseJson::propRecordStr.propRecord.size();//m_mainmapuilayer->m_Recordmsg.size();
	CCSize itemPoint;


	if ( m_isNetHistoryMsg )
		setLoading( false );

	if ( 0 == nFriendLen )
	{
		UIImageView* pNoMsg = UIImageView::create();
		pMessagelistView->addChild( pNoMsg );
		pNoMsg->setTexture( MSG_IMG_NOTHING );
		pNoMsg->setVisible( true );
		pNoMsg->setPosition(ccp( 280, 323 ));

		UIImageView* pStrMsg = UIImageView::create();
		pMessagelistView->addChild( pStrMsg );
		pStrMsg->setTexture( MSG_STR_NOPROPMSG );
		pStrMsg->setVisible( true );
		pStrMsg->setPosition(ccp( 284, 178 ));
	}

	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;

	std::list<UserPropRecordMsg>::iterator p;
	p = AnalyseJson::propRecordStr.propRecord.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nFriendLen * ( 126 + 15 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pMessagelistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	pMessagelistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 126/2;

	for (int i = 0; i<nFriendLen; i++)
	{
		// m_friendlist
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/m_itembg.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(580, 126));
		pItemImg->setVisible( true );
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 126 + 15 );
		pMessagelistView->addChild( pItemImg );

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setVisible( true );
		pHeadbgImg->setScale( 0.8f );
		pHeadbgImg->setTouchEnable( true );
		pHeadbgImg->setPosition(ccp(-217, 0));
		pHeadbgImg->setTag( i );
		pItemImg->addChild( pHeadbgImg);

		char UrlName[128]= {0};
		HeadDownMgr::getHeadNameForUrl(p->headPicUrl, UrlName);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		char *HeadName = (char *)CCString::createWithFormat("%s",UrlName)->getCString();
		char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, HeadName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		char *headPath= (char *)CCString::createWithFormat("Image/wemepci/%s.png", UrlName)->getCString();
#endif
		UIImageView* pHeadImg = UIImageView::create();
		float nScale = 0;
		pHeadImg->setTexture( headPath );
		nScale = 100/pHeadImg->getSize().width;
		pHeadImg->setScale(nScale);
		pHeadImg->setVisible( true );
		pHeadImg->setPosition(ccp(0, 0));
		pHeadbgImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/m_img_headK.png" );
		pHeadKImg->setVisible( true );
		pHeadKImg->setScale( 0.8f );
		pHeadKImg->setPosition(ccp(-217, 0));
		pItemImg->addChild( pHeadKImg);

		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == p->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

		pSexbgImg->setVisible( true );
		pSexbgImg->setPosition(ccp(-167-8, -37+8));
		pItemImg->addChild( pSexbgImg);

		char* pPropPath = (char *)CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", p->propId)->getCString();
		UIImageView* pPropIco = UIImageView::create();
		pPropIco->setVisible( true );
		pPropIco->setPosition(ccp(210, 13));
		pItemImg->addChild( pPropIco);
		pPropIco->setTexture( pPropPath );

		std::string pMsgStrU;
		std::string pMsgStrU2;

		if ( 0 == p->flag )
		{
			// 我给%s赠送%d个%s
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			std::string nTempStr = u2a(CommonData::GetString( "app_my_handsel_friend_str" ).c_str());
			std::string nTempStr1 = u2a(CommonData::GetString( "app_my_handsel_friend_str1" ).c_str());
			std::string nUserNameA = u2a(p->nickName.c_str()); 
			std::string nPropNameA = u2a(p->propName.c_str()); 
			char pMsgStrA[256] = {0};
			char pMsgStrB[256] = {0};

			sprintf(pMsgStrA, nTempStr.c_str(),nUserNameA.c_str() );
			sprintf(pMsgStrB, nTempStr1.c_str(), nPropNameA.c_str() );

			pMsgStrU = a2u( pMsgStrA );
			pMsgStrU2 =  a2u( pMsgStrB );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			char temp2[256] = {0};
			char temp1[256] = {0};
			sprintf(temp2, "我给%s",p->nickName.c_str() );
			sprintf(temp1, "赠送%s", p->propName.c_str() );
			pMsgStrU = temp2;
			pMsgStrU2 = temp1;

#endif
		}
		else if( 1 == p->flag )
		{
			// %s送给我%d个%s
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			std::string nTempStr = u2a(CommonData::GetString( "app_friend_handsel_my_str" ).c_str());
			std::string nTempStr1 = u2a(CommonData::GetString( "app_friend_handsel_my_str1" ).c_str());
			std::string nUserNameA = u2a(p->nickName.c_str()); 
			std::string nPropNameA = u2a(p->propName.c_str()); 
			char pMsgStrA[256] = {0};
			char pMsgStrB[256] = {0};

			sprintf(pMsgStrA, nTempStr.c_str(),nUserNameA.c_str());
			sprintf(pMsgStrB, nTempStr1.c_str(), nPropNameA.c_str() );

			pMsgStrU = a2u( pMsgStrA );
			pMsgStrU2 = a2u( pMsgStrB );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			char temp2[256] = {0};
			char temp1[256] = {0};
			sprintf(temp2, "%s给我",p->nickName.c_str() );
			sprintf(temp1, "赠送%s", p->propName.c_str() );
			pMsgStrU = temp2;
			pMsgStrU2 = temp1;
#endif
		}
		else if( 2 == p->flag )
		{
			// 我向%s索要%d个%s
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			std::string nTempStr = u2a(CommonData::GetString( "app_my_claim_friend_str" ).c_str());
			std::string nTempStr1 = u2a(CommonData::GetString( "app_my_claim_friend_str1" ).c_str());
			std::string nUserNameA = u2a(p->nickName.c_str()); 
			std::string nPropNameA = u2a(p->propName.c_str()); 
			char pMsgStrA[256] = {0};
			char pMsgStrB[256] = {0};

			sprintf(pMsgStrA, nTempStr.c_str(),nUserNameA.c_str() );
			sprintf(pMsgStrB, nTempStr1.c_str(), nPropNameA.c_str() );
			pMsgStrU = a2u( pMsgStrA );
			pMsgStrU2 = a2u( pMsgStrB );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			char temp2[256] = {0};
			char temp1[256] = {0};
			sprintf(temp2, "我向%s",p->nickName.c_str() );
			sprintf(temp1, "索要%s", p->propName.c_str() );
			pMsgStrU = temp2;
			pMsgStrU2 = temp1;
#endif
		}
		else if ( 3 == p->flag )
		{
			// %s向我索要%d个%s
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			std::string nTempStr = u2a(CommonData::GetString( "app_friend_claim_my_str" ).c_str());
			std::string nTempStr2 = u2a(CommonData::GetString( "app_friend_claim_my_str1" ).c_str());
			std::string nUserNameA = u2a(p->nickName.c_str()); 
			std::string nPropNameA = u2a(p->propName.c_str()); 
			char pMsgStrA[256] = {0};
			char pMsgStrB[256] = {0};

			sprintf(pMsgStrA, nTempStr.c_str(),nUserNameA.c_str() );
			sprintf(pMsgStrB, nTempStr2.c_str(), nPropNameA.c_str() );
			pMsgStrU = a2u( pMsgStrA );
			pMsgStrU2 = a2u( pMsgStrB );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			char temp2[256] = {0};
			char temp1[256] = {0};
			sprintf(temp2, "%s向我",p->nickName.c_str() );
			sprintf(temp1, "索要%s", p->propName.c_str() );
			pMsgStrU = temp2;
			pMsgStrU2 = temp1;
#endif
		}

		UILabel* pFriendName = UILabel::create();
		pFriendName->setAnchorPoint( ccp(0.0f, 0.5f));
		pFriendName->setText( pMsgStrU.c_str() );
		pFriendName->setPosition( ccp(-170, 24));
		pFriendName->setFontSize( 35 );
		pFriendName->setVisible( true );
		pFriendName->setColor( ccc3(121,61,10));
		pItemImg->addChild( pFriendName);

		UITextArea* pFriendnamd = UITextArea::create();
		pFriendnamd->setPosition( ccp(-75, -20) );
		pFriendnamd->setColor( ccc3(158,84,10));
		pFriendnamd->setFontSize(26);
		pFriendnamd->setTextHorizontalAlignment( kCCTextAlignmentCenter );
		pFriendnamd->setTextVerticalAlignment( kCCVerticalTextAlignmentCenter );
		pFriendnamd->setTextAreaSize( CCSizeMake(300, 100));
		pFriendnamd->setAnchorPoint( ccp(0.5f, 0.5f));
		pFriendnamd->setText( (const char *)pMsgStrU2.c_str() );
		pFriendnamd->setVisible( true );
		pItemImg->addChild( pFriendnamd );

		UILabel* pTime = UILabel::create();
		pTime->setPosition( ccp(165, -38) );
		pTime->setColor( ccc3(0,0,255));
		pTime->setFontSize(20);
		pTime->setAnchorPoint( ccp(0.0f, 0.5f));
		pTime->setText( (const char *)p->timeEnd.c_str() );
		pTime->setVisible( true );
		pItemImg->addChild( pTime );

		p++;
	}
}


void MainMapUiLayer::addNoticetoList(void)
{
	UIScrollView* pNoticelistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_3" ));
	pNoticelistView->removeAllChildrenAndCleanUp( true );

	UIImageView* pNoMsg = UIImageView::create();
	pNoticelistView->addChild( pNoMsg );
	pNoMsg->setTexture( MSG_IMG_NOTHING );
	pNoMsg->setVisible( true );
	pNoMsg->setPosition(ccp( 280, 323 ));

	UIImageView* pStrMsg = UIImageView::create();
	pNoticelistView->addChild( pStrMsg );
	pStrMsg->setTexture( MSG_STR_NONOTIC );
	pStrMsg->setVisible( true );
	pStrMsg->setPosition(ccp( 284, 178 ));
}

// 添加生命列表
void MainMapUiLayer::addLifetoList(void)
{
//	UIScrollView* pLifelistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->LifeListLayout->getChildByName( "m_sv_lifelist" ));
//	CCSize scrollSize = pLifelistView->getContentSize();
//	pLifelistView->removeAllChildrenAndCleanUp(true);
//	int nFriendLen = 0;
//	CCSize itemPoint;
//	// 计算出scrollView的高
//	float ClipWidth; 
//	float ClipHeight;
//	int sex = 0;
//
//#if defined(DEMO_FOR_INTERFLOW)
//	nFriendLen = 4;
//#elif defined(DEMO_FOR_MOBILE)|| defined(DEMO_FOR_GUEST)
//	nFriendLen = 1;
//#endif
//	ClipWidth = scrollSize.width;
//	ClipHeight = nFriendLen * ( 126 + 15 );
//	if (ClipHeight < scrollSize.height)
//		ClipHeight = scrollSize.height;
//	pLifelistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
//	pLifelistView->setTouchEnable( true );
//	itemPoint.width = scrollSize.width/2;
//	float butMPointY = ClipHeight - 126/2;
//
//	float nDelayTime1 = 0.48f ;//+ 0.08f;
//	float nDelayTime2 = 0.082f;
//	for (int i = 0; i<nFriendLen; i++)
//	{
//		// m_lifelist
//		UIImageView* pItemImg = UIImageView::create();
//		pItemImg->setScale9Enabled( true );
//		pItemImg->setScale9Size( CCSizeMake(560, 120));
//		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
//		pItemImg->setVisible( true );
//		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
//		butMPointY -= ( 126 + 15 );
//		pLifelistView->addChild( pItemImg );
//
//		UIImageView* pLifePICImg = UIImageView::create();
//		std::string nLifePic = CCString::createWithFormat("Image/MainMapUi/m_img_life%d.png",i+1)->getCString();
//		pLifePICImg->setTexture( nLifePic.c_str() );
//		pLifePICImg->setVisible( true );
//		pLifePICImg->setPosition(ccp(-190, 0));
//		pLifePICImg->setTag( i );
//		pItemImg->addChild( pLifePICImg);
//
//		// ＝＝＝〉*
//		UIImageView* psign1 = UIImageView::create();
//		psign1->setTexture( "Image/MainMapUi/m_img_sign1.png" );
//		psign1->setVisible( true );
//		psign1->setPosition(ccp(-100, 0));
//		pItemImg->addChild( psign1 );
//
//		UILabelAtlas* AtlevelNum1 = UILabelAtlas::create();
//		char *strLevelNum= (char *)CCString::createWithFormat("%d",  5)->getCString();
//		AtlevelNum1->setVisible( true );
//		AtlevelNum1->setScale( 0.7f );
//		AtlevelNum1->setProperty(strLevelNum , "Image/MainMapUi/m_img_num2.png",42, 51, "0");  
//		AtlevelNum1->setPosition( ccp(-35, 0));
//		pItemImg->addChild( AtlevelNum1 );
//
//		UIButton* pBuyBut = UIButton::create();
//		pBuyBut->setNormalTexture( "Image/MainMapUi/m_but_buylifeN.png" );
//		pBuyBut->setPressedTexture( "Image/MainMapUi/m_but_buylifeP.png" );
//		pBuyBut->setDisabledTexture( "Image/MainMapUi/m_but_buylifeP.png" );
//		pBuyBut->setTag( i );
//		pBuyBut->setTouchEnabled( true );
//		pBuyBut->setVisible( true );
//		pBuyBut->isEffects( true, nDelayTime1+nDelayTime2*i );
//		pBuyBut->setPosition(ccp(165, 0));
//		pBuyBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackBuyLife));
//		pItemImg->addChild( pBuyBut );
//
//		UIImageView* psign3 = UIImageView::create();
//		psign3->setTexture( "Image/MainMapUi/buyItem/map_gamico.png" );
//		psign3->setVisible( true );
//		psign3->setPosition(ccp(-40, 0));
//		pBuyBut->addChild( psign3 );
//
//		UILabelAtlas* lifeprice = UILabelAtlas::create();
//		lifeprice->setVisible( true );
//		lifeprice->setProperty((char*)AnalyseJson::logOnMsg.lifeInfo.price.c_str() , "Image/MainMapUi/buyItem/gem_price_str.png",29, 40, "0");  
//		lifeprice->setPosition( ccp(35, 0));
//		pBuyBut->addChild( lifeprice );
//
//		UIImageView* pbuydivideLine = UIImageView::create();
//		pbuydivideLine->setTexture( "Image/MainMapUi/buyItem/buydivideline.png" );
//		pbuydivideLine->setVisible( true );
//		pbuydivideLine->setPosition(ccp(0, -65));
//		pItemImg->addChild( pbuydivideLine );
//
//	}
}

void MainMapUiLayer::UpdateGlobeAction()
{
	this->schedule( schedule_selector(MainMapUiLayer::UpdateGlobeActionCB), 2.0f );
}

CCActionInterval* MainMapUiLayer::getMoveAction(int state, CCPoint pos)
{
	CCActionInterval* move = NULL;
	CCActionInterval* move_ease_inout2 = NULL;

	if( MAP_DLG_QUIT == state )
	{
		move = CCMoveTo::create(0.7f, pos);
		move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );
	}
	else if( MAP_DLG_ENTRY == state )
	{
		move = CCMoveTo::create(0.8f, pos);
		move_ease_inout2 = CCEaseElasticOut::create((CCActionInterval*)move,0.8f );
	}
	return move_ease_inout2;
}

CCActionInterval* MainMapUiLayer::getTaskMsgTipsAction(void)
{	
	return CCRepeatForever::create(
		CCSequence::create(	
		CCScaleTo::create(0.4f, 1.0f, 0.9f),
		CCScaleTo::create(0.2f, 0.9, 1.15f), 
		CCScaleTo::create(0.2f, 1.0f),
		CCDelayTime::create(0.1f),
		NULL));
}

// 
void MainMapUiLayer::ReminderLifeCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	UIButton* pBut = (UIButton*)pSender;
	int nIndex = pBut->getTag();

	//MainMap::setLevelButTouches( false );
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(m_mainmapuilayer->reminderLayout->getChildByName( "m_img_dlg" ));
	m_mainmapuilayer->m_pPanel->setVisible( false );
	m_mainmapuilayer->m_pPanel->setTouchEnabled( false );

	CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);

	CCActionInterval * fadeout = CCFadeOut::create(0.2f);
	CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
	CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);
	pImgDlg->runAction(CCSequence::create(
		pScale,
		spawn,
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::EnteyBuyLifeCallBack)),
		NULL)
		);

	if ( !m_mainmapuilayer->widgetList.empty())
		m_mainmapuilayer->widgetList.pop_front();

}

void MainMapUiLayer::ReminderExitCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(m_mainmapuilayer->reminderLayout->getChildByName( "m_img_dlg" ));
	CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
	CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
	pImgDlg->runAction(CCSequence::create(
		pScale,
		pScale1,
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::ReminderClose)),
		NULL)
		);
	if ( !m_mainmapuilayer->widgetList.empty())
		m_mainmapuilayer->widgetList.pop_front();
}

void MainMapUiLayer::ReminderNetCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	int nIndex = pBut->getTag();

	m_mainmapuilayer->reminderLayout->runAction(CCSequence::create(
		getMoveAction(MAP_DLG_QUIT, ccp(-740,0.0f) /*LEVEL_QUIT_CCCP*/),
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::EnteyBuyLifeCallBack)), 
		NULL)
		);
	m_mainmapuilayer->QuitMapWidgetCallback();

}

void MainMapUiLayer::SuccendDlgSurCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	QuitMapWidget();
}

void MainMapUiLayer::CliamLifeSurCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	QuitMapWidget();
}

void MainMapUiLayer::LevelInfoNextCB(CCObject *pSender)
{
	if(pSender != NULL)
	{
		UIButton* pBut = (UIButton*)pSender;
		pBut->setTouchEnabled(false);
	}
	PlayEffect( MUSIC_ITEM_BUTTON_E );


#ifdef CANDY_STATISITICAL_DATA
	/*if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_70 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_80 );*/
#endif

	/*m_mainmapuilayer->levelLayout->runAction(CCSequence::create(
		getMoveAction(MAP_DLG_QUIT, ccp(0.0f,CCDirector::sharedDirector()->getWinSize().height + CCDirector::sharedDirector()->getWinSize().height/2)),
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::EnteyGameCallBack)), 
		NULL)
		);*/
}

void MainMapUiLayer::EnteyBuyLifeCallBack(void)
{
	m_mainmapuilayer->getWidgetUILayer()->removeWidget(m_mainmapuilayer->reminderLayout);
	MainMap::m_mainmap->DisplayMapUi();
	//	m_mainmapuilayer->showMapWidget( MAP_WIDGET_LIFE_INFO );
}

void MainMapUiLayer::EnteyGameCallBack(void)
{
	m_mainmapuilayer->getWidgetUILayer()->removeWidget(m_mainmapuilayer->LevelInfoLayout);
#ifdef CANDY_STATISITICAL_DATA
	/*if( 10 >= CommonData::getMaxLevel() )
	{
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_16, CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString());
	}*/
#endif
#ifdef CANDY_VERSIONS_FOR_SINGLE
	if (0)
#else
	if (LILE_MIN_NUM >= AnalyseJson::logOnMsg.lifeInfo.lifeNum )
#endif
	{
#if defined(DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
		//m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

#else
		MainMapUiLayer::m_mainmapuilayer->m_pTools->setTouchEnable( false );
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

		//m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );.
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

#endif
	}
	else
	{
		CommonData::setLastStarNumForLevel( CandyManager::currentLevel );
		CommonData::setPlayGame( true );
		Loading::replaceScence(CANDY_SCENCE_PLAY_GAME);
	}
}

void MainMapUiLayer::LevelInfoReturnCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

#ifdef CANDY_STATISITICAL_DATA
	/*if ( 10 >= CommonData::getMaxLevel() ) 
	{
		char* pLevel = (char*)CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString();
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_15, pLevel);
	}

	if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_71 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_81 );*/
#endif

	QuitMapWidget();
}

void MainMapUiLayer::BtnCallBackCloseFriendInfo(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	m_mainmapuilayer->friendInfoLayout->setTouchEnabled( false );
	m_mainmapuilayer->friendInfoLayout->setVisible(false);
	m_mainmapuilayer->friendInfoLayout->setPosition( LEVEL_QUIT_CCCP );
	m_mainmapuilayer->showMapWidget( MAP_WIDGET_FRIEND_LIST );

}

void MainMapUiLayer::BtnCallBackCloseFriendList(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	QuitMapWidget();
}

// 邀请
void MainMapUiLayer::InviteButCallBack(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBtn = (UIButton*)pSender;
	int friendid = (int)pBtn->data;
	int index = pBtn->getTag();
	pBtn->disable( true );

	MsgMgr::sendInvateFriendForGuestMsg(AnalyseJson::logOnMsg.baseInfo.id, friendid);

	CCNode* particle = CandyParticle::displayCandyParticle(CANDY_PARTICLE_XINFENG_EFFECT, ccp(0,0));
	particle->setZOrder( 10 );
	pBtn->getRenderer()->addChild( particle );

	if ( INVITEFRIEND_FOR_RECOMMEND == index )
	{
		std::list<UserNoFriendInfoStr>::iterator p;
		if (!AnalyseJson::nofriendInfoMsg.nofriend.empty())
			p = AnalyseJson::nofriendInfoMsg.nofriend.begin();

		for( int i = 0; i< (int)AnalyseJson::nofriendInfoMsg.nofriend.size(); i++, p++)
		{
			if (friendid == p->id )
				break;
		}
		p->isInvite = true ;
		// 		if ( !AnalyseJson::nofriendInfoMsg.nofriend.empty() )
		// 			AnalyseJson::nofriendInfoMsg.nofriend.erase(p);   
		// 		addNofriendtoList();
	}
	else if ( INVITEFRIEND_FOR_SEACH ==  index)
	{

	}
}

void MainMapUiLayer::ButCallBackInviteFriendList(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBtn = (UIButton*)pSender;
	int temp = pBtn->getTag();

	if (0 == temp )
	{
		QuitMapWidget();
	}
	else if (1 == temp )
	{
		int listlen = AnalyseJson::nofriendInfoMsg.nofriend.size();


		if ( 0 == listlen )
		{
			setLoading( true );
		}
		else
		{
			std::list<UserNoFriendInfoStr>::iterator p = AnalyseJson::nofriendInfoMsg.nofriend.begin();
			int listlen = AnalyseJson::nofriendInfoMsg.nofriend.size();

			if ( 5 < listlen )
				listlen = 5;

			for (int i = 0; i<listlen; i++)
			{
				UserNoFriendInfoStr tempNofriendInfo;
				tempNofriendInfo.id				=	p->id; 
				tempNofriendInfo.idx			=	p->idx;
				tempNofriendInfo.gender			=	p->gender;
				tempNofriendInfo.headPicUr		=	p->headPicUr;
				tempNofriendInfo.nickName		=	p->nickName;
				tempNofriendInfo.adate			=	p->adate;
				tempNofriendInfo.isfriend		=	p->isfriend;
				tempNofriendInfo.isSelect		=	p->isSelect;
				tempNofriendInfo.isInvite		=	p->isInvite;

				AnalyseJson::nofriendInfoMsg.nofriend.pop_front();
				p = AnalyseJson::nofriendInfoMsg.nofriend.begin();

				if ( !tempNofriendInfo.isInvite )
					AnalyseJson::nofriendInfoMsg.nofriend.push_back(tempNofriendInfo);

			}
			addNofriendtoList();
		}
	}


}

void MainMapUiLayer::ButCallBackInviteFriend(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	m_mainmapuilayer->QuitMapWidgetCallback();
	showMapWidget( MAP_WIDGET_NOFRIEND_LIST );

	if ( 5 >= AnalyseJson::nofriendInfoMsg.nofriend.size() )
	{
		setLoading( true );
		MsgMgr::sendGetNoFriendForGuestMsg(AnalyseJson::logOnMsg.baseInfo.id);
	}
}

void MainMapUiLayer::ButCallBackSeachFriend(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	QuitMapWidgetCallback();
	showMapWidget( MAP_WIDGET_SEACHFRIEND );
}

void MainMapUiLayer::messageListCloseCallBack(CCObject *pSender)
{
	UIButton* pBtn = (UIButton*)pSender;
	int nTag = pBtn->getTag();

	pBtn->setTouchEnabled(false);
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	if ( 0 == nTag )
	{
		//m_mainmapuilayer->m_messagetips->setVisible( false );
		QuitMapWidget();
	}
	else if ( 1 == nTag )
	{
		AnalyseJson::InviteFriendMsgList.nofriend.clear();
		MsgMgr::sendCleanAddFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id );
		HttpGetMyMessageAsyn();	
	}
}

void MainMapUiLayer::CloseCallBack(CCObject *pSender) 
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );

	UIButton* pBtn = (UIButton*)pSender;
	pBtn->setTouchEnabled(false);
	m_mainmapuilayer->QuitMapWidget();

}

void MainMapUiLayer::LackLifeUiButCallBack(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag();

	switch ( index )
	{
		//close button
	case 0:
		QuitMapWidget();
		m_mainmapuilayer->m_pTools->setTouchEnabled( true );
		//CandyPay::getInstance()->RequestCandyOrder(Super_life);
		break;

		// buy life button
	case 1:
		{
			//mini版本不通过宝石购买
			/*CommonData::m_buytype = CANDY_PROP_LIFE;
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_50, MOBILE_MONEY5_BUY_LIFENUM);*/
			
			MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE);
		//	CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_LIFE);


			/*if ( atoi(AnalyseJson::logOnMsg.lifeInfo.price.c_str()) > AnalyseJson::logOnMsg.baseInfo.gemNum)
			{
				CommonData::m_buytype = CANDY_PROP_LIFE;
				CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_50, MOBILE_MONEY5_BUY_LIFENUM);
			}
			else
			{
				MsgMgr::sendGemBuyLife( AnalyseJson::logOnMsg.baseInfo.id, MOBILE_GOURD_LIFENUM);
			}*/
		}
		break;

		// claim life for friend button
	case 2:
		{
			QuitMapWidget();
			showMapWidget( MAP_WIDGET_CLAIMLIFE_DLG );
			addFriendtoClaimList();
		}
		break;
	}
}

void MainMapUiLayer::CliamLifeUiButCallBack(CCObject *pSender)
{	
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag();

	switch ( index )
	{
		// close button
	case 0:
		{
			QuitMapWidget();
		}
		break;

		// claim button
	case 1:
		{
			showMapWidget( MAP_WIDGET_PROPCLIAORHEANDLE_DLG, 0, DLG_TYPE_CLAIMLIFE );
		}
		break;
	}
}

void MainMapUiLayer::ChangeInfoButCallBack(CCObject* pSender)
{
	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag();
	PlayEffect(MUSIC_ITEM_BUTTON_E);

	switch(index)
	{
	case 0:
		QuitMapWidget();

		break;

	case 1:
		{
			std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
			for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
			{
				if(CANDY_PROP_OUT_HEAD == p->id)
					break;
			}

			if( AnalyseJson::logOnMsg.baseInfo.avatar_upd_times !=0)
			{
				if (atoi(p->candyprice.c_str()) > AnalyseJson::logOnMsg.baseInfo.candyNum)
				{
					//	QuitMapWidgetCallback();
					//	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_BUYGEM_LIST );
					
					//走直接支付流程
// 					int payId = CommonData::getPayIDByGemNum(atoi(p->price.c_str()));
// 					CommonData::m_buytype = CANDY_PROP_OUT_HEAD;
// 					CommonData::m_buyMutipropNum = 0;
// 
// 					CppCallJava::toBuyProp(payId, 1);
				}
				else
				{
					MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_OUT_HEAD, 1,2);
				}
			}
			else
			{
				m_mainmapuilayer->QuitMapWidgetCallback();
				uploadInfo();
			}
		}
		break;
	}
}
void MainMapUiLayer::uploadInfo()
{
	if(m_mainmapuilayer != NULL)
	{
		if(m_mainmapuilayer->changeinfoLayout)
		{
			UILabel* pNiceName = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("inputnickname"));
			UILabel* pQQ = dynamic_cast<UILabel*>(m_mainmapuilayer->changeinfoLayout->getChildByName("inputqq"));

			if (  0 >= strlen( (const char*)pNiceName->getStringValue() ))
				return;

			int qqNum = std::atoi(pQQ->getStringValue());

			updataMyInformtion((char*)pNiceName->getStringValue(),qqNum);

			MsgMgr::sendMyInformation(
				AnalyseJson::logOnMsg.baseInfo.id,
				qqNum,
				AnalyseJson::logOnMsg.baseInfo.gender,
				(char*)AnalyseJson::logOnMsg.baseInfo.nickName.c_str());


			AnalyseJson::logOnMsg.baseInfo.avatar_upd_times = 1;
		}
	}
}

void MainMapUiLayer::ChangeInfoSelectCallBack(CCObject* pSender)
{
	UIImageView* pSelectImg = (UIImageView*)pSender;
	int index = pSelectImg->getTag();
	char* pImgName = NULL;
	switch(index)
	{
	case CHANGEINFO_SELECT_HEAD1:
	case CHANGEINFO_SELECT_HEAD2:
	case CHANGEINFO_SELECT_HEAD3:
	case CHANGEINFO_SELECT_HEAD4:
		{
			std::list<std::string>::iterator p = AnalyseJson::SysHeadUrl.headUrl.begin();

			pImgName = (char*)CCString::createWithFormat("selecthead%d", index)->getCString();
			for(int i = CHANGEINFO_SELECT_HEAD1; i<=CHANGEINFO_SELECT_HEAD4; i++,p++)
			{
				UIImageView* pTempImg = NULL;
				char* temName = (char*)CCString::createWithFormat("selecthead%d", i)->getCString();
				pTempImg = dynamic_cast<UIImageView*>(m_mainmapuilayer->changeinfoLayout->getChildByName(temName));
				pTempImg->setVisible(false);

				if (0 == strcmp( pImgName, temName ))
					AnalyseJson::logOnMsg.baseInfo.headPicUrl = p->c_str();
			}

		}
		break;
	case CHANGEINFO_SELECT_SEXBOY:
	case CHANGEINFO_SELECT_SEXGIRL:
		{
			for(int i = CHANGEINFO_SELECT_SEXBOY; i<=CHANGEINFO_SELECT_SEXGIRL; i++)
			{
				UIImageView* pTempImg = NULL;
				pTempImg = dynamic_cast<UIImageView*>(m_mainmapuilayer->changeinfoLayout->getChildByName((char*)CCString::createWithFormat("selectsex%d", i)->getCString()));
				pTempImg->setVisible(false);
			}
			pImgName = (char*)CCString::createWithFormat("selectsex%d", index)->getCString();
			if ( CHANGEINFO_SELECT_SEXBOY == index )
				AnalyseJson::logOnMsg.baseInfo.gender = SEX_BOY;
			else
				AnalyseJson::logOnMsg.baseInfo.gender = SEX_GIRL;

		}
		break;
	}

	UIImageView* pSelectTarget = dynamic_cast<UIImageView*>(m_mainmapuilayer->changeinfoLayout->getChildByName( pImgName ));
	pSelectTarget->setVisible(true);
}

void MainMapUiLayer::NoticeUiButCallBack(CCObject* pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	pBut->setTouchEnabled( false );
	int index = pBut->getTag();
	int currentId = 0;
	switch ( index )
	{
		//close button
	case 0:
		currentId = CommonData::getCurrentPackage();

		if(currentId != 0 && CommonData::m_isEnterGame)
		{
			QuitMapWidgetCallback();
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_GIFT_DLG);
			CommonData::m_isEnterGame = false;
		}
		else
		{
			QuitMapWidget();
		}


		break;
	}
}

void MainMapUiLayer::SeachfriendBtnCB(CCObject* pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag(); 

	switch ( index )
	{
		//close button
	case 0:
		{
			QuitMapWidget();
		}
		break;

	case 1:
		{
			UITextField* pField = dynamic_cast<UITextField*>(m_mainmapuilayer->seachfriendLayout->getChildByName("Seachinput"));
			std::string seachtext = pField->getStringValue();

			setLoading( true );
			MsgMgr::sendSeachFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id, (char*)seachtext.c_str() );
		}
	}


}

// 向好友 索要/赠送道具
void MainMapUiLayer::friendPropButCB(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag();  // 11/12   21/22   31/32  41/42  51/52   61/62  


	std::list<UserFriendInfoStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();

	std::list<UserPropInfoStr>::iterator q;
	q = AnalyseJson::logOnMsg.propInfo.begin();

	for (int i = 0; i< (int)AnalyseJson::friendInfoMsg.friendInfo.size(); i++)
	{
		if (p->id == m_mainmapuilayer->m_CurSelFriendItem)
		{
			break;
		}
		p++;
	}

	int nPropIndex = index/10 - 1;
	for ( int j = 0; j< (int)AnalyseJson::logOnMsg.propInfo.size(); j++)
	{
		if ( nPropIndex == j)
		{
			break;
		}
		q++;
	}

	if ( 2 == index%10)
	{
		// 赠送道具 
		if ( 0 < q->num )
		{
			MsgMgr::sendHandselPropMsg( AnalyseJson::logOnMsg.baseInfo.id, p->id, q->id, 1, 1);
			showMapWidget( MAP_WIDGET_PROPCLIAORHEANDLE_DLG,q->id , DLG_TYPE_HANDSELPROP);
		}
		else
		{
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(m_mainmapuilayer->friendInfoLayout->getChildByName( "m_img_dlg" ));
			showMapWidget( MAP_WIDGET_PROPCLIAORHEANDLE_DLG,q->id , DLG_TYPE_HANDSELPROP);
			// 购买道具
		}
	}
	// 道具数量不足，走支付平台进行道具购买
	else if (1 == index%10)
	{
		// 索要道具
		MsgMgr::sendClaimPropMsg( AnalyseJson::logOnMsg.baseInfo.id, p->id, q->id, 1, 1);
		showMapWidget( MAP_WIDGET_PROPCLIAORHEANDLE_DLG,q->id, DLG_TYPE_CLAIMEPROP );
	}
}

void MainMapUiLayer::AllAcceptProcCallBack(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	std::list<MessageNode>::iterator p = m_mainmapuilayer->m_messagelist.begin();

	for (int i = 0; i< (int)m_mainmapuilayer->m_messagelist.size(); i++)
	{
		if (MESSAGE_TYPE_HANDSELEFT == p->m_type || MESSAGE_TYPE_HANDSEPROP == p->m_type )
		{
			p->m_isAccept = true;
		}
		p++;
	}
	MsgMgr::sendAllAcceptUserHandsel( AnalyseJson::logOnMsg.baseInfo.id );

	// 	m_mainmapuilayer->messageListLayout->setTouchEnabled( false );
	// 	m_mainmapuilayer->messageListLayout->setVisible(false);
	showMapWidget( MAP_WIDGET_SUCCEEDUI_DLG , PROMPT_TYPE_INVITE);
}

void MainMapUiLayer::MessageTabCallBack(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIImageView* messageTab = (UIImageView*) pSender;
	int bMessageTab = messageTab->getTag();

	UIButton* pButAllAccept = dynamic_cast<UIButton*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_btn_allaccept" ));
	switch (messageTab->getTag())
	{
	case MESSAGE_TABLE_1:
		showMessageTab1();
		pButAllAccept->setVisible( true );
		break;
	case MESSAGE_TABLE_2:
		setLoading( true );
		showMessageTab2();
		pButAllAccept->setVisible( false );
		MsgMgr::sendGetChatRecordMsg( AnalyseJson::logOnMsg.baseInfo.id );
		break;
	case MESSAGE_TABLE_3:
		showMessageTab3();
		addNoticetoList();
		pButAllAccept->setVisible( false );
		break;
	default:
		break;
	}
}

void MainMapUiLayer::showMessageTab1(void)
{
	UIImageView* MessagehightTab1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_giveP" ));
	UIImageView* MessagehightTab2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_reqP" ));
	UIImageView* MessagehightTab3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_noticeP" ));

	UIScrollView* MessageSVTab1 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	UIScrollView* MessageSVTab2 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_2" ));
	UIScrollView* MessageSVTab3 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_3" ));

	MessageSVTab1->setVisible( true );
	MessageSVTab2->setVisible( false );
	MessageSVTab3->setVisible( false );

	MessageSVTab1->setZOrder( 3 );
	MessageSVTab2->setZOrder( 1 );
	MessageSVTab3->setZOrder( 1 );

	MessageSVTab1->setTouchEnabled( true );
	MessageSVTab2->setTouchEnabled( false );
	MessageSVTab3->setTouchEnabled( false );

	MessagehightTab1->setVisible( true );
	MessagehightTab2->setVisible( false );
	MessagehightTab3->setVisible( false );

}
void MainMapUiLayer::showMessageTab2(void)
{
	UIImageView* MessagehightTab1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_giveP" ));
	UIImageView* MessagehightTab2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_reqP" ));
	UIImageView* MessagehightTab3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_noticeP" ));

	UIScrollView* MessageSVTab1 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	UIScrollView* MessageSVTab2 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_2" ));
	UIScrollView* MessageSVTab3 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_3" ));

	MessageSVTab1->setVisible( false );
	MessageSVTab2->setVisible( true );
	MessageSVTab3->setVisible( false );

	MessageSVTab1->setZOrder( 1 );
	MessageSVTab2->setZOrder( 3 );
	MessageSVTab3->setZOrder( 1 );
	MessageSVTab1->setTouchEnabled( false );
	MessageSVTab2->setTouchEnabled( true );
	MessageSVTab3->setTouchEnabled( false );

	MessagehightTab1->setVisible( false );
	MessagehightTab2->setVisible( true );
	MessagehightTab3->setVisible( false );
}
void MainMapUiLayer::showMessageTab3(void)
{
	UIImageView* MessagehightTab1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_giveP" ));
	UIImageView* MessagehightTab2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_reqP" ));
	UIImageView* MessagehightTab3 = dynamic_cast<UIImageView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_img_noticeP" ));

	UIScrollView* MessageSVTab1 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	UIScrollView* MessageSVTab2 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_2" ));
	UIScrollView* MessageSVTab3 = dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_3" ));

	MessageSVTab1->setZOrder( 1 );
	MessageSVTab2->setZOrder( 1 );
	MessageSVTab3->setZOrder( 3 );

	MessageSVTab1->setVisible( false );
	MessageSVTab2->setVisible( false );
	MessageSVTab3->setVisible( true );
	MessagehightTab1->setVisible( false );
	MessagehightTab2->setVisible( false );
	MessagehightTab3->setVisible( true );
}

void MainMapUiLayer::InviteFriendButCB(void)
{
	m_mainmapuilayer->friendListLayout->setTouchEnabled( false );
	m_mainmapuilayer->friendListLayout->setVisible( false );
	m_mainmapuilayer->showMapWidget( MAP_WIDGET_NOFRIEND_LIST );

}

void MainMapUiLayer::BtnCallBackBuyLife(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton *itemIdex = (UIButton *)pSender;
	int curItem = itemIdex->getTag();

	itemIdex->setTouchEnabled( false );

#if defined(DEMO_FOR_MOBILE)|| defined(DEMO_FOR_GUEST)
	if ( atoi(AnalyseJson::logOnMsg.lifeInfo.price.c_str()) > AnalyseJson::logOnMsg.baseInfo.gemNum)
	{
		CommonData::m_buytype = CANDY_PROP_LIFE;

		CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_50, MOBILE_MONEY5_BUY_LIFENUM);
	}
	else
	{
		MsgMgr::sendGemBuyLife( AnalyseJson::logOnMsg.baseInfo.id, MOBILE_GOURD_LIFENUM);
	}
#endif
}

void MainMapUiLayer::ItemCallBackCliamList(CCObject *pSender)
{
	UIImageView* pSelK = (UIImageView*)pSender;
	int index = pSelK->getTag();
	string ItemIdx = pSelK->getName();

	UIImageView* pSel = (UIImageView*)pSelK->getChildByName("Select");

	if ( pSel->isVisible() )
	{
		if ( 0 < m_ClaimLifeNum )
		{
			pSel->setVisible( false );
			m_ClaimLifeNum--;
		}
	}
	else
	{
		if ( 5 > m_ClaimLifeNum )
		{
			pSel->setVisible( true );	
			m_ClaimLifeNum++;
		}
	}
	char pStrClaimNum[2] = {0};
	sprintf(pStrClaimNum, "%d", m_ClaimLifeNum);
	UILabelAtlas* pCurCliamNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->CliamLifelayout->getChildByName("label_1"));
	pCurCliamNum->setStringValue( pStrClaimNum );
}

void MainMapUiLayer::BtnCallBackDelFriend(CCObject* pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* item = (UIButton*)pSender;
	int nfriendid = item->getTag();
	string itemname = item->getName();

	showMapWidget(MAP_WIDGET_SUCCEEDUI_DLG, PROMPT_TYPE_DELFRIEND, nfriendid);
}

void MainMapUiLayer::BtnCallBackBuyFriendLimit(CCObject* pSender)
{
	int nPrice = 0;
	std::list<UserPropInfoStr>::iterator item = AnalyseJson::logOnMsg.specialProp.begin();


	CommonData::CutSceneForGl();
	while ( item!=AnalyseJson::logOnMsg.specialProp.end()) 
	{
		if (item->id == CANDY_PROP_FRIEND_LIMIT )
		{
			nPrice = atoi( item->price.c_str() );
			if ( nPrice <= AnalyseJson::logOnMsg.baseInfo.gemNum )
			{
				AnalyseJson::logOnMsg.baseInfo.gemNum -= nPrice;
				MsgMgr::sendBuyFriendlimitForMsg( AnalyseJson::logOnMsg.baseInfo.id );
			}
			else
			{
				CommonData::m_buytype = CANDY_PROP_FRIEND_LIMIT;
				CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_50 ,MOBILE_MONEY5_BUY_PROPNUM);
			}
		}
		item++;
	}
}

// 向好友赠送生命
void MainMapUiLayer::BtnCallBackFriendList(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* item = (UIButton*)pSender;
	int index = item->getTag();
	string itemname = item->getName();
	item->disable( true );

	std::list<UserFriendInfoStr>::iterator p;
	p = AnalyseJson::friendInfoMsg.friendInfo.begin();

	for (int i = 0; i< (int)AnalyseJson::friendInfoMsg.friendInfo.size(); i++)
	{
		if (p->id == index)
		{
			CCNode* particle = CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(0,0));
			particle->setZOrder( 10 );
			item->getRenderer()->addChild( particle );

			MsgMgr::sendHandselLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, p->id);
			break;
		}
		p++;
	}
}

void MainMapUiLayer::BtnCallBackMessageList(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBtn	= (UIButton*)pSender;
	int index		= pBtn->getTag();
	int userid		= (int)pBtn->data;

	//　获取当前scrollview坐标
	UIScrollView*	pMessagelistView	= dynamic_cast<UIScrollView*>(m_mainmapuilayer->messageListLayout->getChildByName( "m_sv_messagelist_1" ));
	UIWidget*		pwidgt				= pMessagelistView->getInnerContainer();
	CCPoint			point				= pwidgt->getPosition();

	std::list<MessageNode>::iterator tem = m_mainmapuilayer->m_messagelist.begin();
	for (; tem!=m_mainmapuilayer->m_messagelist.end(); tem++)
	{
		if ( userid == tem->m_friendid )
			break;
	}

	switch(index)
	{
		//　the case type will remove!
	case MESSAGE_NOACCEPT_FRIEND:
		MsgMgr::sendNoAcceptAddFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id, tem->m_friendid);
		break;

		// 接受好友
	case MESSAGE_ACCEPT_FRIEND:
		{
			if ((int) AnalyseJson::friendInfoMsg.friendInfo.size() >= (int)AnalyseJson::friendInfoMsg.friendMaxNum )
			{
				showOtherPrompt( PROMPT_TYPE_NOADDFRIEND );
			}
			else
			{
				CCPoint pos = pBtn->getParent()->convertToWorldSpace(pBtn->getPosition());
				CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y), this);
				MsgMgr::sendAcceptAddFriendForGuestMsg( AnalyseJson::logOnMsg.baseInfo.id, tem->m_friendid );

				if ( !m_mainmapuilayer->m_messagelist.empty() )
					m_mainmapuilayer->m_messagelist.erase(tem);   

				pBtn->getParent()->removeFromParent();
				updataMessageList( point );
			}
		}
		break;

	case MESSAGE_ACCEPT_LIFE:
		{
			// 领取生命上限
			if ( AnalyseJson::getHandselMsg.heardLimit > 0)
			{
				CCPoint pos = pBtn->getParent()->convertToWorldSpace(pBtn->getPosition());
				CandyParticle::displayCandyParticle(CANDY_PARTICLE_ADDLIFE_EFFECT, ccp(pos.x, pos.y), this);
				MsgMgr::sendAcceptLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, tem->m_orderid, tem->m_friendid );

				AnalyseJson::getHandselMsg.heardLimit --;
				if ( !m_mainmapuilayer->m_messagelist.empty() )
					m_mainmapuilayer->m_messagelist.erase(tem);   
				pBtn->getParent()->removeFromParent();
				updataMessageList( point );
			}
			else
			{
				showOtherPrompt( PROMPT_TYPE_NOGETREWARD );
			}
		}
		break;
	}
}

// 返回键呼出菜单
void MainMapUiLayer::keyBackClicked()
{	
	// 这里处理连续按返回键时延时按键
	if ( !mDelayBackKey ) return;
	if ( mDelayBackKey )
	{
		mDelayBackKey = false;
		this->schedule(schedule_selector(MainMapUiLayer::UpdataDelayKey), 1.0f);
	}

	// 队列中存在widget时 先移出widget
	if ( widgetList.size() )
	{
		std::list<WidgetNode>::iterator p = widgetList.begin();
		if ( p->widget && p->widget->isVisible() )
		{
			MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
			QuitMapWidget();
		}

		m_isKey = false;
		return;
	}

	if ( !m_isEnableKey )
		return;

	if ( !m_isKey)
	{
		if (m_BackPageviewBtn->isVisible())
		{
			BackTopageview(NULL);
		}
		else
		{
			showMapWidget( MAP_WIDGET_SYSTEMTOOLS_DLG );
			m_isKey = true;
			m_isEnableKey = false;
		}
	}
	else
	{
		//SystemTools::CloseCallBackEx();	
		QuitMapWidget();
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
		m_isKey = false;
	}
}

#if defined(DEMO_FOR_GUEST)
void MainMapUiLayer::keyMenuClicked()
{	
	return;
	CCLog( "MainMapUiLayer::keyMenuClicked" );
	if ( !widgetList.empty() )
		CCLog( "MainMapUiLayer::keyMenuClicked  WidgetList.node:[%d]",  widgetList.begin()->type);

	if ( widgetList.size() )
	{
		std::list<WidgetNode>::iterator p = widgetList.begin();
		if ( p->widget->isVisible() )
			QuitMapWidget();

		m_isKey = false;
		return;
	}

	if ( !m_isEnableKey )
		return;

	if ( !m_isKey)
	{
		showMapWidget( MAP_WIDGET_SYSTEMTOOLS_DLG );
		m_isKey = true;
		m_isEnableKey = false;
	}
	else
	{
		SystemTools::CloseCallBackEx();	
		m_isKey = false;
	}
}
#endif

void MainMapUiLayer::runGemAnimation(void)
{
	//　序列帧动画
	char *animationImg = NULL;
	animationImg = (char*)"gem";

	UIButton* GamegemBut = dynamic_cast<UIButton*>(m_toolsT->getChildByName("gembtn"));

	CCSprite *plistSprite = CCSprite::createWithSpriteFrameName("gem1.png");
	plistSprite->setPosition( GamegemBut->getPosition() );
	plistSprite->setZOrder( 10 );
	plistSprite->setScale( 1.2f );
	m_toolsT->getRenderer()->addChild( plistSprite );

	CCArray *animFramesArray = CCArray::create();
	for(int i =1; i<9; i++)
	{
		CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
			CCString::createWithFormat("%s%d.png",animationImg,i)->getCString());
		animFramesArray->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFramesArray , 0.125f);

	plistSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

}


void MainMapUiLayer::PlayEffect(int index)
{
	MainMap::m_mainmap->PlayEffect(index);
}

void MainMapUiLayer::feedbackbutCallBack(CCObject *pSender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	UIButton* pBtn = (UIButton*)pSender;
	pBtn->setTouchEnabled( false );

	if (m_mainmapuilayer->m_feedbackstr.size() > 0)
	{
		MsgMgr::sendFeedbackMsg(AnalyseJson::logOnMsg.baseInfo.id, m_mainmapuilayer->m_feedbackstr);
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

		showMapWidget(MAP_WIDGET_SUCCEEDUI_DLG, PROMPT_TYPE_FEEDBACK);
	}
}

CCActionInterval *MainMapUiLayer::getEffectBezierAction(CCPoint originPos, CCPoint targetPos)
{
	const float offsetX = (targetPos.x-originPos.x)<100.0f?100.0f:0;
	const float moveTime = 1.0f;//sqrtf(ccpDistance(targetPos, originPos) *0.002f);	

	ccBezierConfig bezier; 
	bezier.controlPoint_1 = originPos; 
	bezier.controlPoint_2 = ccp((targetPos.x+originPos.x)*0.5f+rand()%2?offsetX:-offsetX,
		targetPos.y < originPos.y?originPos.y+100.0f:originPos.y-100.0f); 
	bezier.endPosition = targetPos; 

	return CCBezierTo::create(moveTime, bezier);
}

char* MainMapUiLayer::getDailyTexturesBtnBuyId( int claimid )
{	
	// CANDY_COLLECT_RED,		// 红		0
	// CANDY_COLLECT_BLUE,		// 蓝色		1
	// CANDY_COLLECT_GREEN,	// 绿色		2
	// CANDY_COLLECT_YELLOW,	// 黄色		3
	// CANDY_COLLECT_ORANGE,	// 橙色		4
	// CANDY_COLLECT_PURPLE,	// 紫色		5
	char* pCandy = NULL;
	switch( claimid )
	{
	case CANDY_COLLECT_RED:
		pCandy = (char*)"CandyRedNormal";
		break;
	case CANDY_COLLECT_PURPLE:
		pCandy = (char*)"CandyPurpleNormal";
		break;
	case CANDY_COLLECT_GREEN:
		pCandy = (char*)"CandyGreenNormal";
		break;
	case CANDY_COLLECT_YELLOW:
		pCandy = (char*)"CandyYellowNormal";
		break;
	case CANDY_COLLECT_BLUE:
		pCandy = (char*)"CandyBlueNormal";
		break;
	case CANDY_COLLECT_ORANGE:
		pCandy = (char*)"CandyOrangeNormal";
		break;
	}

	return (char*)CCString::createWithFormat("Image/Common/CandyIco/%s.png", pCandy)->getCString();


}

bool MainMapUiLayer::getMainTaskRewardStatus( void )
{
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
	for( ; item!=AnalyseJson::taskTable.mainTask.end(); item++ )
	{
		//　已完成目标　&& 未领取
		if ( item->targer <= AnalyseJson::logOnMsg.stageInfo.size() && 0 == item->status)
			return true;
	}
	return false;
}

bool MainMapUiLayer::getMainTaskLetRewardStatus( void )
{
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
	for( ; item!=AnalyseJson::taskTable.mainTask.end(); item++ )
	{
		//　已完成目标　&& 未领取　&&　已解锁
		if ( item->targer <= AnalyseJson::logOnMsg.stageInfo.size() && 0 == item->status && 0 == item->lockstate)
			return true;
	}
	return false;
}

bool MainMapUiLayer::getTaskLetRewardStatus( void )
{
	//　星星可领取
	if ( AnalyseJson::taskTable.startTask.size() )
	{
		std::list<SystemStarStarTask>::iterator staritem = AnalyseJson::taskTable.startTask.begin();
		if (AnalyseJson::taskTable.curstarnum - staritem->consumenum >= staritem->maxnum)	
			return true;
	}

	//　主线任务可领取
	std::list<SystemMainTask>::iterator item = AnalyseJson::taskTable.mainTask.begin();
	for( ; item!=AnalyseJson::taskTable.mainTask.end(); item++ )
	{
		//　已完成目标　&& 未领取　&&　已解锁
		if ( item->targer <= AnalyseJson::logOnMsg.stageInfo.size() && 0 == item->status && 0 == item->lockstate)
			return true;
	}

	//　日常任务可领取
	std::list<SystemDailyTask>::iterator dailyitem = AnalyseJson::taskTable.dailyTask.begin();
	for(; dailyitem != AnalyseJson::taskTable.dailyTask.end(); dailyitem++)
	{
		if ( dailyitem->targer <= dailyitem->complete && 0 == dailyitem->status)
			return true;
	}

	return false;
}

bool MainMapUiLayer::getMessagePropmtStatus( void )
{
	//　　let add friend  or have invite message  
	if ( ((int) AnalyseJson::friendInfoMsg.friendInfo.size() < (int)AnalyseJson::friendInfoMsg.friendMaxNum && AnalyseJson::InviteFriendMsgList.nofriend.size()) ||
		( AnalyseJson::getHandselMsg.heardLimit > 0 && AnalyseJson::getHandselMsg.handselMsg.size()) )
		return true;
	else
		return false;
}


void MainMapUiLayer::showBuyPrompt( int type )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if ( !m_BuyPrompt )
	{
		m_BuyPrompt = UIImageView::create();
		m_BuyPrompt->setZOrder( 1000 );
		m_BuyPrompt->setTexture("Image/MainMapUi/ImgBuyPromtp.png");
		m_BuyPrompt->setPosition( ccp(size.width/2,size.height*0.6));
		getWidgetUILayer()->addWidget( m_BuyPrompt );
	}
	
	//CCPoint pos = pBtn->getParent()->convertToWorldSpace(pBtn->getPosition());
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(size.width/2,size.height*0.6), this);

	CCActionInterval * spawn = CCSpawn::create(
		CCMoveTo::create(1.0f, ccp(size.width/2,size.height*0.6 + 150)),
		CCFadeOut::create(1.0f),
		NULL);

	m_BuyPrompt->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		spawn,
		CCCallFunc::create(this, callfunc_selector(MainMapUiLayer::FunCallBuyPromptAction)),
		NULL));
	
}

void MainMapUiLayer::showOtherPrompt( CandyPromptType type )
{
	if ( !m_FntPrompt )
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		char* pPromptStr = NULL;
		switch ( type )
		{
		case PROMPT_TYPE_CHANGEINFO:
			pPromptStr = (char*)CommonData::GetString( "app_changeinfoprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_VIPLIFE:
			pPromptStr = (char*)CommonData::GetString( "app_VIPlifeprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_VIPTASK:
			pPromptStr = (char*)CommonData::GetString( "app_VIPTaskprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_UNLOCKSTARTASK:
			pPromptStr = (char*)CommonData::GetString( "app_unlockstarTaskprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_UNLOCKMAINTASK:
			pPromptStr = (char*)CommonData::GetString( "app_unlockMainTaskrompt_str" ).c_str();
			break;

		case PROMPT_TYPE_UNLOCKMSGORFRIEND:
			pPromptStr = (char*)CommonData::GetString( "app_unlockMsgOrFriendprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_UNLOCKDAYTASK:
			pPromptStr = (char*)CommonData::GetString( "app_unlockdayTaskprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_FRIENDNUMLIMIT:
			pPromptStr = (char*)CommonData::GetString( "app_friendNumLimitprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_NOGETREWARD:
			pPromptStr = (char*)CommonData::GetString( "app_noGetRewardprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_NOADDFRIEND:
			pPromptStr = (char*)CommonData::GetString( "app_noAddfriendprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_RANKEDUP:
			pPromptStr = (char*)CommonData::GetString( "app_RankedUpprompt_str" ).c_str();
			break;

		case PROMPT_TYPE_SIGNINSUC:
			pPromptStr = (char*)CommonData::GetString( "app_signinsuc_str" ).c_str();
			break;

		}
		m_FntPrompt = UILabelBMFont::create();
		m_FntPrompt->setFntFile( "fonts/MapPrompt/font.fnt" );

		m_FntPrompt->setText( /*CCString::createWithFormat("%d",12)->getCString()*/pPromptStr );
		m_FntPrompt->setZOrder( 1000 );
		m_FntPrompt->setPosition( ccp(size.width/2,size.height*0.6));
		getWidgetUILayer()->addWidget( m_FntPrompt );

		CCActionInterval * spawn = CCSpawn::create(
			CCMoveTo::create(1.5f, ccp(size.width/2,size.height*0.6 + 80)),
			CCFadeOut::create(1.5f),
			NULL);

		m_FntPrompt->setScale( 0.8f );
		m_FntPrompt->runAction(CCSequence::create(
			CCScaleTo::create( 0.2f, 1.0f ),
			CCMoveTo::create(1.5f, ccp(size.width/2,size.height*0.6 + 40)),
			spawn,
			CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::FunCallOtherPromptAction), (void*)type),
			NULL));
	}
}

// 显示解锁提示
void MainMapUiLayer::showUnlockPrompt( CandyPromptType type , CCPoint pos)
{
	if ( !m_FntUnlockPrompt )
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		char* pPromptStr = NULL;
		switch ( type )
		{
		case PROMPT_TYPE_UNLOCK_STARTASK:			
			pPromptStr = (char*)CCString::createWithFormat(CommonData::GetString( "app_unlockfuntion_str" ).c_str(), AnalyseJson::unLockConfig.starTask)->getCString();   
			break;	
		case PROMPT_TYPE_UNLOCK_MAINTASK:
			pPromptStr = (char*)CCString::createWithFormat(CommonData::GetString( "app_unlockfuntion_str" ).c_str(), AnalyseJson::unLockConfig.mainTask)->getCString();   
			break;	
		case PROMPT_TYPE_UNLOCK_EVERYDAYTASK:
			pPromptStr = (char*)CCString::createWithFormat(CommonData::GetString( "app_unlockfuntion_str" ).c_str(), AnalyseJson::unLockConfig.dailyTask)->getCString();   
			break;	
		case PROMPT_TYPE_UNLOCK_FRIEND:
			pPromptStr = (char*)CCString::createWithFormat(CommonData::GetString( "app_unlockfuntion_str" ).c_str(), AnalyseJson::unLockConfig.friendFun)->getCString();   
			break;
		case PROMPT_TYPE_UNLOCK_VIP:
			pPromptStr = (char*)CommonData::GetString( "app_viplunlock_str" ).c_str();
			break;		
		}
		m_FntUnlockPrompt = UILabelBMFont::create();
		m_FntUnlockPrompt->setFntFile( "fonts/UnLockPrompt/font.fnt" );

		m_FntUnlockPrompt->setText( pPromptStr );
		m_FntUnlockPrompt->setZOrder( 1000 );
		m_FntUnlockPrompt->setPosition( ccpAdd(pos, ccp(0, 50) ) );
		getWidgetUILayer()->addWidget( m_FntUnlockPrompt );

		m_FntUnlockPrompt->runAction(CCSequence::create(
			CCEaseElasticOut::create((CCActionInterval*)CCMoveTo::create(1.5f, ccpAdd(pos, ccp(0, 100)) ),0.3f ),
			CCSpawn::create(CCMoveTo::create(0.8f, ccpAdd(pos, ccp(0, 150))),CCFadeOut::create(0.8f),NULL),
			CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::FunCallUnlockPromptAction), (void*)type),
			NULL));
	}
}

void MainMapUiLayer::FunCallBuyPromptAction()
{
	m_BuyPrompt->removeFromParent();
	m_BuyPrompt = NULL;
}

void MainMapUiLayer::FunCallOtherPromptAction(CCNode* sender, void* data)
{
	int type = (int)data;
	m_FntPrompt->removeFromParent();
	m_FntPrompt = NULL;

	switch ( type )
	{
	case PROMPT_TYPE_CHANGEINFO:
		break;

	case PROMPT_TYPE_VIPLIFE:
		break;

	case PROMPT_TYPE_VIPTASK:
		break;

	case PROMPT_TYPE_UNLOCKSTARTASK:
		break;

	case PROMPT_TYPE_UNLOCKMAINTASK:
		break;

	case PROMPT_TYPE_UNLOCKMSGORFRIEND:
		break;

	case PROMPT_TYPE_UNLOCKDAYTASK:
		break;

	case PROMPT_TYPE_FRIENDNUMLIMIT:
		break;

	case PROMPT_TYPE_NOGETREWARD:
		break;

	case PROMPT_TYPE_NOADDFRIEND:
		{
			QuitMapWidget( MAP_WIDGET_FRIEND_LIST );
			//showMapWidget( MAP_WIDGET_FRIEND_LIST );
		}
		break;

	}
}


void MainMapUiLayer::FunCallUnlockPromptAction(CCNode* sender, void* data)
{
	int type = (int)data;
	m_FntUnlockPrompt->removeFromParent();
	m_FntUnlockPrompt = NULL;

}

void MainMapUiLayer::setDailyTask( void )
{
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for(int i = 1; i<=AnalyseJson::taskTable.dailyTask.size(); i++ ,item++)
	{
		// 防止服务器多下发日常数据
		if ( 2 < i ) break;

		if ( 1 == item->status)
		{
			const char* pPanelTask = CCString::createWithFormat("PanelTask%d", i)->getCString();
			UIPanel* PanelTask = dynamic_cast<UIPanel*>(m_mainmapuilayer->mapToolbarlayout->getChildByName( pPanelTask )); 
			if ( PanelTask )
				PanelTask->removeFromParent();

			continue;
		}

		const char* pStrBut = CCString::createWithFormat("btnDailyTask%d", i)->getCString();
		const char* pStrLodingBar = CCString::createWithFormat("LoadingBarTask%d", i)->getCString();
		const char* pStrLodLabel = CCString::createWithFormat("LabelDailyTask%d", i)->getCString();
		const char* pStrPanel = CCString::createWithFormat("PanelTask%d", i)->getCString();
		const char* pStrVipLock = CCString::createWithFormat("ImgVipBg%d", i)->getCString();
		const char* pStrlodingbg = CCString::createWithFormat("Imagelodbg%d", i)->getCString();
		const char* pStrVip = CCString::createWithFormat("ImgVipTips%d", i)->getCString();
		const char* pStrLevel = CCString::createWithFormat("LabelLevelnum%d", i)->getCString();

		UIPanel* m_PanelTask = dynamic_cast<UIPanel*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrPanel)); 

		if ( !m_PanelTask ) continue;

		UIButton* m_DailyTaskBut = dynamic_cast<UIButton*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrBut)); 
		UILoadingBar* m_LodingBar = dynamic_cast<UILoadingBar*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrLodingBar)); 
		UILabel* m_LodingLabel = dynamic_cast<UILabel*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrLodLabel)); 
		UIImageView* m_VipLock = dynamic_cast<UIImageView*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrVipLock)); 
		UIImageView* m_StrVipLock = dynamic_cast<UIImageView*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrVip)); 
		UIImageView* m_Lodingbg = dynamic_cast<UIImageView*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrlodingbg)); 
		UILabelAtlas* m_LevelNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->mapToolbarlayout->getChildByName(pStrLevel)); 

		m_StrVipLock->setVisible( false );
		m_VipLock->setVisible( false );
		m_LevelNum->setVisible( false );

		float nPercent = 0;
		// 星星收集日常
		nPercent =(float)item->complete /(float)item->targer;
		const char* pStrPercent = CCString::createWithFormat("%d/%d",item->complete, item->targer)->getCString();
		m_LodingLabel->setText( pStrPercent );//进度文字
		m_LodingBar->setPercent( nPercent * 100 );// 进度表示
		m_DailyTaskBut->setTouchEnabled( true );
		m_DailyTaskBut->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::toolsMenuCallback));

		m_DailyTaskBut->data = (void*)item->taskid;

		m_PanelTask->setTag( item->taskid );

		// 糖果收集日常 并未领取
		if ( 1 == item->type && 0 == item->status)
		{
			char* pBtnTextures = NULL;

			if ( item->targer > item->complete )
			{
				pBtnTextures = getDailyTexturesBtnBuyId(item->claimid );				
			}
			// 已达成目标
			else
			{
				m_LodingLabel->setText( CommonData::GetString("app_taskfinish_str").c_str() );
				pBtnTextures = (char*)CCString::createWithFormat("%s", "Image/MainMapUi/buyItem/map_gamico1.png")->getCString();
				m_DailyTaskBut->runAction( getTaskMsgTipsAction() );
				createLeftImgPrompt( m_PanelTask->getParent()->getRenderer()->convertToNodeSpace(m_DailyTaskBut->getParent()->convertToWorldSpace(m_DailyTaskBut->getPosition())), m_DailyTaskBut->getName() );
				m_Lodingbg->setVisible( false );
			}

			m_DailyTaskBut->setTextures(pBtnTextures, pBtnTextures, pBtnTextures);
			m_DailyTaskBut->setTag( TAG_DAILYTASK_GETCANDY_TOOLSMENU_TIEM );


			// VIP锁定 但 未解锁
			if ( 1 == item->lockstate && 1 == item->isVipTask&& 0 == AnalyseJson::logOnMsg.baseInfo.isVip)	
			{
				m_Lodingbg->setVisible( false );
				m_VipLock->setVisible( true );
			}

		}
		// 关卡完成日常
		else if ( 2 == item->type && 0 == item->status )
		{			
			// 已完成 未领取
			if ( item->targer <= item->complete )
			{
				char* pBtnTextures = NULL;
				m_LodingLabel->setText( CommonData::GetString("app_taskfinish_str").c_str() );
				pBtnTextures = (char*)CCString::createWithFormat("%s", "Image/MainMapUi/buyItem/map_gamico1.png")->getCString();
				m_DailyTaskBut->setTextures(pBtnTextures, pBtnTextures, pBtnTextures);
				m_DailyTaskBut->runAction( getTaskMsgTipsAction() );
				createLeftImgPrompt(m_DailyTaskBut->getPosition(), m_DailyTaskBut->getName() );
				m_Lodingbg->setVisible( false );
			}
			// 未完成
			else
			{
				m_LevelNum->setVisible( true );
				m_LevelNum->setStringValue( CCString::createWithFormat("%d", item->claimid)->getCString() );
				m_DailyTaskBut->isEffects( true );
			}

			m_DailyTaskBut->setTag( TAG_DAILYTASK_TARGETLEVEL_TOOLSMENU_TIEM );

			// 未解锁	是VIP任务	
			if ( 1 == item->isVipTask && 0 == AnalyseJson::logOnMsg.baseInfo.isVip)	
			{
				m_Lodingbg->setVisible( false );
				m_VipLock->setVisible( true );
			}	
			//else if ( 0 == item->lockstate && 1 == item->isVipTask)
			//	m_StrVipLock->setVisible( true );

		}
		else
		{
			m_PanelTask->removeFromParent();
		}

	}

	/*UIPanel* m_PanelTask1 = dynamic_cast<UIPanel*>(mapToolbarlayout->getChildByName("PanelTask1")); 
	UIPanel* m_PanelTask2 = dynamic_cast<UIPanel*>(mapToolbarlayout->getChildByName("PanelTask2")); 
	if ( !m_PanelTask1 && m_PanelTask2 ) m_PanelTask2->setPosition( ccpSub(m_PanelTask2->getPosition(), ccp(0,-120)));*/
}

void MainMapUiLayer::buyUnlockMainTask(int buyprice)
{
	int tem = buyprice;//AnalyseJson::logOnMsg.baseInfo.gemNum > 

	CommonData::m_buytype = CANDY_PROP_UNLACK_MAINTASK;
	if(tem <= 10)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_10, 1);
	}
	else if(tem>10 && tem<=20)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_20, 1);
	}
	else if(tem>20 && tem<=30)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_30, 1);
	}
	else if(tem>30 && tem<=50)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_50, 1);
	}
	else if(tem>50 && tem<=80)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_80, 1);
	}
	else if(tem>80 && tem<=100)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_100, 1);
	}
	else if(tem>100 && tem<=200)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_200, 1);
	}
	else if(tem>200 && tem<=320)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_320, 1);
	}
	else if(tem>320 && tem<=588)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_588, 1);
	}
	else if(tem>588 && tem<=1288)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_1288, 1);
	}
	else if(tem>1288 && tem<=2588)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_2588, 1);
	}
}

void MainMapUiLayer::createLeftImgPrompt( CCPoint pos, const char* name )
{
	UIImageView* pLeftBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_leftIco"));
	if ( !pLeftBar )
		return;

	char pTagname[20];
	sprintf(pTagname, "%sprompt", name );
	UIImageView* pPromptImg = UIImageView::create();
	pPromptImg->setName( pTagname );
	pPromptImg->setTexture( "Image/MainMapUi/ImgLeftJiantou.png" );
	pPromptImg->setPosition( ccpAdd( pos, ccp(150, 30)));
	
	pPromptImg->runAction(CCRepeatForever::create(CCSequence::create(
		CCMoveTo::create(0.5f, ccpAdd(pos, ccp(100, 30))),
		CCMoveTo::create(0.5f, ccpAdd(pos, ccp(150, 30))),
		NULL)));

	pLeftBar->addChild( pPromptImg );
}

void MainMapUiLayer::createDownImgPrompt( CCPoint pos, const char* name )
{

	UIImageView* pRightBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_downIco"));
	if ( !pRightBar || MainMapUiLayer::m_mainmapuilayer->messageListLayout )
		return;

	char pTagname[20];
	sprintf(pTagname, "%sprompt", name );

	UIImageView* pPromptImg = UIImageView::create();
	pPromptImg->setName( pTagname );
	pPromptImg->setTexture( "Image/MainMapUi/ImgLeftJiantou.png" );
	pPromptImg->setRotation( 270 );
	pPromptImg->setPosition( ccpAdd( pos, ccp(0, 150)));

	pPromptImg->runAction(CCRepeatForever::create(CCSequence::create(
		CCMoveTo::create(0.5f, ccpAdd(pos, ccp(0, 100))),
		CCMoveTo::create(0.5f, ccpAdd(pos, ccp(0, 150))),
		NULL)));

	pRightBar->addChild( pPromptImg );
}

void MainMapUiLayer::addEveryDayTaskToList( void )
{
	if ( !m_mainmapuilayer->tasklayout )
		return;

	UIScrollView* plistView = dynamic_cast<UIScrollView*>(m_mainmapuilayer->tasklayout->getChildByName( "ScrollList2" ));
	CCSize scrollSize = plistView->getContentSize();
	plistView->removeAllChildrenAndCleanUp( true );
	int nListLen = AnalyseJson::taskTable.dailyTask.size();
	CCSize itemPoint;

	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();

	ClipWidth = scrollSize.width;
	ClipHeight = nListLen * 140;

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	plistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	plistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 140/2;

	int nOffset = 0;
	bool isCurTask = false;
	for (int i = 0; i<nListLen; i++)
	{
		// m_friendlist

		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setScale9Enabled( true );
		pItemImg->setName(  CCString::createWithFormat("item%d", item->taskid)->getCString() );
		pItemImg->setScale9Size( CCSizeMake(600, 134));
		pItemImg->setVisible( true );
		pItemImg->setTag( item->taskid );
		pItemImg->setName(  CCString::createWithFormat("item%d", item->taskid)->getCString() );
		pItemImg->setPosition(ccp(ClipWidth / 2, butMPointY));
		pItemImg->setTouchEnabled( true );
		pItemImg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackEveryDayTaskItem));
		plistView->addChild( pItemImg );
		butMPointY -= ( 140  );

		UIImageView* pItemBgL = UIImageView::create();
		pItemBgL->setTexture( "res_task/ListItemBg1.png", UI_TEX_TYPE_PLIST );
		pItemBgL->setAnchorPoint( ccp(1.0f, 0.5f) );
		pItemImg->addChild( pItemBgL );

		UIImageView* pItemBgR = UIImageView::create();
		pItemBgR->setTexture( "res_task/ListItemBg1.png", UI_TEX_TYPE_PLIST );
		pItemBgR->setAnchorPoint( ccp(0.0f, 0.5f) );
		pItemBgR->setFlipX( true );
		pItemImg->addChild( pItemBgR );

		UILabelBMFont* pTaskTitle = UILabelBMFont::create();

		if ( 1 == item->lockstate )
			pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt3/font.fnt" );
		else
			pTaskTitle->setFntFile( "Image/MainMapUi/MainMapUi/font/TaskFnt2/font.fnt" );

		pTaskTitle->setText(  item->explain.c_str() );
		pTaskTitle->setPosition( ccp(0, 0));
		pItemImg->addChild( pTaskTitle );

// 		UITextButton* pBtnItem = UITextButton::create();
// 		pBtnItem->setNormalTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setPressedTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setDisabledTexture( "res_task/ImgScale9_5.png", UI_TEX_TYPE_PLIST );
// 		pBtnItem->setTouchEnabled( true );
// 		pBtnItem->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackEveryDayTaskItem));
// 		pBtnItem->setScale9Enable( true );
// 		pBtnItem->setScale9Size( CCSizeMake(550, 120));
// 		pBtnItem->setTag( item->taskid );
// 		pBtnItem->setName(  CCString::createWithFormat("item%d", item->taskid)->getCString() );
// 		pBtnItem->setPosition(ccp(0,0));
// 
// 		pBtnItem->setFontSize( 50 );
// 		pBtnItem->setFontName("黑体");
// 		pBtnItem->setTextColor( 255,255,255 );
// 		pBtnItem->setText( item->explain.c_str() );
// 		pItemImg->addChild( pBtnItem );

		UILabel* pLabelTimeText = UILabel::create();
		pLabelTimeText->setFontSize( 25 );
		//pLabelTimeText->setFontName( "黑体" );
		pLabelTimeText->setText( CommonData::GetString( "app_sytime_str" ).c_str() );
		pLabelTimeText->setPosition( ccp(100, -40) );
		pItemImg->addChild( pLabelTimeText );

		UILabelAtlas* pLabelTimeTask = UILabelAtlas::create();
		pLabelTimeTask->setName( CCString::createWithFormat("LabelDatiyTimeTask%d", item->taskid )->getCString() );
		pLabelTimeTask->setProperty("0" , "Image/MainMapUi/MainMapUi/res_common/NumLabel1.png",28, 40, "-"); 
		pLabelTimeTask->setStringValue( CCString::createWithFormat("%d",  0)->getCString() ); 
		pLabelTimeTask->setPosition( ccp(210, -40) );
		pLabelTimeTask->setScale( 0.45f );
		pItemImg->addChild( pLabelTimeTask );

		if ( item->isVipTask && 0 == AnalyseJson::logOnMsg.baseInfo.isVip )
		{
			//　VIP锁
			UIImageView* pTaskLockL = UIImageView::create();
			pTaskLockL->setTexture( "res_task/ImgTasklock.png", UI_TEX_TYPE_PLIST );
			pTaskLockL->setPosition( ccp(-230, 20));
			pTaskLockL->setScale( 0.8f );
			pTaskLockL->setName( "taskLockL" );
			pItemImg->addChild( pTaskLockL );

			UIImageView* psign3 = UIImageView::create();
			psign3->setTexture( "Image/MainMapUi/buyItem/ImgVipIco.png" );
			psign3->setName( "gemico" );
			psign3->setZOrder( 500 );
			psign3->setScale( 0.6f );
			psign3->setPosition(ccp( 0, -60));
			pTaskLockL->addChild( psign3 );


		}

		item++;
	}
}

void MainMapUiLayer::BtnCallBackEveryDayTaskItem( CCObject *pSender )
{
	UIButton* pBtnItem = (UIButton*)pSender;
	int nTaskid = pBtnItem->getTag();

	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	do 
	{
		if ( item->taskid != nTaskid )
		{
			item++;
			continue;;
		}	

		if ( 1 == item->isVipTask && 0 == AnalyseJson::logOnMsg.baseInfo.isVip )
		{
			QuitMapWidgetCallback();
			showMapWidget( MAP_WIDGET_VIP_DLG );
		}
		else
		{
			setEveryDayTaskInfo( nTaskid );
		}

		break;
	} while ( item!=AnalyseJson::taskTable.dailyTask.end());
}

void MainMapUiLayer::setEveryDayTaskInfo( int taskid )
{
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	do 
	{
		if ( item->taskid != taskid )
		{
			item++;
			continue;;
		}	
		UILabelBMFont* pLabelEveryDayTaskTitle = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->tasklayout->getChildByName( "LabelTaskInfoEveryDayTask" ));
		pLabelEveryDayTaskTitle->setText(  item->explain.c_str() );

		UIPanel* pPanelTaskInfo = dynamic_cast<UIPanel*>(m_mainmapuilayer->tasklayout->getChildByName( "PanelTaskInfo_0" ));
		pPanelTaskInfo->setVisible( true );
		pPanelTaskInfo->setTouchEnabled( true );

		UIImageView* pBtnTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImageStarTaskItem" ));
		pBtnTask->setTouchEnabled( true );
		pBtnTask->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackEveryDayTaskInfo));

		UILabelAtlas* pAtlasPropNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->tasklayout->getChildByName("AtlasPropNum_0_0"));
		pAtlasPropNum->setStringValue( CCString::createWithFormat("%d", item->gemnum )->getCString() );

		UIButton* pBtnRewardProp = dynamic_cast<UIButton*>(m_mainmapuilayer->tasklayout->getChildByName( "btnRewardProp_0_0" ));
		pBtnRewardProp->setTouchEnabled( true );
		pBtnRewardProp->isEffects( true );
		pBtnRewardProp->setTag( taskid );
		pBtnRewardProp->active();
		pBtnRewardProp->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::BtnCallBackEveryDayTaskRewar));

		UILabelAtlas* pLabelCurGetCandy = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->tasklayout->getChildByName("LabelCurGetCandy"));
		pLabelCurGetCandy->setStringValue( CCString::createWithFormat("%d/%d", item->complete, item->targer )->getCString() );

		UILabel* pLabTaskTarget1 = dynamic_cast<UILabel*>(m_mainmapuilayer->tasklayout->getChildByName( "LabelTaskTarget1" ));
		UILabel* pLabTaskTarget2 = dynamic_cast<UILabel*>(m_mainmapuilayer->tasklayout->getChildByName( "LabelTaskTarget2" ));


		pLabTaskTarget1->setVisible( false );
		pLabTaskTarget2->setVisible( false );

		if ( 1 == item->type )
		{
			pLabTaskTarget1->setVisible( true );
			pLabTaskTarget2->setVisible( false );

			UILabelAtlas* pNendGetNum = dynamic_cast<UILabelAtlas*>(m_mainmapuilayer->tasklayout->getChildByName("LabelGetMaxCandy"));
			UIImageView* pImgCandyType = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName("ImgCandyType"));

			pNendGetNum->setStringValue( CCString::createWithFormat("%d", item->targer )->getCString() );
			pImgCandyType->setTexture( getDailyTexturesBtnBuyId( item->claimid ) );
		}
		else if ( 2 == item->type )
		{
			pLabTaskTarget1->setVisible( false );
			pLabTaskTarget2->setVisible( true );

			pLabTaskTarget2->setText( item->explain.c_str() );

		}

		// 糖果收集日常 并未领取
		if ( 0 == item->status)
		{
			//　未完成目标
			if ( item->targer > item->complete )
			{
				pBtnRewardProp->disable( true );
			}
		}
		else
		{
			pBtnRewardProp->disable( true );
		}


		break;
	} while ( item!=AnalyseJson::taskTable.dailyTask.end());
}

void MainMapUiLayer::BtnCallBackEveryDayTaskRewar( CCObject *pSender )
{
	UIButton* pBtnRewar = (UIButton*)pSender;
	int nTaskid = (int)pBtnRewar->getTag();

	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for(; item != AnalyseJson::taskTable.dailyTask.end(); item++)
	{
		if (nTaskid == item->taskid)
		{
			/*{
				UIButton* GamegemBut = dynamic_cast<UIButton*>(mapToolbarlayout->getChildByName("gembtn"));
				CCPoint tem1 = pBtnRewar->getParent()->convertToWorldSpace(pBtnRewar->getParent()->getChildByName("ImgPropIco_0_0")->getPosition());
				CCPoint tem0 = GamegemBut->getParent()->convertToWorldSpace( GamegemBut->getPosition() );
				CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/buyItem/map_gamico.png")->getCString() );

				if(pPropIco != NULL)
				{
					pPropIco->setScale(1.6f);
					pPropIco->setPosition( tem1 );
					getWidgetUILayer()->addChild(pPropIco,232);

					pPropIco->runAction(CCSequence::create(	
						CCSpawn::create(
						getEffectBezierAction(tem1, tem0),
						CCScaleTo::create(1.2f, 0.2f),
						NULL),
						CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::DailyTaskActionCallBack), (void*)item->taskid),
						NULL
						));
				}

#ifdef CANDY_STATISITICAL_DATA
				AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4014, CCString::createWithFormat("%d", CandyManager::currentLevel)->getCString() );
#endif
			}*/
			break;
		}
	}
}

void MainMapUiLayer::BtnCallBackEveryDayTaskInfo( CCObject *pSender )
{
	setTaskLable( 3 );

	UIImageView* pBtnTask = dynamic_cast<UIImageView*>(m_mainmapuilayer->tasklayout->getChildByName( "ImageStarTaskItem" ));
	pBtnTask->setTouchEnabled( false );
}

void MainMapUiLayer::BtnCallBackMyInformat( CCObject *pSender )
{
	UIWidget* pItem = (UIWidget*)pSender;
	int tag = pItem->getTag();

	UIImageView* pLableSel = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable1N"));

	switch ( tag )
	{
	case 0:
		{
			PlayEffect(MUSIC_ITEM_BUTTON_E);
			pItem->setTouchEnabled( false );
			QuitMapWidget();
		}
		break;

	case 1:
		{
			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			setMyInformatLable( 1 );
		}
		break;

	case 2:
		{
			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			setMyInformatLable( 2 );
		}
		break;

	}

}

void MainMapUiLayer::setMyInformatLable( int index )
{

	UIPanel* pPanelLable1 = dynamic_cast<UIPanel*>(m_mainmapuilayer->myInformatlayout->getChildByName("PanelLable1"));
	UIPanel* pPanelLable2 = dynamic_cast<UIPanel*>(m_mainmapuilayer->myInformatlayout->getChildByName("PanelLable2"));

	UIImageView* pLableSel = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable1N"));

	CCPoint nOriginPos = ccp( -295, -314 );
	CCPoint nMoveTo = ccp( 1000, -339 );
	switch ( index )
	{
	case 1:
		{
			UIImageView* pLable1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable1P"));
			pLableSel->runAction( CCMoveTo::create( 0.1f, ccp(pLable1->getPosition().x, pLableSel->getPosition().y)));

			pPanelLable1->setVisible( true );
			pPanelLable2->setVisible( false );

			pPanelLable1->setPosition( nOriginPos );
			pPanelLable2->setPosition( nMoveTo );

			InitMyInformatLable1();
		}
		break;

	case 2:
		{
			UIImageView* pLable2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("ImgLable2P"));
			pLableSel->runAction( CCMoveTo::create( 0.1f, ccp(pLable2->getPosition().x, pLableSel->getPosition().y)));
			pPanelLable1->setVisible( false );
			pPanelLable2->setVisible( true );

			pPanelLable1->setPosition( nMoveTo );
			pPanelLable2->setPosition( nOriginPos );

			InitMyInformatLable2();
		}
		break;
	}
}

void MainMapUiLayer::initChangeInfoLayout(void)
{
	UIImageView *psexSel1 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("selsexboy"));
	UIImageView *psexSel2 = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("selsexgirl"));

	if ( 0 == AnalyseJson::logOnMsg.baseInfo.gender)
	{
		psexSel1->setTouchEnabled(true);
		psexSel2->setTouchEnabled(false);

		psexSel1->setVisible(true);
		psexSel2->setVisible(false);
	}
	else
	{
		psexSel1->setTouchEnabled(false);
		psexSel2->setTouchEnabled(true);
		psexSel1->setVisible(false);
		psexSel2->setVisible(true);
	}

	UIImageView* layout = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("selectnamebg"));
	UINodeContainer* nodeContainer = UINodeContainer::create();
	nodeContainer->setPosition(ccp(0,0));

	CCSize editBoxSize = layout->getContentSize();
	m_pEditBox = CCEditBox::create(CCSizeMake(344, 79), CCScale9Sprite::create("Image/MainMapUi/editboxBG.png"));
	m_pEditBox->setFontSize(20);
	m_pEditBox->setTag(EDITBOX_TYPE_CHANGERINFO);
	m_pEditBox->setMaxLength( 10 );
	m_pEditBox->setTouchPriority( -1 );
	m_pEditBox->setFontColor(ccc3(216, 141, 70));
	m_pEditBox->setPlaceholderFontColor(ccc3(216, 141, 70/*0,0,0*/));
	m_pEditBox->setPlaceHolder( "");
	m_pEditBox->setInputMode(kEditBoxInputModeSingleLine);
	m_pEditBox->setDelegate(this); 
	m_pEditBox->setReturnType(kKeyboardReturnTypeDone);  
	nodeContainer->addCCNode(m_pEditBox);

	layout->addChild( nodeContainer );

	////
	UIImageView* layout_qq = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName("selectqqbg"));
	UINodeContainer* nodeContainer_qq = UINodeContainer::create();
	nodeContainer_qq->setPosition(ccp(0,0));

	CCSize editBoxSize_q = layout_qq->getContentSize();
	m_pEditBox = CCEditBox::create(CCSizeMake(344, 79), CCScale9Sprite::create("Image/MainMapUi/editboxBG.png"));
	m_pEditBox->setFontSize(20);
	m_pEditBox->setTag(EDITBOX_TYPE_QQINFO);
	m_pEditBox->setMaxLength( 10 );
	m_pEditBox->setTouchPriority( -1 );
	m_pEditBox->setFontColor(ccc3(216, 141, 70));
	m_pEditBox->setPlaceholderFontColor(ccc3(216, 141, 70/*0,0,0*/));
	m_pEditBox->setPlaceHolder( "");
	m_pEditBox->setInputMode(kEditBoxInputModePhoneNumber);
	m_pEditBox->setDelegate(this); 
	m_pEditBox->setReturnType(kKeyboardReturnTypeDone);  
	nodeContainer_qq->addCCNode(m_pEditBox);

	layout_qq->addChild( nodeContainer_qq );
}

void MainMapUiLayer::InitMyInformatLable1( void )
{
	UIImageView* pSexboy = dynamic_cast<UIImageView*>(myInformatlayout->getChildByName("selsexboy"));
	UIImageView* pSexgirl = dynamic_cast<UIImageView*>(myInformatlayout->getChildByName("selsexgirl"));
	pSexboy->setTag(SEX_BOY_BUT);
	pSexgirl->setTag(SEX_GIRL_BUT);
	pSexboy->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::SexBtnCallBack));
	pSexgirl->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::SexBtnCallBack));

	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;

	UIButton *SubmitButton = dynamic_cast<UIButton*>(m_mainmapuilayer->myInformatlayout->getChildByName("m_btu_submit"));
	SubmitButton->setTouchEnabled(true);
	SubmitButton->setTag( 1 );
	SubmitButton->isEffects( true, nDelayTime1 + nDelayTime2*2 );
	SubmitButton->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::ChangeInfoButCallBack));
	if( AnalyseJson::logOnMsg.baseInfo.avatar_upd_times !=0)
	{
		SubmitButton->setTextures("Image/CandyGame/Others/HeadPay.png","Image/CandyGame/Others/HeadPayP.png","Image/CandyGame/Others/HeadPayP.png");
	}
	else
	{
		SubmitButton->setTextures("changeinfo/ButtonConfirmN.png","changeinfo/ButtonConfirmP.png","changeinfo/ButtonConfirmP.png");
	}

	UILabel* pNiceName = dynamic_cast<UILabel*>(m_mainmapuilayer->myInformatlayout->getChildByName("inputnickname"));
	pNiceName->setScale( 0.7f );
	pNiceName->setText(AnalyseJson::logOnMsg.baseInfo.nickName.c_str());

	UILabel* pQQ = dynamic_cast<UILabel*>(m_mainmapuilayer->myInformatlayout->getChildByName("inputqq"));
	pQQ->setScale( 0.7f );
	if(AnalyseJson::logOnMsg.baseInfo.qq.size() != 0)
	{
		pQQ->setText(AnalyseJson::logOnMsg.baseInfo.qq.c_str());
	}
	else
	{
		pQQ->setText("");
	}
	UIImageView *pHead = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->myInformatlayout->getChildByName("selectheadico_1"));
	char* headname = (char*)CCString::createWithFormat("%s%d.png", AnalyseJson::CandPicPath,AnalyseJson::logOnMsg.baseInfo.id)->getCString();
	if(!CCFileUtils::sharedFileUtils()->isFileExist(headname))
	{
		std::string headPath = CommonData::getHeadPathForUrl( AnalyseJson::logOnMsg.baseInfo.headPicUrl);
		pHead->setTexture(headPath.c_str());
	}
	else
	{
		pHead->setTexture(headname);
	}
	pHead->setTouchEnabled(true);
	pHead->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::uploadHead));


}

void MainMapUiLayer::InitMyInformatLable2( void )
{
	std::list<UserPropInfoStr>::iterator p  = AnalyseJson::logOnMsg.propInfo.begin();
	int j = 0;
	for (unsigned int i = 0; i < AnalyseJson::logOnMsg.propInfo.size(); i++)
	{
		// 32 为头像道具
		if ( 0 < p->num && 32 != p->id)
		{
			j++;

			UIImageView* pPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName( CCString::createWithFormat( "ImgPropBg_%d", j)->getCString() ));
			pPropBg->setTouchEnabled(true);
			pPropBg->setTag( p->id );
			pPropBg->addReleaseEvent(this, coco_releaseselector(MainMapUiLayer::knapsackBtnCallBack));
			pPropBg->removeAllChildren();

			UIImageView* pPropIco = UIImageView::create();
			pPropIco->setPosition( ccp(0, -5) );
			pPropIco->setTexture( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", p->id)->getCString() );
			pPropIco->setVisible( true );
			pPropBg->addChild( pPropIco );

			UIImageView* pPropNumBg = UIImageView::create();
			pPropNumBg->setTexture( "Image/MainMapUi/m_imgbg_propnum.png" );
			pPropNumBg->setVisible( true );
			pPropNumBg->setPosition( ccp(30 , -40) );
			pPropBg->addChild( pPropNumBg );

			UILabelBMFont *socreLabel = UILabelBMFont::create();
			socreLabel->setFntFile( "fonts/Score3/font.fnt" );
			socreLabel->setText( CCString::createWithFormat("%d",p->num)->getCString() );
			socreLabel->setScale( 0.7f );
			socreLabel->setAnchorPoint( ccp(0.5f, 0.5f) );
			socreLabel->setPosition( ccp(0,-8));
			pPropNumBg->addChild( socreLabel );
		}

		p++;
	}

	UIImageView* pSelectK = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName( "ImgSeletK" ));
	UILabelBMFont* pPropExpain = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->myInformatlayout->getChildByName( "FntPropexpain" ));
	UILabelBMFont* pPropExpain1 = dynamic_cast<UILabelBMFont*>(m_mainmapuilayer->myInformatlayout->getChildByName( "FntPropexpain1" ));
	if ( j == 0 )
	{
		pPropExpain->setVisible( false );
		pPropExpain1->setVisible( false );
		pSelectK->setVisible( false );
	}
	else
	{
		UIImageView* pPropBg = dynamic_cast<UIImageView*>(m_mainmapuilayer->myInformatlayout->getChildByName( "ImgPropBg_1" ));
		if ( 32 != pPropBg->getTag())
		{
			pSelectK->setPosition( ccp(pPropBg->getPosition().x, pPropBg->getPosition().y - 10) );
			pPropExpain->setText(CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain1_forknapsack", pPropBg->getTag() )->getCString()).c_str());
			pPropExpain1->setText( CommonData::GetString(CCString::createWithFormat( "app_prop%d_expain2_forknapsack", pPropBg->getTag() )->getCString()).c_str());
		}

	}
}

void MainMapUiLayer::updataWorldRankedNumber( float t )
{
	static int nCurBS = 0;
	unsigned int nMyWorld= (AnalyseJson::logOnMsg.baseInfo.myWorldRanked / 20)* nCurBS;

	if ( nMyWorld > AnalyseJson::logOnMsg.baseInfo.myWorldRanked )
	{ 
		nMyWorld = AnalyseJson::logOnMsg.baseInfo.myWorldRanked ; 
		nCurBS = 0;
		this->unschedule( schedule_selector(MainMapUiLayer::updataWorldRankedNumber) );
	}
	else
	{
		nCurBS++;
	}

	//　世界排名
	/*UILabelBMFont* pMyWorldRanked = dynamic_cast<UILabelBMFont*>( MainMapUiLayer::mapToolbarlayout->getChildByName("FntAtlasMyRank")); 
	pMyWorldRanked->setText( CCString::createWithFormat("%d", nMyWorld )->getCString() );*/

}

void MainMapUiLayer::updataShopGemAndCandNum( void )
{
	if( CommonWidgt::m_GameShopLayout )
	{
	Layout* pLayout = CommonWidgt::m_GameShopLayout->GameShopLayout;

		UILabelAtlas* pMyMoney = dynamic_cast<UILabelAtlas*>(pLayout->getChildByName( "candy_label" ));
		pMyMoney->setStringValue(CCString::createWithFormat( "%d", AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString());

		UILabelAtlas* pGemMoney = dynamic_cast<UILabelAtlas*>(pLayout->getChildByName( "money_label" ));
		pGemMoney->setStringValue(CCString::createWithFormat( "%d", AnalyseJson::logOnMsg.baseInfo.gemNum)->getCString());
	}
}

void MainMapUiLayer::passLevelRewardCandy( void )
{
	UIButton* pLevelBtn = (UIButton*)MainMap::m_mainmap->getBigMapUILayer()->getWidgetByName( CCString::createWithFormat("LevBut%d",  CommonData::getMaxLevel())->getCString() );
	CCPoint nCurlevelPos = pLevelBtn->getParent()->convertToWorldSpace( pLevelBtn->getPosition() );

	UIImageView* pCandyICO = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ImgCandyMoneyIco"));
	CCPoint nCandyPos = pCandyICO->getParent()->convertToWorldSpace( pCandyICO->getPosition() );

	CCSprite* pGemIco = CCSprite::createWithSpriteFrameName( "res_common/ImgCandymoney.png" );

	if ( pGemIco )
	{
		pGemIco->setPosition( nCurlevelPos );

		getWidgetUILayer()->addChild( pGemIco );

		pGemIco->runAction(CCSequence::create(	
			CCSpawn::create(
			getEffectBezierAction(nCurlevelPos, nCandyPos),
			CCScaleTo::create( 1.0f, 1.2f ),
			NULL),
			CCFadeOut::create( 0.1f ),
			CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::FunCallPassReward), (void*)pGemIco ),
			NULL
			));
	}

}

void MainMapUiLayer::FunCallPassReward( CCNode* pSende, void* data )
{
	CCSprite* pGemIco = (CCSprite*)data;

	pGemIco->removeFromParent();

	AnalyseJson::logOnMsg.baseInfo.candyNum += CommonData::getStarForLevel( CommonData::getMaxLevel() ) - CommonData::getLastStarNumForLevel();
	//　糖果币数量
	UILabelAtlas* pCandyMoneyLabel = dynamic_cast<UILabelAtlas*>( mapToolbarlayout->getChildByName("NumberCandyCandy") );
	pCandyMoneyLabel->setStringValue( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString() );

	// 播放特效 添加宝石
	UIImageView* GameCandy = dynamic_cast<UIImageView*>(mapToolbarlayout->getChildByName("ImgCandyMoneyIco"));
	if ( GameCandy )
	{
		CCPoint pos = GameCandy->getParent()->convertToWorldSpace(GameCandy->getPosition());
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y), this);
	}
}

void MainMapUiLayer::setKnapsackAction( float t )
{
	/*CCSprite* pKnapsack = CCSprite::create();
	pKnapsack->initWithSpriteFrameName( "res_mapmenu/BtnknapsackN.png" );
	getWidgetUILayer()->addChild( pKnapsack , 100);

	UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));
	CCPoint tem0 = pBtnMyInformat->getParent()->convertToWorldSpace( pBtnMyInformat->getPosition() );
	
	CCActionInterval* move_ease_inout2 = NULL;
	pKnapsack->setPosition( ccpAdd( tem0, ccp(0, -10) ) );
	move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)CCMoveTo::create(t, ccpAdd( tem0, ccp(0, 90) )),0.9f );
	pKnapsack->runAction(  CCSequence::create(
		move_ease_inout2,
		CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::callfuncKnapsack), (void*)pKnapsack ),
		NULL));*/
}

void MainMapUiLayer::callfuncKnapsack(  CCNode* node, void* data )
{
	CCSprite* pKnapsack = (CCSprite*)data;
	pKnapsack->removeFromParent();
}

void MainMapUiLayer::SwitchPageViewAndLevelLayer()
{
	//新用户，加上指引界面
	if (CommonData::getMaxLevel() < 1 && CommonData::m_isPlayNewUserAction == false)
	{
		ShowLevelLayer();
		CCActionInterval* delay = CCDelayTime::create(0.5);
		CCCallFunc* addArea = CCCallFunc::create(this,callfunc_selector(MainMapUiLayer::addTouchArea));
		runAction(CCSequence::create(delay,addArea, NULL));

		return;
	}
	int pageNum = CommonData::m_pageViewNum;
	if (pageNum < 0)
	{
		ShowTollgatePageview(pageNum);
	}
	else
	{
		ShowLevelLayer();
	}
	
}

void MainMapUiLayer::ShowTollgatePageview(int pagNum)
{
	tollgaetPageview = TollgateSelectLayer::create(pagNum);
	tollgaetPageview->setMainMapUi(this);
	addChild(tollgaetPageview,-100,TAG_TOLLGATE_VIEW);

	m_BackPageviewBtn->setTouchEnabled(false);
	m_BackPageviewBtn->setVisible(false);
	
}

void MainMapUiLayer::ShowLevelLayer()
{
	levelSelectLayer = SelectLevelLayer::create();
	levelSelectLayer->SetPageNum( CommonData::m_pageViewNum);
	addChild(levelSelectLayer,-100,TAG_LEVEL_LAYER);
	
	if (tollgaetPageview)
	{
		tollgaetPageview->removeFromParentAndCleanup(true);
		tollgaetPageview = NULL;
	}

	m_BackPageviewBtn->setTouchEnabled(true);
	m_BackPageviewBtn->setVisible(true);
	m_pTools->setVisible(false);
	m_pTools->setTouchEnable(false);
}

void MainMapUiLayer::BackTopageview( CCObject* sender )
{
	TollgateDelagate* tollDele = dynamic_cast<TollgateDelagate*>(levelSelectLayer);
	if (levelSelectLayer)
	{
		levelSelectLayer->removeFromParentAndCleanup(true);
		levelSelectLayer = NULL;
	}

	ShowTollgatePageview(CommonData::m_pageViewNum);

	m_BackPageviewBtn->setTouchEnabled(false);
	m_BackPageviewBtn->setVisible(false);
	m_pTools->setVisible(true);
	m_pTools->setTouchEnable(true);
}

void MainMapUiLayer::SetTollgateTouchPriority( int Priority )
{
	//强制修改触摸优先级
	if (levelSelectLayer)
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(Priority,levelSelectLayer);
	}
	if (tollgaetPageview)
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(Priority,tollgaetPageview);

	}

}

void MainMapUiLayer::playKnapsackAction( CCPoint pos ,int propid )
{
	// 背包动作
	//CCSprite* pKnapsack = CCSprite::create();
	//pKnapsack->initWithSpriteFrameName( "res_mapmenu/BtnknapsackN.png" );
	//getWidgetUILayer()->addChild( pKnapsack , 100);

	//UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));
	//CCPoint tem0 = pBtnMyInformat->getParent()->convertToWorldSpace( pBtnMyInformat->getPosition() );

	//CCActionInterval* move_ease_inout2 = NULL;
	//pKnapsack->setPosition( ccpAdd( tem0, ccp(0, -10) ) );
	//move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)CCMoveTo::create(1.2f, ccpAdd( tem0, ccp(0, 90) )),0.9f );
	//pKnapsack->runAction(  CCSequence::create(
	//	move_ease_inout2,
	//	CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::callfuncKnapsack), (void*)pKnapsack ),
	//	NULL));


	//// 物品飞行动作
	//CCSprite* pPropIco = CCSprite::create( CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", propid)->getCString() );

	//if(pPropIco != NULL)
	//{
	//	pPropIco->setScale(1.6f);
	//	pPropIco->setPosition( pos );
	//	getWidgetUILayer()->addChild(pPropIco,232);

	//	pPropIco->runAction(CCSequence::create(	
	//		CCSpawn::create(
	//		getEffectBezierAction(pos, ccpAdd( tem0, ccp(0, 90) )),
	//		CCScaleTo::create(1.2f, 0.2f),
	//		NULL),
	//		CCCallFuncND::create(this, callfuncND_selector(MainMapUiLayer::callfuncKnapsackGoods), (void*)pPropIco ),
	//		NULL
	//		));

	//}
}

void MainMapUiLayer::callfuncKnapsackGoods( CCNode* node, void* data )
{
	/*CCSprite* pGoods = (CCSprite*)data;
	pGoods->removeFromParent();

	UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( mapToolbarlayout->getChildByName( "BtnKnapsack" ));
	CCPoint tem0 = pBtnMyInformat->getParent()->convertToWorldSpace( pBtnMyInformat->getPosition() );
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccpAdd( tem0, ccp(0, 90) ), this);*/
}

Layout* MainMapUiLayer::getGameRouletteLayout( void )
{
	Layout* pLayout = NULL;

	pLayout = CommonWidgt::getGameRouletteWidgetUI( WIDGET_TYPE_MAP );

	return pLayout;
}

void MainMapUiLayer::addTouchArea()
{
	//加上镂空层
	TouchArea area;
	area.centerPos = ccp(115,960);
	area.radius = 70;

	ClippingAreaTouchableLayer* ClippingLayer = ClippingAreaTouchableLayer::create();
	ClippingLayer->addTouchArea(area);
	addChild(ClippingLayer);
	ClippingLayer->addFinger(ClippingLayer,area.centerPos);
}

void MainMapUiLayer::refreshLifeUI()
{
	const char *nlifenum = CCString::createWithFormat("%d",  AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();//itoa(AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	m_plifeNum->setStringValue( nlifenum );
}

void MainMapUiLayer::ShowRoulete(CCObject* sender)
{
	PlayEffect( MUSIC_ITEM_BUTTON_E );
	showMapWidget(MAP_WIDGET_ROULETTE_DLG);
}

void MainMapUiLayer::setKeybackEnabled(bool b)
{
	setKeypadEnabled(b);
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 

//  ToolApi
#include "..\..\..\..\cocos2dx\platform\third_party\win32\iconv\iconv.h"

int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char *temp = inbuf;
	const char **pin = &temp;
	char **pout = &outbuf;
	memset(outbuf,0,outlen);
	cd = iconv_open(to_charset,from_charset);
	if(cd==0)
		return -1;

	if(iconv(cd,pin,&inlen,pout,&outlen)==-1)
		return -1;

	iconv_close(cd);
	return 0; 
}
/*UTF8转为GB2312*/
std::string u2a(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;

	if(code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{ 
		strRet = outbuf;
	} 
	delete [] outbuf;
	return strRet; 
}

/*GB2312转为UTF8*/
std::string a2u(const char *inbuf)
{
	size_t inlen = strlen(inbuf);
	char * outbuf = new char[inlen * 2 + 2];
	std::string strRet;
	if(code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
	{
		strRet = outbuf;
	}     
	delete [] outbuf;
	return strRet; 
} 

#endif


