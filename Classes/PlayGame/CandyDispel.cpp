#include "CandyDispel.h"
#include "CandyManager.h"

USING_NS_CC;

CandyDispelCell* CandyDispelCell::create(CandyIndex index)
{
	CandyDispelCell *ret = new CandyDispelCell();
	CCAssert(ret != NULL, "CandyDispelCell::create");
	ret->autorelease();
	ret->index = index;
	ret->left =index.x;
	ret->right=index.x;
	ret->up=index.y;
	ret->down=index.y;
	
	return ret;
}


CandyDispel::CandyDispel()
{
	changedArray = new CCArray();
	dispelArray = new CCArray();
	redundantArray = new CCArray();
}

CandyDispel::~CandyDispel()
{
	CC_SAFE_DELETE(changedArray);
	CC_SAFE_DELETE(dispelArray);
	CC_SAFE_DELETE(redundantArray);
}


void CandyDispel::removeCandyFromChangeArray(CandyCell* candy)
{
	if(changedArray->containsObject(candy))
		changedArray->removeObject(candy);

}


void CandyDispel::addCandyToChangeArray(CandyCell* candy)
{
	if(!changedArray->containsObject(candy))
		changedArray->addObject(candy);
				
}

void CandyDispel::checkChangeArrayDispel(void)
{
	if(!changedArray )
		return;

	for(int i =0; i<(int)changedArray->count();)
		{
			CandyCell* cell  = (CandyCell*)changedArray->objectAtIndex(i);
			if( !cell->getCandyStates(CANDY_CELL_NORMAL) )
				{
					i++;
					continue;
				}
			
			CandyDispelCell* dispel = checkCandyDispel(cell);
			if(dispel)
				{
					if( !dispelArray->containsObject(dispel) )
						dispelArray->addObject(dispel);
				}
			
			changedArray->removeObjectAtIndex(i, true);
		}
		
}


CandyDispelCell* CandyDispel::checkCandyDispel(CandyCell* candy)
{
	if(CandyManager::getInstance()->mapDataMgr->getCandyByIndex(candy->index) != candy)
		return NULL;

	if(candy->color >= CANDY_COLOR_NORMAL_NUM )
		return NULL;
	
	CandyDispelCell* dispel = CandyDispelCell::create(candy->index);
	
	while(--dispel->left>=0)
		{
			if(!checkCandyColorByIndex(cIndex(dispel->left, candy->index.y), candy->color))
				break;
		}
		++dispel->left;
		
	while(++dispel->right < 9)
		{
			if(!checkCandyColorByIndex(cIndex(dispel->right, candy->index.y), candy->color))
				break;
		}
		--dispel->right;
		
	while(--dispel->up >= 0)
		{
			if(!checkCandyColorByIndex(cIndex( candy->index.x,dispel->up), candy->color))
				break;
		}
		++dispel->up;
		
	while(++dispel->down < 9)
		{
			if(!checkCandyColorByIndex(cIndex( candy->index.x,dispel->down), candy->color))
				break;
		}
		--dispel->down;

	if(dispel->right - dispel->left  <2)
		{
			dispel->right = dispel->index.x;
			dispel->left = dispel->index.x;
		}

	if(dispel->down - dispel->up  <2)
		{
			dispel->down = dispel->index.y;
			dispel->up = dispel->index.y;
		}
	
	if(dispel->right - dispel->left  >=2 || dispel->down- dispel->up  >=2)
		{
			return dispel;
		}
	
	return NULL;

}


//　消除更新新糖果
void CandyDispel::updateCandyDispel(void)
{
	checkChangeArrayDispel();
	
	if(dispelArray->count() <=0)
		return;
	
	removeRedundantDispel();
	
	for(int i =0; i<(int)dispelArray->count(); i++)
		{
			CandyDispelCell* dispel  = (CandyDispelCell*)dispelArray->objectAtIndex(i);
			CandyCell *cell = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(dispel->index);
			if(!cell)
				continue;

			NewBornCandy newBornCandyInfo;
			resetDispelNum();
			getNewBornSpecialCandy(dispel, newBornCandyInfo);
			createNewBornSpecialCandy(newBornCandyInfo);
			doNormalDispel(dispel, &newBornCandyInfo);
		}

	dispelArray->removeAllObjects();

}

void CandyDispel::resetDispelNum(void)
{
	dispelJellyNum= 0;
	dispelExplosionNum= 0;
}

