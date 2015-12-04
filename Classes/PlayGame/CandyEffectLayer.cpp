#include "CandyEffectLayer.h"
#include "CandyManager.h"

USING_NS_CC;

const int energyJarEffectTag[4] = {511,512,513,514};
const int propButtonEffectTag[4] = {611};
CCSprite* CandyEffectLayer::m_SelectWin = NULL;

CandyEffectLayer::~CandyEffectLayer()
{
	CC_SAFE_DELETE(m_SelectWin);
}

bool CandyEffectLayer::init(void)
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	useStepCount = 0;
	return true;
}

void CandyEffectLayer::onEnter(void)
{
	CCLayer::onEnter();
}

void CandyEffectLayer::onExit(void)
{
	CCLayer::onExit();
}

void CandyEffectLayer::displayEnergyJarEffect(void)
{
	CCNode* node =CandyManager::getInstance()->uiLayer->getEnergyJarNode();
	const int jarWidth = 210;
	const int jarHeight = 170;
	CCPoint bornPos[2]={ccp(-jarWidth*0.5f,-jarHeight*0.5f-10),ccp(jarWidth*0.5f,jarHeight*0.5f-10)};
	CCPoint movePoint[2][4] ={{ccp(0,jarHeight),ccp(jarWidth,0),ccp(0,-jarHeight),ccp(-jarWidth,0)},
						{ccp(0,-jarHeight),ccp(-jarWidth,0),ccp(0,jarHeight),ccp(jarWidth,0)}};
	const float moveTime = 0.5f;
	
	for(int i=0; i<2; i++)
		{
			if(node->getChildByTag(energyJarEffectTag[i]))
				continue;
			CCNode* particleNode = CandyParticle::displayCandyParticle(CANDY_PARTICLE_JAR,  bornPos[i],node,energyJarEffectTag[i]);
			particleNode->runAction(CCRepeatForever::create(CCSequence::create(
									CCMoveBy::create(moveTime,movePoint[i][0]),
									CCMoveBy::create(moveTime,movePoint[i][1]),
									CCMoveBy::create(moveTime,movePoint[i][2]),
									CCMoveBy::create(moveTime,movePoint[i][3]),
									NULL)));
		}
	if(!node->getChildByTag(energyJarEffectTag[2]))
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_JAR_FRONT,  ccp(0,0),node,energyJarEffectTag[2]);
	if(!node->getChildByTag(energyJarEffectTag[3]))
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_JAR_BACK,  ccp(0,0),node,energyJarEffectTag[3],-1);
}

void CandyEffectLayer::undisplayEnergyJarEffect(void)
{
	CCNode* node =CandyManager::getInstance()->uiLayer->getEnergyJarNode();
	if(node)
		for(int i=0; i<4; i++)
			node->removeChildByTag(energyJarEffectTag[i]);
}
	
void CandyEffectLayer::displayExplosionBombEffect(CandyIndex index,CandyColor color)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::colorfullCandyParticle(CANDY_PARTICLE_EXPLOSION, color);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_EXPLOSION,  pos);
}


void CandyEffectLayer::displayExchangeCandyEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_NORMAL_EXCHANGE,  pos);
}
	
void CandyEffectLayer::displaySingleNormalDispelEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_NORMAL_DISPEL,  pos);
}

void CandyEffectLayer::displayBombDispelEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_BOMB,  pos);
}

void CandyEffectLayer::displayHorizonDispelEffect(CandyIndex index, CandyColor color)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::colorfullCandyParticle(CANDY_PARTICLE_SPE_HORIZON, color);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_HORIZON,  pos);
}

void CandyEffectLayer::displayVerticalDispelEffect(CandyIndex index, CandyColor color)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::colorfullCandyParticle(CANDY_PARTICLE_SPE_VERTICAL, color);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_VERTICAL,  pos);
}

void CandyEffectLayer::displayCololfulDispelEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_EMIT,  pos);
}

void CandyEffectLayer::displayCololfulMainEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_FIRE,  pos);
}

void CandyEffectLayer::displayCololfulSubEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_TARGET,  pos);
}


