#include "TollgatePage.h"
#include "MainMap/MainMapUiLayer.h"
#include "CommonData/CommonData.h"
#include "Loading/LoadingScene.h"
#include "PlayGame/CandyManager.h"
#include "MainMap/CollectStarsUI.h"
#include "CandyPay/CandyPay.h"
#include "CppCallJava/CppCallJava.h"

#define BIG_MAP_LAYOUT_FILE					"Image/MainMapUi/MainMapUi/UIScrollViewTollgate.ExportJson"

#define MAX_GROUP 15
#define Show_Page_Nums 6		//要显示的总页数

const char* IntoGameLvl1 = "goto level one";

TollgateSelectLayer::TollgateSelectLayer()
	:m_ToPageNum(0)
{

}

TollgateSelectLayer* TollgateSelectLayer::create( int toPageNum )
{
	TollgateSelectLayer* layer = new TollgateSelectLayer();
	if (layer && layer->init())
	{
		layer->autorelease();
		layer->setToPage( toPageNum );
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return NULL;
}

bool TollgateSelectLayer::init()
{
	if (!UILayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	//MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, 35, 1);
	return true;
}

void TollgateSelectLayer::onEnter()
{
	UILayer::onEnter();

	//由于加载场景用到了场景切换过渡特效，影响了Pageview创建，故延迟创建pageview
	runAction(CCSequence::create(
		CCDelayTime::create(0.1),
		CCCallFunc::create(this,callfunc_selector(TollgateSelectLayer::DelayCreate)),
		NULL));
}

void TollgateSelectLayer::DelayCreate()
{
	//ShowYijieUserId(this);

	CreatePageView(Show_Page_Nums);
	ShowProgress();
}

void TollgateSelectLayer::CreatePageView( int pageNum )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize design_size = CCSizeMake(winSize.width*0.7, winSize.height*0.5);
	//创建uipage
	m_pageView = MainMapPageView::create();
	m_pageView->SetClipping(false);
	m_pageView->setTouchEnable(true);
	m_pageView->setSize(design_size);
	m_pageView->setAnchorPoint(ccp(0.5,0.5));
	m_pageView->setPosition(ccp(winSize.width*0.5, winSize.height*0.52));

	//添加page
	for (int i = 0; i < pageNum; ++i)
	{
		Layout* layout = Layout::create();
		layout->setSize(design_size);
		
		UIImageView* actionNode = UIImageView::create();
		actionNode->loadTexture("Image/MainMapUi/m_img_dian1.png");
		actionNode->setAnchorPoint(ccp(0.5,0));
		actionNode->setPosition(ccp(layout->getRect().size.width*0.5,layout->getRect().size.height*0.5));
		layout->addChild(actionNode);
		actionNode->isEffects(true);

		TollgaePage* bg = TollgaePage::create();
		bg->SetPageNum(i);
		bg->setMainMapUi(getMainMapUi());
		bg->setAnchorPoint(ccp(0.5,0));
		bg->setTouchEnabled(true);
		bg->setOpacity(200);
		CCPoint p = ccp(0,-layout->getRect().size.height*0.45);
		bg->setPosition(p);
		actionNode->addChild(bg);

		UIImageView* content = UIImageView::create();
		content->loadTexture(CCString::createWithFormat("Image/BigMap_1/Page%d.png",i+1)->getCString());
		content->setPosition(ccp(0, bg->getSize().height*0.58));
		content->setScale(2.0f);
		bg->addChild(content);


		//锁
		int MaxLvl = MAX_LEVEL/MAX_GROUP;	//15组关卡，每组15关
		int myCurLvl = CommonData::getMaxLevel();
		CCSize bgSize = bg->getSize();

		//玩家玩到的关卡是否有得分记录，有记录代表这关过关，开启下一关；否则不开启下一关
		int openLvl = myCurLvl;
		if (openLvl == 0)
		{
			openLvl = 1;
		}
		if (CommonData::getLevelScore(myCurLvl) > 0)
		{
			if (openLvl < MAX_LEVEL)
			{
				openLvl++;
			}
		}
		
		if (openLvl < MaxLvl*i + 1)
		{
			//遮罩
			UIImageView* zhezhao = UIImageView::create();
			zhezhao->setTexture("Image/BigMap_1/PageShader.png");
			zhezhao->setPosition(ccp(-5, bg->getSize().height*0.515));
			CCSize zhezhaoSize = zhezhao->getContentSize(); 
			zhezhao->setScaleX(bgSize.width/zhezhaoSize.width - 0.12);
			zhezhao->setScaleY(bgSize.height/zhezhaoSize.height - 0.06);
			bg->addChild(zhezhao);
			zhezhao->setZOrder(1000);

			UIImageView* lockImg = UIImageView::create();
			lockImg->setTexture("Image/CandyGame/Others/lock.png");
			lockImg->setPosition(ccp(0, bg->getSize().height*0.5));
			bg->addChild(lockImg);
			lockImg->setScale(2);

		}

		m_pageView->addPage(layout);
	}
	m_pageView->addEventListener(this, pagevieweventselector(TollgateSelectLayer::TurnpageCallback));

	if (m_ToPageNum < 0)
	{
		//没有指定跳到的页面，则跳到当前最大的level对应的page
		int topage = abs((CommonData::getMaxLevel() - 1)/MAX_GROUP);
		m_pageView->scrollToPage(topage);
	}
	else
	{
		m_pageView->scrollToPage(m_ToPageNum);
	}
	
	
	addWidget(m_pageView);
}

void TollgateSelectLayer::TurnpageCallback( CCObject* sender, PageViewEventType eventType )
{
	RefreshProgress();
}

void TollgateSelectLayer::TurnToPage( int idx )
{
	m_pageView->scrollToPage(idx);
}

void TollgateSelectLayer::ShowProgress()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < 3; ++i)
	{
		UIImageView* progess = UIImageView::create();
		progess->loadTexture("Image/BigMap_1/ProgressN.png");
		progess->setPosition(ccp(winSize.width*0.5 + (i-1)*80, winSize.height*0.25));
		progess->setTag(i);
		addWidget(progess);
	}
	RefreshProgress();
}

