#include "CandyStageIntro.h"
#include "CandyManager.h"
#include "../MainMap/MainMapUiLayer.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../CppCallJava/CppCallJava.h"
#include "../MsgMgr/HeadDownMgr.h"

//#define STAGE_INFO_LAYOUT_FILE		"Image/CandyGame/CandyGameLayout/CandyStageInfo.ExportJson"
#define STAGE_INFO_LAYOUT_FILE		"Image/MainMapUi/Tools/CandyStageInfo.ExportJson"
#define BUY_PROP_LOADING_TAG		101

CandyStageIntroLayout::CandyStageIntroLayout()
{
	stageIntroLayout = NULL;
	lastLevel  = 0;
}

Layout* CandyStageIntroLayout::getStageIntroLayout(int level)
{
	//static UIButton *playButton;
	//static UIButton *returnButton;
	//if(!stageIntroLayout)
	//{
	//	stageIntroLayout =dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(STAGE_INFO_LAYOUT_FILE));
	//	stageIntroLayout->retain();

	//	playButton = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("StartGameButton"));
	//	playButton->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::stageInfoPlayCallBack));

	//	returnButton = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("ReturnButton"));
	//	returnButton->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::stageInfoReturnCallBack));

	//}
	//for(int i=0; i<5; i++)
	//{
	//	PropButton[i]  = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("PropButton%d",i+1)->getCString()));
	//	PropButton[i]->setTouchEnable(true);
	//	PropButton[i]->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::stageInfoUsePropCallBack));


	//	PropBuy[i]  = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("PropBuy%d",i+1)->getCString()));
	//	PropNumBg[i]= dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("PropNumBg%d",i+1)->getCString()));
	//	PropNumLabel[i]= dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("PropNumLabel%d",i+1)->getCString()));

	//	PropSelected[i] =  dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("PropTickBg%d",i+1)->getCString()));

 //		PropPriceShow[i] = dynamic_cast<UIImageView *>(stageIntroLayout->getChildByName(
 //			CCString::createWithFormat("ImgProp%dPrice",i+1)->getCString()));
	//	PropPriceShow[i]->setVisible( true );

	//	UIImageView* PropGemICO = dynamic_cast<UIImageView *>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("ImgProp%dGemICO",i+1)->getCString()));
	//	PropGemICO->setVisible( false );

	//	UIImageView* PropCandyICO = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("ImgProp%dCandyICO",i+1)->getCString()));
	//	PropCandyICO->setVisible( false );

	//	UILabelAtlas* PropPriceLable = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName(
	//		CCString::createWithFormat("LabPriceNum%d",i+1)->getCString()));


	//	CandyPropType propType;
	//	switch(i)
	//	{
	//	case 0:
	//		propType = CANDY_PROP_OUT_DOUBLE ;
	//		break;
	//	case 1:
	//		propType = CANDY_PROP_OUT_COLORFULL ;
	//		break;
	//	case 2:
	//		propType = CANDY_PROP_OUT_BOMBNEW ;
	//		break;
	//	}

	//	int currentPropPrice = CommonData::getPropPriceForBuyType( propType );
	//	PropPriceLable->setStringValue( CCString::createWithFormat("%d", currentPropPrice)->getCString() );

	//	if ( 2 == CommonData::getPropBuyMoneyType(propType) )
	//		PropCandyICO->setVisible( true );
	//	else
	//		PropGemICO->setVisible( true );

	//	if ( CommonData::getPropNum( propType ) )
	//		PropPriceShow[i]->setVisible( false );

	//	
	//	PropBuy[i]->setVisible(true);
	//	PropNumBg[i]->setVisible( true );
	//	PropNumLabel[i]->setVisible( true );
	//	PropButton[i]->active(true);

	//}


	//for (int j = 1; j<=3; j++)
	//{
	//	char* pStarName = (char*)CCString::createWithFormat("StarN%d", j)->getCString();
	//	UIImageView *pStar = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName( pStarName ));
	//	pStar->setVisible( false );
	//}

	//std::list<UserStageInfoStr>::iterator item = AnalyseJson::logOnMsg.stageInfo.begin();
	//for (; item!=AnalyseJson::logOnMsg.stageInfo.end(); item++)
	//{
	//	if (item->level == level)
	//	{
	//		for (int j = 1; j<=3; j++)
	//		{
	//			char* pStarName = (char*)CCString::createWithFormat("StarN%d", j)->getCString();
	//			UIImageView *pStar = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName( pStarName ));
	//			if ( j<=item->starnum )
	//				pStar->setVisible( true );
	//			else
	//				pStar->setVisible( false );
	//		}
	//		break;
	//	}
	//}

	//float nDelayTime1 = 0.2f;
	//float nDelayTime2 = 0.081f;

	//for(int i=0; i<5; i++)
	//	PropButton[i]->isEffects(true, nDelayTime1+nDelayTime2*i);

	////　1~5关禁用游戏外道具
	//if ( 1 == level)
	//{
	//	for( int i = 0; i<5; i++)
	//	{
	//		PropButton[i]->setVisible(false);
	//		PropButton[i]->disable();
	//		PropBuy[i]->setVisible(false);
	//		PropNumBg[i]->setVisible( false );
	//		PropNumLabel[i]->setVisible( false );
	//	}
	//}
	//else if(level == 2 || level == 3)
	//{
	//	for( int i = 0; i<5; i++)
	//	{
	//		PropButton[i]->setVisible(false);
	//		PropButton[i]->disable();
	//		PropBuy[i]->setVisible(false);
	//		PropNumBg[i]->setVisible( false );
	//		PropNumLabel[i]->setVisible( false );
	//	}
	//	PropButton[0]->active();
	//	PropButton[0]->setVisible(true);
	//	PropBuy[0]->setVisible(true);
	//	PropNumBg[0]->setVisible( true );
	//	PropNumLabel[0]->setVisible( true );
	//}
	//else if(level == 4)
	//{
	//	for( int i = 0; i<3; i++)
	//	{
	//		PropBuy[i]->setVisible(true);
	//		PropNumBg[i]->setVisible( true );
	//		PropNumLabel[i]->setVisible( true );
	//		PropButton[i]->active(true);
	//	}
	//	PropButton[2]->setVisible(false);
	//	PropButton[2]->disable();
	//	PropBuy[2]->setVisible(false);
	//	PropNumBg[2]->setVisible( false );
	//	PropNumLabel[2]->setVisible( false );
	//}
	//else
	//{
	//	for( int i = 0; i<3; i++)
	//	{
	//		PropBuy[i]->setVisible(true);
	//		PropNumBg[i]->setVisible( true );
	//		PropNumLabel[i]->setVisible( true );
	//		PropButton[i]->active(true);
	//	}
	//}

	////　为显示购买价格处理
	//for( int i = 0; i<3; i++)
	//{
	//	if ( !PropNumBg[i]->isVisible() )
	//		PropPriceShow[i]->setVisible( false );
	//		
	//}

	//playButton->setTouchEnable(true);
	//returnButton->setTouchEnable(true);
	//playButton->isEffects(true , nDelayTime1+nDelayTime2*4);
	//returnButton->isEffects(true , nDelayTime1+nDelayTime2);
	//stageIntroLayout->setVisible(true);

	////if(lastLevel != level || 5 >= CandyManager::currentLevel)
	//{
	//	if(CommonData::m_resetPropState)
	//	{
	//		CommonData::resetPropUseState();
	//	}
	//	int temp = 0;
	//	for(int i=0; i<3; i++)
	//	{
	//		switch(i)
	//		{
	//		case 0:
	//			temp = CANDY_PROP_OUT_DOUBLE ;
	//			break;
	//		case 1:
	//			temp = CANDY_PROP_OUT_COLORFULL ;
	//			break;
	//		case 2:
	//			temp = CANDY_PROP_OUT_BOMBNEW ;
	//			break;
	//		}
	//		updatePropNum(temp);
	//	}
	//	lastLevel = level;
	//}

	//UILabelAtlas *levelLabel= dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("LevelLabel"));
	//levelLabel->setStringValue(CCString::createWithFormat("%d",level)->getCString());
	
//	m_shareWeixin = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("weixinbtn"));
//	m_shareWeixin->setTag(  SHARE_TO_WEXIN );
//	m_shareWeixin->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::ShareBtnCb));
//	m_shareWeixin->setTouchEnabled(false);
//	m_shareWeixin->isEffects(true);
//
//	m_shareTWeibo = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("Tweibo"));
//	m_shareTWeibo->setTag(  SHARE_TO_QZONE);
//	m_shareTWeibo->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::ShareBtnCb));
//	m_shareTWeibo->isEffects(true);
//	m_shareTWeibo->setTouchEnabled(false);
//
//
//	m_shareSWeibo = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("Sweibo"));
//	m_shareSWeibo->setTag( SHARE_TO_SINA );
//	m_shareSWeibo->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::ShareBtnCb));
//	m_shareSWeibo->isEffects(true);
//	m_shareSWeibo->setTouchEnabled(false);
//
//	UIButton *pBtnToShare = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToShare"));
//	pBtnToShare->setTag( BUTTON_TO_SHARE );
//	//pBtnToShare->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::ShareBtnCb));
//	pBtnToShare->setVisible(false);
//	pBtnToShare->setTouchEnabled(false);
//
//	UIButton *pBtnToRank = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToRank"));
//	pBtnToRank->setTag( BUTTON_TO_RANK );
////	pBtnToRank->addReleaseEvent(this, coco_releaseselector(CandyStageIntroLayout::ShareBtnCb));
//	pBtnToRank->isEffects(true);
//	pBtnToRank->setTouchEnabled(false);
//
//	UIPanel *pPanToShare = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_share"));
//	pPanToShare->setZOrder(1);
//	pPanToShare->setVisible( false );
//	pPanToShare->setTouchEnabled( false );
//
//	UIPanel *pPanRank = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_ranking"));		
//	pPanToShare->setZOrder(2);
//	pPanRank->setVisible( true );
//	pPanRank->setTouchEnabled( true  );
//
//	UIImageView *pImgView = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("ContentBg_1"));		
//	if(CommonData::getMaxLevel() < 20)
//	{
//		pImgView->setVisible(false);
//	}
//	else
//	{
//		pImgView->setVisible(true);
//	}

	//initTargetInformat( level );


	return stageIntroLayout;
}