void CandyEffectLayer::displayComBBEffect(CandyIndex index, CCCallFuncN *cb)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_COM_BB,  pos);

	CCNode *node = CCNode::create();
	addChild(node);
	node->runAction(CCSequence::create(
							CCDelayTime::create(0.65f),
							cb,
							CCCallFuncN::create(node, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
							NULL));
}

void CandyEffectLayer::displayComSSEffect(CandyIndex index,CandyColor colorH,CandyColor colorV)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::colorfullCandyParticle(CANDY_PARTICLE_COM_SS, colorH, colorV);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_COM_SS,  pos);
}

void CandyEffectLayer::displayComCCEffect(CCCallFuncN *cb)
{
	float fixedScreenHeight = CandyManager::getInstance()->shareMgr->getFixedScreenHeight();
	CCPoint pos = ccp(TARGET_SCREEN_WIDTH *0.5f, fixedScreenHeight * 0.5f);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_COM_CC, pos);

	CCSequence *action = CCSequence::create(CCDelayTime::create(0.8f),
										cb,
										NULL);
	runAction(action);
}

void CandyEffectLayer::displayColorEmit(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_EMIT,  pos);
}

void CandyEffectLayer::displayColorFire(CandyIndex origin, CandyIndex target, float delayTime)
{
	CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(target);
	CCPoint originPos = CandyManager::getInstance()->shareMgr->getPosByIndex(origin);
	CCPoint candyPos = CandyManager::getInstance()->shareMgr->getPosByIndex(candy->index);

	CCPointArray* pointArray = CCPointArray::create(2);
	pointArray->insertControlPoint(originPos,0);
	pointArray->insertControlPoint(candyPos,1);
	pointArray->retain();
	
	runAction(CCSequence::create(	CCDelayTime::create(delayTime),
								CCCallFuncND::create(NULL, callfuncND_selector(CandyEffectLayer::displayColorFireDelayCb), (void*)pointArray),
								NULL));

		
}

void CandyEffectLayer::displayColorFireDelayCb(CCNode* sender, void* data)
{
	CCPointArray* pointArray = (CCPointArray*)data;
	CCPoint originPos = pointArray->getControlPointAtIndex(0);
	CCPoint candyPos = pointArray->getControlPointAtIndex(1);
	CandyParticle::setCandyParticleMove(CANDY_PARTICLE_SPE_COLOR_FIRE, 300, candyPos.x - originPos.x, candyPos.y - originPos.y);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_FIRE,  originPos);
	
	pointArray->release();
}

void CandyEffectLayer::displayColorTarget(CandyIndex index, float delayTime)
{
	CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
	runAction(CCSequence::create(	CCDelayTime::create(delayTime),
								CCCallFuncND::create(NULL, callfuncND_selector(CandyEffectLayer::displayColorTargetDelayCb), (void*)candy),
								NULL));
}

void CandyEffectLayer::displayColorTargetDelayCb(CCNode* sender, void* data)
{
	CandyCell *candy = (CandyCell *)data;
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(candy->index);
	CandyParticle::colorfullCandyParticle(CANDY_PARTICLE_SPE_COLOR_TARGET, candy->color);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPE_COLOR_TARGET,  pos);
}

void CandyEffectLayer::displayComBSEffect1(CandyIndex index, CCCallFuncN *cb)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_COM_BS,  pos);
	
	CCNode *node = CCNode::create();
	addChild(node);
	node->runAction(CCSequence::create(
							CCDelayTime::create(0.95f),
							cb,
							CCCallFuncN::create(node, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
							NULL));
}

void CandyEffectLayer::displayChangeStripleEffect(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_CHANGE_STRIPLE,  pos);
}

void CandyEffectLayer::displayRouleteeMakeColor(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_RCOLOR,  pos);
}

void CandyEffectLayer::displayRouleteeMakeBomb(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_RBOMB,  pos);
}

void CandyEffectLayer::displayRouleteeMakeStrip(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_RSTRIP,  pos);
}
		
void CandyEffectLayer::displayBreakLicorices(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_LICORICES,  pos);
}

void CandyEffectLayer::displayBreakCream(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_CREAM,  pos);
}

void CandyEffectLayer::displayBreakJelly(CandyIndex index, int jellyNum)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	pos.y = pos.y +5;
	if(jellyNum ==2)
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_JEELY2,  pos);
	else
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_JEELY,  pos);
}

