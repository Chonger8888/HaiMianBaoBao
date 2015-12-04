#include "CandyInterludeAction.h"
#include "../CommonData/CommonData.h"
#include "../Loading/LoadingScene.h"

#include "CandyManager.h"
#include "PlayGameScene.h"

#define CANDY_INTERLUDE_LAYOUT_FILE "Image/CandyGame/CandyInterludeUI/InterludeUI.json"

CandyInterlude::CandyInterlude():
m_pInterludeLayer(NULL),
m_Interludelayer(NULL),
m_countnextNum(0),
m_isLoop(true)
{

}

CandyInterlude::~CandyInterlude()
{
//	CC_SAFE_RELEASE_NULL(m_pInterludeLayer);

//	CCAnimationCache::purgeSharedAnimationCache();
}

void CandyInterlude::onEnter(void)
{
	CCLayer::onEnter();
	scheduleUpdate();
}

void CandyInterlude::onExit(void)
{
	CCLayer::onExit();

	CommonData::ReleaseXml();
}

CCScene* CandyInterlude::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		CCLayer *layer;
		layer= CandyInterlude::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool CandyInterlude::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	m_Interludelayer = UILayer::create();
	this->addChild( m_Interludelayer);

	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;

	m_pInterludeLayer = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDY_INTERLUDE_LAYOUT_FILE));
	m_pInterludeLayer->setZOrder( 20 );
	m_Interludelayer->addWidget( m_pInterludeLayer ); 

#ifdef CANDY_STATISITICAL_DATA
		//AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_49);
#endif

	UIImageView* pIWemeIco = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "wemeico" ));
	pIWemeIco->setPosition(ccp(360,fixedScreenHeight*0.5f));

	UIImageView* pGlobe = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "Gloab" ));
	CCActionInterval* rotate = CCRotateBy::create(4.5f, -34.0f);
	pGlobe->runAction(
		CCSequence::create(
		rotate,
		CCCallFunc::create(this, callfunc_selector(CandyInterlude::GloabActionStop)),
		NULL)
		);

	UIImageView* planghua = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "langhua" ));
	planghua->setZOrder( 20 );
	CCArmature *armature1 = CCArmature::create("NewProject");
	armature1->getAnimation()->playByIndex(0);
	armature1->setZOrder( 25 );
	armature1->setPosition(ccp(0,0));
	planghua->getRenderer()->addChild(armature1);

	UIImageView* pshu1 = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "actionshu1" ));
	UIImageView* pshu2 = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "actionshu2_0" ));

	UIImageView* pcao1 = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "xiaocao1" ));
	UIImageView* pcao2 = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "xiaocao2" ));

	CCArmature *armatureShu1 = CCArmature::create("NewProject");
	armatureShu1->getAnimation()->playByIndex(2);
	armatureShu1->setZOrder( 25 );
	armatureShu1->setScale( 0.7f );
	armatureShu1->setRotation( 100 );
	armatureShu1->setPosition(ccp(0,0));
	pshu1->getRenderer()->addChild( armatureShu1,13);

	CCArmature *armatureShu2 = CCArmature::create("NewProject");
	armatureShu2->getAnimation()->playByIndex(2);
	armatureShu2->setZOrder( 25 );
	armatureShu2->setRotation( 120 );
	armatureShu2->setPosition(ccp(0,0));
	pshu2->getRenderer()->addChild(armatureShu2);

	CCArmature *armaturecao1 = CCArmature::create("NewProject");
	armaturecao1->getAnimation()->playByIndex(1);
	armaturecao1->setZOrder( 25 );
	armaturecao1->setScale( 0.7f );
	armaturecao1->setRotation( 100 );
	armaturecao1->setPosition(ccp(0,0));
	pcao1->getRenderer()->addChild( armaturecao1,13);

	CCArmature *armaturecao2 = CCArmature::create("NewProject");
	armaturecao2->getAnimation()->playByIndex(1);
	armaturecao2->setZOrder( 25 );
	armaturecao2->setRotation( 20 );
	armaturecao2->setPosition(ccp(0,0));
	pcao1->getRenderer()->addChild(armaturecao2);


	UIImageView* pPeople1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1" ));
	CCArmature *pPeople1 = CCArmature::create( "guochang" );
	pPeople1->getAnimation()->playByIndex(0);
	pPeople1->setZOrder( 25 );
	pPeople1->setTag( Anim_Interlude_People1_Audience01 );
	pPeople1->setPosition(ccp(0,0));
	pPeople1Img->getRenderer()->addChild( pPeople1 );

	UIImageView* pPeople2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2" ));
	CCArmature *pPeople2 = CCArmature::create( "tuzi" );
	pPeople2->getAnimation()->play( "Animation2" );
	pPeople2->setZOrder( 25 );
	pPeople2->setRotation( 110 );
	pPeople2->setTag( Anim_Interlude_People2_Audience01 );
	pPeople2->setPosition(ccp(0,0));
	pPeople2Img->getRenderer()->addChild(pPeople2);


	UIImageView* ptaiyangImg = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "taiyang" ));
	UIImageView* pyun1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun1" ));
	UIImageView* pyun2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun2" ));

	ptaiyangImg->runAction( CCMoveTo::create(20.0f , ccp(0 - 50, ptaiyangImg->getPosition().y)));


	pyun1Img->runAction( 
		CCSequence::create(
		CCMoveTo::create(24.0f , ccp(0 - 50, pyun1Img->getPosition().y)),
		CCCallFuncND::create(this, callfuncND_selector(CandyInterlude::RunActionFunND), (void*)RunAction_interlude_FunCb_Cloud1),
		NULL));

	pyun2Img->runAction( 
		CCSequence::create(
		CCMoveTo::create(27.0f , ccp(0 - 50, pyun2Img->getPosition().y)),
		CCCallFuncND::create(this, callfuncND_selector(CandyInterlude::RunActionFunND), (void*)RunAction_interlude_FunCb_Cloud2),
		NULL));

	return true;

}

