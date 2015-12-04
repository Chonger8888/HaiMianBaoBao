
#include "MainMapUiLayer.h"
#include "ShaderSprite.h"
#include "SimpleAudioEngine.h"
#include "../Loading/LoadingScene.h"
#include "../PlayGame/CandyManager.h"
#include "../cocos2dx_support/CCLuaEngine.h"
#include "../CommonData/CommonData.h"
#include "../MsgMgr/AnalyseJson.h"
#include <algorithm>
#include "MainMap/TollgatePage.h"
#include "CandyPay/CandyPay.h"

extern "C"
{
#include "lua.h"
#include "tolua++.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

static lua_State* levelLuaState = NULL;;
using namespace CocosDenshion;

#define BIG_MAP_LAYOUT_FILE					"Image/MainMapUi/MainMapUi/UIScrollViewTollgate.ExportJson"//"Image/BigMap_1/BigMap_1.json"//"Image/BigMap_1/BigMap_1.json"

#define BIG_MAP_WIDTH						1024.0f
#define BIG_MAP_HEIGHT						6144.0f

#define MAP_MAX_SCALE_NUM					2.0f
#define MAP_MIN_SCALE_NUM					1.0f//(720.0f/1024.0f)
#define MAP_MAX_SCALE_ELASTICITY			0.99f
#define MAP_MIN_SCALE_ELASTICITY			1.01f
#define MAP_EXCESS_SCALE_NUM 				1.2f
#define MAP_LEVEL_NUM						225
#define	TOUCH_MOVE_MIN_TIME					16
#define MAP_MOVE_MAX_OFFSET					80
#define MAP_DEFINE_SIZE						1.6f

float MainMap::currentScale = 2.0f;
CCPoint MainMap::currentPos = ccp(0,0);
int MainMap::m_LevInfoShowNum = 1;
bool MainMap::m_isFirst = false;
int MainMap::m_GameState = GAME_STATE_FAIL;
MainMap*  MainMap::m_mainmap = NULL;

//int MainMap::m_MapLevelData[GAME_MAX_LEVEL_NUM][4] = {0};


MainMap::MainMap():
touchNum(0),
touchType(MAP_TOUCH_DEFAULT ),
gameNextLayout(NULL),
widgetUiLayer(NULL),
m_pPanel(NULL),
m_particlePos(NULL),
m_doubleClickTime(0.0f),
m_isMapScale(false),
m_isMove(false),
m_isTouches(false),
m_keystate(KEY_EMPTY),
m_mapScaleType(MAP_SCALE_NULL),
m_pParticle(NULL)
{

}

CCScene* MainMap::scene(bool pare)
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		m_isFirst = ( pare )? true:false;

		CCLayer *layer;
		layer = BackGroudLayer::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer,-100);

		layer = MainMap::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer,0,MAINMAP_TAG);

		layer = MainMapUiLayer::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer,0,MAINMAPUILAYER_TAG);


	} while (0);
	return scene;
}

bool MainMap::init(void)
{
 	if ( !CCLayer::init() )
	{
		return false;
	}
	
	m_mainmap = this;


#ifdef CANDY_STATISITICAL_DATA
	//新用户记录点
	if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
	{
		AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1004);
	}

	// 初始星星个数为0
	AnalyseJson::taskTable.curstarnum = 0;

	//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4006);

	/*if ( m_isFirst )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_10, "");*/

	/*if( !m_isFirst && CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=5)
	{
		char* pLevel = (char*)CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString();
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_47, pLevel);
	}*/

	/*if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_67 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_77 );*/

#endif
	// 生命信息
	MsgMgr::sendAddSysLifeMsg( AnalyseJson::logOnMsg.baseInfo.id );
	MsgMgr::sendGetWorldRanked( AnalyseJson::logOnMsg.baseInfo.id );
	initPreloadEffect();
	initMapBackground(); 
	getLevelNumFromLua( 0 );
	setMapScale(MAP_DEFINE_SIZE);
	//setMapPos(currentPos);

	return true;
}

#define MAPSCALE_TIME_MAX	0.3f  
#define MAPSCALE_SCALE_MAX	2.0f 
#define MAPSCALE_SCALE_MIN	1.0f 

void MainMap::update(float time)
{
	if ( KEY_FIRST == m_keystate )
	{
		m_doubleClickTime++;
		if ( 18 <= m_doubleClickTime )
		{
			m_keystate = KEY_EMPTY;
			m_doubleClickTime = 0.0f;
		}
	}

	// scale screen
	float nScale = getScale();

	if ( m_isMapScale )
	{
		static float  nCurScale = 0.0f;
		static int	nScaleTime = MAPSCALE_TIME_MAX;
		static float nTime = 0;

		nTime += time/16;
		// 放大
		if ( MAP_SCALE_MAGNIFY == m_mapScaleType)
		{
			nCurScale = nCurScale + (MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN)/2/((MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN)/nTime);
			setMapScale( nScale + nCurScale );
			if ( MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN  <= nCurScale || nScale >= MAPSCALE_SCALE_MAX)
			{
				m_mapScaleType = MAP_SCALE_SHRINK;
				nCurScale = 0.0f;
				nTime = 0;
				m_isMapScale = false;
			}
		}	
		// 缩小
		else if ( MAP_SCALE_SHRINK == m_mapScaleType)
		{
			nCurScale = nCurScale + (MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN)/2/((MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN)/nTime);
			setMapScale( nScale - nCurScale );
			if ( MAPSCALE_SCALE_MAX - MAPSCALE_SCALE_MIN  <= nCurScale  || nScale <= MAPSCALE_SCALE_MIN-0.1f)
			{
				m_mapScaleType = MAP_SCALE_NULL;
				nCurScale = 0.0f;
				nTime = 0;
				m_isMapScale = false;
			}
		}	
		//CCLog( "MainMap::update nCurScale:%f  nScale:%f", nCurScale, nScale );
	}


	if(touchNum)
	{
		m_moveTime++;
		return;
	}

	updateMapScale(time);
	updateMapPos(time);
}

void MainMap::onEnter(void)
{
	CCLayer::onEnter();

	scheduleUpdate();
	playMapBgm();
	setAnchorPoint(ccp(0,0));

	this->runAction(CCSequence::create(
		CCDelayTime::create( 1.8f ),
		CCCallFunc::create(this, callfunc_selector(MainMap::showFriendHeadImg)),
		NULL));

}

void MainMap::onEnterTransitionDidFinish(void)
{
	CCLayer::onEnterTransitionDidFinish();

	int num = CommonData::getFriendNumInLevel(CandyManager::currentLevel);
	int bPassStageNum = getPassStageNum();


	if ( 
		(bPassStageNum - 1 <= CandyManager::currentLevel)
 		&&( GAME_STATE_SUCCEE_NEXT == MainMap::m_GameState || GAME_STATE_SUCCEE == MainMap::m_GameState)
 		&& 225 != CandyManager::currentLevel
		)
 	{
		if(num != 0)
		{
			if(CommonData::getMaxLevel() != 5 || CandyManager::currentLevel != 5)
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_SURFRIEND_DLG );
			}
		}
		else
		{
			setHeadMove();
		}		
 	}
	else
	{
		setHeadMove();
	}

	this->schedule(schedule_selector(MainMap::UpdataDelayTouchEnabled), 2.0f);

	if (CommonData::getMaxLevel() < 1 && CommonData::m_isPlayNewUserAction == false)
	{

	}
	else
	{
		if(CommonData::m_GiftIDBuyNow != 0)
		{
			//MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_GIFT_DLG);
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
			//新版支付  游戏开启弹新手礼包
			MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PAY_DLG,CommonData::m_buytype);
		

		}
	}

}

