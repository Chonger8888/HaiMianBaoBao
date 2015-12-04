#include "CandyCorrectMap.h"
#include "CandyManager.h"

// ���š���������ʾ
USING_NS_CC;
CandyCorrectMap::CandyCorrectMap()
{
	displayTipsFlag = true;

	sortArray = new CCArray();

	memset(&colorCout[0], 0, sizeof(CandyCount) * CANDY_COLOR_NORMAL_NUM);
	colorCout[0].color = CANDY_COLOR_RED;
	colorCout[1].color = CANDY_COLOR_BLUE;
	colorCout[2].color = CANDY_COLOR_GREEN;
	colorCout[3].color = CANDY_COLOR_YELLOW;
	colorCout[4].color = CANDY_COLOR_ORANGE;
	colorCout[5].color = CANDY_COLOR_PURPLE;

	isResorting = false;

	memset(&dispelTips[0], 0, sizeof(CandyIndex) * 3);
	memset(&dispelFlag[0], 0, sizeof(CandyIndex) * 3);
	memset(&dispelTipsCandy[0], 0, sizeof(CandyCell*) * 3);

}

CandyCorrectMap::~CandyCorrectMap()
{
	CC_SAFE_DELETE(sortArray);
}

void CandyCorrectMap::updateCandyCorrectMap(void)
{
	static int timeCount = 0;
	if(getResortState())
		return;


	if(CandyManager::gameMode == CANDY_MODE_TIMING)
	{
		if(CandyManager::timeLimit <= 0 )
			return ;
	}
	else
	{
		if(CandyMove::moveLimit<= 0 )
			return ;
	}

	if( CandyManager::getInstance()->shareMgr->getCandyIdle() && CandyManager::getInstance()->resultMgr->getGameRunning())		//��ҿ����ƶ�candy
	{
		if(timeCount == 0)		//�״�����ɷ��������
		{
			if(isNeedToResortCandy())
			{
				CandyManager::getInstance()->candyLayer->runResortCandyAction();
			}
			/*if( !resortCandyExecute(false))//false��ʾ����������candy
			{//����ʧ��
			CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NO_DISPEL);
			}*/
		}
		else if(timeCount %( 60 * 5) == 0) //5�벻����ӳ �������ʾ
		{
			displayCandyDispelTips();
		}
		timeCount++;
	}
	else
	{
		if(timeCount)
		{
			cancelCandyDispelTips();
			timeCount = 0;
		}
	}
}

//����������ʾ
void CandyCorrectMap::displayCandyDispelTips(void)
{
	if(!displayTipsFlag)
		return;

	for(int i=0; i<3; i++)
	{
		dispelTipsCandy[i] = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(dispelTips[i]);
		if(dispelTipsCandy[i])
		{
			CCSequence* scaleAction =  CCSequence::create( CCScaleTo::create(0.5f, 1.2f),CCScaleTo::create(0.5f, 1.0f),NULL);
			CCRepeatForever *dispelAction = CCRepeatForever::create(scaleAction);
			dispelAction->setTag(TAG_ACTION_DISPEL_TIPS);
			dispelTipsCandy[i]->runAction(dispelAction);
#ifndef CANDY_USE_PLIST
			CCSequence* scaleAction2 =  CCSequence::create( CCHSLTo::create(0.5f, HSL_TIPS_H,HSL_TIPS_S,HSL_TIPS_L),CCHSLTo::create(0.5f, 0,0,0),NULL);
			CCRepeatForever *dispelAction2 = CCRepeatForever::create(scaleAction2);
			dispelAction2->setTag(TAG_ACTION_FADE_TIPS);
			dispelTipsCandy[i]->runAction(dispelAction2);
#endif
		}
	}
	CandyManager::getInstance()->candyLayer->scheduleOnce(schedule_selector(CandyCorrectMap::cancelCandyDispelTips), 3);
}