void CandyEffectLayer::displayBreakLock(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_LOCK,  pos);
}


void CandyEffectLayer::displayBreakChocolate(CandyIndex index)
{
	CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_BREAK_CHOCOLATE,  pos);
}


void CandyEffectLayer::displayUsingPropEffect(int type)
{
	CCSprite *sprite = NULL;
	
	switch(type)
		{
			case CANDY_PROP_OUT_STEP3:
				sprite = CCSprite::createWithSpriteFrameName("Image/MainMapUi/Prop/prop2.png");
				break;

			case CANDY_PROP_OUT_STRIP:
				sprite = CCSprite::createWithSpriteFrameName("Image/MainMapUi/Prop/prop3.png");
				break;

			case CANDY_PROP_OUT_BOMB:
				sprite = CCSprite::createWithSpriteFrameName("Image/MainMapUi/Prop/prop4.png");
				break;
			case CANDY_PROP_OUT_BOMBNEW:
				sprite = CCSprite::create("Image/MainMapUi/Prop/prop35.png");
				break;


			case CANDY_PROP_OUT_COLORFULL:
				sprite = CCSprite::create("Image/MainMapUi/Prop/prop34.png");
				break;

			case CANDY_PROP_OUT_DOUBLE:
				displayUsingPropEffectCb1(NULL);
				break;

			case CANDY_PROP_IN_STEP5:
				sprite = CCSprite::create("Image/MainMapUi/Prop/prop5.png");
				break;
			case CANDY_PROP_IN_RESORT:
				sprite = CCSprite::create("Image/MainMapUi/Prop/prop36.png");
				break;

			case CANDY_PROP_IN_SWAP:
			case CANDY_PROP_IN_HAMMER:
			case CANDY_PROP_IN_STRIP:
			case CANDY_PROP_IN_BOMB:
				displayUsingPropEffectCb1(NULL);
				return;
				
			default:
				sprite = CCSprite::create("Image/Prop5ButtonN.png");
				break;
		}
	
	if(!sprite)
		return;
	
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP3, ccp(0,0), sprite);
	
	sprite->setPosition(ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f));
	sprite->setScale(0.01f);
	addChild(sprite);
	sprite->runAction(CCSequence::create(	
										CCScaleTo::create(0.3f,2.0f),
										CCDelayTime::create(0.5f),
										CCCallFuncN::create(sprite, callfuncN_selector(CandyEffectLayer::displayUsingPropEffectCb0)),
										CCSpawn::create(CCFadeOut::create(0.6f),CCScaleTo::create(0.6f,0.1f), NULL),
										CCCallFuncN::create(sprite, callfuncN_selector(CandyEffectLayer::displayUsingPropEffectCb1)),
										CCCallFuncN::create(sprite, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
										NULL));

}

void CandyEffectLayer::displayUsingPropEffectCb0(CCNode* sender)
{
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP6,
							ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f));
}
	
void CandyEffectLayer::displayUsingPropEffectCb1(CCNode* sender)
{
	CCNode *node = CCNode::create();
	CandyManager::getInstance()->effectLayer->addChild(node);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP1,  ccp(0,0), node,123);
	CCPoint originPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f);
	CCPoint targetPos;
	float moveTime = 0.3f;
	switch(CommonData::currentPropType)
		{
			case CANDY_PROP_OUT_STEP3:
			case CANDY_PROP_IN_STEP5:
				targetPos = CandyManager::getInstance()->uiLayer->getStepNumLabelPos(); 
				break;

			case CANDY_PROP_OUT_DOUBLE:
				CandyParticle::displayCandyParticle(CANDY_PARTICLE_DOUBLESCORE_EFFECT, ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f));
				CandyManager::getInstance()->uiLayer->CandyScoreFire();
				originPos = ccp(TARGET_SCREEN_WIDTH*2, CandyShare::getFixedScreenHeight());
				targetPos = originPos;
				//targetPos = CandyManager::getInstance()->uiLayer->getScoreNumLabelPos(); 
				break;

			case CANDY_PROP_OUT_STRIP:
			case CANDY_PROP_OUT_BOMBNEW:
				originPos = CandyManager::getInstance()->uiLayer->getPropButtonPos();
				targetPos = CommonData::currentCandy->getPosition();
				break;

			case CANDY_PROP_IN_RESORT:
				targetPos = originPos;
				break;

			case CANDY_PROP_IN_HAMMER:
			case CANDY_PROP_IN_STRIP:
			case CANDY_PROP_IN_BOMB:
			case CANDY_PROP_OUT_BOMB:
			case CANDY_PROP_OUT_COLORFULL:
				originPos = CandyManager::getInstance()->uiLayer->getPropButtonPos();
				targetPos = CandyManager::getInstance()->shareMgr->getPosByIndex(CommonData::propSelectedIndex);
				break; 
		}
	node->setPosition(originPos);

	node->runAction(CCSequence::create(	CandyManager::getInstance()->shareMgr->getEffectBezierAction(originPos, targetPos),
		CCCallFuncN::create(node, callfuncN_selector(CandyEffectLayer::displayUsingPropEffectCb2)),
		NULL
		));

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_RESORT_TIPS);
}


