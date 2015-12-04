#include "CandyCell.h"
#include "CandyManager.h"

USING_NS_CC;

#define GRAVITY_ACCELERATION		4600.0f
#define ORIGINAL_SPEED				300.0f
#define SLIDING_ORIGINAL_SPEED		1000.0f
#define DELETE_DEFAULT_DELAY		0.35f
#define DROP_DELAY_LEN				4
#define DROP_DELAY_TIME			0.1f

CandyCell* CandyCell::create(CandyIndex index, CandyColor color, CandySpecial special)
{
	CandyCell *ret = new CandyCell();

	char *imgName = getCandyImgName(color, special);
	
#ifdef CANDY_USE_PLIST
	if(ret && ret->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imgName)))
#else
	if(ret && ret->initWithFile(imgName))
#endif		
	{
		ret->autorelease();
		ret->index= index;
		ret->color = color;
		ret->special = special;
		ret->extraColor = CandyManager::getInstance()->shareMgr->getCandyRandomColor();
		ret->stateValue = 0;
		ret->produceFlag = false;
		ret->lastIndex = index;
		ret->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(ret->index));
		ret->runAnimation();
		ret->runSpecialAnimation();
					
		if(special == CANDY_SPECIAL_EXPLOSION)
			ret->setCascadeOpacityEnabled(true);
			
		if(special == CANDY_SPECIAL_BOMBING)
			{
				CCSequence *action = CCSequence::create(CCScaleTo::create(0.3f, 1.3f),
													CCScaleTo::create(0.3f, 1.0f),
													NULL);
				ret->runAction(CCRepeatForever::create(action));
			}
		return ret;
	}
	CCAssert(0, "CandyCell::create failed");
	CC_SAFE_DELETE(ret);
	return NULL;
}


void CandyCell::onEnter(void)
{
	CCNode::onEnter();
	scheduleUpdate();
}

void CandyCell::onExit(void)
{
	unscheduleUpdate();
	CCNode::onExit();
}


void CandyCell::update(float time)
{
	if(!getCandyStates(CANDY_CELL_NORMAL)  && !getCandyStates(CANDY_CELL_NEW_PORTALING) && !getCandyStates(CANDY_CELL_DELETING)  )
		{	
			setScale(1.0f);
		#ifndef CANDY_USE_PLIST
			setHSL(0,0,0);
		#endif
		}
	
	if(produceFlag && isVisible()==false)
		{
			CCPoint currentPos = getPosition();
			CCPoint targetPos = CandyManager::getInstance()->shareMgr->getPosByIndex(visibleIndex);
			if(currentPos.y <= targetPos.y)
				{
					produceFlag = false;
					setVisible(true);
				}
		}
	
	if(getCandyStates(CANDY_CELL_DROPING))
		updateDropPos(time);
}

void CandyCell::setCandyProduceFlag(CandyIndex index)
{
	produceFlag = true;
	setVisible(false);
	visibleIndex = index;
}


