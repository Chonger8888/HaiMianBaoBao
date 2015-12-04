#include "CandyShare.h"
#include "CandyManager.h"

USING_NS_CC;

CandyShare::CandyShare()
{
	currentRandSeed = 0;
	newRandSeed = 1;
}

CandyShare::~CandyShare()
{

}

void CandyShare::updateCandyShare(void)
{
	if(currentRandSeed == newRandSeed )
	{
		newRandSeed++;
	}
}

void CandyShare::initPos(void)
{
	float fixedScreenHeight = getFixedScreenHeight();

	if(fixedScreenHeight >= SCREEN_DEMARCATION1_HEIGHT)
	{
		leftUpPos.x = (TARGET_SCREEN_WIDTH -CANDY_CELL_WIDTH * CANDY_MAP_WIDTH ) *0.5  + getOffsetXForMakeCenter();
		//leftUpPos.y =  fixedScreenHeight -(225.0f + (fixedScreenHeight -SCREEN_DEMARCATION1_HEIGHT)*0.5 ) + getOffsetYForMakeCenter();
		leftUpPos.y =  fixedScreenHeight -(fixedScreenHeight -CANDY_CELL_HEIGHT* CANDY_MAP_HEIGH)*0.5  + getOffsetYForMakeCenter();

		leftDonwPos.x  = leftUpPos.x;
		leftDonwPos.y  = leftUpPos.y - CANDY_CELL_HEIGHT* CANDY_MAP_HEIGH;
	}
	else
	{
		leftUpPos.x = (TARGET_SCREEN_WIDTH -CANDY_CELL_WIDTH * CANDY_MAP_WIDTH ) *0.5  + getOffsetXForMakeCenter();
		leftUpPos.y = (fixedScreenHeight - GAME_UI_LEN2 - TARGET_SCREEN_WIDTH) *0.5f + GAME_UI_LEN2 + TARGET_SCREEN_WIDTH + getOffsetYForMakeCenter();
		leftDonwPos.x  = leftUpPos.x;
		leftDonwPos.y  = leftUpPos.y - CANDY_CELL_HEIGHT* CANDY_MAP_HEIGH;
	}


	/*	CCPoint rightUpPos;
	CCPoint rightDonwPos;*/

}


int CandyShare::getOffsetXForMakeCenter(void)
{
	int offsetNum = 0;
	int x,y;

	for(x = 0; x<CANDY_MAP_WIDTH; x++)
	{
		for(y=0; y<CANDY_MAP_HEIGH; y++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXIST))
				break;
		}

		if(y < CANDY_MAP_HEIGH)
			break;

		offsetNum--;
	}

	for(x = CANDY_MAP_WIDTH -1; x>=0; x--)
	{
		for(y=0; y<CANDY_MAP_HEIGH; y++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXIST))
				break;
		}

		if(y < CANDY_MAP_HEIGH)
			break;

		offsetNum++;
	}

	return (offsetNum*CANDY_CELL_WIDTH)>>1;

}

int CandyShare::getOffsetYForMakeCenter(void)
{
	int offsetNum = 0;
	int x,y;

	for(y=0; y<CANDY_MAP_HEIGH; y++)
	{
		for(x = 0; x<CANDY_MAP_WIDTH; x++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXIST))
				break;
		}

		if(x < CANDY_MAP_WIDTH)
			break;

		offsetNum++;
	}

	for(y= CANDY_MAP_HEIGH - 1; y>=0; y--)
	{
		for(x = 0; x<CANDY_MAP_WIDTH; x++)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_EXIST))
				break;
		}

		if(x < CANDY_MAP_WIDTH)
			break;

		offsetNum--;
	}

	return (offsetNum*CANDY_CELL_HEIGHT)>>1;
}


bool CandyShare::isTwoIndexNeighbour(CandyIndex first, CandyIndex second)
{
	return (first.y ==  second.y&& first.x == second.x-1)||
		(first.y ==  second.y  && first.x == second.x+1)||
		(first.y ==  second.y -1  && first.x == second.x )||
		(first.y ==  second.y +1  && first.x == second.x );
}


CCPoint CandyShare::getPosByIndex(CandyIndex index)
{
	int a = CANDY_CELL_WIDTH >> 1;
	return ccp(leftUpPos.x + index.x*CANDY_CELL_WIDTH + (CANDY_CELL_WIDTH >> 1), 
		leftUpPos.y - index.y*CANDY_CELL_HEIGHT- (CANDY_CELL_HEIGHT >> 1));
}