//移动到目标点后的特效
void CandyEffectLayer::displayUsingPropEffectCb2(CCNode* sender)
{
	sender->getChildByTag(123)->setPosition(ccp(-1000,-1000));
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP2,sender->getPosition());

	if(CommonData::currentPropType == CANDY_PROP_IN_HAMMER )
	{
		CCPoint targetPos = CandyManager::getInstance()->shareMgr->getPosByIndex(CommonData::propSelectedIndex);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/CandyGame/RouletteAnim/harmer/harmer.plist");
		CCAnimationCache::purgeSharedAnimationCache();
		CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("Image/CandyGame/RouletteAnim/harmer/animations.plist");

		CCAnimation *playharmer = CCAnimationCache::sharedAnimationCache()->animationByName("playharmer");
		playharmer->setRestoreOriginalFrame(true);
		playharmer->setDelayPerUnit(2.0f/20);

		CCAnimate *harmer_act = CCAnimate::create(playharmer);

		CCSprite *pSpr = CCSprite::create();
		CandyManager::getInstance()->effectLayer->addChild(pSpr);
		pSpr->setPositionX(targetPos.x + 5);
		pSpr->setPositionY(targetPos.y - 28);
		pSpr->runAction(CCSequence::create(	
			harmer_act,
			NULL
			));
		pSpr->runAction(CCSequence::create(	
			CCDelayTime::create(1.0f),
			CCCallFuncN::create(pSpr, callfuncN_selector(CandyEffectLayer::displayUsingPropEffectCb2_Hammer)),
			CCDelayTime::create(0.5f),
			CCFadeOut::create(0.5f),
			NULL
			));
		
	}
	else 
	{
		CommonData::updateEffectingPropCb();
		sender->runAction(CCSequence::create(
			CCDelayTime::create(3.0f),
			CCCallFuncN::create(sender, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
			NULL));
	}
}

void CandyEffectLayer::displayUsingPropEffectCb2_Hammer(CCNode* sender)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_HAMMER);

	CandyParticle::displayCandyParticle(CANDY_PARTICLE_CHUNZI_EFFECT,ccp(64,122),sender,0,-1);

	CommonData::updateEffectingPropCb();
	sender->runAction(CCSequence::create(
		CCDelayTime::create(0.1f),
		CCFadeOut::create(0.45f),
		CCCallFuncN::create(sender, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
		NULL));
}

void CandyEffectLayer::displayPropLightEffect(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float fixedScreenHeight = CandyShare::getFixedScreenHeight();
	if(fixedScreenHeight>=SCREEN_DEMARCATION1_HEIGHT)
	{
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP7,ccp(size.width*0.5,size.height*0.5),NULL,889);
	}
	else
	{
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP7,ccp(size.width*0.5,size.height*0.5+120),NULL,889);
	}
}