void CandyStageIntroLayout::initTargetInformat( int level )
{
	int nTargetMode = CandyMapData::getTargetMode( level );

	CandyMapData::getMapdataFromLua( level );
	// 收集Mode
	UIImageView* collectTypeImg[3];
	UILabelAtlas* collectTypeLabel[3];
	/*UIPanel* collectModePanel;
	collectModePanel = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("CollectModeTarget"));
	collectTypeImg[0] = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("CollectType1"));
	collectTypeImg[1] = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("CollectType2"));
	collectTypeImg[2] = dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("CollectType3"));
	collectTypeLabel[0] = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("CollectLabel1"));
	collectTypeLabel[1] = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("CollectLabel2"));
	collectTypeLabel[2] = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("CollectLabel3"));*/
	collectTypeImg[0]->setVisible( true );
	collectTypeImg[1]->setVisible( true );
	collectTypeImg[2]->setVisible( true );
	collectTypeLabel[0]->setVisible( true );
	collectTypeLabel[1]->setVisible( true );
	collectTypeLabel[2]->setVisible( true );
	collectTypeImg[0]->setPosition( ccp(-88,25) );
	collectTypeImg[1]->setPosition( ccp(17,25) );
	collectTypeImg[2]->setPosition( ccp(112,25) );

	// 消除果冻模式/冰块模式
	//UIPanel* jellyModePanel;
	//UILabelAtlas* jellyNumLabel;
	//jellyModePanel = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("DispelJellyTarget"));
	//jellyNumLabel = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("JellyNumLabel"));
	//jellyNumLabel->setVisible( true );

	//// 运送模式
	//UIPanel* transportModePanel;
	//UIImageView* chesnutImg;
	//UIImageView* cherryImg;
	//UILabelAtlas* chesnutNumLabel;
	//UILabelAtlas* cherryNumLabel;
	//transportModePanel = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("TransportModeTarget"));
	//chesnutImg 	= dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("ChesnutImg"));
	//cherryImg	= dynamic_cast<UIImageView*>(stageIntroLayout->getChildByName("CherryImg"));
	//chesnutNumLabel = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("ChesnutNumLabel"));
	//cherryNumLabel = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("CherryNumLabel"));
	//chesnutImg->setPosition( ccp(-30,30) );
	//cherryImg->setPosition( ccp(-134,30) );
	//chesnutImg->setVisible( true );
	//cherryImg->setVisible( true );
	//chesnutNumLabel->setVisible( true );
	//cherryNumLabel->setVisible( true );

	// 普通模式
	/*UIPanel* targetNumPanel;
	UILabelAtlas* targetNumLabel;
	targetNumPanel = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("ScoreTarget"));	
	targetNumLabel = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("TargetNumLabel"));	
	targetNumLabel->setVisible( true );


	targetNumPanel->setVisible(false);
	jellyModePanel->setVisible(false);
	transportModePanel->setVisible(false);
	collectModePanel->setVisible(false);

	UILabelAtlas *targetScoreLabel = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("TargetNumLabel"));
	targetScoreLabel->setStringValue(CCString::createWithFormat("%d",CandyMapData::getTargetScore(level))->getCString());*/

	switch( nTargetMode )
	{
	case CANDY_MODE_NORMAL:
		//targetNumPanel->setVisible(true);
		break;

	case CANDY_MODE_JELLY:
		//jellyModePanel->setVisible(true);
		//jellyNumLabel->setStringValue(CCString::createWithFormat("%d",CandyIngredients::numjelly)->getCString());
		break;

	case CANDY_MODE_INGREDIENT:
		//transportModePanel->setVisible(true);
		//cherryNumLabel->setStringValue(CCString::createWithFormat("%d",CandyIngredients::numCherry )->getCString());
		//chesnutNumLabel->setStringValue(CCString::createWithFormat("%d",CandyIngredients::numChesnut)->getCString());
		if(CandyIngredients::numCherry ==0|| CandyIngredients::numChesnut==0)
		{
			//UIImageView *emptyTarget = CandyIngredients::numCherry ==0?cherryImg:chesnutImg;
			//UIImageView *exsitTarget = CandyIngredients::numCherry ==0?chesnutImg:cherryImg;


			//CCPoint emptyPos = emptyTarget->getPosition();
			//CCPoint exsitPos = exsitTarget->getPosition();
			//CCPoint exsitOffset = ccp((exsitPos.x -emptyPos.x)*0.5f,0);

			//exsitTarget->setPosition(ccpSub(exsitPos, exsitOffset));
			//emptyTarget->setVisible(false);
		}
		break;

	case CANDY_MODE_TIMING:
		//targetNumPanel->setVisible(true);
		break;

	case CANDY_MODE_COLLECT:
		{
			//collectModePanel->setVisible(true);

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
				collectTypeLabel[i]->setStringValue(CCString::createWithFormat("%d",CandyManager::collectCandy[i].currentNum)->getCString());
				collectTypeImg[i]->loadTexture(CCString::createWithFormat("%s/CollectType%d.png",COLLECT_TYPE_IMG_PATH,(int)CandyManager::collectCandy[i].type)->getCString());		
				collectTypeImg[i]->setTag( (int)CandyManager::collectCandy[i].type );
			}	
			if(1 == j)
			{
				collectTypeImg[0]->setPosition(collectTypeImg[1]->getPosition());
			}
			else if(2 == j)
			{
				int offsetX = 30;
				collectTypeImg[0]->setPosition(ccp(collectTypeImg[0]->getPosition().x+offsetX, collectTypeImg[0]->getPosition().y));
				collectTypeImg[1]->setPosition(ccp(collectTypeImg[1]->getPosition().x+offsetX, collectTypeImg[1]->getPosition().y));
			}

		}
		break;
	}

}