void CandyInterlude::RunActionFunND(CCNode* sender, void* data)
{
	int index = (int) data;
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	
	switch( index )
	{
	case RunAction_interlude_FunCb_Cloud1:
		{
			UIImageView* pyun1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun1" ));
			pyun1Img->setPosition( ccp(currentScreenWidth-15, pyun1Img->getPosition().y ));
			pyun1Img->runAction( 
				CCSequence::create(
				CCMoveTo::create(24.0f , ccp(0 - 50, pyun1Img->getPosition().y)),
				CCCallFuncND::create(this, callfuncND_selector(CandyInterlude::RunActionFunND), (void*)RunAction_interlude_FunCb_Cloud1),
				NULL));
		}

		break;
	case RunAction_interlude_FunCb_Cloud2:
		{
			UIImageView* pyun2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun2" ));
			pyun2Img->setPosition( ccp(currentScreenWidth-10, pyun2Img->getPosition().y ));
			pyun2Img->runAction( 
				CCSequence::create(
				CCMoveTo::create(27.0f , ccp(0 - 50, pyun2Img->getPosition().y)),
				CCCallFuncND::create(this, callfuncND_selector(CandyInterlude::RunActionFunND), (void*)RunAction_interlude_FunCb_Cloud2),
				NULL));
		}
		break;

	}

}

void CandyInterlude::GloabActionStop(void)
{
	UIImageView* pPeople1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1" ));
	CCArmature *pPeople1 = (CCArmature*)pPeople1Img->getRenderer()->getChildByTag( Anim_Interlude_People1_Audience01 );
 	pPeople1->getAnimation()->playByIndex( 1 );

	UIImageView* pPeople2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2" ));
	CCArmature *pPeople2 = (CCArmature*)pPeople2Img->getRenderer()->getChildByTag( Anim_Interlude_People2_Audience01 );
	pPeople2->getAnimation()->play( "Animation1" );
	pPeople2->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyInterlude::onmovementEvent1));
}