void TollgateSelectLayer::RefreshProgress()
{
	UIImageView* progress1 = (UIImageView*)getWidgetByTag(0);	
	UIImageView* progress2 = (UIImageView*)getWidgetByTag(1);	
	UIImageView* progress3 = (UIImageView*)getWidgetByTag(2);

	int curTurn = m_pageView->getCurPageIndex();
	if (curTurn == 0)
	{
		progress1->loadTexture("Image/BigMap_1/ProgressP.png");
		progress2->loadTexture("Image/BigMap_1/ProgressN.png");
		progress3->loadTexture("Image/BigMap_1/ProgressN.png");
	}
	else if(curTurn == Show_Page_Nums-1)
	{
		progress1->loadTexture("Image/BigMap_1/ProgressN.png");
		progress2->loadTexture("Image/BigMap_1/ProgressN.png");
		progress3->loadTexture("Image/BigMap_1/ProgressP.png");
	}
	else
	{
		progress1->loadTexture("Image/BigMap_1/ProgressN.png");
		progress2->loadTexture("Image/BigMap_1/ProgressP.png");
		progress3->loadTexture("Image/BigMap_1/ProgressN.png");
	}
}

void TollgateSelectLayer::ShowYijieUserId( CCNode* node )
{
	CCSize ws = CCDirector::sharedDirector()->getWinSize();
	std::string userKey = CommonData::GetString("YijieUserId");
	std::string userId = CCString::createWithFormat("%ld",CppCallJava::getUserId())->getCString();
	std::string IdTips = userKey + userId;
	CCLabelTTF* userTips = CCLabelTTF::create(IdTips.c_str(),"", 36);
	userTips->setPosition(ccp(40, ws.height - 115));
	userTips->setHorizontalAlignment(kCCTextAlignmentLeft);
	userTips->setAnchorPoint(CCPoint(0,0.5));
	node->addChild(userTips);
}