void CandyCorrectMap::cancelCandyDispelTips(float dt)
{
	for(int i=0; i<3; i++)
	{
		if(CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i])
		{	
#ifndef CANDY_USE_PLIST
			CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i]->stopActionByTag(TAG_ACTION_FADE_TIPS);
			CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i]->setHSL(0,0,0);
#endif
			CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i]->stopActionByTag(TAG_ACTION_DISPEL_TIPS);
			CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i]->setScale(1.0);
			CandyManager::getInstance()->correctMapMgr->dispelTipsCandy[i] = NULL;
		}
	}
	CandyManager::getInstance()->candyLayer->unschedule(schedule_selector(CandyCorrectMap::cancelCandyDispelTips));
}

bool CandyCorrectMap::isDispelTipsCandy(CandyCell *candy)
{
	for(int i=0; i<3; i++)
	{
		if(dispelTipsCandy[i] == candy)
			return true;
	}
	return false;
}

void CandyCorrectMap::setDisplayCandyDispelTipsFlag(bool flag)
{
	displayTipsFlag = flag;
}

void CandyCorrectMap::createCandyWithMapData(int typeNum)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
		{
			if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CANDY))
				continue;

			if(CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y)))
				continue;

			CandyCell *newCandy;
			do
			{
				newCandy = CandyCell::create(cIndex(x, y), CandyManager::getInstance()->shareMgr->getCandyRandomColor(), CANDY_SPECIAL_NORMAL);
			}
			while(!setCandyByIndexAndCheckDispel(cIndex(x, y), newCandy));

			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(x, y), newCandy);
			CandyManager::getInstance()->candyLayer->addToCandyParent(newCandy);
		}
		if( !CandyManager::getInstance()->mapDataMgr->candyDropMode )
			if(isNeedToResortCandy())
				if( !resortCandyExecute(true))//����ʧ��
				{
					CandyManager::getInstance()->resultMgr->setCurrentResult(CANDY_RESULT_NO_DISPEL);
				}
}

void CandyCorrectMap::setDispelTipsIndex(CandyDispelCell *dispel)
{
	int offset1 = 1, offset2 = -1;
	if(dispel->right - dispel->left  >=2)
	{
		if(dispel->right == dispel->index.x)
			offset1 = -2;
		if(dispel->left== dispel->index.x)
			offset2 = 2;

		dispelTips[1] = cIndex(dispel->index.x + offset1, dispel->index.y);
		dispelTips[2] = cIndex(dispel->index.x + offset2, dispel->index.y);

	}
	else if(dispel->down- dispel->up  >=2)
	{
		if(dispel->down== dispel->index.y)
			offset1 = -2;
		if(dispel->up== dispel->index.y)
			offset2 = 2;

		dispelTips[1] = cIndex(dispel->index.x , dispel->index.y+ offset1);
		dispelTips[2] = cIndex(dispel->index.x , dispel->index.y+ offset2);
	}
}


bool CandyCorrectMap::isCandyDispelByMove(CandyCell *candy, CandyIndex changeIndex)
{
	bool ret = false;

	CandyCell *changeCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(changeIndex);
	if(!changeCandy)
		return ret ;

	//�ж��Ƿ�����ƶ�
	if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(candy->index, MAP_CELL_LOCK) 
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(changeIndex, MAP_CELL_LOCK) )
		return ret;

	//����
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(candy->index,  changeCandy, false);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(changeIndex,  candy, false);

	CandyDispelCell* dispel = CandyManager::getInstance()->dispelMgr->checkCandyDispel(changeCandy);
	if(dispel)
	{
		dispelTips[0] = candy->index;
		setDispelTipsIndex(dispel);
		ret = true;
	}

	//�ع�
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(changeCandy->index,  candy, false);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(changeIndex,  changeCandy, false);

	return ret ;
}