void MainMap::UpdataDelayTouchEnabled(float t)
{
	setTouchEnabled(true);
	this->unschedule( schedule_selector(MainMap::UpdataDelayTouchEnabled) );
}

void MainMap::onExit(void)
{
	CCLayer::onExit();
	unLoadEffect();
	currentPos =  getPosition();
	if ( SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() )
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void MainMap::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	/*for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++) 
	{
		if(touchNum<2)
		{
			CCTouch *pCurTouch =  (CCTouch*)(*iterTouch);
			touchPoint[touchNum] = pCurTouch->getLocation();
		}
		touchNum++;
	}
	firstPoint = touchPoint[0];
	m_moveTime = 0.0f;*/

//	CCPoint point = bigMapUiLayer->convertToNodeSpace(firstPoint);
//	CCNode* particle = CandyParticle::displayCandyParticleForXml(CANDY_EFFECT_TEST, point, this);
	
//	MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_CHANGEINFO );


	// test buy prop
	
}

void MainMap::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	//int touchMoveNum= 0;
	//CCPoint touchMovePoint[2] ;
	//// 	m_isMove = true;

	////	bigMapUiLayer->removeChild( m_pParticle );
	//for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++) 
	//{
	//	if(touchMoveNum<2)
	//	{
	//		CCTouch *pCurTouch =  (CCTouch*)(*iterTouch);
	//		touchMovePoint[touchMoveNum] = pCurTouch->getLocation();
	//	}
	//	touchMoveNum++;
	//}

	//if(touchMoveNum < touchNum)
	//	return;
	//if(touchMoveNum == 1)
	//{

	//	CCPoint pos = getPosition();
	//	pos.x = pos.x + (touchMovePoint[0].x - touchPoint[0].x);
	//	pos.y = pos.y + (touchMovePoint[0].y - touchPoint[0].y);
	//	setMapPos(pos);
	//	//CCLog( "setMapPos  1: x:%d y:%d     2: x:%d y:%d",(int)touchPoint[0].x,(int)touchPoint[0].y,(int)touchMovePoint[0].x,(int)touchMovePoint[0].y );
	//	touchPoint[0] = touchMovePoint[0];
	//}
	//else// if(touchMoveNum == 2)
	//{
	//	float lastLen =  ccpDistance(touchPoint[0], touchPoint[1]);
	//	float newLen = ccpDistance(touchMovePoint[0], touchMovePoint[1]);
	//	float subLen = newLen - lastLen;
	//	float scale = getScale();

	//	//scale += subLen * 0.0005f;
	//	scale += subLen * 0.001f;
	//	setMapScale(scale );

	//	touchPoint[0] = touchMovePoint[0];
	//	touchPoint[1] = touchMovePoint[1];
	//}
}

void MainMap::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	//int nCurTouchNum = touchNum;
	//m_isMove = false;
	//for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++) 
	//{
	//	CCTouch *pCurTouch =  (CCTouch*)(*iterTouch);
	//	CCPoint temPoint =  pCurTouch->getLocation();
	//	touchNum--;

	//	if ( 0 > touchNum)
	//		touchNum = 0;

	//	if(touchNum == 1)
	//	{
	//		if(ccpDistance(touchPoint[0], temPoint) < ccpDistance(touchPoint[1], temPoint))
	//		{
	//			touchPoint[0] = touchPoint[1];
	//		}
	//	}
	//}

	//if ( KEY_EMPTY == m_keystate && 1 == nCurTouchNum /*&& !m_isMove*/)
	//{
	//	m_keystate = KEY_FIRST;
	//}
	//else if ( KEY_FIRST == m_keystate && 1 == nCurTouchNum )
	//{
	//	if ( 18 > m_doubleClickTime )
	//	{
	//		m_isMapScale = true;
	//		float nScale = getScale();
	//		if ( 1.5f > nScale )
	//		{
	//			m_mapScaleType = MAP_SCALE_MAGNIFY;
	//		}
	//		else
	//		{
	//			m_mapScaleType = MAP_SCALE_SHRINK;
	//		}
	//	}
	//}

	//if ( TOUCH_MOVE_MIN_TIME >= m_moveTime && 1 == nCurTouchNum )
	//{
	//	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	//	CCPoint nCurPoing = getPosition();		
	//	float nMaxMoveX, nMaxMoveY;

	//	float scale = getScale();
	//	float nMapMaxX = TARGET_SCREEN_WIDTH -BIG_MAP_WIDTH * scale - MAP_MOVE_MAX_OFFSET* scale;
	//	float nMapMinX = MAP_MOVE_MAX_OFFSET* scale;
	//	float nMapMaxY = currentScreenHeight -BIG_MAP_HEIGHT* scale - MAP_MOVE_MAX_OFFSET* scale;
	//	float nMapMinY = MAP_MOVE_MAX_OFFSET* scale;
	//	int nMoveX, nMoveY;
	//	nMoveX = firstPoint.x - touchPoint[0].x;
	//	nMoveY = firstPoint.y - touchPoint[0].y;

	//	nMaxMoveX = nCurPoing.x-nMoveX*2.0f;
	//	nMaxMoveY = nCurPoing.y-nMoveY*2.0f;
	//	if ( nMapMinX <= nMaxMoveX )
	//		nMaxMoveX = nMapMinX;
	//	else if ( nMapMaxX >= nMaxMoveX )
	//		nMaxMoveX = nMapMaxX;

	//	if ( nMapMinY <= nMaxMoveY )
	//		nMaxMoveY = nMapMinY;
	//	else if ( nMapMaxY >= nMaxMoveY )
	//		nMaxMoveY = nMapMaxY;

	//	if (( 20 < abs( nMoveX ))|| (20 < abs( nMoveY )))
	//	{
	//		m_keystate = KEY_EMPTY;
	//	}

	//	CCActionInterval * move = CCMoveTo::create(0.4f,ccp(nMaxMoveX, nMaxMoveY));
	//	CCActionInterval * easeSineOut = CCEaseSineOut::create(move);
	//	runAction( CCSequence::create(easeSineOut , 
	//		CCCallFunc::create(this, callfunc_selector(MainMap::MoveMapCallback)),
	//		NULL));
	//}
}


void MainMap::MoveMapCallback(void)
{
	// 	m_pParticle = CandyParticle::displayCandyParticle(CANDY_MAP_ACTIVE_NEW2, paricalPoint);
	// 	bigMapUiLayer->addChild( m_pParticle );
}