void CandyInterlude::onmovementEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if ((id.compare("Animation1") == 0)&& m_isLoop)
		{	
			m_isLoop = false;
			UIImageView* pPeople2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2" ));
			CCArmature *pPeople2 = (CCArmature*)pPeople2Img->getRenderer()->getChildByTag( Anim_Interlude_People2_Audience01 );
			pPeople2->getAnimation()->playByIndex( 1 );

			UIImageView* pPeople1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1" ));
			CCArmature *pPeople1 = (CCArmature*)pPeople1Img->getRenderer()->getChildByTag( Anim_Interlude_People1_Audience01 );
			pPeople1->getAnimation()->playByIndex( 3 );


			UIButton* pButSkip = dynamic_cast<UIButton*>(m_pInterludeLayer->getChildByName( "skipBut" ));
			UIButton* pButNext = dynamic_cast<UIButton*>(m_pInterludeLayer->getChildByName( "NextBut" ));
			pButSkip->setVisible( true );
			pButSkip->isEffects(true);
			pButSkip->setZOrder( 20 );
			pButSkip->setTag( Anim_Interlude_Skip_But );
			pButSkip->setTouchEnabled( true );
			pButSkip->addReleaseEvent(this, coco_releaseselector(CandyInterlude::InterludeButCallBack));

			pButNext->setVisible( true );
			pButNext->isEffects( true );
			pButNext->setZOrder( 20 );
			pButNext->setTag( Anim_Interlude_Next_But );
			pButNext->setTouchEnabled( true );
			pButNext->addReleaseEvent(this, coco_releaseselector(CandyInterlude::InterludeButCallBack));

			UIImageView* pPeople1Say = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1Say" ));
			UIImageView* pPeople2Say = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2Say" ));
			UITextArea* pPeople1Text = dynamic_cast<UITextArea*>(m_pInterludeLayer->getChildByName( "people1saystr" ));
			pPeople1Text->setText( CommonData::GetString("app_people1_say1").c_str());
			pPeople1Say->setVisible( true );
			pPeople2Say->setVisible( false );
		}
	}

}

void CandyInterlude::onmovementEvent2(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if ((id.compare("Animation4") == 0))
		{	
			UIPanel* pGloabPanel = dynamic_cast<UIPanel*>(m_pInterludeLayer->getChildByName( "GloabLaye" ));
			pGloabPanel->runAction( CCSequence::create(
				CCMoveTo::create(0.40f , ccp(0,-CCDirector::sharedDirector()->getWinSize().height)),
				CCCallFunc::create(this, callfunc_selector(CandyInterlude::GloabActionExit)),
				NULL));
		}
	}

}