//--------------------------------
bool TollgaePage::init()
{
	if (!UIImageView::init())
	{
		return false;
	}
	m_winSize = CCDirector::sharedDirector()->getWinSize();

	if (CommonData::getMaxLevel() > 0)
	{
		CommonData::m_isPlayNewUserAction = true;
	}

	srand(time(NULL));

	loadTexture("Image/BigMap_1/Pagebg.png");

	setTouchEnabled(true);
	RunAction();
	//isEffects(true);
	return true;
}

bool TollgaePage::onTouchBegan( const CCPoint &touchPoint )
{
	m_beginPoint = touchPoint;
	return UIImageView::onTouchBegan(touchPoint);
}

void TollgaePage::onTouchEnded( const CCPoint &touchPoint )
{
	UIImageView::onTouchEnded(touchPoint);
	CommonData::m_pageViewNum = GetPageNum();		//在触摸结束，设置新的pagenum
	float dis = ccpDistance(touchPoint,m_beginPoint);
	if (dis > 5)
	{
	}
	else
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
		mainMapUi->ShowLevelLayer();
	}
	
}

void TollgaePage::RunAction()
{
	CCActionInterval* func =(CCActionInterval*) CCCallFunc::create(this,callfunc_selector(TollgaePage::UpdateScale));
	this->runAction(CCRepeatForever::create(func));
}

void TollgaePage::UpdateScale()
{
	//一世界坐标为参考系，计算page与屏幕中线的横向距离；距离远大，缩得越小，旋转角度越大；距离越近，效果反之；
	CCPoint thisPos = this->convertToWorldSpace(ccp(0,0));
	float fdisX = fabs(thisPos.x - m_winSize.width*0.5);
	float fratio = fdisX/(m_winSize.width*0.5) + 0.001;
	this->setScaleY(1.001 - sin(fratio*0.3));

	float rdisx = thisPos.x - m_winSize.width*0.5;
	float rratio = rdisx/(m_winSize.width*0.5);
	this->setRotation(3*sin(rratio));
}

void TollgaePage::ShowPerfectTips()
{
	//先判断是否完美通关
	if (!isPerfectPass())
	{
		return;
	}

	UIImageView* perfectIco = UIImageView::create();
	perfectIco->loadTexture("Image/BigMap_1/perfect.png");
	CCSize s = getSize();
	perfectIco->setPosition(ccp(s.width*0.35,s.height*0.9));
	perfectIco->setZOrder(100);
	addChild(perfectIco);
}

void TollgaePage::ShowLvlRange()
{
	UIImageView* RangeBg = UIImageView::create();
	RangeBg->loadTexture("Image/BigMap_1/LvlBg.png");
	RangeBg->setPosition(ccp(0,getSize().height*0.13));
	addChild(RangeBg);
	RangeBg->setScale(1.2);

	int startLvl = GetPageNum()*MAX_GROUP + 1;
	int endLvl = (GetPageNum() + 1)*MAX_GROUP;

	std::string atlasVal = CCString::createWithFormat("%d-%d",startLvl,endLvl)->getCString();

	CCLabelTTF* lvlNums = CCLabelTTF::create(); 
	lvlNums->setString(atlasVal.c_str());
	lvlNums->setFontSize(30);
	RangeBg->addCCNode(lvlNums);

}

void TollgaePage::onEnter()
{
	UIImageView::onEnter();
	ShowLvlRange();
	ShowPerfectTips();
}

bool TollgaePage::isPerfectPass()
{
	//循环取得当前页面的关卡星星数
	int startLvl = GetPageNum()*MAX_GROUP + 1;
	int endLvl = (GetPageNum() + 1)*MAX_GROUP;

	//这里为了效率，换种方式，即循环的时候判断星星数是否小于3，只要存在星星小于3的关卡，返回false，否则返回true
	for (int i = startLvl; i <= endLvl; ++i)
	{
		int curStars = CommonData::getStarForLevel(i);
		if (curStars < 3)
		{
			return false;
		}
	}

	return true;

}




