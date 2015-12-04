#include "CandyUiLayer.h"
#include "CandyManager.h"
#include "../MainMap/MainMapScene.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../CommonData/CommonWidgt.h"
#include "../MsgMgr/AnalyseJson.h"
#include "PlayGameScene.h"
#include "../MsgMgr/MsgMgr.h"
#include "../CppCallJava/CppCallJava.h"
#include "CandyPay/CandyPay.h"
#include "Loading/LoadingScene.h"


USING_NS_CC;

#define CANDY_GAME_UI_LAYOUT_FILE1		"Image/CandyGame/CandyGameUi/CandyGameUi4.ExportJson"
#define CANDY_GAME_UI_LAYOUT_FILE2		"Image/CandyGame/CandyGameUi/CandyGameUi2.ExportJson"

#define GAME_PAUSE_LAYOUT_FILE			"Image/CandyGame/CandyGameLayout/CandyGamePause.ExportJson"



#define COLLECT_TYPE_IMG_PATH			"Image/CandyGame/CollectType"
#define COMBO_PRAISE_IMG_PATH			"Image/CandyGame/Others/comboPraise"

#define RABBIT_FALL_LENGTH				150

#define FULL_ENERGY						AnalyseJson::logOnMsg.baseInfo.all_skill


CandyUiLayer::CandyUiLayer()
{
	selectedFlag = false;
	
	currentScore = -1;
	moveRemain = 0;
	timeRemain = 0;
	jellyFinishNum = -1;
	cherryFinishNum = -1;
	chestnutFinishNum = -1;
	targetScoreNum = -1;
	gameUiLayer = NULL;
	gameUiLayout = NULL;
	gamePauseLayout = NULL;
	gamePropLayout = NULL;

	percentingNode = NULL;
	percentDoneNode= NULL;
	for(int i=0; i<5; i++)
		propsNum[i] = -1;

	m_pCandy1 = NULL;
	m_pCandy2 = NULL;
	m_pCandy3 = NULL;
	m_pCandy4 = NULL;
	//m_pShenDeng = NULL;
	m_pShenDengRabbit = NULL;
	gameShopLayout = NULL;
	SuperGiftLayout = NULL;

// 	m_pRabbitShake2 = NULL;
// 	m_pRabbitShake1 = NULL;
	bPlayAnim = false;

//	m_bReward = false;
	m_nRewardType = -1;
	m_nRewardNum = -1;
}

CandyUiLayer::~CandyUiLayer()
{
	
}
		
bool CandyUiLayer::init(void)
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	SettingBtn();

	return true;
}

void CandyUiLayer::onEnter(void)
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);

	setKeypadEnabled(true);
	scheduleUpdate();
	
	showGameWidget(CANDY_GAME_UI_WIDGE);

	if ( CommonData::getMaxLevel() == 0  && CandyManager::currentLevel == 1 )
	{
	}
	else if(CommonData::getMaxLevel() == 1 && CandyManager::currentLevel == 2 )
	{
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3 )
	{
	}
	else
	{
		MsgMgr::sendMagicLampTimeRequest(AnalyseJson::logOnMsg.baseInfo.id);
	}
	
	//弹出超级大礼包
// 	if (!CommonData::m_isShowSuperGiftInGame && CandyManager::gameMode != CANDY_MODE_TIMING && 
// 		CandyManager::currentLevel > 5 && AnalyseJson::logOnMsg.baseInfo.isBuySuperGift == 0)
// 	{
// 		CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(false);
// 		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PAUSE);
// 
// 		CCActionInterval* delay = CCDelayTime::create(3.5);
// 		CCCallFuncO* showSuperGift = CCCallFuncO::create(this,callfuncO_selector(CandyUiLayer::ShowSuperGiftUI),NULL);
// 		
// 		runAction(CCSequence::create(delay,showSuperGift,NULL));
// 
// 		CommonData::m_isShowSuperGiftInGame = true;
// 	}	
}

void CandyUiLayer::onExit(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();

	/*if(m_pShenDeng)
	{
		m_pShenDeng->removeFromParent();
	}*/

	if(m_pShenDengRabbit)
	{
		m_pShenDengRabbit->removeFromParent();
	}
// 	m_pRabbitShake1->removeFromParentAndCleanup(true);
// 	m_pRabbitShake2->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(gameUiLayout);
	CC_SAFE_RELEASE_NULL(gamePauseLayout);
}

bool CandyUiLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{	
	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_USE_PROP_GAME)
	{
		selectedFlag = false;
		if(CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), selectedIndex))
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(selectedIndex, MAP_CELL_EXIST))
			{
				CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(selectedIndex);
				if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
				{
					CommonData::m_isSwap = true;
					candyUsePropEnd();
					return false;
				}
				else if (CommonData::currentPropType == CANDY_PROP_OUT_COLORFULL || CommonData::currentPropType == CANDY_PROP_OUT_BOMBNEW)
				{
					//彩糖和包装糖处理，只能点击普通糖果false(alex)
					if (candy && candy->special == CANDY_SPECIAL_NORMAL)
					{
						selectedFlag = true;
					}
				}
				else if(CommonData::currentPropType == CANDY_PROP_IN_HAMMER )
				{
					//锤子
					selectedFlag = true;
				}
			}
			
		return true;
	}
	 return false;
}

void CandyUiLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(selectedFlag)
		{
			CandyIndex temIndex;
			CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), temIndex) ;
			if(selectedIndex.x != temIndex.x || selectedIndex.y != temIndex.y)
				selectedFlag = false;
// 			if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
// 			{cand
// 				if(selectedIndex.x != temIndex.x || selectedIndex.y != temIndex.y)
// 				{
// 					removeUsePropEffect();
// 					selectedFlag = false;
// 				}
// 			}
// 			else
// 			{
// 				if(selectedIndex.x != temIndex.x || selectedIndex.y != temIndex.y)
// 					selectedFlag = false;
// 			}
		}
}

void CandyUiLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(selectedFlag)
	{
		if(CommonData::currentPropType != CANDY_PROP_IN_SWAP)
		{
			CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), CommonData::propSelectedIndex) ;
			if(selectedIndex.x == CommonData::propSelectedIndex.x && selectedIndex.y == CommonData::propSelectedIndex.y)
			{
				//选择框
				CandyManager::getInstance()->effectLayer->AddWinForSelectCandy(CandyManager::getInstance()->shareMgr->getPosByIndex(selectedIndex));
				candyUsePropEnd();
			}
				
			removeUsePropEffect();

			selectedFlag = false;
		}
	}
}
void CandyUiLayer::removeUsePropEffect()
{
	CCNode *node = getGameUiLayer()->getRootWidget()->getRenderer()->getChildByTag(789);
	if(node != NULL)
	{
		node->removeFromParent();
	}
	PlayGame *playGameLayer = (PlayGame*)CandyManager::getInstance()->getCurrentLayer();
	playGameLayer->addBg(true);

	CandyManager::getInstance()->effectLayer->removeChildByTag(889);
}

void CandyUiLayer::update(float time)
{
	updateTargetItem();
	updateScoreItem();
	updateMoveTimeItem();
	updatePropItemStates();
	updateEnergy();
	updateBuy();
	updateChatMsgNum();
	if(CandyManager::getInstance()->resultMgr->getCurrentResult() != CANDY_REWARDS_PROP)
	{
		updatePropNum();
	}
	if(CommonData::m_successPassFailed == 1)
	{
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_LOST_EFFECT);
		CommonData::m_successPassFailed = 0;
	}

	if ( CommonData::m_buyAdd5Failed == 1)
	{
		 CommonData::m_buyAdd5Failed = 0;
		 CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PASS_LEVEL);
	}

	if(CommonData::m_successPass == 1)
	{
		CandyManager::getInstance()->correctMapMgr->setDisplayCandyDispelTipsFlag(false);
		CandyManager::getInstance()->scoreMgr->totalScore = CandyMapData::getTargetScore(CandyManager::currentLevel, 3)+DIFFERENCE_DATA+1000;

		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_STAGE_CLEAR);
		
		CommonData::m_successPass = 0;
	}
	if(CommonData::m_nextStage == 1)
	{
		CandyManager::getInstance()->resultMgr->getResultLayer()->nextStageCallback();

		CommonData::m_nextStage = 0;
	}
	if(CommonData::m_superGift == 1)
	{
		list<UserPropInfoStr>::iterator it = AnalyseJson::logOnMsg.propInfo.begin();
		for (it; it != AnalyseJson::logOnMsg.propInfo.end(); ++it)
		{
			int propid = (*it).id;
			CandyStageIntro::buyPropCallBack(propid);
		}

		CommonData::m_superGift = 0;
	}
}

void CandyUiLayer::keyBackClicked(void)
{
	if(CandyManager::getInstance()->guideLayer->getGuiding())
		return;

	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_PLAYING && CandyManager::m_isPropBuying == false)
	{
 		showGameWidget(CANDY_GAME_SETTING);
	}
	else
	{

	}
}

void CandyUiLayer::showComboPraise(int combo)
{
	if(combo <=1)
		return;
	
	if(combo>7)
		combo = 7;
	
	const char *imgPath = CCString::createWithFormat("%s%d.png",COMBO_PRAISE_IMG_PATH,combo)->getCString();
	CCSprite *praiseSpr = CCSprite::create(imgPath);
	showTips(praiseSpr);
}

void CandyUiLayer::showTips(CCSprite *sprite)
{
	float scale = sprite->getScale();
	sprite->setPosition(ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f));
	sprite->setScale(0.01f);
	addChild(sprite);
	sprite->runAction(CCSequence::create(
										CCScaleTo::create(0.3f,1.4f*scale),
										CCMoveBy::create(1.0f,ccp(0,25)),
										CCCallFuncN::create(sprite, callfuncN_selector(CandyUiLayer::showTipsCallback)),
										NULL));

	sprite->runAction(CCSequence::create(
										CCDelayTime::create(1.1f),
										CCFadeOut::create(0.2f),
						 				NULL));
}

void CandyUiLayer::showTipsCallback(CCNode* sender)
{
	sender->removeFromParent();
}

		 	
 UILayer* CandyUiLayer::getGameUiLayer(void)
{
	if(!gameUiLayer)
		{
			gameUiLayer = UILayer::create();
			gameUiLayer->setTouchPriority(RESULT_WIDGET_PRIORITY);
			addChild(gameUiLayer,101);
		}
	return gameUiLayer;
}

 Layout* CandyUiLayer::getHelpUiLayout(void)
 {
	 Layout* pLayout = CommonWidgt::getHelpUI( WIDGET_TYPE_GAME );
	 pLayout->setZOrder( 2 );
	 return pLayout;
 }

 Layout* CandyUiLayer::getBuyGemUiLayout(void)
 {
	 Layout* pLayout = CommonWidgt::getBuyGemUI( WIDGET_TYPE_GAME );
	 pLayout->setZOrder( 2 );
	 return pLayout;
 }
 