void CandyInterlude::InterludeButCallBack(CCObject *pSender)
{
	UIButton* pInterludeBut = (UIButton*)pSender;
	UIImageView* pPeople1Say = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1Say" ));
	UIImageView* pPeople2Say = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2Say" ));


	if (Anim_Interlude_Skip_But == pInterludeBut->getTag())
	{
#ifdef CANDY_STATISITICAL_DATA
		/*if ( 0 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_51);
		else if ( 1 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_53);
		else if ( 2 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_55);*/
#endif


		UIPanel* pGloabPanel = dynamic_cast<UIPanel*>(m_pInterludeLayer->getChildByName( "GloabLaye" ));
		pGloabPanel->runAction( CCSequence::create(
			CCMoveTo::create(0.40f , ccp(0,-CCDirector::sharedDirector()->getWinSize().height)),
			CCCallFunc::create(this, callfunc_selector(CandyInterlude::GloabActionExit)),
			NULL));
	}
	else if (Anim_Interlude_Next_But == pInterludeBut->getTag())
	{

#ifdef CANDY_STATISITICAL_DATA
		/*if ( 0 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_50);
		else if ( 1 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_52);
		else if ( 2 == m_countnextNum )
			AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_54);*/
#endif

		m_countnextNum++;
		if ( 2 == m_countnextNum)
		{
			UITextArea* pPeople1Text = dynamic_cast<UITextArea*>(m_pInterludeLayer->getChildByName( "people1saystr" ));
			pPeople1Text->setText( CommonData::GetString("app_people1_say2").c_str());
			pPeople1Say->setVisible( true );
			pPeople2Say->setVisible( false );

			UIImageView* pPeople1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1" ));
			CCArmature *pPeople1 = (CCArmature*)pPeople1Img->getRenderer()->getChildByTag( Anim_Interlude_People1_Audience01 );
			pPeople1->getAnimation()->playByIndex( 2 );
			//pPeople1->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyInterlude::onmovementEvent2));

			UIPanel* pGloabPanel = dynamic_cast<UIPanel*>(m_pInterludeLayer->getChildByName( "GloabLaye" ));
			pGloabPanel->runAction( CCSequence::create(
				CCDelayTime::create(2),
				CCMoveTo::create(0.40f , ccp(0,-CCDirector::sharedDirector()->getWinSize().height)),
				CCCallFunc::create(this, callfunc_selector(CandyInterlude::GloabActionExit)),
				NULL));

		}
		else if ( 2 < m_countnextNum)
		{
			UIPanel* pGloabPanel = dynamic_cast<UIPanel*>(m_pInterludeLayer->getChildByName( "GloabLaye" ));
			pGloabPanel->runAction( CCSequence::create(
				CCMoveTo::create(0.40f , ccp(0,-CCDirector::sharedDirector()->getWinSize().height)),
				CCCallFunc::create(this, callfunc_selector(CandyInterlude::GloabActionExit)),
				NULL));
		}
		else
		{
			if (pPeople1Say->isVisible())
			{
				UITextArea* pPeople2Text = dynamic_cast<UITextArea*>(m_pInterludeLayer->getChildByName( "people2saystr" ));
				pPeople2Text->setText( CommonData::GetString("app_people2_say1").c_str());
				pPeople1Say->setVisible( false );
				pPeople2Say->setVisible( true );
			}
			else if (pPeople2Say->isVisible())
			{
				UITextArea* pPeople1Text = dynamic_cast<UITextArea*>(m_pInterludeLayer->getChildByName( "people1saystr" ));
				pPeople1Text->setText( CommonData::GetString("app_people1_say2").c_str());
				pPeople1Say->setVisible( true );
				pPeople2Say->setVisible( false );
			}
		}

		
	}
}

void CandyInterlude::GloabActionExit(void)
{
	UIImageView* pPeople2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people2" ));
	CCArmature *pPeople2 = (CCArmature*)pPeople2Img->getRenderer()->getChildByTag( Anim_Interlude_People2_Audience01 );
	pPeople2->removeFromParent();

	UIImageView* pPeople1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "people1" ));
	CCArmature *pPeople1 = (CCArmature*)pPeople1Img->getRenderer()->getChildByTag( Anim_Interlude_People1_Audience01 );
	pPeople1->removeFromParent();

	UIPanel* pGloabPanel = dynamic_cast<UIPanel*>(m_pInterludeLayer->getChildByName( "GloabLaye" ));
	pGloabPanel->stopAllActions();

	UIImageView* ptaiyangImg = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "taiyang" ));
	UIImageView* pyun1Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun1" ));
	UIImageView* pyun2Img = dynamic_cast<UIImageView*>(m_pInterludeLayer->getChildByName( "yun2" ));
	ptaiyangImg->stopAllActions();
	pyun1Img->stopAllActions();
	pyun2Img->stopAllActions();


	stopAllActions();
	m_Interludelayer->removeWidget( m_pInterludeLayer );

	Loading::replaceScence(CANDY_SCENCE_PLAY_GAME);
}