void CandyEffectLayer::displayPropButtonEffect(void)
{
	CCNode* node =CandyManager::getInstance()->uiLayer->getPropButtonNode();
	const int buttonWidth = 90;
	const int buttonHeight = 90;
	CCPoint bornPos[2]=
	{
		ccp(-buttonWidth*0.5f,-buttonHeight*0.5f),
		ccp(buttonWidth*0.5f,buttonHeight*0.5f)
	};
	CCPoint movePoint[4][4] =
	{
		{ccp(0,buttonHeight),ccp(buttonWidth,0),ccp(0,-buttonHeight),ccp(-buttonWidth,0)},
		{ccp(0,-buttonHeight),ccp(-buttonWidth,0),ccp(0,buttonHeight),ccp(buttonWidth,0)},
		{ccp(0,-buttonHeight),ccp(-buttonWidth,0),ccp(0,buttonHeight),ccp(buttonWidth,0)},
		{ccp(0,-buttonHeight),ccp(-buttonWidth,0),ccp(0,buttonHeight),ccp(buttonWidth,0)},
	};
	const float moveTime = 0.5f;
	
	for(int i=0; i<4; i++)
	{
		if(node->getChildByTag(propButtonEffectTag[i]))
			continue;
		CCNode* particleNode = CandyParticle::displayCandyParticle(CANDY_PARTICLE_PROP_BUTTON,  bornPos[i],node,propButtonEffectTag[i]);
		particleNode->runAction(CCRepeatForever::create(CCSequence::create(
			CCMoveBy::create(moveTime,movePoint[i][0]),
			CCMoveBy::create(moveTime,movePoint[i][1]),
			CCMoveBy::create(moveTime,movePoint[i][2]),
			CCMoveBy::create(moveTime,movePoint[i][3]),
			NULL)));
	}
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_PRESS_PROP,ccp(0,0),node,654);
}

void CandyEffectLayer::undisplayPropButtonEffect(void)
{
	CCNode* node =CandyManager::getInstance()->uiLayer->getPropButtonNode();
	if(node)
		for(int i=0; i<4; i++)
			node->removeChildByTag(propButtonEffectTag[i]);
	node->removeChildByTag(654);

}

void CandyEffectLayer::displayPropSelectCellEffect(int type)
{
	/*CCPoint pos = CandyManager::getInstance()->shareMgr->getPosByIndex(CommonData::propSelectedIndex);
	if(type == CANDY_PROP_IN_SWAP)
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP5,  pos);
	else if(type == CANDY_PROP_IN_HAMMER)
		CandyParticle::displayCandyParticle(CANDY_PARTICLE_USE_PROP4,  pos);*/
}

void CandyEffectLayer::displayStageClearTipsExtraPre(void)
{
	CCLayerColor* grayLayer = CCLayerColor::create(ccc4(0,0,0,0));
	grayLayer->runAction(CCSequence::create(
		CCFadeTo::create(1.0f,170),
		CCCallFunc::create(this, callfunc_selector(CandyEffectLayer::displayStageClearTipsExtra)),
		NULL
		));
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(grayLayer,1,99);
}

void CandyEffectLayer::displayStageClearTipsExtra(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
//	CCNode *node = CandyParticle::displayCandyParticle(CANDY_PARTICLE_LIGHT,  ccp(size.width/2,size.height),CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer(),77,2);

	CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f);
	CCArmature *pArm = CCArmature::create("yingle");
	if(pArm != NULL)
	{
		pArm->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyEffectLayer::animationEvent1));
		pArm->getAnimation()->playByIndex(0);
		pArm->setPosition(targetPos);
		CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(pArm,3,89);

		pArm->runAction(CCSequence::create(CCDelayTime::create(1.5f),
			CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)0),
			CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
			CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)1),
			CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
			CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)2),
			CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
			CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)3),
			NULL));
	}
	

// 	CCSprite* sprite =  CCSprite::create("Image/CandyGame/Others/stageClearTipsExtra.png");
// 	CandyManager::getInstance()->uiLayer->addChild(sprite);

// 	CCPoint originalPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()+200.0f);
// 	CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f);
// 	sprite->setPosition(targetPos);
// 	sprite->setScale(1.0f);
// 	sprite->runAction(CCSequence::create(
// 		CCEaseBounceOut::create((CCActionInterval*)(CCScaleTo::create(1.0f, 1.0f))),
// 		CCDelayTime::create(1.0f),
// 		CCFadeOut::create(1.0f),
// 		CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
// 		NULL
// 		));
// 
// 	sprite->runAction(CCSequence::create(CCDelayTime::create(0.15f),
// 		CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)0),
// 		CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
// 		CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)1),
// 		CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
// 		CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)2),
// 		CCDelayTime::create(0.15f + CCRANDOM_0_1()*0.15f),
// 		CCCallFuncND::create(this, callfuncND_selector(CandyEffectLayer::displayStageClearEffect), (void*)3),
// 		NULL));
}