void MainMap::initMapBackground(void)
{
	/*bigMapUiLayer =  UILayer::create();
	this->addChild(bigMapUiLayer);

	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	UIPanel* m_pPanel = UIPanel::create();
	m_pPanel->setSize( CCSizeMake( 600+BIG_MAP_WIDTH,BIG_MAP_HEIGHT+600 ));
	m_pPanel->setPosition( ccp(-300,-300) );
	m_pPanel->setZOrder( 0 );
	m_pPanel->setBackGroundColorType( LAYOUT_COLOR_SOLID );
	m_pPanel->setBackGroundColor( ccc3(150,150,150) );
	m_pPanel->setVisible( true );
	bigMapUiLayer->addWidget((m_pPanel));


	int bPassStageNum = getPassStageNum();*/
	// 	UIImageView *pheadimg = dynamic_cast<UIImageView*>(bigMapLayout->getChildByName( "m_img_head" ));
	// 	pheadimg->setVisible( false );

	//m_pHeadbgImg = UIImageView::create();
	//m_pHeadbgImg->setTexture( "Image/BigMap_1/m_headframe.png" );
	//m_pHeadbgImg->setName( "headIco" );
	//m_pHeadbgImg->setVisible(true);
	//m_pHeadbgImg->setZOrder( 6 );
	//m_pHeadbgImg->setScale(0.5f );
	//bigMapUiLayer->addWidget( m_pHeadbgImg );

	//setVipHead();

	//// Set My name
	//char *pMyNameStr = (char *)CCString::createWithFormat("%s", AnalyseJson::logOnMsg.baseInfo.nickName.c_str())->getCString();
	//UILabel * pMyName = UILabel::create();
	//pMyName->setFontSize( 25 );
	//pMyName->setPosition( ccp(0, -68));
	//pMyName->setName("nickname");
	//pMyName->setVisible( true );
	//pMyName->setText( pMyNameStr );
	//m_pHeadbgImg->addChild(pMyName);

	//UIImageView* pHeadKImg = UIImageView::create();
	//pHeadKImg->setTexture( "Image/MainMapUi/vipkuang.png" );
	//pHeadKImg->setVisible( true );
	//pHeadKImg->setScale(1.1f);
	//pHeadKImg->setZOrder( 2 );
	//pHeadKImg->setPosition(ccp(0, 0));
	//m_pHeadbgImg->addChild( pHeadKImg);

	//std::string path = CommonData::getCurrentHeadPath( AnalyseJson::logOnMsg.baseInfo.headPicUrl ).c_str();
	//UIImageView *pHeadImg = UIImageView::create();
	//float nScale = 0;
	//pHeadImg->setTexture( path.c_str() );
	//nScale = pHeadImg->getSize().width;
	//pHeadImg->setName("myheadico");
	//pHeadImg->setVisible( true );
	//pHeadImg->setPosition( ccp(0,0));
	//m_pHeadbgImg->addChild( pHeadImg );

}
void MainMap::showFriendHeadImg()
{
	int maxLevel = CommonData::getMaxLevel();
	int num = 0;
	int countFront = 0;
	int countBack = 0;
	std::vector<int> haveAddVec;
	haveAddVec.clear();
	std::list<UserFriendInfoStr>::iterator iter = AnalyseJson::friendInfoMsg.friendInfo.begin();
	std::list<UserFriendInfoStr>::iterator iterEnd= AnalyseJson::friendInfoMsg.friendInfo.end();
	AnalyseJson::friendInfoMsg.friendInfo.sort(Cmpare());
	if(MainMap::m_mainmap)
	{
	for(;iter!=iterEnd;++iter)
	{

		std::vector<int>::iterator checkIter = std::find(haveAddVec.begin(), haveAddVec.end(),  iter->level);
		
		if(checkIter == haveAddVec.end()) 
		{
			int diff = iter->level - (maxLevel+1);

			if(diff > 0 && diff <= 20)
			{
				if(countFront <= 4)
				{
					setHeadImg(*iter);
					haveAddVec.push_back(iter->level);
					countFront++;
				}
			}
			else if(diff <0 && diff>=-20)
			{
				if(countBack <= 4)
				{
					setHeadImg(*iter);
					haveAddVec.push_back(iter->level);
					countBack++;
				}
			}
		}
	}
	}
	
}
void MainMap::setHeadImg(UserFriendInfoStr player)
{
 //	UIImageView *headbgImg = UIImageView::create();
 //	headbgImg->setTexture( "Image/BigMap_1/m_headframe.png" );
 //	headbgImg->setVisible(true);
 //	headbgImg->setZOrder( 6 );
 //	headbgImg->setScale(0.5f );
 //	bigMapUiLayer->addWidget( headbgImg );
 //
 //	// Set name
 //	char *pMyNameStr = (char *)CCString::createWithFormat("%s", player.nickName.c_str())->getCString();
 //	UILabel * pMyName = UILabel::create();
 //	pMyName->setFontSize( 25 );
 //	pMyName->setPosition( ccp(0, -68));
 //	pMyName->setVisible( true );
 //	pMyName->setText( pMyNameStr );
 //	headbgImg->addChild(pMyName);
 //
 //	UIImageView* pHeadKImg = UIImageView::create();
 //	pHeadKImg->setTexture( "Image/BigMap_1/m_img_headK.png" );
 //	pHeadKImg->setVisible( true );
 //	pHeadKImg->setScale(1.1f);
 //	pHeadKImg->setZOrder( 2 );
 //	pHeadKImg->setPosition(ccp(0, 0));
 //	headbgImg->addChild( pHeadKImg);
 //
	//std::string headPath = CommonData::getHeadPathForUrl( player.headPicUr.c_str() );
 //	UIImageView *pHeadImg = UIImageView::create();
 //	pHeadImg->setTexture( headPath.c_str() );
 //	pHeadImg->setVisible( true );
 //	pHeadImg->setPosition( ccp(0,0));
 //	headbgImg->addChild( pHeadImg );

	//CCPoint offsetPos = ccp(0, -60);
	//CCPoint bCurLevelPoint = getLevelNumFromLua(  player.level );
	//headbgImg->setPosition( ccp( bCurLevelPoint.x - offsetPos.x, bCurLevelPoint.y - offsetPos.y ));

	//// vip 皇冠
	//if ( 0 != player.isvip )
	//{
	//	UIImageView* pVipImg = UIImageView::create();
	//	pVipImg->setTexture( "Image/BigMap_1/ImgVipTips.png" );
	//	pVipImg->setZOrder( 10 );
	//	pVipImg->setPosition(ccp(0, 55));
	//	headbgImg->addChild( pVipImg);
	//}

	//if(player.level > getPassStageNum())
	//{
	//	addMapLevelButton(player.level,225,0,true);
	//}
}

