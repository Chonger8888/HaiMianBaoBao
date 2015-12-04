#include "CandyResult.h"
#include "CandyManager.h"
#include "PlayGameScene.h"
#include "CandyRoulette.h"
#include "CandyRouletteNew.h"
#include "../MsgMgr/HeadDownMgr.h"
#include "../MainMap/MainMapScene.h"
#include "../MsgMgr/MsgMgr.h"
#include "../CommonData/CommonWidgt.h"
#include "../CommonData/CommonData.h"
#include "../CppCallJava/CppCallJava.h"
#include "CandyPay/CandyPay.h"

#define PROP_TIPS_LAYOUT_FILE				"Image/CandyGame/CandyGameLayout/CandyGameFailedTips.ExportJson"
#define PROP_BUY_LAYOUT_FILE				"Image/CandyGame/BuyPropLayout/BuyPropLayout_2.ExportJson"

#define NO_LIFE_LAYOUT_FILE					"Image/CandyGame/CandyGameLayout/CandyNoLife.ExportJson"


#define GAME_WIN_LAYOUT_FILE				"Image/MainMapUi/Tools/CandyGameStageClear.ExportJson"
#define GAME_LOSE_LAYOUT_FILE				"Image/MainMapUi/Tools/CandyGameFailed.ExportJson"
#define ADD5PROP_LIFE_LAYOUT_FILE			"Image/MainMapUi/Tools/CandyBuyAdd5.ExportJson"
#define REWARDSPROP_LIFE_LAYOUT_FILE		"Image/MainMapUi/Tools/CandyRewardsProp.ExportJson"
#define RESORTRANKSHOW_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/ResortRankShowUI.ExportJson"
#define GAMEDISCOUNTGOODS_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/GameDiscountGoods.ExportJson"

#define STATE_BG_IMG				"Image/CandyGame/Others/CandyStateBg.png"

#define MOVE_SCREEN_LEN			800.0f
#define MOVE_SCREEN_TIME			0.7f

CandyResultLayer* CandyResultLayer::create(void)
{
	CandyResultLayer * pLayer = new CandyResultLayer();
	if(pLayer && pLayer->init())
	{

		pLayer->UiLayer = NULL;
		pLayer->propTipsLayout = NULL;
		pLayer->gemeResortRankLayout = NULL;
		pLayer->propBuyLayout = NULL;
		pLayer->gameWinLayout = NULL;
		pLayer->gamePropLayout = NULL;
		pLayer->gameLoseLayout = NULL;
		pLayer->noLifeLayout= NULL;
		pLayer->add5PropLayout = NULL;
		pLayer->discountGoodsLayout = NULL;
		pLayer->rewardsPropLayout = NULL;
		pLayer->currentGetStar = 0;
		pLayer->grayLayer = CCLayerColor::create(ccc4(0,0,0,0));
		pLayer->addChild(pLayer->grayLayer,-1);
		pLayer->autorelease();
		return pLayer;
	}

	CC_SAFE_DELETE(pLayer);
	return NULL;
}

void CandyResultLayer::onEnter(void)
{	
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, RESULT_LAYER_PRIORITY, true);

//	propTipsLayout 	= getPropTipsLayout();
//	propBuyLayout 	= getPropBuyLayout();
	gameWinLayout 	= getGameWinLayout();
	gameLoseLayout 	= getGameLoseLayout();
	m_nCountDown = 4;
}

void CandyResultLayer::onExit(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();

//	CC_SAFE_RELEASE_NULL(propTipsLayout);
	//CC_SAFE_RELEASE_NULL(propBuyLayout);
	CC_SAFE_RELEASE_NULL(gemeResortRankLayout);
	CC_SAFE_RELEASE_NULL(gameWinLayout);
	CC_SAFE_RELEASE_NULL(gameLoseLayout);
	//CC_SAFE_RELEASE_NULL(noLifeLayout);
	CC_SAFE_RELEASE_NULL(add5PropLayout);
	CC_SAFE_RELEASE_NULL(discountGoodsLayout);
	CC_SAFE_RELEASE_NULL(rewardsPropLayout);
	CandyStageIntro::releaseLayout();
}

bool CandyResultLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(CandyManager::getInstance()->resultMgr->getGameRunning())
	{
		return false;
	}
	else if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_USE_PROP)
	{
		if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
		{
			return false;
		}
	}

	return true;
}

void CandyResultLayer::showWidget(ResultWidgetType type, bool action,void* data)
{
	currentWidgetType = type;
	Layout* widget = NULL;
	UILayer *pLayer = NULL;
	switch(type)
	{
	case RESULT_WIDGE_REWARDS:
		{
			widget = getRewardsPropLayout();
#ifdef CANDY_STATISITICAL_DATA
			/*if( 0 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_63 );
			else if( 2 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_89 );
			else if( 4 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_89 );*/
#endif
		}
		break;
	case RESULT_WIDGE_ADD5PROP:
		{
			grayLayer->runAction(CCFadeTo::create(0.5f,170));
			widget = getAdd5PropLayout();
		}
		break;
	case RESULT_WIDGE_DISCOUNTGOODS:
		{
			widget = getDiscountGoodsLayout();
		}
		break;
	case RESULT_WIDGE_PROP_TIPS:
		// 				grayLayer->runAction(CCFadeTo::create(0.5f,200));
		//  			widget = getPropTipsLayout();
		// 				CandyManager::getInstance()->uiLayer->updateCurrentTargetData(widget);
		//  			CandyManager::getInstance()->uiLayer->RabbitStop();
		break;

	case RESULT_WIDGE_GAME_WIN:
		{
			grayLayer->runAction(CCFadeTo::create(0.5f,170));
			widget = getGameWinLayout();
#ifdef CANDY_STATISITICAL_DATA
			/*if( 0 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_65 );
			else if( 1 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_75 );*/
#endif
		}
		break;
	case RESULT_WIDGE_GAME_RESORTRANK:
		{
			grayLayer->runAction(CCFadeTo::create(0.5f,170));
			widget = getResortRankLayout(data);
		}
		break;

	case RESULT_WIDGE_GAME_LOSE:
		CommonData::m_doubleScore = 1;
		//CommonData::sendEnergyNum();
		MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
		CommonData::m_levelFailNum[CandyManager::currentLevel]++;
		MsgMgr::sendLevelFail( AnalyseJson::logOnMsg.baseInfo.id,CandyManager::currentLevel);

#if defined (DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
		CommonData::consumeGameLife();
#endif
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_2, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());

		grayLayer->setOpacity(170);
		widget = getGameLoseLayout();
		//失败界面更新失败数据
//		CandyManager::getInstance()->uiLayer->updateCurrentTargetData(widget);
//		CandyManager::getInstance()->uiLayer->RabbitStop();
		break;

	case RESULT_WIDGE_GAME_NEXT:
		widget = CandyStageIntro::getLayout(STAGE_INTRO_PLAY_GAME,CandyManager::currentLevel);
		break;

	case RESULT_WIDGE_ROULETTE:
		//widget = CandyRoulette::getLayout();
		pLayer = CandyRouletteLayer::GetInstance();
		pLayer->setTag(RESULT_WIDGE_ROULETTE);
		getUILayer()->addChild(pLayer);
		pLayer->setTouchPriority(RESULT_WIDGET_PRIORITY);
		break;

	case RESULT_WIDGE_NO_LIFE:
		{
			widget = getNoLifeLayout();

			//显示超级生命包购买
// 			UIButton* m_but_surBtn = dynamic_cast<UIButton*>(widget->getChildByName("m_but_sur"));
// 			m_but_surBtn->setTouchEnabled(false);
// 			m_but_surBtn->setVisible(false);
// 
// 			UIWidget* m_img_tip_titleWidget = widget->getChildByName("m_img_tip_title");
// 			m_img_tip_titleWidget->setVisible(false);
// 
// 			UIButton* BtnConfirmBtn = dynamic_cast<UIButton*>(widget->getChildByName("BtnConfirm"));
// 			BtnConfirmBtn->setVisible(true);
// 			BtnConfirmBtn->setTouchEnabled(true);
// 			BtnConfirmBtn->addReleaseEvent(this,coco_releaseselector(CandyResultLayer::BuySuperLifePackCallback));
// 			BtnConfirmBtn->isEffects(true);
// 
// 			UIButton* BtnCancelBtn = dynamic_cast<UIButton*>(widget->getChildByName("BtnCancel"));
// 			BtnCancelBtn->setVisible(true);
// 			BtnCancelBtn->setTouchEnabled(true);
// 			BtnCancelBtn->addReleaseEvent(this,coco_releaseselector(CandyResultLayer::CancelBuySuperLifeCallback));
// 			BtnCancelBtn->isEffects(true);
// 
// 			UILabel* LabelnameLabel = dynamic_cast<UILabel*>(widget->getChildByName("Labelname"));
// 			LabelnameLabel->setVisible(true);
// 			CCPoint pos = LabelnameLabel->getPosition();
// 			LabelnameLabel->setPosition(ccp(pos.x, pos.y + 30));
// 			LabelnameLabel->setText(CommonData::GetString("BuySuperLifeDesc").c_str());
// 			LabelnameLabel->setFontSize(45);
		}
		
		break;
	case RESULT_WIDGE_GAMEPAY:
		{
			widget = CommonWidgt::getGamePayWidgetUI(WIDGET_TYPE_GAME,int(data));
			//CommonData::gamePay( int(data) );
			//return;
		}
		break;
	case RESULT_WIDGE_BUYGEM:
		break;

	case RESULT_WIDGET_NET:
		widget = CommonWidgt::getSuccessUI( WIDGET_TYPE_GAME, PROMPT_TYPE_REMINDNETWORK );
		break;
	}
	if(widget)
	{
		float fixedScreenHeight = CandyShare::getFixedScreenHeight();
		CCPoint targetPos = ccp(0,(fixedScreenHeight - TARGET_SCREEN_HEIGHT)*0.5f);
		widget->setPosition(targetPos) ;
		getUILayer()->addWidget((widget));

		if ((RESULT_WIDGE_ADD5PROP == type)||( RESULT_WIDGE_REWARDS == type))
		{
#if 1
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "Content" ));
			CCPoint originalPos = pImgDlg->getPosition();
			pImgDlg->setPosition(ccp(originalPos.x , originalPos.y + TARGET_SCREEN_HEIGHT));
			pImgDlg->runAction(CCSequence::create(
				getMoveAction(true,1.0f, ccp(0.0f, -TARGET_SCREEN_HEIGHT)),
				CCCallFuncN::create(this, callfuncN_selector(CandyResultLayer::showWidgetCb)),
				NULL
				));
#else
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "Content" ));
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
#endif
		}
		
		if(action)
		{
			if (RESULT_WIDGE_GAME_WIN == type)
			{
				float fixedScreenHeight = CandyShare::getFixedScreenHeight();

				

				UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "ContentBg" ));
				CCPoint originalPos;
				if(CommonData::getMaxLevel() < 20)
				{
					originalPos = ccp(pImgDlg->getPosition().x,pImgDlg->getPosition().y -80);
				}
				else
				{
					originalPos = pImgDlg->getPosition();
				}	
				pImgDlg->setPosition(ccp(originalPos.x , originalPos.y + TARGET_SCREEN_HEIGHT));
				pImgDlg->runAction(CCSequence::create(
					getMoveAction(true,1.0f, ccp(0.0f, -TARGET_SCREEN_HEIGHT)),
					CCCallFuncN::create(this, callfuncN_selector(CandyResultLayer::showWidgetCb)),
					NULL
					));

				/* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "ContentBg_1" ));
				 originalPos = pImgDlg->getPosition();
				 pImgDlg->setPosition(ccp(originalPos.x , originalPos.y - TARGET_SCREEN_HEIGHT));
				 pImgDlg->runAction(CCSequence::create(
					 getMoveAction(true,1.0f, ccp(0.0f, TARGET_SCREEN_HEIGHT)),
					 NULL
					 ));*/
			}
			else if(RESULT_WIDGE_GAME_LOSE == type)
			{
				float fixedScreenHeight = CandyShare::getFixedScreenHeight();

				UIImageView* pImgTop = dynamic_cast<UIImageView*>(widget->getChildByName( "Fail_des" ));
				CCPoint originalPos = pImgTop->getPosition();

				pImgTop->setPosition(ccp(originalPos.x , originalPos.y + 110));
				pImgTop->runAction(CCSequence::create(
					CCSpawn::create(
					CCFadeIn::create(1.0f),
					CCMoveBy::create(1.0f,ccp(0.0f,-110)),
					NULL),
					NULL
					));

				pImgTop = dynamic_cast<UIImageView*>(widget->getChildByName( "Img_place" ));
				originalPos = pImgTop->getPosition();
				pImgTop->setPosition(ccp(originalPos.x , originalPos.y - TARGET_SCREEN_HEIGHT));
				pImgTop->runAction(CCSequence::create(
					getMoveAction(true,1.0f, ccp(0.0f, TARGET_SCREEN_HEIGHT)),
					NULL
					));

			}
			else
			{
				performUI_Fall(widget);
			}
		}
	}
}