void CandyUiLayer::showGameWidget(CandyGameWidgetType type)
{
	Layout* widget = NULL;	
	m_curWidgetType = type;
	switch(type)
		{
			case CANDY_GAME_UI_WIDGE:
				widget = getGameUiLayout();
				break;
				
			case CANDY_GAME_PAUSE_WIDGE:
				UIGray();
				widget = getGamePauseLayout();
				updateCurrentTargetData(widget);
				break;
				
			case CANDY_GAME_SETTING:
				widget = CommonWidgt::getSystemToolsUI(WIDGET_TYPE_GAME);
				widget->setVisible( true );
				widget->setTouchEnabled( true );
				UIPerform(widget);
				break;

			case CANDY_GAME_GUIDE:
				widget = getHelpUiLayout();
				UIPerform_Guide(widget);
				break;

			case CANDY_GAME_BUYGEM:
				widget = getBuyGemUiLayout();
				widget->setVisible( true );
				widget->setTouchEnabled( true );
				UIPerform_Guide(widget);
				break;
			case CANDY_GAME_SHOP:
				//游戏内商城
				widget = getShopLayout();
				widget->setTouchEnabled(true);
				ShopEasein();
				break;

			case CANDY_GAME_SUPERGIFT:
				//超级礼包
				widget = getSuperGiftLayout();
				SuperGiftEaseIn();
				break;
			default:
				return;
		}
	
	if(type != CANDY_GAME_UI_WIDGE )
	{
		float fixedScreenHeight = CandyShare::getFixedScreenHeight();
		widget->setPosition(ccp(0,(fixedScreenHeight - TARGET_SCREEN_HEIGHT)*0.5f));
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PAUSE);
		widget->setZOrder(100);
	}	
	getGameUiLayer()->addWidget((widget));
	if(type == CANDY_GAME_PAUSE_WIDGE)
	{
		CandyManager::getInstance()->resultMgr->getResultLayer()->performUI_Fall(widget);
	}
	
}

void CandyUiLayer::UIGray()
{
	CCLayerColor* grayLayer = CCLayerColor::create(ccc4(0,0,0,0));
	grayLayer->runAction(CCFadeTo::create(0.5f,170));
	getGameUiLayer()->getRootWidget()->getRenderer()->addChild(grayLayer,80,99);
}


void CandyUiLayer::UIPerform_Guide(Layout* widget)
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
	pImgDlg->setPosition( ccp(720+720/2, currentScreenHeight/2) );
	CCActionInterval* move1 = CCMoveTo::create(0.8f, ccp(currentScreenWidth/2, currentScreenHeight/2));
	CCActionInterval* move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move1, 0.9f );
	pImgDlg->runAction(CCSequence::create(
		move_ease_inout2,
		NULL)
		);
}

void CandyUiLayer::UIPerform(Layout* widget)
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	UIWidget* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
	if (!pImgDlg)
	{
		pImgDlg = dynamic_cast<UIPanel*>(widget->getChildByName( "m_img_dlg" ));
	}
	pImgDlg->setPosition( ccp(currentScreenWidth/2, currentScreenHeight * 1.5) );
	pImgDlg->setVisible( true );
	pImgDlg->stopAllActions();

	pImgDlg->runAction(	CommonData::getMoveAction(2, ccp(currentScreenWidth/2, currentScreenHeight * 0.5)) );
	widget->setPosition(ccp(0,0));
}

Layout* CandyUiLayer::getGameUiLayout(void)
{
	float fixedScreenHeight = CandyShare::getFixedScreenHeight();

	if(!gameUiLayout)
	{
		gameUiLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(
			fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT?CANDY_GAME_UI_LAYOUT_FILE1:CANDY_GAME_UI_LAYOUT_FILE1));
		gameUiLayout->retain();

		initUiWidget();
		initCandyScoreStar();
		adjustUiWidget(fixedScreenHeight);
	}
	return gameUiLayout;
}

Layout* CandyUiLayer::getGamePauseLayout(void)
{
	if( !gamePauseLayout)
		{
			gamePauseLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(GAME_PAUSE_LAYOUT_FILE));
			gamePauseLayout->retain();
			
			pausePlayOnButton = dynamic_cast<UIButton*>(gamePauseLayout->getChildByName("PlayOnButton"));
			pausePlayOnButton->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::gamePlayOnCallBack));

			pauseExitButton = dynamic_cast<UIButton*>(gamePauseLayout->getChildByName("ExitGameButton"));
			pauseExitButton->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::gameExitCallBack));
		}
	pausePlayOnButton->setTouchEnable(true);
	pauseExitButton->setTouchEnable(true);
	pausePlayOnButton->isEffects(true);
	pauseExitButton->isEffects(true);
	return gamePauseLayout;
}

void CandyUiLayer::initFlyCandy(void)
{
// 	m_pCandy1 = CCSprite::create("Image/CandyGame/tg000.png");
// 	gameUiLayout->getRenderer()->addChild(m_pCandy1,101);
// 	m_pCandy1->setVisible(false);
// 	//
// 	m_pCandy2 = CCSprite::create("Image/CandyGame/tg001.png");
// 	gameUiLayout->getRenderer()->addChild(m_pCandy2,101);
// 	m_pCandy2->setVisible(false);
// 	//
// 	m_pCandy3 = CCSprite::create("Image/CandyGame/tg002.png");
// 	gameUiLayout->getRenderer()->addChild(m_pCandy3,101);
// 	m_pCandy3->setVisible(false);
// 	//
// 	m_pCandy4 = CCSprite::create("Image/CandyGame/tg003.png");
// 	gameUiLayout->getRenderer()->addChild(m_pCandy4,101);
// 	m_pCandy4->setVisible(false);
}

void CandyUiLayer::initArmature(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if ( CommonData::getMaxLevel() == 0  && CandyManager::currentLevel == 1 )
	{
	}
	else if(CommonData::getMaxLevel() == 1 && CandyManager::currentLevel == 2 )
	{
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3 )
	{
	}
	else
	{   
		//去掉罐子动画(alex)
		/*m_pShenDeng = CCArmature::create("guanzi");
		gameUiLayout->getRenderer()->addChild(m_pShenDeng);

		m_pShenDeng->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyUiLayer::animationEvent1));
		m_pShenDeng->setPosition(ccp(size.width-145,75));
		m_pShenDeng->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(CandyUiLayer::onFrameEvent1));

		m_pShenDengRabbit = CCArmature::create("guanzi");
		gameUiLayout->getRenderer()->addChild(m_pShenDengRabbit,1000);
		m_pShenDengRabbit->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyUiLayer::animationEvent2));
		m_pShenDengRabbit->setPosition(ccp(size.width-80,120));
		m_pShenDengRabbit->setVisible(false);*/
	}

// 	CCSize size = CCDirector::sharedDirector()->getWinSize();
// 
// 	if ( CommonData::getMaxLevel() == 0  && CandyManager::currentLevel == 1 )
// 	{
// 	}
// 	else if(CommonData::getMaxLevel() == 1 && CandyManager::currentLevel == 2 )
// 	{
// 	}
// 	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3 )
// 	{
// 	}
// 	else
// 	{
// 		m_pRabbitShake1 = CCArmature::create("RabbitShake01");
// 		gameUiLayout->getRenderer()->addChild(m_pRabbitShake1,100);
// 		m_pRabbitShake1->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyUiLayer::animationEvent1));
// 		m_pRabbitShake1->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(CandyUiLayer::onFrameEvent1));
// 		m_pRabbitShake1->setPosition(ccp(size.width-60,20));
// 
// 		m_pRabbitShake2 = CCArmature::create("RabbitShake02");
// 		gameUiLayout->getRenderer()->addChild(m_pRabbitShake2,100);
// 		m_pRabbitShake2->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyUiLayer::animationEvent2));
// 		m_pRabbitShake2->setVisible(false);
// 		m_pRabbitShake2->setPosition(ccp(size.width-60,20 - RABBIT_FALL_LENGTH));
// 
// 	}
}

void CandyUiLayer::initUiWidget(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	/*UIImageView *pImg 	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("FuckerMan"));
	if(pImg)
	{
		pImg->setVisible(false);
	}*/
#ifndef CLOSE_ARMATURE
	initFlyCandy();
 	initArmature();
#endif

	//targetContent 	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("TargetContent"));
	moveContent 	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("MoveContent"));
	bottomUi 		= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("BottomUi"));
	//chatMsgNumBg	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("wemechatmsg"));


	//energyJarButton		= dynamic_cast<UIPanel*>(gameUiLayout->getChildByName("magic_lamp"));
	//energyJarButton->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyEnergyJarCallBack));
	
	//labelTime		= dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("label_time"));

	if ( CommonData::getMaxLevel() == 0  && CandyManager::currentLevel == 1)
	{
		//energyJarButton->setTouchEnabled(false);
		//labelTime->setVisible(false);
	}
	else if(CommonData::getMaxLevel() == 1 && CandyManager::currentLevel == 2)
	{
		//energyJarButton->setTouchEnabled(false);
		//labelTime->setVisible(false);
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3)
	{
		//energyJarButton->setTouchEnabled(false);
		//labelTime->setVisible(false);
	}
	else
	{
		//energyJarButton->setTouchEnabled(true);
		//labelTime->setVisible(true);
	}
	increaseEnergyJarPercentage(0);

	//settingButton	= dynamic_cast<UIButton*>(gameUiLayout->getChildByName("ButtonSettingButton"));
	//settingButton->setVisible( false );
	// 5关后开启
	if ( CandyManager::currentLevel > 5 )
	{
		//settingButton->setVisible( true );
		//settingButton->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candySettingCallBack));
		//settingButton->setTouchEnable(true);
		//settingButton->isEffects(true);
	}
	
	for(int i=0; i<5; i++)
	{
		PropButton[i]  = dynamic_cast<UIButton*>(gameUiLayout->getChildByName(
									CCString::createWithFormat("ButtonProp%d",i+1)->getCString()));
		PropButton[i]->setTouchEnable(true);
		PropButton[i]->isEffects(true);
		PropBuy[i]  = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName(
									CCString::createWithFormat("PropBuy%d",i+1)->getCString()));
		PropNumBg[i]= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName(
									CCString::createWithFormat("PropNum%d",i+1)->getCString()));
		PropNumLabel[i]= dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName(
									CCString::createWithFormat("PropNumLabel%d",i+1)->getCString()));

		//坐标适配
		CCPoint fixPos = PropButton[i]->getPosition();
		PropButton[i]->setPosition(ccp(fixPos.x,70));
	}
	PropButton[0]->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyPropExtendCallBack));
	PropButton[1]->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyPropChangeBSCallBack));
	PropButton[2]->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyPropChangeCCallBack));
	PropButton[3]->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyPropColorCallBack));
	PropButton[4]->addReleaseEvent(this, coco_releaseselector(CandyUiLayer::candyPropBoomCallBack));
	

	/*if ( 1 == CandyManager::currentLevel)
	{
		for( int i = 0; i<5; i++)
		{
			PropButton[i]->setVisible(false);
			PropButton[i]->disable();
		}
	}
	else if(CandyManager::currentLevel == 2 || CandyManager::currentLevel == 3)
	{
		for( int i = 0; i<5; i++)
		{
			PropButton[i]->setVisible(false);
			PropButton[i]->disable();
		}
		PropButton[0]->setVisible(true);
		PropButton[0]->active();
	}
	else if(CandyManager::currentLevel == 4  || CandyManager::currentLevel == 5)
	{
		for( int i = 0; i<5; i++)
		{
			PropButton[i]->setVisible(true);
			PropButton[i]->active(true);
		}
		PropButton[2]->setVisible(false);
		PropButton[2]->disable();
	}
	else
	{
		for( int i = 0; i<5; i++)
		{
			PropButton[i]->setVisible(true);
			PropButton[i]->active(true);
		}
	}*/
		
	actionNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("ActionNumLabel"));
	scoreNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("ScoreNumLabel"));
	moveLabelImg = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("MoveLabel"));
	timeLabelImg  = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("TimeLabel"));


	collectModePanel = dynamic_cast<UIPanel*>(gameUiLayout->getChildByName("CollectModeTarget"));
	collectTypeImg[0] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("CollectType1"));
	collectTypeImg[1] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("CollectType2"));
	collectTypeImg[2] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("CollectType3"));
	collectTypeLabel[0] = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("CollectLabel1"));
	collectTypeLabel[1] = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("CollectLabel2"));
	collectTypeLabel[2] = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("CollectLabel3"));

	jellyModePanel = dynamic_cast<UIPanel*>(gameUiLayout->getChildByName("DispelJellyTarget"));
	jellyNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("JellyNumLabel"));

	transportModePanel = dynamic_cast<UIPanel*>(gameUiLayout->getChildByName("TransportModeTarget"));
	chesnutImg 	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("ChesnutImg"));
	cherryImg	= dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("CherryImg"));
	chesnutNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("ChesnutNumLabel"));
	cherryNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("CherryNumLabel"));

	targetNumPanel = dynamic_cast<UIPanel*>(gameUiLayout->getChildByName("ScoreTarget"));	
	targetNumLabel = dynamic_cast<UILabelAtlas*>(gameUiLayout->getChildByName("TargetNumLabel"));	
	targetNumLabel->setVisible(false);

	targetNumPanel->setVisible(false);
	jellyModePanel->setVisible(false);
	transportModePanel->setVisible(false);
	collectModePanel->setVisible(false);
	
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
				targetNumLabel->setVisible(true);
				targetNumPanel->setVisible(true);
				break;

			case CANDY_MODE_JELLY:
				jellyModePanel->setVisible(true);
				break;

			case CANDY_MODE_INGREDIENT:
				transportModePanel->setVisible(true);
				if(CandyIngredients::numCherry ==0|| CandyIngredients::numChesnut==0)
					{
						UIImageView *emptyTarget = CandyIngredients::numCherry ==0?cherryImg:chesnutImg;
						UIImageView *exsitTarget = CandyIngredients::numCherry ==0?chesnutImg:cherryImg;
						UILabelAtlas *emptyLabel =  CandyIngredients::numCherry==0?cherryNumLabel:chesnutNumLabel;
						UILabelAtlas *exsitLabel =  CandyIngredients::numCherry==0?chesnutNumLabel:cherryNumLabel;

						CCPoint emptyPos = emptyTarget->getPosition();
						CCPoint exsitPos = exsitTarget->getPosition();
						CCPoint exsitOffset = ccp((exsitPos.x -emptyPos.x)*0.5f,0);
						CCPoint exsitLabelPos = exsitLabel->getPosition();
						
						exsitTarget->setPosition(ccpSub(exsitPos, exsitOffset));
						exsitLabel->setPosition(ccpSub(exsitLabelPos, exsitOffset));
						
						emptyTarget->setVisible(false);
						emptyLabel->setVisible(false);
						
					}
				break;

			case CANDY_MODE_TIMING:
				if(timeLabelImg)
					timeLabelImg->setVisible(true);
				if(moveLabelImg)
					moveLabelImg->setVisible(false);
				if(targetNumPanel)
					targetNumPanel->setVisible(true);
				// 时间模式禁用+5