void CandyStageIntroLayout::ShareBtnCb(CCObject *pSender)
{
	int BtnType = ((UIButton*)pSender)->getTag();
	int userid = (int)((UIButton*)pSender)->data;

	switch( BtnType )
	{
	case SHARE_TO_QZONE:
		{
			m_shareTWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "1", "2");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case SHARE_TO_SINA:
		{
			m_shareSWeibo->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "1", "1");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case SHARE_TO_WEXIN:
		{
			m_shareWeixin->setTouchEnabled(false);
#ifdef CANDY_STATISITICAL_DATA
			//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_4007, "1", "3");
#endif
			CommonData::CutOutScene();
			std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + "MyCurScene.png" ;
		}
		break;

	case BUTTON_TO_RANK:
		{
			/*UIPanel *pPanToShare = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( false );
			pPanToShare->setZOrder( 5 );
			pPanToShare->setTouchEnabled( false );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( true );
			pPanRank->setZOrder( 6 );
			pPanRank->setTouchEnabled( true );

			UIButton *pBtnToShare = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(true);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(false);*/
		}
		break;

	case BUTTON_TO_SHARE:
		{
			/*UIPanel *pPanToShare = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_share"));
			pPanToShare->setVisible( true );
			pPanToShare->setZOrder( 6 );
			pPanToShare->setTouchEnabled( true );

			UIPanel *pPanRank = dynamic_cast<UIPanel*>(stageIntroLayout->getChildByName("panl_ranking"));		
			pPanRank->setVisible( false );
			pPanRank->setZOrder( 5 );
			pPanRank->setTouchEnabled( false );


			UIButton *pBtnToShare = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToShare"));
			pBtnToShare->setTouchEnabled(false);

			UIButton *pBtnToRank = dynamic_cast<UIButton*>(stageIntroLayout->getChildByName("btnToRank"));
			pBtnToRank->setTouchEnabled(true);

			m_shareWeixin->setTouchEnabled(true);

			m_shareTWeibo->setTouchEnabled(true);

			m_shareSWeibo->setTouchEnabled(true);*/
		}
		break;

	case BUTTON_TO_HANDLELIFE:
		{
			((UIButton*)pSender)->setVisible(false);
			MsgMgr::sendHandselLifeMsg( AnalyseJson::logOnMsg.baseInfo.id, userid);
		}
		break;
	}
}