void CandyResultLayer::BuyAdd5DelayCB(void)
{
	if ( add5PropLayout )
	{
		UIImageView* pImgTop = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Img_des" ));
		pImgTop->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			NULL)
			);

		UIImageView* pImgBtom = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Img_content" ));
		pImgBtom->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,-TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::Add5Dispear)), 
			NULL)
			);

// 		UIButton* pBtnBuy = dynamic_cast<UIButton*>(add5PropLayout->getChildByName( "buypropbtn" ));
// 		pBtnBuy->setTouchEnabled(false);
// 
// 		UIImageView* pContent = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Content" ));
// 		pContent->stopAllActions();
// 
// 		pContent->runAction(CCSequence::create(
// 			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
// 			NULL)
// 			);
	}
}
void CandyResultLayer::Add5Dispear(void)
{
	if ( add5PropLayout )
	{
		add5PropLayout->removeFromParentAndCleanup(true);
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_LOSE);
	}
}

//************************************
// Method:    showPropBuy
// FullName:  CandyResultLayer::showPropBuy
// Access:    public 
// Returns:   void
// Qualifier: 显示购买道具界面
//************************************
void CandyResultLayer::showPropBuy()
{
	if ( CommonData::checkGoodsPriceEnough( _propid ))
	{
		CommonData::directBuyGoods( _propid );
	}
	else
	{		
		gamePropLayout = getPropBuyInfoLayout(_propid);

		Layout* widget = gamePropLayout;

		widget->setVisible( true );
		widget->setTouchEnabled( true );
		if(widget)
		{	
			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
			pImgDlg->setPosition( ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f +TARGET_SCREEN_HEIGHT));
			pImgDlg->runAction(CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(true,1.0f, ccp(0,-TARGET_SCREEN_HEIGHT)));
			getUILayer()->addWidget((widget));
		}
	}
}

//************************************
// Method:    getPropBuyInfoLayout
// FullName:  CandyResultLayer::getPropBuyInfoLayout
// Access:    public 
// Returns:   Layout*
// Qualifier:
// Parameter: int propid
//************************************
Layout* CandyResultLayer::getPropBuyInfoLayout(int propid)
{
	gamePropLayout = CommonWidgt::getPropInfoUI( WIDGET_TYPE_GAME, propid );
	gamePropLayout->setZOrder( 2 );

	return gamePropLayout;
}

//************************************
// Method:    QuitPropWidget
// FullName:  CandyResultLayer::QuitPropWidget
// Access:    public 
// Returns:   void
// Qualifier: 退出道具购买界面
//************************************
void CandyResultLayer::QuitPropWidget()
{
	Layout* widget = gamePropLayout;
	if(widget)
	{	
		float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
		float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->runAction(CCSequence::create(
			CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::showStageInfoLayout)), 
			NULL)
			);
	}
}
void CandyResultLayer::QuitPropWidget_dis()
{
	CCLog("buy prop quit ");

	Layout* widget = gamePropLayout;
	if(widget)
	{	
		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(widget->getChildByName( "m_img_dlg" ));
		pImgDlg->runAction(CCSequence::create(
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::showStageInfoLayout)), 
			NULL)
			);
	}
}

//************************************
// Method:    showStageInfoLayout
// FullName:  CandyResultLayer::showStageInfoLayout
// Access:    public 
// Returns:   void
// Qualifier: 弹出关卡内容界面
//************************************
void CandyResultLayer::showStageInfoLayout()
{
	Layout* widget = gamePropLayout;
	if (widget)
	{
		if(CandyManager::getInstance()->resultMgr->getCurrentResult()  != CANDY_RESULT_NO_MOVE)
			showWidget(RESULT_WIDGE_GAME_NEXT,true);
		widget->setVisible(false);
		widget->setTouchEnabled(false);
		getUILayer()->removeWidget(widget);
	}
}

void CandyResultLayer::performUI_Fall(Layout* widget)
{
	float fixedScreenHeight = CandyShare::getFixedScreenHeight();
	widget->setPosition(ccp(0.0f, (fixedScreenHeight + TARGET_SCREEN_HEIGHT)*0.5f));
	widget->runAction(CCSequence::create(
		getMoveAction(true,0.7f, ccp(0.0f, -TARGET_SCREEN_HEIGHT)),
		CCCallFuncN::create(this, callfuncN_selector(CandyResultLayer::showWidgetCb)),
		// 						CCDelayTime::create(2.0f),
		// 						CCEaseBackIn::create(CCMoveTo::create(0.5f,ccp(360.0f, fixedScreenHeight+400.0))),
		NULL
		));
}

void CandyResultLayer::showWidgetCb(CCNode* sender)
{
	removeYouWin2();
	if(currentWidgetType == RESULT_WIDGE_GAME_WIN)
	{
		const float beginDelay = 0.2f;
		const float gapDelay = 0.3f;
		CCNode *lastScoreNode;

		for(int i=0; i<3; i++)
		{
			if(CandyManager::getInstance()->scoreMgr->getCurrentScore() >= CandyScore::starScoreNum[i])
			{
				ScoreStar[i]->runAction(CCSequence::create(CCDelayTime::create(beginDelay + gapDelay *i),
					CCFadeIn::create(0.2f),
					CCCallFuncN::create(this, callfuncN_selector(CandyResultLayer::displayScoreStarParticle)),
					NULL));
				lastScoreNode = ScoreStar[i]->getRenderer();

				CommonData::changeLevelTaskStarNum( CandyManager::currentLevel );

			}
		}
		lastScoreNode->setUserData((void *)gameWinNextButton);
	}
}

UILayer* CandyResultLayer::getUILayer(void)
{
	if(!UiLayer)
	{
		UiLayer = UILayer::create();
		this->addChild(UiLayer);
		UiLayer->setTouchPriority(RESULT_WIDGET_PRIORITY);
	}
	return UiLayer;
}


Layout* CandyResultLayer::getAdd5PropLayout(void)
{
	if (!add5PropLayout)
	{
		add5PropLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(ADD5PROP_LIFE_LAYOUT_FILE));
		add5PropLayout->retain();
		add5PropLayout->setTouchEnabled(true);

		UIButton* pBuyBtn = dynamic_cast<UIButton*>(add5PropLayout->getChildByName("buypropbtn"));
		pBuyBtn->isEffects(true );
		pBuyBtn->setTag( 1 );
		pBuyBtn->setTouchEnabled( true );
		pBuyBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::BuyAdd5PropBtnCallBack));

//  		UIButton* pExitBtn = dynamic_cast<UIButton*>(add5PropLayout->getChildByName("m_btn_exit"));
//  		pExitBtn->isEffects(true );
//  		pExitBtn->setTag( 0 );
//  		pExitBtn->setTouchEnabled( true );
//  		pExitBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::BuyAdd5PropBtnCallBack));
	}


	UIImageView* pContent = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Content" ));
	pContent->stopAllActions();
	pContent->setOpacity(255);
	add5PropLayout->setPosition(ccp(0,0));
	return add5PropLayout;
}

Layout* CandyResultLayer::getRewardsPropLayout(void)
{
	if (!rewardsPropLayout)
	{
		rewardsPropLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(REWARDSPROP_LIFE_LAYOUT_FILE));
		rewardsPropLayout->retain();
	}
	UIButton* RewardsBut = dynamic_cast<UIButton*>(rewardsPropLayout->getChildByName("RewardsBut"));
	RewardsBut->isEffects( true );
	RewardsBut->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::rewardsPropBtnCallBack));
	RewardsBut->setTouchEnabled(true);

	std::string tem = CommonData::getReward();
	UIImageView* RewardsImg = dynamic_cast<UIImageView*>(rewardsPropLayout->getChildByName("RewardProp"));
	RewardsImg->setTexture(tem.c_str());
	RewardsImg->setScale(1.6f);

	UILabel* pPropName = dynamic_cast<UILabel*>(rewardsPropLayout->getChildByName( "prop_name" ));
	UILabel* pPropExpain = dynamic_cast<UILabel*>(rewardsPropLayout->getChildByName( "prop_explain" ));
	char* pSPropName = NULL;
	char* pSPropExpain = NULL;
	if ( CommonData::getMaxLevel() == 0 && CandyManager::currentLevel == 1  )
	{
		pSPropName	  =	(char*)CCString::createWithFormat("app_prop%d_title", 36)->getCString();
		pSPropExpain  = (char*)CCString::createWithFormat( "app_prop%d_expain", 36)->getCString();
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3)
	{
		pSPropName	  =	(char*)CCString::createWithFormat("app_prop%d_title", 37)->getCString();
		pSPropExpain  = (char*)CCString::createWithFormat( "app_prop%d_expain", 37)->getCString();
	}
	else if(CommonData::getMaxLevel() == 4 && CandyManager::currentLevel == 5)
	{
		pSPropName	  =	(char*)CCString::createWithFormat("app_prop%d_title", 38)->getCString();
		pSPropExpain  = (char*)CCString::createWithFormat( "app_prop%d_expain", 38)->getCString();
	}

	pPropName->setText( CommonData::GetString(pSPropName).c_str() );
	pPropExpain->setText( CommonData::GetString(pSPropExpain).c_str());

	return rewardsPropLayout;
}

void CandyResultLayer::DiscountGoodsButtonCallBack(CCObject *pSender)
{
	UIButton* useBtn = dynamic_cast<UIButton*>(discountGoodsLayout->getChildByName("use_btn"));
	UIButton* buyBtn = dynamic_cast<UIButton*>(discountGoodsLayout->getChildByName("buy_btn"));
	if(pSender == useBtn)
	{
		for(int type = 33; type <= 35; ++type)
		{
			int propNum = CommonData::getPropNum((CandyPropType)type);
			if(propNum > 0)
			{
				CommonData::setPropUseState((CandyPropType)type, true);
			}
		}
		Layout *pLayout = getDiscountGoodsLayout();
		pLayout->setTouchEnable(false);
		pLayout->removeFromParent();
		CommonData::m_resetPropState = false;
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NEXT_STAGE);
	}
	else
	{
		std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
		for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
		{
			if(CANDY_PROP_COMPOSE_1 == p->id)
				break;
		}

		if (atoi(p->price.c_str()) > AnalyseJson::logOnMsg.baseInfo.gemNum)
		{
 			//直接进入支付界面
 			CommonData::m_buytype = CANDY_PROP_COMPOSE_1;
 			CommonData::m_buyMutipropNum = 0;
			int payId = CommonData::getPayIDByGemNum(atoi(p->price.c_str()));
			CppCallJava::toBuyProp(payId, MOBILE_MONEY8_BUY_PROPNUM );
		}
		else
		{
			CommonData::setButtonTouchEnable(pSender, false);
			MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_COMPOSE_1, 1);
		}
	}
}