void MainMap::setHeadMove()
{
	CCPoint bCurLevelPoint, bNextLevelPoint;
	int bPassStageNum = getPassStageNum();
	CCPoint offsetPos = ccp(0, -60); // 在地图上头像位置

	int nLevel = getPassStageNum();
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

	if ( (bPassStageNum - 1 <= CandyManager::currentLevel) && 225 != CandyManager::currentLevel
		&&( GAME_STATE_SUCCEE_NEXT == MainMap::m_GameState || GAME_STATE_SUCCEE == MainMap::m_GameState ))
	{	  
	
		bNextLevelPoint = getLevelNumFromLua( bPassStageNum );
		bCurLevelPoint = getLevelNumFromLua( bPassStageNum-1 );
		 
		setMapScale( 1.0f );
		setMapPos(ccp(-bNextLevelPoint.x+currentScreenWidth/2, -bNextLevelPoint.y+currentScreenHeight/2));
		setMapScale( 1.5f );
		MapBorderCheck();

		bPassStageNum = getPassStageNum() - 1;

#ifdef CANDY_STATISITICAL_DATA
		/*if( 1 == CommonData::getMaxLevel() )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_68 );
		else if( 2 == CommonData::getMaxLevel() )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_78 );*/
#endif


		/*m_pHeadbgImg->setPosition( ccp( bCurLevelPoint.x - offsetPos.x, bCurLevelPoint.y - offsetPos.y ));
		m_pHeadbgImg->runAction(
			CCSequence::create(
			CCDelayTime::create( CommonData::getLastStarNumForLevel() < CommonData::getStarForLevel( bPassStageNum-1 )?1.5f:0.0f ),
			CCCallFunc::create(this, callfunc_selector(MainMap::callFuncRewardCandy)),
			CCDelayTime::create( 0.5f ),
			CCMoveTo::create(1.0f ,ccp(bNextLevelPoint.x - offsetPos.x, bNextLevelPoint.y - offsetPos.y)),
			CCCallFunc::create(this, callfunc_selector(MainMap::callFuncMoveHead)),
			NULL));*/

		if ( bPassStageNum > AnalyseJson::unLockConfig.friendFun && (bPassStageNum - AnalyseJson::unLockConfig.friendFun)%5 == 0 )		
		{
			AnalyseJson::friendInfoMsg.friendMaxNum +=1;
			//MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_FRIENDNUMLIMIT ); //好友上限+1
		}

	}
	else
	{
		char *LevelNum= (char *)CCString::createWithFormat("MapLevel%d",  nLevel)->getCString();
		int x = 0, y = 0;

		bNextLevelPoint = getLevelNumFromLua( bPassStageNum );

		nLevel = getPassStageNum();
		if ( 0 == nLevel )	nLevel = 1;
		if ( 225 >= nLevel )	addMapLevelButton( nLevel,nLevel,0, false);

 		/*m_pParticle = CandyParticle::displayCandyParticle( CANDY_MAP_ACTIVE_NEW2, ccp(0,0));
 		m_particlePos->getRenderer()->addChild( m_pParticle );*/
		
		lua_getglobal(levelLuaState, LevelNum);
		x = getTableNumFromLua(nLevel, 1 );
		y = getTableNumFromLua(nLevel, 2 );
		//m_pHeadbgImg->setPosition( ccp( x - offsetPos.x, y - offsetPos.y ));

#if defined( DEMO_FOR_GUEST )
		
		if ( 1 != getPassStageNum() )
		{
			int currentId = CommonData::getCurrentPackage();
		
			// 显示公告
			if ( 1 == AnalyseJson::logOnMsg.baseInfo.isFirstLogin && 1 == AnalyseJson::logOnMsg.baseInfo.isNotice )
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_NOTICE_DLG);
				AnalyseJson::logOnMsg.baseInfo.isFirstLogin = 0;
			}
			// 显示礼包
			else if(currentId != 0 && CommonData::m_isEnterGame)
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_GIFT_DLG );
				CommonData::m_isEnterGame = false;
			}
			// 显示VIP
			else if(AnalyseJson::logOnMsg.baseInfo.isVip && AnalyseJson::logOnMsg.baseInfo.today_has_receice == 0)
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_REWARDVIPUI );
				AnalyseJson::logOnMsg.baseInfo.today_has_receice = 1;
			}
			// 显示VIP奖励
			else if ( (1 == AnalyseJson::logOnMsg.lifeInfo.lifeNum || 3 == AnalyseJson::logOnMsg.lifeInfo.lifeNum ) && !AnalyseJson::logOnMsg.baseInfo.isVip )
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_VIP_DLG, 1 );
				//this->scheduleOnce(schedule_selector(MainMap::FirstConsumsLifeDelay), 1.0f );		
			}
			nLevel = CandyManager::currentLevel;
		}
#endif

		LevelNum= (char *)CCString::createWithFormat("MapLevel%d",  nLevel)->getCString();
		lua_getglobal(levelLuaState, LevelNum);

		setMapScale( 1.0f );
		setMapPos(ccp(-bNextLevelPoint.x+currentScreenWidth/2, -bNextLevelPoint.y+currentScreenHeight/2));
		setMapScale( 1.6f );
		//MapBorderCheck();

	}
}

void MainMap::MapBorderCheck(void)
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	int nMapBorderX = 0, nMapBorderY = 0;
	int x = 0, y = 0 , offsetx = 0, offsety = 0;
	float nScale = 0;
	int nLevel = getPassStageNum();

	x = getTableNumFromLua( nLevel,1 );
	y = getTableNumFromLua( nLevel,2 );
	//  Map move border check
	nScale = MAP_DEFINE_SIZE;//getScale();
	nMapBorderX = -x* nScale+currentScreenWidth/2;
	nMapBorderY = -y* nScale+currentScreenHeight/2;
	if (0 < nMapBorderX * nScale )// left border check
	{
		nMapBorderX = 0;
	}
	else if ( BIG_MAP_WIDTH * nScale < abs(int(x  * nScale + currentScreenWidth/2))) // right border check
	{
		//nMapBorderX = -x + currentScreenWidth/2+ currentScreenWidth/2 - ( BIG_MAP_WIDTH - x );
		nMapBorderX = currentScreenWidth - BIG_MAP_WIDTH* nScale;
		offsetx = (currentScreenWidth/2 - (BIG_MAP_WIDTH - x  ))* MAP_DEFINE_SIZE;
	}

	if ( 0 < nMapBorderY  * nScale ) // down border check
	{
		nMapBorderY = 0;
	}
	else if ( BIG_MAP_HEIGHT  * nScale < abs(int(y  * nScale + currentScreenHeight/2)))// top border check
	{
		nMapBorderY =  (currentScreenHeight - BIG_MAP_HEIGHT  * nScale);
		offsety = (currentScreenHeight/2 - (BIG_MAP_WIDTH - y  ))* MAP_DEFINE_SIZE;
	}
	setMapScale( MAP_DEFINE_SIZE );
	setMapPos(ccp(nMapBorderX , nMapBorderY));
}

// 首次扣除生命弹出的VIP界面时
void MainMap::FirstConsumsLifeDelay(float t)
{
	MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_VIP_DLG, 1 );
}

void MainMap::callFuncMoveHead(void)
{
	CCPoint bNextLevelPoint;
	int nLevel = 0;

#ifdef CANDY_STATISITICAL_DATA
	/*if(CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=5)
	{
		char* pLevel = (char*)CCString::createWithFormat("%d",CandyManager::currentLevel )->getCString();
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_48, pLevel);
	}*/
#endif
	if ( GAME_STATE_SUCCEE == MainMap::m_GameState )
	{
		MainMapUiLayer::m_mainmapuilayer->m_pPanel->setTouchEnabled( false );
	}

	if ( GAME_STATE_SUCCEE_NEXT == MainMap::m_GameState )
	{
		this->schedule(schedule_selector(MainMap::headMoveDelay), 1.0, kCCRepeatForever, 0);
	}
	nLevel = getPassStageNum();
	addMapLevelButton( nLevel,nLevel,0, false);

	bNextLevelPoint = getLevelNumFromLua( nLevel );
	//m_pParticle = CandyParticle::displayCandyParticle(CANDY_MAP_ACTIVE_NEW2, /*bNextLevelPoint*/ccp(0,0));
	//m_particlePos->getRenderer()->addChild( m_pParticle );
}

void MainMap::callFuncRewardCandy(void)
{
	if ( CommonData::getLastStarNumForLevel() < CommonData::getStarForLevel( getPassStageNum() - 1 )) 
		MainMapUiLayer::m_mainmapuilayer->passLevelRewardCandy();
}


void MainMap::buttonCallBack(CCObject *pSender)
{
 	UIButton *levelButton = (UIButton *)pSender;
 	CandyManager::currentLevel  = levelButton->getTag();
 	CommonData::m_gamemode = (int)levelButton->data;
 
#if defined ( CANDY_VERSIONS_FOR_SINGLE )
	MainMapUiLayer::showLevelInfo( CandyManager::currentLevel );

#else
	int lockResult = CommonData::isUnlockedLevel(CandyManager::currentLevel);
 	if (LILE_MIN_NUM >= AnalyseJson::logOnMsg.lifeInfo.lifeNum )
	{
 		//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LACKLIFE_DLG );
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_PAY_DLG,CANDY_PROP_LIFE );


	}
	else if(lockResult == 0)
	{
		MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_UNLOCKLEVEL_DLG ,CandyManager::currentLevel );
	}
	else if(lockResult == -1 || lockResult == 1)
	{
		MainMapUiLayer::showLevelInfo( CandyManager::currentLevel );
	}
#endif
}