void CandyDispel::doNormalDispel(CandyDispelCell* dispel, NewBornCandy* newBorn)
{
	int dispelNum = 1;

	CandyCell *dispelCandy;

	if(dispel->right - dispel->left  >=2)
	{
		for(int x =dispel->left; x<= dispel->right; x++)
			if(dispelCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, dispel->index.y)),  dispelCandy)
			{
				if(dispelCandy->special == CANDY_SPECIAL_BOMBING)
					continue;

				if( newBorn->flag)
					if(newBorn->index.x == x && newBorn->index.y == dispel->index.y)
						continue;

				normalDispelCandy(dispelCandy);
			}

			dispelNum += (dispel->right - dispel->left );
	}
	if(dispel->down- dispel->up  >=2)
	{
		for(int y =dispel->up; y<= dispel->down; y++)
			if(dispelCandy= CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(dispel->index.x, y)),  dispelCandy)
			{
				if(dispelCandy->special == CANDY_SPECIAL_BOMBING)
					continue;

				if( newBorn->flag)
					if(newBorn->index.x == dispel->index.x && newBorn->index.y == y)
						continue;

				normalDispelCandy(dispelCandy);	

			}
			dispelNum += (dispel->down - dispel->up );
	}

	if(dispelNum >1)
	{
		int comboNum = CandyManager::getInstance()->scoreMgr->getComboNumber();
		int score = CANDY_SCORE_BASE * dispelNum * (dispelNum - 2) * ( comboNum + 1) + CANDY_SCORE_JELLY * dispelJellyNum + CANDY_SCORE_EXPLOSION * dispelExplosionNum;

		CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(dispel->index);
		CandyColor color = candy?candy->color:CANDY_COLOR_RED;

		CCPoint pos;
		if(dispel->right - dispel->left  >=2 && dispel->down- dispel->up  >=2)
		{
			pos = CandyManager::getInstance()->shareMgr->getPosByIndex(dispel->index);
		}
		else
		{
			pos = CandyManager::getInstance()->shareMgr->getPosByIndex(cIndex((dispel->right + dispel->left)>>1, (dispel->down+ dispel->up)>>1));
			pos.x = pos.x + (dispel->right - dispel->left) % 2 * (CANDY_CELL_WIDTH>>1);
			pos.y = pos.y - (dispel->down - dispel->up) % 2 * (CANDY_CELL_HEIGHT>>1);
		}

		CandyManager::getInstance()->scoreMgr->addCandyScore(score, pos, color);
		CandyManager::getInstance()->scoreMgr->increaseComboNumber();
		CandyManager::getInstance()->uiLayer->increaseEnergyJarPercentage(dispelNum);
	}
}
void CandyDispel::normalDispelCandy(CandyCell *dispelCandy)
{
	if(CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(dispelCandy->index))
		dispelJellyNum++;
	
	if(dispelSingleCandy(dispelCandy))
		{
			if(dispelCandy->special == CANDY_SPECIAL_EXPLOSION)
				dispelExplosionNum++;
			
			CandyManager::getInstance()->creamMgr->dispelCandyEffectCream(dispelCandy->index);
		
			CandyManager::getInstance()->licoricesMgr->dispelCandyEffectLicorice(dispelCandy->index);

			CandyManager::getInstance()->chocolateMgr->dispelCandyEffectChocolate(dispelCandy->index);
		}
}

/*返回true表示成功消除*/
bool CandyDispel::dispelSingleCandy(CandyCell* candy, bool checkSpecial)
{
	if(!candy || !candy->getCandyStates(CANDY_CELL_NORMAL))
		return false;

	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(candy->index, MAP_CELL_LOCK))
	{
		CandyManager::getInstance()->lockMgr->removeCandyLockCell(candy->index);
		return false;
	}
	else
	{
		if(candy->special != CANDY_SPECIAL_COLORFULL) //彩球会在runSpecialCandy释放
			candy->runCandyDeleteAction();
		if(candy->special != CANDY_SPECIAL_NORMAL)
		{
			CandyManager::getInstance()->specialMgr->runSpecialCandy(candy, true);
			CandyManager::getInstance()->scoreMgr->increaseComboNumber();
		}
		return true;
	}
}