void CandyResultLayer::DiscountGoodsExitCallBack(CCObject *pSender)
{
	CommonData::setButtonTouchEnable(pSender, false);
	Layout *pLayout = getDiscountGoodsLayout();
	pLayout->setTouchEnable(false);
	pLayout->removeFromParent();
	CommonData::m_resetPropState = true;
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NEXT_STAGE);
}

Layout* CandyResultLayer::getDiscountGoodsLayout(void)
{
	if (!discountGoodsLayout)
	{
		discountGoodsLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(GAMEDISCOUNTGOODS_LAYOUT_JSONFILE));
		discountGoodsLayout->retain();
	}
	UIButton* RewardsBut = dynamic_cast<UIButton*>(discountGoodsLayout->getChildByName("exit_btn"));
	RewardsBut->isEffects( true );
	RewardsBut->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::DiscountGoodsExitCallBack));
	RewardsBut->setTouchEnabled(true);

	UIButton* useBtn = dynamic_cast<UIButton*>(discountGoodsLayout->getChildByName("use_btn"));
	useBtn->isEffects( true );
	useBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::DiscountGoodsButtonCallBack));
	UIButton* buyBtn = dynamic_cast<UIButton*>(discountGoodsLayout->getChildByName("buy_btn"));
	buyBtn->isEffects( true );
	buyBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::DiscountGoodsButtonCallBack));


	std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
	for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
	{
		if(CANDY_PROP_COMPOSE_1 == p->id)
			break;
	}
	UILabelAtlas* pPrice = dynamic_cast<UILabelAtlas*>(discountGoodsLayout->getChildByName("price"));
	pPrice->setStringValue(p->price.c_str());


	UIPanel* panel = dynamic_cast<UIPanel*>(discountGoodsLayout->getChildByName("daoju"));

	int propNum = 0;
	for(int type = 33; type <= 35; ++type)
	{
		propNum = CommonData::getPropNum((CandyPropType)type);
		if(propNum !=0)
			break;
	}
	if(propNum == 0)
	{
		useBtn->setVisible(false);
		useBtn->setTouchEnable(false);
		buyBtn->setVisible(true);
		buyBtn->setTouchEnable(true);

		panel->setVisible(true);
	}
	else
	{
		useBtn->setVisible(true);
		useBtn->setTouchEnable(true);
		buyBtn->setVisible(false);
		buyBtn->setTouchEnable(false);

		panel->setVisible(false);
	}

	return discountGoodsLayout;
}

Layout* CandyResultLayer::getPropTipsLayout(void)
{
	if( !propTipsLayout)
	{
		propTipsLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(PROP_TIPS_LAYOUT_FILE));
		propTipsLayout->retain();

		propTipsPlayOnButton = dynamic_cast<UIButton*>(propTipsLayout->getChildByName("PlayOnButton"));
		if(CandyManager::getInstance()->resultMgr->getCurrentResult()  != CANDY_RESULT_NO_MOVE)
			propTipsPlayOnButton->setVisible(false);

		propTipsPlayOnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::PropTipsPlayOnCallBack));

		propTipsExitButton = dynamic_cast<UIButton*>(propTipsLayout->getChildByName("ExitGameButton"));
		propTipsExitButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::PropTipsExitCallBack));

		UIImageView *NoStepsImg = dynamic_cast<UIImageView*>(propTipsLayout->getChildByName("NoStepsTips"));
		UIImageView *NoTimeImg = dynamic_cast<UIImageView*>(propTipsLayout->getChildByName("NoTimeTips"));
		UIImageView *ExplosionImg = dynamic_cast<UIImageView*>(propTipsLayout->getChildByName("ExplosionTips"));
		NoStepsImg->setVisible(false);
		NoTimeImg->setVisible(false);
		ExplosionImg->setVisible(false);
		if(CandyManager::explosionBomb)
		{
			ExplosionImg->setVisible(true);
		}
		else if(CandyManager::gameMode == CANDY_MODE_TIMING)
		{
			NoTimeImg->setVisible(true);
		}
		else
		{
			NoStepsImg->setVisible(true);
		}
	}

	UIImageView *GoBuyImg = dynamic_cast<UIImageView*>(propTipsLayout->getChildByName("GoBuyImg"));
	UIImageView *PlayOnImg = dynamic_cast<UIImageView*>(propTipsLayout->getChildByName("PlayOnImg"));

	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_NO_MOVE)
	{
		propTipsPlayOnButton->setVisible(true);
		propTipsPlayOnButton->setTouchEnable(true);
		propTipsPlayOnButton->isEffects(true);
	}
	else
	{
		propTipsPlayOnButton->isEffects(false);
		propTipsPlayOnButton->setTouchEnable(false);
		propTipsPlayOnButton->setVisible(false);
	}

	propTipsExitButton->setTouchEnable(true);
	propTipsExitButton->isEffects(true);

	return propTipsLayout;
}

Layout* CandyResultLayer::getPropBuyLayout(void)
{
	if( !propBuyLayout)
	{
		propBuyLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(PROP_BUY_LAYOUT_FILE));
		propBuyLayout->retain();
		propBuyLayout->setTouchEnable(true);

		UIButton *pay = dynamic_cast<UIButton*>(propBuyLayout->getChildByName("BuyButton"));
		pay->setTouchEnable(true);
		pay->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::PropBuyOKCallBack));
		pay->isEffects(true);

		UIButton *cancel = dynamic_cast<UIButton*>(propBuyLayout->getChildByName("CloseButton"));
		cancel->setTouchEnable(true);
		cancel->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::PropBuyCancelCallBack));
		cancel->isEffects(true);
	}
	return propBuyLayout;
}

Layout* CandyResultLayer::getResortRankLayout(void *data)
{
	if ( !gemeResortRankLayout )
	{
		gemeResortRankLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(RESORTRANKSHOW_LAYOUT_JSONFILE));
		gemeResortRankLayout->retain();
		gemeResortRankLayout->setZOrder( 2 );
	}
	gemeResortRankLayout->setVisible(true);
	gemeResortRankLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("ReturnButton"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ButtonCallBack));

//	UIButton *m_shareWeixin = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("weixinbtn"));
//	m_shareWeixin->setTag( 99 );
////	m_shareWeixin->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	m_shareWeixin->setTouchEnable(true);
//	m_shareWeixin->isEffects(true);
//
//	UIButton *m_shareTWeibo = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("Tweibo"));
//	m_shareTWeibo->setTag( 100 );
////	m_shareTWeibo->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	m_shareTWeibo->isEffects(true);
//	m_shareTWeibo->setTouchEnable(true);
//
//	UIButton *m_shareSWeibo = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("Sweibo"));
//	m_shareSWeibo->setTag( 101 );
////	m_shareSWeibo->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	m_shareSWeibo->isEffects(true);
//	m_shareSWeibo->setTouchEnable(true);
//
//	UIButton *m_shareBtn = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("share_button"));
//	m_shareBtn->setTag( 105 );
//	m_shareBtn->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	m_shareBtn->isEffects(true);
//	m_shareBtn->setTouchEnable(true);
//
//
//
//
//	UIButton *pBtnToShare = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToShare"));
//	pBtnToShare->setTag( 102 );
////	pBtnToShare->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	pBtnToShare->setVisible(false);
//	pBtnToShare->setTouchEnabled(false);
//
//	UIButton *pBtnToRank = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToRank"));
//	pBtnToRank->setTag( 103 );
////	pBtnToRank->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ResortShareBtnCb));
//	pBtnToRank->setVisible(false);
//	pBtnToRank->setTouchEnabled(false);
//
//	UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_share"));
//	pPanToShare->setVisible( false );
//	pPanToShare->setTouchEnabled( false );
//
//	UIPanel *pPanRank = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_ranking"));		
//	pPanRank->setVisible( true );
//	pPanRank->setTouchEnabled( true );

	if(data != NULL)
	{
		UserSingleLevelStr *player = static_cast<UserSingleLevelStr *>(data);
		UIPanel* pPanel2 = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName( "HeadImg2" ));
		UIWidget *pWid2 = addHeadImg(*player);
		pPanel2->addChild(pWid2);
		//
		int i=0;
		std::list<UserSingleLevelStr>::iterator iterbegin = AnalyseJson::SingleLevelResultStr.friendInfo.begin();
		std::list<UserSingleLevelStr>::iterator iterend   = AnalyseJson::SingleLevelResultStr.friendInfo.end();
		for(i = 0;iterbegin!=iterend; ++iterbegin)
		{
			if(iterbegin->id == AnalyseJson::logOnMsg.baseInfo.id)
			{
				break;
			}
			i++;
		}
		UIPanel* pPanel1 = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName( "HeadImg1" ));
		UIWidget *pWid1 = addHeadImg(*iterbegin);
		pPanel1->addChild(pWid1);

		UILabelAtlas* pWenzi1 = dynamic_cast<UILabelAtlas*>(gemeResortRankLayout->getChildByName( "Rank_Score1" ));
		UILabelAtlas* pWenzi2 = dynamic_cast<UILabelAtlas*>(gemeResortRankLayout->getChildByName( "Rank_Score2" ));
		pWenzi1->setStringValue(CCString::createWithFormat("%d",iterbegin->result)->getCString());
		pWenzi2->setStringValue(CCString::createWithFormat("%d",player->result)->getCString());


		UILabel* pName1 =  dynamic_cast<UILabel*>(gemeResortRankLayout->getChildByName( "Rank_name1" ));
		UILabel* pName2 =  dynamic_cast<UILabel*>(gemeResortRankLayout->getChildByName( "Rank_name2" ));
		pName1->setFontSize(35);
		pName2->setFontSize(35);
		pName1->setText(iterbegin->nickname.c_str());
		pName2->setText(player->nickname.c_str());

		int myRank = i+1;
		UILabelAtlas* pRankNum1 = dynamic_cast<UILabelAtlas*>(gemeResortRankLayout->getChildByName( "Rank_num1" ));
		UILabelAtlas* pRankNum2 = dynamic_cast<UILabelAtlas*>(gemeResortRankLayout->getChildByName( "Rank_num2" ));
		pRankNum1->setStringValue(CCString::createWithFormat("%d",myRank)->getCString());
		pRankNum2->setStringValue(CCString::createWithFormat("%d",myRank+1)->getCString());

		AddFriendToRank(RESULT_WIDGE_GAME_RESORTRANK);

 		UIImageView *pFrame1 = dynamic_cast<UIImageView*>(gemeResortRankLayout->getChildByName("Rank_Frame1"));
 		UIImageView *pFrame2 = dynamic_cast<UIImageView*>(gemeResortRankLayout->getChildByName("Rank_Frame2"));
		pFrame1->runAction(CCSequence::create(
			CCDelayTime::create(0.8f),
			CCEaseElasticInOut::create(CCMoveBy::create(0.6f,ccp(0,289)),0.8f ),
			NULL)
			);
		pFrame2->runAction(CCSequence::create(
			CCDelayTime::create(0.8f),
			CCEaseElasticInOut::create(CCMoveBy::create(0.6f,ccp(0,-299)),0.8f ),
			NULL)
			);
	}
 	return gemeResortRankLayout;
}

