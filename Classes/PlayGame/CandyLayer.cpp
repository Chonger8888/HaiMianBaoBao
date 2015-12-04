#include "CandyLayer.h"
#include "PlayGameScene.h"
#include "CandyManager.h"

USING_NS_CC;

extern bool crazyMode;

#define CANDY_ELEMENT_IMG				"Image/CandyGame/Candy/CandyElement.png"
#define CANDY_BARRIER_TOP_IMG		"Image/CandyGame/Candy/CandyBarrierTop.png"
#define CANDY_BARRIER_BOTTOM_IMG	"Image/CandyGame/Candy/CandyBarrierBottom.png"

#define LIGHTN_IN_IMG		"Image/CandyGame/Others/LightningIn.png"
#define LIGHTN_OUT_IMG		"Image/CandyGame/Others/LightningOut.png"

bool CandyLayer::init(void)
{	
	if ( !CCLayer::init() )
		{
			return false;
		}
	
	clipper = NULL;
	candyElementBatchNode = NULL;
	candyBarrierTopBatchNode = NULL;
	candyBarrierBottomBatchNode = NULL;
	moveableStates = false;
	
	CCPoint candyLayerPos = getPosition();
	setPosition(ccp(candyLayerPos.x+1000.0f, candyLayerPos.y));
	runAction(CCSequence::create( CCEaseBackOut::create(CCMoveTo::create(0.5f,candyLayerPos)),
						CCCallFunc::create(this, callfunc_selector(CandyLayer::layerActionCallback)),
						NULL));
	return true;
}

void CandyLayer::onEnter(void)
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, CANDY_LAYER_PRIORITY, true);
}

void CandyLayer::onExit(void)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
	
}

bool CandyLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//CandyParticle::displayCandyParticle(CANDY_PARTICLE_SPECIAL_SPRIP_RED, pTouch->getLocation(), this);

	if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_SHOW_TARGET)
		{
			CandyManager::getInstance()->resultMgr->unDisplayTargetTips();
			return false;
		}

	if(!CandyManager::getInstance()->resultMgr->getGameRunning())
	{
		if(CandyManager::getInstance()->resultMgr->getCurrentResult() == CANDY_RESULT_USE_PROP)
		{
			if(CommonData::currentPropType == CANDY_PROP_IN_SWAP)
			{

			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	if(CandyManager::getInstance()->explosionMgr->isReadyToExplode() || CandyManager::getInstance()->moveMgr->moveLimit <=0)
		return false;

	if(CandyManager::gameMode == CANDY_MODE_TIMING && CandyManager::timeLimit <=0)
		return false;
	
	if(CandyManager::gameMode != CANDY_MODE_TIMING)
		if(!CandyManager::getInstance()->shareMgr->getCandyIdle())
			return false;

	if(moveableStates)
		return false;
	
	if( CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), firstTouchCandy) 
		&& CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)
		&& CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy)->getCandyStates(CANDY_CELL_NORMAL)
		&& !CandyManager::getInstance()->mapDataMgr->getMapCellStates(firstTouchCandy, MAP_CELL_LOCK))
		{
			CandyCell * candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy);
			candy->setScale(1.2f);
		#ifndef CANDY_USE_PLIST
			candy->setHSL(HSL_TIPS_H,HSL_TIPS_S,HSL_TIPS_L);
		#endif
			moveableStates = true;
		}
	return moveableStates;
}

void CandyLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(!moveableStates)
		return;
	
	bool ret = CandyManager::getInstance()->shareMgr->getIndexByPos(pTouch->getLocation(), secondTouchCandy) ;

	if(firstTouchCandy.x == secondTouchCandy.x && firstTouchCandy.y == secondTouchCandy.y)
		return;

	moveableStates = false;

	CandyCell *firstCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy);
	CandyCell *secondCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(secondTouchCandy);

	if(firstCandy)
		{
			firstCandy->setScale(1.0f);
		#ifndef CANDY_USE_PLIST
			firstCandy->setHSL(0,0,0);
		#endif
		}

	if(!firstCandy || !firstCandy->getCandyStates(CANDY_CELL_NORMAL))
		return;
	
	if(!CandyManager::getInstance()->shareMgr->isTwoIndexNeighbour(firstTouchCandy, secondTouchCandy) )
		return;

	if(ret)//ret=true 表示secondToch格子存在
		{
			if(secondCandy  && secondCandy->getCandyStates(CANDY_CELL_NORMAL))
			{
				CandyManager::getInstance()->moveMgr->moveCandy(firstTouchCandy, secondTouchCandy, (CommonData::m_isSwap||crazyMode)?CHANGE_MODE_BY_ANYWAY:CHANGE_MODE_BY_USER);
				if(CommonData::m_isSwap)
				{
					CandyManager::getInstance()->uiLayer->removeUsePropEffect();
					CommonData::m_isSwap = false;
				}
			}
		}
	else//不存在 检测新传送门
		{
			CandyManager::getInstance()->newPortal->checkCandyMoveNewPortal(firstTouchCandy, secondTouchCandy);
		}
}

void CandyLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(moveableStates)
		{
			moveableStates = false;
			CandyCell * candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(firstTouchCandy);
			if(candy)
			{
				candy->setScale(1.0f);
			#ifndef CANDY_USE_PLIST
				candy->setHSL(0,0,0);
			#endif
			}
		}
		
}

CCNode* CandyLayer::getCandyParent(void)
{
#ifdef CANDY_USE_PLIST
	return getCandyElementBatchNode();
#else
	return getClipper();
#endif

}

void CandyLayer::addToCandyParent(CandyCell *candy)
{
	getCandyParent()->addChild(candy);
}

CCClippingNode* CandyLayer::getClipper(void)
{
	if(!clipper)
		{
			clipper =  CCClippingNode::create();
			clipper->setAnchorPoint(ccp(0.0, 0.0));
			clipper->setPosition( ccp(0, 0) );
			clipper->setStencil(CandyManager::getInstance()->mapDataMgr->getMapShape());
			//clipper->setInverted(true);
			this->addChild(clipper, CLIPPER_ORDER);
		}
	return clipper;   
}

CCSpriteBatchNode* CandyLayer::getCandyElementBatchNode(void)
{
	if(candyElementBatchNode == NULL)
		{
		#if 1
			candyElementBatchNode= CCSpriteBatchNode::create(CANDY_ELEMENT_IMG);
			getClipper()->addChild(candyElementBatchNode);
		#else
			candyElementBatchNode= (CCSpriteBatchNode*)CCNode::create();
			getClipper()->addChild(candyElementBatchNode);
		#endif
		}
	return candyElementBatchNode;
}

void CandyLayer::addToCandyElementBatchNode(CandyCell *candy)
{
	CCAssert( dynamic_cast<CandyCell*>(candy), "addToCandyElementBatchNode");
#ifdef CANDY_USE_PLIST
	getCandyElementBatchNode()->addChild(candy);
#else
	getClipper()->addChild(candy);
#endif
}

void CandyLayer::addToCandyBarrierTopBatchNode(CCNode *node, int order)
{
	if(candyBarrierTopBatchNode == NULL)
		{
		#if 1
			candyBarrierTopBatchNode = CCSpriteBatchNode::create(CANDY_BARRIER_TOP_IMG,100);
			this->addChild(candyBarrierTopBatchNode, BARRIER_TOP_ORDER);
		#else
			candyBarrierTopBatchNode =  (CCSpriteBatchNode*)CCNode::create();
			this->addChild(candyBarrierTopBatchNode, BARRIER_TOP_ORDER);
		#endif
		}
	candyBarrierTopBatchNode->addChild(node,order);
}

void CandyLayer::addToCandyBarrierBottomBatchNode(CCNode *node, int order)
{
	if(candyBarrierBottomBatchNode == NULL)
		{
		CCAssert( dynamic_cast<CCSprite*>(node), "addToCandyBarrierBottomBatchNode");
		#if 1
			candyBarrierBottomBatchNode = CCSpriteBatchNode::create(CANDY_BARRIER_BOTTOM_IMG,100);
			this->addChild(candyBarrierBottomBatchNode, BARRIER_BOTTOM_ORDER);
		#else
			candyBarrierBottomBatchNode = (CCSpriteBatchNode*)CCNode::create();
			this->addChild(candyBarrierBottomBatchNode, BARRIER_BOTTOM_ORDER);
		#endif
		}
	candyBarrierBottomBatchNode->addChild(node,order);
}

void CandyLayer::runResortCandyLightning(CCNode* sender, void* data)
{
	const int moveOffset = 200;
	bool inFlag = data?false:true;
	int startPos = inFlag?-moveOffset:TARGET_SCREEN_WIDTH+moveOffset;
	int moveLen = inFlag?TARGET_SCREEN_WIDTH+moveOffset*2:-(TARGET_SCREEN_WIDTH+moveOffset*2);
	
	CCSprite *lightningSpr = CCSprite::create(inFlag?LIGHTN_IN_IMG:LIGHTN_OUT_IMG);
	lightningSpr->setPosition(ccp(startPos,CandyManager::getInstance()->shareMgr->getFixedScreenHeight() *0.5));
	lightningSpr->runAction(CCSequence::create(
									CCMoveBy::create(1.3f,ccp(moveLen, 0)),
									CCDelayTime::create(5.0f),
									CCCallFuncN::create(lightningSpr, callfuncN_selector(CandyLayer::resortCandyLightningCallBack)),
									NULL));
	CandyParticle::displayCandyParticle(inFlag?CANDY_PARTICLE_RESORT_IN:CANDY_PARTICLE_RESORT_OUT,  ccp(70,350), lightningSpr);
	CandyManager::getInstance()->candyLayer->getClipper()->addChild(lightningSpr,10);
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_COLOR);
}

