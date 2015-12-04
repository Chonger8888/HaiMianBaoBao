#include "CandyCommon.h"
#include "CandyRouletteNew.h"
#include "CandyManager.h"

#define CANDY_ROULETTE_LAYOUT_FILE "Image/CandyGame/CandyGameRoulette/CandyRoulette.json"
#define ROULETTE_MOVE_LEN				1280
#define ROULETTE_MOVE_LEN2				950
#define ROULETTE_MOVE_TIME				1.2f
#define ROULETTE_ANIM_MOVE_LEN			300

#define RABBIT_STAND_POS_X				size.width/2+260
#define RABBIT_STAND_POS_Y				size.height/2+750 

#define RABBIT_FALL_LEN					790

CandyRouletteLayer::CandyRouletteLayer():
m_nRouletteSpecialtype(0),
m_nRouletteSpecialNum(0),
m_nRouletteNumRotate(0.0f),
m_nRouletteTypeRotate(0.0f),
m_bPressed(false)
{
	m_pRouletteLayout = NULL;
	m_pRouletteStartBtn = NULL;
	m_pRouletteBgImg = NULL;
	m_pRouletteNumImg = NULL;
//	m_pRouletteTypeImg = NULL;
	m_pAudiences = NULL;
// 	m_pRabbitAnim01 = NULL;
//	m_pRabbitAnim02 = NULL;
	m_pIndiaRabbitAnim = NULL;
	m_pStart = NULL;
	m_pStick = NULL;
	m_pLight0 = NULL;
	m_pLight1 = NULL;
	m_pLight2 = NULL;
	m_pLight3 = NULL;
	m_pContain = NULL;
	m_pLight = NULL;
	m_pCounter = NULL;
}

CandyRouletteLayer::~CandyRouletteLayer()
{
	CC_SAFE_RELEASE_NULL(m_pRouletteLayout);
	CC_SAFE_RELEASE_NULL(m_pRouletteStartBtn);
	CC_SAFE_RELEASE_NULL(m_pRouletteBgImg);
	CC_SAFE_RELEASE_NULL(m_pRouletteNumImg);
//	CC_SAFE_RELEASE_NULL(m_pRouletteTypeImg);

	CCAnimationCache::purgeSharedAnimationCache();
}

bool CandyRouletteLayer::init()
{
	if(!UILayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_BG_ROULETTE);

	m_pRouletteLayout = dynamic_cast<Layout*>(CCUIHELPER->createWidgetFromJsonFile(CANDY_ROULETTE_LAYOUT_FILE));
	m_pRouletteLayout->retain();
	m_pRouletteLayout->setTouchEnable(true);
	//todo...	测试不加retain 不add,是否自动释放
	this->addWidget(m_pRouletteLayout);

	m_pRouletteStartBtn = dynamic_cast<UIButton*>(m_pRouletteLayout->getChildByName("RouletteStartBtn"));
	m_pRouletteStartBtn->addReleaseEvent(this,coco_releaseselector(CandyRouletteLayer::StartBtnCallBack));
	m_pRouletteStartBtn->setVisible(false);
 	CCPoint originalPos = m_pRouletteStartBtn->getPosition();
 	float fixedScreenHeight = CandyShare::getFixedScreenHeight();
 	m_pRouletteStartBtn->setPosition(ccp(originalPos.x , originalPos.y - 100 + (fixedScreenHeight -TARGET_SCREEN_HEIGHT) ));
	m_pRouletteStartBtn->retain();

	m_pStart= CCArmature::create("qidong");
	this->addChild(m_pStart);
	m_pStart->setPosition(ccp(originalPos.x , originalPos.y - 100 + (fixedScreenHeight -TARGET_SCREEN_HEIGHT) ));
	m_pStart->setVisible(false);
	m_pStart->getAnimation()->play("Animation3");
	m_pStart->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyRouletteLayer::StartAnimationEvent));
	
	m_pRouletteBgImg = dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteBgImg"));
	m_pRouletteBgImg->retain();
	m_pRouletteBgImg->setPosition(ccp(size.width/2, size.height/2+190+ROULETTE_MOVE_LEN2));

	m_pRouletteNumImg = dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteNumImg"));
	m_pRouletteNumImg->retain();


	int count = 24;
	CCArray* presenters = CCArray::createWithCapacity(count);
	for(int i = 0;i < count;i++){
		int type = i%3;
		CCSprite *pSpr = CCSprite::create(CCString::createWithFormat("Image/CandyGame/Others/candy%d.png",type)->getCString());
		presenters->addObject(pSpr);
	}
	m_pCounter = Counter::create(presenters);
	UIImageView *pImgCenter = dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteCenter"));
	pImgCenter->addCCNode(m_pCounter);
	m_pCounter->setZOrder(1000);
	m_pCounter->setPosition(ccp(0,0));


 	UIImageView* pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteBack"));
  	CCPoint pos = pImg->getPosition();
  	pImg->setPosition(ccp(pos.x, pos.y + ROULETTE_MOVE_LEN+200));