// 				if(PropButton[0])
// 					PropButton[0]->disable(false);
				break;

			case CANDY_MODE_COLLECT:
				{
					collectModePanel->setVisible(true);
					for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
						currentCollect[i] = -1;
					
					int j=0;
					for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
						{
							if(CandyManager::collectCandy[i].targetNum <= 0)
								{
									collectTypeImg[i]->setVisible(false);
									collectTypeLabel[i]->setVisible(false);
									continue;
								}
							j++;
							collectTypeImg[i]->loadTexture(CCString::createWithFormat("%s/CollectType%d.png",COLLECT_TYPE_IMG_PATH,(int)CandyManager::collectCandy[i].type)->getCString());		
							collectTypeImg[i]->setTag( (int)CandyManager::collectCandy[i].type );
						}	
					if(1 == j)
					{
						collectTypeImg[0]->setPosition(collectTypeImg[1]->getPosition());
						collectTypeLabel[0]->setPosition(collectTypeLabel[1]->getPosition());
					}
					else if(2 == j)
					{
						int offsetX = 50;
						collectTypeImg[0]->setPosition(ccp(collectTypeImg[0]->getPosition().x+offsetX, collectTypeImg[0]->getPosition().y));
						collectTypeLabel[0]->setPosition(ccp(collectTypeLabel[0]->getPosition().x+offsetX, collectTypeLabel[0]->getPosition().y));
						collectTypeImg[1]->setPosition(ccp(collectTypeImg[1]->getPosition().x+offsetX, collectTypeImg[1]->getPosition().y));
						collectTypeLabel[1]->setPosition(ccp(collectTypeLabel[1]->getPosition().x+offsetX, collectTypeLabel[1]->getPosition().y));
					}

				}
				break;
		}
	update(0);

	//商城
	UIButton* shopBtn = dynamic_cast<UIButton*>(gameUiLayout->getChildByName("ButtonShop"));
	shopBtn->setTouchEnabled(true);
	shopBtn->addReleaseEvent(this,coco_releaseselector(CandyUiLayer::ShowShop));

	UIButton* m_pExit_Btn = dynamic_cast<UIButton*>(gameUiLayout->getChildByName("Exit_Btn"));
	m_pExit_Btn->setTouchEnabled(true);
	m_pExit_Btn->addReleaseEvent(this,coco_releaseselector(CandyUiLayer::SettingCallback));
}

void CandyUiLayer::ShowShop(CCObject* sender)
{
	CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );

	if( CandyManager::getInstance()->guideLayer->getGuiding() )
		return;

	showGameWidget(CANDY_GAME_SHOP);
}

void CandyUiLayer::CandyScoreFire(void)
{
	UIImageView *scoreBarBg = dynamic_cast<UIImageView *>(gameUiLayout->getChildByName("ScoreProgressBg"));
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_DOUBLESCOREFIRE_EFFECT, ccp(0,0),scoreBarBg->getRenderer(),0,-1);
	scoreNumLabel->setProperty(CCString::createWithFormat("%d",currentScore)->getCString(),"Image/CandyGame/Others/doubleScoreLabel.png",22,28,"0");
}

void CandyUiLayer::initCandyScoreStar(void)
{
	if(!gameUiLayout)
		return;

	scoreBar = dynamic_cast<UILoadingBar*>(gameUiLayout->getChildByName("ScoreProgress"));
	scoreBar->setPercent(0);
	
	CCPoint barPos =  scoreBar->getPosition();
	CCSize barSize = scoreBar->getContentSize();

	float starX[3];
	starX[0] 	= barPos.x -barSize.width *0.5 + barSize.width * CandyScore::starScoreNum[0]/CandyScore::starScoreNum[2] ;
	starX[1] 	= barPos.x -barSize.width *0.5 + barSize.width * CandyScore::starScoreNum[1]/CandyScore::starScoreNum[2] ;
	starX[2] 	= barPos.x -barSize.width *0.5 + barSize.width ;
	
	CCPoint originalPos;
	
	starGap[0] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("ScoreRedStar"));
	starGap[1] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("ScoreYellowStar"));
	starGap[2] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName("ScoreBlueStar"));

	for(int i=0; i<3; i++)
		{
			originalPos = starGap[i]->getPosition();
			starGap[i]->setPosition(ccp(starX[i], originalPos.y));
			grayStar[i] = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName(
						CCString::createWithFormat("ScoreGrayStar%d",i+1)->getCString()));
		}
}

//屏幕适配修正位置
void CandyUiLayer::adjustUiWidget(float fixedScreenHeight)
{
	CCPoint originalPos;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	originalPos = bottomUi->getPosition();
	bottomUi->setPosition(ccp(originalPos.x , originalPos.y + (winSize.height -TARGET_SCREEN_HEIGHT) ));

	originalPos = moveContent->getPosition();
	moveContent->setPosition(ccp(originalPos.x , originalPos.y + (winSize.height -TARGET_SCREEN_HEIGHT)));

	UIImageView *scoreBarBg = dynamic_cast<UIImageView *>(gameUiLayout->getChildByName("ScoreProgressBg"));
	originalPos = scoreBarBg->getPosition();
	scoreBarBg->setPosition(ccp(originalPos.x , originalPos.y + (winSize.height -TARGET_SCREEN_HEIGHT)));
}

void CandyUiLayer::updateChatMsgNum(void)
{	

}

void CandyUiLayer::updateTargetItem(void)
{
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
			case CANDY_MODE_TIMING:
				if(targetScoreNum != CandyScore::starScoreNum[0])
					{
						targetScoreNum = CandyScore::starScoreNum[0];
						targetNumLabel->setStringValue(CCString::createWithFormat("%d",targetScoreNum)->getCString());
					}
				break;

			case CANDY_MODE_JELLY:
					{
						int jellyRemain = CandyManager::getInstance()->jellyMgr->getCandyJellyRemainNum();
						int jellyTotal = CandyManager::getInstance()->jellyMgr->getCandyJellyTotalNum();
						if(jellyTotal - jellyRemain != jellyFinishNum)
							{
								jellyFinishNum = jellyTotal - jellyRemain;
								jellyNumLabel->setStringValue(CCString::createWithFormat("%d",jellyRemain)->getCString());
								drawTargetTick(jellyRemain, jellyNumLabel);

								drawTargetNumChange(jellyNumLabel, jellyRemain);
							}
					}
				break;	

			case CANDY_MODE_INGREDIENT:
					{
						if(cherryFinishNum != CandyManager::getInstance()->ingredientsMgr->numDropDoneCherry)
							{
								cherryFinishNum = CandyManager::getInstance()->ingredientsMgr->numDropDoneCherry;
								cherryNumLabel->setStringValue(CCString::createWithFormat("%d",CandyIngredients::numCherry -cherryFinishNum)->getCString());
								drawTargetTick(CandyIngredients::numCherry -cherryFinishNum, cherryNumLabel);

								drawTargetNumChange(cherryNumLabel, CandyIngredients::numCherry -cherryFinishNum);
							}

						if(chestnutFinishNum != CandyManager::getInstance()->ingredientsMgr->numDropDoneChesnut)
							{
								chestnutFinishNum = CandyManager::getInstance()->ingredientsMgr->numDropDoneChesnut;
								chesnutNumLabel->setStringValue(CCString::createWithFormat("%d",CandyIngredients::numChesnut-chestnutFinishNum)->getCString());
								drawTargetTick(CandyIngredients::numChesnut-chestnutFinishNum, chesnutNumLabel);
								drawTargetNumChange(chesnutNumLabel, CandyIngredients::numChesnut -chestnutFinishNum);
							}
					}
				break;	


			case CANDY_MODE_COLLECT:
				for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
					if(CandyManager::collectCandy[i].targetNum > 0)
						{
							if(currentCollect[i] != CandyManager::collectCandy[i].currentNum)
								{
									currentCollect[i] = CandyManager::collectCandy[i].currentNum;
									collectTypeLabel[i]->setStringValue(CCString::createWithFormat("%d",CandyManager::collectCandy[i].currentNum)->getCString());
									drawTargetTick(CandyManager::collectCandy[i].currentNum, collectTypeLabel[i]);
									drawTargetNumChange(collectTypeLabel[i], CandyManager::collectCandy[i].currentNum);
								}
						}
				break;	
		}
}

void CandyUiLayer::updateScoreItem(void)
{
	int lastCurrentScore = currentScore;
	currentScore = CandyManager::getInstance()->scoreMgr->getCurrentScore();
	if(lastCurrentScore != currentScore)
		{
			scoreNumLabel->setStringValue(CCString::createWithFormat("%d",currentScore)->getCString());
		}
	
}

