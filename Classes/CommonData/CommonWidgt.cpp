#include "CommonWidgt.h"

#include "../Loading/LoadingScene.h"
#include "../MainMap/MainMapScene.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/HeadDownMgr.h"
#include "../CommonData/CommonData.h"
#include "../CppCallJava/CppCallJava.h"
#include "../PlayGame/CandyManager.h"
#include <iterator>
#include "SimpleAudioEngine.h"
#include "CommonMacro.h"
#include "../CandyPay/CandyPay.h"

using namespace CocosDenshion;





#define RESUME_SHENDENG_HOUR	72

#define TOOLS_HELP_IMGN	 			"tools/helpbutN.png"
#define TOOLS_HELP_IMGP	 			"tools/helpbutP.png"
#define TOOLS_MUSIC_IMGN	 		"tools/musicbugN.png"
#define TOOLS_MUSIC_IMGP	 		"tools/musicbugP.png"
#define TOOLS_MUSIC_IMGEN	 		"tools/m_img_MsEN.png"
#define TOOLS_MUSIC_IMGEP	 		"tools/m_img_MsEP.png"	
#define TOOLS_VOL_IMGN	 			"tools/volbutN.png"
#define TOOLS_VOL_IMGP	 			"tools/volbutP.png"
#define TOOLS_VOL_IMGEN	 			"tools/m_img_volEN.png"
#define TOOLS_VOL_IMGEP	 			"tools/m_img_volEP.png"

#if defined(DEMO_FOR_MOBILE)|| defined(DEMO_FOR_GUEST)
/****************************************************/
/*Corresponding to china mobile props serial number */
/****************************************************/
static char* mobilePropIdManager[10] = 
{
	(char*)MOBILE_PROP1_ID,
	(char*)MOBILE_PROP2_ID,
	(char*)MOBILE_PROP3_ID,
	(char*)MOBILE_PROP4_ID,
	(char*)MOBILE_PROP5_ID,
	(char*)MOBILE_PROP6_ID,
	(char*)MOBILE_PROP7_ID,
	(char*)MOBILE_PROP8_ID,
	(char*)MOBILE_PROP9_ID,
	(char*)MOBILE_PROP10_ID
};
#endif


#define LEVEL_QUIT_CCCP		(ccp(CCDirector::sharedDirector()->getWinSize().width/2  , CCDirector::sharedDirector()->getWinSize().height + CCDirector::sharedDirector()->getWinSize().height))   // 顶侧退出


/***********************************/
/*CommonWidgt                     */
/***********************************/
UpdataGameWidget* CommonWidgt::Updatalayout = NULL;
SystemTools* CommonWidgt::Systemlayout = NULL;
HelpWidgt* CommonWidgt::Helplayout = NULL;
PropInfoWidget* CommonWidgt::PropWidgetLayout = NULL;
SuccessWidget* CommonWidgt::SuccessWidgetLayout = NULL;
BuyGemWidget* CommonWidgt::BuyGemWidgetLayout = NULL;
SurpassFriend* CommonWidgt::SurpassFriendLayout = NULL;
GameShopWidget* CommonWidgt::m_GameShopLayout = NULL;
GameVipWidget* CommonWidgt::m_GameVipWidget = NULL;
GameGiftWidget* CommonWidgt::m_GameGiftWidget = NULL;
GameUnlockLevelWidget* CommonWidgt::m_GameUnlockLevelWidget = NULL;
GameSignInWidget* CommonWidgt::m_SignInWidget = NULL;
GameRankWidget* CommonWidgt::m_GameRankWidget = NULL;
GameRouletteWidget* CommonWidgt::m_GameRouletteWidget = NULL;
GiftRewardEffWidget* CommonWidgt::m_GiftRewardWidget = NULL;
GameSuperGiftWidget* CommonWidgt::m_SuperGiftWidget = NULL;
GamePayWidget* CommonWidgt::m_GamePayWidget = NULL;

Layout* CommonWidgt::getGamePayWidgetUI( CommonWidgetType type ,int widget_type )
{
	Layout* layout = NULL;;
	if( !m_GamePayWidget )
	{
		m_GamePayWidget = new GamePayWidget();
	}

	layout = m_GamePayWidget->getGamePayLayout(widget_type);
	return layout;
}

Layout* CommonWidgt::getGameRankWidgetUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !m_GameRankWidget )
	{
		m_GameRankWidget = new GameRankWidget();
	}

	layout = m_GameRankWidget->getGameRankLayout(type);
	return layout;
}

Layout* CommonWidgt::getGameUnlockLevelUI( CommonWidgetType type ,int level)
{
	Layout* layout = NULL;;
	if( !m_GameUnlockLevelWidget )
	{
		m_GameUnlockLevelWidget = new GameUnlockLevelWidget();
	}

	layout = m_GameUnlockLevelWidget->getGameUnlockLevelLayout(level);
	return layout;
}

Layout* CommonWidgt::getGameGiftUI( CommonWidgetType type ,int pra)
{
	Layout* layout = NULL;;
	if( !m_GameGiftWidget )
	{
		m_GameGiftWidget = new GameGiftWidget();
	}

	layout = m_GameGiftWidget->getGameGiftLayout(pra);
	return layout;
}

Layout* CommonWidgt::getGameVipUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !m_GameVipWidget )
	{
		m_GameVipWidget = new GameVipWidget();
	}

	layout = m_GameVipWidget->getGameVipLayout();
	return layout;
}

Layout* CommonWidgt::getGameShopUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !m_GameShopLayout )
	{
		m_GameShopLayout = new GameShopWidget();
	}
	m_GameShopLayout->type = type;
	layout = m_GameShopLayout->getGameShopLayout();
	return layout;
}
Layout* CommonWidgt::getUpdataGameUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !Updatalayout )
	{
		Updatalayout = new UpdataGameWidget();
	}

	Updatalayout->getUpdataGameLayout();
	layout = Updatalayout->UpdataGameLayout;
	return layout;
}


Layout* CommonWidgt::getSurpassFriendUI()
{
	Layout* layout = NULL;;
	if( !SurpassFriendLayout )
	{
		SurpassFriendLayout = new SurpassFriend();
	}

	SurpassFriendLayout->getSurpassFriendLayout();
	layout = SurpassFriendLayout->SurpassFriendLayout;
	return layout;
}

Layout* CommonWidgt::getSystemToolsUI(CommonWidgetType type)
{
	Layout* layout = NULL;;
	if( !Systemlayout )
	{
		Systemlayout = new SystemTools();
		Systemlayout->autorelease();
		Systemlayout->retain();
	}

	Systemlayout->type = type;
	Systemlayout->getSystemToolsLayout();
	layout = Systemlayout->SystemtoolsLayout;
	return layout;
}

Layout* CommonWidgt::getHelpUI(CommonWidgetType type)
{
	if ( !Helplayout )
	{
		Helplayout = new HelpWidgt();
		Helplayout->autorelease();
		Helplayout->retain();
	}
	Helplayout->type = type;
	return Helplayout->getHelpLayout();
}

Layout* CommonWidgt::getPropInfoUI(CommonWidgetType type, int propid )
{
	if ( !PropWidgetLayout )
	{
		PropWidgetLayout = new PropInfoWidget();
		PropWidgetLayout->autorelease();
		PropWidgetLayout->retain();
		
	}
	PropWidgetLayout->type = type;
	PropWidgetLayout->propid = propid;
	return PropWidgetLayout->getPropInfoLayout();
}

Layout* CommonWidgt::getSuccessUI( CommonWidgetType type ,int sucType, int data)
{
	if ( !SuccessWidgetLayout )
	{
		SuccessWidgetLayout = new SuccessWidget();
		SuccessWidgetLayout->autorelease();
		SuccessWidgetLayout->retain();
	}
	SuccessWidgetLayout->type = type;
	SuccessWidgetLayout->sucType = sucType;
	SuccessWidgetLayout->data = data;
	return SuccessWidgetLayout->getSuccessLayout();
}

Layout* CommonWidgt::getBuyGemUI(CommonWidgetType type)
{
	if ( !BuyGemWidgetLayout )
	{
		BuyGemWidgetLayout = new BuyGemWidget();
		BuyGemWidgetLayout->autorelease();
		BuyGemWidgetLayout->retain();
	}
	BuyGemWidgetLayout->type = type;
	return BuyGemWidgetLayout->getBuyGemLayer();
}

Layout* CommonWidgt::getSignInUI( void )
{
	if ( !m_SignInWidget )
	{
		m_SignInWidget = new GameSignInWidget();
		m_SignInWidget->autorelease();
		m_SignInWidget->retain();
	}
	return m_SignInWidget->getSignInLayout();
}

void CommonWidgt::releaseWidgt(void)
{
	if ( Systemlayout )
	{
		Systemlayout->releaseSystemToolsLayout();
		CC_SAFE_RELEASE_NULL( Systemlayout );
		Systemlayout = NULL;
	}


	if ( Helplayout )
	{
		Helplayout->releaseHelpLayout();
		CC_SAFE_RELEASE_NULL( Helplayout );
		Helplayout = NULL;
	}

	if ( PropWidgetLayout )
	{
		PropWidgetLayout->releasePropInfoLayout();
		CC_SAFE_RELEASE_NULL( PropWidgetLayout );
		PropWidgetLayout = NULL;
	}

	if ( BuyGemWidgetLayout )
	{
		BuyGemWidgetLayout->releaseGemLayout();
		CC_SAFE_RELEASE_NULL( BuyGemWidgetLayout );
		BuyGemWidgetLayout = NULL;
	}

	if ( SuccessWidgetLayout )
	{
		SuccessWidgetLayout->releaseSuccessLayout();
		CC_SAFE_RELEASE_NULL( SuccessWidgetLayout );
		SuccessWidgetLayout = NULL;
	}
	if ( SurpassFriendLayout )
	{
		CC_SAFE_RELEASE_NULL( SurpassFriendLayout );
	}
	if ( m_GameShopLayout )
	{
		CC_SAFE_RELEASE_NULL( m_GameShopLayout );
	}
	if ( m_GameVipWidget )
	{
		CC_SAFE_RELEASE_NULL( m_GameVipWidget );
	}
	if ( m_GameUnlockLevelWidget )
	{
		CC_SAFE_RELEASE_NULL( m_GameUnlockLevelWidget );
	}
	if ( m_GameGiftWidget )
	{
		CC_SAFE_RELEASE_NULL( m_GameGiftWidget );
	}
	if ( m_GameRankWidget )
	{
		CC_SAFE_RELEASE_NULL( m_GameRankWidget );
	}
	if ( Updatalayout )
	{
		Updatalayout->releaseLayout();
		CC_SAFE_RELEASE_NULL( Updatalayout );
	}

	if ( m_SignInWidget )
	{
		CC_SAFE_RELEASE_NULL( m_SignInWidget );
	}
	if ( m_SignInWidget )
	{
		CC_SAFE_RELEASE_NULL( m_SignInWidget );
	}
	if ( m_GamePayWidget )
	{
		CC_SAFE_RELEASE_NULL( m_GamePayWidget );
	}
//	AnalyseJson::cleanData();
//	HeadDownMgr::Destroy();
//	CCHttpClient::getInstance()->destroyInstance();
}

Layout* CommonWidgt::getGameRouletteWidgetUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !m_GameRouletteWidget )
	{
		m_GameRouletteWidget = new GameRouletteWidget();
	}

	layout = m_GameRouletteWidget->getGameRouletteLayout(type);
	return layout;
}

Layout* CommonWidgt::getGiftRewardUI( CommonWidgetType type, int ui_type,int data )
{
	if ( !m_GiftRewardWidget )
	{
		m_GiftRewardWidget = new GiftRewardEffWidget();
		m_GiftRewardWidget->autorelease();
		m_GiftRewardWidget->retain();
	}
	m_GiftRewardWidget->type = type;
	if(ui_type == MAP_WIDGET_SIGNIN)
	{
		m_GiftRewardWidget->m_CurrentDay = data;
	}
	else if(ui_type == MAP_WIDGET_ROULETTE_DLG)
	{
		m_GiftRewardWidget->m_RouletteReward = data;
	}
	return m_GiftRewardWidget->getGiftEffectLayout(ui_type);
}

Layout* CommonWidgt::getGameSuperGiftUI( CommonWidgetType type )
{
	Layout* layout = NULL;;
	if( !m_SuperGiftWidget )
	{
		m_SuperGiftWidget = new GameSuperGiftWidget();
	}

	layout = m_SuperGiftWidget->getGameSuperGiftLayout();

	return layout;
}




/***********************************/
/*CommonWidgt                     */
/***********************************/
#define BUYGEM_LAYOUT_JSONFILE				"Image/MainMapUi/Tools/BuyGameGemUi.ExportJson"
#define SYSTEMTOOL_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/SystemTools.ExportJson"
#define HELP_LAYOUT_JSONFILE				"Image/MainMapUi/Tools/HelpUi.ExportJson"
#define PROPINFO_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/PropInfoUi.ExportJson"
#define SUCCESSUI_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/SucceedUi.ExportJson"
#define SURPASSFRIEND_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/SurpassFriendUi.ExportJson"
#define UPDATAGAME_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/UpdataGameUI.ExportJson"
#define CANDYSHOP_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/CandyShopUI.ExportJson"
#define CANDYSHOPBUY_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/CandyShopBuy.ExportJson"
#define CANDYVIP_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/CandyVipUI.ExportJson"
#define CANDYGIFT_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/CandyGiftUI.ExportJson"
#define SIGNIN_LAYOUT_JSONFILE				"Image/MainMapUi/Tools/SignInUI.ExportJson"
#define UNLOCKLEVEL_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/CandyLockLevelUI.ExportJson"
#define CANDYWORLDRANK_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/CandyWorldRankUI.ExportJson"
#define GIFTREWARD_LAYOUT_JSONFILE			"Image/MainMapUi/Tools/RewardEffUI.ExportJson"
#define CANDYWROULETTE_LAYOUT_JSONFILE		"Image/MainMapUi/Tools/CandyRoulette.ExportJson"
#define CANDYPAY_LAYOUT_JSONFILE			"Image/CandyPay/CandyPay_Canvas.ExportJson"
#define SUPERGIFT_LAYOUT_JSONFILE			"Image/CandyGame/CandyGameUi/SuperGigtUI.ExportJson"

SystemTools::SystemTools():
SystemtoolsLayout(NULL)
{
}


Layout* SystemTools::getSystemToolsLayout(void)
{
	if ( !SystemtoolsLayout )
	{
		SystemtoolsLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(SYSTEMTOOL_LAYOUT_JSONFILE));
		SystemtoolsLayout->retain();
		//SystemtoolsLayout->setZOrder( 2 );
	}
	SystemtoolsLayout->setTouchEnabled( true );
	SystemtoolsLayout->setVisible(true);

	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));
	pImgDlg->setScale( 1.0f );	

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(SystemTools::CloseCallBack));

	UIPanel *pPanelForMap = dynamic_cast<UIPanel*>(SystemtoolsLayout->getChildByName("PanelForMap"));
	UIPanel *pPanelForGame = dynamic_cast<UIPanel*>(SystemtoolsLayout->getChildByName("PanelForGame"));
	pPanelForMap->setVisible(true);
	pPanelForGame->setVisible(true);


	//UIButton *pHelpForMapButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("Btngamehelp"));
	UIButton *pContinueGame = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("ContinueGame"));
	UIButton *pExitGameButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("Btnexitgame"));
	//UIButton *pNoticeButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("BtnNotice"));
	//UIButton *pFeedbackButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("Btnfeedback"));


	//UIButton *pHelpForGameButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("BtnGamehelp1"));
	UIButton *pQuitGameButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("BtnQuitGame"));
	UIButton *pContiuneGameButton = dynamic_cast<UIButton*>(SystemtoolsLayout->getChildByName("BtnContiuneGame"));

	//pHelpForMapButton->setTag( TOOLS_ITEM_HELPFORMAP );
	//pHelpForMapButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	pContinueGame->setTag( TOOLS_CONTINUE_GAME );
	pContinueGame->addReleaseEvent(this, coco_releaseselector(SystemTools::CloseCallBack));

	pExitGameButton->setTag( TOOLS_TILE_EXITGAME );
	pExitGameButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	//pNoticeButton->setTag( TOOLS_TILE_NOTICE );
	//pNoticeButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	//pFeedbackButton->setTag( TOOLS_TIEL_FEEDBACK );
	//pFeedbackButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	//pHelpForGameButton->setTag( TOOLS_ITEM_HELPFORGAME );
	//pHelpForGameButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	pQuitGameButton->setTag( TOOLS_TILE_QUITGAME );
	pQuitGameButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));

	pContiuneGameButton->setTag( TOOLS_TIEM_CONTOUNE );
	pContiuneGameButton->addReleaseEvent(this, coco_releaseselector(SystemTools::toolsmenuitemCallBack));


	if(type == WIDGET_TYPE_GAME)
	{
		//pHelpForMapButton->setTouchEnabled( false );
		pContinueGame->setTouchEnabled( false );
		pExitGameButton->setTouchEnabled( false );
		//pNoticeButton->setTouchEnabled( false );
		//pFeedbackButton->setTouchEnabled( false );
		//pHelpForGameButton->setTouchEnabled( true );
		pQuitGameButton->setTouchEnabled( true );
		pContiuneGameButton->setTouchEnabled( true );

		//pHelpForMapButton->setVisible( false );
		pContinueGame->setVisible( false );
		pExitGameButton->setVisible( false );
		//pNoticeButton->setVisible( false );
		//pFeedbackButton->setVisible( false );

		//pHelpForGameButton->setVisible( true );
		pQuitGameButton->setVisible( true );
		pContiuneGameButton->setVisible( true );

		//pHelpForGameButton->isEffects( true, nDelayTime1+nDelayTime2*2 );
		pQuitGameButton->isEffects( true, nDelayTime1+nDelayTime2*3 );
		pContiuneGameButton->isEffects( true, nDelayTime1+nDelayTime2*4 );

	}
	else if (type ==  WIDGET_TYPE_MAP)
	{
		//pHelpForMapButton->setTouchEnabled( true );
		pContinueGame->setTouchEnabled( true );
		pExitGameButton->setTouchEnabled( true );
		//pNoticeButton->setTouchEnabled( true );
		//pFeedbackButton->setTouchEnabled( true );
		//pHelpForGameButton->setTouchEnabled( false );
		pQuitGameButton->setTouchEnabled( false );
		pContiuneGameButton->setTouchEnabled( false );

		//pHelpForMapButton->setVisible( true );
		pContinueGame->setVisible( true );
		pExitGameButton->setVisible( true );
		//pNoticeButton->setVisible( true );
		//pFeedbackButton->setVisible(true );
		//pHelpForGameButton->setVisible( false );
		pQuitGameButton->setVisible( false );
		pContiuneGameButton->setVisible( false );

#if !defined( CANDY_VERSIONS_FOR_SINGLE )
		//pContinueGame->isEffects( true, nDelayTime1+nDelayTime2*2 );
		//pNoticeButton->isEffects( true, nDelayTime1+nDelayTime2*2 );
		//pFeedbackButton->isEffects( true, nDelayTime1+nDelayTime2*3 );
#endif
		pContinueGame->isEffects( true, nDelayTime1+nDelayTime2*3 );
		//pHelpForMapButton->isEffects( true, nDelayTime1+nDelayTime2*3 );
		pExitGameButton->isEffects( true, nDelayTime1+nDelayTime2*4 );
	}


	UIImageView* pSoundOpen = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName("soundeffopen"));
	UIImageView* pSoundClose = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName("soundeffclose"));
	UIImageView* pMusicOpen = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName("muiseopen"));
	UIImageView* pMusicClose = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName("muiseclose"));

	if ( CommonData::getSoundEffectState() )
	{
		pSoundClose->setVisible(false);
		pSoundClose->setTouchEnabled(false);
		pSoundOpen->setVisible(true);
		pSoundOpen->setTouchEnabled(true);
	}
	else
	{
		pSoundClose->setVisible(true);
		pSoundClose->setTouchEnabled(true);
		pSoundOpen->setVisible(false);
		pSoundOpen->setTouchEnabled(false);
	}

	if ( SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() )
	{
		pMusicClose->setVisible(false);
		pMusicClose->setTouchEnabled(false);
		pMusicOpen->setVisible(true);
		pMusicOpen->setTouchEnabled(true);
	}
	else
	{
		pMusicClose->setVisible(true);
		pMusicClose->setTouchEnabled(true);
		pMusicOpen->setVisible(false);
		pMusicOpen->setTouchEnabled(false);
	}

	pSoundOpen->setTag(TOOLS_ITEM_SOUNDOPEN);
	pSoundClose->setTag(TOOLS_ITEM_SOUNDCLOSE);
	pMusicOpen->setTag(TOOLS_ITEM_MUSICOPEN);
	pMusicClose->setTag(TOOLS_ITEM_MUSICCLOSE);

	pSoundOpen->addReleaseEvent(this, coco_releaseselector(SystemTools::MusicBtnCallBack));
	pSoundClose->addReleaseEvent(this, coco_releaseselector(SystemTools::MusicBtnCallBack));
	pMusicOpen->addReleaseEvent(this, coco_releaseselector(SystemTools::MusicBtnCallBack));
	pMusicClose->addReleaseEvent(this, coco_releaseselector(SystemTools::MusicBtnCallBack));

