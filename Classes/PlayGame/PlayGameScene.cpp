#include "PlayGameScene.h"
#include "CandyManager.h"
#include "../MsgMgr/MsgMgr.h"
#include "../MsgMgr/AnalyseJson.h"
#include "../CppCallJava/CppCallJava.h"
#include "CandyInterludeAction.h"
USING_NS_CC;


#define CANDY_BG_IMG			"Image/CandyGame/Background/Bg"
#define CANDY_BG_TAG			101


PlayGame* PlayGame::currentLayer = NULL;

#if 1 //just for test
bool crazyMode = false;	

static CCSprite *bar = NULL;
static int barNum;
float timeCount;

CCLabelTTF *levelLabel ;

void PlayGame::startCrazyHappyMode(cocos2d::CCObject *pSender)
{
	if(crazyMode == false)
		{
			crazyMode = true;
				
			bar->setTextureRect(CCRectMake(0, 0, 0, 27));
			barNum = 412;
			timeCount = 5.0f;
		}
}

void PlayGame::crazyModeUpdateTest(float time)
{
	if(crazyMode == true)
		{
			if(timeCount >0)
				{
					bar->setTextureRect(CCRectMake(0, 0, timeCount/10.0f * barNum, 27));
					timeCount = timeCount - time;
				}
			else				{
					crazyMode = false;
				}
		}
}

void PlayGame::lastLevelCallBack(cocos2d::CCObject *pSender)
{
	CandyManager::currentLevel--;
	if(CandyManager::currentLevel < 1)
		CandyManager::currentLevel = 225;
	
	CCScene *pScene = PlayGame::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PlayGame::nextLevelCallBack(cocos2d::CCObject *pSender)
{
	CandyManager::currentLevel++;
	if(CandyManager::currentLevel >225)
		CandyManager::currentLevel = 1;
	
	CCScene *pScene = PlayGame::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PlayGame::addTestMenu(void)
{
#ifdef WIN32

#elif  defined(DEMO_FOR_GUEST) || defined(DEMO_FOR_MOBILE)
	return;
#endif

#ifndef CANDY_VERSIONS_FOR_SINGLE		
#if 1//def WIN32
	bar = CCSprite::create("LoadingLayerBar.png");
	this->addChild(bar);
	bar->setPosition( ccp(100, 300) );
	bar->setAnchorPoint(ccp(0.0,0.5));
	bar->setTextureRect(CCRectMake(0, 0, 0, 27));

	CCMenuItemImage *pIconConfirm = CCMenuItemImage::create(
									"XiaoChu1.png",
									"XiaoChu1_active.png",
									this,
									menu_selector(PlayGame::startCrazyHappyMode));

	CCMenuItemImage *lastLevel = CCMenuItemImage::create(
									"lastLevelNormal.png",
									"lastLevelSelect.png",
									this,
									menu_selector(PlayGame::lastLevelCallBack));
	CCMenuItemImage *nextLevel = CCMenuItemImage::create(
									"nextLevelNormal.png",
									"nextLevelSelect.png",
									this,
									menu_selector(PlayGame::nextLevelCallBack));
	
// 	levelLabel = CCLabelTTF::create(CCString::createWithFormat("level: %d",CandyManager::currentLevel)->getCString(),  "Arial", 60);
// 	levelLabel->setColor(ccRED);
// 	this->addChild(levelLabel);	

	levelLabel = CCLabelTTF::create(CCString::createWithFormat("Ver:1.1.0")->getCString(),  "Arial", 10);
	levelLabel->setColor(ccc3(150,150,150));
	this->addChild(levelLabel);	

	float fixedScreenHeight = CandyShare::getFixedScreenHeight();
	
	if(fixedScreenHeight >= SCREEN_DEMARCATION1_HEIGHT)
		{
			float offsetY = fixedScreenHeight -TARGET_SCREEN_HEIGHT;
			lastLevel->setPosition(ccp(50+60,1215+offsetY));
			nextLevel->setPosition(ccp(50+160,1215+offsetY));
			#ifdef DEMO_FOR_NEW_UI
			lastLevel->setPosition(ccp(250+60,1100+offsetY));
			nextLevel->setPosition(ccp(250+160,1100+offsetY));
			#endif
			pIconConfirm->setPosition(ccp(250,200));
			levelLabel->setPosition(ccp(320,1080+ 125+offsetY));

			
		}
	else
		{
			lastLevel->setPosition(ccp(60,185));
			nextLevel->setPosition(ccp(160,185));
			pIconConfirm->setPosition(ccp(120,225));
			levelLabel->setPosition(ccp(600,200));
		}
	
	CCMenu* pMenu = CCMenu::create(pIconConfirm,
	#ifdef WIN32
		lastLevel, nextLevel,
	#endif
		NULL);
  	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,100000);	
#endif
#endif

}

#endif

extern bool drawBgAgain ;

bool PlayGame::init(void)
{
	if ( !CCLayer::init() )
		{
			return false;
		}
	lastMixGridState = false;
	scheduleUpdate();

	CommonData::initLevelTaskStarNum();
	CandyManager::getInstance();
	return true;
}
void PlayGame::update(float time)
{
	CandyManager::getInstance()->updateStates(time);
	crazyModeUpdateTest(time);

	if(drawBgAgain)
		addBg(lastMixGridState);
}

void PlayGame::onEnter(void)
{
	CCLayer::onEnter();
	
#ifdef CANDY_STATISITICAL_DATA
	//新用户记录点
	if (AnalyseJson::logOnMsg.baseInfo.isNewUser)
	{
		AnalyseJson::setRecordingMsg( RECODING_MSG_ACTIONID_1007);
	}

	/*if ( 0 == CommonData::getMaxLevel()  )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_57 );
	else if( 1 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_73 );
	else if( 2 == CommonData::getMaxLevel() )
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_83 );

	if ( 10 >= CommonData::getMaxLevel() ) 
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_13, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());

	if (1 == CandyManager::currentLevel && 10 >= CommonData::getMaxLevel() ) 
		AnalyseJson::setRecordingMsg(RECODING_MSG_ACTIONID_17, CCString::createWithFormat("%d",CandyManager::currentLevel)->getCString());*/
#endif

	CandyManager::getInstance()->setCurrentLayer(this);
	CandyManager::getInstance()->startCandyGame();

	addBg(false);
	addTestMenu();
	this->schedule(schedule_selector(PlayGame::updateLife), 1.0f);
}

void PlayGame::updateLife(float dt)
{
}
void PlayGame::onExit(void)
{
	CandyManager::getInstance()->purgeInstance();
	CCLayer::onExit();
}

CCScene* PlayGame::scene(void)
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		currentLayer= PlayGame::create();
		CC_BREAK_IF(! currentLayer);

		scene->addChild(currentLayer);
	} while (0);

	return scene;
}