void CandyUiLayer::updateMoveTimeItem(void)
{
	if(CandyManager::gameMode != CANDY_MODE_TIMING)
		{
			if(moveRemain != CandyMove::moveLimit)
				{
					actionNumLabel->setStringValue(CCString::createWithFormat("%d",CandyMove::moveLimit)->getCString());

					if(CandyMove::moveLimit - moveRemain ==1)
						{
							CCLabelAtlas *label = CCLabelAtlas::create(CCString::createWithFormat("%d",CandyMove::moveLimit)->getCString(),
								"Image/CandyGame/CandyGameUi/NumLabel/ScoreNumLabel.png",22,28,'0');
							label->setPosition(getStepNumLabelPos() );
							CandyManager::getInstance()->effectLayer->displayNumLabelChange(label);
						}
					
					moveRemain = CandyMove::moveLimit;
				}
		}
	else
		{
			if(CandyManager::timeLimit > 0)
				if(timeRemain != (int)CandyManager::timeLimit)
					{
						timeRemain = (int)CandyManager::timeLimit;
						actionNumLabel->setStringValue(CCString::createWithFormat("%d",timeRemain)->getCString());
					}
		}
}

void CandyUiLayer::updatePropItemStates(void)
{
	if(!CandyManager::getInstance()->resultMgr->getGameRunning())
		{
			//pPropMenu->setEnabled(false);
		}
}

// 更新失败界面达成目标数据
void CandyUiLayer::updateCurrentTargetData(Layout* layout)
{
	UIImageView *TickBg[4];
	UIImageView *Tick[4];
	
	int lastCurrentScore = currentScore;
	currentScore = CandyManager::getInstance()->scoreMgr->getCurrentScore();

	for(int i = 0; i<4; i++)
		{
			TickBg[i] = dynamic_cast<UIImageView*>(layout->getChildByName(
				CCString::createWithFormat("TickBg%d",i+1)->getCString()));
			Tick[i] = dynamic_cast<UIImageView*>(layout->getChildByName(
				CCString::createWithFormat("Tick%d",i+1)->getCString()));

			TickBg[i]->setVisible(false);
		}
	
	UIImageView *collectImg[3];
	UILabelAtlas 	*numLabel[3];
	for(int i = 0; i<3; i++)
		{
			collectImg[i] = dynamic_cast<UIImageView*>(layout->getChildByName(
				CCString::createWithFormat("CollectMode%d",i+1)->getCString())); 
			numLabel[i] = dynamic_cast<UILabelAtlas*>(layout->getChildByName(
				CCString::createWithFormat("NumLabel%d",i+1)->getCString()));
		}
	
	UIImageView *jellyImg= dynamic_cast<UIImageView*>(layout->getChildByName("JellyMode"));
	UIImageView *chesnutImg = dynamic_cast<UIImageView*>(layout->getChildByName("ChesnutMode"));
	UIImageView *cherryImg = dynamic_cast<UIImageView*>(layout->getChildByName("CherryMode"));
	UILabelAtlas 	*scoreLabel = dynamic_cast<UILabelAtlas*>(layout->getChildByName("ScoreNumLabel"));
	
	TickBg[0]->setVisible(true);
	Tick[0]->setVisible(CandyManager::getInstance()->scoreMgr->getCurrentScore() >= CandyScore::starScoreNum[0]);
	scoreLabel->setStringValue(CCString::createWithFormat("%d",/*CandyScore::starScoreNum[0]*/currentScore )->getCString());
		
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_JELLY:
					{
						TickBg[1]->setVisible(true);
						chesnutImg->setVisible(false);
						jellyImg->setVisible(true);
						collectImg[0]->setVisible(false);

						int jellyRemain = CandyManager::getInstance()->jellyMgr->getCandyJellyRemainNum();
						int jellyTotal = CandyManager::getInstance()->jellyMgr->getCandyJellyTotalNum();
						numLabel[0]->setStringValue(CCString::createWithFormat("%d/%d",jellyTotal-jellyRemain,jellyTotal)->getCString());
						Tick[1]->setVisible( jellyRemain <= 0 );
					}
				break;
			
			case CANDY_MODE_INGREDIENT:
					{
						TickBg[1]->setVisible(CandyIngredients::numChesnut==0?false:true);
						TickBg[2]->setVisible(CandyIngredients::numCherry==0?false:true);
						jellyImg->setVisible(false);
						collectImg[0]->setVisible(false);
						collectImg[1]->setVisible(false);
						chesnutImg->setVisible(CandyIngredients::numChesnut==0?false:true);
						cherryImg->setVisible(CandyIngredients::numCherry==0?false:true);
						numLabel[0]->setStringValue(CCString::createWithFormat("%d/%d",chestnutFinishNum, CandyIngredients::numChesnut)->getCString());
						numLabel[1]->setStringValue(CCString::createWithFormat("%d/%d",cherryFinishNum,CandyIngredients::numCherry)->getCString());
						Tick[1]->setVisible(chestnutFinishNum>=CandyIngredients::numChesnut);
						Tick[2]->setVisible(cherryFinishNum>=CandyIngredients::numCherry);
						
					}
				break;

			case CANDY_MODE_COLLECT:
					{
						jellyImg->setVisible(false);
						chesnutImg->setVisible(false);
						cherryImg->setVisible(false);
						
						for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
							{
								if(CandyManager::collectCandy[i].targetNum > 0)
									{
										
										TickBg[i+1]->setVisible(true);
										collectImg[i]->setVisible(true);
										collectImg[i]->loadTexture(CCString::createWithFormat(
											"%s/CollectType%d.png",COLLECT_TYPE_IMG_PATH,(int)CandyManager::collectCandy[i].type)->getCString());
										numLabel[i]->setStringValue(CCString::createWithFormat(
											"%d/%d",CandyManager::collectCandy[i].targetNum -CandyManager::collectCandy[i].currentNum,
												CandyManager::collectCandy[i].targetNum)->getCString());
										Tick[i+1]->setVisible((CandyManager::collectCandy[i].targetNum -CandyManager::collectCandy[i].currentNum < CandyManager::collectCandy[i].targetNum)?false:true);
									}
							}
							
							
					}
				break;
		}
}

void CandyUiLayer::drawTargetTick(int num, UILabelAtlas* label)
{
	if(num==0)
	{
		label->setStringValue("");
		CCSprite* tick = CCSprite::createWithSpriteFrameName("Others/Tick.png");	
		label->getRenderer()->addChild(tick);
	}
}

CCLabelAtlas* CandyUiLayer::getTargetLabel(int num)
{
	CCLabelAtlas *label;
	if(CandyShare::getFixedScreenHeight()>=SCREEN_DEMARCATION1_HEIGHT)
		label= CCLabelAtlas::create(CCString::createWithFormat("%d",num)->getCString(),
		"Image/CandyGame/CandyGameUi/NumLabel/TargetNumLabe.png",24,28,'/');
	else
		label= CCLabelAtlas::create(CCString::createWithFormat("%d",num)->getCString(),
		"Image/CandyGame/CandyGameUi/NumLabel/NumLabel1.png",28,40,'-');
	return label;
}

void CandyUiLayer::drawTargetNumChange(UILabelAtlas* targetLabel, int num)
{
	CCLabelAtlas *label = getTargetLabel(num);
	label->setAnchorPoint(ccp(0.5f,0.5f));
	label->setPosition(getTargetNumLabelPos(targetLabel));
	CandyManager::getInstance()->effectLayer->displayNumLabelChange(label);
}

const CCPoint& CandyUiLayer::getStepNumLabelPos(void)
{
	static CCPoint retPos;

	//mini版本无需调整
	retPos = moveContent->getPosition();
	retPos = ccpAdd(moveContent->getPosition(), ccp(30, 15));

	/*if(CandyShare::getFixedScreenHeight()>=SCREEN_DEMARCATION1_HEIGHT)
	retPos = ccpAdd(moveContent->getPosition(), ccp(105,-40));
	else
	retPos = ccpAdd(bottomUi->getPosition(), ccp(-125,10));*/
	
	return retPos;
}

const CCPoint& CandyUiLayer::getScoreNumLabelPos(void)
{
	static CCPoint retPos;
	if(CandyShare::getFixedScreenHeight()>=SCREEN_DEMARCATION1_HEIGHT)
		retPos = ccpAdd(moveContent->getPosition(), ccp(-85,-40));
	else
		retPos = ccpAdd(bottomUi->getPosition(), ccp(-150,-50));

	return retPos;
}

const CCPoint& CandyUiLayer::getTargetNumLabelPos(UILabelAtlas* label)
{
	static CCPoint retPos;
	if(!label)
		label = targetNumLabel;
	retPos = label->convertToWorldSpace(ccp(0,0));

	//retPos = ccpAdd(label->getPosition(), bottomUi->getPosition());
	/*if(CandyShare::getFixedScreenHeight()>=SCREEN_DEMARCATION1_HEIGHT)
		retPos = ccpAdd(retPos, ccp(-40,-100));
	else
		retPos = ccpAdd(retPos, ccp(-50, -175));*/
	return retPos;
}

const CCPoint&  CandyUiLayer::getPropButtonPos(void)
{
	static CCPoint retPos;
	
	int buttonNum =0;
	if(CommonData::currentPropType == CANDY_PROP_IN_HAMMER)
		buttonNum = 2;
	else if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
		buttonNum = 1;
	else if(CommonData::currentPropType == CANDY_PROP_OUT_COLORFULL)
		buttonNum = 3;
	else if(CommonData::currentPropType == CANDY_PROP_OUT_BOMBNEW)
		buttonNum = 4;

	retPos = PropButton[buttonNum]->getRenderer()->convertToWorldSpace(CCPointZero);
	
	return retPos;
}

CCNode *CandyUiLayer::getTargetIngreidentNode(int num, char *imgName, UILabelAtlas* targetLabel)
{
	CCLabelAtlas *label = getTargetLabel(num);
	label->setAnchorPoint(ccp(0.0f,0.5f));
	label->setPosition(ccp(72,36));
	
	CCSprite *sprite =  CCSprite::createWithSpriteFrameName(imgName);
	sprite->addChild(label,0,TARGET_NODE_LABEL_TAG);
	sprite->setAnchorPoint(ccp(1.0f,0.5f));
	sprite->setPosition(getTargetNumLabelPos(targetLabel));
	sprite->setScale(1.5f);
	return sprite;
}

CCNode *CandyUiLayer::getTargetCollectNode(int collectIndex, UILabelAtlas* targetLabel)
{
	if(collectIndex <0 || collectIndex>=3)
		return NULL;
	
	if(CandyManager::collectCandy[collectIndex].targetNum <= 0 || !targetLabel)
		return NULL;
	
	CCLabelAtlas *label = getTargetLabel(CandyManager::collectCandy[collectIndex].targetNum);
	label->setAnchorPoint(ccp(0.0f,0.5f));
	label->setPosition(ccp(40,20));

	CCSprite *sprite =  CCSprite::create(
		CCString::createWithFormat("%s/CollectType%d.png",COLLECT_TYPE_IMG_PATH,(int)CandyManager::collectCandy[collectIndex].type)->getCString());
	sprite->addChild(label,0,TARGET_NODE_LABEL_TAG);
	sprite->setAnchorPoint(ccp(0.5f,0.5f));
	sprite->setPosition(getTargetNumLabelPos(targetLabel));
	return sprite;
}