void CandyEffectLayer::animationEvent1(cocos2d::extension::CCArmature *armature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;

	if (movementType == LOOP_COMPLETE)
	{
		if (id.compare("Animation1") == 0)
		{
			armature->getAnimation()->stop();
		}
	}
}

void CandyEffectLayer::displayStageClearTips(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* sprite =  CCSprite::create("Image/CandyGame/Others/stageClearTips.png");
	CandyManager::getInstance()->uiLayer->addChild(sprite);

	CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f+125);
	if(sprite != NULL)
	{
		sprite->setPosition(targetPos);
		sprite->setScale(0.4f);
		// 	sprite->runAction(CCSequence::create(
		// 								CCEaseBounceOut::create((CCActionInterval*)(CCScaleTo::create(1.0f, 1.0f))),
		// 								CCDelayTime::create(1.0f),
		// 								CCFadeOut::create(1.0f),
		// 								CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
		// 								NULL
		// 								));
		sprite->runAction(CCSequence::create(
			CCScaleTo::create(0.04f, 0.5f),
			CCScaleTo::create(0.04f, 1.35f),
			CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayHighLightFront)),
			CCScaleTo::create(0.08f, 1.2f),
			CCScaleTo::create(0.08f, 1.0f),
			CCScaleTo::create(0.08f, 1.06f),
			CCScaleTo::create(0.08f, 0.96f),
			CCScaleTo::create(0.08f, 1.02f),
			CCScaleTo::create(0.08f, 1.0f),
			CCDelayTime::create(1.5f),
			CCScaleTo::create(0.08f, 1.0f),
			CCScaleTo::create(0.08f, 0.8f),
			CCScaleTo::create(0.08f, 0.6f),
			CCScaleTo::create(0.08f, 0.4f),
			CCScaleTo::create(0.08f, 0.2f),
			CCScaleTo::create(0.08f, 0.1f),
			CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
			NULL
			));
	}


// 	CCArmature *pAram = CCArmature::create("pb");
// 	CandyManager::getInstance()->uiLayer->addChild(pAram);
// 	if(pAram != NULL)
// 	{
// 		pAram->getAnimation()->playByIndex(0);
// 		pAram->setPosition(ccp(size.width +150, CandyShare::getFixedScreenHeight()*0.5f+125));
// 		pAram->runAction(CCSequence::create(
// 			CCMoveBy::create(1.7f,ccp(-size.width-300,0)),
// 			CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
// 			NULL
// 			));
// 		CandyParticle::displayCandyParticle(CANDY_PARTICLE_CANDYCRUSH_EFFECT,ccp(0,pAram->getContentSize().height/2),pAram,765);
// 	}

}

void CandyEffectLayer::displayHighLightFront(CCNode* sender)
{
	CCSprite* sprite =  CCSprite::create("Image/CandyGame/Others/stageClearTipsFront.png");
	if(sprite != NULL)
	{
		sprite->setScale(2.0f);
		CandyManager::getInstance()->uiLayer->addChild(sprite);

		CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f+125);
		sprite->setPosition(targetPos);
		sprite->runAction(CCSequence::create(
			CCDelayTime::create(0.1f),
			CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
			NULL
			));
	}
}

void CandyEffectLayer::displayStageClearEffect(CCNode* sender, void* data)
{
	CCPoint pos[4];
	pos[0] = ccp(TARGET_SCREEN_WIDTH *0.25f, CandyShare::getFixedScreenHeight()*0.5f+150.0f);
	pos[1] = ccp(TARGET_SCREEN_WIDTH *0.75f, CandyShare::getFixedScreenHeight()*0.5f+150.0f);
	pos[2] = ccp(TARGET_SCREEN_WIDTH *0.25f, CandyShare::getFixedScreenHeight()*0.7f+150.0f);
	pos[3] = ccp(TARGET_SCREEN_WIDTH *0.75f, CandyShare::getFixedScreenHeight()*0.7f+150.0f);
	
	CCNode *node = CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAGE_CLEAR,  
		ccpAdd(pos[(int)data] , ccp(-50+rand()%100,-50+rand()%100)) );
	node->setScale(0.6f + CCRANDOM_0_1()*0.8f);
}