bool CandyCorrectMap::isCandySpecialDispelByMove(CandyCell *candy, CandyIndex changeIndex)
{
	CandyCell *changeCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(changeIndex);
	if(!changeCandy)
		return false ;

	//��������ӣ�� 
	if(changeCandy->special==  CANDY_SPECIAL_INGREDIENT ||  changeCandy->special==  CANDY_SPECIAL_LICORICE ||  changeCandy->special==  CANDY_SPECIAL_EXPLOSION ||  changeCandy->special==  CANDY_SPECIAL_COLORFULL)
		return false;

	//�ж��Ƿ�����ƶ�
	if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(candy->index, MAP_CELL_LOCK) 
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(changeIndex, MAP_CELL_LOCK) )
		return false;


	if(candy->special == CANDY_SPECIAL_COLORFULL 	//���ǲ�����������������
		|| changeCandy->special != CANDY_SPECIAL_NORMAL) // ����һ�ǹ�Ҳ�������ǹ�
	{
		dispelTips[0] = candy->index;
		dispelTips[1] = changeCandy->index;
		dispelTips[2] = cIndex(-1, -1);
		return true;
	}
	return false;
}


bool CandyCorrectMap::isNeedToResortCandy(void)
{	
	//�������
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
			if(!candy || candy->special == CANDY_SPECIAL_NORMAL 
				|| candy->special == CANDY_SPECIAL_INGREDIENT
				|| candy->special == CANDY_SPECIAL_LICORICE
				||  candy->special==  CANDY_SPECIAL_EXPLOSION)
				continue;

			if(isCandySpecialDispelByMove(candy, cIndex(candy->index.x-1, candy->index.y))
				||isCandySpecialDispelByMove(candy, cIndex(candy->index.x+1, candy->index.y))
				||isCandySpecialDispelByMove(candy, cIndex(candy->index.x, candy->index.y-1))
				||isCandySpecialDispelByMove(candy, cIndex(candy->index.x, candy->index.y+1)) )
				return false;
		}

	//��ͨ
	for(int y=0; y<CANDY_MAP_HEIGH; y++)
		for(int x=0; x<CANDY_MAP_WIDTH; x++)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
			if(!candy)
				continue;

			if(isCandyDispelByMove(candy, cIndex(candy->index.x-1, candy->index.y))
				||isCandyDispelByMove(candy, cIndex(candy->index.x+1, candy->index.y))
				||isCandyDispelByMove(candy, cIndex(candy->index.x, candy->index.y-1))
				||isCandyDispelByMove(candy, cIndex(candy->index.x, candy->index.y+1)) )
				return false;
		}

		return true;
}


//��ȡ��ͼ�Ͽ���������ĸ��ӣ���������һ���ӿ����ϻ��»�������ƶ�һ��
//horizontal �����ж�
//verticcal �����ж�
bool CandyCorrectMap::getMapDispelFlagByIndex(CandyIndex index, int horizontal, int verticcal)
{
	dispelFlag[0] = cIndex(index.x+0*horizontal, index.y + 0 * verticcal);
	dispelFlag[1] = cIndex(index.x+1 *horizontal, index.y + 1 * verticcal);
	dispelFlag[2] = cIndex(index.x+2 *horizontal, index.y + 2 * verticcal);

	if(!getStatesFromResortMap(dispelFlag[0])
		|| !getStatesFromResortMap(dispelFlag[1])
		|| !getStatesFromResortMap(dispelFlag[2]))
		return false;

	CandyCell *candy0 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( dispelFlag[0] ) ;
	CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( dispelFlag[1] ) ;
	CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( dispelFlag[2] ) ;

#if 0
	//�жϵ�ǰ���������Ƿ���Ч
	if(	candy0 && candy0->color < CANDY_COLOR_NORMAL_NUM
		&& candy1 && candy1->color < CANDY_COLOR_NORMAL_NUM
		&& candy2  && candy2->color < CANDY_COLOR_NORMAL_NUM	)
#endif
	{
		//�жϵ�һ�������Ƿ������һλ(�������)������һλ(�������)
		if( getStatesFromResortMap( cIndex( dispelFlag[0].x- horizontal , dispelFlag[0].y- verticcal  ) ) 
			&&  getStatesFromResortMap(cIndex( dispelFlag[0].x- horizontal , dispelFlag[0].y- verticcal  )) )
		{
			dispelFlag[0] = cIndex( dispelFlag[0].x- horizontal , dispelFlag[0].y- verticcal ); 
			return true;
		}
		//�жϵ����������Ƿ������һλ(�������)������һλ(�������)
		else if( getStatesFromResortMap( cIndex( dispelFlag[2].x+ horizontal , dispelFlag[2].y+ verticcal  ) ) 
			&& getStatesFromResortMap(cIndex( dispelFlag[2].x+ horizontal , dispelFlag[2].y+ verticcal  ) ) )
		{
			dispelFlag[2] = cIndex( dispelFlag[2].x+ horizontal , dispelFlag[2].y+ verticcal  );
			return true;
		}
		else
		{
			//�ж����������Ƿ��������һλ(�������)��������һλ(�������)
			for(int i=0; i<3; i++)
			{
				if( getStatesFromResortMap( cIndex( dispelFlag[i].x - verticcal ,dispelFlag[i].y - horizontal) ) 
					&&  getStatesFromResortMap(cIndex( dispelFlag[i].x - verticcal ,dispelFlag[i].y - horizontal) ))
				{
					dispelFlag[i] = cIndex( dispelFlag[i].x - verticcal ,dispelFlag[i].y - horizontal) ;
					return true;
				}
				else if( getStatesFromResortMap( cIndex( dispelFlag[i].x + verticcal ,dispelFlag[i].y + horizontal) ) 
					&&  getStatesFromResortMap(cIndex( dispelFlag[i].x + verticcal ,dispelFlag[i].y + horizontal)) )
				{
					dispelFlag[i] = cIndex( dispelFlag[i].x + verticcal ,dispelFlag[i].y + horizontal);
					return true;
				}
			}
		}
	}
	return false;
}