CCNode *CandyUiLayer::getTargetIconNode(int num)
{
	switch(CandyManager::gameMode)
		{
			case CANDY_MODE_NORMAL:
			case CANDY_MODE_TIMING:
				if(num ==1)
				{
					CCLabelAtlas *label = getTargetLabel(CandyScore::starScoreNum[0]);
					label->setAnchorPoint(ccp(0.5f,0.5f));
					label->setPosition(getTargetNumLabelPos(targetNumLabel));
					label->setScale(2.0f);
					return label;
				}
				break;

			case CANDY_MODE_JELLY:
				if(num ==1)
				{
					CCLabelAtlas *label = getTargetLabel(CandyManager::getInstance()->jellyMgr->getCandyJellyTotalNum());
					label->setAnchorPoint(ccp(0.0f,0.5f));
					label->setPosition(ccp(72,36));

					CCSprite *jellySprite =  CCSprite::createWithSpriteFrameName("jelly1.png");
					jellySprite->addChild(label,0,TARGET_NODE_LABEL_TAG);
					jellySprite->setAnchorPoint(ccp(1.0f,0.5f));
					jellySprite->setPosition(getTargetNumLabelPos(jellyNumLabel));
					jellySprite->setScale(1.5f);

					return jellySprite;
				}
				break;

			case CANDY_MODE_INGREDIENT:
					{
						static bool firstNumExist = true;
						CCNode *cherryTaget = getTargetIngreidentNode(CandyIngredients::numCherry, (char*)"cherry0.png",cherryNumLabel);
						CCNode *chesnutTaget = getTargetIngreidentNode(CandyIngredients::numChesnut, (char*)"chesnut0.png",chesnutNumLabel);
						
						if(num == 1)
							{
								if(CandyIngredients::numCherry)
									{
										firstNumExist = true;
										return cherryTaget;
									}
								else
									{
										firstNumExist = false;
										return chesnutTaget;
									}
							}
						else if(num == 2 && firstNumExist)
							{
								return chesnutTaget;
							}
					}
				break;

			case CANDY_MODE_COLLECT:
				{
					return getTargetCollectNode(num-1, collectTypeLabel[num-1]);
					
				}
				break;
				
		}
	return NULL;
}

void CandyUiLayer::setScoreStarPercentage(float per)
{
	if(per < 0 )
		per = 0;
	else if( per > 100.0f)
		per = 100.0f;
	scoreBar->setPercent((int)per);

	if(per>=100.0f)
	{
		if(percentingNode)
		{
			percentingNode->removeFromParent();
			percentingNode = NULL;
		}

		if(!percentDoneNode)
			percentDoneNode = CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAR_PERCENTDONE, ccp( 0,0), scoreBar->getRenderer());
	}
	else 
	{
		if(!percentingNode)
			percentingNode = CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAR_PERCENTING, ccp( 0,0), scoreBar->getRenderer());

		CCSize barSize = scoreBar->getContentSize();
		percentingNode->setPosition(ccp(barSize.width*per*0.01f - barSize.width*0.5f, 0));
	}
}

void CandyUiLayer::displayStarPercentEffect(int starNum)
{
	if(starNum<0 || starNum>=3)
		return;

	const float delay = 0.8f;
	
	CCNode *node = starGap[starNum]->getRenderer();
	if(!node)
		return;
	node->setTag(starNum);
	
	switch(starNum)
	{
	case 0:
	case 1:
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAR_PERCENT1, ccp(0,0), node);
		node->schedule(schedule_selector(CandyUiLayer::displayBlinkPercentEffect), delay);
		break;

	case 2:
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAR_PERCENT2, ccp(0,0), node);
		node->schedule(schedule_selector(CandyUiLayer::displayBlinkPercentEffect), delay);
		break;
	}
	
}

void CandyUiLayer::displayBlinkPercentEffect(float dt)
{
	int tag = getTag();
	CCPoint pos = ccp(rand()%16-8,rand()%16-8) ;
	if(tag==0 || tag ==1)
		pos.y = pos.y+ 15;
	
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_BLINK_PERCENT, pos, this);
}
	
void CandyUiLayer::setScoreGrayStarVisible(int starNum, bool visible)
{
	if(starNum<0 || starNum>=3)
		return;

	if(grayStar[starNum])
		grayStar[starNum]->setVisible(visible);
}


void CandyUiLayer::displayMoveWarning(void)
{
	//　剩余时间或剩余步数倒计时警告　　道具使用提示
	CandyManager::getInstance()->explosionMgr->addExplosionsAnimation(actionNumLabel->getRenderer());

	// 闪烁提示前5关关闭
	if ( CandyManager::currentLevel > 5 )
	{
		for(int i=0; i<5; i++)
		{
			PropButton[i]->stopAllActions();
			PropButton[i]->runAction(
				CCRepeatForever::create(
				CCSequence::create(	
				CCScaleTo::create(0.4f, 1.0f, 0.9f),
				CCScaleTo::create(0.2f, 0.9f, 1.15f), 
				CCScaleTo::create(0.2f, 1.0f),
				CCDelayTime::create(0.1f),
				NULL)));
		}
	}
}

CCNode* CandyUiLayer::getEnergyJarNode(void)
{
//	return energyJarButton->getRenderer();
	return NULL;
}

void CandyUiLayer::resetEnergyJarPercentage(void)
{
	//energyJarButton->setTouchEnable(true);
	MsgMgr::sendUseMagicLampTimeRequest(AnalyseJson::logOnMsg.baseInfo.id);
	AnalyseJson::magicLampInfo.hasMagicLamp = 0;
	CandyManager::energyNum = 0;
	//CommonData::sendEnergyNum();
	increaseEnergyJarPercentage(0);
}
	
void CandyUiLayer::increaseEnergyJarPercentage(int num)
{
	bool bFlag = false;
	if(CandyManager::energyNum < 0)
		CandyManager::energyNum = 0;
	CandyManager::energyNum += num;

	if(CandyManager::energyNum >= FULL_ENERGY)
	{
		CandyManager::energyNum = FULL_ENERGY;
//		energyJarButton->setTouchEnable(true);
//		CandyManager::getInstance()->effectLayer->displayEnergyJarEffect();
	}
	else
	{
		//energyJarButton->setTouchEnable(false);
//		CandyManager::getInstance()->effectLayer->undisplayEnergyJarEffect();
	}

// 	for(int i=0; i<20; i++)
// 	{
// 		UIImageView *energyCandy  = dynamic_cast<UIImageView*>(gameUiLayout->getChildByName(
// 			CCString::createWithFormat("caneyEnergy%d",i+1)->getCString()));
// 		if(energyCandy)
// 		{
// 			if(CandyManager::energyNum > 250*i)
// 			{
// 				if(!energyCandy->isVisible())
// 				{
// 					bFlag = true;
// 					energyCandy->setVisible(true);
// 				}
// 			}
// 			else
// 			{
// 				energyCandy->setVisible(false);
// 			}
// 		}
// 	}
 	
//  	if(bFlag)
//  	{
//  		RabbitPutSugar();
//  	}
}

void CandyUiLayer::RabbitPutSugar()
{
// #ifndef CLOSE_ARMATURE
// 	if(!bPlayAnim)
// 	{
// 		bPlayAnim = true;
// 		if(m_pRabbitShake1!=NULL)
// 		{
// 			m_pRabbitShake1->setVisible(true);
// 			m_pRabbitShake1->getAnimation()->play("Animation1");
// 		}
// 	}
// #endif
}

void CandyUiLayer::animationEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
  	std::string id = movementID;
  	if (movementType == LOOP_COMPLETE)
  	{
 		if(id.compare("Animation2") == 0)
  		{
  			armature->getAnimation()->stop();
  		}
  	}
}

void CandyUiLayer::onFrameEvent1(cocos2d::extension::CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
 	if(strcmp(evt,"candyfly") == 0) 
 	{
		m_pShenDengRabbit->setPosition(ccp(size.width-80,120));
		m_pShenDengRabbit->setVisible(true);
		m_pShenDengRabbit->getAnimation()->stop();
		m_pShenDengRabbit->getAnimation()->play("Animation3");
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT,ccp(0,0),m_pShenDengRabbit,0,100);
 	}
}

void CandyUiLayer::SpecialReward()
{
	CandySpecial special;
	switch(m_nRewardType)
	{
	case 0:
		special = CANDY_SPECIAL_COLORFULL;
		break;

	case 1:
		special = CANDY_SPECIAL_BOMB;
		break;

	case 2:
		special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;
		break;
	}
	for(int i=0; i<m_nRewardNum; i++)
	{
		if(m_nRewardType == 2)
			special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;

		CandyCell *candy = CandyCell::getRandomNormalCandy();

		if(candy)
		{
			displaySpecialCandyEffect(candy,special);
		}
	}
}

void CandyUiLayer::SpecialCandyFly()
{
// 	CandySpecial special;
// 	switch(m_nRewardType)
// 	{
// 	case 0:
// 		special = CANDY_SPECIAL_COLORFULL;
// 		break;
// 
// 	case 1:
// 		special = CANDY_SPECIAL_BOMB;
// 		break;
// 
// 	case 2:
// 		special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;
// 		break;
// 	}
// 	for(int i=0; i<m_nRewardNum; i++)
// 	{
// 		if(m_nRewardType == 2)
// 			special =rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;
// 
// 		CandyCell *candy = CandyCell::getRandomNormalCandy();
// 
// 		if(candy)
// 		{
// 			displaySpecialCandyEffect(candy,special);
// 		}
// 	}
}

void CandyUiLayer::displaySpecialCandyEffect(CCNode* targetNode,int special)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

//	m_bReward = false;
	CCNode *node = CCNode::create();
	CandyManager::getInstance()->effectLayer->addChild(node);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP1,  ccp(0,0), node,123);
	
	CCPoint originPos = ccp(size.width/2,size.height/2+150);
	float moveTime = 0.3f;
	
	node->setPosition(originPos);
	node->runAction(CCSequence::create(CandyManager::getInstance()->shareMgr->getEffectBezierAction(originPos, targetNode->getPosition()),
		CCCallFuncN::create(node,callfuncN_selector(CandyUiLayer::displaySpecialCandyEffectCb1)),
		NULL
		));
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_COLOR);
	
	CandyCell* pCandy = (CandyCell*)targetNode;
	pCandy->runCandyChangeSpecialDelay((CandySpecial)special, 1.5f);
		
}

void CandyUiLayer::displaySpecialCandyEffectCb1(CCNode *pSender)
{
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP2,pSender->getPosition());
	pSender->getChildByTag(123)->setPosition(ccp(-1000,-1000));
	pSender->runAction(CCSequence::create(
		CCDelayTime::create(3.0f),
		CCCallFuncN::create(pSender, callfuncN_selector(CandyUiLayer::displaySpecialCandyEffectCb2)),
		NULL));
}

void CandyUiLayer::displaySpecialCandyEffectCb2(CCNode* pSender)
{
	pSender->removeFromParent();
}