void CandyEffectLayer::displayStageFailedTipsPre(void)
{
	CCLayerColor* grayLayer = CCLayerColor::create(ccc4(0,0,0,0));
	grayLayer->runAction(CCSequence::create(
		CCFadeTo::create(1.0f,170),
		CCCallFunc::create(this, callfunc_selector(CandyEffectLayer::displayStageFailedTips)),
		NULL
		));
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(grayLayer,1,99);
}
void CandyEffectLayer::displayStageFailedTips(void)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f);
	CCArmature *pArm1 = CCArmature::create("shibaile");
	//pArm1->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyEffectLayer::animationEvent2));
	pArm1->getAnimation()->playByIndex(0);
	pArm1->setPosition(targetPos);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(pArm1,2,101);

	CCArmature *pArm2 = CCArmature::create("shibaile");
	pArm2->setScale(0.8f);
	//pArm2->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(CandyEffectLayer::animationEvent2));
	pArm2->getAnimation()->playByIndex(1);
	pArm2->setPosition(targetPos);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->addChild(pArm2,3,102);

	pArm1->runAction(CCSequence::create(
		CCDelayTime::create(0.8f),
		CCCallFunc::create(this, callfunc_selector(CandyEffectLayer::displayStageFailedEffect)),
		CCDelayTime::create(2.8f),
		CCCallFunc::create(this, callfunc_selector(CandyEffectLayer::displayStageFailedCallback)),
		NULL));


// 	CCSprite* sprite =  CCSprite::create("Image/CandyGame/Others/stageFailesTips.png");
// 	CandyManager::getInstance()->uiLayer->addChild(sprite,2);
// 	CCPoint originalPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()+200.0f);
// 	CCPoint targetPos = ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f);
// 	sprite->setPosition(originalPos);
// 	sprite->runAction(CCSequence::create(
// 								CCEaseBounceOut::create((CCActionInterval*)(CCMoveTo::create(1.0f, targetPos)) ),
// 								CCDelayTime::create(2.0f),
// 								CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
// 								NULL));
// 	sprite->runAction(CCSequence::create(	CCDelayTime::create(0.35f),
// 										CCCallFunc::create(this, callfunc_selector(CandyEffectLayer::displayStageFailedEffect)),
// 										NULL));
}

void CandyEffectLayer::displayStageFailedCallback(void)
{
	/*CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(99);*/
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(101);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(102);
	CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer()->removeChildByTag(634);
}

void CandyEffectLayer::displayStageFailedEffect(void)
{
	CCPoint pos = ccp(TARGET_SCREEN_WIDTH *0.5f-50, CandyShare::getFixedScreenHeight()*0.5f+50);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAGE_FAILED1,  pos,CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer(),0,0);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_STAGE_FAILED2,  pos,CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer(),0,2);
	
	CCPoint pos_wuyun = ccp(TARGET_SCREEN_WIDTH *0.5f+250, CandyShare::getFixedScreenHeight()*0.5f+250);
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_WUYUN_EFFECT,  pos_wuyun,CandyManager::getInstance()->uiLayer->getGameUiLayer()->getRootWidget()->getRenderer(),634,2);
}

void CandyEffectLayer::displayCountDown(float time)
{
	const int tag = 509;

	static float lastTime = 0;

	time = time - 0.00001f;
	
	if((int)lastTime == (int)time || time <0)
		return;
	
	lastTime = time;
	removeChildByTag(tag);
	
	CCSprite* countTimeSpr = CCSprite::create(CCString::createWithFormat("Image/CandyGame/Others/CountTime%d.png",(int)lastTime +1)->getCString());
	addChild(countTimeSpr,0,tag);
	
	countTimeSpr->setAnchorPoint(ccp(0.5f,0.5f));
	countTimeSpr->setPosition(ccp(TARGET_SCREEN_WIDTH *0.5f, CandyShare::getFixedScreenHeight()*0.5f));
	countTimeSpr->setScale(2.0f);
	countTimeSpr->setOpacity(0);

	countTimeSpr->runAction(CCSequence::create(
								CCSpawn::create(CCScaleTo::create(0.17f, 0.8f), CCFadeIn::create(0.17f),NULL),
								CCScaleTo::create(0.13f,1.10f),
								CCScaleTo::create(0.13f, 1.0f),
								CCDelayTime::create(0.38f),
								CCFadeOut::create(0.19f),
								CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
								NULL
							));
}