void CandyStageIntroLayout::AddFriendToRank()
{
	//CCFileUtils *sharedFileUtils = CCFileUtils::sharedFileUtils();
	//UIScrollView* plistView = dynamic_cast<UIScrollView*>(stageIntroLayout->getChildByName( "ScrollFriendRank" ));
	//CCSize scrollSize = plistView->getContentSize();
	//plistView->removeAllChildrenAndCleanUp(true);
	//int nFriendLen = AnalyseJson::SingleLevelResultStr.friendInfo.size();
	//CCSize itemPoint;

	//// 计算出scrollView的高
	//float ClipWidth; 
	//float ClipHeight;
	//int myRank = 0;
	//int sex = 0;

	//ClipHeight = scrollSize.height;
	//ClipWidth = nFriendLen * ( 200 + 15 );
	//if (ClipWidth < scrollSize.width)
	//	ClipWidth = scrollSize.width;
	//plistView->setInnerContainerSize(CCSizeMake(ClipWidth, ClipHeight));
	//plistView->setTouchEnable( true );
	//itemPoint.width = scrollSize.width/2;
	//float butMPointX = 0;

	//std::list<UserSingleLevelStr>::iterator p = AnalyseJson::SingleLevelResultStr.friendInfo.begin();
	//for(int i=0; i< (int)AnalyseJson::SingleLevelResultStr.friendInfo.size(); i++,p++)
	//{
	//	UIImageView* pItemImg = UIImageView::create();
	//	pItemImg->setScale9Enabled( true );
	//	pItemImg->setScale9Size( CCSizeMake(200, 150));
	//	pItemImg->setTexture( "Image/MainMapUi/editboxBG.png" );
	//	pItemImg->setVisible( true );
	//	pItemImg->setAnchorPoint( ccp(0,0));
	//	pItemImg->setPosition(ccp(butMPointX, 0));
	//	butMPointX += ( 200 + 15);
	//	plistView->addChild( pItemImg );

	//	std::string headPath ;
	//	if(p->id == AnalyseJson::logOnMsg.baseInfo.id)
	//		headPath = CommonData::getCurrentHeadPath( AnalyseJson::logOnMsg.baseInfo.headPicUrl ).c_str();
	//	else
	//		headPath = CommonData::getHeadPathForUrl( p->headPicUr );

	//	UIImageView* pImgHead = UIImageView::create();
	//	pImgHead->setTexture( headPath.c_str() );
	//	pImgHead->setPosition(ccp(38, 118));
	//	pImgHead->setScale( 0.7f );
	//	pImgHead->setVisible( true );
	//	pItemImg->addChild( pImgHead );

	//	UIImageView* pImgHeadK = UIImageView::create();
	//	pImgHeadK->setTexture( "Image/CandyGame/Others/headframe.png" );
	//	pImgHeadK->setPosition(ccp(0, -2));
	//	pImgHeadK->setVisible( true );
	//	pImgHead->addChild( pImgHeadK );

	//	if ( 0 != p->isvip )
	//	{
	//		UIImageView* pVipImg = UIImageView::create();
	//		pVipImg->setTexture( "Image/BigMap_1/ImgVipTips.png" );
	//		pVipImg->setZOrder( 7 );
	//		pVipImg->setPosition(ccp(0, 55));
	//		pImgHead->addChild( pVipImg);
	//	}

	//	// Setting friend Sex  1: girl  0: boy
	//	UIImageView* pSexbgImg = UIImageView::create();
	//	if ( 1 == p->gender )
	//		pSexbgImg->setTexture( "Image/MainMapUi/m_img_girlbg.png" );
	//	else
	//		pSexbgImg->setTexture( "Image/MainMapUi/m_img_boybg.png" );

	//	pSexbgImg->setVisible( true );
	//	pSexbgImg->setPosition(ccp(44, -37));
	//	pImgHead->addChild( pSexbgImg);

	//	UIImageView* pTopBg = UIImageView::create();
	//	if ( 0 == i )
	//		pTopBg->setTexture( "Image/CandyGame/Others/ImgTop1.png" );
	//	else if ( 1 == i )
	//		pTopBg->setTexture( "Image/CandyGame/Others/ImgTop2.png" );
	//	else if ( 2 == i )
	//		pTopBg->setTexture( "Image/CandyGame/Others/ImgTop3.png" );

	//	pTopBg->setPosition(ccp(30, 42));
	//	pTopBg->setSize( CCSizeMake(80,76));
	//	pTopBg->setVisible( true );
	//	pItemImg->addChild( pTopBg );

	//	UILabelAtlas* TopNum = UILabelAtlas::create();
	//	char *strLevelNum= (char *)CCString::createWithFormat("%d",  i+1)->getCString();
	//	TopNum->setProperty(strLevelNum , "Image/CandyGame/Others/RankStr.png",28, 31, "0");  
	//	TopNum->setPosition( ccp(-2, 1));
	//	TopNum->setVisible( true );
	//	pTopBg->addChild( TopNum );

	//	UILabelAtlas* AtlevelNum1 = UILabelAtlas::create();
	//	strLevelNum= (char *)CCString::createWithFormat("%d",  p->result)->getCString();
	//	AtlevelNum1->setProperty(strLevelNum , "Image/CandyGame/Others/imgreslt.png",16, 26, "0");  
	//	AtlevelNum1->setPosition( ccp(123, 64));
	//	AtlevelNum1->setVisible( true );
	//	pItemImg->addChild( AtlevelNum1 );

	//	UITextArea* pFriendnamdbg = UITextArea::create();
	//	pFriendnamdbg->setAnchorPoint( ccp(0.5f, 0.5f));
	//	pFriendnamdbg->setPosition( ccp(126, 4) );
	//	pFriendnamdbg->setFontSize( 20 );
	//	pFriendnamdbg->setTextHorizontalAlignment( kCCTextAlignmentCenter );
	//	pFriendnamdbg->setTextVerticalAlignment( kCCVerticalTextAlignmentTop );
	//	pFriendnamdbg->setTextAreaSize( CCSizeMake(150, 100));
	//	pFriendnamdbg->setColor( ccc3(200,200,200));
	//	pFriendnamdbg->setText( CCString::createWithFormat( "%s", p->nickname.c_str())->getCString());
	//	pFriendnamdbg->setVisible( true );
	//	pItemImg->addChild( pFriendnamdbg );

	//	UITextArea* pFriendnamd = UITextArea::create();
	//	pFriendnamd->setAnchorPoint( ccp(0.5f, 0.5f));
	//	pFriendnamd->setPosition( ccp(125, 5) );
	//	pFriendnamd->setFontSize( 20 );
	//	pFriendnamd->setTextHorizontalAlignment( kCCTextAlignmentCenter );
	//	pFriendnamd->setTextVerticalAlignment( kCCVerticalTextAlignmentTop );
	//	pFriendnamd->setTextAreaSize( CCSizeMake(150, 100));
	//	pFriendnamd->setColor( ccc3(255,255,255));
	//	pFriendnamd->setText( CCString::createWithFormat( "%s", p->nickname.c_str())->getCString());
	//	pFriendnamd->setVisible( true );
	//	pItemImg->addChild( pFriendnamd );


	//	if ( 0 == p->click_timestamp && p->id != AnalyseJson::logOnMsg.baseInfo.id )
	//	{
	//		UIButton* pSloveImg = UIButton::create();
	//		pSloveImg->setNormalTexture( "Image/MainMapUi/btn_handlife2N.png" );
	//		pSloveImg->setPressedTexture( "Image/MainMapUi/btn_handlife2P.png" );
	//		pSloveImg->setDisabledTexture ( "Image/MainMapUi/btn_handlife2P.png" );
	//		pSloveImg->setTag( BUTTON_TO_HANDLELIFE );
	//		pSloveImg->setTouchEnable( true );
	//		pSloveImg->setVisible( true );
	//		pSloveImg->isEffects( true );
	//		pSloveImg->setPosition(ccp(138, 117));
	//		pSloveImg->data = (void*)p->id;
	//		pSloveImg->addReleaseEvent(this, coco_releaseselector(CandyResultLayer::ShareBtnCb)); 
	//		pItemImg->addChild( pSloveImg );

	//	}

	//	if ( p->id == AnalyseJson::logOnMsg.baseInfo.id)
	//		myRank = i+1;

	//	UIImageView* pdivdeline2 = UIImageView::create();
	//	pdivdeline2->setTexture( "Image/MainMapUi/buyItem/line_divdeline2.png" );
	//	pdivdeline2->setPosition(ccp(200, 80));
	//	pdivdeline2->setVisible( true );
	//	pItemImg->addChild( pdivdeline2 );
	//}

	////　我的排行
	//UILabelAtlas *pBtnToRank = dynamic_cast<UILabelAtlas*>(stageIntroLayout->getChildByName("LablemyRank"));
	//pBtnToRank->setStringValue( CCString::createWithFormat( "%d", myRank)->getCString() );

// 	  	UIWidget *pwidgt = plistView->getInnerContainer();
// 	  	pwidgt->setPosition(ccp(-215*(myRank-2),0));
}