void CandyResultLayer::ResortShareBtnCb(CCObject *pSender)
{
	UIButton *m_shareWeixin = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("weixinbtn"));
	UIButton *m_shareTWeibo = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("weixinbtn"));
	UIButton *m_shareSWeibo = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("Sweibo"));
	UIButton *m_shareBtn = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("share_button"));

	int BtnType = ((UIButton*)pSender)->getTag();
	int userid = (int)((UIButton*)pSender)->data;

	switch( BtnType )
	{
	case 105:
		{
			m_shareBtn->setTouchEnabled(false);
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case 100:
		{
			m_shareTWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "4", "2");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case 101:
		{
			m_shareSWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "4", "1");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case 99:
		{
			m_shareWeixin->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "4", "3");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case 103:
		{
			UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( false );
			pPanToShare->setZOrder( 5 );
			pPanToShare->setTouchEnabled( false );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( true );
			pPanRank->setZOrder( 6 );
			pPanRank->setTouchEnabled( true );

			UIButton *pBtnToShare = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(true);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(false);
		}
		break;

	case 102:
		{
			UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( true );
			pPanToShare->setZOrder( 6 );
			pPanToShare->setTouchEnabled( true );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(gemeResortRankLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( false );
			pPanRank->setZOrder( 5 );
			pPanRank->setTouchEnabled( false );

			UIButton *pBtnToShare = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(false);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(gemeResortRankLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(true);

			m_shareWeixin->setTouchEnabled(true);

			m_shareTWeibo->setTouchEnabled(true);

			m_shareSWeibo->setTouchEnabled(true);
		}
		break;

	case BUTTON_TO_HANDLELIFE:
		{
			((UIButton*)pSender)->setVisible(false);
			MsgMgr::sendHandselLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, userid);
			CCPoint pos = ((UIButton*)pSender)->getParent()->convertToWorldSpace(((UIButton*)pSender)->getPosition());
			CCNode* particle = CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(0,0));
			((UIButton*)pSender)->getRenderer()->addChild(particle);
			//CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(pos.x, pos.y),this);
		}
		break;
	}
}

UIWidget* CandyResultLayer::addHeadImg(UserSingleLevelStr player)
{
	UIPanel* pPanel = UIPanel::create();
	pPanel->setBackGroundColor(ccBLACK);
	//头像框
	UIImageView* pHeadFrameImg = UIImageView::create();
	pHeadFrameImg->setTexture( "Image/MainMapUi/headframe.png" );
	pHeadFrameImg->setVisible( true );
	pHeadFrameImg->setPosition(ccp(58, 60));
	pPanel->addChild( pHeadFrameImg );
	//头像
	UIImageView* pHeadImg = UIImageView::create();
	float nScale = 0;
	char UrlName[128]= {0};
	HeadDownMgr::getHeadNameForUrl(player.headPicUr, UrlName);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	char *HeadName = (char *)CCString::createWithFormat("%s.png",UrlName)->getCString();
	char *headPath= (char *)CCString::createWithFormat("%s%s",AnalyseJson::CandPicPath, HeadName)->getCString();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	char *headPath= (char *)CCString::createWithFormat("Image/wemepci/%s.png", UrlName)->getCString();
#endif
	pHeadImg->setTexture( headPath );
	nScale = 110/95;
	pHeadImg->setScale( nScale );
	pHeadImg->setVisible( true );
	pHeadImg->setPosition(ccp(58, 60));
	pPanel->addChild( pHeadImg);
	pHeadImg->setZOrder(-1);
	//性别
	UIImageView* pSexbgImg = UIImageView::create();
	if ( 1 == player.gender )
	{
		pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
	}
	else
	{
		pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );
	}
	pSexbgImg->setVisible( true );
	pSexbgImg->setPosition(ccp(95,22));
	pPanel->addChild( pSexbgImg);

// 	UITextArea* pName = UITextArea::create();
// 	pName->setPosition( ccp(57, -16) );
// 	pName->setColor( ccc3(255,255,255));
// 	pName->setFontSize(30);
// 	pName->setText(player.nickname.c_str());
// 	pName->setVisible( true );
// 	pPanel->addChild( pName );

	return pPanel;
}
void CandyResultLayer::ButtonCallBack(CCObject *pSender)
{
	grayLayer->setOpacity(0);

	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	Layout* widget  = gemeResortRankLayout;
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::TurnToGameWinLayout)), 
			NULL)
			);
	}
}
void CandyResultLayer::TurnToGameWinLayoutByJava()
{
	grayLayer->setOpacity(0);

	Layout* widget  = gemeResortRankLayout;
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,0.7f, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::TurnToGameWinLayout)), 
			NULL)
			);
	}
}

void CandyResultLayer::TurnToGameWinLayout()
{
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_WIN);
}

Layout* CandyResultLayer::getGameWinLayout(void)
{
	if(!gameWinLayout)
	{
		gameWinLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(GAME_WIN_LAYOUT_FILE));
		gameWinLayout->retain();
		gameWinLayout->setTouchEnabled(true);

		gameWinNextButton = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("NextStageButton"));
		gameWinNextButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::gameWinNextCallBack));
		gameWinNextButton->isEffects(true,0.5);

		gameWinReturnButton = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("ReturnButton"));
		gameWinReturnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::gameWinReturnCallBack));
		gameWinReturnButton->setVisible(true);
		gameWinReturnButton->setTouchEnabled(true);


		if ( 6 <= CandyManager::currentLevel )
		{
			gameWinReturnButton->isEffects( true ); 
			gameWinReturnButton->setVisible( true );
			gameWinReturnButton->setTouchEnabled( true );
		}

		m_ChoujiangBtn = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("ButtonChoujiang"));
		m_ChoujiangBtn->setTouchEnabled(false);
		m_ChoujiangBtn->addReleaseEvent(this,coco_releaseselector(CandyResultLayer::ChoujiangCallback));
		m_ChoujiangBtn->setVisible(false);
		m_ChoujiangBtn->setZOrder(10);

		UIImageView* zhuanpan = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("zhuanpan"));
		zhuanpan->setVisible(false);

		if (AnalyseJson::logOnMsg.baseInfo.candyNum >= 2000)
		{
			m_ChoujiangBtn->setVisible(true);
			m_ChoujiangBtn->setTouchEnabled(true);

			zhuanpan->setVisible(true);
			//m_ChoujiangBtn->isEffects(true,0.5);
			zhuanpan->runAction(CCRepeatForever::create(CCRotateBy::create(1,360)));
		}
		else
		{
			gameWinNextButton->setPosition(ccp(0,gameWinNextButton->getPosition().y));
		}

		/*m_shareWeixin = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("weixinbtn"));
		m_shareWeixin->setTag(  SHARE_TO_WEXIN  );
		m_shareWeixin->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb));
		m_shareWeixin->setTouchEnable(true);
		m_shareWeixin->isEffects(true);*/

		/*m_shareTWeibo = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("Tweibo"));
		m_shareTWeibo->setTag(   SHARE_TO_QZONE);
		m_shareTWeibo->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb));
		m_shareTWeibo->isEffects(true);
		m_shareTWeibo->setTouchEnable(true);*/


		/*m_shareSWeibo = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("Sweibo"));
		m_shareSWeibo->setTag(  SHARE_TO_SINA );
		m_shareSWeibo->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb));
		m_shareSWeibo->isEffects(true);
		m_shareSWeibo->setTouchEnable(true);*/


		for(int i=0; i<3; i++)
		{
			ScoreStar[i] = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName(
				CCString::createWithFormat("ScoreStar%d",i+1)->getCString()));
			ScoreStar[i] ->setOpacity(0);
		}

		//　播放特效
// 		UIImageView *particleEffectNode = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("particleEffect"));
// 		CandyParticle::displayCandyParticle(CANDY_PARTICLE_WIN_LIGHT, ccp(0,0), particleEffectNode->getRenderer());

#ifndef CLOSE_ARMATURE	
		UIImageView *leftManNode = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("ArmatureManL"));
		leftManNode->setPosition(leftManNode->getPosition() + CCPoint(0, 40));
		leftManNode->setTexture("Image/CandyGame/Others/ImgRole2.png");
		// 		CCArmature *leftManArmature = CCArmature::create("shengli2");
// 		leftManArmature->getAnimation()->play("Animation1");
// 		leftManNode->getRenderer()->addChild(leftManArmature);

		UIImageView *rightManNode = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("ArmatureManR"));
		rightManNode->setTexture("Image/CandyGame/Others/ImgRole1.png");
		// 		CCArmature *rightManArmature = CCArmature::create("shengli");
// 		rightManNode->getRenderer()->addChild(rightManArmature);
// 		rightManArmature->getAnimation()->play("Animation1");
#endif
	}

	UIButton* gameWinPlayOnButton = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("PlayOnButton"));
	gameWinPlayOnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::gameWinPalyAgainCallback));
	gameWinPlayOnButton->setTouchEnable(true);
	gameWinPlayOnButton->isEffects(true);

	if ( 5 >= CandyManager::currentLevel )
	{
		gameWinPlayOnButton->setVisible( false );
		gameWinPlayOnButton->setTouchEnable(false);
	}
	else
		gameWinPlayOnButton->setVisible( true );

	UIImageView *pScoreImg = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("FontScoreImg"));

	int tempScore = CandyManager::getInstance()->scoreMgr->getCurrentScore();

	std::list<UserSingleLevelStr>::iterator p = AnalyseJson::SingleLevelResultStr.friendInfo.begin();
	int i ,j;
	for ( i = 0, j = 0; i < (int)AnalyseJson::SingleLevelResultStr.friendInfo.size(); i++)
	{
		if ( p->result > tempScore )
			j++;

		if ( p->id == AnalyseJson::logOnMsg.baseInfo.id )
			p->result = tempScore;
	}

	AnalyseJson::SingleLevelResultStr.friendInfo.sort(Cmpare2());

	if ( 0 )//j < i)
	{
		pScoreImg->setVisible( false );
	}
	else	
	{
		pScoreImg->setVisible( true );
	}

	// 奖励糖果币

	UIImageView *pRewardCandyBg = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("FontRewardImg"));
	UIImageView *pScoreBg = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("FontScoreImg"));

	pRewardCandyBg->setVisible( false );
	pScoreBg->setVisible( false );

	// 有奖励
	if ( CommonData::getLastStarNumForLevel() < CommonData::getStarForLevel( CandyManager::currentLevel ))
	{
		pRewardCandyBg->setVisible( true );
		UILabelAtlas *pCandyNumLabel = dynamic_cast<UILabelAtlas*>(gameWinLayout->getChildByName("CandyNumLabel"));
		pCandyNumLabel->setStringValue(CCString::createWithFormat("%d",CommonData::m_curLevelRewardNum)->getCString());

		UILabelAtlas *pScoreLabel = dynamic_cast<UILabelAtlas*>(gameWinLayout->getChildByName("ScoreLabel1"));
		pScoreLabel->setStringValue(CCString::createWithFormat("%d",CandyManager::getInstance()->scoreMgr->getCurrentScore())->getCString());
	}
	// 无奖励
	else
	{
		pScoreBg->setVisible( true );

		UILabelAtlas *scoreLabel = dynamic_cast<UILabelAtlas*>(gameWinLayout->getChildByName("ScoreLabel"));
		scoreLabel->setStringValue(CCString::createWithFormat("%d",CandyManager::getInstance()->scoreMgr->getCurrentScore())->getCString());
	}
	

//	UIButton *pBtnToShare = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToShare"));
//	pBtnToShare->setTag( BUTTON_TO_SHARE );
////	pBtnToShare->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb));
//	pBtnToShare->setTouchEnabled(false);
//	pBtnToShare->setVisible(false);
//
//	UIButton *pBtnToRank = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToRank"));
//	pBtnToRank->setTag( BUTTON_TO_RANK );
////	pBtnToRank->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb));
//	pBtnToRank->setTouchEnabled(false);
//	pBtnToRank->setVisible(false);
//
//	UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_share"));
//	pPanToShare->setVisible( false );
//	pPanToShare->setTouchEnabled( false );
//
//	UIPanel *pPanRank = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_ranking"));		
//	pPanRank->setVisible( true );
//	pPanRank->setTouchEnabled( true );
//
//	gameWinNextButton->setVisible(false);

// 	UILabelAtlas *levelLabel = dynamic_cast<UILabelAtlas*>(gameWinLayout->getChildByName("StageNumLabel"));
// 	levelLabel->setStringValue(CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());

	/*UIImageView *pImgView = dynamic_cast<UIImageView*>(gameWinLayout->getChildByName("ContentBg_1"));		
	if(CommonData::getMaxLevel() < 20)
	{
		pImgView->setVisible(false);
		pImgView->setTouchEnable(false,true);
	}
	else
	{
		pImgView->setVisible(true);
		pImgView->setTouchEnable(true,true);
	}*/

	AddFriendToRank(RESULT_WIDGE_GAME_WIN);
	return gameWinLayout;
}