char* CandyCell::getCandyImgName(CandyColor color, CandySpecial special)
{
	static char imgName[50] = {0};
	memset(&imgName[0], 0, sizeof(char) *50);
#ifndef CANDY_USE_PLIST
	sprintf(imgName, "Image/CandyGame/Candy/Cell/");
#endif
	switch(color )
	{
	case CANDY_COLOR_RED:
		sprintf(imgName,"%sCandyRed",imgName);
		break;

	case CANDY_COLOR_BLUE:
		sprintf(imgName,"%sCandyBlue",imgName);
		break;

	case CANDY_COLOR_GREEN:
		sprintf(imgName,"%sCandyGreen",imgName);
		break;

	case CANDY_COLOR_YELLOW:
		sprintf(imgName,"%sCandyYellow",imgName);
		break;

	case CANDY_COLOR_ORANGE:
		sprintf(imgName,"%sCandyOrange",imgName);
		break;

	case CANDY_COLOR_PURPLE:
		sprintf(imgName,"%sCandyPurple",imgName);
		break;

	case CANDY_COLOR_SPECIAL:
		break;

	case CANDY_COLOR_CHERRY:
		sprintf(imgName,"%scherry0.png",imgName);
		break;

	case CANDY_COLOR_CHESNUT:
		sprintf(imgName,"%schesnut0.png",imgName);
		break;

	case CANDY_COLOR_LICORICE:
		sprintf(imgName,"%slicorice.png",imgName);
		break;
	}

	switch(special)
		{
			case CANDY_SPECIAL_NORMAL:
				sprintf(imgName,"%sNormal.png",imgName);
				break;

			case CANDY_SPECIAL_HORIZONTAL:
				sprintf(imgName,"%sNormal.png",imgName);
				break;

			case CANDY_SPECIAL_VERTICAL:
				sprintf(imgName,"%sNormal.png",imgName);
				break;

			case CANDY_SPECIAL_BOMB:
				sprintf(imgName,"%sBomb.png",imgName);
				break;

			case CANDY_SPECIAL_BOMBING:
				sprintf(imgName,"%sNormal.png",imgName);
				break;

			case CANDY_SPECIAL_COLORFULL:
				sprintf(imgName,"%sCandyColorful.png",imgName);
				break;

			case CANDY_SPECIAL_EXPLOSION:
				sprintf(imgName,"%sExplosion.png",imgName);
				break;
		}
	return imgName;
}

void CandyCell::runSpecialAnimation(void)
{
	char *animationImg = NULL;
	if (CANDY_SPECIAL_COLORFULL == special)
	{
		animationImg = (char*)"CandyColorfuleff";
		CCArray *animFramesArray = CCArray::create();
		for (int i = 0; i < 12; i++)
		{
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				CCString::createWithFormat("%s%d.png", animationImg, i)->getCString());
			animFramesArray->addObject(frame);
		}
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFramesArray, 0.08f);
		runAction(CCRepeatForever::create(
			CCSequence::create(
			//CCDelayTime::create( 0.2f ), 
			CCAnimate::create(animation),
			NULL)));
	}
	else if ( CANDY_SPECIAL_HORIZONTAL == special)
	{ 
		CCSprite * director1 = CCSprite::createWithSpriteFrameName("director.png");
		addChild(director1);
		director1->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(0.2, CCPoint(5, 35)), CCMoveTo::create(0.3, CCPoint(10, 35)), NULL)));

		CCSprite * director2 = CCSprite::createWithSpriteFrameName("director.png");
		director2->setRotation(180);
		addChild(director2);
		director2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(0.2, CCPoint(65, 35)), CCMoveTo::create(0.3, CCPoint(60, 35)), NULL)));
	}
	else if (CANDY_SPECIAL_VERTICAL == special)
	{
		CCSprite * director1 = CCSprite::createWithSpriteFrameName("director.png");
		director1->setRotation(90);
		addChild(director1);
		director1->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(0.2, CCPoint(35, 65)), CCMoveTo::create(0.3, CCPoint(35, 60)), NULL)));

		CCSprite * director2 = CCSprite::createWithSpriteFrameName("director.png");
		director2->setRotation(-90);
		addChild(director2);
		director2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(0.2, CCPoint(35, 5)), CCMoveTo::create(0.3, CCPoint(35, 10)), NULL)));
	}


	
}

void CandyCell::runAnimation(void)
{
	return;
	//　运输模式水果序列帧动画
	char *animationImg = NULL;
	
	if(color == CANDY_COLOR_CHESNUT)
		animationImg = (char*)"chesnut";
	else if(color == CANDY_COLOR_CHERRY)
		animationImg = (char*)"cherry";
	else 
		return;
	
	CCArray *animFramesArray = CCArray::create();
	for(int i =0; i<20; i++)
		{
			CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				CCString::createWithFormat("%s%d.png",animationImg,i)->getCString());
			animFramesArray->addObject(frame);
		}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFramesArray , 0.05f);
	runAction(CCRepeatForever::create(CCAnimate::create(animation)));
}