//  	pImg->runAction(CCSequence::create(
// 		CCEaseBackIn::create(CCMoveBy::create(ROULETTE_MOVE_TIME,ccp(0,-ROULETTE_MOVE_LEN))),
//  		CCDelayTime::create(0.5f),
//  		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RouletteLightUp)),
//  		NULL));

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuTop"));
	pImg->setPosition(ccp(size.width/2, size.height+32));
	pImg->runAction(CCSequence::create(
		CCEaseElasticInOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(size.width/2,size.height-32)),0.9f),
		NULL));

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuLeft"));
	pImg->setPosition(ccp(-180, size.height/2));
	pImg->runAction(CCSequence::create(
		CCEaseElasticInOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(size.width/2-177,size.height/2)),0.9f),
		NULL));

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuRight"));
	pImg->setPosition(ccp(size.width+180, size.height/2));
	pImg->runAction(CCSequence::create(
		CCEaseElasticInOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(size.width/2+177,size.height/2)),0.9f),
		CCDelayTime::create(0.6f),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RouletteLightUp)),
		NULL));

	initArmature();

	initAnimation();

	return true;
}
void CandyRouletteLayer::initAnimation(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	m_pStick = CCSprite::create();
	this->addChild(m_pStick,1);

	UIImageView* pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteBack"));

	m_pLight0 = CCSprite::create();
	pImg->getRenderer()->addChild(m_pLight0);
	m_pLight0->setPosition(ccp(15-size.width/2,size.height/2-320-size.height/2));

	m_pLight1 = CCSprite::create();
	pImg->getRenderer()->addChild(m_pLight1);
	m_pLight1->setPosition(ccp(15-size.width/2,size.height/2+320-size.height/2));

	m_pLight2 = CCSprite::create();
	pImg->getRenderer()->addChild(m_pLight2);
	m_pLight2->setPosition(ccp(size.width-15-size.width/2,size.height/2-320-size.height/2));

	m_pLight3 = CCSprite::create();
	pImg->getRenderer()->addChild(m_pLight3);
	m_pLight3->setPosition(ccp(size.width-15-size.width/2,size.height/2+320-size.height/2));
}