void PlayGame::addGameBg(void)
{
	this->removeChildByTag(CANDY_BG_TAG);

	CCSprite *bg1;
	int bgImgNum = (CandyManager::currentLevel-1)/15 +1;

	bg1 = CCSprite::create(CCString::createWithFormat("%s%d.jpg",CANDY_BG_IMG,bgImgNum)->getCString());
	if(bg1)
	{
		bg1->setAnchorPoint(ccp(0,0));
		bg1->setPosition( ccp(0,0) );
	}

	addChild(bg1,-10,CANDY_BG_TAG);
}

void PlayGame::addBg(bool mixGrid)
{
	lastMixGridState = mixGrid;
	drawBgAgain = false;
	
	this->removeChildByTag(CANDY_BG_TAG);
	  
	int bgImgNum = (CandyManager::currentLevel-1)/15 +1;
	
	CCSprite *bg1;
	bg1 = CCSprite::create(CCString::createWithFormat("%s6.jpg",CANDY_BG_IMG)->getCString());
	 if(bg1)
	 	{
	 		bg1->setAnchorPoint(ccp(0,0));
			bg1->setPosition( ccp(0,0) );
	 	}

	/*CCSprite *bg2;
	bg2 = CCSprite::create("Image/CandyGame/Background/BgMask.png");
	if(bg2)
	{
		bg2->setAnchorPoint(ccp(0,0));
		bg2->setPosition( ccp(0,0) );
	}*/

	CCRenderTexture* texture = CCRenderTexture::create(720, 1280);
	texture->begin();
	bg1->visit();
	//bg2->visit();
	if(mixGrid)
		{
			CandyManager::getInstance()->bgGridMgr->createGridsVisit();
		}
		
	texture->end();
	
	if(mixGrid)
		{
			CandyManager::getInstance()->bgGridMgr->removeBgGrid();
		}
	else
		{
			//格子底图
			CandyManager::getInstance()->bgGridMgr->createBgGrid();
		}
	
	CCSprite* ret = CCSprite::createWithTexture(texture->getSprite()->getTexture());
	ret->setFlipY(true);
	ret->setAnchorPoint(ccp(0.0,0.0));
	ret->setPosition(ccp(0,0));
	addChild(ret,-10,CANDY_BG_TAG);

}