#if defined( CANDY_VERSIONS_FOR_SINGLE ) 
	pContinueGame->setVisible( false );
	pNoticeButton->setVisible( false );
	//pFeedbackButton->setVisible( false );

	pContinueGame->setTouchEnabled( false );
	pNoticeButton->setTouchEnabled( false );
	//pFeedbackButton->setTouchEnabled( false );
#endif


	return SystemtoolsLayout;	
}

void SystemTools::releaseSystemToolsLayout(void)
{
	//SystemtoolsLayout->removeAllChildrenAndCleanUp(true);
	CC_SAFE_RELEASE_NULL(SystemtoolsLayout);
}

void SystemTools::MusicBtnCallBack(CCObject *pSender)
{
	UIImageView* pItemBut = (UIImageView*)pSender;
	int index = pItemBut->getTag();


	switch( index )
	{

	case TOOLS_ITEM_MUSICOPEN:
		{
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_MUSICCLOSE)->setVisible(true);
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_MUSICCLOSE)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);

			if ( WIDGET_TYPE_MAP == type )
			{
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			}
			else if (WIDGET_TYPE_GAME == type )
			{
				SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				//CandyManager::getInstance()->musicMgr->playBgm();
			}
			CommonData::setBackgroundState( false );
		}
		break;
	case TOOLS_ITEM_MUSICCLOSE:
		{
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_MUSICOPEN)->setVisible(true);
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_MUSICOPEN)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);

			if ( WIDGET_TYPE_MAP == type )
			{
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_BUTTON_BGMUSIC, true);
			}
			else if (WIDGET_TYPE_GAME == type )
			{
				CandyManager::getInstance()->musicMgr->playBgm();
			}
			CommonData::setBackgroundState( true );
		}
		break;
	case TOOLS_ITEM_SOUNDOPEN:
		{
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_SOUNDCLOSE)->setVisible(true);
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_SOUNDCLOSE)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);

			CommonData::setSoundEffectState( false );
		}
		break;
	case TOOLS_ITEM_SOUNDCLOSE:
		{
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_SOUNDOPEN)->setVisible(true);
			pItemBut->getParent()->getChildByTag(TOOLS_ITEM_SOUNDOPEN)->setTouchEnabled(true);
			pItemBut->setVisible(false);
			pItemBut->setTouchEnabled(false);

			CommonData::setSoundEffectState( true );
		}
		break;
	}
}

void SystemTools::toolsmenuitemCallBack(CCObject *pSender)
{
	UIButton* pItemBut = (UIButton*)pSender;
	int index = pItemBut->getTag();

	std::list<UserPropInfoStr>::iterator p;
	p = AnalyseJson::logOnMsg.propInfo.begin();

	if ( WIDGET_TYPE_MAP == type )
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
	}
	else if (WIDGET_TYPE_GAME == type )
	{
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	}

	switch( index )
	{
		//　继续游戏
	case TOOLS_TIEM_CONTOUNE:
		{
			CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);

			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));

			CCActionInterval* move = NULL;
			CCActionInterval* move_ease_inout2 = NULL;

			move = CCMoveTo::create(0.7f, LEVEL_QUIT_CCCP);
			move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );

			pImgDlg->runAction(CCSequence::create(
				move_ease_inout2,
				CCCallFunc::create(this, callfunc_selector(SystemTools::SystemtoolsClose)),
				NULL)
				);
		}
		break;

		//　反馈
	case TOOLS_TIEL_FEEDBACK:
		{
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_42, "");
#endif
			MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_FEEDBACK_DLG);
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetDirect();
		}
		break;

		//　公告
	case TOOLS_TILE_NOTICE:
		{
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_43, "");
#endif
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_NOTICE_DLG );
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetDirect();
		}
		break;

		//　离开关卡
	case TOOLS_TILE_QUITGAME:
		{
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

			UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));

			CCActionInterval* move = NULL;
			CCActionInterval* move_ease_inout2 = NULL;

			move = CCMoveTo::create(0.7f, LEVEL_QUIT_CCCP);
			move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );

			pImgDlg->runAction(CCSequence::create(
				move_ease_inout2,
				CCCallFunc::create(this, callfunc_selector(SystemTools::funCallGameQuit)),
				NULL)
				);

#ifdef CANDY_STATISITICAL_DATA
			CommonData::sendActiveExitGameStatistics();
#endif
		}
		break;

		//　退出游戏
	case TOOLS_TILE_EXITGAME:
		{
#ifdef CANDY_STATISITICAL_DATA
			CommonData::sendExitStatistics();
#endif

			CommonData::m_isBuyExitGift = 1;// 退出游戏时不弹礼包 dianxin

			if(CommonData::m_isBuyExitGift == 0)
			{
				//CandyPay::getInstance()->RequestCandyOrder(Exit_Gift);
				MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PAY_DLG,Exit_Gift);
			}
			else{
				HeadDownMgr::Destroy();
				CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
				CCTextureCache::sharedTextureCache()->removeUnusedTextures();

				CCArmatureDataManager::purge();
				CCSSceneReader::sharedSceneReader()->purgeSceneReader();
				cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
				cocos2d::extension::UIHelper::instance()->purgeUIHelper();
				CCHttpClient::getInstance()->destroyInstance();

				CCDirector::sharedDirector()->end();
				//CppCallJava::gameExit();
				 
			}

		}
		break;

		//　更改资料
	case TOOLS_ITEM_CHANGEINFO:
		{
			if ( WIDGET_TYPE_MAP == type )
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_CHANGEINFO_DLG );
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetDirect();
			}
			else if (WIDGET_TYPE_GAME == type )
			{
				CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );
				CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);

				UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));

				CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
				CCActionInterval * fadeout = CCFadeOut::create(0.2f);
				CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
				CCFiniteTimeAction * spawn =CCSpawn::create(fadeout,pScale1,NULL);
				pImgDlg->runAction(CCSequence::create(
					pScale,
					spawn,
					CCCallFunc::create(this, callfunc_selector(SystemTools::SystemtoolsClose)),
					NULL)
					);


			}
		}
		break;

		//　游戏帮助
	case TOOLS_ITEM_HELPFORGAME:
	case TOOLS_ITEM_HELPFORMAP:
		{
			//AnalyseJson::setRecordingMsg(WIDGET_TYPE_MAP == type?RECODING_MSG_ACTIONID_44:RECODING_MSG_ACTIONID_45);
			CommonWidgt::Systemlayout->SystemtoolsLayout->setPosition( LEVEL_QUIT_CCCP );
			if ( WIDGET_TYPE_MAP == type )
			{
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_HELP_DLG );
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetDirect();
			}
			else if (WIDGET_TYPE_GAME == type )
			{
				CandyManager::getInstance()->uiLayer->showGameWidget(CANDY_GAME_GUIDE);
			}
		}
		break;

	case TOOLS_ITEM_CHANGEUSER:
		// 注销
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if ( WIDGET_TYPE_MAP == type )
		{
 			MainMapUiLayer::m_mainmapuilayer->m_messagelist.clear();
 
 			AnalyseJson::cleanData();
 			HeadDownMgr::Destroy();
 			CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
 			CCTextureCache::sharedTextureCache()->removeUnusedTextures();
 
 			CCArmatureDataManager::purge();
 			CCSSceneReader::sharedSceneReader()->purgeSceneReader();
 			cocos2d::extension::ActionManager::shareManager()->purgeActionManager();//  :UIActionManager::shareManager()->purgeUIActionManager();
 			cocos2d::extension::UIHelper::instance()->purgeUIHelper();

			//CppCallJava::gameExit();
		}
#endif
		break;

	case  TOOLS_ITEM_VOL:
		if ( SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() )
		{
			pItemBut->setTextures( TOOLS_VOL_IMGEN, TOOLS_VOL_IMGEP, TOOLS_VOL_IMGEP,UI_TEX_TYPE_PLIST);
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CommonData::setBackgroundState( false );
		}
		else
		{
			pItemBut->setTextures( TOOLS_VOL_IMGN, TOOLS_VOL_IMGP, TOOLS_VOL_IMGP,UI_TEX_TYPE_PLIST);

			if ( WIDGET_TYPE_MAP == type )
			{
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_BUTTON_BGMUSIC, true);
			}
			else if (WIDGET_TYPE_GAME == type )
			{
				CandyManager::getInstance()->musicMgr->playBgm();
			}
			CommonData::setBackgroundState( true );
		}
		break;

	case TOOLS_ITEM_MUSIC:
		if ( CommonData::getSoundEffectState() )
		{
			pItemBut->setTextures( TOOLS_MUSIC_IMGEN, TOOLS_MUSIC_IMGEP, TOOLS_MUSIC_IMGEP,UI_TEX_TYPE_PLIST);
			CommonData::setSoundEffectState( false );
		}
		else
		{
			pItemBut->setTextures( TOOLS_MUSIC_IMGN, TOOLS_MUSIC_IMGP, TOOLS_MUSIC_IMGP,UI_TEX_TYPE_PLIST);
			CommonData::setSoundEffectState( true );
		}
		break;

		//　will funtion remove;
	case TOOLS_ITEM_LOGOUT:
		{
			if ( WIDGET_TYPE_MAP == type )
			{
#ifdef CANDY_STATISITICAL_DATA
				CommonData::sendExitStatistics();
#endif
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
			else if ( WIDGET_TYPE_GAME == type )
			{
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);

				UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));

				CCActionInterval* move = NULL;
				CCActionInterval* move_ease_inout2 = NULL;

				move = CCMoveTo::create(0.7f, LEVEL_QUIT_CCCP);
				move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );

				pImgDlg->runAction(CCSequence::create(
					move_ease_inout2,
					CCCallFunc::create(this, callfunc_selector(SystemTools::funCallGameQuit)),
					NULL)
					);

#ifdef CANDY_STATISITICAL_DATA
				CommonData::sendActiveExitGameStatistics();
#endif
			}

		}
		break;
	}
}

void SystemTools::CloseCallBackEx()
{
	return;
	UIImageView* pImgDlg = dynamic_cast<UIImageView*>(CommonWidgt::Systemlayout->SystemtoolsLayout->getChildByName( "m_img_dlg" ));

	CCActionInterval* pScale = CCScaleTo::create(0.13f, 1.08f, 1.08f);
	CCActionInterval* pScale1 = CCScaleTo::create(0.2f, 0.1f, 0.1f);
	pImgDlg->runAction(CCSequence::create(
		pScale,
		pScale1,
		CCCallFunc::create(CommonWidgt::Systemlayout->SystemtoolsLayout, callfunc_selector(SystemTools::SystemtoolsClose)),
		NULL)
		);
}

void SystemTools::CloseCallBack(CCObject *pSender) 
{
	if ( WIDGET_TYPE_MAP == type )
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
	else if ( WIDGET_TYPE_GAME == type )
	{
		CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);

		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(SystemtoolsLayout->getChildByName( "m_img_dlg" ));

		CCActionInterval* move = NULL;
		CCActionInterval* move_ease_inout2 = NULL;

		move = CCMoveTo::create(0.7f, LEVEL_QUIT_CCCP);
		move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move,0.9f );

		pImgDlg->runAction(CCSequence::create(
			move_ease_inout2,
			CCCallFunc::create(this, callfunc_selector(SystemTools::SystemtoolsClose)),
			NULL)
			);
	}
}

void SystemTools::funCallGameQuit()
{
	if (WIDGET_TYPE_GAME == type )
	{
		CommonWidgt::releaseWidgt();

		CandyManager::getInstance()->resultMgr->getResultLayer()->moveOutGameLayerAction();
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_PUSE_EXIT_GAME);
	}
}

void SystemTools::SystemtoolsClose()
{
	CommonWidgt::Systemlayout->SystemtoolsLayout->setTouchEnabled( false );
 	CommonWidgt::Systemlayout->SystemtoolsLayout->setVisible(false);

	if (WIDGET_TYPE_MAP == type)
	{		
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
		MainMapUiLayer::m_mainmapuilayer->m_isKey = false;

		MainMap::m_mainmap->DisplayMapUi();
	}

}


/***********************************/
/*buy gem widget                     */
/***********************************/
BuyGemWidget::BuyGemWidget():
BuyGemLayout(NULL)
{
}

Layout* BuyGemWidget::getBuyGemLayer()
{
	if ( !BuyGemLayout )
	{
		BuyGemLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(BUYGEM_LAYOUT_JSONFILE));
		BuyGemLayout->retain();
		BuyGemLayout->setZOrder( 2 );
		BuyGemLayout->setTouchEnable(true);
	}
	BuyGemLayout->setVisible(true);
	BuyGemLayout->setTouchEnable(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(BuyGemLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( BTN_TAG_CLOSE );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(BuyGemWidget::ButtonCallBack));

	addGemItemtoList();

	return BuyGemLayout;
}


void BuyGemWidget::addGemItemtoList(void)
{
	CCFileUtils *sharedFileUtils = CCFileUtils::sharedFileUtils();
	UIScrollView* plistView = dynamic_cast<UIScrollView*>(BuyGemLayout->getChildByName( "m_sv_gemlist" ));
	CCSize scrollSize = plistView->getContentSize();
	plistView->removeAllChildrenAndCleanUp(true);
	int nFriendLen = AnalyseJson::logOnMsg.preciousConfig.size();
	CCSize itemPoint;
	// 计算出scrollView的高
	float ClipWidth; 
	float ClipHeight;
	int sex = 0;

	ClipWidth = scrollSize.width;
	ClipHeight = nFriendLen * ( 126 + 10 );
	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;
	plistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	plistView->setTouchEnable( true );
	itemPoint.width = scrollSize.width/2;
	float butMPointY = ClipHeight - 126/2;

	float nDelayTime1 = 0.48f ;//+ 0.08f;
	float nDelayTime2 = 0.082f;

	std::list<PreciousInfoStr>::iterator p = AnalyseJson::logOnMsg.preciousConfig.begin();
	for(int i=0; i< (int)AnalyseJson::logOnMsg.preciousConfig.size(); i++,p++)
	{
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setScale9Enabled( true );
		pItemImg->setScale9Size( CCSizeMake(560, 120));
		pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
		pItemImg->setVisible( true );
		pItemImg->setPosition(ccp(itemPoint.width, butMPointY));
		butMPointY -= ( 126 + 10 );
		plistView->addChild( pItemImg );

		UIImageView* pLifePICImg = UIImageView::create();
		const char* headPath =  CCString::createWithFormat("Image/MainMapUi/gemico%d.png", p->preciousnum)->getCString() ;
		if ( sharedFileUtils->isFileExist(headPath) )
			pLifePICImg->setTexture( headPath  );
		else
			pLifePICImg->setTexture( "Image/MainMapUi/gemico50.png"  );
		pLifePICImg->setVisible( true );
		pLifePICImg->setPosition(ccp(-180, 0));
		pLifePICImg->setTag( i );
		pItemImg->addChild( pLifePICImg);

		// ＝＝＝〉*
		UIImageView* psign1 = UIImageView::create();
		psign1->setTexture( "Image/MainMapUi/m_img_sign1.png" );
		psign1->setVisible( true );
		psign1->setPosition(ccp(-95, 0));
		pItemImg->addChild( psign1 );

		UILabelAtlas* AtlevelNum1 = UILabelAtlas::create();
		char *strLevelNum= (char *)CCString::createWithFormat("%d",  p->preciousnum)->getCString();
		AtlevelNum1->setVisible( true );
		AtlevelNum1->setScale( 0.7f );
		AtlevelNum1->setProperty(strLevelNum , "Image/MainMapUi/m_img_num2.png",42, 51, "0");  
		AtlevelNum1->setPosition( ccp(-35, 0));
		pItemImg->addChild( AtlevelNum1 );

		UIButton* pBuyBut = UIButton::create();
		pBuyBut->setNormalTexture( "Image/MainMapUi/m_but_buylifeN.png" );
		pBuyBut->setPressedTexture( "Image/MainMapUi/m_but_buylifeP.png" );
		pBuyBut->setDisabledTexture( "Image/MainMapUi/m_but_buylifeP.png" );
		pBuyBut->data = (void*)p->preciousid;
		pBuyBut->setTag( i );
		pBuyBut->setTouchEnabled( true );
		pBuyBut->setVisible( true );
		pBuyBut->isEffects( true, nDelayTime1+nDelayTime2*i );
		pBuyBut->setPosition(ccp(155, 0));
		pBuyBut->setTag( BTN_TAG_BUYGEM );
		pBuyBut->addReleaseEvent(this, coco_releaseselector(BuyGemWidget::ButtonCallBack));
		pItemImg->addChild( pBuyBut );

		UILabelAtlas* PriceNum1 = UILabelAtlas::create();
		char *strNum= (char *)CCString::createWithFormat("%d",  atoi(p->preciousprice.c_str()))->getCString();
		PriceNum1->setVisible( true );
		PriceNum1->setProperty(strNum , "Image/MainMapUi/buyItem/gem_price_str.png",29, 40, "0");  
		PriceNum1->setPosition( ccp(-25, 0));
		pBuyBut->addChild( PriceNum1 );

		UIImageView* psign3 = UIImageView::create();
		psign3->setTexture( "Image/MainMapUi/buyItem/gem_price_yuan.png" );
		psign3->setVisible( true );
		psign3->setPosition(ccp(28, 0));
		pBuyBut->addChild( psign3 );

		UIImageView* pbuydivideLine = UIImageView::create();
		pbuydivideLine->setTexture( "Image/MainMapUi/buyItem/buydivideline.png" );
		pbuydivideLine->setVisible( true );
		pbuydivideLine->setPosition(ccp(0, -65));
		pItemImg->addChild( pbuydivideLine );
	}
}

void BuyGemWidget::releaseGemLayout(void)
{
	BuyGemLayout->removeAllChildrenAndCleanUp(true);
	CC_SAFE_RELEASE_NULL(BuyGemLayout);
}