void CandyRouletteLayer::initArmature(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCArmature *pArmature = NULL;
 	m_pAudiences = CCNode::create();
 	this->addChild(m_pAudiences);

 	pArmature= CCArmature::create("Audience01");
 	pArmature->setTag(Anim_Roulette_Audience01);
 	m_pAudiences->addChild(pArmature);
 	pArmature->setPosition(ccp(690,1280-1240-25));
 
 	pArmature= CCArmature::create("Audience02");
 	pArmature->setTag(Anim_Roulette_Audience02);
 	m_pAudiences->addChild(pArmature);
 	pArmature->setPosition(ccp(310,1280-1345-50));
 
 	pArmature= CCArmature::create("Audience03");
 	pArmature->setTag(Anim_Roulette_Audience03);
 	m_pAudiences->addChild(pArmature);
 	pArmature->setPosition(ccp(180,1280-1325-50));
   
  	pArmature= CCArmature::create("Audience04");
  	pArmature->setTag(Anim_Roulette_Audience04);
  	m_pAudiences->addChild(pArmature);
  	pArmature->setPosition(ccp(30,1280-1260-65));
 
 	pArmature= CCArmature::create("Audience05");
 	pArmature->setTag(Anim_Roulette_Audience05);
 	m_pAudiences->addChild(pArmature);
 	pArmature->setPosition(ccp(470,1280-1335-20));
 
 	m_pAudiences->setPosition(ccp(0,-ROULETTE_ANIM_MOVE_LEN));

// 	m_pRabbitAnim01= CCArmature::create("NewProject");
// 	this->addChild(m_pRabbitAnim01);
// 	m_pRabbitAnim01->setPosition(ccp(RABBIT_STAND_POS_X,RABBIT_STAND_POS_Y));
// 	m_pRabbitAnim01->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyRouletteLayer::animationEvent));
 
//   	m_pRabbitAnim02= CCArmature::create("NewProject1");
//   	this->addChild(m_pRabbitAnim02);
//  	m_pRabbitAnim02->setPosition(ccp(RABBIT_STAND_POS_X,RABBIT_STAND_POS_Y));

	m_pIndiaRabbitAnim= CCArmature::create("huipanzi");
	this->addChild(m_pIndiaRabbitAnim);
	m_pIndiaRabbitAnim->setPosition(ccp(RABBIT_STAND_POS_X,RABBIT_STAND_POS_Y+100));
	m_pIndiaRabbitAnim->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyRouletteLayer::IndiaAnimationEvent));


}

void CandyRouletteLayer::RouletteLightUp(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//窗帘拉开
	UIImageView *pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuTop"));
	pImg->runAction(CCSequence::create(
		CCEaseElasticOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(size.width/2, size.height+50)),0.8f),
		NULL));

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuLeft"));
	pImg->runAction(CCSequence::create(
		CCEaseElasticOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(-190, size.height/2)),0.8f),
		NULL));

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteLianbuRight"));
	pImg->runAction(CCSequence::create(
		CCEaseElasticOut::create(CCMoveTo::create(ROULETTE_MOVE_TIME,ccp(size.width+190, size.height/2)),0.8f),
		NULL));

	this->stopAllActions();
	this->runAction(CCSequence::create(
		CCDelayTime::create(0.8f),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RouletteFall)),
		NULL
		));
	//背景图出现 打开灯光
	m_pLight = UINodeContainer::create();
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_LIGHT,  ccp(0,size.height/2), m_pLight->getRenderer());

	pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteBack"));
	pImg->setPosition(ccp(size.width/2, size.height/2));
	pImg->addChild(m_pLight);
	m_pLight->setPosition(ccp(0,0));

	m_pRouletteBgImg->setPosition(ccp(size.width/2, size.height/2+190));
}

void CandyRouletteLayer::RouletteFall(void)
{
// 	m_pRouletteBgImg->runAction(CCSequence::create(
// 		CCEaseIn::create(CCMoveBy::create(ROULETTE_MOVE_TIME,ccp(0,-ROULETTE_MOVE_LEN2)),3.0f),
// 		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RabbitFall)),
// 		NULL
// 		));

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pAudiences->runAction(CCSequence::create(
		CCMoveBy::create(ROULETTE_MOVE_TIME,ccp(0,ROULETTE_ANIM_MOVE_LEN)),
		NULL
		));
	RabbitFall();
}

void CandyRouletteLayer::RabbitFall(void)
{
// 	m_pRabbitAnim01->runAction(CCSequence::create(
// 		CCEaseIn::create(CCMoveBy::create(0.5f,ccp(0,-RABBIT_FALL_LEN)),3.0f),
// 		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RabbitAction1)),
// 		NULL
// 		));
	RabbitAction1();
}