void CandyStageIntroLayout::releaseStageIntroLayout(void)
{
	//CC_SAFE_RELEASE_NULL(stageIntroLayout);
}

void CandyStageIntroLayout::updatePropNum(int type)
{
	int propNum = CommonData::getPropNum((CandyPropType)type);
	int i = 0;
	switch (type)
	{
	case CANDY_PROP_OUT_DOUBLE:
		i = 0;
		break;
	case CANDY_PROP_OUT_COLORFULL:
		i = 1;
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		i = 2;
		break;
	}

	if(CommonData::getPropUseState((CandyPropType)type))
	{
		PropBuy[i]->setVisible(false);
		PropNumBg[i]->setVisible(false);
		PropSelected[i]->setVisible(true);
	}
	else if( propNum >0)
	{
		PropBuy[i]->setVisible(false);
		PropNumBg[i]->setVisible(true);
		PropNumLabel[i]->setVisible(true);
		PropNumLabel[i]->setStringValue(CCString::createWithFormat("%d",propNum)->getCString());
		PropSelected[i]->setVisible(false);
	}
	else
	{
		PropBuy[i]->setVisible(true);
		PropNumBg[i]->setVisible(false);
		PropSelected[i]->setVisible(false);
	}

	if ( CommonData::getPropNum( (CandyPropType)type ) )
		PropPriceShow[i]->setVisible( false );

// 	if ( 3 == CommonData::m_gamemode)
// 	{
// 		PropButton[0]->disable( false );
// 		PropBuy[0]->setVisible( false );
// 		PropNumBg[0]->setVisible( false );
// 		PropNumLabel[0]->setVisible( false );
// 		PropSelected[0]->setVisible( false );
// 	}

	//1~5关禁用游戏外道具
	//int m = AnalyseJson::logOnMsg.stageInfo.size();
	//if ( 5 >= CandyManager::currentLevel)
	//{
	//	if ( m == 5 )
	//	{
	//		for( int i = 0; i<3; i++)
	//		{
	//			PropBuy[i]->setVisible(true);
	//			PropNumBg[i]->setVisible( true );
	//			PropNumLabel[i]->setVisible( true );
	//			PropButton[i]->active(true);
	//		}
	//	}
	//	else
	//	{
	//		for( int i = 0; i<3; i++)
	//		{
	//			PropButton[i]->disable();
	//			PropBuy[i]->setVisible(false);
	//			PropNumBg[i]->setVisible( false );
	//			PropNumLabel[i]->setVisible( false );
	//		}
	//	}
	//}	

}
int CandyStageIntroLayout::TypeToCordinate(int type)
{
	int i = 0;
	switch(type)
	{
	case CANDY_PROP_OUT_DOUBLE:
		i = 0;
		break;
	case CANDY_PROP_OUT_COLORFULL:
		i = 1;
		break;
	case CANDY_PROP_OUT_BOMBNEW:
		i = 2;
		break;
	}
	return i;
}