/*#include "../CommonData/CommonData.h"*/
void MainMap::playMapBgm(void)
{
#ifndef WIN32
	if ( CommonData::getBackgroundState() )
	{
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_BUTTON_BGMUSIC);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_BUTTON_BGMUSIC, true);
	}
#endif
}

CCActionInterval* MainMap::getMoveAction(float time, CCPoint pos)
{
	CCActionInterval* move = CCMoveTo::create(time, pos);
	CCActionInterval* move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move, 0.6f );
	return move_ease_inout2;
}

// game level sucees, entey main map
// 增加一个参数 区别 成功 or 失败状态下 返回到地图界面的动作处理
void MainMap::EnteyMapScene( int para )
{
	m_GameState = para;

#ifdef CANDY_VERSIONS_FOR_SINGLE
	if ( GAME_STATE_SUCCEE == m_GameState || GAME_STATE_SUCCEE_NEXT == m_GameState)
		setPassStageNum(CandyManager::currentLevel+1);
#endif
	CommonData::submitTaskNum();
	// 进入loading
	Loading::replaceScence(CANDY_SCENCE_MAIN_MAP);
}

void MainMap::setPassStageNum(int num)
{
	int passStageNum = getPassStageNum();
	if(passStageNum <= num)
		CCUserDefault::sharedUserDefault()->setIntegerForKey("CandyPassStage", num);
}

int MainMap::getPassStageNum(void)
{
#if defined( CANDY_VERSIONS_FOR_SINGLE ) 

	int passStageNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("CandyPassStage");
	if(passStageNum <= 0)
		passStageNum = 1;
	return 225;//passStageNum;

#else

	int level;
	level = CommonData::getMaxLevel();
	if ( 0 == level)
	{
		level = 1;
	}
	else if ( 225 == level )
	{
		level = 225;
	}
	else
	{
		level  += 1;
	}
	return level;

#endif
}

void MainMap::initMapLuaFile()
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	char *mapInfoPath= (char *)CCString::createWithFormat("lua/MapLevel.lua")->getCString();	
	int err = pEngine->executeScriptFile( mapInfoPath );

	if( err )
	{
		CCLog("initMapLuaFile--luaL_dofile   %s\n", lua_tostring(levelLuaState, -1));
		CCAssert(0, "CandyMapData::luaL_dofile failed");
	}
	if ( !levelLuaState )
	{
		levelLuaState = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
	}
}

unsigned int MainMap::getDataNumFromLua(int num)
{
	unsigned int result;
	lua_pushnumber(levelLuaState, (lua_Number)num);
	lua_gettable(levelLuaState, -2);
	if ( lua_isnumber(levelLuaState, -1) )
		result = (unsigned int)lua_tonumber(levelLuaState, -1);
	lua_pop(levelLuaState, 1);
	return result;
}

CCPoint& MainMap::getLevelNumFromLua(int level)
{
	int passLevelNum = getPassStageNum();

	if ( 0 == passLevelNum )
		passLevelNum = 1;

	if ( !level )
	{
		std::list<UserStageInfoStr>::iterator p;
		p = AnalyseJson::logOnMsg.stageInfo.begin();
		int i;
#ifdef CANDY_VERSIONS_FOR_SINGLE
		for ( i = 1; i <= passLevelNum-1; i++ )
#else
		for ( i = 1; i <= (int)AnalyseJson::logOnMsg.stageInfo.size(); i++ )
#endif
		{
			// Get Level button position for Lua file! 
#ifdef CANDY_VERSIONS_FOR_SINGLE
			addMapLevelButton(i ,passLevelNum, 0, false);
#else
			addMapLevelButton(i ,passLevelNum,p->score, false);
			//CCLog( "passLevelNum :%d" ,p->level);
			p++;
#endif
		}

		return m_nLevelPos;
	}
	else
	{
		char *LevelNum= (char *)CCString::createWithFormat("MapLevel%d",  level)->getCString();
		lua_getglobal(levelLuaState, LevelNum);
		m_nLevelPos.x = getTableNumFromLua(level, 1 );
		m_nLevelPos.y = getTableNumFromLua(level, 2 );

		return m_nLevelPos;
	}
}

void MainMap::addMapLevelButton(int level, int maxlevel, int score, bool isEnabled)
{
//	if ( level >= 225 )
//		level = maxlevel;
//
//	int x, y ,nlevel, btncolor;
//	char *LevelNum= (char *)CCString::createWithFormat("MapLevel%d",  level)->getCString();
//	lua_getglobal(levelLuaState, LevelNum);
//
//	x = getTableNumFromLua( level, 1 );
//	y = getTableNumFromLua( level, 2 );
//	nlevel = getTableNumFromLua( level, 3 );
//	CommonData::m_gamemode = btncolor = getTableNumFromLua( level, 4 );
//
//	if ( maxlevel == level )
//	{
//		if ( !m_particlePos )
//		{
//			m_particlePos = UIImageView::create();
//			m_particlePos->setTexture("Image/MainMapUi/editboxBG.png");
//			bigMapUiLayer->addWidget( m_particlePos );
//		}
//		m_particlePos->setPosition( ccp(x+2, y));
//	}
//
//	// Add Level Button!
//	UIButton* levelBut = UIButton::create();
//	char *btnColorN = (char *)CCString::createWithFormat("Image/BigMap_1/Mode%dLevelIconNormal.png",  btncolor)->getCString();
//	char *btnColorP = (char *)CCString::createWithFormat("Image/BigMap_1/Mode%dLevelIconDisable.png",  btncolor)->getCString();
//	char *levelName = (char *)CCString::createWithFormat("LevBut%d",  nlevel)->getCString();
//
//	levelBut->data = (void*)btncolor;
//	levelBut->setName( levelName );
//	levelBut->setTag( nlevel ); // Setting button level!!
//	levelBut->setZOrder( 1 );
//	levelBut->setPosition( ccp(x, y) );
//	levelBut->setVisible( true );
//	levelBut->setScale( 0.5f );
//	levelBut->setTextures( btnColorN, btnColorP, btnColorP);
//	levelBut->setTouchEnabled( true );
//	levelBut->isEffects( true );
//	levelBut->addReleaseEvent(this, coco_releaseselector(MainMap::buttonCallBack));
//	bigMapUiLayer->addWidget( levelBut );
//
//	int lockResult = CommonData::isUnlockedLevel(level);
//	if(lockResult == 0)
//	{
//		UIImageView *lockImg = UIImageView::create();
//		lockImg->setTexture("Image/CandyGame/Others/lock.png");
//		lockImg->setPosition( ccp(x, y+10) );
//		lockImg->setTag(2000 + nlevel);//待定
//		lockImg->setScale(0.5f);
//		lockImg->setZOrder(1000);
//
//		UIImageView *starNum = UIImageView::create();
//		starNum->setTexture("Image/CandyGame/Others/lock_star.png");
//		starNum->setPosition( ccp(-22,-60) );
//		lockImg->addChild(starNum);
//
//		UILabelAtlas *pLabelNum = UILabelAtlas::create();
//		pLabelNum->setProperty("0" , "Image/MainMapUi/MainMapUi/NumLabel/NumLabel1.png",28, 40, "-");  
//		pLabelNum->setScale(0.7f);
//		pLabelNum->setPosition( ccp(13,-60) );
//
//		list<UserUnlockLevelInfo>::iterator iter;
//		for(iter= AnalyseJson::logOnMsg.unlockInfo.begin();	iter!=AnalyseJson::logOnMsg.unlockInfo.end(); iter++)
//		{
//			if(iter->level == level)
//			{
//				break;
//			}
//		}
//		pLabelNum->setStringValue(CCString::createWithFormat("%d",iter->needStar)->getCString());
//		lockImg->addChild(pLabelNum);
//
//		bigMapUiLayer->addWidget(lockImg);
//	}
//
//	if ( isEnabled )
//		levelBut->disable( true );
//
//	char *strLevelNum= (char *)CCString::createWithFormat("%d",  nlevel)->getCString();
//	UILabelBMFont* AtlevelNum = UILabelBMFont::create();
//	AtlevelNum->setFntFile( "Image/BigMap_1/NumFont/font.fnt");
//	AtlevelNum->setVisible( true );
//	AtlevelNum->setText( strLevelNum );
//	levelBut->addChild( AtlevelNum );
//
//#if !defined(CANDY_VERSIONS_FOR_SINGLE) 
//#if (1 )//CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
//
//	//Add Level Star based on the Score
//	if ( level < maxlevel )
//	{
//		int starnum = 0;
//		UIImageView* pStar1 = UIImageView::create();
//		if (score >= CandyMapData::getTargetScore(level, 1))
//		{		
//			char *strStarNum= (char *)CCString::createWithFormat("star%d",  nlevel)->getCString();
//			pStar1->setName( strStarNum );
//			pStar1->setTexture( "Image/MainMapUi/m_pic_star1.png" );
//			pStar1->setVisible( true );
//			pStar1->setZOrder( 5 );
//			pStar1->setScale( 0.7f );
//			pStar1->setPosition(ccp(x - 33 + 12, y-35 + 10 + 4));
//			bigMapUiLayer->addWidget( pStar1 );//   addWidget( pStar1 );
//
//			AnalyseJson::taskTable.curstarnum += 1;
//			starnum++;
//		}
//
//		if (score >= CandyMapData::getTargetScore(level, 2))
//		{
//			UIImageView* pStar2 = UIImageView::create();
//			pStar2->setTexture( "Image/MainMapUi/m_pic_star2.png" );
//			pStar2->setVisible( true );
//			pStar2->setZOrder( 5 );
//			pStar2->setPosition(ccp( 30, 3));
//			pStar1->addChild( pStar2);
//
//			AnalyseJson::taskTable.curstarnum += 1;
//			starnum++;
//		}
//		if (score >= CandyMapData::getTargetScore(level, 3))
//		{
//			UIImageView* pStar3 = UIImageView::create();
//			pStar3->setTexture( "Image/MainMapUi/m_pic_star3.png" );
//			pStar3->setVisible( true );
//			pStar3->setZOrder( 5 );
//			//pStar3->setScale( 0.7f );
//			//pStar3->setPosition(ccp(x - 33 + 60 - 12, y-35 + 10 + 4));
//			pStar3->setPosition(ccp( 60 ,  0));
//			pStar1->addChild( pStar3 );
//
//			AnalyseJson::taskTable.curstarnum += 1;
//			starnum++;
//		}
//
//		std::list<UserStageInfoStr>::iterator item = AnalyseJson::logOnMsg.stageInfo.begin();
//		for (; item!=AnalyseJson::logOnMsg.stageInfo.end(); item++)
//		{
//			if (item->level == level)
//			{
//				item->starnum = starnum;
//				break;
//			}
//		}
//
//	}
//#endif
//#endif

}