void CandyRouletteLayer::RabbitAction1(void)
{
//	m_pRabbitAnim01->getAnimation()->play("Animation1");
	m_pRouletteStartBtn->setTouchEnable(true);
	m_pStart->setVisible(true);


	CCActionInterval*  pActionNum = CCRotateBy::create(14400, -360*2000);
	m_pRouletteNumImg->runAction(pActionNum);

}

void CandyRouletteLayer::animationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
// 	CCSize size = CCDirector::sharedDirector()->getWinSize();
// 	std::string nid = movementID;
// 
// 	if (movementType == LOOP_COMPLETE)
// 	{
// 		if(nid.compare("Animation1") == 0)
// 		{
// 			m_pRabbitAnim01->getAnimation()->play("Animation2");
// 
// 			m_pRouletteStartBtn->setVisible(true);
// 			m_pRouletteStartBtn->isEffects(true,0,true,false);
// 			m_pRouletteStartBtn->setTouchEnable(true);
// 		}
// 		else if(nid.compare("Animation2") == 0)
// 		{
// 			m_pRabbitAnim01->getAnimation()->play("Animation3");
// 		}
// 		else if(nid.compare("Animation3") == 0)
// 		{
// 			if(m_bPressed)
// 			{
// 				m_pRabbitAnim01->getAnimation()->play("Animation4");
// 			}
// 		}
// 		else if(nid.compare("Animation4") == 0)
// 		{
// 			m_pRabbitAnim01->getAnimation()->play("Animation5");
// 			PlayStick();
// 		}
// 	}
}

void CandyRouletteLayer::PlayStick(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/CandyGame/RouletteAnim/Stick/NewProject0.plist");

	CCAnimationCache::purgeSharedAnimationCache();
	CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("Image/CandyGame/RouletteAnim/Stick/animations.plist");

	CCAnimation *playstick = CCAnimationCache::sharedAnimationCache()->animationByName("playstick");
	playstick->setRestoreOriginalFrame(true);
	playstick->setDelayPerUnit(0.6f/18.0f);

	CCAnimate *stick_act = CCAnimate::create(playstick);
	CCSequence *seq = CCSequence::create(stick_act,CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RabbitAction2)),NULL);

	m_pStick->runAction(seq);
	m_pStick->setPosition(ccp(RABBIT_STAND_POS_X-40,RABBIT_STAND_POS_Y - RABBIT_FALL_LEN+13));
}

void CandyRouletteLayer::RabbitAction2(void)
{
//  	CCSize size = CCDirector::sharedDirector()->getWinSize();
// // 	
// // 	m_pRabbitAnim01->removeFromParent();
// // 
//  	m_pRabbitAnim02->setPosition(ccp(RABBIT_STAND_POS_X,RABBIT_STAND_POS_Y - RABBIT_FALL_LEN));
//  	m_pRabbitAnim02->getAnimation()->playByIndex(0);
}

void CandyRouletteLayer::StartBtnCallBack(CCObject *pSender)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	m_bPressed = true;
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_BUTTON);
	CommonData::setButtonTouchEnable( pSender, false);
	m_pRouletteStartBtn->setVisible(false);

	m_pStart->getAnimation()->stop();
	m_pStart->getAnimation()->play("Animation2");

	m_pIndiaRabbitAnim->setPosition(ccp(RABBIT_STAND_POS_X+35,RABBIT_STAND_POS_Y - RABBIT_FALL_LEN+5));
	m_pIndiaRabbitAnim->setScale(0.2f);
	m_pIndiaRabbitAnim->getAnimation()->playByIndex(0);
	m_pIndiaRabbitAnim->runAction(CCSequence::create(
		CCScaleTo::create(0.04f,1.05f),
		CCScaleTo::create(0.2f,1.0f),
		CCMoveBy::create(0.63f,ccp(0,3)),
		CCMoveBy::create(0.63f,ccp(0,-3)),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::IndiaRabbitAction1)),
		NULL));

	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SHENDENGZHAKAI_EFFECT,ccp(0,0),m_pIndiaRabbitAnim,0,100);

	RouletteInCallback();
}