bool CandyCell::getCandyStates(CandyCellState  type)
{
	if(type == CANDY_CELL_NORMAL)
		{
			return  !stateValue;
		}
	return (stateValue>>type)&1;
}

void CandyCell::setCandyStates(CandyCellState  type, bool states)
{
	if(states)
		stateValue |= (1<<type);
	else
		stateValue &= (~(1<<type));
}



void CandyCell::runCandyMoveAction(CandyIndex movetIndex)
{
	CandyIndex originalIndex = index;
	index = movetIndex;
	
	setCandyStates(CANDY_CELL_MOVING, true);

	CCFiniteTimeAction*  action = CCSequence::create(
	 	CCMoveTo::create(0.20f, CandyManager::getInstance()->shareMgr->getPosByIndex(movetIndex)),
	 	CCCallFunc::create(this, callfunc_selector(CandyCell::candyMoveActionCallBack)),
	 	NULL);
	
	this->runAction(action);
}

void CandyCell::candyMoveActionCallBack(void)
{
	setCandyStates(CANDY_CELL_MOVING, false);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, this);
}
	
void CandyCell::runCandySlideAction(CandyIndex slideIndex, CandyIndex dropIndex, bool dopFlag)
{
	CandyIndex originalIndex = index;
	index   = dopFlag?dropIndex:slideIndex;
	
	setCandyStates(CANDY_CELL_SLIDEING, true);
	
	slideToDrop = dopFlag;
	if(slideToDrop)
		{
			CandyManager::getInstance()->placeMgr->addCandyToDropArray(this);
		}
		
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(originalIndex, NULL);
	CandyManager::getInstance()->mapDataMgr->setMapCellStates(originalIndex,  MAP_CELL_CANDY, false);
	CandyManager::getInstance()->mapDataMgr->setMapCellStates(index,  MAP_CELL_CANDY, true);

	CCFiniteTimeAction*  action = CCSequence::create(
								 	CCMoveTo::create(0.10f, CandyManager::getInstance()->shareMgr->getPosByIndex(slideIndex)),
								 	CCCallFunc::create(this, callfunc_selector(CandyCell::candySlideActionCallBack)),
								 	NULL);
	this->runAction(action);
	this->stopActionByTag(TAG_ACTION_UPSPRING);
	
}

void CandyCell::candySlideActionCallBack(void)
{
	setCandyStates(CANDY_CELL_SLIDEING, false);
	
	if(slideToDrop)
		{
			CandyIndex dopIndex = index;
			CandyManager::getInstance()->shareMgr->getIndexByPos(getPosition(), index);
			runCandyDropAction(dopIndex);
		}
		
	else
		{
			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, this);
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(this);
		}
}

void CandyCell::runCandyDeleteAction(void)
{
	if(!CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index))
		return;
	
	CandyManager::getInstance()->shareMgr->collectCandy(this);
			
	setCandyStates(CANDY_CELL_DELETING, true);

	float delayTime = DELETE_DEFAULT_DELAY;
	//if(this->special == CANDY_SPECIAL_VERTICAL)
	//	delayTime = delayTime + SPECIAL_HOR_VER_DELAY;
	CCFiniteTimeAction*  action = CCSequence::create(
	 	CCScaleTo::create(delayTime,0.01f),
	 	CCCallFunc::create(this, callfunc_selector(CandyCell::candyDeleteActionCallBack)),
	 	NULL);
	this->runAction(action);

	CandyManager::getInstance()->effectLayer->displaySingleNormalDispelEffect(index);
}


void CandyCell::candyDeleteActionCallBack(void)
{
	CandyCell *candy =  CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
	bool ret = CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CANDY);
	if(this == CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index) )
		CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, NULL);
	
	destroyCandy();
}