void BuyGemWidget::ButtonCallBack(CCObject *pSender)
{
	UIButton* pBtn = (UIButton*)pSender;
	int index = pBtn->getTag();

	MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);

	if(BTN_TAG_BUYGEM == index)
	{
		if (AnalyseJson::logOnMsg.preciousConfig.empty())
			return;

		int itemid = 0;
		itemid = (int)pBtn->data;

		std::list<PreciousInfoStr>::iterator p = AnalyseJson::logOnMsg.preciousConfig.begin();
		for(int i=0; i< (int)AnalyseJson::logOnMsg.preciousConfig.size(); i++,p++)
		{
			if ( itemid == p->preciousid)
				break;
		}
		CommonData::m_buytype = 0;
		CommonData::m_buyMutipropNum = 0;

		if (0 == strcmp( "1", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_10 , 1);
		else if (0 == strcmp( "2", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_20 , 1);
		else if (0 == strcmp( "3", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_30 , 1);
		else if (0 == strcmp( "5", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_50 , 1);
		else if (0 == strcmp( "8", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_80 , 1);
		else if (0 == strcmp( "10", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_100 , 1);
		else if (0 == strcmp( "20", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_200 , 1);
		else if (0 == strcmp( "30", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_320 , 1);
		else if (0 == strcmp( "50", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_588 , 1);
		else if (0 == strcmp( "100", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_1288 , 1);
		else if (0 == strcmp( "200", p->preciousprice.c_str() ))
			CppCallJava::toBuyProp( CANDY_BUYGEM_NUM_2588 , 1);
	}
	else if (BTN_TAG_CLOSE == index)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
// 		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(BuyGemLayout->getChildByName( "m_img_dlg" ));
// 		pImgDlg->runAction(CCSequence::create(
// 			MainMapUiLayer::m_mainmapuilayer->getMoveAction( MAP_DLG_QUIT, LEVEL_QUIT_CCCP),
// 			CCCallFunc::create(this, callfunc_selector(HelpWidgt::helpUiClose)),
// 			NULL)
// 			);
	}
}
/***********************************/
/*help widget                     */
/***********************************/
HelpWidgt::HelpWidgt():
HelpLayout(NULL)
{
}

Layout* HelpWidgt::getHelpLayout()
{
	if ( !HelpLayout )
	{
		HelpLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(HELP_LAYOUT_JSONFILE));
		HelpLayout->retain();
		HelpLayout->setZOrder( 2 );
		HelpLayout->setTouchEnable(true);
	}
	HelpLayout->setVisible(true);
	HelpLayout->setTouchEnable(true);

	float nDelayTime1 = 0.08f + 0.08f;
	float nDelayTime2 = 0.041f;

	UIButton *closeButton = dynamic_cast<UIButton*>(HelpLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(HelpWidgt::CloseCallBack));

	UIButton *pNextPagButton = dynamic_cast<UIButton*>(HelpLayout->getChildByName("m_but_nextpg"));
	pNextPagButton->setTouchEnabled(true);
	pNextPagButton->isEffects( true, nDelayTime1+nDelayTime2*2 );
	pNextPagButton->addReleaseEvent(this, coco_releaseselector(HelpWidgt::NextPagButCallBack));

	return HelpLayout;

}

void HelpWidgt::releaseHelpLayout(void)
{
	HelpLayout->removeAllChildrenAndCleanUp(true);
	CC_SAFE_RELEASE_NULL(HelpLayout);
}

void HelpWidgt::NextPagButCallBack(CCObject* sender)
{
	UIPanel *pImgPg1 = dynamic_cast<UIPanel*>(HelpLayout->getChildByName("panel_pag1"));
	UIPanel *pImgPg2 = dynamic_cast<UIPanel*>(HelpLayout->getChildByName("panel_pag2"));

	if (pImgPg1->isVisible())
	{
		pImgPg1->setVisible( false );
		pImgPg2->setVisible( true );
	}
	else
	{
		pImgPg1->setVisible( true );
		pImgPg2->setVisible( false );
	}
}

void HelpWidgt::CloseCallBack(CCObject *pSender)
{
	if ( WIDGET_TYPE_MAP == type )
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
	else if ( WIDGET_TYPE_GAME == type )
	{
		UIImageView* pImgDlg = dynamic_cast<UIImageView*>(HelpLayout->getChildByName( "m_img_dlg" ));
		CCActionInterval* move = CCMoveTo::create(0.8f, LEVEL_QUIT_CCCP);
		CCActionInterval* move_ease_inout2 = CCEaseElasticInOut::create((CCActionInterval*)move, 0.9f );
		pImgDlg->runAction(CCSequence::create(
			move_ease_inout2,
			CCCallFunc::create(this, callfunc_selector(HelpWidgt::helpUiClose)),
			NULL)
			);
	}
}

void HelpWidgt::helpUiClose()
{
	HelpLayout->setTouchEnabled( false );
	if ( WIDGET_TYPE_MAP == type )
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
	else if ( WIDGET_TYPE_GAME == type )
	{
		HelpLayout->setPosition( ccp(0, CCDirector::sharedDirector()->getWinSize().height) );
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	}

}

/***********************************/
/*PropInfo widget                  */
/***********************************/
PropInfoWidget::PropInfoWidget():
PropInfoLayout(NULL)
{
}

PropInfoWidget::~PropInfoWidget()
{
}

Layout* PropInfoWidget::getPropInfoLayout() 
{
	if ( !PropInfoLayout )
	{
		PropInfoLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(PROPINFO_LAYOUT_JSONFILE));
		PropInfoLayout->retain();
		PropInfoLayout->setZOrder( 2 );
		PropInfoLayout->setTouchEnable(true);
	}
	PropInfoLayout->setVisible(true);
	PropInfoLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;
	float nDelayTime2 = 0.041f;


	UIButton *closeButton = dynamic_cast<UIButton*>(PropInfoLayout->getChildByName("m_btu_exit"));
	closeButton->setTouchEnabled(true);
	closeButton->setTag( 0 );
	closeButton->isEffects( true, nDelayTime1 );
	closeButton->addReleaseEvent(this, coco_releaseselector(PropInfoWidget::ButtonCallBack));

	UIButton *pBuyButton = dynamic_cast<UIButton*>(PropInfoLayout->getChildByName("prop_butbuy"));
	pBuyButton->setTouchEnabled(true);
	pBuyButton->setTag( 1 );
	pBuyButton->active();
	pBuyButton->isEffects( true, nDelayTime1+nDelayTime2*3 );
	pBuyButton->addReleaseEvent(this, coco_releaseselector(PropInfoWidget::ButtonCallBack));

	UILabelBMFont* pPropName = dynamic_cast<UILabelBMFont*>(PropInfoLayout->getChildByName( "img_propname" ));
	UIImageView* pPropIco = dynamic_cast<UIImageView*>(PropInfoLayout->getChildByName( "img_prop" ));

	UILabelBMFont* pPropExpain = dynamic_cast<UILabelBMFont*>(PropInfoLayout->getChildByName( "img_propexpain" ));
	UILabelBMFont* pPropExpain_0 = dynamic_cast<UILabelBMFont*>(PropInfoLayout->getChildByName( "img_propexpain_0" ));
	UIPanel* explainPanel = dynamic_cast<UIPanel*>(PropInfoLayout->getChildByName( "explainPanel" ));
	UITextArea* descArea = dynamic_cast<UITextArea*>(PropInfoLayout->getChildByName( "DescArea" ));

	char* pSPropName = (char*)CCString::createWithFormat("app_prop%d_title", propid)->getCString();
	char* pSPropIco = (char*)CCString::createWithFormat( "Image/MainMapUi/Prop/prop%d.png", propid)->getCString();

	pPropExpain->setScale( 0.8f);
	pPropExpain_0->setScale( 0.8f);
	pPropExpain->setVisible( true );
	pPropExpain_0->setVisible( true );
	pPropName->setText( CommonData::GetString(pSPropName).c_str() );

	pPropIco->setTexture( pSPropIco );

	//道具描述区分版本
#ifdef KK_PAY_VERSION
	explainPanel->setVisible(false);
	descArea->setVisible(true);

	const char* desckey = CCString::createWithFormat("newPropDesc_%d",propid)->getCString();
	descArea->setText(CommonData::GetString(desckey).c_str());

#else
	explainPanel->setVisible(true);
	descArea->setVisible(false);
	char* pSPropExpain = (char*)CCString::createWithFormat( "app_prop%d_expain1_forknapsack", propid)->getCString();
	char* pSPropExpain1 = (char*)CCString::createWithFormat( "app_prop%d_expain2_forknapsack", propid)->getCString();
	pPropExpain->setText( CommonData::GetString(pSPropExpain).c_str());
	pPropExpain_0->setText( CommonData::GetString(pSPropExpain1).c_str());
#endif

	/*UILabelAtlas* pPrice = dynamic_cast<UILabelAtlas*>(PropInfoLayout->getChildByName( "label_propprice" ));
	if ( CANDY_PROP_IN_GUANZI != propid )
	{
		std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
		for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
		{
			if(propid == p->id)
			{
				pPrice->setStringValue( (char*)p->price.c_str() );
				break;
			}
		}
	}
	else
	{
		int leftHour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
		int totoalHour =   CommonData::getHourForSever(AnalyseJson::logOnMsg.baseInfo.jar_replay_time);
		int passHour = totoalHour - (leftHour + 1);
		int money = AnalyseJson::logOnMsg.baseInfo.jar_price - passHour*AnalyseJson::logOnMsg.baseInfo.jar_hour_reduce;
		pPrice->setStringValue( (char*)CCString::createWithFormat("%d",money)->getCString() );		
	}*/

#if 0
	UIImageView* pMoney5Img = dynamic_cast<UIImageView*>(PropInfoLayout->getChildByName( "img_money5" ));
	UIImageView* pMoney8Img = dynamic_cast<UIImageView*>(PropInfoLayout->getChildByName( "img_money8" ));

	if ( CANDY_PROP_OUT_STEP3 == propid || CANDY_PROP_OUT_STRIP == propid || CANDY_PROP_OUT_BOMB == propid)
	{
		pMoney5Img->setVisible( true );
		pMoney8Img->setVisible( false );
	}
	else if(  CANDY_PROP_IN_STEP5 == propid || CANDY_PROP_IN_STRIP == propid || CANDY_PROP_IN_BOMB == propid )
	{
		pMoney5Img->setVisible( false );
		pMoney8Img->setVisible( true );
	}
	else if(propid == CANDY_PROP_IN_GUANZI)
	{
		pMoney5Img->setVisible( true );
		pMoney8Img->setVisible( false );

		if(AnalyseJson::energyUsetime.usetime.compare("10")==0)
		{
			if(CommonData::m_isUseEnergy)
			{

				pMoney5Img->setTexture("Image/MainMapUi/Prop/tenrmb.png");
			}
			else
			{
				pMoney5Img->setTexture("Image/MainMapUi/Prop/tenrmbD.png");
			}
		}
		else if(AnalyseJson::energyUsetime.usetime.compare("20")==0)
		{
			if(CommonData::m_isUseEnergy)
			{
				pMoney5Img->setTexture("Image/MainMapUi/Prop/twentyrmb.png");
			}
			else
			{
				pMoney5Img->setTexture("Image/MainMapUi/Prop/twentyrmbD.png");
			}
		}
		else if(AnalyseJson::energyUsetime.usetime.compare("30")==0)
		{
			if(CommonData::m_isUseEnergy)
			{
				pMoney5Img->setTexture("Image/MainMapUi/Prop/thirtyrmb.png");
			}
			else
			{
				pMoney5Img->setTexture("Image/MainMapUi/Prop/thirtyrmbD.png");
			}
		}
	}
#endif
	return PropInfoLayout;
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "../Loading/LoadingScene.h"

#endif
void PropInfoWidget::ButtonCallBack(CCObject *pSender)
{			
	if ( WIDGET_TYPE_MAP == type )
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);
	}
	else if( WIDGET_TYPE_GAME == type )
	{

	}

	UIButton* pBut = (UIButton*)pSender;
	int index = pBut->getTag();

	UIWidget* pwidget = PropInfoLayout->getParent();
	switch( index )
	{
	case 0:
		{	
			if ( WIDGET_TYPE_MAP == type )
			{
#ifdef KK_PAY_VERSION
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidget(MAP_WIDGET_PROPBUY_DLG);
#else 
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
#endif
				
				//MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_LEVEL_INFO, CandyManager::currentLevel );
			}
			else if( WIDGET_TYPE_GAME == type )
			{
				UIWidget* pWid = (UIWidget*)CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget();
				UIWidget* rWid = PropInfoLayout->getParent();
				/**暂时进行分类处理解决，以后做一个全局的界面逻辑管理器类*/
				if(pWid == rWid)
				{
					CandyManager::getInstance()->uiLayer->QuitPropWidget();

					if ( GAME_STATE_FAIL == CandyManager::getInstance()->resultMgr->gamestate )
						CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_LOST_EFFECT);
				}
				else /*if(PropInfoLayout->getParent() == (UIWidget*)CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget())*/
				{
					CandyManager::getInstance()->resultMgr->getResultLayer()->QuitPropWidget();
				}
				CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
			}
		}

		break;

	case 1:
		{
			UIButton *pBuyButton = dynamic_cast<UIButton*>(PropInfoLayout->getChildByName("prop_butbuy"));
			pBuyButton->setTouchEnabled( false );

			std::list<UserPropInfoStr>::iterator p = AnalyseJson::logOnMsg.propInfo.begin();
			for(int i = 0; i<(int)AnalyseJson::logOnMsg.propInfo.size(); i++, p++)
			{
				if(propid == p->id)
					break;
			}

			if ( WIDGET_TYPE_MAP == type )
			{
#ifdef KK_PAY_VERSION
				//mini不需要判断宝石不足
				CommonData::m_buytype = p->id;
				CommonData::m_buyMutipropNum = 0;

				int pricetype = 0;
				//mini版本
				if (CommonData::m_buytype == CANDY_PROP_OUT_COLORFULL )
				{
					pricetype = CANDY_BUYGEM_NUM_60;
				}
				else if (CommonData::m_buytype == CANDY_PROP_OUT_BOMBNEW )
				{
					pricetype = CANDY_BUYGEM_NUM_60;
				}
				else if (CommonData::m_buytype == CANDY_PROP_IN_RESORT )
				{
					pricetype = CANDY_BUYGEM_NUM_60;
				}
				else if (CommonData::m_buytype == CANDY_PROP_IN_SWAP )
				{
					pricetype = CANDY_BUYGEM_NUM_60;
				}
				else if (CommonData::m_buytype == CANDY_PROP_IN_HAMMER )
				{
					pricetype = CANDY_BUYGEM_NUM_60;
				}
				else if(CommonData::m_buytype == CANDY_PROP_IN_STEP5)
				{
					pricetype = CANDY_BUYGEM_NUM_80;
				}

				//CppCallJava::toBuyProp(pricetype, MOBILE_MONEY8_BUY_PROPNUM );	//alex
				
				//新版支付
				CandyPay::getInstance()->RequestCandyOrder(CommonData::m_buytype);
#endif
				
			}
			else if (  WIDGET_TYPE_GAME == type  )
			{
				//　罐子购买
				if( CANDY_PROP_IN_GUANZI == propid )
				{
					CCLog("CANDY_PROP_IN_GUANZI 1");
					int leftHour =   CommonData::getHourForSever(AnalyseJson::magicLampInfo.magicLampTime);
					int totoalHour =   CommonData::getHourForSever(AnalyseJson::logOnMsg.baseInfo.jar_replay_time);

					int passHour = totoalHour - (leftHour+1);
					int tem = AnalyseJson::logOnMsg.baseInfo.jar_price - passHour*AnalyseJson::logOnMsg.baseInfo.jar_hour_reduce;

					//　宝石不足
					if( tem > AnalyseJson::logOnMsg.baseInfo.gemNum )
					{
						CCLog("CANDY_PROP_IN_GUANZI 2");

						CommonData::m_buytype = CANDY_PROP_IN_GUANZI;
						CommonData::m_buyMutipropNum = 0;

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
					else
					{
						CCLog("CANDY_PROP_IN_GUANZI 3");

						MsgMgr::sendGemBuySkill( AnalyseJson::logOnMsg.baseInfo.id );
					}
				}
				else
				{

					////　宝石不足
					//if ( atoi(p->price.c_str()) > AnalyseJson::logOnMsg.baseInfo.gemNum)
					//{
					//	CommonData::m_buytype = p->id;
					//	CommonData::m_buyMutipropNum = 0;

					//	int pricetype = 0;
					//	//mini版本
					//	if (CommonData::m_buytype == CANDY_PROP_OUT_COLORFULL )
					//	{
					//		pricetype = CANDY_BUYGEM_NUM_50;
					//	}
					//	else if (CommonData::m_buytype == CANDY_PROP_OUT_BOMBNEW )
					//	{
					//		pricetype = CANDY_BUYGEM_NUM_50;
					//	}
					//	else if (CommonData::m_buytype == CANDY_PROP_IN_RESORT )
					//	{
					//		pricetype = CANDY_BUYGEM_NUM_80;
					//	}
					//	else if (CommonData::m_buytype == CANDY_PROP_IN_SWAP )
					//	{
					//		pricetype = CANDY_BUYGEM_NUM_80;
					//	}
					//	else if (CommonData::m_buytype == CANDY_PROP_IN_HAMMER )
					//	{
					//		pricetype = CANDY_BUYGEM_NUM_80;
					//	}

					//	CppCallJava::toBuyProp(pricetype, MOBILE_MONEY8_BUY_PROPNUM );	//alex
					//}
					//else
					//{
					//	//MsgMgr::sendGemBuyProp( AnalyseJson::logOnMsg.baseInfo.id, propid, MOBILE_MONEY8_BUY_PROPNUM);	//alex
					//}

					//mini不需要判断宝石不足
					CommonData::m_buytype = p->id;
					CommonData::m_buyMutipropNum = 0;

					int pricetype = 0;
					//mini版本
					if (CommonData::m_buytype == CANDY_PROP_OUT_COLORFULL )
					{
						pricetype = CANDY_BUYGEM_NUM_60;
					}
					else if (CommonData::m_buytype == CANDY_PROP_OUT_BOMBNEW )
					{
						pricetype = CANDY_BUYGEM_NUM_60;
					}
					else if (CommonData::m_buytype == CANDY_PROP_IN_RESORT )
					{
						pricetype = CANDY_BUYGEM_NUM_60;
					}
					else if (CommonData::m_buytype == CANDY_PROP_IN_SWAP )
					{
						pricetype = CANDY_BUYGEM_NUM_60;
					}
					else if (CommonData::m_buytype == CANDY_PROP_IN_HAMMER )
					{
						pricetype = CANDY_BUYGEM_NUM_60;
					}
					else if(CommonData::m_buytype == CANDY_PROP_IN_STEP5)
					{
						pricetype = CANDY_BUYGEM_NUM_80;
					}

					//CppCallJava::toBuyProp(pricetype, MOBILE_MONEY8_BUY_PROPNUM );	//alex

					//新版支付
					CandyPay::getInstance()->RequestCandyOrder(CommonData::m_buytype);
				}				
			}
		}
		break;
	}
}

void PropInfoWidget::PropInfoUiClose()
{
	PropInfoLayout->setTouchEnabled( false );
	PropInfoLayout->setVisible(false);
	MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
}

void PropInfoWidget::releasePropInfoLayout(void)
{
	PropInfoLayout->removeAllChildrenAndCleanUp(true);
	CC_SAFE_RELEASE_NULL(PropInfoLayout);
}


/***********************************/
/*Success widget                  */
/***********************************/

#define SUCCEEDUI_BTNFNT_CONFIRM		"Image/Common/FontImg/BtnFntConfirm.png"
#define SUCCEEDUI_BTNFNT_AGAINCONNENT	"Image/Common/FontImg/BtnFntAgainConnent.png"
SuccessWidget::SuccessWidget():
SuccessLayout(NULL)
{
}

SuccessWidget::~SuccessWidget()
{
}

Layout* SuccessWidget::getSuccessLayout() 
{
	if ( !SuccessLayout )
	{
		SuccessLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(SUCCESSUI_LAYOUT_JSONFILE));
		SuccessLayout->retain();
		SuccessLayout->setZOrder( 2 );
		SuccessLayout->setTouchEnable(true);
	}
	SuccessLayout->setVisible(true);
	SuccessLayout->setTouchEnable(true);

	float nDelayTime1 = 0.0f;

	CCLog("SuccessWidget::getSuccessLayout");
	UIButton *confirmButton = dynamic_cast<UIButton*>(SuccessLayout->getChildByName("m_but_sur"));
	confirmButton->setTouchEnabled(true);
	confirmButton->isEffects( true, nDelayTime1 );
	confirmButton->addReleaseEvent(this, coco_releaseselector(SuccessWidget::ButtonCallBack));


	UIButton *delfriendconfirmBbtn = dynamic_cast<UIButton*>(SuccessLayout->getChildByName("BtnConfirm"));
	delfriendconfirmBbtn->setTouchEnabled(true);
	delfriendconfirmBbtn->setTag( SUCCESSUI_BTNTAG_DELFRIENDCONFIRM );
	delfriendconfirmBbtn->isEffects( true, nDelayTime1 );
	delfriendconfirmBbtn->addReleaseEvent(this, coco_releaseselector(SuccessWidget::ButtonCallBack));


	UIButton *cancelButton = dynamic_cast<UIButton*>(SuccessLayout->getChildByName("BtnCancel"));
	cancelButton->setTouchEnabled(true);
	cancelButton->setTag( SUCCESSUI_BTNTAG_DELFRIENDCANCEL );
	cancelButton->isEffects( true, nDelayTime1 );
	cancelButton->addReleaseEvent(this, coco_releaseselector(SuccessWidget::ButtonCallBack));


	UILabel* pTitleName = dynamic_cast<UILabel*>(SuccessLayout->getChildByName( "m_img_tip_title" ));
	UIImageView* pBtnFnt = dynamic_cast<UIImageView*>(SuccessLayout->getChildByName( "m_img_tip_buttitle_0" ));

	UIImageView* pPropImg = dynamic_cast<UIImageView*>(SuccessLayout->getChildByName( "PropImg" ));

	UILabel *pNicename = dynamic_cast<UILabel*>(SuccessLayout->getChildByName( "Labelname" ));

	pTitleName->setPosition( ccp(0, pTitleName->getPosition().y) );
	pPropImg->setVisible( false );

	if ( PROMPT_TYPE_DELFRIEND == sucType )
	{
		confirmButton->setVisible( false );
		delfriendconfirmBbtn->setVisible( true );
		cancelButton->setVisible( true );

		confirmButton->setTouchEnable( false );
		delfriendconfirmBbtn->setTouchEnable( true );
		cancelButton->setTouchEnable( true );

		pNicename->setVisible( true );

		std::list<UserFriendInfoStr>::iterator p;
		p = AnalyseJson::friendInfoMsg.friendInfo.begin();

		for (int i = 0; i<(int)AnalyseJson::friendInfoMsg.friendInfo.size(); i++, p++)
		{
			if (data == p->id)
				break;
		}
		pNicename->setText( p->nickName.c_str() );
	}
	else
	{
		confirmButton->setVisible( true );
		delfriendconfirmBbtn->setVisible( false );
		cancelButton->setVisible( false );

		confirmButton->setTouchEnable( true );
		delfriendconfirmBbtn->setTouchEnable( false );
		cancelButton->setTouchEnable( false );

		pNicename->setVisible( false  );

	}

	if ( PROMPT_TYPE_BUYSUC == sucType )
	{
		data;
		pTitleName->setPosition( ccp(0 - 50, pTitleName->getPosition().y) );
		pPropImg->setVisible( true );
		pPropImg->setTexture( CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png", CommonData::m_curBuyPropid )->getCString() );

		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_buy_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_FEEDBACK == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_feedback_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_INVITE == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_invite_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_SUBMITSUC == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_submit_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_NETERR == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_NETERR );
		pTitleName->setText( CommonData::GetString("app_prompt_neterror").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_AGAINCONNENT );
	}
	else if ( PROMPT_TYPE_REMINDNETWORK == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_REMINDNETWORK );
		pTitleName->setText( CommonData::GetString("app_prompt_neterror").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_LIFELACK_TO_MAP == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_TOMAP );
		pTitleName->setText( CommonData::GetString("app_prompt_lacklifetomap1").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_CHITNOOPEN == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_chit_noopen").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_DELFRIEND == sucType )
	{
		pTitleName->setText( CommonData::GetString("app_prompt_delfriend").c_str() );
	}
	else if ( PROMPT_TYPE_FRIENDLIMIT == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_prompt_friendlimit").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_BUYLIFESUC == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_buy_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}
	else if ( PROMPT_TYPE_BUYVIPSUC == sucType )
	{
		confirmButton->setTag( SUCCESSUI_BTNTAG_CONFIRM );
		pTitleName->setText( CommonData::GetString("app_buy_success").c_str() );
		pBtnFnt->setTexture( SUCCEEDUI_BTNFNT_CONFIRM );
	}

	return SuccessLayout;
}

void SuccessWidget::releaseSuccessLayout(void)
{
	if ( SuccessLayout )
	{
		SuccessLayout->removeFromParentAndCleanup(true);
		CC_SAFE_RELEASE_NULL(SuccessLayout);
	}
}

void SuccessWidget::ButtonCallBack(CCObject *pSender)
{
	UIButton* pButton = (UIButton*)pSender;
	int BtnType = pButton->getTag();

	switch (BtnType)
	{
	case SUCCESSUI_BTNTAG_CONFIRM:
		{
			MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
		}
		break;
		
	case SUCCESSUI_BTNTAG_TOMAP:
		{			
			CommonData::setButtonTouchEnable( pSender, false);
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
			//CandyManager::getInstance()->resultMgr->setCurrentResult( CANDY_NOLIFE_EXIT_GAME);
			CommonData::m_isShowBuyLife = true;	//返回关卡页面时，显示购买生命界面
			MainMap::EnteyMapScene(GAME_STATE_FAIL);
		}
		break;

	case SUCCESSUI_BTNTAG_NETERR:
		{
			if ( WIDGET_TYPE_LOADING == type )
			{
				Loading::m_loading->NetworkErrBtnCallback();
			}
	
		}
		break;
	case SUCCESSUI_BTNTAG_REMINDNETWORK:
		{
			if( WIDGET_TYPE_GAME == type)
			{
				if(SuccessLayout != NULL)
				{
					SuccessLayout->removeFromParentAndCleanup(true);
				}
			}
			else if(type == WIDGET_TYPE_MAP)
			{
				if(MainMapUiLayer::m_mainmapuilayer)
				{
					MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
					if(SuccessLayout != NULL)
					{
						SuccessLayout->removeFromParentAndCleanup(true);
					}
			}
		}
		}
		break;

		//　确定删除
	case SUCCESSUI_BTNTAG_DELFRIENDCONFIRM:
		{
			MainMapUiLayer::m_mainmapuilayer->removeFriendAndUpdataList( data );
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
		}
		break;

		//　取消删除
	case SUCCESSUI_BTNTAG_DELFRIENDCANCEL:
		{
			MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
		}
		break;

	default:
		break;
	}

}

void SuccessWidget::ButtonClose(void)
{

}

/***********************************/
/*SurpassFriend widget                  */
/***********************************/
SurpassFriend::SurpassFriend():
SurpassFriendLayout(NULL)
{
}

SurpassFriend::~SurpassFriend()
{
	CC_SAFE_RELEASE_NULL(SurpassFriendLayout);
}

Layout* SurpassFriend::getSurpassFriendLayout() 
{
	if ( !SurpassFriendLayout )
	{
		SurpassFriendLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(SURPASSFRIEND_LAYOUT_JSONFILE));
		SurpassFriendLayout->retain();
		SurpassFriendLayout->setZOrder( 2 );
	}
	SurpassFriendLayout->setVisible(true);
	SurpassFriendLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(SurpassFriendLayout->getChildByName("ReturnButton"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(SurpassFriend::ButtonCallBack));

	UIButton *goBtn = dynamic_cast<UIButton*>(SurpassFriendLayout->getChildByName("NextStageButton"));
	goBtn->setTouchEnabled(true);
	goBtn->isEffects( true, nDelayTime1 );
	goBtn->setTag( 105 );

	UIButton *m_shareWeixin = dynamic_cast<UIButton*>(SurpassFriendLayout->getChildByName("weixinBtn"));
	m_shareWeixin->setTag( 99 );
//	m_shareWeixin->addReleaseEvent(this, coco_releaseselector(SurpassFriend::ShareBtnCb));
	m_shareWeixin->setTouchEnable(false);

	UIButton *m_shareTWeibo = dynamic_cast<UIButton*>(SurpassFriendLayout->getChildByName("TweiboBtn"));
	m_shareTWeibo->setTag( 100 );
//	m_shareTWeibo->addReleaseEvent(this, coco_releaseselector(SurpassFriend::ShareBtnCb));
	m_shareTWeibo->setTouchEnable(false);

	UIButton *m_shareSWeibo = dynamic_cast<UIButton*>(SurpassFriendLayout->getChildByName("SweiboBtn"));
	m_shareSWeibo->setTag( 101 );
//	m_shareSWeibo->addReleaseEvent(this, coco_releaseselector(SurpassFriend::ShareBtnCb));
	m_shareSWeibo->setTouchEnable(false);

	UIPanel* pPanel = dynamic_cast<UIPanel*>(SurpassFriendLayout->getChildByName( "Panel_head" ));
	int maxLevel = CommonData::getMaxLevel();
	int count = 0;
	//统计真实人数
	int num = 0;
	std::list<UserFriendInfoStr>::iterator iter = AnalyseJson::friendInfoMsg.friendInfo.begin();
	std::list<UserFriendInfoStr>::iterator iterEnd= AnalyseJson::friendInfoMsg.friendInfo.end();
	for(;iter!=iterEnd;++iter)
	{
		if(iter->level == maxLevel)
		{
			if(count <= 4)
			{
				UIWidget *pWid = addHeadImg(*iter);
				pPanel->addChild(pWid);
				pWid->setTag(count);
				count++;
			}
			num++;
		}
	}
	for(int i = 0;i<count;i++)
	{
		int wid = pPanel->getContentSize().width/(count+1);
		CCPoint pos = CCPointMake((i+1)*wid-60,pPanel->getContentSize().height*0.5);
		pPanel->getChildByTag(i)->setPosition(pos);
	}
	UILabelAtlas* pWenzi1 = dynamic_cast<UILabelAtlas*>(SurpassFriendLayout->getChildByName( "title_wenzi_1" ));
	UILabelAtlas* pWenzi2 = dynamic_cast<UILabelAtlas*>(SurpassFriendLayout->getChildByName( "title_wenzi_2" ));

	pWenzi1->setStringValue(CCString::createWithFormat("%d",num)->getCString());
	pWenzi2->setStringValue(CCString::createWithFormat("%d",maxLevel)->getCString());

	return SurpassFriendLayout;
}
UIWidget* SurpassFriend::addHeadImg(UserFriendInfoStr player)
{
	UIPanel* pPanel = UIPanel::create();
	pPanel->setBackGroundColor(ccBLACK);


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
	pHeadImg->setScale( 0.7f );
	pHeadImg->setVisible( true );
	pHeadImg->setPosition(ccp(58, 55));
	pPanel->addChild( pHeadImg);
	pHeadImg->setZOrder(-1);
	//头像框
	UIImageView* pHeadFrameImg = UIImageView::create();
	pHeadFrameImg->setTexture( "Image/MainMapUi/headframe.png" );
	pHeadFrameImg->setVisible( true );
	pHeadFrameImg->setPosition(ccp(0, 0));
	pHeadImg->addChild( pHeadFrameImg );
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

	UITextArea* pName = UITextArea::create();
	pName->setPosition( ccp(57, -16) );
	pName->setColor( ccc3(255,255,255));
	pName->setFontSize(30);
	pName->setText(player.nickName.c_str());
	pName->setVisible( true );
	pPanel->addChild( pName );

	
	return pPanel;
}
void SurpassFriend::ButtonCallBack(CCObject *pSender)
{
	MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
}

void SurpassFriend::CloseCallBack()
{
	SurpassFriendLayout->setTouchEnabled( false );
	SurpassFriendLayout->setVisible(false);
	
	MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
	MainMap::m_mainmap->DisplayMapUi();

	MainMap::m_mainmap->setHeadMove();
}

/***********************************/
/*ResortRank widget                  */
/***********************************/
UpdataGameWidget::UpdataGameWidget( void ):
UpdataGameLayout(NULL)
{

}

UpdataGameWidget::~UpdataGameWidget( void )
{
	CC_SAFE_RELEASE_NULL(UpdataGameLayout);
}

void UpdataGameWidget::releaseLayout(void)
{
	if ( UpdataGameLayout )
	{
		UpdataGameLayout->removeAllChildrenAndCleanUp(true);
		CC_SAFE_RELEASE_NULL(UpdataGameLayout);
		UpdataGameLayout = NULL;
	}
}

Layout* UpdataGameWidget::getUpdataGameLayout( void )
{
	if ( !UpdataGameLayout )
	{
		UpdataGameLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(UPDATAGAME_LAYOUT_JSONFILE));
		UpdataGameLayout->retain();
		UpdataGameLayout->setZOrder( 2 );
	}
	UpdataGameLayout->setVisible(true);
	UpdataGameLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *pNowUpdata = dynamic_cast<UIButton*>(UpdataGameLayout->getChildByName("NowUpdataBtn"));
	pNowUpdata->setTag( TAG_FORUPDATA_NOWUPDATA );
	pNowUpdata->setTouchEnabled(true);
	pNowUpdata->isEffects( true, nDelayTime1 );
	pNowUpdata->addReleaseEvent(this, coco_releaseselector(UpdataGameWidget::ButtonCallBack));

	UIButton *pWaitUpdata = dynamic_cast<UIButton*>(UpdataGameLayout->getChildByName("WaitUpdataBtn"));
	pWaitUpdata->setTag( TAG_FORUPDATA_WAITUPDATA );
	pWaitUpdata->setTouchEnabled(true);
	pWaitUpdata->isEffects( true, nDelayTime1 );
	pWaitUpdata->addReleaseEvent(this, coco_releaseselector(UpdataGameWidget::ButtonCallBack));

	UITextArea *pUpdataText = dynamic_cast<UITextArea*>(UpdataGameLayout->getChildByName("Updatatext"));
	pUpdataText->setText( AnalyseJson::updataData.update_info.c_str() );

	return UpdataGameLayout;
}

void UpdataGameWidget::ButtonCallBack( CCObject *pSender )
{
	UIButton* pBtn = (UIButton*)pSender;
	int tag = pBtn->getTag();

	if ( TAG_FORUPDATA_NOWUPDATA == tag )
	{
	}
	else if ( TAG_FORUPDATA_WAITUPDATA == tag )
	{
		MsgMgr::SendSoundOutLogin( AnalyseJson::logOnMsg.baseInfo.idx.c_str(), AnalyseJson::logOnMsg.baseInfo.channel.c_str() );
	}

	Loading::m_loading->UPdataBtnBtnCallback( pSender );
}


/***********************************/
/*GameShopWidget widget                  */
/***********************************/
GameShopWidget::GameShopWidget():
GameShopLayout(NULL),
m_buyNum(1),
m_buyPropid(0)
{
}

GameShopWidget::~GameShopWidget()
{
	CC_SAFE_RELEASE_NULL(GameShopLayout);
}

Layout* GameShopWidget::getGameShopLayout() 
{
	if ( !GameShopLayout )
	{
		GameShopLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYSHOP_LAYOUT_JSONFILE));
		GameShopLayout->retain();
		GameShopLayout->setZOrder( 2 );
	}
	GameShopLayout->setVisible(true);
	GameShopLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(GameShopLayout->getChildByName("ShopExitBtn"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameShopWidget::ShopExitCallBack));
	returnBtn->setTag(ShopInMaptag);

	InitShopScrollview();

	return GameShopLayout;
}

void GameShopWidget::ShopExitCallBack(CCObject *pSender)
{
	UIButton *returnBtn = dynamic_cast<UIButton*>(GameShopLayout->getChildByName("ShopExitBtn"));
	int tag = returnBtn->getTag();
	((UIButton*)pSender)->setTouchEnabled(false);

	if (ShopInMaptag == tag)	//在游戏外面的商城退出时的处理
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
	else //游戏里面的商城的退出处理 
	{
		CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );

		//动作
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCActionInterval* moveBy = CCMoveBy::create(0.7, ccp(0,winSize.height*1.5));
		CCActionInterval* easeMove = CCEaseElasticInOut::create(moveBy,0.9);

		CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(GameShopWidget::RemoveShop));
		UIImageView* shopPanel = dynamic_cast<UIImageView*>(GameShopLayout->getChildByName("m_img_dlg"));
		shopPanel->runAction(CCSequence::create(easeMove,func, NULL));
	}

}

void GameShopWidget::RemoveShop()
{
	if (GameShopLayout)
	{
		GameShopLayout->removeFromParentAndCleanup(true);
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);		//游戏状态要设置成进行中s
	}
}