void CandyRouletteLayer::IndiaRabbitAction1(void)
{
	m_pIndiaRabbitAnim->getAnimation()->play("Animation2");

}

void CandyRouletteLayer::IndiaAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	std::string nid = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if(nid.compare("Animation2") == 0)
		{
			m_pIndiaRabbitAnim->getAnimation()->play("Animation3");
		}
		else if(nid.compare("Animation3") == 0)
		{
			m_pIndiaRabbitAnim->getAnimation()->play("Animation4");
		}
	}
}
void CandyRouletteLayer::StartAnimationEvent(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string nid = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if(nid.compare("Animation2") == 0)
		{
			m_pIndiaRabbitAnim->getAnimation()->play("Animation1");
		}
	}
}


void CandyRouletteLayer::RouletteInCallback(void)
{
// 	int randNum = rand()%360;
// 	if(randNum%120 < 5)
// 		randNum +=5;
// 
// 	else if(randNum%120 > (120-5))
// 		randNum -=5;

//   	float nPassedTypeRoulette = m_pRouletteTypeImg->getRotation()-20;
//   	int temp = (int)nPassedTypeRoulette % 360;
//   	m_nRouletteTypeRotate = 360*11 + (360-abs(temp)) + randNum;
//   	m_nRouletteSpecialtype = 2 -((int)(m_nRouletteTypeRotate - (360-abs(temp))) %360)/120;

	int randNum = rand()%100;

	if(randNum<20)
	{
		m_nRouletteSpecialtype = 0;
		m_pCounter->animation(21);
	}
	else if(randNum<55)
	{
		m_nRouletteSpecialtype = 1;
		m_pCounter->animation(22);
	}
	else if(randNum<100)
	{
		m_nRouletteSpecialtype = 2;
		m_pCounter->animation(23);
	}
	

	float nPassedNumRoulette = m_pRouletteNumImg->getRotation()-140;
	int temp = (int)nPassedNumRoulette % 360;
	m_nRouletteNumRotate = 360 *5 +(360-abs(temp)) + AdjustRouletteProbability();

	CCActionInterval*  rouletteNumAction = CCRotateBy::create(7, -m_nRouletteNumRotate);
//	CCActionInterval*  rouletteTypeAction = CCRotateBy::create(7, m_nRouletteTypeRotate);

	CCActionInterval*  rouletteNumEase = CCEaseInOut::create(rouletteNumAction, 2.0f);
//	CCActionInterval*  rouletteTypeEase = CCEaseInOut::create(rouletteTypeAction, 2.0f);


 	m_pRouletteNumImg->stopAllActions();
 	m_pRouletteNumImg->runAction(CCSequence::create(
 		rouletteNumEase,
 		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::AudienceCheer)),
 		NULL));

	m_pRouletteNumImg->runAction(CCSequence::create(
		CCDelayTime::create(0.5f),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RotateMusicCallback)),
		NULL));

}

void CandyRouletteLayer::RotateMusicCallback(void)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_ROULETTE_IN);
}

void CandyRouletteLayer::AudienceCheer(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_CHEER);

	if(m_pContain == NULL)
	{
		m_pContain = UINodeContainer::create();
		m_pRouletteBgImg->addChild(m_pContain);
	}
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_ROULETEE_END,  ccp(0,0), m_pContain->getRenderer());
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_ROULETEE_EDGE,  ccp(0,0), m_pContain->getRenderer());

	m_pContain->setPosition(ccp(0,0));
	m_pContain->setZOrder(-1);

	CCArray *pArray = m_pAudiences->getChildren();
	if(pArray != NULL && pArray->count()!=0)
	{
		CCObject *iter = NULL;
		CCARRAY_FOREACH(pArray,iter){
			CCArmature *pArm = (CCArmature*)iter;
			pArm->getAnimation()->playByIndex(0);
		}
	}

	this->runAction(CCSequence::create(
		CCDelayTime::create(1.5f),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RotateDoneCallback)),
		NULL
		));

	LightAtTheEnd();
}