void CandyCell::runCandyPortalAction(CandyIndex portalIndex)
{
	setCandyStates(CANDY_CELL_PORTALING, true);	
	
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, NULL);
	CandyManager::getInstance()->mapDataMgr->setMapCellStates(index,  MAP_CELL_CANDY, false);
	
		
	CCActionInterval* portal = CCMoveTo::create(sqrtf((float)(portalIndex.y - index.y)* 0.05f), 
											CandyManager::getInstance()->shareMgr->getPosByIndex(portalIndex) );

	CCFiniteTimeAction*  action = CCSequence::create(
									 	portal,
									 	CCMoveBy::create(0.1f, ccp(0,5)),
									 	CCMoveBy::create(0.1f, ccp(0,-5)),
									 	CCCallFunc::create(this, callfunc_selector(CandyCell::candyPortalActionCallBack)),
									 	NULL);
	this->runAction(action);
}
	
void CandyCell::candyPortalActionCallBack(void)
{
	setCandyStates(CANDY_CELL_PORTALING, false);
	destroyCandy();
}

void CandyCell::runCandyDelayDelete(float time, int score)
{
	if(special == CANDY_SPECIAL_INGREDIENT)
		return;

	if(getCandyStates(CANDY_CELL_DELAY_DELETING) || getCandyStates(CANDY_CELL_DELETING))
		return;
		
	setCandyStates(CANDY_CELL_DELAY_DELETING, true);
	this->runAction(CCSequence::create(
									CCDelayTime::create(time),
									CCCallFuncND::create(this, callfuncND_selector(CandyCell::candyDelayDeleteActionCallBack), (void*)score),
									NULL
								));
}

void CandyCell::candyDelayDeleteActionCallBack(CCNode* sender, void* data)
{
	setCandyStates(CANDY_CELL_DELAY_DELETING, false);
	CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(index,data?true:false);
	if(color == CANDY_COLOR_LICORICE)
		CandyManager::getInstance()->effectLayer->displayBreakLicorices(index);
}

void CandyCell::runCandyDropAction(CandyIndex droptIndex, bool changeLastIndex)
{
	CandyIndex originalIndex = index;
	index = droptIndex;

	if(changeLastIndex)
		lastIndex = originalIndex;
	
	if(!getCandyStates(CANDY_CELL_DROPING))
		currentSpeed = ORIGINAL_SPEED;
	setCandyStates(CANDY_CELL_DROPING, true);	
	
	dropTargetY = CandyManager::getInstance()->shareMgr->getPosByIndex(droptIndex).y;

	
	CandyManager::getInstance()->placeMgr->addCandyToDropArray(this);

	if(!produceFlag)
		CandyManager::getInstance()->mapDataMgr->setCandyByIndex(originalIndex, NULL);

	CandyManager::getInstance()->mapDataMgr->setMapCellStates(droptIndex,  MAP_CELL_CANDY, true);
		
}

void CandyCell::updateDropPos(float time)
{
	float currentPosY = getPositionY();
	float offsetY = currentSpeed * time + 0.5 * GRAVITY_ACCELERATION * time * time;
	float newPosY = currentPosY - offsetY;
	
	currentSpeed  = currentSpeed + time * GRAVITY_ACCELERATION;
	
	setPositionY(newPosY);
	if(newPosY <  dropTargetY)
		checkCandyDropStatus();
}

void CandyCell::checkCandyDropStatus(void)
{
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, this);
	CandyManager::getInstance()->placeMgr->removeCandyFromDropArray(this);
	
	CandyIndex dropIndex;
	bool dropContinue  = CandyManager::getInstance()->placeMgr->getCandyDropEnable(index, dropIndex);
	if(dropContinue)//检测是否可继续掉落
	{
		runCandyDropAction(dropIndex, false);
	}
	else
	{
		float lenRatio =  sqrt(currentSpeed/ORIGINAL_SPEED);
		float timeRatio =  sqrt(lenRatio);
		setCandyStates(CANDY_CELL_DROPING, false);
		setPositionY(dropTargetY);
		CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(this);
		CCActionInterval* moveUp = CCMoveBy::create(DROP_DELAY_TIME *timeRatio, ccp(0,DROP_DELAY_LEN * lenRatio));
		CCActionInterval* moveDown = CCMoveBy::create(DROP_DELAY_TIME*timeRatio, ccp(0,-DROP_DELAY_LEN* lenRatio));

		CCFiniteTimeAction*  action = CCSequence::create(
			CCEaseOut::create(moveUp,2.5f),
			moveDown,
			//CCCallFunc::create(this, callfunc_selector(CandyCell::dropAjustActionCallBack)),
			NULL);
		action->setTag(TAG_ACTION_UPSPRING);
		this->runAction(action);

		CandyManager::getInstance()->musicMgr->playDropEffect(index.y - lastIndex.y);
	}
}