void GameShopWidget::InitShopScrollview()
{
	UIScrollView*  shopScroll = dynamic_cast<UIScrollView*>( GameShopLayout->getChildByName("ShopScrollView") );
	shopScroll->setTouchEnabled(true);

	CCSize contentSize = shopScroll->getContentSize();

	int itemNum = AnalyseJson::logOnMsg.propInfo.size();
	shopScroll->setInnerContainerSize(CCSizeMake( contentSize.width,itemNum*160 + 8));
	CCSize ScrollSize = shopScroll->getInnerContainerSize();

	list<UserPropInfoStr>::iterator it = AnalyseJson::logOnMsg.propInfo.begin();
	
	//添加item
	int pos = 0;
	CCLOG("-----shoplist size = %d",AnalyseJson::logOnMsg.propInfo.size());
	for ( int i = 0; i < AnalyseJson::logOnMsg.propInfo.size(); ++i,++it)
	{
		int propId = (*it).id;
		CCLOG("----list id = %d",propId);
		if (CANDY_PROP_OUT_HEAD == propId || CANDY_PROP_COMPOSE_1 == propId)
		{
			continue;
		}
		UIImageView* item = AddShopItem(pos%3+1,propId,(char*)(*it).name.c_str(),(char*)(*it).price.c_str());
		shopScroll->addChild(item);

		item->setPosition(ccp(ScrollSize.width*0.5,
			ScrollSize.height - item->getSize().height*0.6 - item->getSize().height*pos));
		++pos;
		
	}

}

UIImageView* GameShopWidget::AddShopItem(int color, int propId, char* propName,char* propPrice)
{
	UIScrollView*  shopScroll = dynamic_cast<UIScrollView*>( GameShopLayout->getChildByName("ShopScrollView") );
	CCSize contentSize = shopScroll->getContentSize();

	CCSize itemSize = CCSizeMake(contentSize.width,160);

	UIImageView* itemBg = UIImageView::create();
	itemBg->setTexture("Image/MainMapUi/ItemBg.png");
	itemBg->setScale9Enabled(true);
	itemBg->setScale9Size(itemSize);

	UIImageView* itemColor = UIImageView::create();
	itemColor->setTexture(CCString::createWithFormat("Image/MainMapUi/ItemColor%d.png",color)->getCString());
	itemColor->setScale9Enabled(true);
	itemColor->setScale9Size(CCSizeMake(itemSize.width-6,itemSize.height-6));
	itemBg->addChild(itemColor);

	//道具ico
	UIImageView* propIco = UIImageView::create();
	propIco->setTexture(CCString::createWithFormat("Image/MainMapUi/Prop/prop%d.png",propId)->getCString());
	propIco->setPosition(ccp(-itemBg->getSize().width*0.38,0));
	propIco->setScale(1.4);
	propIco->isEffects(true);
	itemBg->addChild(propIco);

	//道具价格及购买按钮
	UITextButton* BuyBtn = UITextButton::create();
	BuyBtn->setTextures("Image/MainMapUi/m_but_buylifeN.png","Image/MainMapUi/m_but_buylifeP.png","Image/MainMapUi/m_but_buylifeP.png");
	BuyBtn->setTag(propId);
	BuyBtn->setPosition(ccp(itemBg->getSize().width*0.32,5));
	BuyBtn->setTouchEnabled(true);
	BuyBtn->setScale9Enabled(true);
	BuyBtn->setSize(CCSizeMake(BuyBtn->getContentSize().width * 1.3,BuyBtn->getContentSize().height*1.1));
	BuyBtn->setAnchorPoint(ccp(0.5,0.5));
	BuyBtn->addReleaseEvent(this,coco_releaseselector(GameShopWidget::BuybtnCallback));
	itemBg->addChild(BuyBtn);
	BuyBtn->isEffects(true);

	CCSize BtnSize = BuyBtn->getSize();

	//价格标签
	/*char* price = "";
	if (propId >= CANDY_PROP_OUT_COLORFULL && propId <= CANDY_PROP_IN_HAMMER)
	{
#ifdef KK_PAY_VERSION
		price = "5 元";
#else
		price = "6 元";
#endif
	}
	else if (propId == CANDY_PROP_IN_STEP5)
	{
#ifdef KK_PAY_VERSION
		price = "5 元";
#else
		price = "8 元";
#endif
	}*/
	std::string price = propPrice;
	price += "元";
	BuyBtn->setText(price.c_str());
	BuyBtn->setFontSize(36);

	//道具名称
	int PropNum = 1;
	/*if (propId == CANDY_PROP_IN_RESORT || propId == CANDY_PROP_IN_SWAP )
	{
		PropNum = 3;
	}*/
	std::string nameStr = CCString::createWithFormat("%s×%d",propName, PropNum)->getCString();
	CCLabelTTF* nameTtf = CCLabelTTF::create(nameStr.c_str(),"",34);
	nameTtf->setPosition(ccp(-itemBg->getSize().width*0.25, 47));
	nameTtf->setAnchorPoint(ccp(0,0.5));
	itemBg->addCCNode(nameTtf);

	//描述
	std::string key = CommonData::GetString(CCString::createWithFormat("app_prop%d_expain",propId)->getCString());
	CCLabelTTF* DiscLabel = CCLabelTTF::create(key.c_str(),"",24);
	DiscLabel->setDimensions(CCSizeMake(itemBg->getSize().width*0.43,itemBg->getSize().height*0.8));
	DiscLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
	DiscLabel->setAnchorPoint(ccp(0,0.5));
	DiscLabel->setPosition(ccp(-itemBg->getSize().width*0.25, -itemBg->getSize().height * 0.32));
	itemBg->addCCNode(DiscLabel);
	DiscLabel->setColor(ccc3(79,39,21));

	return itemBg;
}

void GameShopWidget::BuybtnCallback(CCObject* sender)
{
	if (type == WIDGET_TYPE_MAP)
	{
		MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);
	}
	else
	{
		CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );
	}

	UIButton* btn = (UIButton*)sender;
	int tag = btn->getTag();

	//新版MM支付
	CommonData::m_BuyAdd5From = 0;	
	CandyPay::getInstance()->RequestCandyOrder(tag);
	return;

#ifdef KK_PAY_VERSION
	if (type == WIDGET_TYPE_MAP)
	{
		//游戏外面
		//MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();

		//测试,延时0.5s购买
		CCActionInterval* delay = CCDelayTime::create(0.5);
		CCCallFunc * buyFunc = CCCallFunc::create(NULL,callfunc_selector(CommonData::DelayCallBuyPropfunc));
		btn->runAction(CCSequence::create(delay,buyFunc,NULL));

		////直接移除，同时清空列表
		//GameShopLayout->removeFromParentAndCleanup(true);

		//std::list<WidgetNode>::iterator tem = MainMapUiLayer::m_mainmapuilayer->widgetList.begin();
		//tem->widget->setPosition( ccp(0, 1280.0f) );
		//MainMapUiLayer::m_mainmapuilayer->m_pPanel->setVisible( false );
		//MainMapUiLayer::m_mainmapuilayer->m_pPanel->setTouchEnabled( false );
		//MainMapUiLayer::m_mainmapuilayer->widgetList.erase( tem );

		////显示道具购买界面
		//MainMapUiLayer::m_mainmapuilayer->showMapWidget(MAP_WIDGET_PROPBUY_DLG , tag);

		

	}
	else if(WIDGET_TYPE_GAME)
	{
		//游戏里面
		CandyManager::getInstance()->uiLayer->showPropBuy(tag);
		GameShopLayout->removeFromParentAndCleanup(true);
	}
#else
	//回调处理,调出短信购买界面
	CommonData::m_buytype = tag;
	if (tag == CANDY_PROP_IN_STEP5)
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_80,1);
	}
	else
	{
		CppCallJava::toBuyProp(CANDY_BUYGEM_NUM_60,1);
	}
#endif // KK_PAY_VERSION

}




/***********************************/
/*GameVipWidget widget*/
/***********************************/
GameVipWidget::GameVipWidget():
GameVipLayout(NULL)
{

}

GameVipWidget::~GameVipWidget()
{
	CC_SAFE_RELEASE_NULL(GameVipLayout);
}