void CandyRouletteLayer::LightAtTheEnd(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pLight0->stopAllActions();
	m_pLight1->stopAllActions();
	m_pLight2->stopAllActions();
 	m_pLight3->stopAllActions();
 
 	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/CandyGame/RouletteAnim/Light/LightAtTheEnd0.plist");
 
 	CCAnimationCache::purgeSharedAnimationCache();
	CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("Image/CandyGame/RouletteAnim/Light/animations.plist");
 
 	CCAnimation *LightEnd = CCAnimationCache::sharedAnimationCache()->animationByName("lightplay");
 	LightEnd->setRestoreOriginalFrame(true);
 
 	CCAnimate *playLight = CCAnimate::create(LightEnd);
	CCRepeatForever *pAct = CCRepeatForever::create(playLight);
	CCRepeatForever *pAct1 = (CCRepeatForever*)pAct->copy();
	CCRepeatForever *pAct2 = (CCRepeatForever*)pAct->copy();
 	CCRepeatForever *pAct3 = (CCRepeatForever*)pAct->copy();
 
	m_pLight0->runAction(pAct);
	m_pLight0->setFlipX(true);
	m_pLight1->runAction(pAct1);
	m_pLight1->setFlipX(true);
	m_pLight2->runAction(pAct2);
 	m_pLight3->runAction(pAct3);
}

void CandyRouletteLayer::RotateDoneCallback(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//转盘淡出
 	m_pRouletteBgImg->runAction(CCSequence::create(
 		CCFadeOut::create(1.8f),
 		NULL
 		));
	//背景淡出
	UIImageView* pImg =  dynamic_cast<UIImageView*>(m_pRouletteLayout->getChildByName("RouletteBack"));
	pImg->removeChild(m_pLight);
	pImg->stopAllActions();
	pImg->runAction(CCFadeOut::create(1.8f));
	//观众淡出
	CCArray *pArray = m_pAudiences->getChildren();
	if(pArray != NULL && pArray->count()!=0)
	{
		CCObject *iter = NULL;
		CCARRAY_FOREACH(pArray,iter){
			CCArmature *pArm = (CCArmature*)iter;
			pArm->stopAllActions();
			pArm->runAction(CCFadeOut::create(1.8f));
		}
	}
	//小兔子淡出
//  	if(m_pRabbitAnim02)
//  	{
//  		m_pRabbitAnim02->stopAllActions();
//  		m_pRabbitAnim02->runAction(CCFadeOut::create(1.8f));
//  	}
	if(m_pIndiaRabbitAnim)
	{
		m_pIndiaRabbitAnim->stopAllActions();
		m_pIndiaRabbitAnim->removeFromParent();
	}
	if(m_pStart)
	{
		m_pStart->stopAllActions();
		m_pStart->removeFromParent();
	}
	//
 	CCSprite *pSpr = NULL;
 	switch(m_nRouletteSpecialtype)
 	{
 	case 0:
 		pSpr = CCSprite::create("Image/CandyGame/Others/candy0.png");
 		break;
 	case 1:
 		pSpr = CCSprite::create("Image/CandyGame/Others/candy1.png");
 		break;
 	case 2:
 		pSpr = CCSprite::create("Image/CandyGame/Others/candy2.png");
 		break;
 	default:
 		break;
 	}
 	this->addChild(pSpr,3);
 
 	m_pCounter->setVisible(false);
 	pSpr->stopAllActions();
 	pSpr->setPosition(m_pCounter->getParent()->convertToWorldSpace(m_pCounter->getPosition()));
 	pSpr->runAction(CCSpawn::create(
 		CCSequence::create(CCMoveTo::create(2,ccp(size.width/2,size.height/2+150)),CCFadeOut::create(0.5f),NULL),
 		CCEaseOut::create(CCRotateBy::create(2,1800),0.5f),
 		CCScaleTo::create(2,2.0),
 		NULL
 		));
	//后方特效
	CCNode *pRewardLight = CCNode::create();
 	this->addChild(pRewardLight,2,99);
 	pRewardLight->stopAllActions();
	pRewardLight->setPosition(m_pCounter->getParent()->convertToWorldSpace(m_pCounter->getPosition()));
	pRewardLight->runAction(CCSequence::create(CCMoveTo::create(2.3f,ccp(size.width/2,size.height/2+150)),
		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::SpecialEffectCb)),
		NULL));
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_REWARD_LIGHT,  ccp(0,0), pRewardLight,101);

	this->stopAllActions();
 	this->runAction(CCSequence::create(
 		CCDelayTime::create(2.5f),
 		CCCallFunc::create(this, callfunc_selector(CandyRouletteLayer::RouletteOutCallback)),
 		NULL
 		));

	m_pRouletteBgImg->removeChild(m_pContain);
	m_pLight0->removeFromParent();
	m_pLight1->removeFromParent();
	m_pLight2->removeFromParent();
	m_pLight3->removeFromParent();
}
void CandyRouletteLayer::SpecialEffectCb()
{
	CCNode* pLight = this->getChildByTag(99);
	if(pLight)
	{
		pLight->removeChildByTag(101);
	}
}