//　获得重新生成特殊糖果
void CandyDispel::getNewBornSpecialCandy(CandyDispelCell* dispel, NewBornCandy &newBornCandyInfo)
{	
	newBornCandyInfo.flag = false;
	
	CandyCell *dispelNode = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(dispel->index);
	if(!dispelNode)
		return;
	
	newBornCandyInfo.color =  dispelNode->color;
			
	if(dispel->right - dispel->left  >=4 || dispel->down- dispel->up  >=4)
		{
			newBornCandyInfo.color =  CANDY_COLOR_SPECIAL;
			newBornCandyInfo.special = CANDY_SPECIAL_COLORFULL;
			
		}
	else if(dispel->right - dispel->left  >=2 && dispel->down- dispel->up  >=2)
		{
			newBornCandyInfo.special = CANDY_SPECIAL_BOMB;
			
		}
	else if(dispel->right - dispel->left  >=3  || dispel->down- dispel->up  >=3)
		{
			/*if(dispelNode->special == CANDY_SPECIAL_HORIZONTAL || dispelNode->special == CANDY_SPECIAL_VERTICAL )
				{
					newBornCandyInfo.special = rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL;
				}
			else */if(dispel->right - dispel->left  >=3)
				{
					newBornCandyInfo.special = CANDY_SPECIAL_VERTICAL;
				}
			else if(dispel->down- dispel->up  >=3)
				{
					newBornCandyInfo.special = CANDY_SPECIAL_HORIZONTAL;
				}
		}
	else
		{
			return;
		}

// 节点 为普通糖果时，新特殊糖果位置则在该位置生成
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(dispelNode->index, MAP_CELL_EXIST)
		&& dispelNode->special == CANDY_SPECIAL_NORMAL)
		{
			newBornCandyInfo.index = dispelNode->index;
			newBornCandyInfo.flag = true;
			return;
		}

//节点为特殊糖果，寻找其他位置生成新特殊糖果
	if( dispel->down- dispel->up  >=2 )
		{
			for(int y =dispel->up; y <= dispel->down; y++ )
				{
					CandyCell *dispelCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(dispel->index.x, y));
					if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(dispelCandy->index, MAP_CELL_EXIST)
						&& dispelCandy->special== CANDY_SPECIAL_NORMAL)
						{
							newBornCandyInfo.index = cIndex(dispel->index.x, y);
							newBornCandyInfo.flag = true;
							return;
						}
				}
		}

	if( dispel->right- dispel->left  >=2 )
		{
			for(int x =dispel->left; x <= dispel->right; x++ )
				{
					CandyCell *dispelCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, dispel->index.y));
					if( CandyManager::getInstance()->mapDataMgr->getMapCellStates(dispelCandy->index, MAP_CELL_EXIST)
						&& dispelCandy->special == CANDY_SPECIAL_NORMAL)
						{
							newBornCandyInfo.index = cIndex(x, dispel->index.y);
							newBornCandyInfo.flag = true;
							return;
						}
				}
		}
	
}

void CandyDispel::createNewBornSpecialCandy(NewBornCandy &newBornCandyInfo)
{
	if( !newBornCandyInfo.flag )
		return;

	if(CandyManager::getInstance()->mapDataMgr->getCandyByIndex(newBornCandyInfo.index))
		{
			CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(newBornCandyInfo.index);
			normalDispelCandy(candy);
			if(candy && candy->getCandyStates(CANDY_CELL_DELETING))
				{
					candy->destroyCandy();
				}
			else
				{
					return;
				}
		}

	CandyCell *newBornCandy = CandyCell::create(newBornCandyInfo.index, newBornCandyInfo.color, newBornCandyInfo.special);
	newBornCandy->displayNewSpecialEffect();
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(newBornCandy->index, newBornCandy);
	CandyManager::getInstance()->candyLayer->addToCandyParent(newBornCandy);
	addCandyToChangeArray(newBornCandy);
}
	

bool CandyDispel::isDispelContainsDispel(CandyDispelCell* dispel1, CandyDispelCell* dispel2)
{	
	bool ret = false;
	
	if(dispel1->index.y == dispel2->index.y)
		{
			if(dispel1->left <= dispel2->left && dispel1->right>= dispel2->right)
				ret = true;
			else 
				return false;
		}
	else if( dispel2->right- dispel2->left >= 2 )
		{
			return false;
		}
	
	if(dispel1->index.x == dispel2->index.x)
		{
			if(dispel1->up<= dispel2->up&& dispel1->down>= dispel2->down)
				ret = true;
			else 
				return false;
		}
	else if( dispel2->down - dispel2->up >= 2  )
		{
			return false;
		}
	
	return ret;
	
}