bool CandyShare::getIndexByPos(CCPoint point, CandyIndex &index)
{
	if(point.x - leftUpPos.x < 0 || point.y - (leftUpPos.y - CANDY_CELL_HEIGHT * CANDY_MAP_HEIGH) <0)
		return false;

	index.x = ((int)point.x - leftUpPos.x)/CANDY_CELL_WIDTH;
	index.y = 8 -(int)(point.y - (leftUpPos.y - CANDY_CELL_HEIGHT * CANDY_MAP_HEIGH))/CANDY_CELL_HEIGHT;
	return 	CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_EXIST);	

}

bool CandyShare::getAllCandyStopAction(bool ingoreBombing)
{
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	CCArray *candyArray = candyParent->getChildren();
	if(!candyArray)
		return true;

	for(unsigned int i=0; i<candyArray->count(); i++)
	{
		CandyCell *candy = (CandyCell *)candyArray->objectAtIndex(i);

		if(!candy->getCandyStates(CANDY_CELL_NORMAL))
			return false;

		if(!ingoreBombing && candy->special == CANDY_SPECIAL_BOMBING)
			return false;
#if 0
		if(!ingoreBombing && (candy->special == CANDY_SPECIAL_BOMBING ||candy->special == CANDY_SPECIAL_COLORFULL) )
		{
			if( candy->numberOfRunningActions() >1)
				return false;
		}
		else if( CandyManager::getInstance()->correctMapMgr->isDispelTipsCandy(candy))
		{
			if( candy->numberOfRunningActions() >1)
				return false;
		}
		else if(candy->numberOfRunningActions())
			return false;
#endif
	}
	return true;

}

float CandyShare::getFixedScreenHeight(void)
{
	float currentScreenWidth = CCDirector::sharedDirector()->getWinSize().width;
	float currentScreenHeight = CCDirector::sharedDirector()->getWinSize().height;

	float fixedScreenHeight = currentScreenHeight * TARGET_SCREEN_WIDTH/currentScreenWidth;

	return fixedScreenHeight;
}


bool CandyShare::getLayerIncludeCandy(CandyCell *candy)
{
	CCNode *candyParent = CandyManager::getInstance()->candyLayer->getCandyParent();
	return candyParent->getChildren()->containsObject(candy);
}


bool CandyShare::getCandyIdle(void)
{
	return getAllCandyStopAction(false) && CandyManager::getInstance()->combinationMgr->getCombinationActionDone();
}

void CandyShare::updateCollectNum(CandyCollectType type)
{

	for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
	{
		if(CandyManager::collectCandy[i].type == type && CandyManager::collectCandy[i].currentNum >0)
			CandyManager::collectCandy[i].currentNum--;
	}


	if ( CommonData::getMaxLevel() < AnalyseJson::unLockConfig.dailyTask )
		return;

	// 日常任务收集糖果模式
	std::list<SystemDailyTask>::iterator item = AnalyseJson::taskTable.dailyTask.begin();
	for(; item != AnalyseJson::taskTable.dailyTask.end(); item++)
	{
		if (1 == item->type && item->claimid == type )
		{
			item->complete++;
			break;
		}
	}
}


void CandyShare::collectCandy(CandyCell *candy, CandyComType comType)
{
	CandyCollectType type = CANDY_COLLECT_NUM;

	if(comType < CANDY_COM_NUM)
	{
		switch(comType)
		{
		case CANDY_COM_COLORFULL_COLORFULL:
			type = CANDY_COLLECT_COLOR_COLOR;
			break;

		case CANDY_COM_COLORFULL_NORMAL:
			type = CANDY_COLLECT_COLORFULL;
			break;

		case CANDY_COM_COLORFULL_STRIPE:
			type = CANDY_COLLECT_STR_COLOR;
			break;

		case CANDY_COM_COLORFULL_BOMB:
			type = CANDY_COLLECT_BOMB_COLOR;
			break;

		case CANDY_COM_STRIPE_STRIPE:
			type = CANDY_COLLECT_STR_STR;
			break;

		case CANDY_COM_STRIPE_BOMB:
			type = CANDY_COLLECT_STR_BOMB;
			break;

		case CANDY_COM_BOMB_BOMB:
			type = CANDY_COLLECT_BOMB_BOMB;
			break;
		}
	}
	else if(candy->special ==  CANDY_SPECIAL_NORMAL)
	{
		type = (CandyCollectType)candy->color;
	}
	else
	{
		switch(candy->special)
		{
		case CANDY_SPECIAL_HORIZONTAL:
		case CANDY_SPECIAL_VERTICAL:
			type = CANDY_COLLECT_STRIPE;
			break;

		case CANDY_SPECIAL_BOMB:
			type = CANDY_COLLECT_BOMB;
			break;

		case CANDY_SPECIAL_COLORFULL:
			type = CANDY_COLLECT_COLORFULL;
			break;
		}
	}

	if(type < CANDY_COLLECT_NUM)
		updateCollectNum(type);

	if ( candy )
		collectCandyActive(candy, type);
	return ;
}