Layout* GameVipWidget::getGameVipLayout() 
{
	if ( !GameVipLayout )
	{
		GameVipLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYVIP_LAYOUT_JSONFILE));
		GameVipLayout->retain();
		GameVipLayout->setZOrder( 2000 );
	}
	GameVipLayout->setVisible(true);
	GameVipLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_exit"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ExitCallBack));

	UIButton *Btn_vip1 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip1"));
	Btn_vip1->setTouchEnabled(true);
	Btn_vip1->isEffects( true, nDelayTime1 );
	Btn_vip1->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIButton *Btn_vip2 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip2"));
	Btn_vip2->setTouchEnabled(true);
	Btn_vip2->isEffects( true, nDelayTime1 );
	Btn_vip2->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIButton *Btn_vip3 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip3"));
	Btn_vip3->setTouchEnabled(true);
	Btn_vip3->isEffects( true, nDelayTime1 );
	Btn_vip3->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIImageView *Img_vip1 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip1"));
	Img_vip1->setTouchEnabled(true);
	Img_vip1->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIImageView *Img_vip2 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip2"));
	Img_vip2->setTouchEnabled(true);
	Img_vip2->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIImageView *Img_vip3 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip3"));
	Img_vip3->setTouchEnabled(true);
	Img_vip3->addReleaseEvent(this, coco_releaseselector(GameVipWidget::ButtonCallBack));

	UIImageView *pDataImg = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_date_des"));
	if(AnalyseJson::logOnMsg.baseInfo.isVip == 3)
	{
		Btn_vip1->disable();
		Btn_vip2->disable();
		Btn_vip3->disable();
		Img_vip1->setTouchEnabled(false);
		Img_vip2->setTouchEnabled(false);
		Img_vip3->setTouchEnabled(false);
		pDataImg->setVisible(false);
	}
	else
	{
		pDataImg->setVisible(true);
	}

	UIImageView *pImg = UIImageView::create();
	pImg->setTexture(CCString::createWithFormat("Image/CandyGame/Others/viplevel%d.png",AnalyseJson::logOnMsg.baseInfo.isVip)->getCString());
	UIPanel *pPanel = dynamic_cast<UIPanel*>(GameVipLayout->getChildByName("vip_level"));
	pPanel->removeAllChildren();
	pPanel->addChild(pImg);
	CCSize size = pPanel->getContentSize();
	pImg->setPosition(ccp(size.width/2,size.height/2));

	UIImageView *pLight1 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Light1"));
	UIImageView *pLight2 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Light2"));
	pLight1->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCFadeTo::create(1.0f,65),
		CCFadeTo::create(1.0f,255),
		NULL))
		);
	pLight2->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCFadeTo::create(1.0f,255),
		CCFadeTo::create(1.0f,65),
		NULL))
		);

	UILabelBMFont* pVipPrice1 = dynamic_cast<UILabelBMFont*>(GameVipLayout->getChildByName( "price_vip1" ));
	UILabelBMFont* pVipPrice2 = dynamic_cast<UILabelBMFont*>(GameVipLayout->getChildByName( "price_vip2" ));
	UILabelBMFont* pVipPrice3 = dynamic_cast<UILabelBMFont*>(GameVipLayout->getChildByName( "price_vip3" ));


	list<UserVipInfoStr >::iterator iter;
	for(iter= AnalyseJson::logOnMsg.vipConfig.begin();	iter!=AnalyseJson::logOnMsg.vipConfig.end(); iter++)
	{
		if((*iter).id == 1002)
		{
			pVipPrice1->setText(iter->price.c_str());
		}
		else if((*iter).id == 1003)
		{
			pVipPrice2->setText(iter->price.c_str());
		}
		else
		{
			pVipPrice3->setText(iter->price.c_str());
		}
	}


	UILabelAtlas *pData = dynamic_cast<UILabelAtlas*>(GameVipLayout->getChildByName("limit_data"));
	pData->setStringValue(CCString::createWithFormat("%d",AnalyseJson::logOnMsg.baseInfo.vipLength)->getCString());

	return GameVipLayout;
}

void GameVipWidget::ExitCallBack(CCObject *pSender)
{
	if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
}
void GameVipWidget::ButtonCallBack(CCObject *pSender)
{
	UIButton *Btn_vip1 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip1"));
	UIButton *Btn_vip2 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip2"));
	UIButton *Btn_vip3 = dynamic_cast<UIButton*>(GameVipLayout->getChildByName("Btn_vip3"));
	UIImageView *Img_vip1 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip1"));
	UIImageView *Img_vip2 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip2"));
	UIImageView *Img_vip3 = dynamic_cast<UIImageView*>(GameVipLayout->getChildByName("Img_vip3"));

	list<UserVipInfoStr >::iterator iter;
	int payId = 0;
	if(pSender == Btn_vip1 || pSender == Img_vip1)
	{
		CommonData::m_buytype = GameVip_Level1;
		for(iter= AnalyseJson::logOnMsg.vipConfig.begin();	iter!=AnalyseJson::logOnMsg.vipConfig.end(); iter++)
		{
			if((*iter).id == 1002)
			{
				payId = CommonData::getPayIDByPrice(atoi(iter->price.c_str()));
			}
		}
		CppCallJava::toBuyProp(payId, 1);
	}
	else if(pSender == Btn_vip2 || pSender == Img_vip2)
	{
		CommonData::m_buytype = GameVip_Level2;
		for(iter= AnalyseJson::logOnMsg.vipConfig.begin();	iter!=AnalyseJson::logOnMsg.vipConfig.end(); iter++)
		{
			if((*iter).id == 1003)
			{
				payId = CommonData::getPayIDByPrice(atoi(iter->price.c_str()));
			}
		}
		CppCallJava::toBuyProp(payId, 1);
	}
	else if(pSender == Btn_vip3 || pSender == Img_vip3)
	{
		CommonData::m_buytype = GameVip_Level3;
		for(iter= AnalyseJson::logOnMsg.vipConfig.begin();	iter!=AnalyseJson::logOnMsg.vipConfig.end(); iter++)
		{
			if((*iter).id == 1004)
			{
				payId = CommonData::getPayIDByPrice(atoi(iter->price.c_str()));
			}
		}
		CppCallJava::toBuyProp(payId, 1);
	}
}
/***********************************/
/*GameGiftWidget widget*/
/***********************************/
GameGiftWidget::GameGiftWidget():
GameGiftLayout(NULL),
m_isSelf(false)
{

}

GameGiftWidget::~GameGiftWidget()
{
	CC_SAFE_RELEASE_NULL(GameGiftLayout);
}

Layout* GameGiftWidget::getGameGiftLayout(int type) 
{
	if ( !GameGiftLayout )
	{
		GameGiftLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYGIFT_LAYOUT_JSONFILE));
		GameGiftLayout->retain();
		GameGiftLayout->setZOrder( 2 );
	}
	GameGiftLayout->setVisible(true);
	GameGiftLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(GameGiftLayout->getChildByName("m_btu_exit"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameGiftWidget::ExitCallBack));

	UIButton *buyBtn = dynamic_cast<UIButton*>(GameGiftLayout->getChildByName("m_btu_buy"));
	buyBtn->setTouchEnabled(true);
	buyBtn->isEffects( true, nDelayTime1 );
	buyBtn->addReleaseEvent(this, coco_releaseselector(GameGiftWidget::ButtonCallBack));
//	UITextArea*	desArea = dynamic_cast<UITextArea*>(GameGiftLayout->getChildByName("desArea"));
//	UIPanel*	descPanel = dynamic_cast<UIPanel*>(GameGiftLayout->getChildByName("descPanel"));

#ifdef KK_PAY_VERSION 
//	desArea->setVisible(true);
//	descPanel->setVisible(false);
//	char* desc = (char*)CCString::createWithFormat("giftDescribe_%d", CommonData::m_GiftIDBuyNow)->getCString();

//	desArea->setText(CommonData::GetString(desc).c_str());
//	desArea->setFontSize(30);
#else
//	desArea->setVisible(false);
//	descPanel->setVisible(true);

	UILabelBMFont *des_1 = dynamic_cast<UILabelBMFont*>(GameGiftLayout->getChildByName("des_1"));
	UILabelBMFont *des_2 = dynamic_cast<UILabelBMFont*>(GameGiftLayout->getChildByName("des_2"));
	des_1->setText(CommonData::GetString("gift_describe_1").c_str());
	if(type == 1)
	{
		m_isSelf = false;
		int currendId = CommonData::getCurrentPackage();
		char* pSPropName = (char*)CCString::createWithFormat("gift_describe_2_%d", currendId)->getCString();
		des_2->setText( CommonData::GetString(pSPropName).c_str() );
	}
	else if(type == 0)
	{
		m_isSelf = true;
		if(CommonData::m_GiftIDBuyNow > 6 || CommonData::m_GiftIDBuyNow < 4)
		{
			return GameGiftLayout;
		}
		char* pSPropName = (char*)CCString::createWithFormat("gift_describe_2_%d", CommonData::m_GiftIDBuyNow)->getCString();
		des_2->setText( CommonData::GetString(pSPropName).c_str() );
	}
#endif
	

	UIImageView *pLight1 = dynamic_cast<UIImageView*>(GameGiftLayout->getChildByName("Light1"));
	UIImageView *pLight2 = dynamic_cast<UIImageView*>(GameGiftLayout->getChildByName("Light2"));
	pLight1->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCFadeTo::create(1.0f,65),
		CCFadeTo::create(1.0f,255),
		NULL))
		);
	pLight2->runAction(CCRepeatForever::create(
		CCSequence::create(
		CCFadeTo::create(1.0f,255),
		CCFadeTo::create(1.0f,65),
		NULL))
		);

	UIImageView *pImg = dynamic_cast<UIImageView*>(GameGiftLayout->getChildByName("titleImg"));
	UIImageView *pImgContent = dynamic_cast<UIImageView*>(GameGiftLayout->getChildByName("contentArea"));
	switch( CommonData::m_GiftIDBuyNow )
	{
	case 4:
		pImgContent->setTexture("Image/CandyGame/Others/giftContent4.png");
		pImg->setTexture("Image/CandyGame/Others/libao4.png");
		break;
	case 5:
		pImgContent->setTexture("Image/CandyGame/Others/giftContent5.png");
		pImg->setTexture("Image/CandyGame/Others/libao5.png");
		break;
	case 6:
		pImgContent->setTexture("Image/CandyGame/Others/giftContent6.png");
		pImg->setTexture("Image/CandyGame/Others/libao6.png");
		break;
	default:
		break;
	}

	return GameGiftLayout;
}

void GameGiftWidget::ExitCallBack(CCObject *pSender)
{
	if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
		MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );

		if(AnalyseJson::logOnMsg.baseInfo.isVip && AnalyseJson::logOnMsg.baseInfo.today_has_receice == 0)
		{
			MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_REWARDVIPUI );
			AnalyseJson::logOnMsg.baseInfo.today_has_receice = 1;
		}
	}
}

void GameGiftWidget::ButtonCallBack(CCObject *pSender)
{
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
		CandyPay::getInstance()->RequestCandyOrder(CommonData::m_buytype);
		return;
	}
	


#ifdef KK_PAY_VERSION
	int currentId = CommonData::m_GiftIDBuyNow;;

	if(currentId == 4)
	{
		CommonData::m_buytype = GameGift_Level1;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_8, 1);
	}
	else if(currentId == 5)
	{
		CommonData::m_buytype = GameGift_Level2;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_18, 1);
	}
	else if(currentId == 6)
	{
		CommonData::m_buytype = GameGift_Level3;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_28, 1);
	}
	
#else
	int currentId = 0;
	if(m_isSelf == true)
	{
		currentId = CommonData::m_GiftIDBuyNow;
	}
	else
	{
		currentId = CommonData::getCurrentPackage();
	}

	if(currentId == 0)
		return;

	list<UserPackInfoStr >::iterator iter;
	int price = 0;
	for(iter= AnalyseJson::logOnMsg.packInfo.begin();	iter!=AnalyseJson::logOnMsg.packInfo.end(); iter++)
	{
		if(iter->id == currentId)
		{
			price = iter->price;
			break;
		}
	}
	if(currentId == 4)
	{
		CommonData::m_buytype = GameGift_Level1;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_8, 1);
	}
	else if(currentId == 5)
	{
		CommonData::m_buytype = GameGift_Level2;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_18, 1);
	}
	else if(currentId == 6)
	{
		CommonData::m_buytype = GameGift_Level3;
		CppCallJava::toBuyProp(CANDY_BUY_GIFTBIG_NUM_28, 1);
	}
#endif // KK_PAY_VERSION
}






/***********************************/
/*GameRewardWidget widget*/
/***********************************/
GameUnlockLevelWidget::GameUnlockLevelWidget():
m_GameUnlockLevelLayout(NULL)
{

}

GameUnlockLevelWidget::~GameUnlockLevelWidget()
{
	CC_SAFE_RELEASE_NULL(m_GameUnlockLevelLayout);
}

Layout* GameUnlockLevelWidget::getGameUnlockLevelLayout(int level) 
{
	if ( !m_GameUnlockLevelLayout )
	{
		m_GameUnlockLevelLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(UNLOCKLEVEL_LAYOUT_JSONFILE));
		m_GameUnlockLevelLayout->retain();
		m_GameUnlockLevelLayout->setZOrder( 2 );
	}
	m_GameUnlockLevelLayout->setVisible(true);
	m_GameUnlockLevelLayout->setTouchEnable(true);

	//当前解锁关卡
	m_Currentlevel = level;

	list<UserUnlockLevelInfo>::iterator iter;
	for(iter= AnalyseJson::logOnMsg.unlockInfo.begin();	iter!=AnalyseJson::logOnMsg.unlockInfo.end(); iter++)
	{
		if(iter->level == m_Currentlevel)
		{
			break;
		}
	}

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(m_GameUnlockLevelLayout->getChildByName("m_btu_exit"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameUnlockLevelWidget::ExitCallBack));

	UIButton *buyBtn = dynamic_cast<UIButton*>(m_GameUnlockLevelLayout->getChildByName("butbuy"));
	buyBtn->setTouchEnabled(true);
	buyBtn->isEffects( true, nDelayTime1 );
	buyBtn->addReleaseEvent(this, coco_releaseselector(GameUnlockLevelWidget::ButtonCallBack));

	UILabelAtlas *pCurrentLevel = dynamic_cast<UILabelAtlas*>(m_GameUnlockLevelLayout->getChildByName("label_level"));
	pCurrentLevel->setVisible( true );
	pCurrentLevel->setStringValue( CCString::createWithFormat("%d", m_Currentlevel)->getCString() );
	
	UILabel* pStarNum = dynamic_cast<UILabel*>(m_GameUnlockLevelLayout->getChildByName("loadingLabel"));
	pStarNum->setText( CCString::createWithFormat("%d/%d", AnalyseJson::taskTable.curstarnum,iter->needStar)->getCString());

	UILoadingBar* pLoadingBar = dynamic_cast<UILoadingBar*>(m_GameUnlockLevelLayout->getChildByName("progressbar"));
	pLoadingBar->setPercent(100.0f*AnalyseJson::taskTable.curstarnum / iter->needStar);

	UIImageView* pImgUnlock = dynamic_cast<UIImageView*>(m_GameUnlockLevelLayout->getChildByName("ImgUnlock"));
	UIImageView* pImgLock = dynamic_cast<UIImageView*>(m_GameUnlockLevelLayout->getChildByName("ImgLock"));
	if(AnalyseJson::taskTable.curstarnum >= iter->needStar)
	{
		pImgLock->setVisible(false);
		pImgUnlock->setVisible(true);
	}
	else
	{
		pImgLock->setVisible(true);
		pImgUnlock->setVisible(false);
	}

	UILabelAtlas *pPrice = dynamic_cast<UILabelAtlas*>(m_GameUnlockLevelLayout->getChildByName("label_price"));
	int price = (iter->needStar - AnalyseJson::taskTable.curstarnum) * 20;
	if(price >= 200)
	{
		price = 200;
	}
	pPrice->setStringValue( CCString::createWithFormat("%d", price)->getCString());

	return m_GameUnlockLevelLayout;
}

void GameUnlockLevelWidget::ExitCallBack(CCObject *pSender)
{
	if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
}

void GameUnlockLevelWidget::ButtonCallBack(CCObject *pSender)
{
	UIButton *pbtn = dynamic_cast<UIButton*>(pSender);
	pbtn->setTouchEnable(false);

	list<UserUnlockLevelInfo>::iterator iter;
	for(iter= AnalyseJson::logOnMsg.unlockInfo.begin();	iter!=AnalyseJson::logOnMsg.unlockInfo.end(); iter++)
	{
		if(iter->level == m_Currentlevel)
		{
			break;
		}
	}
	if(AnalyseJson::taskTable.curstarnum >= iter->needStar)
	{
		MsgMgr::sendUnlockLevel( AnalyseJson::logOnMsg.baseInfo.id ,0, m_Currentlevel );
	}
	else
	{
		int price = (iter->needStar - AnalyseJson::taskTable.curstarnum) * 20;
		if(price >= 200)
		{
			price = 200;
		}

		if (price > AnalyseJson::logOnMsg.baseInfo.gemNum)
		{
			if(MainMapUiLayer::m_mainmapuilayer)
			{
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
				MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_BUYGEM_LIST );
			}
		}
		else
		{
			MsgMgr::sendUnlockLevel( AnalyseJson::logOnMsg.baseInfo.id ,price, m_Currentlevel );
		}
	}
}


/***********************************/
/*Game signin widget*/
/***********************************/
GameSignInWidget::GameSignInWidget( void ):
GameSignInLayout(NULL)
{

}

GameSignInWidget::~GameSignInWidget( void )
{
	CC_SAFE_RELEASE_NULL( GameSignInLayout );
}

Layout* GameSignInWidget::getSignInLayout()
{
	if ( !GameSignInLayout )
	{
		GameSignInLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(SIGNIN_LAYOUT_JSONFILE));
		GameSignInLayout->retain();
		GameSignInLayout->setZOrder( 2 );

	}

	GameSignInLayout->setVisible(true);
	GameSignInLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(GameSignInLayout->getChildByName("m_btu_exit"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameSignInWidget::ExitCallBack));

	UIButton *buyBtn = dynamic_cast<UIButton*>(GameSignInLayout->getChildByName("BtnSignIn"));
	buyBtn->isEffects( true );
	buyBtn->addReleaseEvent(this, coco_releaseselector(GameSignInWidget::ButtonCallBack));

	// 设置到当前可签位置
	UIImageView *pSignInZhuanpan = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName("ImageZP"));
	pSignInZhuanpan->setRotation( - AnalyseJson::logOnMsg.baseInfo.hasSignInDay*24 );

	// 设置当前可签奖励信息
	setSignInRawardInfo( AnalyseJson::logOnMsg.baseInfo.hasSignInDay+1 );

	// 设置签到转盘数据
	updataSignInfo();

	return GameSignInLayout;
}

void GameSignInWidget::ButtonCallBack( CCObject *pSender )
{
	UIButton* pBtn = (UIButton*)pSender;
	int nTag = pBtn->getTag();

	switch( nTag)
	{
	case TAG_SIGNSTATE_QD:
		{

			UIImageView *pSignInZhuanpan = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName("ImageZP"));
			float nCurRotation = - AnalyseJson::logOnMsg.baseInfo.practicalSignInDay * 24;

			pSignInZhuanpan->runAction( CCRotateTo::create(0.2f, nCurRotation ));

			MsgMgr::sendSignInMsg( AnalyseJson::logOnMsg.baseInfo.id );

			AnalyseJson::logOnMsg.baseInfo.hasSignInDay++;

			// 播放特效
			UIImageView* pCurSignTag = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( "ImageCurSign"));
			CCPoint pos = pCurSignTag->getParent()->convertToWorldSpace(pCurSignTag->getPosition());
			CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y), MainMapUiLayer::m_mainmapuilayer );
			updataSignInfo();
		}
		break;
	case TAG_SIGNSTATE_BQ:
		{
			// 是VIP 并有补签卡
			if (AnalyseJson::logOnMsg.baseInfo.isVip && AnalyseJson::logOnMsg.baseInfo.RetroactiveCardNum )
			{
				// 发送补签
				MsgMgr::sendSignInMsg( AnalyseJson::logOnMsg.baseInfo.id, 1 );

				AnalyseJson::logOnMsg.baseInfo.hasSignInDay++;

				// 播放特效
				UIImageView* pCurSignTag = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( "ImageCurSign"));
				CCPoint pos = pCurSignTag->getParent()->convertToWorldSpace(pCurSignTag->getPosition());
				CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, ccp(pos.x, pos.y), MainMapUiLayer::m_mainmapuilayer );

				updataSignInfo();
			}
			// 不可补签
			else
			{
				// 非VIP 进行购买VIP
				if ( !AnalyseJson::logOnMsg.baseInfo.isVip )
				{
					MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetDirect();
					MainMapUiLayer::m_mainmapuilayer->showMapWidget( MAP_WIDGET_VIP_DLG );
				}
				// 无补签卡进行购买
				else if ( !AnalyseJson::logOnMsg.baseInfo.RetroactiveCardNum )
				{
					CommonData::m_buytype = CANDY_PROP_RETROACTIVE;
					CppCallJava::toBuyProp( CommonData::getPayIDByPrice( AnalyseJson::logOnMsg.baseInfo.RetroactiveCatdPrice ), 1 );
				}
			}
		}
		break;
	default:
		break;
	}

	setSignInRawardInfo( AnalyseJson::logOnMsg.baseInfo.hasSignInDay+1 );
	updataSignInfo();
}

void GameSignInWidget::ExitCallBack( CCObject *pSender )
{
	MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
	MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
}

void GameSignInWidget::BtnSignInItemCallBack( CCObject* pSender )
{
	UIImageView* nSignInItem = (UIImageView*)pSender;
	int nIndex = nSignInItem->getTag();

	for (int i = 1; i<=15; i++)
	{
		UIImageView *pSignInItem = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( CCString::createWithFormat("ImgSignInDay%d", i)->getCString() ));
		pSignInItem->setTouchEnabled( true );
		pSignInItem->setTag( i );
		pSignInItem->addReleaseEvent(this, coco_releaseselector(GameSignInWidget::BtnSignInItemCallBack));

		if ( i == nIndex )
			pSignInItem->setTexture("res_signin/ImgSignInXZ.png",UI_TEX_TYPE_PLIST );
		else if ( i <= AnalyseJson::logOnMsg.baseInfo.hasSignInDay )
			pSignInItem->setTexture("res_signin/ImgSignInYQD.png",UI_TEX_TYPE_PLIST );
		else
			pSignInItem->setTexture("res_signin/BtnSignInWQD.png",UI_TEX_TYPE_PLIST );

	}

	setSignInRawardInfo( nIndex );	
}