bool CandyCorrectMap::getMapDispelFlag(void)
{
	for(int y =0; y < CANDY_MAP_HEIGH; y++)
		for(int x =0; x < CANDY_MAP_WIDTH; x++)
		{
			if(getMapDispelFlagByIndex(cIndex(x, y), 1, 0) || getMapDispelFlagByIndex(cIndex(x, y), 0, 1))
			{
				memcpy(&dispelTips[0], &dispelFlag[0], sizeof(CandyIndex) * 3);
				return true;
			}
		}

		return false;
}

bool CandyCorrectMap::getStatesFromResortMap(CandyIndex index)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return false;

	return resortMap[index.y][index.x];
}

bool CandyCorrectMap::resortCandyInit(bool changeLock)
{
	for(int y =0; y < CANDY_MAP_HEIGH; y++)
		for(int x =0; x < CANDY_MAP_WIDTH; x++)
		{
			CandyCell *cell = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
			if(!cell)
			{
				resortMap[y][x] = false;
			}
			else if(!changeLock &&  CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_LOCK))//����������candy
			{
				resortMap[y][x] = false;
			}
			else if(cell->special == CANDY_SPECIAL_INGREDIENT || cell->special == CANDY_SPECIAL_LICORICE || cell->special == CANDY_SPECIAL_COLORFULL)//����������ӣ�Ҹʲ�
			{
				resortMap[y][x] = false;
			}
			else if(cell->special == CANDY_SPECIAL_EXPLOSION)//��������ʱը��
			{
				resortMap[y][x] = false;
			}
			else
			{
				sortArray->addObject(cell);
				resortMap[y][x] = true;
				CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(x, y), NULL);

				cell->setPosition(ccp(0,0));
			}
		}

		if(!getMapDispelFlag())
			return false;

		return true;

}