void CandyShare::collectCandyActive( CandyCell *candy, CandyCollectType type )
{
	if ( CANDY_MODE_COLLECT != CandyManager::gameMode )
		return;

	const char *tempImgName = NULL;
	for(int i=0; i<COLLECT_MAX_TYPE_NUM; i++)
	{
		// 收集模式判断收集类型处理    横条竖条+彩糖时  条应该为收集的部分
		if( (CandyManager::collectCandy[i].targetNum && CandyManager::collectCandy[i].type == type) || 
			( CandyManager::collectCandy[i].targetNum && ( CANDY_SPECIAL_VERTICAL == candy->special || CANDY_SPECIAL_HORIZONTAL == candy->special) && candy->color == CandyManager::collectCandy[i].type ) )
		{
			static char imgName[50] = {0};
			memset(&imgName[0], 0, sizeof(char) *50);


			tempImgName = CCString::createWithFormat("%s/CollectType%d.png",COLLECT_TYPE_IMG_PATH,(int)CandyManager::collectCandy[i].type)->getCString();
			switch( CandyManager::collectCandy[i].type )
			{
				case CANDY_COLLECT_RED:
					sprintf(imgName,"%sCandyRedNormal.png",imgName);
					break;

				case CANDY_COLLECT_BLUE:
					sprintf(imgName,"%sCandyBlueNormal.png",imgName);
					break;

				case CANDY_COLLECT_GREEN:
					sprintf(imgName,"%sCandyGreenNormal.png",imgName);
					break;

				case CANDY_COLLECT_YELLOW:
					sprintf(imgName,"%sCandyYellowNormal.png",imgName);
					break;

				case CANDY_COLLECT_ORANGE:
					sprintf(imgName,"%sCandyOrangeNormal.png",imgName);
					break;

				case CANDY_COLLECT_PURPLE:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_STRIPE:
						sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_BOMB:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_COLORFULL:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_STR_STR:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_STR_BOMB:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_STR_COLOR:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_BOMB_BOMB:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_BOMB_COLOR:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

				case CANDY_COLLECT_COLOR_COLOR:
					sprintf(imgName,"%sCandyPurpleNormal.png",imgName);
					break;

			}
			CCSprite* pCollectCandy = CCSprite::create( tempImgName );
			pCollectCandy->setTag( type );
			pCollectCandy->setScale( 1.0f );
			pCollectCandy->setPosition( candy->getPosition() );
			pCollectCandy->setUserData( (void*)candy );
			CandyManager::getInstance()->getCurrentLayer()->addChild( pCollectCandy ,1000);

			for (int j = 0; j<COLLECT_MAX_TYPE_NUM; j++)
			{
				//if ( CandyManager::getInstance()->uiLayer->collectTypeImg[i]->isVisible() && type == CandyManager::getInstance()->uiLayer->collectTypeImg[i]->getTag())
				if ( CandyManager::collectCandy[i].targetNum)
				{
					CCPoint tem = CandyManager::getInstance()->uiLayer->collectTypeImg[i]->getParent()->convertToWorldSpace(CandyManager::getInstance()->uiLayer->collectTypeImg[i]->getPosition());
					CCActionInterval * repeatForever =CCRepeatForever::create((CCActionInterval* )CCRotateTo::create(1, 30));
					float nScale = 1.6f	;

					CCActionInterval*  actionScale1 = CCScaleTo::create(0.083f, 0.50f * nScale, 0.50f * nScale);
					CCActionInterval*  actionScale2 = CCScaleTo::create(0.083f, 0.68f * nScale, 0.68f * nScale);
					CCActionInterval*  actionScale3 = CCScaleTo::create(0.083f, 0.53f * nScale, 0.53f * nScale);
					CCActionInterval*  actionScale4 = CCScaleTo::create(0.083f, 0.65f * nScale, 0.65f * nScale);
					CCActionInterval*  actionScale5 = CCScaleTo::create(0.083f, 0.56f * nScale, 0.56f * nScale);
					CCActionInterval*  actionScale6 = CCScaleTo::create(0.083f, 0.63f * nScale, 0.63f * nScale);
					CCActionInterval*  actionScale7 = CCScaleTo::create(0.083f, 0.58f * nScale, 0.58f * nScale);
					CCActionInterval*  actionScale8 = CCScaleTo::create(0.083f, 0.61f * nScale, 0.61f * nScale);
					CCActionInterval*  actionScale9 = CCScaleTo::create(0.083f, 0.59f * nScale, 0.59f * nScale);
					CCActionInterval*  actionScale10 = CCScaleTo::create(0.083f, 0.6f * nScale, 0.60f * nScale);


					pCollectCandy->runAction(
						CCSequence::create(
						CCSpawn::create(getEffectBezierAction(candy->getPosition(), tem), CCScaleTo::create( 0.8f, 1.3f ), CCRotateTo::create(1, 1441), NULL),
						//CCCallFuncND::create(candy, callfuncND_selector(CandyShare::callfuncCollectCandyNumChange), (void*)i),
						CCSequence::create(
						actionScale1,
						actionScale2,
						actionScale3,
						actionScale4,
// 						actionScale5,
// 						actionScale6,
// 						actionScale7,
// 						actionScale8,
// 						actionScale9,
// 						actionScale10,
						NULL),
						CCFadeOut::create( 0.1f ),
						CCCallFuncND::create(this, callfuncND_selector(CandyShare::callfuncCollectCandy), (void*)pCollectCandy),
						NULL));
					return;
				}
			}
			break;
		}
	}
}