void GameSignInWidget::setSignInRawardInfo( int day )
{

	for (int i=1; i<=3; i++)
	{
		UIImageView *pSignRawardInfoICO = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( CCString::createWithFormat("ImgSignInGoods_%d", i)->getCString() ));
		pSignRawardInfoICO->setVisible( false );
	}

	list<SystemSignInConfig>::iterator item = AnalyseJson::signInConfigStr.signInConfig.begin();
	for (; item!= AnalyseJson::signInConfigStr.signInConfig.end(); item++)
	{
		if (item->SignInDay == day)
		{
			list<SignReward>::iterator nDayItem = item->signReward.begin();
			for (int j = 1; nDayItem!=item->signReward.end();nDayItem++, j++)
			{
				UIImageView *pSignRawardInfoICO = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( CCString::createWithFormat("ImgSignInGoods_%d", j)->getCString() ));
				UILabelAtlas *pSignRawardInfoNUM = dynamic_cast<UILabelAtlas*>(GameSignInLayout->getChildByName( CCString::createWithFormat("LabelGoodsNum_%d", j)->getCString() ));
				pSignRawardInfoICO->setVisible( true );
				pSignRawardInfoNUM->setStringValue( CCString::createWithFormat("%d", nDayItem->propnum)->getCString() );

				//1:糖果币；2:宝石；3:生命
				switch( nDayItem->proptype )
				{
					//　
				case 1:
					{
						pSignRawardInfoICO->setTexture("Others/ImgCandyICO.png",UI_TEX_TYPE_PLIST );
					}
					break;
					//　
				case 2:
					{
						pSignRawardInfoICO->setTexture("Others/ImgGemICO.png",UI_TEX_TYPE_PLIST );
					}
					break;
					//　
				case 3:
					{
						pSignRawardInfoICO->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
					}
					break;
				}

			}
		}
	}
}

int GameSignInWidget::getCurSignStart( void )
{
	int ret = 0;
	//　可签到
	if ( AnalyseJson::logOnMsg.baseInfo.hasSignInDay < AnalyseJson::logOnMsg.baseInfo.practicalSignInDay && AnalyseJson::logOnMsg.baseInfo.hasSignInDay <= AnalyseJson::logOnMsg.baseInfo.MaxSignInDay )
	{
		ret = TAG_SIGNSTATE_QD;
	}
	//　可补签
	else if ( AnalyseJson::logOnMsg.baseInfo.hasSignInDay == AnalyseJson::logOnMsg.baseInfo.practicalSignInDay 
		&& AnalyseJson::logOnMsg.baseInfo.hasSignInDay < AnalyseJson::logOnMsg.baseInfo.MaxSignInDay 
		&& 0 == AnalyseJson::logOnMsg.baseInfo.IsRetroactive )
	{
		ret = TAG_SIGNSTATE_BQ;
	}
	else
	{
		ret = TAG_SIGNSTATE_DISABLED;
	}

	return ret;
}

void GameSignInWidget::updataSignInfo( void )
{
	UIButton *buyBtn = dynamic_cast<UIButton*>(GameSignInLayout->getChildByName("BtnSignIn"));

	// 设置签到按钮事件
	switch( getCurSignStart() )
	{
	case TAG_SIGNSTATE_DISABLED:
		{
			buyBtn->setTouchEnabled(false);
			buyBtn->setVisible( false );
		}
		break;
	case TAG_SIGNSTATE_QD:
		{
			UIImageView *pSignBtn = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName("ImgSignInBtn"));
			pSignBtn->setTexture( "res_signin/BtnSignInTitle.png", UI_TEX_TYPE_PLIST );

			buyBtn->setTag( TAG_SIGNSTATE_QD );
			buyBtn->setTouchEnabled(true);
			buyBtn->setVisible( true );
		}
		break;
	case TAG_SIGNSTATE_BQ:
		{
			UIImageView *pSignBtn = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName("ImgSignInBtn"));
			pSignBtn->setTexture( "res_signin/ImgBqBtn.png", UI_TEX_TYPE_PLIST );

			buyBtn->setTag( TAG_SIGNSTATE_BQ );
			buyBtn->setTouchEnabled(true);
			buyBtn->setVisible( true );
		}
		break;
	}

	for (int i = 1; i<=15; i++)
	{
		UIImageView *pSignInItem = dynamic_cast<UIImageView*>(GameSignInLayout->getChildByName( CCString::createWithFormat("ImgSignInDay%d", i)->getCString() ));
		pSignInItem->setTouchEnabled( true );
		pSignInItem->setTag( i );
		pSignInItem->addReleaseEvent(this, coco_releaseselector(GameSignInWidget::BtnSignInItemCallBack));

		UILabelAtlas *pLableNumItem = dynamic_cast<UILabelAtlas*>(GameSignInLayout->getChildByName( CCString::createWithFormat("LabelSignNum_%d", i)->getCString() ));

		//　已完成签到
		if ( i <= AnalyseJson::logOnMsg.baseInfo.hasSignInDay )
		{
			const char* pLableNum = CCString::createWithFormat("%d", i)->getCString();
			pLableNumItem->setProperty( pLableNum, "Image/MainMapUi/Tools/NumLabel/StageNumLabel.png",38, 47, "0", true);  
			pLableNumItem->setStringValue( pLableNum );
			pLableNumItem->setScale( 0.8f );
			pSignInItem->setTexture("res_signin/ImgSignInYQD.png",UI_TEX_TYPE_PLIST );
		}
		else
		{
			pLableNumItem->setProperty(CCString::createWithFormat("%d", i)->getCString() , "Image/MainMapUi/Tools/NumLabel/NumLabel5.png",22, 26, "0", true);  
			const char* pLableNum = CCString::createWithFormat("%d", i)->getCString();

			pLableNumItem->setStringValue( pLableNum );
			pLableNumItem->setScale( 1.0f );
			pSignInItem->setTexture("res_signin/BtnSignInWQD.png",UI_TEX_TYPE_PLIST );
		}
	}

	char* pSignInPromptInfo = (char*)CommonData::GetString( "app_signintime_str" ).c_str();
	UILabel* pSignInTimeInfo = dynamic_cast<UILabel*>(GameSignInLayout->getChildByName("LabelSignInPrmpt"));
	pSignInTimeInfo->setText( CCString::createWithFormat(pSignInPromptInfo, 15 - AnalyseJson::logOnMsg.baseInfo.MaxSignInDay)->getCString());

}



/***********************************/
/*GameRankWidget widget*/
/***********************************/
GameRankWidget::GameRankWidget():
GameRankLayout(NULL)
{

}

GameRankWidget::~GameRankWidget()
{
	CC_SAFE_RELEASE_NULL(GameRankLayout);
}

Layout* GameRankWidget::getGameRankLayout(int type) 
{
	if ( !GameRankLayout )
	{
		GameRankLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYWORLDRANK_LAYOUT_JSONFILE));
		GameRankLayout->retain();
		GameRankLayout->setZOrder( 2 );
	}
	GameRankLayout->setVisible(true);
	GameRankLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *returnBtn = dynamic_cast<UIButton*>(GameRankLayout->getChildByName("m_btu_exit"));
	returnBtn->setTouchEnabled(true);
	returnBtn->isEffects( true, nDelayTime1 );
	returnBtn->addReleaseEvent(this, coco_releaseselector(GameRankWidget::ExitCallBack));

	UIImageView* pLable1 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("friend_title"));
	UIImageView* pLable2 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("world_title"));

	pLable1->setTouchEnable( true );
	pLable2->setTouchEnable( true );

	pLable1->setTag( 1 );
	pLable2->setTag( 2 );

	pLable1->addReleaseEvent(this, coco_releaseselector(GameRankWidget::ButtonSelLabel));
	pLable2->addReleaseEvent(this, coco_releaseselector(GameRankWidget::ButtonSelLabel));


	UIScrollView* pWorldlistView = dynamic_cast<UIScrollView*>(GameRankLayout->getChildByName( "world_list" ));
	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(GameRankLayout->getChildByName( "friend_list" ));
	pWorldlistView->removeAllChildrenAndCleanUp( true );
	pFriendlistView->removeAllChildrenAndCleanUp( true );

	setRankLabel(1);

	return GameRankLayout;
}

void GameRankWidget::ExitCallBack(CCObject *pSender)
{
	if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}
}

void GameRankWidget::ButtonSelLabel(CCObject *pSender)
{
	UIWidget* pItem = (UIWidget*)pSender;
	int tag = pItem->getTag();

	char* pItemName =(char*)pItem->getName();

	UIImageView* pLableSel = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("title_select"));
	UIImageView* pLable1 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("friend_title"));
	UIImageView* pLable2 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("world_title"));


	switch ( tag )
	{
	case 1:
		{
			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			pLable1->setTouchEnable(false);
			pLable2->setTouchEnable(true);
			setRankLabel( 1 );
		}
		break;

	case 2:
		{
			if ( 0 == ccpDistance(pLableSel->getPosition(), ccp(pItem->getPosition().x, pLableSel->getPosition().y) ))
				break;

			pLable1->setTouchEnable(true);
			pLable2->setTouchEnable(false);
			setRankLabel( 2 );
		}
		break;

	default:
		break;
	}

}

void GameRankWidget::setRankLabel( int index )
{
	UIPanel* pPanelLable1 = dynamic_cast<UIPanel*>(GameRankLayout->getChildByName("friend_panel"));
	UIPanel* pPanelLable2 = dynamic_cast<UIPanel*>(GameRankLayout->getChildByName("world_panel"));

	UIImageView* pLableSel = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("title_select"));

	switch ( index )
	{
	case 1:
		{
			UIImageView* pLable1 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("friend_title"));
			pLableSel->runAction( CCMoveTo::create( 0.1f, ccp(pLable1->getPosition().x, pLableSel->getPosition().y)));

			pPanelLable1->setVisible( true );
			pPanelLable1->setTouchEnable(true,true);

			pPanelLable2->setVisible( false );
			pPanelLable2->setTouchEnable(false,true);

			AddFriendListContent();
		}
		break;

	case 2:
		{
			UIImageView* pLable2 = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName("world_title"));
			pLableSel->runAction( CCMoveTo::create( 0.1f, ccp(pLable2->getPosition().x, pLableSel->getPosition().y)));

			pPanelLable1->setVisible( false );
			pPanelLable1->setTouchEnable(false,true);

			pPanelLable2->setVisible( true );
			pPanelLable2->setTouchEnable(true,true);

			AddWorldFriendListContent();
		}
		break;
	}
}

void GameRankWidget::AddWorldFriendListContent()
{
	UIScrollView* pWorldFriendlistView = dynamic_cast<UIScrollView*>(GameRankLayout->getChildByName( "world_list" ));
	pWorldFriendlistView->removeAllChildrenAndCleanUp( true );
	pWorldFriendlistView->setTouchEnable( true );

	// 计算出scrollView的高
	float ClipWidth = 0; 
	float ClipHeight = 0;

	CCSize scrollSize = pWorldFriendlistView->getContentSize();
	ClipWidth = scrollSize.width;

	int nFriendLen = AnalyseJson::worldFriendInfoMsg.friendInfo.size();
	if ( nFriendLen )
		ClipHeight = ( nFriendLen ) * ( 132 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pWorldFriendlistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	
	AnalyseJson::worldFriendInfoMsg.friendInfo.sort(Cmpare());
	


	UIImageView* pnothing = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName( "img_nothing" ));
	if ( 0== nFriendLen)
	{
		pnothing->setVisible( true );
	}
	else
	{
		pnothing->setVisible( false );
	}


	if ( !nFriendLen )
		return;


	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;

	std::list<UserFriendInfoStr>::iterator pBegin = AnalyseJson::worldFriendInfoMsg.friendInfo.begin();
	std::list<UserFriendInfoStr>::iterator pEnd = AnalyseJson::worldFriendInfoMsg.friendInfo.end();

	CCPoint itemPoint;
	itemPoint.x = scrollSize.width/2;
	itemPoint.y = ClipHeight - 132/2;
	int rank = 0;
	for( ; pBegin != pEnd ; ++pBegin)
	{

		const char* pItemName = CCString::createWithFormat("FriendItem%d", pBegin->id )->getCString();
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setName( pItemName );
		pItemImg->setTexture("Image/MainMapUi/editboxBG.png");
		pItemImg->setPosition(ccp(itemPoint.x, itemPoint.y));
		itemPoint.y -= ( 132 );
		pWorldFriendlistView->addChild( pItemImg );

		rank++;
		if(rank <= 3)
		{
			UIImageView* pRankImg = UIImageView::create();
			pRankImg->setTexture( CCString::createWithFormat("Image/CandyGame/Others/ImageRank%d.png",rank)->getCString());
			pRankImg->setPosition(ccp(-226+80-105, 0));
			pItemImg->addChild( pRankImg);	
		}
		else
		{
			UILabelAtlas* pRankLabel = UILabelAtlas::create();
			pRankLabel->setProperty( CCString::createWithFormat("%d",rank)->getCString() , "Image/CandyGame/Others/NumLabel.png",44, 48, "0");  
			pRankLabel->setPosition(ccp(-226+80-105, 0));
			pItemImg->addChild( pRankLabel );
		}

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setPosition(ccp(-226+80, 0));
		pHeadbgImg->setTag( pBegin->id );
		pItemImg->addChild( pHeadbgImg);

		UIImageView* pHeadImg = UIImageView::create();	
		std::string headPath = CommonData::getHeadPathForUrl( pBegin->headPicUr );
		pHeadImg->setTexture( headPath.c_str() );	
		pHeadImg->setPosition(ccp(0, 2));
		pHeadbgImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setPosition(ccp(0, 0));
		pHeadbgImg->addChild( pHeadKImg);

		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == pBegin->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );
		pSexbgImg->setPosition(ccp(44, -37));
		pHeadbgImg->addChild( pSexbgImg);

		UILabel* pNameBg = UILabel::create();
		pNameBg->setPosition( ccp(-146+80, -19) );
		pNameBg->setColor( ccc3(100,100,100));
		pNameBg->setFontSize(35);
		pNameBg->setAnchorPoint( ccp(0.0f, 0.5f));
		pNameBg->setText( (const char *)pBegin->nickName.c_str() );
		pItemImg->addChild( pNameBg );	

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-147+80, -18) );
		pName->setColor( ccc3(255,255,255));
		pName->setFontSize(35);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)pBegin->nickName.c_str() );
		pItemImg->addChild( pName );

		UILabel* plevel = UILabel::create();
		std::string levelstr = CommonData::GetString( "app_friendlevel_str" );
		plevel->setPosition( ccp(-145+80, 24) );
		plevel->setColor( ccc3(107,53,27));
		plevel->setFontSize(30);
		plevel->setAnchorPoint( ccp(0.0f, 0.5f));
		plevel->setText( CCString::createWithFormat( levelstr.c_str(), pBegin->level)->getCString());
		pItemImg->addChild( plevel );

		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setPosition(ccp(0, -62));
		pItemImg->addChild( pDivideline);
	}

}

void GameRankWidget::AddFriendListContent()
{
	UIScrollView* pFriendlistView = dynamic_cast<UIScrollView*>(GameRankLayout->getChildByName( "friend_list" ));
	pFriendlistView->removeAllChildrenAndCleanUp( true );
	pFriendlistView->setTouchEnable( true );

	// 计算出scrollView的高
	float ClipWidth = 0; 
	float ClipHeight = 0;

	CCSize scrollSize = pFriendlistView->getContentSize();
	ClipWidth = scrollSize.width;

	UserFriendInfoStr myself;
	myself.id = AnalyseJson::logOnMsg.baseInfo.id;
	myself.gender = AnalyseJson::logOnMsg.baseInfo.gender;
	myself.nickName = AnalyseJson::logOnMsg.baseInfo.nickName;
	myself.headPicUr = AnalyseJson::logOnMsg.baseInfo.headPicUrl;
	myself.level = CommonData::getMaxLevel();

	std::list<UserFriendInfoStr> FriendRankInfo;
	std::copy(AnalyseJson::friendInfoMsg.friendInfo.begin(),AnalyseJson::friendInfoMsg.friendInfo.end(),std::back_inserter(FriendRankInfo));
	FriendRankInfo.push_back(myself);

	int nFriendLen = FriendRankInfo.size();
	if ( nFriendLen )
		ClipHeight = ( nFriendLen ) * ( 132 );

	if (ClipHeight < scrollSize.height)
		ClipHeight = scrollSize.height;

	pFriendlistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));

	FriendRankInfo.sort(Cmpare());


	UIImageView* pnothing = dynamic_cast<UIImageView*>(GameRankLayout->getChildByName( "img_nothing" ));
	if ( 0== nFriendLen)
	{
		pnothing->setVisible( true );
	}
	else
	{
		pnothing->setVisible( false );
	}


	if ( !nFriendLen )
		return;


	float nDelayTime1 = 0.48f;
	float nDelayTime2 = 0.082f;

	std::list<UserFriendInfoStr>::iterator pBegin = FriendRankInfo.begin();
	std::list<UserFriendInfoStr>::iterator pEnd = FriendRankInfo.end();

	CCPoint itemPoint;
	itemPoint.x = scrollSize.width/2;
	itemPoint.y = ClipHeight - 132/2;
	int rank = 0;
	for( ; pBegin != pEnd ; ++pBegin)
	{

		const char* pItemName = CCString::createWithFormat("FriendItem%d", pBegin->id )->getCString();
		UIImageView* pItemImg = UIImageView::create();
		pItemImg->setName( pItemName );
		pItemImg->setTexture("Image/MainMapUi/editboxBG.png");
		pItemImg->setPosition(ccp(itemPoint.x, itemPoint.y));
		itemPoint.y -= ( 132 );
		pFriendlistView->addChild( pItemImg );

		rank++;
		if(rank <= 3)
		{
			UIImageView* pRankImg = UIImageView::create();
			pRankImg->setTexture( CCString::createWithFormat("Image/CandyGame/Others/ImageRank%d.png",rank)->getCString());
			pRankImg->setPosition(ccp(-226+80-105, 0));
			pItemImg->addChild( pRankImg);	
		}
		else
		{
			UILabelAtlas* pRankLabel = UILabelAtlas::create();
			pRankLabel->setProperty( CCString::createWithFormat("%d",rank)->getCString() , "Image/CandyGame/Others/NumLabel.png",44, 48, "0");  
			pRankLabel->setPosition(ccp(-226+80-105, 0));
			pItemImg->addChild( pRankLabel );
		}

		UIImageView* pHeadbgImg = UIImageView::create();
		pHeadbgImg->setTexture( "Image/MainMapUi/m_img_headbg.png" );
		pHeadbgImg->setPosition(ccp(-226+80, 0));
		pHeadbgImg->setTag( pBegin->id );
		pItemImg->addChild( pHeadbgImg);

		UIImageView* pHeadImg = UIImageView::create();	
		std::string headPath = CommonData::getHeadPathForUrl( pBegin->headPicUr );
		pHeadImg->setTexture( headPath.c_str() );	
		pHeadImg->setPosition(ccp(0, 2));
		pHeadbgImg->addChild( pHeadImg);

		UIImageView* pHeadKImg = UIImageView::create();
		pHeadKImg->setTexture( "Image/MainMapUi/headframe.png" );
		pHeadKImg->setPosition(ccp(0, 0));
		pHeadbgImg->addChild( pHeadKImg);

		// Setting friend Sex  1: girl  0: boy
		UIImageView* pSexbgImg = UIImageView::create();
		if ( 1 == pBegin->gender )
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
		else
			pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );
		pSexbgImg->setPosition(ccp(44, -37));
		pHeadbgImg->addChild( pSexbgImg);

		UILabel* pNameBg = UILabel::create();
		pNameBg->setPosition( ccp(-146+80, -19) );
		pNameBg->setColor( ccc3(100,100,100));
		pNameBg->setFontSize(35);
		pNameBg->setAnchorPoint( ccp(0.0f, 0.5f));
		pNameBg->setText( (const char *)pBegin->nickName.c_str() );
		pItemImg->addChild( pNameBg );	

		UILabel* pName = UILabel::create();
		pName->setPosition( ccp(-147+80, -18) );
		pName->setColor( ccc3(255,255,255));
		pName->setFontSize(35);
		pName->setAnchorPoint( ccp(0.0f, 0.5f));
		pName->setText( (const char *)pBegin->nickName.c_str() );
		pItemImg->addChild( pName );

		UILabel* plevel = UILabel::create();
		std::string levelstr = CommonData::GetString( "app_friendlevel_str" );
		plevel->setPosition( ccp(-145+80, 24) );
		plevel->setColor( ccc3(107,53,27));
		plevel->setFontSize(30);
		plevel->setAnchorPoint( ccp(0.0f, 0.5f));
		plevel->setText( CCString::createWithFormat( levelstr.c_str(), pBegin->level)->getCString());
		pItemImg->addChild( plevel );

		if(pBegin->id != AnalyseJson::logOnMsg.baseInfo.id)
		{
			int offset = 50;
			UIButton* pSloveImg = UIButton::create();
			pSloveImg->setNormalTexture( "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			pSloveImg->setPressedTexture(  "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			pSloveImg->setDisabledTexture (  "res_common/ImgCandymoney.png", UI_TEX_TYPE_PLIST );
			char *pHandselLifeBut = (char *)CCString::createWithFormat( "HandselLife%d", pBegin->id )->getCString();
			pSloveImg->setName( pHandselLifeBut );
			pSloveImg->setTag( pBegin->id );
			pSloveImg->setTouchEnable( true );
			pSloveImg->isEffects( true, nDelayTime1 );
			pSloveImg->setPosition(ccp(289 - offset, 5));
			pSloveImg->addReleaseEvent(this, coco_releaseselector(GameRankWidget::ButtonSendCandy)); 
			pItemImg->addChild( pSloveImg );

			// 已赠送
			if ( 0 < pBegin->click_timestamp )
			{
				pSloveImg->disable( true );

				UILabel* pTime = UILabel::create();
				pTime->setColor( ccc3(255,255,255));
				pTime->setFontSize(20);
				pTime->setAnchorPoint( ccp(0.5f, 0.5f));
				pTime->setText( CommonData::GetString( "app_handselover_str" ).c_str() );
				pSloveImg->addChild( pTime );
			}
		}
		UIImageView* pDivideline = UIImageView::create();
		pDivideline->setTexture( "Image/MainMapUi/buyItem/line_divdeline.png" );
		pDivideline->setPosition(ccp(0, -62));
		pItemImg->addChild( pDivideline);
	}

}