unsigned int MainMap::getTableNumFromLua(const int level,const int num)
{
	unsigned int result = 0;

	lua_pushnumber(levelLuaState, (lua_Number)num);
	lua_gettable(levelLuaState, -2);

	result = (unsigned int)lua_tonumber(levelLuaState, -1);
	
	lua_pop(levelLuaState, 1);
	return result;
}

void MainMap::setMapScale(float newScale)
{
	if(newScale > MAP_MAX_SCALE_NUM * MAP_EXCESS_SCALE_NUM)
	{
		newScale = MAP_MAX_SCALE_NUM * MAP_EXCESS_SCALE_NUM;
	}
	else if(newScale < MAP_MIN_SCALE_NUM / MAP_EXCESS_SCALE_NUM)
	{
		newScale = MAP_MIN_SCALE_NUM / MAP_EXCESS_SCALE_NUM;
	}

	float lastScale = getScale();

	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * 720/currentScreenWidth;

	CCPoint centerPos =  ccp(currentScreenWidth*0.5f, currentScreenHeight *0.5f);
	CCPoint pos = this->getPosition();

	CCPoint centerPosInMap1 =  ccp((centerPos.x - pos.x)/lastScale, (centerPos.y - pos.y)/lastScale);
	CCPoint centerPosInMap2 =  ccp((centerPos.x - pos.x)/newScale, (centerPos.y - pos.y)/newScale);

	setScale(newScale);

	CCPoint newPos = ccp(pos.x +( centerPosInMap2.x -centerPosInMap1.x)*newScale , pos.y +( centerPosInMap2.y -centerPosInMap1.y)*newScale);
	setPosition(newPos);
}

void MainMap::updateMapScale(float time)
{
	float scale = getScale();
	if(scale> MAP_MAX_SCALE_NUM)
	{
		scale  = scale *pow(MAP_MAX_SCALE_ELASTICITY,time*60);
		if(scale < MAP_MAX_SCALE_NUM)
			scale = MAP_MAX_SCALE_NUM;
		setMapScale(scale);
	}
	else if(scale < MAP_MIN_SCALE_NUM)
	{
		scale  = scale *pow(MAP_MIN_SCALE_ELASTICITY,time*60);
		if(scale > MAP_MIN_SCALE_NUM)
			scale = MAP_MIN_SCALE_NUM;
		setMapScale(scale);
	}
}

void MainMap::setMapPos(CCPoint pos)
{
	float scale = getScale();
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight;// * 720/currentScreenWidth;

	if(pos.x > MAP_MOVE_MAX_OFFSET * scale)
	{
		pos.x = MAP_MOVE_MAX_OFFSET* scale;
	}
	else if(pos.x < /*TARGET_SCREEN_WIDTH*/currentScreenWidth -BIG_MAP_WIDTH * scale - MAP_MOVE_MAX_OFFSET* scale )
	{
		pos.x  = /*TARGET_SCREEN_WIDTH*/currentScreenWidth -BIG_MAP_WIDTH * scale - MAP_MOVE_MAX_OFFSET* scale ;
	}

	if(pos.y > MAP_MOVE_MAX_OFFSET* scale)
	{
		pos.y = MAP_MOVE_MAX_OFFSET* scale;
	}
	else if(pos.y < fixedScreenHeight -BIG_MAP_HEIGHT* scale - MAP_MOVE_MAX_OFFSET* scale)
	{
		pos.y  = fixedScreenHeight -BIG_MAP_HEIGHT* scale - MAP_MOVE_MAX_OFFSET* scale;
	}
	setPosition(pos);
}

void MainMap::updateMapPos(float time)
{
	CCPoint pos = getPosition();
	float scale = getScale();

	float autoMoveLen = 5.0f*(time*60) *scale;

	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;

	if(pos.x > 0)
	{
		pos.x = pos.x - autoMoveLen;
		if(pos.x < 0)
			pos.x  = 0;
	}
	else if(pos.x < TARGET_SCREEN_WIDTH -BIG_MAP_WIDTH *scale)
	{
		pos.x = pos.x + autoMoveLen;
		if(pos.x > TARGET_SCREEN_WIDTH -BIG_MAP_WIDTH *scale)
			pos.x  = TARGET_SCREEN_WIDTH -BIG_MAP_WIDTH *scale;
	}

	if(pos.y > 0)
	{	
		pos.y = pos.y - autoMoveLen;
		if(pos.y < 0)
			pos.y  = 0;
	}
	else if(pos.y < fixedScreenHeight -BIG_MAP_HEIGHT *scale )
	{
		pos.y = pos.y + autoMoveLen;
		if(pos.y > fixedScreenHeight -BIG_MAP_HEIGHT *scale)
			pos.y  = fixedScreenHeight -BIG_MAP_HEIGHT *scale;
	}
	setPosition(pos);
}