void CandyDispel::removeRedundantDispel(void)
{
	for(int i =0; i<(int)dispelArray->count(); i++)
	{
		CandyDispelCell* dispel1 =  (CandyDispelCell*)dispelArray->objectAtIndex(i);
		if(redundantArray->containsObject(dispel1))
			continue;
			
		for(int j =i+1; j<(int)dispelArray->count(); j++)
		{
			CandyDispelCell* dispel2 =  (CandyDispelCell*)dispelArray->objectAtIndex(j);
			if( isDispelContainsDispel(dispel1,  dispel2) )
			{
				if(!redundantArray->containsObject(dispel2))
					redundantArray->addObject(dispel2);
			}
			else if( isDispelContainsDispel(dispel2, dispel1 ) )
			{
				if(!redundantArray->containsObject(dispel1))
					redundantArray->addObject(dispel1);
				break;
			}
		}
	}
	
	for(int i =0; i<(int)redundantArray->count(); i++)
	{
		CandyDispelCell* redundantDispel =  (CandyDispelCell*)redundantArray->objectAtIndex(i);
		dispelArray->removeObject(redundantDispel);
	}

	redundantArray->removeAllObjects();
}

bool CandyDispel::checkCandyColorByIndex(CandyIndex index, CandyColor color)
{
	CandyCell* cell = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index) ;
	if(cell  && cell->getCandyStates(CANDY_CELL_NORMAL) && cell->color == color && cell->special != CANDY_SPECIAL_BOMBING)
		return true;
	return false;
}


//返回所得 分数
int CandyDispel::specialDispelSingleCandy(CandyIndex index,bool displayScore)
{
	int getScore = 0;


	/*消除雪糕*/
	if(CandyManager::getInstance()->creamMgr->removeCandyCreamCell(index))
		return 0;

	if(CandyManager::getInstance()->chocolateMgr->removeCandyChocolateCell(index))
		return 0;

	if(CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(index)) /*消除果冻*/
		getScore += CANDY_SCORE_JELLY;
	
	/*消除糖果*/
	CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);

	if(deleteCandy && deleteCandy->special == CANDY_SPECIAL_INGREDIENT)
		return 0;
	
	if(deleteCandy && deleteCandy->special != CANDY_SPECIAL_BOMBING && dispelSingleCandy(deleteCandy))
		{
			if(deleteCandy->special == CANDY_SPECIAL_EXPLOSION)
				getScore += CANDY_SCORE_EXPLOSION;
			else
				getScore += CANDY_SCORE_SINGLE_DISPEL;
		}
	
	if(displayScore && getScore)
		{
			CandyColor color=deleteCandy?deleteCandy->color:CANDY_COLOR_BLUE;
			CandyManager::getInstance()->scoreMgr->addCandyScore(getScore, 
					CandyManager::getInstance()->shareMgr->getPosByIndex(index), color);
		}
	return getScore;
}

bool CandyDispel::getDispelStateByChangeCandy(CandyIndex index1 ,CandyIndex index2)
{
	CandyCell *candy1 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index1);
	CandyCell *candy2 = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index2);

	if(!candy1 || !candy2)
		return false;
	
	//交换
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index1,  candy2, false);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index2,  candy1, false);

	CandyDispelCell* dispel1 = CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy1);
	CandyDispelCell* dispel2 = CandyManager::getInstance()->dispelMgr->checkCandyDispel(candy2);
	

	//回归
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index1,  candy1, false);
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index2,  candy2, false);

	
	return dispel1 || dispel2  ;
}


int CandyDispel::specialDispelCandyByProp(CandyIndex index,bool displayScore)
{
	int getScore = 0;

	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_LOCK))
	{
		CandyManager::getInstance()->lockMgr->removeCandyLockCell(index);
	}

	CandyManager::getInstance()->licoricesMgr->removeLicorice(index);

	/*消除雪糕*/
	if(CandyManager::getInstance()->creamMgr->removeCandyCreamCell(index))
		return 0;

	if(CandyManager::getInstance()->chocolateMgr->removeCandyChocolateCell(index))
		return 0;

	if(CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(index)) /*消除果冻*/
		getScore += CANDY_SCORE_JELLY;

	/*消除糖果*/
	CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);

	if(deleteCandy && deleteCandy->special == CANDY_SPECIAL_INGREDIENT)
		return 0;

	if(deleteCandy && deleteCandy->special != CANDY_SPECIAL_BOMBING && dispelSingleCandy(deleteCandy))
	{
		if(deleteCandy->special == CANDY_SPECIAL_EXPLOSION)
			getScore += CANDY_SCORE_EXPLOSION;
		else
			getScore += CANDY_SCORE_SINGLE_DISPEL;
	}

	if(displayScore && getScore)
	{
		CandyColor color=deleteCandy?deleteCandy->color:CANDY_COLOR_BLUE;
		CandyManager::getInstance()->scoreMgr->addCandyScore(getScore, 
			CandyManager::getInstance()->shareMgr->getPosByIndex(index), color);
	}
	return getScore;
}
