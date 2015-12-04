#include "CandyRouletteStory.h"
#include "CommonMacro.h"
#include "../Loading/LoadingScene.h"

#define CANDY_ROULETTE_STORY_LAYOUT_FILE "Image/CandyGame/CandyRouletteStory/CandyRouletteStory.ExportJson"

CandyRouletteStory::CandyRouletteStory()
{

}

CandyRouletteStory::~CandyRouletteStory()
{
	CCTextureCache::sharedTextureCache()->removeTextureForKey("Image/CandyGame/CandyRouletteStory/CandyRouletteStory0.png");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("Image/CandyGame/CandyRouletteStory/CandyRouletteStory1.png");  
	CCTextureCache::sharedTextureCache()->removeTextureForKey("Image/CandyGame/CandyRouletteStory/CandyRouletteStory2.png");  

}

void CandyRouletteStory::onEnterTransitionDidFinish(void)
{
	CCSize designSize = CCSizeMake(TARGET_SCREEN_WIDTH,  TARGET_SCREEN_HEIGHT);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height,kResolutionShowAll);	
}
void CandyRouletteStory::onExitTransitionDidStart(void)
{

}
void CandyRouletteStory::onEnter(void)
{
	CCLayer::onEnter();
}
void CandyRouletteStory::onExit(void)
{
	CCLayer::onExit();
}
CCScene* CandyRouletteStory::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		CCLayer *layer= CandyRouletteStory::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}
bool CandyRouletteStory::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
 	CCSize size = CCDirector::sharedDirector()->getWinSize();
 	m_RouletteStoryLayer = UILayer::create();
 	this->addChild( m_RouletteStoryLayer);
 
 	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
 	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;
 	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;
 
 	m_pLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDY_ROULETTE_STORY_LAYOUT_FILE));
 	m_RouletteStoryLayer->addWidget( m_pLayout ); 
 
 	m_pImage1 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1" ));
 	m_pImage1_role1 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1_role1" ));
 	m_pImage1_role2 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1_role2" ));
 	m_pImage1_dialogue1 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1_dialogue_1" ));
 	m_pImage1_dialogue2 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1_dialogue_2" ));
 	m_pImage1_candy = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image1_candy" ));
 
 	m_pImage2 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image2" ));
 	m_pImage2_role1 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image2_role1" ));
 	m_pImage2_role2 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image2_role2" ));
 	m_pImage2_dialogue = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image2_dialogue" ));
 	m_pImage2_paopao = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image2_role_paopao" ));
 	
 	m_pImage3 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image3" ));
 	m_pImage3_role1 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image3_role1" ));
 	m_pImage3_role2 = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image3_role2" ));
 	m_pImage3_dialogue = dynamic_cast<UIImageView*>(m_pLayout->getChildByName( "Image3_dialogue" ));
 	m_pImage3_button = dynamic_cast<UIButton*>(m_pLayout->getChildByName( "ButtonTry"));
 	m_pImage3_button->isEffects(true);
 	m_pImage3_button->addReleaseEvent(this, coco_releaseselector(CandyRouletteStory::ButtonCallBack));
 
 	m_pImage1->setVisible(false);
 	m_pImage1_candy->setVisible(false);
 	m_pImage1_role1->setVisible(false);
 	m_pImage1_role2->setVisible(false);
 	m_pImage1_dialogue1->setVisible(false);
 	m_pImage1_dialogue2->setVisible(false);
 	
 	m_pImage2->setVisible(false);
 	m_pImage2_role1->setVisible(false);
 	m_pImage2_role2->setVisible(false);
 	m_pImage2_dialogue->setVisible(false);
 	m_pImage2_paopao->setVisible(false);
 
 	m_pImage3->setVisible(false);
 	m_pImage3_role1->setVisible(false);
 	m_pImage3_role2->setVisible(false);
 	m_pImage3_dialogue->setVisible(false);
 	m_pImage3_button->setVisible(false);
 	m_pImage3_button->setTouchEnable(true);

 	CCProgressTo *to = CCProgressTo::create(0.7f, 100);
 	CCSprite *pSpr = CCSprite::createWithSpriteFrameName("jc011__1.png");
 	CCProgressTimer *progress = CCProgressTimer::create(pSpr);
 	progress->setType(kCCProgressTimerTypeBar);
 	progress->setMidpoint(ccp(0.5f, 0.5f));
 	progress->setBarChangeRate(ccp(1,1));
 	m_pLayout->addCCNode(progress);
 	CCPoint pos = m_pImage1->getPosition();
 	progress->setPosition(pos);
 	progress->runAction(CCSequence::create(
 		to,
 		CCDelayTime::create(0.5f),
 		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::StartTheStory)),
 		NULL
 		));

	return true;
}
void CandyRouletteStory::StartTheStory()
{
	m_pImage1->setVisible(true);
	m_pImage1_candy->setVisible(true);
	m_pImage1_candy->setScale(0.0f);
	
	m_pImage1_role1->setVisible(true);
	m_pImage1_role1->setScale(0.0f);

	m_pImage1_role2->setVisible(true);
	m_pImage1_role2->setScale(0.0f);

	m_pImage1_role1->runAction(getAppearAction());

	m_pImage1_candy->runAction(CCSequence::create(
		CCDelayTime::create(0.2f),
		getAppearAction(),
		NULL
		));

	m_pImage1_role2->runAction(CCSequence::create(
		CCDelayTime::create(0.4f),
		getAppearAction(),
		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::candyAppearCb)),
		NULL));

}
CCActionInterval* CandyRouletteStory::getAppearAction()
{
	CCActionInterval*  actionScale1 = CCScaleTo::create(0.13f, 1.1f);
	CCActionInterval*  actionScale2 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* pAct =CCSequence::create(
		actionScale1,
		actionScale2,
		NULL);
	return pAct;
}
void CandyRouletteStory::candyAppearCb()
{
	m_pImage1_dialogue1->setVisible(true);
	m_pImage1_dialogue1->setScale(0.45f);
	m_pImage1_dialogue1->setOpacity(0);

	m_pImage1_dialogue2->setVisible(true);
	m_pImage1_dialogue2->setScale(0.45f);
	m_pImage1_dialogue2->setOpacity(0);

	m_pImage1_dialogue1->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		CCFadeIn::create(0.001f),
		getAppearAction(),
		NULL
		));
	m_pImage1_dialogue2->runAction(CCSequence::create(
		CCDelayTime::create(1.1f),
		CCFadeIn::create(0.001f),
		getAppearAction(),
		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::Image2Appear)),
		NULL
		));
}
void CandyRouletteStory::Image2Appear()
{
	m_pImage2->setVisible(true);
	CCPoint pos = m_pImage2->getPosition();
	m_pImage2->setPosition(ccp(pos.x-1000,pos.y));
	m_pImage2->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		CCMoveBy::create(0.3f,ccp(1000,0)),
		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::Image2RoleAppear)),
		NULL
		));
}
void CandyRouletteStory::Image2RoleAppear()
{
	CCPoint pos;
	m_pImage2_role1->setVisible(true);
	pos = m_pImage2_role1->getPosition();
	m_pImage2_role1->setPosition(ccp(pos.x+1000,pos.y));
	m_pImage2_role1->runAction(CCSequence::create(
		CCMoveBy::create(0.5f,ccp(-990,0)),
		CCMoveBy::create(1.0f,ccp(-10,0)),
		NULL
		));

	m_pImage2_role2->setVisible(true);
	pos = m_pImage2_role2->getPosition();
	m_pImage2_role2->setPosition(ccp(pos.x-1000,pos.y));
	m_pImage2_role2->runAction(CCSequence::create(
		CCMoveBy::create(0.5f,ccp(990,0)),
		CCMoveBy::create(1.0f,ccp(10,0)),
		NULL
		));

	m_pImage2_paopao->setVisible(true);
	m_pImage2_paopao->setOpacity(0);
	m_pImage2_paopao->runAction(CCSequence::create(
		CCDelayTime::create(0.6f),
		CCFadeIn::create(0.17f),
		CCSpawn::create(CCScaleTo::create(0.4f,1.02f),CCFadeOut::create(0.4f),NULL),
		NULL
		));

	m_pImage2_dialogue->setVisible(true);
	m_pImage2_dialogue->setScale(0.45f);
	m_pImage2_dialogue->setOpacity(0);
	m_pImage2_dialogue->runAction(CCSequence::create(
		CCDelayTime::create(1.2f),
		CCFadeIn::create(0.001f),
		CCScaleTo::create(0.13f,1.02f),
		CCScaleTo::create(0.2f,1.0f),
		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::Image3Appear)),
		NULL
		));
}