void CandyResultLayer::ChoujiangCallback(CCObject* sender)
{
	grayLayer->setOpacity(0);

	CommonData::setButtonTouchEnable(sender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	getUILayer()->getRootWidget()->getRenderer()->removeChildByTag(567);
	moveOutGameLayerAction();

	Layout* widget  = gameWinLayout;
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::BackToMainMapAndShowChoujiangUI)), 
			NULL)
			);
	}
}

void CandyResultLayer::BackToMainMapAndShowChoujiangUI()
{
	CommonData::m_isShowChoujiang = true;
	//返回到大地图，并且显示抽奖界面
	returnMainMapCallBack();
}

void CandyResultLayer::AddFriendToRank(ResultWidgetType type)
{
	

}

void CandyResultLayer::ShareBtnCb(CCObject *pSender)
{
	int BtnType = ((UIButton*)pSender)->getTag();
	int userid = (int)((UIButton*)pSender)->data;

	switch( BtnType )
	{
	case SHARE_TO_QZONE:
		{
			//m_shareTWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "2", "2");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case SHARE_TO_SINA:
		{
			//m_shareSWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "2", "1");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case SHARE_TO_WEXIN:
		{
			//m_shareWeixin->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "2", "3");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case BUTTON_TO_RANK:
		{
			/*UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( false );
			pPanToShare->setZOrder( 5 );
			pPanToShare->setTouchEnabled( false );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( true );
			pPanRank->setZOrder( 6 );
			pPanRank->setTouchEnabled( true );

			UIButton *pBtnToShare = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(true);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(false);*/
		}
		break;

	case BUTTON_TO_SHARE:
		{
			/*UIPanel *pPanToShare = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( true );
			pPanToShare->setZOrder( 6 );
			pPanToShare->setTouchEnabled( true );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(gameWinLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( false );
			pPanRank->setZOrder( 5 );
			pPanRank->setTouchEnabled( false );

			UIButton *pBtnToShare = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(false);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(gameWinLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(true);*/

			//m_shareWeixin->setTouchEnabled(true);
			//m_shareTWeibo->setTouchEnabled(true);
			//m_shareSWeibo->setTouchEnabled(true);
		}
		break;

	case BUTTON_TO_HANDLELIFE:
		 {
			 //((UIButton*)pSender)->setVisible(false);
			 MsgMgr::sendHandselLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, userid);
			// CCPoint pos = ((UIButton*)pSender)->getParent()->convertToWorldSpace(((UIButton*)pSender)->getPosition());
			 //CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(pos.x, pos.y),this);
			 CCNode* particle = CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGXIN_EFFECT, ccp(0,0));
			 ((UIButton*)pSender)->getRenderer()->addChild(particle, 1000);
			 ((UIButton*)pSender)->disable(true);
		 }
		 break;
	}
}

Layout* CandyResultLayer::getGameLoseLayout(void)
{
	if(!gameLoseLayout)
	{
		gameLoseLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(GAME_LOSE_LAYOUT_FILE));
		gameLoseLayout->retain();
		gameLoseLayout->setTouchEnabled(true);

		gameLosePlayOnButton = dynamic_cast<UIButton*>(gameLoseLayout->getChildByName("PlayOnButton"));
		gameLosePlayOnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::gameLosePlayAgainCallBack));

		gameLoseReturnButton = dynamic_cast<UIButton*>(gameLoseLayout->getChildByName("ReturnButton"));
		gameLoseReturnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::gameLoseReturnCallBack));

#ifndef CLOSE_ARMATURE	
		UIImageView *leftManNode = dynamic_cast<UIImageView*>(gameLoseLayout->getChildByName("ArmatureManL"));
		leftManNode->setPosition(leftManNode->getPosition() + CCPoint(-40, -40));
		leftManNode->setOpacity(255);
		leftManNode->setTexture("Image/CandyGame/Others/ImgRole3.png");
// 		CCArmature *leftManArmature = CCArmature::create("stageFailedRightMan");
// 		leftManArmature->getAnimation()->play("Animation1");
// 		leftManNode->getRenderer()->addChild(leftManArmature);
// 
// 		UIImageView *rightManNode = dynamic_cast<UIImageView*>(gameLoseLayout->getChildByName("ArmatureManR"));
// 		CCArmature *rightManArmature = CCArmature::create("stageFailedLeftMan");
// 		rightManNode->getRenderer()->addChild(rightManArmature);
// 		rightManArmature->getAnimation()->play("Animation1");
// 		rightManArmature->setScaleX( - 1);
#endif

	}

	gameLosePlayOnButton->setTouchEnable(true);
	gameLoseReturnButton->setTouchEnable(true);
	gameLosePlayOnButton->isEffects(true,1.5f);
	gameLoseReturnButton->isEffects(true);

	return gameLoseLayout;
}

Layout* CandyResultLayer::getNoLifeLayout(void)
{
	noLifeLayout = CommonWidgt::getSuccessUI(WIDGET_TYPE_GAME, PROMPT_TYPE_LIFELACK_TO_MAP );
	return noLifeLayout;
	
#if 0
	if( !noLifeLayout)
	{
		noLifeLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(NO_LIFE_LAYOUT_FILE));
		noLifeLayout->retain();
		noLifeLayout->setTouchEnable(true);

		noLifeReturnButton = dynamic_cast<UIButton*>(noLifeLayout->getChildByName("ReturnButton"));
		noLifeReturnButton->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::noLifeReturnCallBack));
	}
	noLifeReturnButton->setTouchEnable(true);
	noLifeReturnButton->isEffects(true);
	return noLifeLayout;
#endif
}

void CandyResultLayer::rewardsPropBtnCallBack(CCObject* pSender)
{
	UIButton* RewardsBut = (UIButton*)pSender;
	RewardsBut->setTouchEnabled(false);

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(49);

#ifdef CANDY_STATISITICAL_DATA
	/*if( 0 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_64 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_90 );*/
#endif

	CCPoint tem0;
	if ( CommonData::getMaxLevel() == 0 && CandyManager::currentLevel == 1  )
	{
		UIButton* pPropPoint = dynamic_cast<UIButton*>(CandyManager::getInstance()->uiLayer->gameUiLayout->getChildByName("ButtonProp1"));
		tem0 = pPropPoint->getParent()->convertToWorldSpace(pPropPoint->getPosition());
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);
	}
	else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3)
	{
		UIButton* pPropPoint = dynamic_cast<UIButton*>(CandyManager::getInstance()->uiLayer->gameUiLayout->getChildByName("ButtonProp2"));
		tem0 = pPropPoint->getParent()->convertToWorldSpace(pPropPoint->getPosition());
		CommonData::changePropNum(CANDY_PROP_IN_SWAP,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_SWAP);
	}
	else if(CommonData::getMaxLevel() == 4 && CandyManager::currentLevel == 5)
	{
		UIButton* pPropPoint = dynamic_cast<UIButton*>(CandyManager::getInstance()->uiLayer->gameUiLayout->getChildByName("ButtonProp3"));
		tem0 = pPropPoint->getParent()->convertToWorldSpace(pPropPoint->getPosition());
		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);
	}

	CCPoint tem1;
	UIImageView* RewardProp = dynamic_cast<UIImageView*>(rewardsPropLayout->getChildByName( "RewardProp" ));
	if(RewardProp != NULL)
	{
		tem1 = RewardProp->getParent()->convertToWorldSpace(RewardProp->getPosition());
	}

	CCSprite* propadd5 = CCSprite::create(CommonData::getReward().c_str());
	if(propadd5 != NULL)
	{
		propadd5->setScale(1.6f);
		propadd5->setPosition( tem1 );
		CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(propadd5,232);

		CCActionInterval* pMoveto = CCMoveTo::create(0.8f, tem0);
		propadd5->runAction(CCSequence::create(
			pMoveto,
			CCCallFuncN::create(this, callfuncN_selector(CandyResultLayer::AddRewardCallback)),
			NULL));
		propadd5->runAction(CCScaleTo::create(0.8f,1.0f));
	}
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(rewardsPropLayout->getChildByName( "Content" ));
	CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
	CCActionInterval * fadeout = CCFadeOut::create(0.2f);
	CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
	CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);
	pImgDlg->runAction(CCSequence::create(
		pScale,
		spawn,
		CCCallFunc::create(this, callfunc_selector(CandyResultLayer::removeRewardCallBack)),
		NULL)
		);
}

void CandyResultLayer::removeRewardCallBack()
{
	getUILayer()->removeWidget(rewardsPropLayout);
}

void CandyResultLayer::AddRewardCallback(CCNode* pSender)
{
	//mini精简版全部显示
	for (int i = 0; i < 5; ++i)
	{
		CandyManager::getInstance()->uiLayer->PropButton[0]->setVisible(true);
		CandyManager::getInstance()->uiLayer->PropButton[0]->active();
	}
	
	/*if ( 1 == CandyManager::currentLevel)
	{
		CandyManager::getInstance()->uiLayer->PropButton[0]->setVisible(true);
		CandyManager::getInstance()->uiLayer->PropButton[0]->active();
	}
	else if(CandyManager::currentLevel == 3)
	{
		CandyManager::getInstance()->uiLayer->PropButton[1]->setVisible(true);
		CandyManager::getInstance()->uiLayer->PropButton[1]->active();
	}
	else if(CandyManager::currentLevel == 5)
	{
		CandyManager::getInstance()->uiLayer->PropButton[2]->setVisible(true);
		CandyManager::getInstance()->uiLayer->PropButton[2]->active();
	}*/

	CCPoint pos = pSender->getParent()->convertToWorldSpace(pSender->getPosition());
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y),this);

	pSender->removeFromParent();

	CandyManager::getInstance()->uiLayer->updatePropNum();
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_STAGE_CLEAR);
	grayLayer->runAction(CCFadeTo::create(0.5f,170));

	if(CandyManager::getInstance()->scoreMgr->getCurrentScore() > CommonData::getLevelScore(CandyManager::currentLevel) )
		CommonData::sendLevelScore( CandyManager::currentLevel, CandyManager::getInstance()->scoreMgr->getCurrentScore() );

}

void CandyResultLayer::BuyAdd5PropBtnCallBack(CCObject* pSender)
{
	UIButton* pBtn = (UIButton*)pSender;
	int nIndex = pBtn->getTag();

	if (0 ==  nIndex)
	{
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PASS_LEVEL);
	}
	else if(1 == nIndex)
	{
		CommonData::m_BuyAdd5From = 1;	//购买+5在失败界面	

		this->unschedule(schedule_selector(CandyResultLayer::UpdataCountDown));
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
		CandyManager::getInstance()->resultMgr->getResultLayer()->setpropId(CANDY_PROP_IN_STEP5);

		grayLayer->setOpacity(0);
		Layout* widget = getAdd5PropLayout();
		CCPoint point = widget->getPosition();;
		widget->setPosition(ccp(-1000,0));
		if(CommonData::getPropNum(CANDY_PROP_IN_STEP5))
		{
			CandyManager::getInstance()->musicMgr->playBgm();
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
			CandyManager::getInstance()->uiLayer->useProp(CANDY_PROP_IN_STEP5);
		}
		else
		{
			CandyManager::getInstance()->resultMgr->setCurrentResult( CANDY_RESULT_BUYPROPING );

			//if (atoi(p->price.c_str()) > AnalyseJson::logOnMsg.baseInfo.gemNum)
			//{
			//	//直接进入支付界面
			//	CommonData::m_buytype = CANDY_PROP_IN_STEP5;
			//	CommonData::m_buyMutipropNum = 0;
			//	CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_80, MOBILE_MONEY8_BUY_PROPNUM );
			//}
			//else
			//{
			//	MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_IN_STEP5, 1);
			//}

			//mini版本直接进入支付界面
			/*CommonData::m_buytype = CANDY_PROP_IN_STEP5;
			CommonData::m_buyMutipropNum = 0;
			CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_80, MOBILE_MONEY8_BUY_PROPNUM );*/

			//新版支付
			CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_STEP5);
		}
	}
}