void CandyStageIntroLayout::buyProp(int type)
{
	//int propPrice[CANDY_PROP_NUM] = {0,0,5,5,5,8,8,8};
	CCSprite *waitingSpr = CCSprite::create("Image/CandyGame/Others/NetWaiting.png");
	waitingSpr->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f,90)));
	int i = TypeToCordinate(type);
	PropButton[i]->getRenderer()->addChild(waitingSpr,0,BUY_PROP_LOADING_TAG);
}

void CandyStageIntroLayout::buyPropCb(int propId)
{
	int i = TypeToCordinate(type);
	CCNode *waitingSpr = PropButton[i]->getRenderer()->getChildByTag(BUY_PROP_LOADING_TAG);
	if(waitingSpr)
		waitingSpr->removeFromParent();
}

void CandyStageIntroLayout::stageInfoPlayCallBack(CCObject *pSender)
{
	switch(type)
	{
	case STAGE_INTRO_PLAY_GAME:
		CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
		CandyManager::getInstance()->resultMgr->getResultLayer()->stageInfoPlayGame();
		CommonData::setButtonTouchEnable( pSender, false);
		break;

	case STAGE_INTRO_MAIN_MAP:

		MainMapUiLayer::m_mainmapuilayer->LevelInfoNextCB(pSender);

		break;
	}
}