//--------------------
void SelectLevelLayer::onEnter()
{
	UILayer::onEnter();
	ShowLvls();
	ShowCollectProgress();

	//TollgateSelectLayer::ShowYijieUserId(this);
}

void SelectLevelLayer::ShowCollectProgress()
{
	CollectStarsLayer* layer = CollectStarsLayer::create(GetPageNum());
	addWidget(layer);
}

void SelectLevelLayer::ShowLvls()
{
	if (GetPageNum() < 0)
	{
		SetPageNum(0);
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize design_size = ccp(winSize.width, winSize.height*0.75);
	//this->setAnchorPoint(ccp(0,1));
	CCPoint anchP = this->getAnchorPoint();
	this->setContentSize(design_size);
	int MaxLvl = MAX_LEVEL/MAX_GROUP;	//15组关卡，每组15关
	int level = 1;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if ((i+1) * (j+1) >= MaxLvl)
			{
				break;
			}

			//小关卡
			LevelBtn* levelIco = LevelBtn::create(GetPageNum()*MaxLvl + level);
			CCPoint p = ccp(design_size.width*0.16 + design_size.width*0.23 * j, design_size.height - 157*i);
			levelIco->setPosition(p);
			levelIco->setScale(0.9);
			addWidget(levelIco);
			level++;
		}
	}
}




//------------------

LevelBtn::LevelBtn()
{
	m_lock = NULL;
}


LevelBtn* LevelBtn::create( int lvl)
{
	LevelBtn* btn = new LevelBtn;
	if ( btn && btn->init())
	{
		btn->autorelease();
		btn->SetLevel(lvl);
		return btn;
	}

	CC_SAFE_DELETE(btn);
	return NULL;
}

bool LevelBtn::init()
{
	if (!UIImageView::init())
	{
		return false;
	}
	
	isEffects(true);

	return true;
}

void LevelBtn::onEnter()
{
	UIImageView::onEnter();

	if (m_CurLevel == 1)
	{
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(LevelBtn::GotoGameLevelOne),IntoGameLvl1,NULL);
	}

	m_button = UIButton::create();
	int maxCurLvl = CommonData::getMaxLevel();		//玩家玩到的关卡
	bool islock = isLock();
	if (!islock)		//如果点击的是已经过关，且不是玩家当前通关的最大关卡
	{
		m_button->loadTextures("Image/BigMap_1/PassLvlN.png","Image/BigMap_1/Locklvl.png","Image/BigMap_1/Locklvl.png");
		if ( m_CurLevel == (maxCurLvl + 1) && CommonData::getLevelScore(maxCurLvl)>0)
		{
			m_button->loadTextures("Image/BigMap_1/MaxLvlN.png","Image/BigMap_1/Locklvl.png","Image/BigMap_1/Locklvl.png");
		}
	}
	else 
	{
		m_button->loadTextures("Image/BigMap_1/Locklvl.png","Image/BigMap_1/Locklvl.png","Image/BigMap_1/Locklvl.png");
	}
	
	m_button->setPosition(ccp(0,0));
	addChild(m_button);
	setLockIco();	//加上锁
	ShowStar();		//显示星星
	ShowAtlas();	//显示数字标签


	//没锁的话，允许触摸，监听事件
	m_button->setTouchEnabled(true);
	m_button->addTouchEventListener(this,toucheventselector(LevelBtn::ClickCallback));

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(LevelBtn::UnlockAllLvl),unlockAllLvl,this);
}

void LevelBtn::onExit()
{
	UIImageView::onExit();
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	if (m_CurLevel == 1)
	{
		CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	}
}
void LevelBtn::ClickCallback( CCObject* snder,TouchEventType eventType )
{
#ifdef CANDY_STATISITICAL_DATA
	//新用户记录点
	if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
	{
		AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1005);
	}