void CandyEffectLayer::displayNumLabelChange(CCLabelAtlas *label)
{
	addChild(label);
	label->setAnchorPoint(ccp(0.5f,0.5f));
	label->setScale(5.0f);
	label->runAction(CCSequence::create(
								CCSpawn::create(CCScaleTo::create(0.3f,0.1f), CCFadeOut::create(0.3f),NULL),
								CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayEffectCallBack)),
								NULL));
	
}

void CandyEffectLayer::displayUseStepChangeStripe(CandyIndex index)
{
	CandyManager::getInstance()->effectLayer->displayRouleteeMakeStrip(index);	
	CandyManager::getInstance()->musicMgr->playUseStepEffect(useStepCount++);
}

void CandyEffectLayer::displayTargetIconEffect(void)
{
	CCPoint pos=CandyManager::getInstance()->uiLayer->getTargetNumLabelPos();
	CandyParticle::displayCandyParticle(CANDY_PARTICLE_TARGET_ICON,  pos);
}

void CandyEffectLayer::displayStarLightEffect(CCNode *node)
{
	const int starLightTag = 888;
	if(!node ||node->getChildByTag(starLightTag))
		return;

	CCSprite *starLight = CCSprite::create("Particle/ParticleImg/stars05.png");
	starLight->setScale(2.0f+CCRANDOM_0_1()*0.5f);
	node->addChild(starLight, 0 , starLightTag);
	
	ccBlendFunc blendFunc;
	blendFunc.src = GL_ONE;//GL_ONE_MINUS_DST_ALPHA;
	blendFunc.dst = GL_ONE;    // maskSprite不可见
	starLight->setBlendFunc(blendFunc);

	int offset = 40;
	starLight->setPosition(ccp(-offset+rand()%(offset*2), -offset+rand()%(offset*2)));
	starLight->setOpacity(0);
	starLight->runAction( CCSequence::create(
						CCDelayTime::create(CCRANDOM_0_1()),
						CCFadeIn::create(0.5f),
						CCDelayTime::create(0.2f),
						CCFadeOut::create(1.0f),
						CCCallFuncN::create(this, callfuncN_selector(CandyEffectLayer::displayStarLightEffectCallBack)),
						NULL));
	starLight->runAction(CCRepeatForever::create(CCRotateBy::create(0.5f, 90)));
}

void CandyEffectLayer::displayStarLightEffectCallBack(CCNode *node)
{
	if(node)
		{
			CCNode *parent = node->getParent();
			node->removeFromParent();
			displayStarLightEffect(parent);
		}
}

void CandyEffectLayer::displayEffectCallBack(CCNode* sender)
{
	sender->removeFromParent();
	CandyManager::getInstance()->uiLayer->removeChildByTag(99);

	RemoveWinFromSelectCandy();
}

void CandyEffectLayer::delayCallBack(float delay,CCCallFuncND *cb)
{
	runAction(CCSequence::create(CCDelayTime::create(delay),cb,NULL));
}

void CandyEffectLayer::AddWinForSelectCandy( CCPoint idxPos )
{
	m_SelectWin = CCSprite::create("Image/MainMapUi/mz.png");
	m_SelectWin->setPosition(idxPos);
	CCActionInterval* scaleAction = CCSequence::create(CCScaleTo::create(0.5,1.0),CCScaleTo::create(0.5,0.9),NULL);
	m_SelectWin->runAction(CCRepeatForever::create(scaleAction));
	addChild(m_SelectWin);
}

void CandyEffectLayer::RemoveWinFromSelectCandy()
{
	if (m_SelectWin)
	{
		m_SelectWin->removeFromParent();
		m_SelectWin = NULL;
	}
	
}