void CandyResultLayer::PropTipsPlayOnCallBack(CCObject *pSender)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	CandyManager::getInstance()->resultMgr->getResultLayer()->setpropId(CANDY_PROP_IN_STEP5);
	if(CommonData::getPropNum(CANDY_PROP_IN_STEP5))
	{
		CandyManager::getInstance()->musicMgr->playBgm();
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
		CandyManager::getInstance()->uiLayer->useProp(CANDY_PROP_IN_STEP5);

		grayLayer->setOpacity(0);
		Layout* widget = getPropTipsLayout();
		widget->setPosition(ccp(-1000,0));
	}
	else
	{
		CandyManager::getInstance()->resultMgr->getResultLayer()->showPropBuy();
	}
#ifdef CANDY_STATISITICAL_DATA
	CommonData::sendUseMoreFiveStepStatistics();
#endif
}

void CandyResultLayer::PropTipsExitCallBack(CCObject *pSender)
{
	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	grayLayer->runAction(CCFadeTo::create(0.5f,0));

	CCAction *action;
	if(CandyManager::explosionBomb)
	{
		action = CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::runExplosionBomb)), 
			NULL);
	}
	else
	{
		action = CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::runStageFailedAction)), 
			NULL);
	}
	Layout* widget  = getPropTipsLayout();
	if(widget)
		widget->runAction(action);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
}

void CandyResultLayer::PropBuyOKCallBack(CCObject *pSender)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
}

void CandyResultLayer::PropBuyCancelCallBack(CCObject *pSender)
{
	CandyResultType ret = CandyManager::getInstance()->resultMgr->getCurrentResult();
	if(ret == CANDY_RESULT_PLAYING)
	{
		CandyManager::getInstance()->resultMgr->removeResultLayer();
	}
	else// if(ret == CANDY_RESULT_LOSE)
	{
		//getUILayer()->removeWidget(getPropBuyLayout());
	}
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
}

void CandyResultLayer::gameWinNextCallBack(CCObject *pSender)
{
	grayLayer->setOpacity(0);

	getUILayer()->getRootWidget()->getRenderer()->removeChildByTag(567);

	//grayLayer->runAction( CCFadeTo::create(0.5f, 0));
	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

#ifdef CANDY_STATISITICAL_DATA
	/*if(CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=10)
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_21, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());

	CandyManager::currentLevel;
	if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_66 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_76 );*/
#endif

//	if(currentWidgetType != RESULT_WIDGE_GAME_LOSE &&CandyManager::currentLevel >= CommonData::getMaxLevel())
//	{
//		// by Eason
//		CandyManager::getInstance()->resultMgr->setCurrentResult( CANDY_WIN_EXIT_GAME);
//
//		moveOutGameLayerAction();
//		Layout* widget  = getGameWinLayout();
//		if(widget)
//		{
//			widget->runAction(CCSequence::create(
//				getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
//				NULL)
//				);
//		}
//
//		//MainMap::EnteyMapScene(GAME_STATE_SUCCEE_NEXT);
//	}
//	else
//	{
//		Layout* widget;
//		if(currentWidgetType == RESULT_WIDGE_GAME_LOSE)
//		{
//			widget= getGameLoseLayout();
//		}
//		else
//		{
//			widget= gameWinLayout;
//			CandyManager::currentLevel++;
//			if(CandyManager::currentLevel >225)
//				CandyManager::currentLevel = 1;
//		}
//
//		if(widget)
//		{
//#if defined( CANDY_VERSIONS_FOR_SINGLE)
//			widget->runAction(CCSequence::create(
//				getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
//				CCCallFunc::create(this, callfunc_selector(CandyResultLayer::nextStageCallback)), 
//				NULL)
//				);
//
//#else
//			if(AnalyseJson::logOnMsg.lifeInfo.lifeNum > 0)
//			{
//				if(currentWidgetType == RESULT_WIDGE_GAME_WIN)
//				{
//					widget->runAction(CCSequence::create(
//						getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
//						CCCallFunc::create(this, callfunc_selector(CandyResultLayer::nextStageCallback)), 
//						NULL)
//						);
//				}
//				else if(currentWidgetType == RESULT_WIDGE_GAME_LOSE)
//				{
//					widget->runAction(CCSequence::create(
//						getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
//						CCCallFunc::create(this, callfunc_selector(CandyResultLayer::discountGoodsCallback)), 
//						NULL)
//						);
//				}
//			}
//			else
//			{
//				showWidget(RESULT_WIDGE_NO_LIFE, true);
//			}
//#endif
//
//		}
//	}
//

	Layout* widget;
	if(currentWidgetType == RESULT_WIDGE_GAME_LOSE)
	{
		widget= getGameLoseLayout();
	}
	else
	{
		widget= gameWinLayout;
		CandyManager::currentLevel++;
		if(CandyManager::currentLevel >225)
			CandyManager::currentLevel = 1;
	}

	if(widget)
	{
#if defined( CANDY_VERSIONS_FOR_SINGLE)
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::nextStageCallbackBefore())), 
			NULL)
			);

#else
		if(AnalyseJson::logOnMsg.lifeInfo.lifeNum > 0)
		{
			if(currentWidgetType == RESULT_WIDGE_GAME_WIN)
			{
				widget->runAction(CCSequence::create(
					getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
					CCCallFunc::create(this, callfunc_selector(CandyResultLayer::nextStageCallbackBefore)), 
					NULL)
					);
			}
			else if(currentWidgetType == RESULT_WIDGE_GAME_LOSE)
			{
				widget->runAction(CCSequence::create(
					getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
					CCCallFunc::create(this, callfunc_selector(CandyResultLayer::discountGoodsCallback)), 
					NULL)
					);
			}
		}
		else
		{
			showWidget(RESULT_WIDGE_NO_LIFE, true);
		}
#endif

	}
}

void CandyResultLayer::gameWinReturnCallBack(CCObject *pSender)
{
	grayLayer->setOpacity(0);

	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	getUILayer()->getRootWidget()->getRenderer()->removeChildByTag(567);
	moveOutGameLayerAction();

	Layout* widget  = gameWinLayout;
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::returnMainMapCallBack)), 
			NULL)
			);
	}
}


// 重新开始
void CandyResultLayer::gameLosePlayAgainCallBack(CCObject *pSender)
{
	if (AnalyseJson::logOnMsg.lifeInfo.lifeNum > 0)
	{
		moveOutGameLayerAction();
		CCScene *pScene = PlayGame::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	else
	{
		showWidget(RESULT_WIDGE_NO_LIFE, true);
	}
	return;

	//CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);

	//grayLayer->runAction(CCFadeTo::create(0.5f, 0));

	//CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	//moveOutGameLayerAction();

	//Layout* widget  = getGameLoseLayout();
	//if(widget)
	//{
	//	widget->runAction(CCSequence::create(
	//		getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
	//		//CCCallFunc::create(this, callfunc_selector(CandyResultLayer::playAgainCallback)), 
	//		NULL)
	//		);
	//}

	//gameWinNextCallBack(NULL);
	//CommonData::setButtonTouchEnable(pSender, false);
}


// 返回大地图
void CandyResultLayer::gameLoseReturnCallBack(CCObject *pSender)
{
	grayLayer->runAction(CCFadeTo::create(0.5f, 0));

	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);
	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

	CandyManager::getInstance()->resultMgr->setCurrentResult( CANDY_FAIL_EXIT_GAME);
	moveOutGameLayerAction();
	Layout* widget  = getGameLoseLayout();
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			NULL)
			);
	}
}

void CandyResultLayer::stageInfoPlayGame(void)
{
//	Layout* widget  = CandyStageIntro::getLayout(STAGE_INTRO_PLAY_GAME,CandyManager::currentLevel);
	Layout* widget = CandyStageIntro::layout->stageIntroLayout;
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::playNextCallback)), 
			NULL)
			);
	}
}

void CandyResultLayer::gameNextReturnCallBack(CCObject *pSender)
{
	Layout* widget  = CandyStageIntro::getLayout(STAGE_INTRO_PLAY_GAME,CandyManager::currentLevel);
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			CCCallFunc::create(this, callfunc_selector(CandyResultLayer::returnMainMapCallBack)), 
			NULL)
			);
	}
}

void CandyResultLayer::noLifeReturnCallBack(CCObject *pSender)
{
	CommonData::setButtonTouchEnable( pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	MainMap::EnteyMapScene(GAME_STATE_FAIL);
}

void CandyResultLayer::displayScoreStarParticle(CCNode* sender)
{	
	UIButton *nextButton = (UIButton *)sender->getUserData();
	if(nextButton)
	{
		nextButton->setVisible(true);
		nextButton->setTouchEnable(true);
		nextButton->isEffects(true);
	}

	CandyManager::getInstance()->effectLayer->displayStarLightEffect(sender);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CLEAR_STAR);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAR_FIREWORKS, ccp(0,0), sender);
}

void CandyResultLayer::moveOutGameLayerAction(void)
{
	PlayGame *playGameLayer = (PlayGame *)CandyManager::getInstance()->getCurrentLayer();
	playGameLayer->addBg(false);
	CandyManager::getInstance()->uiLayer->runAction(CCMoveBy::create(0.5f,ccp(-1000,0)));
	CandyManager::getInstance()->candyLayer->runAction(CCMoveBy::create(0.5f,ccp(1000,0)));
//	CandyManager::getInstance()->effectLayer->undisplayEnergyJarEffect();
}

void CandyResultLayer::runStageClearAction(void)
{
	stageClearCallback();
}


void CandyResultLayer::runPropTipsAction(void)
{
	showWidget(RESULT_WIDGE_PROP_TIPS, true);
}

void CandyResultLayer::runExplosionBomb(void)
{
	CandyCell *explosion = CandyManager::getInstance()->explosionMgr->getExplosionsCandy();
	if(explosion)
	{
		CandyManager::getInstance()->effectLayer->displayExplosionBombEffect(explosion->index, explosion->color);
	}
	runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCCallFunc::create(this, callfunc_selector(CandyResultLayer::runStageFailedAction)), 
		NULL));
}

void CandyResultLayer::UpdataAdd5CountDown()
{
//	UIImageView* pAdd5CountDown = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Img_labelNum" ));
//	pAdd5CountDown->setTexture("Image/CandyGame/Others/CountTime5.png");
	m_nCountDown = 100;
	this->schedule(schedule_selector(CandyResultLayer::UpdataCountDown), 0.04f, kCCRepeatForever, 0);
}

void CandyResultLayer::UpdataCountDown(float t)
{	
//	UIImageView* pAdd5CountDown = dynamic_cast<UIImageView*>(add5PropLayout->getChildByName( "Img_labelNum" ));

// 	switch(m_nCountDown)
// 	{
// 	case 4:
// 		pAdd5CountDown->setTexture("Image/CandyGame/Others/CountTime4.png");
// 		break;
// 	case 3:															 
// 		pAdd5CountDown->setTexture("Image/CandyGame/Others/CountTime3.png");
// 		break;
// 	case 2:															 
// 		pAdd5CountDown->setTexture("Image/CandyGame/Others/CountTime2.png");
// 		break;
// 	case 1:															 
// 		pAdd5CountDown->setTexture("Image/CandyGame/Others/CountTime1.png");
// 		break;
// 	}

	UILoadingBar* pLoading = dynamic_cast<UILoadingBar*>(add5PropLayout->getChildByName( "LoadingBar" ));
	pLoading->setPercent(100.0f*m_nCountDown/100);


	if(0 == m_nCountDown)
	{
		m_nCountDown = 100;
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PASS_LEVEL);
		this->unschedule(schedule_selector(CandyResultLayer::UpdataCountDown));
	}
	else
	{
		m_nCountDown--;
	}
}

// 退到大地图处理 
void CandyResultLayer::runStageFailedAction(void)
{
	if(grayLayer)
	{
		grayLayer->removeFromParent();
		grayLayer = NULL;
	}

	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_STAGE_FAILED);
}