bool CandyCorrectMap::setCandyCanDispel(void)
{
	for(int i=0; i<CANDY_COLOR_NORMAL_NUM; i++)
	{
		CandyDispelCell* dispel = NULL;

		//�ж����ֵ�Ƿ�����3
		if(colorCout[i].num < 3)
			return false;

		CandyCell *candy[3];

		for(int j=0; j<3; j++)
		{
			candy[j] = getCandyInArrayByColor(colorCout[i].color);
			CandyManager::getInstance()->mapDataMgr->setCandyByIndex(dispelFlag[j],  candy[j]);
			sortArray->removeObject(candy[j]);
			colorCout[i].num--;
			if(!dispel)
				dispel = CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy[j]);
		}
		if(!dispel)//������lockcandy ����
		{
			return true;
		}
		else
		{
			//��ԭ
			for(int j=0; j<3; j++)
			{
				colorCout[i].num++;
				sortArray->addObject(candy[j]);
				CandyManager::getInstance()->mapDataMgr->setCandyByIndex( dispelFlag[j], NULL );
			}
		}
	}
	return false;
}


bool CandyCorrectMap::getResortState(void)
{
	return isResorting;
}

void CandyCorrectMap::setResortState(bool state)
{
	isResorting = state;
}

bool CandyCorrectMap::getResortResult(void)
{
	return resortRet;
}

void CandyCorrectMap::setResortResult(bool ret)
{
	resortRet = ret;
}

//����moveLock��ʾ�����е��ǹ��ɸ���λ��
bool CandyCorrectMap::resortCandyExecute(bool changeLock)
{
	bool ret = false;

	ret= resortCandyInit(changeLock);

	//��ȡ������ɫ������������
	getColorCount(true);

	//���������
	//if(rand()%3==1)

	sortColorCount();

	//�����������������
	if(setCandyCanDispel() == false)
		ret = false;
#ifdef DEMO_FOR_TELECOM
	// ���������ӣ������ӷ�ֹ��������	
	for(int y =0; y < CANDY_MAP_HEIGH; y++)
		for(int x =0; x < CANDY_MAP_WIDTH; x++)
		{
			if( resortMap[y][x] && CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex( x, y) )== NULL  )
			{
				if(!isSuccessToSetCandyByIndex( cIndex( x, y) ))
					exchangeAvailableCandy(cIndex( x, y) );
			}
		}
#else
	backTrackingResort();
#endif
	return ret;
}


void CandyCorrectMap::backTrackingResort(void)
{
	for(int y =0; y < CANDY_MAP_HEIGH; y++)
		for(int x =0; x < CANDY_MAP_WIDTH; x++)
		{
			if( resortMap[y][x] && CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex( x, y) )== NULL  )
				startColor[y][x] = currentColor[y][x] =rand()%CANDY_COLOR_NORMAL_NUM;
			else
				startColor[y][x] = currentColor[y][x] = -1;
		}



		for(int y =0; y < CANDY_MAP_HEIGH;)
			for(int x =0; x < CANDY_MAP_WIDTH; )
			{
				if( resortMap[y][x] && CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex( x, y) )== NULL  )
				{
					CandyCell* candy = backTrackingGetCandy(x,y);
					if(candy)
					{
						if(setCandyByIndexAndCheckDispel( cIndex(x, y), candy) )
						{
							sortArray->removeObject(candy);
							if(++x >= CANDY_MAP_WIDTH)
								++y;
						}
						else
						{
							backTrackingGetNextColor(x,y);
						}
					}
				}
				else
				{
					if(++x >= CANDY_MAP_WIDTH)
						++y;
				}
			}

}

CandyCell* CandyCorrectMap::backTrackingGetCandy(int &x, int &y)
{
	CandyCell *candy = NULL;
	while(!candy)
	{
		candy = getCandyInArrayByColor((CandyColor)currentColor[y][x]);
		if(candy == NULL)
		{
			if(!backTrackingGetNextColor(x,y))
				return NULL;
		}
	}
	return candy;
}

bool CandyCorrectMap::backTrackingIndex(int &x, int &y)
{
	int offset = y * CANDY_MAP_WIDTH + x;
	while(--offset >= 0)
	{
		x = offset % CANDY_MAP_WIDTH;
		y = offset / CANDY_MAP_WIDTH;
		if(currentColor[y][x] != -1)
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex( x, y) );
			if(candy)
			{
				CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex( x, y), NULL);
				sortArray->addObject(candy);
				backTrackingGetNextColor(x,y);
				return true;
			}
		}
	}
	return false;

}