void MainMap::headMoveDelay(float t)
{
	this->unschedule( schedule_selector(MainMap::headMoveDelay) );

	MainMapUiLayer::m_mainmapuilayer->m_pPanel->setTouchEnabled( false );

	if(CommonData::getMaxLevel() != 5 || CandyManager::currentLevel != 5)
	{
		if ( AnalyseJson::unLockConfig.starTask ==  MainMap::getPassStageNum()-1 )		
			MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_UNLOCKSTARTASK ); //第三关过关,提示文字"您解锁了<星星收集>"
		else if ( AnalyseJson::unLockConfig.mainTask ==  MainMap::getPassStageNum()-1 )		
			MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_UNLOCKMAINTASK ); //第8关过关,提示文字"您解锁了<糖果之旅>"
		else if ( AnalyseJson::unLockConfig.friendFun ==  MainMap::getPassStageNum()-1 )		
			MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_UNLOCKMSGORFRIEND ); //第20关过关,提示文字"您解锁了<好友列表>和<消息>"
		else if ( AnalyseJson::unLockConfig.dailyTask ==  MainMap::getPassStageNum()-1 )		
			MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_UNLOCKDAYTASK ); //第30关过关,提示文字"您解锁了<每日任务>"
		else
		{
			int lockResult = CommonData::isUnlockedLevel(CandyManager::currentLevel +1);
			if(lockResult == 0)
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_UNLOCKLEVEL_DLG ,CandyManager::currentLevel + 1);
			}
			else if(lockResult == -1 || lockResult == 1)
			{
				MainMapUiLayer::showLevelInfo( CandyManager::currentLevel +1);
				MainMapUiLayer::m_mainmapuilayer->m_pPanel->setTouchEnabled( true );
			}
		}
	}
	else if(CommonData::getMaxLevel() == 5 && CandyManager::currentLevel == 5)
	{
		if(AnalyseJson::logOnMsg.baseInfo.avatar_upd_times ==0)
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_CHANGEINFO_DLG
				);
			MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_CHANGEINFO );	// 过完第5关弹出的更改资料时
		}
	}	

	//　只要成功过关　就会弹　优先级底
	//MainMapUiLayer::m_mainmapuilayer->showOtherPrompt( PROMPT_TYPE_RANKEDUP );	// 排名上升
	//　世界排名跳跃更新

	CandyManager::currentLevel +=1;
#ifdef CANDY_STATISITICAL_DATA
	/*if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_69 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_79 );*/
#endif
}

void MainMap::HideMapUi(void)
{
	//int nLevel = getPassStageNum();

	//// hide level button
	//for (int i = 1; i <= nLevel; i++)
	//{
	//	char *levelName = (char *)CCString::createWithFormat("LevBut%d",  i)->getCString();
	//	UIButton* pLevelBut = (UIButton*)bigMapUiLayer->getWidgetByName( levelName );
 //		if ( pLevelBut )
 //			pLevelBut->setHideEffects();

	//	char *strStarNum= (char *)CCString::createWithFormat("star%d",  i)->getCString();
	//	UIImageView* pStarImg = NULL;
	//	pStarImg = (UIImageView*)bigMapUiLayer->getWidgetByName( strStarNum );
	//	if ( pStarImg )
	//		pStarImg->setVisible( false );
	//}

	// hide head img
	/*if ( m_pHeadbgImg )
		m_pHeadbgImg->setVisible( false );*/

	/*if (m_pParticle)
		m_pParticle->setVisible( false );*/

#if defined ( DEMO_FOR_GUEST )

	MainMapUiLayer::m_mainmapuilayer->SetTollgateTouchPriority(10000);

	// hide 
	if (MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout)
	{
		UIImageView* pTopBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_topIco"));
		UIImageView* pLeftBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_leftIco"));
		UIImageView* pRightBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_rightIco"));
		UIImageView* pDownBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_downIco"));


		pTopBar->runAction( CCMoveTo::create(0.3f, ccp(0, pTopBar->getSize().height + 115)));

		pLeftBar->runAction( CCSequence::create(
			CCMoveTo::create(0.3f, ccp(-115,  pLeftBar->getPosition().y)),
			CCCallFunc::create(this, callfunc_selector(MainMap::funcallBarMoveOut)),
			NULL));
		pRightBar->runAction( CCMoveTo::create(0.3f, ccp(CCDirector::sharedDirector()->getWinSize().width + 115,  pLeftBar->getPosition().y)));
		pDownBar->runAction( CCMoveTo::create(0.3f, ccp(CCDirector::sharedDirector()->getWinSize().width,  -110 )));
	}
#endif
}

void MainMap::DisplayMapUi(void)
{
	if ( 0 < MainMapUiLayer::m_mainmapuilayer->widgetList.size() )
		return;
	MainMapUiLayer::m_mainmapuilayer->SetTollgateTouchPriority(-128);

	//int nLevel = getPassStageNum();
	//touchPoint[0] = CCPointMake(0,0);
	//touchPoint[1] = CCPointMake(0,0);
	//touchNum = 0;

	//for (int i = 1; i <= nLevel; i++)
	//{
	//	char *levelName = (char *)CCString::createWithFormat("LevBut%d",  i)->getCString();
	//	UIButton* pLevelBut = (UIButton*)bigMapUiLayer->getWidgetByName( levelName );
	//	if ( pLevelBut )
	//		pLevelBut->setDisPlayEffects();

	//	//char *strStarNum= (char *)CCString::createWithFormat("star%d",  i)->getCString();
	//	char strStarNum[20] = {0};
	//	sprintf(strStarNum, "star%d",  i);
	//	UIImageView* pStarImg = NULL;
	//	pStarImg = (UIImageView*)bigMapUiLayer->getWidgetByName( strStarNum );
	//	if ( pStarImg )
	//		pStarImg->setVisible( true );
	//}

	////if ( m_pHeadbgImg )
	////	m_pHeadbgImg->setVisible( true );

	//if ( m_pParticle )
	//	m_pParticle->setVisible( true );

#if defined (CANDY_VERSIONS_FOR_SINGLE)
	if (MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout)
	{
		UIButton* pTools = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("BtnSetting"));
		if ( pTools && pTools->isVisible() )			pTools->setTouchEnabled( true );
	}