void CandyShare::callfuncCollectCandy(CCNode* sender, void* data)
{
	CCSprite* pCollectCandy = (CCSprite*)data;
	pCollectCandy->removeFromParent();
}


CandyColor CandyShare::getCandyRandomColorByLua(void)
{
	if( CommonData::m_levelFailNum[CandyManager::currentLevel]>= CandyManager::modifyPercent
		&& CandyManager::currentLevel == (CommonData::getMaxLevel()+1)
		&& CandyManager::modifyPercent != 0)
	{
		int resultColor =0;

		int randNum = rand()%100;
		int percentRed = CandyManager::modifyRed;
		int percentBlue = percentRed + CandyManager::modifyBlue;
		int percentGreen = percentBlue + CandyManager::modifyGreen;
		int percentYellow = percentGreen + CandyManager::modifyYellow;
		int percentOrange = percentYellow + CandyManager::modifyOrange;
		int percentPurple = percentOrange + CandyManager::modifyPurple;


		if(randNum < percentRed)
		{
			resultColor =0;
		}
		else if(randNum < percentBlue)
		{
			resultColor =1;
		}
		else if(randNum < percentGreen)
		{
			resultColor =2;
		}
		else if(randNum < percentYellow)
		{
			resultColor =3;
		}
		else if(randNum < percentOrange)
		{
			resultColor =4;
		}
		else
		{
			resultColor =5;
		}
		return (CandyColor)resultColor;
	}
	else
	{
		if(CandyManager::randomSeed)
		{
			if(currentRandSeed != newRandSeed )
			{
				currentRandSeed = newRandSeed;
				srand( CandyManager::randomSeed + currentRandSeed);
			}
		}	
		return (CandyColor)(rand()%CandyManager::numberOfColours);
	}
}

CandyColor CandyShare::getCandyRandomColor(void)
{
	if(CandyManager::randomSeed)
	{
		if(currentRandSeed != newRandSeed )
		{
			currentRandSeed = newRandSeed;
			srand( CandyManager::randomSeed + currentRandSeed);
		}
	}	
	return (CandyColor)(rand()%CandyManager::numberOfColours);
}

void CandyShare::changeColor(CandyColor color, ccColor4F& ret)
{
	switch(color)
	{
	case CANDY_COLOR_RED:
		ret =  ccc4f(1,0,0,1);
		break;	

	case CANDY_COLOR_BLUE:
		ret =  ccc4f(45.0f/255,159.0f/255,255.0f/255,1);
		break;

	case CANDY_COLOR_GREEN:
		ret =  ccc4f(0,1,0,1);
		break;

	case CANDY_COLOR_YELLOW:
		ret =  ccc4f(1,1,0,1);
		break;	

	case CANDY_COLOR_ORANGE:
		ret =  ccc4f(233.0f/255,199.0f/255,0,1);
		break;	

	case CANDY_COLOR_PURPLE:
		ret =  ccc4f(253.0f/255,42.0f/255,247.0f/255,1);
		break;	
	}
}

CCActionInterval *CandyShare::getEffectBezierAction(CCPoint originPos, CCPoint targetPos)
{
	const float offsetX = (targetPos.x-originPos.x)<100.0f?100.0f:0;
	const float moveTime = sqrtf(ccpDistance(targetPos, originPos) *0.002f)/2;	

	ccBezierConfig bezier; 
	bezier.controlPoint_1 = originPos; 
	bezier.controlPoint_2 = ccp((targetPos.x+originPos.x)*0.5f+rand()%2?offsetX:-offsetX,
		targetPos.y < originPos.y?originPos.y+100.0f:originPos.y-100.0f); 
	bezier.endPosition = targetPos; 

	return CCBezierTo::create(moveTime, bezier);
}