void CandyUiLayer::CandyFly()
{
// 	m_pCandy1->setVisible(true);
// 	m_pCandy1->stopAllActions();
// 	m_pCandy1->setOpacity(255);
// 	m_pCandy1->setPosition(ccp(644,93));
// 
// 	m_pCandy2->setVisible(true);
// 	m_pCandy2->stopAllActions();
// 	m_pCandy2->setOpacity(255);
// 	m_pCandy2->setPosition(ccp(680,96));
// 
// 	m_pCandy3->setVisible(true);
// 	m_pCandy3->stopAllActions();
// 	m_pCandy3->setOpacity(255);
// 	m_pCandy3->setPosition(ccp(654,99));
// 
// 	m_pCandy4->setVisible(true);
// 	m_pCandy4->stopAllActions();
// 	m_pCandy4->setOpacity(255);
// 	m_pCandy4->setPosition(ccp(659,93));
// 
// 	//
// 	ccBezierConfig tr0;    
// 	tr0.endPosition=ccp(-125, -25);
// 	tr0.controlPoint_1=ccp(-40, 280);
// 	tr0.controlPoint_2=ccp(-125, 80);
// 
// 	CCActionInterval* bezierForward01 = CCBezierBy::create(3.0f, tr0);
// 	CCEaseOut *bezierForward0 = CCEaseOut::create(bezierForward01,0.5f);
// 	CCFadeOut *fadeOut0 = CCFadeOut::create(0.5f);
// 	CCSequence* rep0 = CCSequence::create( bezierForward0, fadeOut0, NULL);
// 	CCSpeed* action0 = CCSpeed::create(rep0, 6.0f);
// 
// 	m_pCandy1->runAction(action0);
// 	//
// 	ccBezierConfig tr1;    
// 	tr1.endPosition=ccp(-115, -20);
// 	tr1.controlPoint_1=ccp(-40, 270);
// 	tr1.controlPoint_2=ccp(-125, 70);
// 
// 	CCActionInterval* bezierForward11 = CCBezierBy::create(3.0f, tr1);
// 	CCEaseOut *bezierForward1 = CCEaseOut::create(bezierForward11,0.5f);
// 	CCFadeOut *fadeOut1 = CCFadeOut::create(0.5f);
// 	CCSequence* rep1 = CCSequence::create( bezierForward1, fadeOut1, NULL);
// 	CCSpeed* action1 = CCSpeed::create(rep1, 6.0f);
// 	m_pCandy2->runAction(action1);
// 	//
// 	ccBezierConfig tr2;    
// 	tr2.endPosition=ccp(-135, -27);
// 	tr2.controlPoint_1=ccp(-35, 260);
// 	tr2.controlPoint_2=ccp(-120, 70);
// 
// 	CCActionInterval* bezierForward21 = CCBezierBy::create(3.0f, tr2);
// 	CCEaseOut *bezierForward2 = CCEaseOut::create(bezierForward21,0.5f);
// 	CCFadeOut *fadeOut2 = CCFadeOut::create(0.5f);
// 	CCSequence* rep2 = CCSequence::create( bezierForward2, fadeOut2, NULL);
// 	CCSpeed* action2 = CCSpeed::create(rep2, 6.0f);
// 	m_pCandy3->runAction(action2);
// 	//
// 	ccBezierConfig tr3;    
// 	tr3.endPosition=ccp(-120, -28);
// 	tr3.controlPoint_1=ccp(-35, 265);
// 	tr3.controlPoint_2=ccp(-120, 75);
// 
// 	CCActionInterval* bezierForward31 = CCBezierBy::create(3.0f, tr3);
// 	CCEaseOut *bezierForward3 = CCEaseOut::create(bezierForward31,0.5f);
// 	CCFadeOut *fadeOut3 = CCFadeOut::create(0.5f);
// 	CCSequence* rep3 = CCSequence::create( bezierForward3, fadeOut3,
// 			CCCallFunc::create(this, callfunc_selector(CandyUiLayer::CandyAppear)), 
// 		NULL);
// 	CCSpeed* action3 = CCSpeed::create(rep3, 6.0f);
// 	m_pCandy4->runAction(action3);
}

void CandyUiLayer::CandyAppear()
{
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_CANDY_APPEAR,m_pCandy4->getPosition());
}

void CandyUiLayer::updateBuy()
{
 	if ( CommonData::m_buyState) 
 	{
		CCLog("updateBuy");

 		CommonData::m_buyState = false;
		AnalyseJson::magicLampInfo.magicLampTime = 0;
 	}
}

void CandyUiLayer::updateEnergy()
{

// 	CandyResultType ntype = CandyManager::getInstance()->resultMgr->getCurrentResult();
// 	
// 	if((CandyManager::energyNum == FULL_ENERGY) && (bPlayAnim == false) && ntype==CANDY_RESULT_PLAYING)
// 	{
// #ifndef CLOSE_ARMATURE
// 		RabbitAppear();
// #endif
// 	}
}

void CandyUiLayer::RabbitAppear()
{
// 	CCSize size = CCDirector::sharedDirector()->getWinSize();
// 
// 	if(!bPlayAnim)
// 	{
// 		bPlayAnim = true;
// 		if(m_pRabbitShake2!=NULL)
// 		{
// 			m_pRabbitShake2->setVisible(true);
// 			m_pRabbitShake2->stopAllActions();
// 			m_pRabbitShake2->setPosition(ccp(size.width-60,20 - RABBIT_FALL_LENGTH));
// 
// 			m_pRabbitShake2->runAction(CCSequence::create(
// 				CCMoveBy::create(0.5f,ccp(0,RABBIT_FALL_LENGTH)),
// 				NULL
// 				));
// 			RabbitPointToSugar();
// 		}
// 	}
}

void CandyUiLayer::RabbitPointToSugar()
{
// 	if(m_pRabbitShake2 != NULL)
// 	{
// 		m_pRabbitShake2->getAnimation()->play("Animation1_Copy1");
// 
// 	}
}
void CandyUiLayer::RabbitStop()
{
// #ifndef CLOSE_ARMATURE
// 	if(m_pRabbitShake2 != NULL)
// 	{
// 		m_pRabbitShake2->getAnimation()->stop();
// 	}
// 	CandyManager::getInstance()->effectLayer->undisplayEnergyJarEffect();
// #endif
}
void CandyUiLayer::animationEvent2(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Animation3") == 0)
		{
			//停止动画
			armature->getAnimation()->stop();
			armature->runAction(CCRepeatForever::create(CommonData::getAfloatAction()));
			//动画播放完毕
			bPlayAnim = true;
		}
	}
}

void CandyUiLayer::RabbitDisappear()
{
// 	if(m_pRabbitShake2 != NULL)
// 	{
// 		m_pRabbitShake2->stopAllActions();
// 		m_pRabbitShake2->getAnimation()->stop();
// 		m_pRabbitShake2->setVisible(false);
// 		bPlayAnim = false;
// 	}
	RabbitDisappearCallBack();

}

void CandyUiLayer::RabbitDisappearCallBack()
{
 	if(!CandyManager::getInstance()->resultMgr->getGameRunning() )
 		return;
 
 	if( CandyManager::getInstance()->guideLayer->getGuiding())
 		return;

	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_ROULETTE);

#ifdef CANDY_STATISITICAL_DATA
	CommonData::sendUsePropStatistics(8);
#endif
}

void CandyUiLayer::updatePropNum(void)
{
	for(int i=0; i<5; i++)
	{
		int propNum = 0;
		switch (i)
		{
		case 0:
			propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_RESORT));
			break;
		case 1:
			propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_SWAP));
			break;
		case 2:
			propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_HAMMER));
			break;
		case 3:
			propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_COLORFULL));
			break;
		case 4:
			propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_BOMBNEW));
			break;
		}
		if(propNum == propsNum[i]||!PropButton[i]->isActive())
			continue;
		propsNum[i] = propNum ;
		if( propNum >0)
		{
			PropBuy[i]->setVisible(false);
			PropNumBg[i]->setVisible(true);
			PropNumLabel[i]->setVisible(true);
			PropNumLabel[i]->setStringValue(CCString::createWithFormat("%d",propNum)->getCString());
		}
		else
		{
			PropBuy[i]->setVisible(true);
			PropNumBg[i]->setVisible(false);
			PropNumLabel[i]->setVisible(false);
		}

// 		if(CandyManager::gameMode == CANDY_MODE_TIMING)
// 		{
// 			PropButton[0]->disable();
// 			PropBuy[0]->setVisible(false);
// 			PropNumBg[0]->setVisible( false );
// 			PropNumLabel[0]->setVisible( false );
// 		}
	}
}

void CandyUiLayer::useProp(int type)
{
	//mini版本不再显示+5道具购买界面
	CCLog("buy type = %d",type);
	int currentPropNum = CommonData::getPropNum((CandyPropType)type);
	CCLog("buy type num = %d",currentPropNum);
	if(currentPropNum <= 0 )
	{
		if (CANDY_PROP_IN_STEP5 != (CandyPropType)type)
		{
			CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)type);
			//CandyPay::getInstance()->RequestCandyOrder(type);
		}
		else
		{
			//mini版本购买+5道具后，如果道具数量出错时，让游戏能继续
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
		}
	}
	else
	{
		setPropButtonTouchEnable(false);
		CommonData::changePropNum((CandyPropType)type, -1);
		CommonData::setPropUseState((CandyPropType)type, true);
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_USE_PROP);
	}
	
}

CCNode* CandyUiLayer::getPropButtonNode(void)
{
	int buttonNum =0;
	if(CommonData::currentPropType == CANDY_PROP_IN_HAMMER)
		buttonNum = 2;
	else if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
		buttonNum = 1;
	else if(CommonData::currentPropType == CANDY_PROP_OUT_COLORFULL)
		buttonNum = 3;
	else if(CommonData::currentPropType == CANDY_PROP_OUT_BOMBNEW)
		buttonNum = 4;

	return PropButton[buttonNum]->getRenderer();
}

CCDrawNode* CandyUiLayer::getShape(int type)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float fixedScreenHeight = CandyShare::getFixedScreenHeight();

	CCDrawNode *shape = CCDrawNode::create();
	CCPoint rect[4];
	ccColor4F green = {0, 1, 0, 1};

	if(fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT)
	{
		rect[0]=ccp(size.width*0.5 - 350,size.height*0.5 - 340);
		rect[1]=ccp(size.width*0.5 + 350,size.height*0.5 - 340);
		rect[2]=ccp(size.width*0.5 + 350,size.height*0.5 + 340);
		rect[3]=ccp(size.width*0.5 - 350,size.height*0.5 + 340);
	}
	else
	{
		rect[0]=ccp(size.width*0.5 - 350,size.height*0.5 - 340+120);
		rect[1]=ccp(size.width*0.5 + 350,size.height*0.5 - 340+120);
		rect[2]=ccp(size.width*0.5 + 350,size.height*0.5 + 340+120);
		rect[3]=ccp(size.width*0.5 - 350,size.height*0.5 + 340+120);
	}

	shape->drawPolygon(rect, 4, green, 0, green);
	CCPoint pos;
	CCSize nsize;
	if(type == CANDY_PROP_IN_BOMB)
	{
		pos = PropButton[2]->convertToWorldSpace(CCPointZero);

		nsize = PropButton[2]->getSize();
		rect[0]=ccp(pos.x - nsize.width*0.5,pos.y - nsize.height*0.5);
		rect[1]=ccp(pos.x + nsize.width*0.5,pos.y - nsize.height*0.5);
		rect[2]=ccp(pos.x + nsize.width*0.5,pos.y + nsize.height*0.5);
		rect[3]=ccp(pos.x - nsize.width*0.5,pos.y + nsize.height*0.5);
		shape->drawPolygon(rect, 4, green, 0, green);
	}
	else if(type == CANDY_PROP_IN_STRIP)
	{
		pos = PropButton[1]->convertToWorldSpace(CCPointZero);

		nsize = PropButton[1]->getSize();
		rect[0]=ccp(pos.x - nsize.width*0.5,pos.y - nsize.height*0.5);
		rect[1]=ccp(pos.x + nsize.width*0.5,pos.y - nsize.height*0.5);
		rect[2]=ccp(pos.x + nsize.width*0.5,pos.y + nsize.height*0.5);
		rect[3]=ccp(pos.x - nsize.width*0.5,pos.y + nsize.height*0.5);
		shape->drawPolygon(rect, 4, green, 0, green);
	}

	return shape;	
}