void CandyLayer::runResortCandyFade(CCNode* sender, void* data)
{
	const float delayTime =0.2f;
	const float delayGap = 0.1f;
	bool inFlag = data?true:false;
	
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=0; y< CANDY_MAP_HEIGH; y++)
		{
			float delay = delayTime + (inFlag?8-x:x)*delayGap;
			CandyCell *candy =   CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x,y));
			if(candy )//&& candy->color <CANDY_COLOR_NORMAL_NUM && candy->special != CANDY_SPECIAL_EXPLOSION)
				runFadeAction(candy, inFlag, delay);

			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_LOCK) )
			{
				CandyLockCell* lock = CandyManager::getInstance()->lockMgr->getLockCell(cIndex(x, y));
				runFadeAction(lock, inFlag, delay);
			}

			if(CandyManager::getInstance()->creamMgr->getCandyCreamCell(cIndex(x, y)) )
			{
				CandyCreamCell* cream = CandyManager::getInstance()->creamMgr->getCandyCreamCell(cIndex(x, y)) ;
				runFadeAction(cream, inFlag, delay);
			}

			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CHOCOLATA) )
			{
				CandyChocolateCell * chocolate = CandyManager::getInstance()->chocolateMgr->getCandyChocolateCell(cIndex(x, y));
				runFadeAction(chocolate, inFlag, delay);
			}
		}
}

void CandyLayer::runFadeAction(CCNode *node, bool inFlag, float delay)
{
	if(!node)
		return;
	
	const float fadeTime = 0.2f;
	
	CCAction *fadeAction;
	if(inFlag)
		fadeAction = CCFadeIn::create(fadeTime);
	else
		fadeAction = CCFadeOut::create(fadeTime);
	
	node->runAction(CCSequence::create(CCDelayTime::create(delay), fadeAction, NULL));
}

void CandyLayer::runResortCandyAction(void)
{
	runAction( CCSequence::create(  CCCallFunc::create(this, callfunc_selector(CandyLayer::resortCandyStart)),
							CCDelayTime::create(1.0f),
							CCCallFuncND::create(this, callfuncND_selector(CandyLayer::runResortCandyLightning), (void*)0),//fade out
							CCCallFuncND::create(this, callfuncND_selector(CandyLayer::runResortCandyFade), (void*)0),//fade out
							CCDelayTime::create(1.2f),
							CCCallFunc::create(this, callfunc_selector(CandyLayer::resortCandyFadeOutCallback)),
							CCCallFuncND::create(this, callfuncND_selector(CandyLayer::runResortCandyLightning), (void*)1),//fade in
								CCCallFuncND::create(this, callfuncND_selector(CandyLayer::runResortCandyFade), (void*)1),//fade in
							CCCallFunc::create(this, callfunc_selector(CandyLayer::resortCandyFadeInCallback)),
							CCCallFunc::create(this, callfunc_selector(CandyLayer::resortCandyEnd)),
							NULL));
}

void CandyLayer::resortCandyLightningCallBack(CCNode* sender)
{
	sender->removeFromParent();
}

void CandyLayer::resortCandyStart(void)
{
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_RESORT_TIPS);
	if(CommonData::m_ResortByProp == true)
	{
		CandyManager::getInstance()->uiLayer->showTips(CCSprite::create("Image/CandyGame/Others/candyResortTipsByProp.png"));
		CommonData::m_ResortByProp = false;
	}
	else
	{
		CandyManager::getInstance()->uiLayer->showTips(CCSprite::create("Image/CandyGame/Others/candyResortTips.png"));
	}
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_RESORT);
}

void CandyLayer::resortCandyEnd(void)
{
	CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_PLAYING);
	if(CandyManager::getInstance()->correctMapMgr->getResortResult()== false)
		CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NO_DISPEL);
	CandyManager::getInstance()->candyLayer->getCandyParent()->setGrid(NULL);
}

void CandyLayer::resortCandyFadeOutCallback(void)
{
	CandyManager::getInstance()->correctMapMgr->setResortState(true);
	CandyManager::getInstance()->correctMapMgr->setResortResult(CandyManager::getInstance()->correctMapMgr->resortCandyExecute(false));
}

void CandyLayer::resortCandyFadeInCallback(void)
{
	CandyManager::getInstance()->correctMapMgr->setResortState(false);
}

void CandyLayer::layerActionCallback(void)
{
	PlayGame *playGameLayer = (PlayGame *)CandyManager::getInstance()->getCurrentLayer();
	playGameLayer->addBg(true);
}