void CandyResultLayer::returnMainMapCallBack(void)
{
	CandyManager::getInstance()->musicMgr->unreloadCandyGameMusic();

	if( CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_STAGE_CLEAR)
		MainMap::EnteyMapScene(GAME_STATE_SUCCEE);
	else
		MainMap::EnteyMapScene(GAME_STATE_FAIL);
}

void CandyResultLayer::stageClearCallback(void)
{
//	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_WIN);
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_RESORTRANK);
}

void CandyResultLayer::nextStageCallbackBefore(void)
{
	int temp = (CandyManager::currentLevel - 1) % 6;
// 	if(temp == 1)
// 	{
// 		showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)Zhadan_Gift);
// 	}
// 	else 
	if(temp == 4)
	{
		showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)Zhizun_Gift);
	}
	else
	{
		nextStageCallback();
	}
}

void CandyResultLayer::nextStageCallback(void)
{
	//将原先的开始游戏界面去掉，直接进入下一关
	moveOutGameLayerAction();
	CommonData::m_pageViewNum = (CandyManager::currentLevel - 1)/15;		//返回PAGEVIEW的页面
	CCScene *pScene = PlayGame::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CandyResultLayer::discountGoodsCallback(void)
{
	moveOutGameLayerAction();
	showWidget(RESULT_WIDGE_DISCOUNTGOODS, true);
}

void CandyResultLayer::playAgainCallback(void)
{
	gameWinNextCallBack(NULL);
}

void CandyResultLayer::playNextCallback(void)
{
#if defined (DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
	if(AnalyseJson::logOnMsg.lifeInfo.lifeNum > 0)
#else
	if(CommonData::consumeGameLife())
#endif
	{
		CCScene *pScene = PlayGame::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
	else
	{
		showWidget(RESULT_WIDGE_NO_LIFE, true);
	}
}

void CandyResultLayer::showNoLifeTips(void)
{
	showWidget(RESULT_WIDGE_NO_LIFE, true);
}

CCActionInterval* CandyResultLayer::getMoveAction(bool inFlag, float time, CCPoint pos)
{
#if 1
	return CCEaseElasticInOut::create((CCActionInterval*)CCMoveBy::create(time,pos),1.0f );
#else
	if(inFlag)
		return CCEaseBackOut::create(CCMoveBy::create(time,pos));
	else
		return CCEaseBackIn::create(CCMoveBy::create(time,pos));
#endif

}

void CandyResultLayer::removeYouWin2()
{
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(77);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(89);
}

void CandyResultLayer::gameWinPalyAgainCallback( CCObject* pSender )
{
#ifdef CANDY_STATISITICAL_DATA
	//AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_4008 );
#endif

	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);

	grayLayer->runAction(CCFadeTo::create(0.5f, 0));

	CommonData::setButtonTouchEnable(pSender, false);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	moveOutGameLayerAction();

	Layout* widget  = getGameWinLayout();
	if(widget)
	{
		widget->runAction(CCSequence::create(
			getMoveAction(false,MOVE_SCREEN_TIME, ccp(0,TARGET_SCREEN_HEIGHT)),
			//CCCallFunc::create(this, callfunc_selector(CandyResultLayer::playAgainCallback)), 
			NULL)
			);
	}

	CandyManager::currentLevel--;
	gameWinNextCallBack(NULL);
}

void CandyResultLayer::updateEnterNextLevel( float dt)
{
	static int count  = 0;
	if(count < 0 )
	{
		count++;
	}
	else
	{
		count = 0;
		this->unschedule( schedule_selector(CandyResultLayer::updateEnterNextLevel) );
		if(CommonData::m_isEnterNext == false)
		{
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_WIN);
			CommonData::m_isEnterNext = true;
		}
	}
}

void CandyResultLayer::BuySuperLifePackCallback( CCObject* sender )
{
//	CandyPay::getInstance()->RequestCandyOrder(Super_life);
}

void CandyResultLayer::CancelBuySuperLifeCallback( CCObject* sender )
{
	gameLoseReturnCallBack(sender);
}






CandyResult::CandyResult()
{
	targetMgr = new CandyTarget();
	gamestate = GAME_STATE_SUCCEE;
	currentResult = CANDY_RESULT_SHOW_TARGET;
	resultLayer = NULL;
}

CandyResult::~CandyResult()
{
	CC_SAFE_DELETE(targetMgr);
	CC_SAFE_RELEASE_NULL(resultLayer);
}

void CandyResult::initCandyResult(void)
{
	getCurrentResult();
	setCurrentResult(CANDY_RESULT_SHOW_TARGET);
}

void CandyResult::updateCandyResult(float time)
{
	static int timeCount = 0;

	if(!CandyManager::getInstance()->shareMgr->getCandyIdle())
		timeCount = 0;
	if(timeCount ++ < 3)
		return;

	switch(currentResult)
	{
	case CANDY_RESULT_PLAYING:
		{		

			/*					isRewards = CandyManager::getInstance()->guideLayer->currentStep;	*/
			if(targetMgr->getReachingTarget())
			{
				//CommonData::sendEnergyNum();
				MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
				setCurrentResult(CANDY_RESULT_CLEAR_TIPS);
			}
			else
			{
				LoseTargetType loseTarget = targetMgr->getLosingTarget();
				switch(loseTarget)
				{
				case LOSE_TARGET_NOT_YET:
					break;

				case LOSE_TARGET_EXPLOSION:
					gamestate = GAME_STATE_FAIL;
					CommonData::m_doubleScore = 1;
					//CommonData::sendEnergyNum();
					MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
					CandyManager::explosionBomb = true;
					setCurrentResult(CANDY_RESULT_EXPLOSION_DELAY);
					break;

				case LOSE_TARGET_NO_MOVE:
					gamestate = GAME_STATE_FAIL;
					CommonData::m_doubleScore = 1;
					//CommonData::sendEnergyNum();
					MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
					setCurrentResult(CANDY_RESULT_NO_MOVE_DELAY);
					break;

				case LOSE_TARGET_NO_TIME:
					gamestate = GAME_STATE_FAIL;
					CommonData::m_doubleScore = 1;
					//CommonData::sendEnergyNum();
					MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
					setCurrentResult(CANDY_RESULT_NO_TIME_DELAY);
					break;
				}
			}
		}
		break;

	case CANDY_RESULT_EXPLOSION_DELAY:
		// 				{
		// 					static float countTime = 0;
		// 					timeDelayChangeResult(countTime, time, 3.0f,CANDY_RESULT_EXPLOSION);
		// 				}
		break;

	case CANDY_RESULT_NO_MOVE_DELAY:
		// 				{
		// 					static float countTime = 0;
		// 					timeDelayChangeResult(countTime, time, 3.0f,CANDY_RESULT_NO_MOVE);
		// 				}
		break;
		//此状态下播放"你失败了"
	case CANDY_RESULT_NO_TIME_DELAY:
		{
			static float countTime = 0;
			timeDelayChangeResult(countTime, time, 0.5f,CANDY_RESULT_NO_TIME);//相当于CANDY_RESULT_LOSE
		}
		break;
		//该状态下播放"你失败了"特效
	case CANDY_RESULT_LOST_EFFECT:
		{
			static float countTime = 0;
			timeDelayChangeResult(countTime, time, 1.5f, CANDY_RESULT_LOSE);
		}
		break;
	case CANDY_RESULT_ACTIVE_SPECIAL_DELAY:
		{
			static float countTime = 0;
			timeDelayChangeResult(countTime, time, 3.0f, CANDY_RESULT_ACTIVE_SPECIAL);
		}
		break;

	case CANDY_RESULT_STAGE_DELAY:
		{
			static float countTime = 0;
			CandyResultType ret;

			if(CandyManager::getInstance()->scoreMgr->getCurrentScore() >= CandyScore::starScoreNum[0])
			{
				ret = CANDY_RESULT_STAGE_CLEAR_EFFECT;
				timeDelayChangeResult(countTime, time, 0, ret);
			}
			else
			{
				ret = CANDY_RESULT_STAGE_FAILED;
				timeDelayChangeResult(countTime, time, 1.0f, ret);
			}
		}
		break;	

	case CANDY_RESULT_CLEAR_TIPS:
		{
			static float countTime = 0;
			if(CandyManager::gameMode != CANDY_MODE_TIMING &&  CandyManager::gameMode != CANDY_MODE_NORMAL && CandyMove::moveLimit > 0)
			{
				timeDelayChangeResult(countTime, time, 1.0f, CANDY_RESULT_ACTIVE_SPECIAL_DELAY);
			}
			else
			{
				timeDelayChangeResult(countTime, time, 1.0f, CANDY_RESULT_ACTIVE_SPECIAL);
			}
		}
		break;

	case CANDY_RESULT_ACTIVE_SPECIAL:
		{
			if(CandyManager::gameMode != CANDY_MODE_TIMING  && CandyMove::moveLimit > 0)
			{
				setCurrentResult(CANDY_RESULT_USE_STEPS_DELAY);
			}
			else if(CandyManager::getInstance()->specialMgr->activeSpecialCandyInMap(5))
			{

			}
			else
			{
				setCurrentResult(CANDY_RESULT_STAGE_DELAY);
			}
		}
		break;

	case CANDY_RESULT_USE_STEPS_DELAY:
		{
			static float countTime = 0;
			timeDelayChangeResult(countTime, time, 0.2f,CANDY_RESULT_USE_STEPS);
		}
		break;

	case CANDY_RESULT_USE_STEPS:
		{
			if(CandyMove::moveLimit > 0)
			{
				CandyMove::moveLimit--;
				CandyCell *candy = CandyCell::getRandomNormalCandy();
				if(candy)
				{
					CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(candy->index);
					candy->changeCandySpecial(rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL, false);
					CandyManager::getInstance()->effectLayer->displayUseStepChangeStripe(candy->index);
					CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_USE_STEPS,  pos, candy->color);
				}
				setCurrentResult(CANDY_RESULT_USE_STEPS_DELAY);
			}
			else
			{
				setCurrentResult(CANDY_RESULT_ACTIVE_SPECIAL);
			}
		}
		break;
		//该状态下播放“你赢了”特效
	case CANDY_RESULT_STAGE_CLEAR_EFFECT:
		{
			static float countTime = 0;
			timeDelayChangeResult(countTime, time, 0.5f, CANDY_REWARDS_PROP);
		}
		break;
	case CANDY_REWARDS_PROP:
		{

		}
		break;
	case CANDY_RESULT_STAGE_CLEAR:
		{

		}
		break;

	case CANDY_RESULT_STAGE_FAILED:
		{
			//稍作延迟
			static int timeCount = 0;
			if(++timeCount % 30)
				return;
			setCurrentResult(CANDY_RESULT_LOSE);
		}
		break;
	case CANDY_FAIL_EXIT_GAME:
	case CANDY_PUSE_EXIT_GAME:
		{
			//稍作延迟
			static int exitTimeCount = 0;
			if(++exitTimeCount % 80)
				return;

			exitTimeCount = 0;
// 			if ( CandyManager::getInstance()->uiLayer )
// 				CandyManager::getInstance()->uiLayer->stopAllActions();
// 
// 			if ( CandyManager::getInstance()->candyLayer )
// 				CandyManager::getInstance()->candyLayer->stopAllActions();

			resultLayer->returnMainMapCallBack();
		}
		break;
	case CANDY_WIN_EXIT_GAME:
		{
			//稍作延迟
			static int winexitTimeCount = 0;
			if(++winexitTimeCount % 90)
				return;

			winexitTimeCount = 0;
			CandyManager::getInstance()->musicMgr->unreloadCandyGameMusic();

			MainMap::EnteyMapScene(GAME_STATE_SUCCEE_NEXT);

		}

	case CANDY_NOLIFE_EXIT_GAME:
		{
			//稍作延迟
			static int exitTimeCount = 0;
			if(++exitTimeCount % 90)
				return;

			exitTimeCount = 0;
			//CandyManager::getInstance()->musicMgr->unreloadCandyGameMusic();

			MainMap::EnteyMapScene(GAME_STATE_FAIL);

		}

	case CANDY_RESULT_USE_PROP:
		{
			//稍作延迟
			static int timeCount = 0;
			if(++timeCount % 20)
				return;

			if(!CommonData::updatePropData())
			{
				if(lastResult == CANDY_RESULT_SHOW_TARGET)
				{
					setCurrentResult(CANDY_RESULT_COUNT_DOWN);
				}
				else
				{
					setCurrentResult(CANDY_RESULT_PLAYING);
				}
			}
		}
		break;

	case CANDY_RESULT_COUNT_DOWN:
		{
			CandyManager::getInstance()->effectLayer->displayCountDown(remainTime);

			if(remainTime = remainTime - time, remainTime<=0)
				setCurrentResult(CANDY_RESULT_PLAYING);


		}
		break;

	case CANDY_BUY_ADD5PROP:
		{
			//static float countTime = 0;
			//timeDelayChangeResult(countTime, time, 5.0f, CANDY_RESULT_LOST_EFFECT);
			//CCLog("CandyResult::updateCandyResult :[%f]",countTime);
		}
		break;
	case CANDY_RESULT_PASS_LEVEL:
		{

		}
		break;



	}
}