void GameRankWidget::ButtonSendCandy( CCObject *pSender )
{
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

			UILabel* pTime = UILabel::create();
			pTime->setColor( ccc3(255,255,255));
			pTime->setFontSize(20);
			pTime->setAnchorPoint( ccp(0.5f, 0.5f));
			pTime->setText( CommonData::GetString( "app_handselover_str" ).c_str() );
			item->addChild( pTime );

			MsgMgr::sendHandselLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, p->id);
			break;
		}
		p++;
	}
}



/***********************************/
/*GameRoulette widget*/
/***********************************/
GameRouletteWidget::GameRouletteWidget():
	m_GameRouletteLayout(NULL),
	m_RewardType(0)
{
	m_RemindDes = UILabel::create();
	m_RemindDes->retain();
}

GameRouletteWidget::~GameRouletteWidget()
{
	CC_SAFE_RELEASE_NULL(m_GameRouletteLayout);
	CC_SAFE_RELEASE_NULL(m_RemindDes);
}

Layout* GameRouletteWidget::getGameRouletteLayout(int level) 
{
	if ( !m_GameRouletteLayout )
	{
		m_GameRouletteLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYWROULETTE_LAYOUT_JSONFILE));
		m_GameRouletteLayout->retain();
		m_GameRouletteLayout->setZOrder( 2 );
	}
	m_GameRouletteLayout->setVisible(true);
	m_GameRouletteLayout->setTouchEnable(true);


	UIButton *m_pRouletteStartBtn = dynamic_cast<UIButton*>(m_GameRouletteLayout->getChildByName("Start_btn"));
	m_pRouletteStartBtn->active();
	m_pRouletteStartBtn->setTouchEnable(true);
	m_pRouletteStartBtn->addReleaseEvent(this,coco_releaseselector(GameRouletteWidget::ButtonCallBack));

	UIButton *m_pRouletteExitBtn = dynamic_cast<UIButton*>(m_GameRouletteLayout->getChildByName("m_btu_exit"));
	m_pRouletteExitBtn->setTouchEnable(true);
	m_pRouletteExitBtn->addReleaseEvent(this,coco_releaseselector(GameRouletteWidget::ExitCallBack));


	UIImageView* pRouletteImg =  dynamic_cast<UIImageView*>(m_GameRouletteLayout->getChildByName("Roulette_content"));
	pRouletteImg->stopAllActions();

	//宝石数量
	UILabelAtlas* baoshiIco = dynamic_cast<UILabelAtlas*>(m_GameRouletteLayout->getChildByName("BaoshiNum"));
	baoshiIco->setStringValue(CCString::createWithFormat("%d",AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString());


	m_RewardType = 0;

	return m_GameRouletteLayout;
}

void GameRouletteWidget::ExitCallBack(CCObject *pSender)
{
	/*if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	}*/
	MainMapUiLayer::m_mainmapuilayer->PlayEffect( MUSIC_ITEM_BUTTON_E );
	MainMapUiLayer::m_mainmapuilayer->QuitMapWidget();
	
}

void GameRouletteWidget::ButtonCallBack(CCObject *pSender)
{
	MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	const char* pPromptStr = NULL;
	std::string strTemp;

 	if( AnalyseJson::logOnMsg.baseInfo.candyNum >= AnalyseJson::logOnMsg.baseInfo.Roulette_UseCandy 
 		&& AnalyseJson::logOnMsg.baseInfo.today_Roulette_num > 0
 		)
 	{
 		UIButton *pExitBtn = dynamic_cast<UIButton*>(m_GameRouletteLayout->getChildByName("m_btu_exit"));
 		pExitBtn->setTouchEnable(false);
 
 		CommonData::setButtonTouchEnable( pSender, false);
 		UIButton *pBtn = (UIButton*)pSender;
 		pBtn->disable();
 		
 		AnalyseJson::logOnMsg.baseInfo.today_Roulette_num--;
 
 		UIImageView* zhuanpan = dynamic_cast<UIImageView*>(m_GameRouletteLayout->getChildByName("Roulette_content"));
 		int angle = zhuanpan->getRotation();
 		float m_nRouletteNumRotate = 360 *10 - abs(angle%360) + AdjustRouletteProbability();
 
 		CCActionInterval*  rouletteAction = CCRotateBy::create(5, m_nRouletteNumRotate);
 		CCActionInterval*  rouletteEase = CCEaseInOut::create(rouletteAction, 5.0f);
 
 		UIImageView* pRouletteImg =  dynamic_cast<UIImageView*>(m_GameRouletteLayout->getChildByName("Roulette_content"));
 		pRouletteImg->stopAllActions();
 		pRouletteImg->runAction(CCSequence::create(
 			rouletteEase,
 			CCCallFunc::create(this, callfunc_selector(GameRouletteWidget::RewardCallBack)),
 			NULL));
 
 
 		MainMap::m_mainmap->PlayEffect(MUSIC_ITEM_ROULETTE_E);
 
 	}
 	else
 	{
 		m_RemindDes->removeFromParent();
 		m_GameRouletteLayout->addChild( m_RemindDes );
 		if(AnalyseJson::logOnMsg.baseInfo.candyNum < AnalyseJson::logOnMsg.baseInfo.Roulette_UseCandy )
 		{
 			pPromptStr = CommonData::GetString( "app_shop_no_candy_str" ).c_str();   
 		}
 		else if(AnalyseJson::logOnMsg.baseInfo.today_Roulette_num == 0)
 		{
 			pPromptStr = CommonData::GetString( "app_roulette_no_num_str" ).c_str();   
 		}
 		m_RemindDes->setText(pPromptStr);
 		m_RemindDes->setZOrder( 1000 );
 		m_RemindDes->setOpacity(255);
 		//m_RemindDes->setFontName("黑体");
 		m_RemindDes->setFontSize(40);
 		CCPoint pos = ccp(size.width*0.5,size.height*0.5);
 		m_RemindDes->setPosition(pos);
 		m_RemindDes->runAction(CCSequence::create(
 			CCEaseElasticOut::create((CCActionInterval*)CCMoveTo::create(1.5f, ccpAdd(pos, ccp(0, 100)) ),0.3f ),
 			CCSpawn::create(CCMoveTo::create(0.8f, ccpAdd(pos, ccp(0, 150))),CCFadeOut::create(0.8f),NULL),
 			NULL));
 
 		return;
 	}
}

void GameRouletteWidget::RewardCallBack(void)
{
	// 	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	// 	const char* pPromptStr = NULL;
	// 	
	// 
	// 	m_RemindDes->removeFromParent();
	// 	m_GameRouletteLayout->addChild( m_RemindDes );
	// 
	// 	pPromptStr = CCString::createWithFormat(CommonData::GetString( CCString::createWithFormat("app_roulette_Reward_%d",m_RewardType)->getCString() ).c_str())->getCString();   
	// 	m_RemindDes->setText(pPromptStr);
	// 	m_RemindDes->setZOrder( 1000 );
	// 	m_RemindDes->setOpacity(255);
	// 	m_RemindDes->setFontName("黑体");
	// 	m_RemindDes->setFontSize(40);
	// 	CCPoint pos = ccp(size.width*0.5,size.height*0.5);
	// 	m_RemindDes->setPosition(pos);
	// 	m_RemindDes->runAction(CCSequence::create(
	// 		CCEaseElasticOut::create((CCActionInterval*)CCMoveTo::create(1.5f, ccpAdd(pos, ccp(0, 100)) ),0.3f ),
	// 		CCSpawn::create(CCMoveTo::create(0.8f, ccpAdd(pos, ccp(0, 150))),CCFadeOut::create(0.8f),NULL),
	// 		CCCallFunc::create(this, callfunc_selector(GameRouletteWidget::ExitCallBack1)),
	// 		NULL));

	Layout* layout = CommonWidgt::getGiftRewardUI(WIDGET_TYPE_MAP, MAP_WIDGET_ROULETTE_DLG,m_RewardType);

	MainMapUiLayer::m_mainmapuilayer->getWidgetUILayer()->addWidget ( layout );
	MsgMgr::sendRouletteReward( AnalyseJson::logOnMsg.baseInfo.id, m_RewardType);


	switch(m_RewardType)
	{
	case 1:
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 1;
		CommonData::setLifeInfo();
		break;
	case 2:
		CommonData::changePropNum(CANDY_PROP_OUT_COLORFULL,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_COLORFULL);
		break;
	case 3:
		CommonData::changePropNum(CANDY_PROP_IN_RESORT,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_RESORT);
		break;
	case 5:
		AnalyseJson::logOnMsg.lifeInfo.lifeNum += 5;
		CommonData::setLifeInfo();
		break;
	case 6:
		CommonData::changePropNum(CANDY_PROP_OUT_BOMBNEW,1);
		CommonData::setPropInfoById(CANDY_PROP_OUT_BOMBNEW);
		break;
	case 7:
		CommonData::changePropNum(CANDY_PROP_IN_HAMMER,1);
		CommonData::setPropInfoById(CANDY_PROP_IN_HAMMER);
		break;
	default:
		return;
	}
	//宝石数量-2000
	AnalyseJson::logOnMsg.baseInfo.candyNum -= 2000;
	CommonData::setCandyNum();
	UILabelAtlas* baoshiIco = dynamic_cast<UILabelAtlas*>(m_GameRouletteLayout->getChildByName("BaoshiNum"));
	baoshiIco->setStringValue(CCString::createWithFormat("%d",AnalyseJson::logOnMsg.baseInfo.candyNum)->getCString());

}
void GameRouletteWidget::ExitCallBack1(void)
{
	if(MainMapUiLayer::m_mainmapuilayer)
	{
		MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
	}
}

int GameRouletteWidget::AdjustRouletteProbability(void)
{
	AnalyseJson::setForRoulettePercent();

	int randNum = rand()%100;
	int ratio = 0;
	
	for (int i = 0; i < AnalyseJson::RouleteRatioVec.size(); ++i)
	{
		if (AnalyseJson::RouleteRatioVec.at(i).RewardRatio <= 0)
		{
			continue;;
		}
		ratio += AnalyseJson::RouleteRatioVec.at(i).RewardRatio;
		if(randNum < ratio)
		{
			m_RewardType = AnalyseJson::RouleteRatioVec.at(i).RewardId;
			break;;
		}
	}
	CCLog("m_RewardType = %d",m_RewardType);
	return  (8 - m_RewardType) * 45 + 15 + rand()%30;
}




//--------------------------

GiftRewardEffWidget::GiftRewardEffWidget( void )
{
	m_GiftEffectLayout = NULL;
	m_CurrentDay = 2;
	m_RouletteReward = 0;
}

GiftRewardEffWidget::~GiftRewardEffWidget( void )
{
	CC_SAFE_RELEASE_NULL(m_GiftEffectLayout);
}

Layout* GiftRewardEffWidget::getGiftEffectLayout( int ui_type )
{
	if ( !m_GiftEffectLayout )
	{
		m_GiftEffectLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(GIFTREWARD_LAYOUT_JSONFILE));
		m_GiftEffectLayout->retain();
		m_GiftEffectLayout->setZOrder( 2 );

	}
	m_GiftEffectLayout->setVisible(true);
	m_GiftEffectLayout->setTouchEnable(true);

	float nDelayTime1 = 0.5f;

	UIButton *pBtnConfirm = dynamic_cast<UIButton*>(m_GiftEffectLayout->getChildByName("BtnConfirm"));
	pBtnConfirm->setTouchEnabled(true);
	pBtnConfirm->isEffects( true, nDelayTime1 );
	pBtnConfirm->addReleaseEvent(this, coco_releaseselector(GiftRewardEffWidget::ButtonCallBack));

	// 宝箱摇晃
	UIImageView *pImgGift = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgGift"));
	pImgGift->setVisible( true ) ;
	pImgGift->runAction( CCSequence::create (
		CCRotateTo::create( 0.1f, -10.0f ),
		CCRotateTo::create( 0.1f, 10.0f ),
		CCRotateTo::create( 0.1f, -10.0f ),
		CCRotateTo::create( 0.1f, 10.0f ),
		CCRotateTo::create( 0.1f, -10.0f ),
		CCRotateTo::create( 0.1f, 10.0f ),
		CCRotateTo::create( 0.1f, -10.0f ),
		CCRotateTo::create( 0.1f, 10.0f ),
		CCRotateTo::create( 0.1f, -10.0f ),
		CCRotateTo::create( 0.1f, 0.0f ),
		CCDelayTime::create( 0.2f ),
		CCCallFunc::create(this, callfunc_selector(GiftRewardEffWidget::CallFunOpenGift)), 

		NULL
		) );

	// 飞行物品
	// 奖励显示
	UILabel *pLabelRewardTitle = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName("LabelRewardTitle"));
	pLabelRewardTitle->setVisible( false );

	UIImageView *pImgRewardNumGoods1 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods1"));
	UIImageView *pImgRewardNumGoods2 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods2"));
	UIImageView *pImgRewardNumGoods3 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods3"));
	pImgRewardNumGoods1->setVisible( false );
	pImgRewardNumGoods2->setVisible( false );
	pImgRewardNumGoods3->setVisible( false );

	CCPoint nPoint1, nPoint2, nPoint3;
	nPoint1 = pImgRewardNumGoods1->getPosition();
	nPoint2 = pImgRewardNumGoods2->getPosition();
	nPoint3 = pImgRewardNumGoods3->getPosition();

	pImgRewardNumGoods1->setScale( 0.1f );
	pImgRewardNumGoods2->setScale( 0.1f );
	pImgRewardNumGoods3->setScale( 0.1f );
	pImgRewardNumGoods1->setPosition( pImgGift->getParent()->convertToWorldSpace( pImgGift->getPosition() ) );
	pImgRewardNumGoods2->setPosition( pImgGift->getParent()->convertToWorldSpace( pImgGift->getPosition() ) );
	pImgRewardNumGoods3->setPosition( pImgGift->getParent()->convertToWorldSpace( pImgGift->getPosition() ) );

	pImgRewardNumGoods1->runAction( CCSequence::create ( CCDelayTime::create( 2.0f ), CCSpawn::create(CCMoveTo::create( 0.3f , nPoint1),CCScaleTo::create( 0.3f, 1.0f ),NULL ), NULL ));
	pImgRewardNumGoods2->runAction( CCSequence::create ( CCDelayTime::create( 2.0f ), CCSpawn::create(CCMoveTo::create( 0.3f , nPoint2),CCScaleTo::create( 0.3f, 1.0f ),NULL ), NULL ));
	pImgRewardNumGoods3->runAction( CCSequence::create ( CCDelayTime::create( 2.0f ), CCSpawn::create(CCMoveTo::create( 0.3f , nPoint3),CCScaleTo::create( 0.3f, 1.0f ),NULL ), NULL ));
	// 奖励标签
	UILabel *pLabelNumGoods1 = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName("LabelNumGoods1"));
	UILabel *pLabelNumGoods2 = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName("LabelNumGoods2"));
	UILabel *pLabelNumGoods3 = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName("LabelNumGoods3"));


	// 	ActionObject* pGiftAction = ActionManager::shareManager()->getActionByName( GIFTREWARD_LAYOUT_JSONFILE,"Animation0" );
	// 	pGiftAction->play();



	m_UiType = ui_type;
	if(ui_type == MAP_WIDGET_SIGNIN)
	{

		std::list<SystemSignInConfig>::iterator tem = AnalyseJson::signInConfigStr.signInConfig.begin();
		do 
		{
			if ( tem == AnalyseJson::signInConfigStr.signInConfig.end() )
				break;

			if ( tem->SignInDay == m_CurrentDay )
			{
				std::list<SignReward>::iterator tem1 = tem->signReward.begin();
				for (int i = 1; tem1 != tem->signReward.end(); tem1++, i++)
				{
					UIImageView *pImgRewardNumGoods = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName(CCString::createWithFormat( "ImgRewardNumGoods%d", i)->getCString()));
					UILabel *pLabelNumGoods = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName(CCString::createWithFormat( "LabelNumGoods%d", i)->getCString()));

					pImgRewardNumGoods->setVisible( true );

					pLabelNumGoods->setText( CCString::createWithFormat(" X %d", tem1->propnum )->getCString() );
					switch( tem1->proptype )
					{
					case 1:
						{
							pImgRewardNumGoods->setTexture("Others/ImgCandyICO.png",UI_TEX_TYPE_PLIST );
							pImgRewardNumGoods->setTag( 1 );
						}
						break;
						//　
					case 2:
						{
							pImgRewardNumGoods->setTexture("Others/ImgGemICO.png",UI_TEX_TYPE_PLIST );
							pImgRewardNumGoods->setTag( 2 );
						}
						break;
						//　
					case 3:
						{
							pImgRewardNumGoods->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
							pImgRewardNumGoods->setTag( 3 );
						}
						break;
						break;
					}
				}
			}

			tem++;
		} while ( 1 );
	}
	else if(ui_type == MAP_WIDGET_ROULETTE_DLG)
	{
		//UIImageView *ImgRewardGoods = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardGoods1"));
		UIImageView *pImgRewardNumGoods = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods1"));
		UILabel *pLabelNumGoods = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName(CCString::createWithFormat( "LabelNumGoods1")->getCString()));

		pImgRewardNumGoods->stopAllActions();
		pImgRewardNumGoods->setVisible( true );

		CCPoint nPoint = pImgRewardNumGoods->getPosition();

		pImgRewardNumGoods->setScale( 0.1f );
		pImgRewardNumGoods->setPosition( pImgGift->getParent()->convertToWorldSpace( pImgGift->getPosition() ) );


		switch (m_RouletteReward)
		{
		case RouletteRewardType_Life:
			//ImgRewardGoods->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
			pImgRewardNumGoods->setTag( 3 );
			pImgRewardNumGoods->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		case RouletteRewardType_ColorCandy:
			//ImgRewardGoods->setTexture("Image/CandyGame/Others/candy0.png");
			pImgRewardNumGoods->setTag( 34 );
			pImgRewardNumGoods->setTexture("Image/CandyGame/Others/candy0.png");
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		case RouletteRewardType_Gem:
			//ImgRewardGoods->setTexture("Others/ImgGemICO.png",UI_TEX_TYPE_PLIST );
			pImgRewardNumGoods->setTag( 2 );
			pImgRewardNumGoods->setTexture("Image/MainMapUi/Prop/prop37.png" );
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		case RouletteRewardType_Double:
			//ImgRewardGoods->setTexture("Image/MainMapUi/Prop/prop33.png");
			pImgRewardNumGoods->setTag( 33 );
			pImgRewardNumGoods->setTexture("Image/MainMapUi/Prop/prop33.png");
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		case RouletteRewardType_MultiLife:
			//ImgRewardGoods->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
			pImgRewardNumGoods->setTag( 3 );
			pImgRewardNumGoods->setTexture("Others/ImgLifeICO.png",UI_TEX_TYPE_PLIST );
			pLabelNumGoods->setText( CCString::createWithFormat(" X 5 ")->getCString() );
			break;
		case RouletteRewardType_BombCandy:
			//ImgRewardGoods->setTexture("Image/MainMapUi/Prop/prop35.png");
			pImgRewardNumGoods->setTag( 35 );
			pImgRewardNumGoods->setTexture("Image/MainMapUi/Prop/prop35.png");
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		case RouletteRewardType_Harmmer:
			//ImgRewardGoods->setTexture("Image/MainMapUi/Prop/prop38.png");
			pImgRewardNumGoods->setTag( 38 );
			pImgRewardNumGoods->setTexture("Image/MainMapUi/Prop/prop38.png");
			pLabelNumGoods->setText( CCString::createWithFormat(" X 1 ")->getCString() );
			break;
		}

		pImgRewardNumGoods->runAction( CCSequence::create ( CCDelayTime::create( 2.0f ), CCSpawn::create(CCMoveTo::create( 0.3f , nPoint1),CCScaleTo::create( 0.3f, 1.0f ),NULL ), NULL ));

	}


	return m_GiftEffectLayout;
}