void CandyCell::dropAjustActionCallBack(void)
{
	if(getCandyStates(CANDY_CELL_NORMAL))
		CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, this);
}

void CandyCell::runCandyNewPortalAction(CandyIndex portalOrigin, CandyIndex portalTarget)
{
	setCandyStates(CANDY_CELL_NEW_PORTALING, true);	

	newPortalOrigin = portalOrigin;
	newPortalTarget = portalTarget;
	
	this->runAction(getCandyNewPortalAction());
}

CCFiniteTimeAction*  CandyCell::getCandyNewPortalAction(void)
{
	CCPoint portalOriginPos = CandyManager::getInstance()->shareMgr->getPosByIndex(newPortalOrigin);
	CCPoint portalTargetPos = CandyManager::getInstance()->shareMgr->getPosByIndex(newPortalTarget);
	
	CCSequence*  action = CCSequence::create(CCMoveTo::create(0.2f, portalOriginPos),
										CCScaleTo::create(0.2f, 0.1f),	
										CCMoveTo::create(0.000001f, portalTargetPos),
										CCScaleTo::create(0.2f, 1.0f),
										CCCallFunc::create(this, callfunc_selector(CandyCell::newPortalActionCallback)),
										NULL);
	return action;
}
	
CCFiniteTimeAction*  CandyCell::getCandyNewPortalReverseAction(void)
{
	CCPoint portalOriginPos = CandyManager::getInstance()->shareMgr->getPosByIndex(newPortalOrigin);
	CCPoint portalTargetPos = CandyManager::getInstance()->shareMgr->getPosByIndex(newPortalTarget);
	CCPoint originPos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
	
	CCSequence*  action = CCSequence::create(CCScaleTo::create(0.2f, 0.1f),
										CCMoveTo::create(0.000001f, portalOriginPos),
										CCScaleTo::create(0.2f, 1.0f),
										CCMoveTo::create(0.2f, originPos),
										CCCallFunc::create(this, callfunc_selector(CandyCell::newPortalReverseActionCallback)),
										NULL);
	return action;
}



void CandyCell::newPortalActionCallback(void)
{
	CandyIndex indexBackUp = index;
	
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(newPortalTarget, this, true,false);
	if(CandyManager::getInstance()->dispelMgr->checkCandyDispel(this))
		{
			CandyManager::getInstance()->dispelMgr->addCandyToChangeArray(this);
			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(indexBackUp, NULL);
			setCandyStates(CANDY_CELL_NEW_PORTALING, false);
			CandyManager::getInstance()->moveMgr->moveDone();
			CandyManager::getInstance()->dispelMgr->updateCandyDispel();
		}
	else
		{
			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(newPortalTarget, NULL);
			index = indexBackUp;
			this->runAction(getCandyNewPortalReverseAction());
		}

}

void CandyCell::newPortalReverseActionCallback(void)
{
	setCandyStates(CANDY_CELL_NEW_PORTALING, false);
}

void CandyCell::CreateNewCandySpecial(CandyIndex index, CandySpecial newSpecial)
{
	CandyCell *candy1 = CandyCell::create(index, (CandyColor)(rand()%4), newSpecial);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, candy1);
	CandyManager::getInstance()->candyLayer->addToCandyParent(candy1);
}