#endif

	CCPoint myPos = convertToWorldSpace(CCPointZero);
	CCLog("my pos = %f, %f",myPos.x, myPos.y);

	if (eventType == TOUCH_EVENT_ENDED)
	{
		if (isLock())
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PAY_DLG,UnLock_Level);
			//CandyPay::getInstance()->RequestCandyOrder(UnLock_Level);
			return;
		}

// 电信不能在进入游戏时弹出计费点修改 dianxin
#if 1
		if (CommonData::m_isPlayNewUserAction == false && m_CurLevel == 1 && CommonData::m_GiftIDBuyNow != 0)
		{
			//第一次点击弹出新手大礼包
			CCNotificationCenter::sharedNotificationCenter()->postNotification(ShowOrHideLayer,NULL);
		//	MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_GIFT_DLG);
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
			return;
		}
#endif
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
		CCLog("pressed lvl = %d",m_CurLevel);

		MainMapUiLayer::m_mainmapuilayer->getWidgetUILayer()->removeWidget(MainMapUiLayer::m_mainmapuilayer->LevelInfoLayout);
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
			//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

#else
			MainMapUiLayer::m_mainmapuilayer->m_pTools->setTouchEnable( false );
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

			//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );


#endif
		}
		else
		{
			CandyManager::currentLevel = m_CurLevel;
			CommonData::setPlayGame( true );
			Loading::replaceScence(CANDY_SCENCE_PLAY_GAME);
		}
	}
}

void LevelBtn::setLockIco()
{
	bool islock = isLock();
	if (!islock)
	{
		return;
	}
	//枷锁
	m_lock = CCSprite::create("Image/CandyGame/Others/lock.png");
	m_lock->setPosition(ccp(getContentSize().width*0.5,getContentSize().height*0.5));
	m_lock->setScale(0.7);
	m_button->addCCNode(m_lock);
	
}

bool LevelBtn::isLock()
{
	int MaxCurLvl = CommonData::getMaxLevel();
	if (MaxCurLvl == 0)
	{
		MaxCurLvl = 1;
	}

	if (m_CurLevel <= MaxCurLvl)
	{
		return false;
	}

	//判断最大关卡是否有成绩，如果有，代表玩通关，下一关解锁；反之枷锁
	int LvlScore = 0;
	LvlScore = CommonData::getLevelScore(m_CurLevel - 1);

	if (LvlScore > 0)
	{
		return false;
	}	

	return true;
}

void LevelBtn::ShowStar()
{
	int starNum = CommonData::getStarForLevel(m_CurLevel);
	if (starNum < 1)
	{
		return;
	}
	CCSize size = m_button->getSize();
	for (int i = 1; i <= 3; i++)
	{
		UIImageView* star = UIImageView::create();
		if (i <= starNum)
		{
			star->loadTexture(CCString::createWithFormat("Image/MainMapUi/m_pic_star%d.png",i)->getCString());
		}
		else
		{
			star->loadTexture(CCString::createWithFormat("Image/MainMapUi/m_pic_starB%d.png",i)->getCString());
		}
		star->setPosition(ccp(size.width * 0.25 * (i-2),-size.height*0.25 - 15* (i%2) ));
		star->setScale(0.9);
		m_button->addChild(star);
	}
}

void LevelBtn::ShowAtlas()
{
	if (isLock())
	{
		return;
	}
	UILabelAtlas* lvlAtlas = UILabelAtlas::create();
	lvlAtlas->setVisible( true );
	lvlAtlas->setScale( 0.85f );
	lvlAtlas->setProperty(CCString::createWithFormat("%d",m_CurLevel)->getCString() , "Image/MainMapUi/res_cliamlife/m_cliamnum.png",44, 52, "0");  
	lvlAtlas->setPosition( ccp(0, 0));
	m_button->addChild( lvlAtlas );
}