void CandyResult::timeDelayChangeResult(float &currentTime, float time, float delayTime, CandyResultType nextRet)
{
	currentTime = currentTime + time;
	if(currentTime > delayTime && currentTime > time)//currentTime > time 防止第一次就nextRet
	{
		currentTime = 0;
		setCurrentResult(nextRet);
	}
}

bool CandyResult::getGameRunning(void)
{
	return currentResult == CANDY_RESULT_PLAYING;
}

void CandyResult::unDisplayTargetTips(void)
{
	targetMgr->targetTipsActionCallback();
}

void CandyResult::setCurrentResult(CandyResultType result)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	lastResult = currentResult;
	currentResult = result;
	float waitTime = 0.0f;

	switch(currentResult)
	{
	case CANDY_RESULT_CLEAR_TIPS:
		{
			CandyManager::getInstance()->correctMapMgr->setDisplayCandyDispelTipsFlag(false);
		}
		break;

	case CANDY_RESULT_ACTIVE_SPECIAL_DELAY:
		{
			CandyManager::getInstance()->effectLayer->displayStageClearTips();
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CANDYCRUSH);
		}
		break;

	case CANDY_RESULT_EXPLOSION_DELAY:
	case CANDY_RESULT_NO_MOVE_DELAY:
		{
			// 前5关如果游戏失败均不显示+5界面直接游戏失败
			if ( 5 >= CandyManager::currentLevel)
				setCurrentResult(CANDY_RESULT_LOST_EFFECT);
			else
			{
				setCurrentResult( CANDY_BUY_ADD5PROP );
			}
		}
		break;
	case CANDY_RESULT_NO_TIME_DELAY:
		{
			// 播放失败特效
// 			CandyManager::getInstance()->effectLayer->displayStageFailedTipsPre();
// 			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_FAILED_TIPS);
		}
		break;
	case CANDY_RESULT_LOSE://GAME_LOSE_LAYOUT_FILE
		{
			getResultLayer()->showWidget(RESULT_WIDGE_GAME_LOSE, true);
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_BG_GAME_OVER);

		}
		break;
		// 			case CANDY_RESULT_EXPLOSION:
		// 			case CANDY_RESULT_NO_MOVE:
	case CANDY_RESULT_NO_TIME:
		{
			CommonData::m_doubleScore = 1;
			//CommonData::sendEnergyNum();
			MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);

			getResultLayer()->showWidget(RESULT_WIDGE_GAME_LOSE, true);
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_BG_GAME_OVER);

			//getResultLayer()->runPropTipsAction();
			//CandyManager::getInstance()->correctMapMgr->setDisplayCandyDispelTipsFlag(false);
		}
		break;		
	case CANDY_PUSE_EXIT_GAME:
		{
			CommonData::m_doubleScore = 1;
			//CommonData::sendEnergyNum();
			MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
			//getResultLayer()->moveOutGameLayerAction();
#if defined (DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
			CommonData::consumeGameLife();
#endif
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_2, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());
		}
		break;
	case CANDY_RESULT_STAGE_FAILED:
		{
			CommonData::m_doubleScore = 1;
			//CommonData::sendEnergyNum();
			MsgMgr::sendGetGameState( AnalyseJson::logOnMsg.baseInfo.id, 0);
			//getResultLayer()->moveOutGameLayerAction();
#if defined (DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
			//CommonData::consumeGameLife();
#endif
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_2, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());
		}
		break;

	case CANDY_RESULT_SHOW_TARGET:
		{
			targetMgr->runTargetTipsAction();
		}
		break;

	case CANDY_RESULT_COUNT_DOWN:	
		{
			if(CandyManager::gameMode != CANDY_MODE_TIMING)
				setCurrentResult(CANDY_RESULT_PLAYING);
			remainTime = 3.0f;	
		}
		break;

	case CANDY_RESULT_NO_DISPEL:
		{
			setCurrentResult(CANDY_RESULT_LOSE);
			//getResultLayer()->showWidget(RESULT_WIDGE_GAME_LOSE);
		}
		break;
	case CANDY_RESULT_STAGE_CLEAR:
		{
			getResultLayer()->runStageClearAction();
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_STAGE_CLEAR);
#ifdef CANDY_STATISITICAL_DATA
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_1, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());
			/*if(CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=10)
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_19, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());*/
#endif
		}
		break;
	case CANDY_RESULT_RESORTRANK:
		{
			CommonData::m_isEnterNext = false;
			if(CommonData::getMaxLevel() >= AnalyseJson::unLockConfig.friendFun)
			{
				waitTime = 1.0f;
				MsgMgr::sendGetSingleLevelResult( AnalyseJson::logOnMsg.baseInfo.id, CandyManager::currentLevel );
			}
			else
			{
				waitTime = 0.5f;
			}
			resultLayer->schedule(schedule_selector(CandyResultLayer::updateEnterNextLevel), waitTime);

			CandyManager::getInstance()->musicMgr->playMusic(CANDY_BG_BGM1);
			if(CandyManager::getInstance()->scoreMgr->getCurrentScore() > CommonData::getLevelScore(CandyManager::currentLevel) )
				CommonData::sendLevelScore( CandyManager::currentLevel, CandyManager::getInstance()->scoreMgr->getCurrentScore() );

			break;
		}
	case CANDY_RESULT_WIN:
		{ 
			CommonData::m_doubleScore = 1;

			if(CandyManager::getInstance()->scoreMgr->getCurrentScore() > CommonData::getLevelScore(CandyManager::currentLevel) )
				CommonData::sendLevelScore( CandyManager::currentLevel, CandyManager::getInstance()->scoreMgr->getCurrentScore() );

			getResultLayer()->showWidget(RESULT_WIDGE_GAME_WIN, true);

			//播放胜利花瓣特效
			CandyParticle::displayCandyParticle(CANDY_PARTICLE_WIN_EFFECT,  ccp(size.width/2 ,size.height),getResultLayer()->getUILayer()->getRootWidget()->getRenderer(),567);

			CandyManager::getInstance()->musicMgr->playMusic(CANDY_BG_GAME_CLEAR);

#ifdef CANDY_STATISITICAL_DATA
			/*if(CommonData::getMaxLevel() <= CandyManager::currentLevel && CandyManager::currentLevel<=10)
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_20, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());*/
#endif
		}
		break;
	case CANDY_RESULT_STAGE_CLEAR_EFFECT:
		{
#ifdef CANDY_STATISITICAL_DATA
			/*if( 0 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_62 );
			else if( 1 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_74 );
			else if( 2 == CommonData::getMaxLevel() )
				AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_88 );*/
#endif
// 			CandyManager::getInstance()->effectLayer->displayStageClearTipsExtraPre();
// 			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CLEAR_TIPS);
		}
		break;

	case CANDY_RESULT_NEXT_STAGE:
		{
			MsgMgr::sendGetSingleLevelResultInMap( AnalyseJson::logOnMsg.baseInfo.id, CandyManager::currentLevel );

			getResultLayer()->showWidget(RESULT_WIDGE_GAME_NEXT, true);
		}
		break;

	case CANDY_RESULT_USE_PROP:
		{

		}
		break;

	case CANDY_RESULT_ROULETTE:
		{
			getResultLayer()->showWidget(RESULT_WIDGE_ROULETTE);
		}
		break;
		//奖励道具

	case CANDY_REWARDS_PROP:
		{

			if (CommonData::getMaxLevel() == 0 && CandyManager::currentLevel == 1) 
			{
				CandyManager::getInstance()->uiLayer->removeYouWinAni();
				addGrayLayer();
				MsgMgr::sendSystemGiveProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_IN_RESORT);
				getResultLayer()->showWidget( RESULT_WIDGE_REWARDS);
				break;
			}
			else if(CommonData::getMaxLevel() == 2 && CandyManager::currentLevel == 3)
			{
				CandyManager::getInstance()->uiLayer->removeYouWinAni();
				addGrayLayer();
				MsgMgr::sendSystemGiveProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_IN_SWAP);
				getResultLayer()->showWidget( RESULT_WIDGE_REWARDS);
				break;
			}
			else if(CommonData::getMaxLevel() == 4 && CandyManager::currentLevel == 5)
			{
				CandyManager::getInstance()->uiLayer->removeYouWinAni();
				addGrayLayer();
				MsgMgr::sendSystemGiveProp( AnalyseJson::logOnMsg.baseInfo.id, CANDY_PROP_IN_HAMMER);
				getResultLayer()->showWidget( RESULT_WIDGE_REWARDS);
				break;
			}

			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_STAGE_CLEAR);
		}
		break;
		// 购买+5道具
	case CANDY_BUY_ADD5PROP:
		{
			//去掉SDK支付后，直接弹出
#ifdef CLEAN_VERSION
			getResultLayer()->showWidget( RESULT_WIDGE_GAME_LOSE );
#else
//  		getResultLayer()->showWidget( RESULT_WIDGE_ADD5PROP );
//  		resultLayer->UpdataAdd5CountDown();
			 
			CommonData::m_BuyAdd5From = 1;	//购买+5在失败界面	

			CandyManager::getInstance()->resultMgr->getResultLayer()->setpropId(CANDY_PROP_IN_STEP5);

			CandyManager::getInstance()->resultMgr->setCurrentResult( CANDY_RESULT_BUYPROPING );

			getResultLayer()->showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)CANDY_PROP_IN_STEP5);
		//	CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_STEP5);

#endif // CLEAN_VERSION

		}
		break;
	case CANDY_RESULT_LOST_EFFECT:
		{
			if ( resultLayer )
			{
				//resultLayer->BuyAdd5DelayCB();
			}
			//播放失败特效
// 			CandyManager::getInstance()->effectLayer->displayStageFailedTipsPre();
// 			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_FAILED_TIPS);
		}
		break;
	case CANDY_RESULT_PASS_LEVEL:
		{
			getResultLayer()->showWidget(RESULT_WIDGE_GAMEPAY,true,(void*)Success_Pass);
			//CandyPay::getInstance()->RequestCandyOrder(Success_Pass);
		}
		break;
	}
}

void CandyResult::addGrayLayer(void)
{
	CCLayerColor* grayLayer = CCLayerColor::create(ccc4(0,0,0,0));
	grayLayer->runAction(CCSequence::create(
		CCFadeTo::create(1.0f,170),
		NULL
		));
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(grayLayer,1,49);
}

CandyResultType CandyResult::getCurrentResult(void)
{
	return currentResult;
}

CandyResultLayer* CandyResult::getResultLayer(void)
{
	if(!resultLayer)
	{
		resultLayer =CandyResultLayer::create();
		resultLayer->retain();

		CandyManager::getInstance()->getCurrentLayer()->addChild(resultLayer, RESULT_LAYER_ORDER);
	}
	return resultLayer;
}

void CandyResult::removeResultLayer(void)
{
	if(resultLayer)
	{
		resultLayer->removeFromParent();
		resultLayer = NULL;
	}
}