void CandyRouletteStory::Image3Appear()
{
	m_pImage3->setVisible(true);
	CCPoint pos = m_pImage3->getPosition();
	CCSize size = m_pImage3->getContentSize();
	m_pImage3->setPosition(ccp(pos.x+size.width,pos.y+size.height/2));
	m_pImage3->setScale(0.5f);
	m_pImage3->runAction(CCSequence::create(
		CCDelayTime::create(1.1f),
		CCSpawn::create(CCScaleTo::create(0.3f,1.0f),CCMoveBy::create(0.3f,ccp(-size.width,-size.height/2)),NULL),
		CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::Image3RoleAppear)),
		NULL
		));
}

void CandyRouletteStory::Image3RoleAppear()
{
	m_pImage3_role1->setVisible(true);
	m_pImage3_role1->setOpacity(0);
	m_pImage3_role1->runAction(CCSequence::create(
		CCSpawn::create(CCFadeIn::create(0.5f),CCRotateBy::create(0.25f,90),NULL),
		NULL
		));
	m_pImage3_role2->setVisible(true);
	m_pImage3_role2->setOpacity(0);
	m_pImage3_role2->runAction(CCSequence::create(
		CCDelayTime::create(0.15f),
		CCSpawn::create(CCFadeIn::create(0.25f),CCRotateBy::create(0.25f,90),NULL),
		NULL
		));

	m_pImage3_dialogue->setVisible(true);
	m_pImage3_dialogue->setScale(0.45f);
	m_pImage3_dialogue->setOpacity(0);
	m_pImage3_dialogue->runAction(CCSequence::create(
		CCDelayTime::create(0.45f),
		CCFadeIn::create(0.001f),
		CCScaleTo::create(0.13f,1.02f),
		CCScaleTo::create(0.2f,1.0f),
		//CCDelayTime::create(1.4f),
		//CCCallFunc::create(this,callfunc_selector(CandyRouletteStory::Image3End)),
		NULL
		));
	m_pImage3_button->setDisPlayEffects();
}

void CandyRouletteStory::Image3End()
{
}

void CandyRouletteStory::ButtonCallBack(CCObject *pSender)
{
	Loading::replaceScence(CANDY_SCENCE_PLAY_GAME);
}