void GiftRewardEffWidget::ButtonCallBack( CCObject *pSender )
{
	MainMapUiLayer::m_mainmapuilayer->PlayEffect(MUSIC_ITEM_BUTTON_E);

	UIButton* pBtn = (UIButton*)pSender;
	pBtn->setTouchEnabled( false );

	float nRunTime = 0.5f;
	UIImageView* PanelRewardBg = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardBg"));

	if(m_UiType == MAP_WIDGET_SIGNIN)
	{
		// 飞行物品
		UIImageView *pImgRewardGoods1 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods1"));
		UIImageView *pImgRewardGoods2 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods2"));
		UIImageView *pImgRewardGoods3 = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods3"));

		UIButton* gameLifeBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("lifebtn"));
		//UIButton* GamegemBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("gembtn"));
		UIImageView* pImgCandyMoneyIco = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("ImgCandyMoneyIco"));

		MsgMgr::sendSignInMsg( AnalyseJson::logOnMsg.baseInfo.id );
		//MsgMgr::sendSignInMsg( AnalyseJson::logOnMsg.baseInfo.id, 1 );// 补签

		for (int i=1; i<=3; i++)
		{
			UIImageView *pImgRewardGoods = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName( CCString::createWithFormat("ImgRewardNumGoods%d", i)->getCString() ));
			UILabel *pLabelNumGoods = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName(CCString::createWithFormat( "LabelNumGoods%d", i)->getCString()));
			pLabelNumGoods->setVisible( false );

			if ( pImgRewardGoods->isVisible() )
			{
				CCPoint nTemp;
				switch(pImgRewardGoods->getTag())//1:糖果币；2:宝石；3:生命
				{
				case 3:				
					nTemp = gameLifeBut->getParent()->convertToWorldSpace( gameLifeBut->getPosition() );
					break;
				case 2:
					//nTemp = GamegemBut->getParent()->convertToWorldSpace( GamegemBut->getPosition() );
					break;
				case 1:
					nTemp = pImgCandyMoneyIco->getParent()->convertToWorldSpace( pImgCandyMoneyIco->getPosition() );
					break;
				}
				pImgRewardGoods->runAction( CCMoveTo::create( nRunTime , nTemp));
			}
		}
	}
	else if(m_UiType == MAP_WIDGET_ROULETTE_DLG)
	{
		if(CommonWidgt::m_GameRouletteWidget->m_GameRouletteLayout != NULL)
		{
			UIButton *pBtn = dynamic_cast<UIButton*>(CommonWidgt::m_GameRouletteWidget->m_GameRouletteLayout->getChildByName("Start_btn"));
			pBtn->setTouchEnabled(true);
			pBtn->active();
			UIImageView *pImg = dynamic_cast<UIImageView*>(CommonWidgt::m_GameRouletteWidget->m_GameRouletteLayout->getChildByName("Roulette_content"));
			pImg->stopAllActions();

			UIButton *pExitBtn = dynamic_cast<UIButton*>(CommonWidgt::m_GameRouletteWidget->m_GameRouletteLayout->getChildByName("m_btu_exit"));
			pExitBtn->setTouchEnable(true);
		}
		UIButton* gameLifeBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("lifebtn"));
		UIButton* GamegemBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("gembtn"));
		UIImageView* pImgCandyMoneyIco = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("ImgCandyMoneyIco"));

		UIImageView *pImgRewardNumGoods = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgRewardNumGoods1"));
		pImgRewardNumGoods->setScale( 1.3f );

		UILabel *pLabelNumGoods = dynamic_cast<UILabel*>(m_GiftEffectLayout->getChildByName("LabelNumGoods1"));
		pLabelNumGoods->setVisible( false );

		CCPoint nTemp;
		switch(pImgRewardNumGoods->getTag())//1:糖果币；2:宝石；3:生命
		{
		//case 3:				
		//	nTemp = gameLifeBut->getParent()->convertToWorldSpace( gameLifeBut->getPosition() );
		//	pImgRewardNumGoods->runAction( CCSequence::create( 
		//		CCMoveTo::create( nRunTime , nTemp), 
		//		CCCallFuncND::create(this, callfuncND_selector(GiftRewardEffWidget::CallFunGoodsFly), (void*)3),
		//		NULL));
		//	break;
		//case 2:
		///*	nTemp = GamegemBut->getParent()->convertToWorldSpace( GamegemBut->getPosition() );
		//	pImgRewardNumGoods->runAction(CCSequence::create( 
		//		CCMoveTo::create( nRunTime , nTemp), 
		//		CCCallFuncND::create(this, callfuncND_selector(GiftRewardEffWidget::CallFunGoodsFly), (void*)2),
		//		NULL));*/
		//	break;
		//case 1:
		//	nTemp = pImgCandyMoneyIco->getParent()->convertToWorldSpace( pImgCandyMoneyIco->getPosition() );
		//	pImgRewardNumGoods->runAction( CCSequence::create( 
		//		CCMoveTo::create( nRunTime , nTemp), 
		//		CCCallFuncND::create(this, callfuncND_selector(GiftRewardEffWidget::CallFunGoodsFly), (void*)1),
		//		NULL));
		//	break;
		default:
			pImgRewardNumGoods->setVisible( false );
			MainMapUiLayer::m_mainmapuilayer->playKnapsackAction( pImgRewardNumGoods->getParent()->convertToWorldSpace(pImgRewardNumGoods->getPosition()),  pImgRewardNumGoods->getTag());
		
			//渐隐动作
			pImgRewardNumGoods->runAction(CCSequence::create(
				CCFadeOut::create(0.5),
				CCCallFuncO::create(this, callfuncO_selector(GiftRewardEffWidget::PropFadeOutCallBack),pImgRewardNumGoods),
				NULL
				));
		}
	}
	// 背景消失
	PanelRewardBg->runAction(CCSequence::create(
		CCDelayTime::create( 1.0f ),
		CCFadeOut::create( nRunTime ),
		CCCallFunc::create(this, callfunc_selector(GiftRewardEffWidget::CallFuncConfirm)), 
		NULL));

}

void GiftRewardEffWidget::PropFadeOutCallBack(CCObject* sender)
{
	UIImageView* image = (UIImageView*)sender;
	if (image)
	{
		image->removeFromParentAndCleanup(true);
		image = NULL;
	}
}

void GiftRewardEffWidget::CallFuncConfirm( void )
{
	m_GiftEffectLayout->removeFromParentAndCleanup( true );
	CC_SAFE_RELEASE_NULL(CommonWidgt::m_GiftRewardWidget);
}

void GiftRewardEffWidget::releaseGiftEffectLayout( void )
{
	m_GiftEffectLayout->removeFromParent();
	CC_SAFE_RELEASE_NULL(m_GiftEffectLayout);
}

void GiftRewardEffWidget::CallFunOpenGift( void )
{
	UIImageView *pImgGift = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgGift"));
	pImgGift->setTexture( "Image/MainMapUi/ImgChestOPen.png");

	UIImageView *pImgGiftFront = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgGiftFront"));
	UIImageView *pImgGiftBack = dynamic_cast<UIImageView*>(m_GiftEffectLayout->getChildByName("ImgGiftBack"));
	CCNode* pParticleBack = CandyParticle::displayCandyParticle( CANDY_GIFT_BACK_EFFECT, ccp(0,0));
	CCNode* pParticleFront = CandyParticle::displayCandyParticle( CANDY_GIFT_FRONT_EFFECT, ccp(0,0));
	// 宝箱特效下
	pImgGiftBack->getRenderer()->addChild( pParticleBack );
	// 宝箱特效上
	pImgGiftFront->getRenderer()->addChild( pParticleFront );
}

void GiftRewardEffWidget::CallFunGoodsFly( CCNode* sender, void* data )
{
	int nTag = (int)(data);

	UIButton* gameLifeBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("lifebtn"));
	//UIButton* GamegemBut = dynamic_cast<UIButton*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("gembtn"));
	UIImageView* pImgCandyMoneyIco = dynamic_cast<UIImageView*>(MainMapUiLayer::m_mainmapuilayer->mapToolbarlayout->getChildByName("ImgCandyMoneyIco"));
	CCPoint nTemp;
	switch( nTag )//1:糖果币；2:宝石；3:生命
	{
	case 3:				
		nTemp = gameLifeBut->getParent()->convertToWorldSpace( gameLifeBut->getPosition() );
		break;
	case 2:
		//nTemp = GamegemBut->getParent()->convertToWorldSpace( GamegemBut->getPosition() );
		break;
	case 1:
		nTemp = pImgCandyMoneyIco->getParent()->convertToWorldSpace( pImgCandyMoneyIco->getPosition() );
		break;
	}
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SONGDAOJU_EFFECT, nTemp, MainMapUiLayer::m_mainmapuilayer );
}




//----------------------
GameSuperGiftWidget::GameSuperGiftWidget()
	:GameSuperGiftLayout(NULL)
{

}

GameSuperGiftWidget::~GameSuperGiftWidget()
{
	CC_SAFE_RELEASE_NULL(GameSuperGiftLayout);
}

Layout* GameSuperGiftWidget::getGameSuperGiftLayout()
{
	if ( !GameSuperGiftLayout )
	{
		GameSuperGiftLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(SUPERGIFT_LAYOUT_JSONFILE));
		GameSuperGiftLayout->retain();
		GameSuperGiftLayout->setZOrder( 2 );
	}
	GameSuperGiftLayout->setVisible(true);
	GameSuperGiftLayout->setTouchEnable(true);

	//立即领取按钮
	UIButton* getgiftBtn = dynamic_cast<UIButton*>(GameSuperGiftLayout->getChildByName("GetGiftBtn"));
	getgiftBtn->setTouchEnabled(true);
	getgiftBtn->addReleaseEvent(this,coco_releaseselector(GameSuperGiftWidget::GetGiftCallback));

	//退出按钮
	UIButton* superGiftExit = dynamic_cast<UIButton*>(GameSuperGiftLayout->getChildByName("Supergift_exit"));
	superGiftExit->setTouchEnabled(true);
	superGiftExit->addReleaseEvent(this,coco_releaseselector(GameSuperGiftWidget::GameGiftExit));

	//设置奖励数量
	int RewardsNum[] = {3,3,3,3,3};
	for (int i = 0; i < 5; ++i)
	{
		UILabelAtlas* numAtlas = dynamic_cast<UILabelAtlas*>(
			GameSuperGiftLayout->getChildByName(CCString::createWithFormat("PropNumLabel%d",i + 1)->getCString()));
		numAtlas->setStringValue(CCString::createWithFormat("%d",RewardsNum[i])->getCString());
	}

	CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(false);


	return GameSuperGiftLayout;
}

void GameSuperGiftWidget::GetGiftCallback(CCObject* sender)
{
	Loading::scenceType =  CANDY_SCENCE_PLAY_GAME;

	GameGiftExit(sender);

	//回调处理,调出短信购买界面
	//CppCallJava::BuySuperGift();

	//新版支付
	CandyPay::getInstance()->RequestCandyOrder(Super_gift);

	CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(true);
}

void GameSuperGiftWidget::GameGiftExit(CCObject* sender)
{
	CandyManager::getInstance()->musicMgr->playMusic( CANDY_EFFECT_BUTTON );

	if (!GameSuperGiftLayout)
	{
		return;
	}

	CandyManager::getInstance()->uiLayer->setPropButtonTouchEnable(true);

	GameSuperGiftLayout->removeFromParentAndCleanup(true);
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);

}











/***********************************/
/*GamePay widget*/
/***********************************/
GamePayWidget::GamePayWidget():
	m_GamePayLayout(NULL)
{
	m_PayType = 0;
}

GamePayWidget::~GamePayWidget()
{
	CC_SAFE_RELEASE_NULL(m_GamePayLayout);
}

Layout* GamePayWidget::getGamePayLayout(int type) 
{
	if ( !m_GamePayLayout )
	{
		m_GamePayLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDYPAY_LAYOUT_JSONFILE));
		m_GamePayLayout->retain();
		m_GamePayLayout->setZOrder( 2 );
	}
	m_GamePayLayout->setVisible(true);
	m_GamePayLayout->setTouchEnable(true);


	UIButton *m_pPayBtn = dynamic_cast<UIButton*>(m_GamePayLayout->getChildByName("pay_btn"));
	m_pPayBtn->setTouchEnable(true);
	m_pPayBtn->setVisible(true);
	m_pPayBtn->addReleaseEvent(this,coco_releaseselector(GamePayWidget::ButtonCallBack));

	UIButton *m_pPayBtn_Small = dynamic_cast<UIButton*>(m_GamePayLayout->getChildByName("pay_btn_small"));
	m_pPayBtn_Small->setTouchEnable(false);
	m_pPayBtn_Small->setVisible(false);
	m_pPayBtn_Small->addReleaseEvent(this,coco_releaseselector(GamePayWidget::ButtonCallBack));

	UIButton *m_pExitBtn = dynamic_cast<UIButton*>(m_GamePayLayout->getChildByName("exit_btn"));
	m_pExitBtn->setTouchEnable(true);
	m_pExitBtn->setVisible(true);
	m_pExitBtn->addReleaseEvent(this,coco_releaseselector(GamePayWidget::ExitCallBack));

	UIButton *m_pExitBtn_Small = dynamic_cast<UIButton*>(m_GamePayLayout->getChildByName("exit_btn_small"));
	m_pExitBtn_Small->setTouchEnable(false);
	m_pExitBtn_Small->setVisible(false);
	m_pExitBtn_Small->addReleaseEvent(this,coco_releaseselector(GamePayWidget::ExitCallBack));

	UIImageView *m_pImg = dynamic_cast<UIImageView*>(m_GamePayLayout->getChildByName("content_real"));
	//m_pImg->setScale(1.7f);

	UILabel* payTips = dynamic_cast<UILabel*>(m_GamePayLayout->getChildByName("LabelPayTips1"));

	//m_pPayBtn_Small->setPosition(CCPoint(5, -207));
	//m_pExitBtn_Small->setPosition(CCPoint(235, 222));

	m_PayType = type;
	switch (m_PayType)
	{
	case CANDY_PROP_LIFE:
		//生命
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_1.png");
		payTips->setText( CommonData::GetString("app_paytips_1_str").c_str() );
		break;
	case CANDY_PROP_OUT_COLORFULL:
		//彩塘
		m_pPayBtn_Small->setTouchEnable(true);
		m_pPayBtn_Small->setVisible(true);
		m_pExitBtn_Small->setTouchEnable(true);
		m_pExitBtn_Small->setVisible(true);
		m_pPayBtn->setTouchEnable(false);
		m_pPayBtn->setVisible(false);
		m_pExitBtn->setTouchEnable(false);
		m_pExitBtn->setVisible(false);

		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_3.png");
		payTips->setText( CommonData::GetString("app_paytips_3_str").c_str() );
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		//炸弹唐
		m_pPayBtn_Small->setTouchEnable(true);
		m_pPayBtn_Small->setVisible(true);
		m_pExitBtn_Small->setTouchEnable(true);
		m_pExitBtn_Small->setVisible(true);
		m_pPayBtn->setTouchEnable(false);
		m_pPayBtn->setVisible(false);
		m_pExitBtn->setTouchEnable(false);
		m_pExitBtn->setVisible(false);
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_2.png");
		payTips->setText( CommonData::GetString("app_paytips_2_str").c_str() );
		break;
	case CANDY_PROP_IN_RESORT:
		//重排
		m_pPayBtn_Small->setTouchEnable(true);
		m_pPayBtn_Small->setVisible(true);
		m_pExitBtn_Small->setTouchEnable(true);
		m_pExitBtn_Small->setVisible(true);
		m_pPayBtn->setTouchEnable(false);
		m_pPayBtn->setVisible(false);
		m_pExitBtn->setTouchEnable(false);
		m_pExitBtn->setVisible(false);
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_5.png");
		payTips->setText( CommonData::GetString("app_paytips_5_str").c_str() );
		break;
	case CANDY_PROP_IN_SWAP:
		//交换
		m_pPayBtn_Small->setTouchEnable(true);
		m_pPayBtn_Small->setVisible(true);
		m_pExitBtn_Small->setTouchEnable(true);
		m_pExitBtn_Small->setVisible(true);
		m_pPayBtn->setTouchEnable(false);
		m_pPayBtn->setVisible(false);
		m_pExitBtn->setTouchEnable(false);
		m_pExitBtn->setVisible(false);
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_6.png");
		payTips->setText( CommonData::GetString("app_paytips_6_str").c_str() );
		break;
	case CANDY_PROP_IN_HAMMER:
		//锤子
		m_pPayBtn_Small->setTouchEnable(true);
		m_pPayBtn_Small->setVisible(true);
		m_pExitBtn_Small->setTouchEnable(true);
		m_pExitBtn_Small->setVisible(true);
		m_pPayBtn->setTouchEnable(false);
		m_pPayBtn->setVisible(false);
		m_pExitBtn->setTouchEnable(false);
		m_pExitBtn->setVisible(false);
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_4.png");
		payTips->setText( CommonData::GetString("app_paytips_4_str").c_str() );
		break;

// 	case TeHui_gift:
// 	{
// 
// 		m_pPayBtn_Small->setPosition(CCPoint(5, -247));
// 		m_pExitBtn_Small->setPosition(CCPoint(245, 240));
// 		m_pPayBtn_Small->setTouchEnable(true);
// 		m_pPayBtn_Small->setVisible(true);
// 		m_pExitBtn_Small->setTouchEnable(true);
// 		m_pExitBtn_Small->setVisible(true);
// 		m_pPayBtn->setTouchEnable(false);
// 		m_pPayBtn->setVisible(false);
// 		m_pExitBtn->setTouchEnable(false);
// 		m_pExitBtn->setVisible(false);
// 		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_16.png");
// 	
// 	}
// 		break;

	case CANDY_PROP_IN_STEP5:
		//加五步
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_7.png");
		payTips->setText( CommonData::GetString("app_paytips_7_str").c_str() );
		break;
	case GameGift_Level1:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_8.png");
		payTips->setText( CommonData::GetString("app_paytips_8_str").c_str() );
		break;
	case GameGift_Level2:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_8.png");
		payTips->setText( CommonData::GetString("app_paytips_8_str").c_str() );
		break;
	case GameGift_Level3:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_8.png");
		payTips->setText( CommonData::GetString("app_paytips_8_str").c_str() );
		break;
	case Super_gift:
		//限时优惠包
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_11.png");
		payTips->setText( CommonData::GetString("app_paytips_11_str").c_str() );
		break;
	case Success_Pass:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_12.png");
		payTips->setText( CommonData::GetString("app_paytips_12_str").c_str() );
		break;
	case UnLock_Level:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_13.png");
		payTips->setText( CommonData::GetString("app_paytips_13_str").c_str() );
		break;
	case Exit_Gift:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_14.png");
		payTips->setText( CommonData::GetString("app_paytips_14_str").c_str() );
		break;
	case Zhadan_Gift:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_15.png");
		payTips->setText( CommonData::GetString("app_paytips_15_str").c_str() );
		break;
	case Zhizun_Gift:
		m_pImg->loadTexture("Image/CandyGame/Others/skypay_bg_11.png");
		payTips->setText( CommonData::GetString("app_paytips_11_str").c_str() );
		break;
	default:
		break;
	}
	return m_GamePayLayout;
}

void GamePayWidget::ExitCallBack(CCObject *pSender)
{
	if ( CANDY_SCENCE_PLAY_GAME == Loading::scenceType )
	{
		WidgetRemove();

		if(m_PayType == CANDY_PROP_IN_STEP5)
		{
			//如果是在商城购买的加五步，购买失败后不弹出过关失败界面
			if (CommonData::m_BuyAdd5From == 1)
			{
				CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PASS_LEVEL);
			}
		}
		else if(m_PayType == Success_Pass)
		{
			CommonData::m_successPassFailed = 1;
		}
		else if(m_PayType == Zhadan_Gift || m_PayType == Zhizun_Gift )
		{
			CommonData::m_nextStage = 1;
		}

	}
	else if(CANDY_SCENCE_MAIN_MAP == Loading::scenceType)
	{
		if(MainMapUiLayer::m_mainmapuilayer)
		{
			if ( m_PayType == Exit_Gift )
			{
				CCDirector::sharedDirector()->end();
			}
			else
			{
				MainMapUiLayer::m_mainmapuilayer->QuitMapWidgetCallback();
			}
		}
	}
}

void GamePayWidget::ButtonCallBack(CCObject *pSender)
{
	//不要支付
	//return;
	switch (m_PayType)
	{
	case CANDY_PROP_LIFE:
		//生命
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_LIFE);
		break;
	case CANDY_PROP_OUT_COLORFULL:
		//彩塘
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_OUT_COLORFULL);
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		//炸弹唐
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_OUT_BOMBNEW);
		break;
	case CANDY_PROP_IN_RESORT:
		//重排
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_RESORT);
		break;
	case CANDY_PROP_IN_SWAP:
		//交换
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_SWAP);
		break;
	case CANDY_PROP_IN_HAMMER:
		//锤子
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_HAMMER);
		break;
	case CANDY_PROP_IN_STEP5:
		//加五步
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(CANDY_PROP_IN_STEP5);
		break;
	case GameGift_Level1:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level1);
		break;
	case GameGift_Level2:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level2);
		break;
	case GameGift_Level3:
		CandyPay::getInstance()->RequestCandyOrder(GameGift_Level3);
		break;
	case Super_gift:
		//限时优惠包
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(Super_gift);
		break;
	case Success_Pass:
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(Success_Pass);
		break;
	case UnLock_Level:
		CandyPay::getInstance()->RequestCandyOrder(UnLock_Level);
		break;
	case Exit_Gift:
		CandyPay::getInstance()->RequestCandyOrder(Exit_Gift);
		break;
	case Zhadan_Gift:
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(Zhadan_Gift);
		break;
	case Zhizun_Gift:
		WidgetRemove();
		CandyPay::getInstance()->RequestCandyOrder(Zhizun_Gift);
		break;
// 	case TeHui_gift:
// 		CandyPay::getInstance()->RequestCandyOrder(TeHui_gift);
// 		break;
	default:
		break;
	}
}
void GamePayWidget::WidgetRemove()
{
	if (!m_GamePayLayout)
	{
		return;
	}
	m_GamePayLayout->removeFromParentAndCleanup(true);
	m_GamePayLayout->setTouchEnable(false);
}