bool CandyCorrectMap::backTrackingGetNextColor( int &x,  int &y)
{
	currentColor[y][x] = (currentColor[y][x] + 1) %CANDY_COLOR_NORMAL_NUM;
	if(currentColor[y][x] == startColor[y][x])
	{
		backTrackingIndex(x,y);
		return false;
	}
	return true;
}

void CandyCorrectMap::getColorCount(bool fromArray)
{
	for(int i=0; i<CANDY_COLOR_NORMAL_NUM; i++)
	{
		colorCout[i].num = 0;

		if(fromArray)
		{
			for(int j=0; j<(int)sortArray->count(); j++)
			{
				CandyCell* candy  = (CandyCell*)sortArray->objectAtIndex(j);
				if(colorCout[i].color == candy->color)
					colorCout[i].num++;
			}
		}
		else
		{
			for(int y =0; y < CANDY_MAP_HEIGH; y++)
				for(int x =0; x < CANDY_MAP_WIDTH; x++)
				{
					CandyCell *candy =  CandyManager::getInstance()->mapDataMgr->getCandyByIndex( cIndex( x, y) );
					if(candy && candy->color == colorCout[i].color)
						colorCout[i].num++;
				}
		}

	}
}

void CandyCorrectMap::sortColorCount(void)
{
	for(int i=0; i<CANDY_COLOR_NORMAL_NUM; i++)
		for(int j=i+1; j< CANDY_COLOR_NORMAL_NUM; j++)
		{
			if(colorCout[i].num <=  colorCout[j].num)
			{
				CandyCount countTem = colorCout[i];
				colorCout[i] = colorCout[j];
				colorCout[j] = countTem;
			}
		}
}

CandyCell* CandyCorrectMap::getCandyInArrayByColor(CandyColor color)
{
	for(int i=0; i<(int)sortArray->count(); i++)
	{
		CandyCell* candy  = (CandyCell*)sortArray->objectAtIndex(i);
		if(candy->color == color)
		{
			return candy;
		}
	}
	return NULL;
}

bool CandyCorrectMap::setCandyByIndexAndCheckDispel(CandyIndex index, CandyCell* candy)
{
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, candy);
	if(CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy))
	{
		//������ ���ɷ��ô�candy
		CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, NULL);
		return false;
	}
	return true;
}

bool CandyCorrectMap::isSuccessToSetCandyByIndex(CandyIndex index)
{
	//����ͬһ��ɫ�������򣬱�֤������������
	sortColorCount();

	for(int i=0; i<CANDY_COLOR_NORMAL_NUM; i++)
	{
		CandyCell *candy = getCandyInArrayByColor(colorCout[i].color);
		if(candy  && setCandyByIndexAndCheckDispel( index , candy)  )
		{
			colorCout[i].num--;
			sortArray->removeObject(candy);
			return true;
		}
	}
	return false;
}

void CandyCorrectMap::exchangeAvailableCandy(CandyIndex index)
{
	for(int i=0; i<CANDY_COLOR_NORMAL_NUM; i++)
	{
		CandyCell *candy = getCandyInArrayByColor(colorCout[i].color);
		for(int y =0; y < CANDY_MAP_HEIGH; y++)
			for(int x =0; x < CANDY_MAP_WIDTH; x++)
			{
				bool isDispelTipsIndex = false;

				for(int j=0; j<3; j++)
					if(dispelTips[j].x == x && dispelTips[j].y == y)
						isDispelTipsIndex = true;

				if(!isDispelTipsIndex && resortMap[y][x])
				{
					CandyCell *changeCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x,  y));
					if(candy  && setCandyByIndexAndCheckDispel( cIndex(x,  y) , candy)
						&& changeCandy  && setCandyByIndexAndCheckDispel( index , changeCandy))
					{
						// �����ɹ�
						colorCout[i].num--;
						sortArray->removeObject(candy);
						return;
					}
					else
					{
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(cIndex(x,  y), changeCandy);//����
					}
				}
			}
	}
}