void CandyUiLayer::candyUsePropStart(int type)
{
	if(CommonData::getPropNum((CandyPropType)type) <= 0)
	{
		CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)type);
		//CandyPay::getInstance()->RequestCandyOrder(type);
		return;
	}
	CommonData::currentPropType = type;
	CandyManager::getInstance()->effectLayer->displayPropButtonEffect();
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_USE_PROP_GAME);

	CandyManager::getInstance()->effectLayer->displayPropLightEffect();

	//加入蒙板
	CCClippingNode *pClip=CCClippingNode::create();
	CCLayerColor *pColor=CCLayerColor::create(ccc4(0,0,0,150));
	pClip->addChild(pColor);
	pClip->setStencil(getShape(type));
	pClip->setInverted(true);
	getGameUiLayer()->getRootWidget()->getRenderer()->addChild(pClip,100,789);

	PlayGame *playGameLayer = (PlayGame*)CandyManager::getInstance()->getCurrentLayer();
	playGameLayer->addBg(false);
	CCSprite *bgGrid = (CCSprite *)CandyManager::getInstance()->candyLayer->getChildByTag(BG_GRID_TAG);
 	if(bgGrid)
 	{
 		bgGrid->runAction(CCRepeatForever::create(
 		CCSequence::create(
 		CCFadeTo::create(0.5f, 128),
 		CCFadeTo::create(0.5f,255),
 		NULL)));
 	}

	CCSprite* chooseTargetTips = CCSprite::create("Image/CandyGame/Others/chooseTargetTips.png");
	chooseTargetTips->setScale(1.0f/1.4f);
	showTips(chooseTargetTips);
	setPropButtonTouchEnable(false);
}

void CandyUiLayer::candyUsePropEnd(void)
{
	CandyManager::getInstance()->effectLayer->displayPropSelectCellEffect(CommonData::currentPropType);
	CandyManager::getInstance()->effectLayer->undisplayPropButtonEffect();
	useProp(CommonData::currentPropType);
}

void CandyUiLayer::candyPropChangeBSCallBack(CCObject *pSender)
{	
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle() )
		return;


	UIButton *btn = (UIButton*)pSender;
	//btn->setTouchEnabled(false);
	btn->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFuncN::create(this, callfuncN_selector(CandyUiLayer::propBuyBtnCallBack)),
		NULL));

	if(CandyManager::getInstance()->resultMgr->getGameRunning()
		&& !CandyManager::getInstance()->guideLayer->getGuiding())
		{
			int propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_SWAP));
			if (propNum <= 0)
			{
				//是否是第一次使用道具并且没有购买过礼包，是则弹出超级礼包
				bool firstuse = isFirstTimeUseProp();
				if (firstuse)
				{
					ShowSuperGiftUI(NULL);
					return;
				}
			}

			candyUsePropStart(CANDY_PROP_IN_SWAP);
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
		}
}

void CandyUiLayer::candyPropChangeCCallBack(CCObject *pSender)
{
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle() )
		return;
	
	UIButton *btn = (UIButton*)pSender;
	//btn->setTouchEnabled(false);
	btn->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFuncN::create(this, callfuncN_selector(CandyUiLayer::propBuyBtnCallBack)),
		NULL));

	if(CandyManager::getInstance()->resultMgr->getGameRunning()
		&& !CandyManager::getInstance()->guideLayer->getGuiding())
	{
		int propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_HAMMER));
		if (propNum <= 0)
		{
			//是否是第一次使用道具并且没有购买过礼包，是则弹出超级礼包
			bool firstuse = isFirstTimeUseProp();
			if (firstuse)
			{
				ShowSuperGiftUI(NULL);
				return;
			}
		}

		candyUsePropStart(CANDY_PROP_IN_HAMMER);
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	}
}

void CandyUiLayer::propBuyBtnCallBack(CCNode* pSender)
{
	UIButton *btn = (UIButton*)pSender;
	btn->setTouchEnabled(true);
}

void CandyUiLayer::candyPropExtendCallBack(CCObject *pSender)
{
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle() )
		return;

	UIButton *btn = (UIButton*)pSender;
	//btn->setTouchEnabled(false);
	btn->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFuncN::create(this, callfuncN_selector(CandyUiLayer::propBuyBtnCallBack)),
		NULL));
	
	if(CandyManager::getInstance()->resultMgr->getGameRunning()
		&& !CandyManager::getInstance()->guideLayer->getGuiding())
	{
		int propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_RESORT));
		if (propNum <= 0)
		{
			//是否是第一次使用道具并且没有购买过礼包，是则弹出超级礼包
			bool firstuse = isFirstTimeUseProp();
			if (firstuse)
			{
				ShowSuperGiftUI(NULL);
				return;
			}
		}
		useProp(CANDY_PROP_IN_RESORT);
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	}
}

void CandyUiLayer::candyPropColorCallBack( CCObject* pSender )
{
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle() )
		return;

	UIButton *btn = (UIButton*)pSender;
	//btn->setTouchEnabled(false);
	btn->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFuncN::create(this, callfuncN_selector(CandyUiLayer::propBuyBtnCallBack)),
		NULL));

	if(CandyManager::getInstance()->resultMgr->getGameRunning()
		&& !CandyManager::getInstance()->guideLayer->getGuiding())
	{
		int propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_COLORFULL));
		if (propNum <= 0)
		{
			//是否是第一次使用道具并且没有购买过礼包，是则弹出超级礼包
			bool firstuse = isFirstTimeUseProp();
			if (firstuse)
			{
				ShowSuperGiftUI(NULL);
				return;
			}
		}
		candyUsePropStart(CANDY_PROP_OUT_COLORFULL);
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	}
}

void CandyUiLayer::candyPropBoomCallBack( CCObject* pSender )
{
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle() )
		return;

	if(CandyManager::getInstance()->resultMgr->getGameRunning()
		&& !CandyManager::getInstance()->guideLayer->getGuiding())
	{
		int propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_BOMBNEW));
		if (propNum <= 0)
		{
			//是否是第一次使用道具并且没有购买过礼包，是则弹出超级礼包
			bool firstuse = isFirstTimeUseProp();
			if (firstuse)
			{
				ShowSuperGiftUI(NULL);
				return;
			}
		}
		candyUsePropStart(CANDY_PROP_OUT_BOMBNEW);
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	}
}
void CandyUiLayer::setPropButtonTouchEnable(bool enable)
{
	if(enable)
	{
		PropButton[0]->active();
		PropButton[1]->active();
		PropButton[2]->active();
		PropButton[3]->active();
		PropButton[4]->active();
		/*if(CandyManager::currentLevel > 5)
		{
			PropButton[0]->active();
			PropButton[1]->active();
			PropButton[2]->active();
			PropButton[3]->active();
			PropButton[4]->active();
		}
		else if(CandyManager::currentLevel == 2 || CandyManager::currentLevel == 3)
		{
			PropButton[0]->active();
		}
		else if(CandyManager::currentLevel == 4 || CandyManager::currentLevel == 5)
		{
			PropButton[0]->active();
			PropButton[1]->active();
		}
*/
		for(int i=0; i<5; i++)
		{
			int propNum = 0;
			switch (i)
			{
			case 0:
				propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_RESORT));
				break;
			case 1:
				propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_SWAP));
				break;
			case 2:
				propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_IN_HAMMER));
				break;
			case 3:
				propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_COLORFULL));
				break;
			case 4:
				propNum = CommonData::getPropNum((CandyPropType)(CANDY_PROP_OUT_BOMBNEW));
				break;
			}

			if( propNum >0)
			{
				PropBuy[i]->setVisible(false);
				PropNumBg[i]->setVisible(true);
				PropNumLabel[i]->setVisible(true);
				PropNumLabel[i]->setStringValue(CCString::createWithFormat("%d",propNum)->getCString());
			}
			else
			{
				PropBuy[i]->setVisible(true);
				PropNumBg[i]->setVisible(false);
				PropNumLabel[i]->setVisible(false);
			}

// 				// 时间模式禁用+5
// 				if(CandyManager::gameMode == CANDY_MODE_TIMING)
// 				{
// 					PropButton[0]->disable();
// 					PropBuy[0]->setVisible(false);
// 					PropNumBg[0]->setVisible( false );
// 					PropNumLabel[0]->setVisible( false );
// 				}

		}
	}
	else
	{
		if(CandyManager::gameMode != CANDY_MODE_TIMING)
		{
			PropButton[0]->setDisabledTexture("MiniUI/prop36P.png",UI_TEX_TYPE_PLIST);
		}
		else
		{
			PropButton[0]->setDisabledTexture("MiniUI/prop36.png",UI_TEX_TYPE_PLIST);
		}

		//mini版本全部有效
		PropButton[0]->disable();
		PropButton[1]->disable();
		PropButton[2]->disable();
		PropButton[3]->disable();
		PropButton[4]->disable();
		/*if(CandyManager::currentLevel > 5)
		{
			PropButton[0]->disable();
			PropButton[1]->disable();
			PropButton[2]->disable();
			PropButton[3]->disable();
			PropButton[4]->disable();
		}
		else if(CandyManager::currentLevel == 2 || CandyManager::currentLevel == 3)
		{
			PropButton[0]->disable();
		}
		else if(CandyManager::currentLevel == 4 || CandyManager::currentLevel == 5)
		{
			PropButton[0]->disable();
			PropButton[1]->disable();
		}*/
		PropBuy[0]->setVisible( false );
		PropBuy[1]->setVisible( false );
		PropBuy[2]->setVisible( false );
		PropBuy[3]->setVisible( false );
		PropBuy[4]->setVisible( false );
		PropNumBg[0]->setVisible( false );
		PropNumBg[1]->setVisible( false );
		PropNumBg[2]->setVisible( false );
		PropNumBg[3]->setVisible( false );
		PropNumBg[4]->setVisible( false );
	}
// 	// 时间模式禁用+5
// 	if(CandyManager::gameMode == CANDY_MODE_TIMING)
// 	{
// 		PropButton[0]->disable();
// 		PropBuy[0]->setVisible(false);
// 		PropNumBg[0]->setVisible( false );
// 		PropNumLabel[0]->setVisible( false );
// 	}

}

//显示道具购买界面
void CandyUiLayer::showPropBuy(int _propid)
{
#if defined ( CANDY_VERSIONS_FOR_SINGLE )
	return;
#endif

	CandyManager::m_isPropBuying = true;

	/*CCLog("CandyUiLayer::showPropBuy");
	if ( CommonData::checkGoodsPriceEnough( _propid ))
	{
		CCLog("CandyUiLayer::showPropBuy1");
		CommonData::directBuyGoods( _propid );
	}
	else
	{
		CCLog("CandyUiLayer::showPropBuy2");
		gamePropLayout = getPropBuyInfoLayout(_propid);

		Layout* widget = gamePropLayout;

		widget->setVisible( true );
		widget->setTouchEnabled( true );
		if(widget)
		{	
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
			pImgDlg->setPosition( ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f +TARGET_SCREEN_HEIGHT));

			pImgDlg->runAction(CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(true,0.7f, ccp(0,-TARGET_SCREEN_HEIGHT)));
		}
		getGameUiLayer()->addWidget((widget));
	}*/


	//mini版本不判断宝石是否足够
	CCLog("CandyUiLayer::showPropBuy2");
	gamePropLayout = getPropBuyInfoLayout(_propid);

	Layout* widget = gamePropLayout;

	widget->setVisible( true );
	widget->setTouchEnabled( true );
	if(widget)
	{	
		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->setPosition( ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f +TARGET_SCREEN_HEIGHT));

		pImgDlg->runAction(CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(true,0.7f, ccp(0,-TARGET_SCREEN_HEIGHT)));
	}
	getGameUiLayer()->addWidget((widget));
}