#elif defined ( DEMO_FOR_GUEST )

	float nDelayTime1 = 0.2f;
	float nDelayTime2 = 0.041f;

	if (MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout)
	{
		UIImageView* pTopBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_topIco"));
		UIImageView* pLeftBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_leftIco"));
		UIImageView* pRightBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_rightIco"));
		UIImageView* pDownBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_downIco"));

		pLeftBar->setVisible( true );
		pRightBar->setVisible( true );
		pDownBar->setVisible( true );

		pTopBar->runAction(  CCMoveTo::create(0.3f, ccp(0, 0)) );
		pLeftBar->runAction(CCMoveTo::create(0.3f, ccp( 0,  pLeftBar->getPosition().y)));
		pRightBar->runAction( CCMoveTo::create(0.3f, ccp(CCDirector::sharedDirector()->getWinSize().width,  pLeftBar->getPosition().y)));
		pDownBar->runAction( CCMoveTo::create(0.3f, ccp(CCDirector::sharedDirector()->getWinSize().width,  0 )));

		MainMapUiLayer::m_mainmapuilayer->m_gameShopBut->setTouchEnable(true);
		//MainMapUiLayer::m_mainmapuilayer->m_MessageBut->setTouchEnable(true);

		UIButton* m_btnGameVip = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameVip")); 
		UIButton* pgameGiftBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameGift")); 
		UIButton* pBtnSetting = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnSetting" ));
		UIButton* pBtnTollgate  = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnSetting_0" ));
		//UIButton* pBtnTask = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnTask" ));
		//UIButton* pBtnMyInformat = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnMyInfo" ));
		//UIButton* pBtnNotice = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnNotice" ));
		//UIButton* pBtnRANK = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnGameRank")); 
		//UIButton* pBtnKnapsack = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnKnapsack" ));
		UIButton* pBtnZhuanpan = dynamic_cast<UIButton*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName( "BtnZhuanpan" ));
		if ( m_btnGameVip )
			m_btnGameVip->setTouchEnabled( true );

		if ( pgameGiftBut )
		{
			pgameGiftBut->setTouchEnabled( true );

			if(CommonData::m_GiftIDBuyNow == 0)
			{
				pgameGiftBut->setTouchEnabled( false );
			}
		}

		/*if ( pBtnKnapsack )
			pBtnKnapsack->setTouchEnabled( true );
		if ( pBtnTask )
			pBtnTask->setTouchEnabled( true );
		if ( pBtnMyInformat )
			pBtnMyInformat->setTouchEnabled( true );
		if ( pBtnNotice )
			pBtnNotice->setTouchEnabled( true );
		if ( pBtnRANK )
			pBtnRANK->setTouchEnabled( true );*/
		if (pBtnZhuanpan)
		{
			pBtnZhuanpan->setTouchEnabled(true);
		}

		//用于pageview的按钮
		if (pBtnTollgate->isVisible())
		{
			pBtnSetting->setTouchEnabled( false );
			pBtnSetting->setVisible( false);
		}
		else
		{
			pBtnSetting->setTouchEnabled( true );
			pBtnSetting->setVisible( true );

		}
		


		UIButton* gameLifeBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("lifebtn"));
		//UIButton* GamegemBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("gembtn"));
		//UIButton* friendBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("BtnFriend")); 
		//UIButton* wemeChatBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btn_wemechat")); 
		UIButton* pTools = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("BtnSetting"));
		//UIButton* messageBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("BtnMessages")); 
		//UIButton* btnSiginIn = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("btnSiginIn")); 
		//UIImageView* Gamegembg = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("showgembg"));

		//if ( btnSiginIn && btnSiginIn->isVisible() )	btnSiginIn->setTouchEnabled( true );
		//if ( Gamegembg && Gamegembg->isVisible() )		Gamegembg->setTouchEnabled( true );
		if ( gameLifeBut && gameLifeBut->isVisible() )	gameLifeBut->setTouchEnabled( true );
		//if ( GamegemBut && GamegemBut->isVisible() )	GamegemBut->setTouchEnabled( true );
		//if ( friendBut && friendBut->isVisible() )		friendBut->setTouchEnabled( true );
		//if ( wemeChatBut && wemeChatBut->isVisible() )	wemeChatBut->setTouchEnabled( true );
		if ( pTools && pTools->isVisible() )			pTools->setTouchEnabled( true );

		/*if ( messageBut && messageBut->isVisible() && MainMapUiLayer::m_mainmapuilayer->messageListLayout )	
		{ 
			messageBut->setTouchEnabled( true ); 
			messageBut->stopAllActions(); 
			messageBut->isEffects(true); 
		}*/

	}

	char *Gemnum = (char*)CCString::createWithFormat( "%d", AnalyseJson::logOnMsg.baseInfo.gemNum )->getCString();
	/*if ( MainMapUiLayer::m_mainmapuilayer->m_pGemNum )
		MainMapUiLayer::m_mainmapuilayer->m_pGemNum->setStringValue( Gemnum );*/

	const char *nlifenum = CCString::createWithFormat("%d",  AnalyseJson::logOnMsg.lifeInfo.lifeNum )->getCString();//itoa(AnalyseJson::logOnMsg.lifeInfo.lifeNum);
	if ( MainMapUiLayer::m_mainmapuilayer->m_plifeNum )
		MainMapUiLayer::m_mainmapuilayer->m_plifeNum->setStringValue( nlifenum );


	UILabelAtlas* pCandyMoneyLabel = dynamic_cast<UILabelAtlas*>( MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("NumberCandyCandy") );
	if ( pCandyMoneyLabel )
		pCandyMoneyLabel->setStringValue( CCString::createWithFormat("%d", AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString() );

	if ( 5 <= AnalyseJson::logOnMsg.lifeInfo.lifeNum )
	{
		MainMapUiLayer::m_mainmapuilayer->m_pAddLifeTips->setVisible( false );
		MainMapUiLayer::m_mainmapuilayer->m_pFullLifeTips->setVisible( true );
	}

#endif
}

void MainMap::initPreloadEffect(void)
{
	EffectMusicPath[MUSIC_ITEM_BUTTON_E] = (char *)MUSIC_BUTTON_EFFECT;
	EffectMusicPath[MUSIC_ITEM_MOVEHEAD_E] = (char *)MUSIC_MOVEHEAD_EFFECT;
	EffectMusicPath[MUSIC_ITEM_ROULETTE_E] = (char *)MUSIC_MOVEHEAD_EFFECT;
	for (int i = 0; i < MUSIC_ITEM_MAX_NUM; i++)
	{
		SimpleAudioEngine::sharedEngine()->preloadEffect( EffectMusicPath[i] );
	}
}

void MainMap::unLoadEffect(void)
{
	for (int i = 0; i < MUSIC_ITEM_MAX_NUM; i++)
	{
		SimpleAudioEngine::sharedEngine()->unloadEffect( EffectMusicPath[i] );
	}
}

void MainMap::PlayEffect(int index)
{
	if ( !CommonData::getSoundEffectState() )
		return;

	switch(index)
	{
	case MUSIC_ITEM_BUTTON_E:
		SimpleAudioEngine::sharedEngine()->playEffect( EffectMusicPath[MUSIC_ITEM_BUTTON_E] );
		break;
	case MUSIC_ITEM_MOVEHEAD_E:
		SimpleAudioEngine::sharedEngine()->playEffect( EffectMusicPath[MUSIC_ITEM_MOVEHEAD_E] );
		break;
	default:
		break;
	}
}

void MainMap::StopAllEffect(void)
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void MainMap::stopAllMusic(void)
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void MainMap::setVipHead( void )
{
	UIImageView* pVipMark = (UIImageView*)m_pHeadbgImg->getChildByName("viphead");
	// vip 皇冠
	if ( 0 != AnalyseJson::logOnMsg.baseInfo.isVip && !pVipMark)
	{
		UIImageView* pVipImg = UIImageView::create();
		pVipImg->setTexture( "Image/BigMap_1/ImgVipTips.png" );
		pVipImg->setName( "viphead" );
		pVipImg->setZOrder( 7 );
		pVipImg->setPosition(ccp(0, 55));
		m_pHeadbgImg->addChild( pVipImg);
	}
}

void MainMap::funcallBarMoveOut( void )
{
	UIImageView* pLeftBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_leftIco"));
	UIImageView* pRightBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_rightIco"));
	UIImageView* pDownBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_downIco"));
	pLeftBar->setVisible( false );
	pRightBar->setVisible( false );
	pDownBar->setVisible( false );
}

void MainMap::funcallBarMoveEntry( void )
{
	UIImageView* pLeftBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_leftIco"));
	UIImageView* pRightBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_rightIco"));
	UIImageView* pDownBar = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("map_downIco"));
	pLeftBar->setVisible( true );
	pRightBar->setVisible( true );
	pDownBar->setVisible( true );
}