CandyCell* CandyCell::changeCandySpecial(CandySpecial newSpecial, bool displayEffect)
{
	if(newSpecial == CANDY_SPECIAL_COLORFULL)
		color = CANDY_COLOR_SPECIAL;
	
	CandyCell* changeCandy = CandyCell::create(index, color, newSpecial);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(changeCandy->index, changeCandy);
	CandyManager::getInstance()->candyLayer->addToCandyParent(changeCandy);

	destroyCandy();
	if(displayEffect)
		changeCandy->displayNewSpecialEffect();
	return changeCandy;
}

void CandyCell::runCandyChangeSpecialDelay(CandySpecial newSpecial, float time)
{
	if(getCandyStates(CANDY_CELL_DELAY_DELETING) || getCandyStates(CANDY_CELL_DELETING))
		return;

	setCandyStates(CANDY_CELL_DELAY_CHANGING, true);
	runAction(CCSequence::create(
									CCDelayTime::create(time),
									CCCallFuncND::create(this, callfuncND_selector(CandyCell::candyChangeSpecialDelayCallBack), (void*)newSpecial),
									NULL
								));
}

void CandyCell::candyChangeSpecialDelayCallBack(CCNode* sender, void* data)
{
	int newSpecial = (int)data;
	setCandyStates(CANDY_CELL_DELAY_CHANGING, false);
	
	CandyCell *newCandy =  changeCandySpecial((CandySpecial)newSpecial);

// for candy roulette
	newCandy->extraColor =(CandyColor)( rand() %CandyManager::numberOfColours);
	CandyManager::getInstance()->specialMgr->addActivedSpecial(newCandy);
	CandyManager::getInstance()->specialMgr->setDisplayEffectTime(0.5f);
}

void CandyCell::displaySpecialCandyEffect(void)
{
	//CandyParticleType type = (CandyParticleType)getSpecialCandyEffectIndex();
}

void CandyCell::displayNewSpecialEffect(void)
{
	switch(special)
		{
			case CANDY_SPECIAL_HORIZONTAL:
				CandyManager::getInstance()->effectLayer->displayRouleteeMakeStrip(index);
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_NEW_HORIZON);
				break;
				
			case CANDY_SPECIAL_VERTICAL:
				CandyManager::getInstance()->effectLayer->displayRouleteeMakeStrip(index);
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_NEW_VERTICAL);
				break;

			case CANDY_SPECIAL_BOMB:
				CandyManager::getInstance()->effectLayer->displayRouleteeMakeBomb(index);
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_NEW_BOMB);
				break;

			case CANDY_SPECIAL_COLORFULL:
				CandyManager::getInstance()->effectLayer->displayRouleteeMakeColor(index);
				CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_NEW_COLORFULL);
				break;
		}
}
	
void CandyCell::removeFromArray(void)
{
	CandyManager::getInstance()->specialMgr->removeActivedSpecial(this);
	CandyManager::getInstance()->placeMgr->removeCandyFromDropArray(this);
	CandyManager::getInstance()->dispelMgr->removeCandyFromChangeArray(this);
}

void CandyCell::destroyCandy(void)
{
	removeFromArray();
	removeFromParent();

	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
		{
			CandyCell *candy =   CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x,y));
			if(this == candy)
			{
				CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(x,y), NULL);
				CCLog("candyDeleteActionCallBack %d %d",x,y);
			}
		}
}

CandyCell* CandyCell::getRandomNormalCandy(void)
{
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	if(!candyArray)
		return NULL;

	int totalNum = candyArray->count() ;
	int target = rand() % totalNum;
	int count = 0;
	CandyCell* candy = NULL;
	while(1)
		{
			candy = (CandyCell *)candyArray->objectAtIndex(target);
			if(candy && candy->special == CANDY_SPECIAL_NORMAL 
				&& !CandyManager::getInstance()->mapDataMgr->getMapCellStates(candy->index, MAP_CELL_LOCK))
				{
					break;
				}
			else
				{
					target = (++target) % totalNum;
				}
			if(count++ > totalNum)
				return NULL;
		}
	return candy;
}