Layout* CandyUiLayer::getPropBuyInfoLayout(int propid)
{
	gamePropLayout = CommonWidgt::getPropInfoUI( WIDGET_TYPE_GAME, propid );
	gamePropLayout->setZOrder( 2 );

	return gamePropLayout;
}

void CandyUiLayer::QuitPropWidget(Layout* layer)
{
	Layout* widget;
	if (layer == NULL)
	{
		widget = gamePropLayout;
	}
	else
	{
		widget = layer;
	}

	if(widget)
	{	
		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->runAction(CCSequence::create(
			CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(false,0.7f, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFuncND::create(this, callfuncND_selector(CandyUiLayer::AfterQuit),(void*)pImgDlg), 
			NULL)
			);
	}
}
void CandyUiLayer::QuitPropWidget_dis()
{
	Layout* widget = gamePropLayout;
	if(widget)
	{	
		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->runAction(CCSequence::create(
			CCCallFuncND::create(this, callfuncND_selector(CandyUiLayer::AfterQuit),(void*)pImgDlg), 
			NULL)
			);
	}
}

void CandyUiLayer::AfterQuit(CCNode* node, void* data)
{
	UIWidget* widget = (UIWidget*)data;
	if (widget)
	{
		widget->getParent()->removeFromParentAndCleanup(true);
	}
	return;
	if (widget)
	{
		CCLog("qiut atfer");
		widget->setVisible(false);
		widget->setTouchEnabled(false);
		getGameUiLayer()->removeWidget(widget);
		CandyManager::m_isPropBuying = false;
	}
}

Layout* CandyUiLayer::getShopLayout()
{
	if (!gameShopLayout)
	{
		gameShopLayout = CommonWidgt::getGameShopUI(WIDGET_TYPE_GAME);
	}
	UIButton *returnBtn = dynamic_cast<UIButton*>(gameShopLayout->getChildByName("ShopExitBtn"));
	returnBtn->setTag(ShopinGametag);
	returnBtn->setTouchEnabled(true);

	return gameShopLayout;
}

void CandyUiLayer::candySettingCallBack(CCObject *pSender)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

	if(CandyManager::getInstance()->guideLayer->getGuiding())
		return;

}

void CandyUiLayer::candyEnergyJarCallBack(CCObject *pSender)
{
	if(!CandyManager::getInstance()->resultMgr->getGameRunning() )
		return;

	if( CandyManager::getInstance()->guideLayer->getGuiding())
		return;

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);


	if(AnalyseJson::magicLampInfo.hasMagicLamp == 1 && bPlayAnim)
	{
		bPlayAnim = false;
		//energyJarButton->setTouchEnable(false);
		m_pShenDengRabbit->setVisible(false);
		m_pShenDengRabbit->stopAllActions();
		RabbitDisappear();
	}
	else if(AnalyseJson::magicLampInfo.hasMagicLamp == 1 && bPlayAnim == false)
	{

	}
	else
	{
		CCLog("candyEnergyJarCallBack %d",bPlayAnim);
		showPropBuy(CANDY_PROP_IN_GUANZI);
	}

// 	if(CandyManager::energyNum >= FULL_ENERGY)
// 	{
// 		RabbitDisappear();
// 	}
// 	else
// 	{
// 	}
}

void CandyUiLayer::gamePlayOnCallBack(CCObject *pSender)
{
	Layout* widget  = getGamePauseLayout();
	if(widget)
		widget->runAction(CCSequence::create(
								CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(false,0.7f, ccp(0,TARGET_SCREEN_HEIGHT)),
								CCCallFunc::create(this, callfunc_selector(CandyUiLayer::pauseWidgetOutActionCb)),
								NULL
								 ));
	getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->removeWidget(widget);

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	CommonData::setButtonTouchEnable(pSender, false);
}

void CandyUiLayer::gameExitCallBack(CCObject *pSender)
{
	CandyUiLayer *uiLayer = CandyManager::getInstance()->uiLayer;
	getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);

	CandyManager::getInstance()->resultMgr->getResultLayer()->moveOutGameLayerAction();
	CandyManager::getInstance()->resultMgr->setCurrentResult(/*CANDY_RESULT_STAGE_FAILED*/CANDY_PUSE_EXIT_GAME);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	CommonData::setButtonTouchEnable(pSender, false);
#ifdef CANDY_STATISITICAL_DATA
	CommonData::sendActiveExitGameStatistics();
#endif
}

void CandyUiLayer::returnCallBack(CCObject *pSender)
{
	CandyUiLayer *uiLayer = CandyManager::getInstance()->uiLayer;
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
}

void CandyUiLayer::pauseWidgetOutActionCb(void)
{
	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_PAUSE)
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);

}
void CandyUiLayer::removeYouWinAni(void)
{
	getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);
	getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(77);
	getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(89);
}

void CandyUiLayer::showMagicLamp()
{
	if(AnalyseJson::magicLampInfo.magicLampTime > 0 && AnalyseJson::magicLampInfo.hasMagicLamp == 0 )
	{
		//m_pShenDeng->getAnimation()->stop();
		//m_pShenDeng->getAnimation()->play("Animation1");

		int hour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
		int minute = CommonData::getMinuteForSever(hour,AnalyseJson::magicLampInfo.magicLampTime);
		int secoud = CommonData::getSecoudForSever(hour, minute, AnalyseJson::magicLampInfo.magicLampTime);

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

		char* pTaskTime = (char*)CCString::createWithFormat("%s.%s.%s", pStrHour, pStrminute, pStrsecoud)->getCString();

		//CandyManager::getInstance()->uiLayer->labelTime->setStringValue(pTaskTime);

		//CandyManager::getInstance()->uiLayer->labelTime->setVisible(true);
		CandyManager::getInstance()->uiLayer->schedule( schedule_selector(CandyUiLayer::updateMagicLampTime), 1, kCCRepeatForever, 0 );
	}
	else if(AnalyseJson::magicLampInfo.hasMagicLamp != 0)
	{
		/*CandyParticle::displayCandyParticle(CANDY_PARTICLE_SHENDENGOPEN_EFFECT,ccp(0,0),m_pShenDeng,0,-1);
		m_pShenDeng->runAction(CCSequence::create(
			CCDelayTime::create(1.0f),
			CCCallFunc::create(this, callfunc_selector(CandyUiLayer::shenDengStart)),
			NULL
			));*/
		//CandyManager::getInstance()->uiLayer->labelTime->setVisible(false);
	}
}

void CandyUiLayer::updateMagicLampTime(float dt)
{
	if ( AnalyseJson::magicLampInfo.magicLampTime > 0 && AnalyseJson::magicLampInfo.hasMagicLamp == 0)
	{
		int hour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
		int minute = CommonData::getMinuteForSever(hour,AnalyseJson::magicLampInfo.magicLampTime);
		int secoud = CommonData::getSecoudForSever(hour, minute, AnalyseJson::magicLampInfo.magicLampTime);

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

		char* pTaskTime = (char*)CCString::createWithFormat("%s.%s.%s", pStrHour, pStrminute, pStrsecoud)->getCString();

		//CandyManager::getInstance()->uiLayer->labelTime->setVisible(true);
		//CandyManager::getInstance()->uiLayer->labelTime->setStringValue(pTaskTime);

		AnalyseJson::magicLampInfo.magicLampTime--;
	}
	else
	{
		/*CandyParticle::displayCandyParticle(CANDY_PARTICLE_SHENDENGOPEN_EFFECT,ccp(0,0),m_pShenDeng,0,-1);

		m_pShenDeng->runAction(CCSequence::create(
			CCDelayTime::create(1.0f),
			CCCallFunc::create(this, callfunc_selector(CandyUiLayer::shenDengStart)),
			NULL
			));*/
		//恢复时间满，神灯充满
		AnalyseJson::magicLampInfo.hasMagicLamp = 1;

		//倒计时消失
		//CandyManager::getInstance()->uiLayer->labelTime->setVisible(false);
		this->unschedule( schedule_selector(CandyUiLayer::updateMagicLampTime) );
	}
}


void CandyUiLayer::shenDengStart()
{
	/*CandyParticle::displayCandyParticle(CANDY_PARTICLE_SHENDENGYAODONG_EFFECT,ccp(0,0),m_pShenDeng,0,100);
	m_pShenDeng->getAnimation()->stop();
	m_pShenDeng->getAnimation()->play("Animation2");*/
}

void CandyUiLayer::ShopEasein()
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(gameShopLayout->getChildByName( "m_img_dlg" ));
	
	pImgDlg->setPosition( ccp(currentScreenWidth * 0.5, currentScreenHeight * 1.5) );
	pImgDlg->setVisible( true );
	pImgDlg->stopAllActions();

	pImgDlg->runAction(	CommonData::getMoveAction(2, ccp(currentScreenWidth * 0.5, currentScreenHeight * 0.5)) );
	gameShopLayout->setPosition(ccp(0,0));
}

void CandyUiLayer::SettingBtn()
{
// 	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
// 	CCMenuItemImage* setBtn = CCMenuItemImage::create("Image/MainMapUi/SettingBtnN.png","Image/MainMapUi/SettingBtnP.png","Image/MainMapUi/SettingBtnP.png",
// 		this, menu_selector(CandyUiLayer::SettingCallback));
// 	setBtn->setPosition(ccp(580,1100));
// 	setBtn->setScale(0.7f);
// 	CCMenu* menu = CCMenu::create(setBtn, NULL);
// 	menu->setPosition(ccp(0,0));
// 	addChild(menu);

}

void CandyUiLayer::SettingCallback(CCObject* sender)
{
	keyBackClicked();
}

Layout* CandyUiLayer::getSuperGiftLayout()
{
	if (!SuperGiftLayout)
	{
		SuperGiftLayout = CommonWidgt::getGameSuperGiftUI(WIDGET_TYPE_GAME);
	}
	
	return SuperGiftLayout;
}

void CandyUiLayer::SuperGiftEaseIn()
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SuperGiftLayout->getChildByName( "m_img_dlg" ));

	pImgDlg->setPosition( ccp(currentScreenWidth * 0.5, currentScreenHeight * 1.5) );
	pImgDlg->setVisible( true );
	pImgDlg->stopAllActions();

	pImgDlg->runAction(	CommonData::getMoveAction(2, ccp(currentScreenWidth * 0.5, currentScreenHeight * 0.5)) );
	SuperGiftLayout->setPosition(ccp(0,0));
}

void CandyUiLayer::ShowSuperGiftUI( CCObject* sender )
{
	int isUse = CCUserDefault::sharedUserDefault()->getIntegerForKey("superGift",0);
	if(isUse == 0)
	{
	//	showGameWidget(CANDY_GAME_SUPERGIFT);
		Loading::scenceType =  CANDY_SCENCE_PLAY_GAME;

		//新版支付
		CandyManager::getInstance()->resultMgr->getResultLayer()->showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)Super_gift);
	//	CandyPay::getInstance()->RequestCandyOrder(Super_gift);

		CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(true);
	}
}

bool CandyUiLayer::isFirstTimeUseProp()
{
	if (AnalyseJson::logOnMsg.baseInfo.isBuySuperGift == 0 && AnalyseJson::logOnMsg.baseInfo.isUsePropToday == 0)
	{
		AnalyseJson::logOnMsg.baseInfo.isUsePropToday = 1;
		return true;
	}
		
	return false;
}

CandyGameWidgetType CandyUiLayer::getCurUIType()
{
	return m_curWidgetType;
}