void CandyStageIntroLayout::stageInfoReturnCallBack(CCObject *pSender)
{
	switch(type)
	{
		case STAGE_INTRO_PLAY_GAME:
			CandyManager::getInstance()->resultMgr->getResultLayer()->gameNextReturnCallBack(NULL);
			CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
			CommonData::setButtonTouchEnable( pSender, false);
			break;

		case STAGE_INTRO_MAIN_MAP:
			MainMapUiLayer::m_mainmapuilayer->LevelInfoReturnCB(NULL);
			break;
	}
}

void CandyStageIntroLayout::stageInfoUsePropCallBack(CCObject *pSender)
{
	int i;
	for(i=0; i<3; i++)
		if(PropButton[i] == pSender)
			break;

	if(i>=3)
		return;	

	CandyPropType propType;

	switch(i)
	{
	case 0:
		propType = CANDY_PROP_OUT_DOUBLE ;
		break;
	case 1:
		propType = CANDY_PROP_OUT_COLORFULL ;
		break;
	case 2:
		propType = CANDY_PROP_OUT_BOMBNEW ;
		break;
	}
	int currentPropNum = CommonData::getPropNum(propType);
	if(CommonData::getPropUseState(propType))
	{
		CommonData::setPropUseState(propType, false);
	}
	else if(currentPropNum <= 0)
	{
#if defined(DEMO_FOR_MOBILE)||defined(DEMO_FOR_GUEST)
		switch(type)
		{
		case STAGE_INTRO_PLAY_GAME:
			{
				if ( CommonData::checkGoodsPriceEnough( propType ))
				{
					CandyManager::getInstance()->resultMgr->getResultLayer()->showPropBuy();
				}
				else
				{
					Layout* widget  = CandyStageIntro::getLayout(STAGE_INTRO_PLAY_GAME,CandyManager::currentLevel);
					if(widget)
					{
						CandyManager::getInstance()->resultMgr->getResultLayer()->setpropId(propType);

						widget->runAction(CCSequence::create(
							CandyManager::getInstance()->resultMgr->getResultLayer()->getMoveAction(false,0.7f, ccp(0,TARGET_SCREEN_HEIGHT)),
							CCCallFunc::create(this, callfunc_selector(CandyStageIntroLayout::showPropBuy)), 
							NULL)
							);
						CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
					}
				}
			}
			break;
		case STAGE_INTRO_MAIN_MAP:
			MainMapUiLayer::m_mainmapuilayer->showPropInfoBuy( propType );
			break;
		}
#endif
	}
	else
	{
		CommonData::setPropUseState(propType, true);
	}
	updatePropNum(propType);
}

//************************************
// Method:    showPropBuy
// FullName:  CandyStageIntroLayout::showPropBuy
// Access:    private 
// Returns:   void
// Qualifier: 弹出购买道具界面
//************************************
void CandyStageIntroLayout::showPropBuy()
{
	CandyManager::getInstance()->resultMgr->getResultLayer()->showPropBuy();
}

CandyStageIntroLayout* CandyStageIntro::layout = NULL;

Layout* CandyStageIntro::getLayout(StageIntroType type,int level)
{
	if(!layout)
	{
		layout = new CandyStageIntroLayout();
		layout->autorelease();
		layout->retain();
		layout->type = type;
	}
	return layout->getStageIntroLayout(level);
}

void CandyStageIntro::releaseLayout(void)
{
	if(layout)
	{
		layout->releaseStageIntroLayout();
		CC_SAFE_RELEASE_NULL(layout);
	}
}

void CandyStageIntro::buyPropCallBack(int propId)
{
	// 	if(statae)
	// 		CommonData::changePropNum((CandyPropType)propId, 1);
	if(layout)
	{
		layout->buyPropCb(propId);
		layout->updatePropNum(propId);
	}

}