void CandyRouletteLayer::RouletteOutCallback()
{
	/*startRunRoulette();*/
//	CandyManager::getInstance()->uiLayer->m_bReward = false;
	CandyManager::getInstance()->uiLayer->m_nRewardNum = m_nRouletteSpecialNum;
	CandyManager::getInstance()->uiLayer->m_nRewardType = m_nRouletteSpecialtype;

  	CandyManager::getInstance()->resultMgr->getResultLayer()->getUILayer()->removeChildByTag(RESULT_WIDGE_ROULETTE);
  	CandyManager::getInstance()->resultMgr->removeResultLayer();
  	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
 	CandyManager::getInstance()->uiLayer->resetEnergyJarPercentage();
	CandyManager::getInstance()->uiLayer->SpecialReward();
	//CandyManager::getInstance()->uiLayer->RabbitPutSugar();

	CandyManager::getInstance()->musicMgr->playBgm();
}

int CandyRouletteLayer::AdjustRouletteProbability(void)
{
	int resultNum =1;

	int randNum = rand()%100;
	if(m_nRouletteSpecialtype == 0)//colorful
	{
		if(randNum<45)
		{
			resultNum =1;
		}
		else if(randNum<75)
		{
			resultNum =2;
		}
		else if(randNum<90)
		{
			resultNum =3;
		}
		else if(randNum<98)
		{
			resultNum =4;
		}
		else
		{
			resultNum =5;
		}
	}
	else if(m_nRouletteSpecialtype == 1)//bomb
	{
		if(randNum<40)
		{
			resultNum =1;
		}
		else if(randNum<64)
		{
			resultNum =2;
		}
		else if(randNum<82)
		{
			resultNum =3;
		}
		else if(randNum<92)
		{
			resultNum =4;
		}
		else if(randNum<98)
		{
			resultNum =5;
		}
		else
		{
			resultNum =6;
		}
	}
	else if(m_nRouletteSpecialtype == 2)//strip
	{
		if(randNum<30)
		{
			resultNum =1;
		}
		else if(randNum<60)
		{
			resultNum =2;
		}
		else if(randNum<80)
		{
			resultNum =3;
		}
		else if(randNum<90)
		{
			resultNum =4;
		}
		if(randNum<95)
		{
			resultNum =5;
		}
		else
		{
			resultNum =6;
		}
	}
	m_nRouletteSpecialNum = resultNum + 2;
	return  (6-resultNum) *60 + 5 + rand()%35;
}