void LevelBtn::GotoGameLevelOne( CCObject* sender )
{
	CommonData::m_isPlayNewUserAction = true;

	MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
	CCLog("pressed lvl = %d",m_CurLevel);

	MainMapUiLayer::m_mainmapuilayer->getWidgetUILayer()->removeWidget(MainMapUiLayer::m_mainmapuilayer->LevelInfoLayout);
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
	//	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

#else
		MainMapUiLayer::m_mainmapuilayer->m_pTools->setTouchEnable( false );
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

	//	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );

#endif
	}
	else
	{
		CandyManager::currentLevel = 1;
		CommonData::setPlayGame( true );
		Loading::replaceScence(CANDY_SCENCE_PLAY_GAME);
	}
}

void LevelBtn::UnlockAllLvl( CCObject*obj )
{
	if(m_lock!= NULL)
	{
		m_lock->removeFromParentAndCleanup(true);
		m_lock = NULL;

		m_button->removeAllChildrenAndCleanUp(true);

		int maxCurLvl = CommonData::getMaxLevel();		//玩家玩到的关卡
		m_button->loadTextures("Image/BigMap_1/PassLvlN.png","Image/BigMap_1/PassLvlP.png","Image/BigMap_1/PassLvlP.png");
		if ( m_CurLevel == (maxCurLvl + 1) && CommonData::getLevelScore(maxCurLvl)>0)
		{
			m_button->loadTextures("Image/BigMap_1/MaxLvlN.png","Image/BigMap_1/MaxLvlP.png","Image/BigMap_1/MaxLvlP.png");
		}

		ShowStar();		//显示星星
		ShowAtlas();	//显示数字标签
	}
}




//--------------
bool BackGroudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_gradientPos = ccp(0,0);
	//背景
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* map_bg = CCSprite::create("Image/CandyGame/Background/Bg5.jpg");
	map_bg->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
	addChild(map_bg);

	CCLayerGradient* layer1 = CCLayerGradient::create(ccc4(255,255,255,20), ccc4(255,215,0,120), ccp(1.0f, 0.1f));
	addChild(layer1, 0, 1);

	CCNode* RotatNode = CCNode::create();
	addChild(RotatNode);

	m_VecNode = CCNode::create();
	RotatNode->addChild(m_VecNode);
	m_VecNode->setPosition(ccp(100,100));
	CCActionInterval* action = CCSequence::create(
		CCRotateBy::create(2,150),
		CCDelayTime::create(2),
		CCRotateBy::create(2,-150),
		NULL);
	RotatNode->runAction(CCRepeatForever::create(action));

	schedule(schedule_selector(BackGroudLayer::UpdateVector));

	return true;
}

void BackGroudLayer::onEnter()
{
	CCLayer::onEnter();
	
}

void BackGroudLayer::UpdateVector( float dt )
{
	CCPoint p = m_VecNode->convertToWorldSpace(CCPointZero);
	CCLayerGradient *gradient = (CCLayerGradient*) getChildByTag(1);
	gradient->setVector(p);
}



//-------------------------
MainMapPageView::MainMapPageView()
{

}

void MainMapPageView::SetClipping( bool b )
{
	setClippingEnabled(b);
}

void MainMapPageView::handleReleaseLogic( const CCPoint &touchPoint )
{
	UIWidget* curPage = dynamic_cast<UIWidget*>(m_pages->objectAtIndex(m_nCurPageIdx));
	if (curPage)
	{
		CCPoint curPagePos = curPage->getPosition();
		int pageCount = m_pages->count();
		float curPageLocation = curPagePos.x;
		float pageWidth = getSize().width;
		float boundary = pageWidth/8.0f;	//优化滑动灵敏度
		if (curPageLocation <= -boundary)
		{
			if (m_nCurPageIdx >= pageCount-1)
			{
				scrollPages(-curPageLocation);
			}
			else
			{
				scrollToPage(m_nCurPageIdx+1);
			}
		}
		else if (curPageLocation >= boundary)
		{
			if (m_nCurPageIdx <= 0)
			{
				scrollPages(-curPageLocation);
			}
			else
			{
				scrollToPage(m_nCurPageIdx-1);
			}
		}
		else
		{
			scrollToPage(m_nCurPageIdx);
		}
	}
}

