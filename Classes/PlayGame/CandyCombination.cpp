#include "CandyCombination.h"
#include "CandyManager.h"

// 组合消除
CandyCombination::CandyCombination()
{
	combinationArray = new CCArray();
}

CandyCombination::~CandyCombination()
{
	CC_SAFE_DELETE(combinationArray);
}

bool CandyCombination::activedCombinationContainsCandy(CandyCell *candy)
{
	return combinationArray->containsObject(candy);
}

void CandyCombination::addActivedCombination(CandyCell *candy)
{
	if(!activedCombinationContainsCandy(candy))
		combinationArray->addObject(candy);
}

void CandyCombination::removeActivedCombination(CandyCell *candy)
{
	combinationArray->removeObject(candy);
}


bool CandyCombination::getCombinationActionDone(void)
{
	return combinationArray->count()>0?false:true;
}

void CandyCombination::updateCandyCombination(void)
{
	static int timeDelayCount = 0;
	
	if(getCombinationActionDone())
		return;
					
	switch(combinationType)
		{
			case CANDY_COM_COLORFULL_COLORFULL:
				break;

			case CANDY_COM_COLORFULL_NORMAL:
				break;

			case CANDY_COM_COLORFULL_STRIPE:
				{
					if(timeDelayCount++ % 15 !=0)
						return;

					//timeDelayCount = 0;

					CandyCell *candy = NULL;
					while(combinationArray->count())
					{
						candy = (CandyCell *)combinationArray->objectAtIndex(0);
						combinationArray->removeObject(candy);

						if(CandyManager::getInstance()->shareMgr->getLayerIncludeCandy(candy))
							break;
						else
							candy = NULL;
					}
					if(candy)
					{
						candy->runCandyDeleteAction();
						CandyManager::getInstance()->specialMgr->runSpecialCandy(candy);
						//CandyManager::getInstance()->scoreMgr->increaseComboNumber();
					}

				}
				break;

			case CANDY_COM_COLORFULL_BOMB:
					{
						if(timeDelayCount++  <5)
							return;

						timeDelayCount = 0;
						
						if(!CandyManager::getInstance()->shareMgr->getAllCandyStopAction(false))
							return;

						CandyCell *bombColorFulCandy = (CandyCell *)combinationArray->objectAtIndex(0);
						combinationArray->removeAllObjects();
						if(bombColorFulCandy)
							{
								CandyManager::getInstance()->specialMgr->runSpecialCandy(bombColorFulCandy);
							}
						//CandyManager::getInstance()->scoreMgr->increaseComboNumber();
					}
				break;

			case CANDY_COM_STRIPE_STRIPE:
				break;

			case CANDY_COM_STRIPE_BOMB:
				break;

			case CANDY_COM_BOMB_BOMB:
				break;

		}
}


bool CandyCombination::checkCandyCombination(CandyCell *candy1, CandyCell *candy2)
{
	if(!candy1 || !candy2)
		return false;

	targetIndex = candy2->index;
	return isSpecialCombination(candy1, candy2) || isSpecialCombination(candy2, candy1);
}

bool CandyCombination::isSpecialCombination(CandyCell *candy1, CandyCell *candy2)
{
	if(!candy1 || !candy2)
		return false;
	
	if( candy1->special == CANDY_SPECIAL_COLORFULL &&  candy2->special == CANDY_SPECIAL_COLORFULL)
		{
			combinationType = CANDY_COM_COLORFULL_COLORFULL;
			return true;
		}
	else if( (candy1->special == CANDY_SPECIAL_COLORFULL && candy2->special ==   CANDY_SPECIAL_NORMAL )
		|| (candy1->special == CANDY_SPECIAL_COLORFULL && candy2->special ==   CANDY_SPECIAL_EXPLOSION))
		{
			combinationType = CANDY_COM_COLORFULL_NORMAL;
			return true;
		}
	else if( candy1->special == CANDY_SPECIAL_COLORFULL
			&&  (candy2->special == CANDY_SPECIAL_HORIZONTAL || candy2->special == CANDY_SPECIAL_VERTICAL) )
		{
			combinationType = CANDY_COM_COLORFULL_STRIPE;
			return true;
		}
	else if( candy1->special == CANDY_SPECIAL_COLORFULL &&  candy2->special == CANDY_SPECIAL_BOMB)
		{
			combinationType = CANDY_COM_COLORFULL_BOMB;
			return true;
		}
	
	else if( (candy1->special == CANDY_SPECIAL_HORIZONTAL || candy1->special == CANDY_SPECIAL_VERTICAL) 
			&& (candy2->special == CANDY_SPECIAL_HORIZONTAL || candy2->special == CANDY_SPECIAL_VERTICAL) )
		{	
			combinationType = CANDY_COM_STRIPE_STRIPE;
			return true;
		}
	else if( (candy1->special == CANDY_SPECIAL_HORIZONTAL || candy1->special == CANDY_SPECIAL_VERTICAL) 
		 	&& candy2->special == CANDY_SPECIAL_BOMB )
		{
			combinationType = CANDY_COM_STRIPE_BOMB;
			return true;
		}
	else if( candy1->special == CANDY_SPECIAL_BOMB && candy2->special == CANDY_SPECIAL_BOMB )
		{
			combinationType = CANDY_COM_BOMB_BOMB;
			return true;
		}
	
	return false;
}



void CandyCombination::runCandyCombination(CandyCell *candy1, CandyCell *candy2)
{
	int energyNum =20;
	
	comCandy1 = candy1;
	comCandy2 = candy2;
	
	CandyManager::getInstance()->shareMgr->collectCandy(NULL,combinationType);	
	
	switch(combinationType)
		{
			case CANDY_COM_COLORFULL_COLORFULL:
					{
						candy1->setCandyStates(CANDY_CELL_EFFECTING, true);	
						CandyManager::getInstance()->scoreMgr->setAccumulateScoreFlag(true);
						CandyManager::getInstance()->effectLayer->displayComCCEffect(
							CCCallFuncN::create(NULL, callfuncN_selector(CandyCombination::comCCEffectCB)));
					}
					break;

			case CANDY_COM_COLORFULL_NORMAL:
					{
						energyNum = 10;
						CandyCell *colorfulCandy = candy1->special==CANDY_SPECIAL_COLORFULL?candy1:candy2;
						CandyCell *normalCandy = candy1->special==CANDY_SPECIAL_COLORFULL?candy2:candy1;
						CandyColor dispelColor = normalCandy->color;
						runComCNEffect(colorfulCandy, dispelColor);
					}
					break;
				
			case CANDY_COM_COLORFULL_STRIPE:
					{
						runCombinationCS(candy1, candy2);
					}
					break;

			case CANDY_COM_COLORFULL_BOMB:
					{
						runCombinationCB(candy1, candy2);
					}	
					break;

			case CANDY_COM_STRIPE_STRIPE:
					{
						runCombinationSS(candy1, candy2);
					}
					break;

			
			case CANDY_COM_STRIPE_BOMB:
					{
						comCandy2->setCandyStates(CANDY_CELL_EFFECTING, true);	
						CandyManager::getInstance()->effectLayer->displayComBSEffect1(comCandy2->index, 
							CCCallFuncN::create(NULL, callfuncN_selector(CandyCombination::comSBEffectCB)));
					}
					break;

			case CANDY_COM_BOMB_BOMB:
					{
						comCandy2->setCandyStates(CANDY_CELL_EFFECTING, true);	
						CandyManager::getInstance()->effectLayer->displayComBBEffect(comCandy2->index, 
							CCCallFuncN::create(NULL, callfuncN_selector(CandyCombination::comBBEffectCB)));
					}
					break;
		}

	CandyManager::getInstance()->uiLayer->increaseEnergyJarPercentage(energyNum);
}

void CandyCombination::comCNEffectCB(CCNode* sender, void* data)
{
	CandyManager::getInstance()->combinationMgr->runCombinationCN((CandyCell*)data);
}

void CandyCombination::comBBEffectCB(CCNode* sender)
{
	CandyManager::getInstance()->combinationMgr->comCandy2->setCandyStates(CANDY_CELL_EFFECTING, false);
	CandyManager::getInstance()->combinationMgr->runCombinationBB(CandyManager::getInstance()->combinationMgr->comCandy1, 
					CandyManager::getInstance()->combinationMgr->comCandy2);
}

void CandyCombination::comSBEffectCB(CCNode* sender)
{
	CandyManager::getInstance()->combinationMgr->comCandy2->setCandyStates(CANDY_CELL_EFFECTING, false);
	
	//CandyManager::getInstance()->effectLayer->displayBombDispelEffect(CandyManager::getInstance()->combinationMgr->comCandy2->index);
	CandyManager::getInstance()->combinationMgr->runCombinationSB(CandyManager::getInstance()->combinationMgr->comCandy1, 
					CandyManager::getInstance()->combinationMgr->comCandy2);
}

void CandyCombination::comCCEffectCB(CCNode* sender)
{
	CandyManager::getInstance()->combinationMgr->runCombinationCC(CandyManager::getInstance()->combinationMgr->comCandy1, 
					CandyManager::getInstance()->combinationMgr->comCandy2);
}


void CandyCombination::runCombinationCC(CandyCell *candy1, CandyCell *candy2)
{
	candy1->runCandyDeleteAction();
	candy2->runCandyDeleteAction();
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(candy1->index);
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(candy2->index);
		
	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			{
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y ));
				if(deleteCandy && deleteCandy->special != CANDY_SPECIAL_LICORICE)
					{
						CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(cIndex(x, y ),true);
					}
			}
		
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_COLOR);
	CandyManager::getInstance()->scoreMgr->setAccumulateScoreFlag(false, true);
}

void CandyCombination::runCombinationCS(CandyCell *candy1, CandyCell *candy2)
{
	CandyCell *stripeCandy = candy1->special==CANDY_SPECIAL_COLORFULL?candy2:candy1;
	CandyCell *colorCandy = candy1->special==CANDY_SPECIAL_COLORFULL?candy1:candy2;
	CandyColor dispelColor = stripeCandy->color;
						
	colorCandy->runCandyDeleteAction();
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(colorCandy->index);
	
	addActivedCombination(stripeCandy);
	
	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			{
				
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y ));
				if(deleteCandy && deleteCandy->color == dispelColor && deleteCandy->getCandyStates(CANDY_CELL_NORMAL))
					{
						//解锁
						if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(deleteCandy->index, MAP_CELL_LOCK))
							CandyManager::getInstance()->lockMgr->removeCandyLockCell(deleteCandy->index);
						
						CandyCell *newBornCandy = deleteCandy->changeCandySpecial(rand()%2?CANDY_SPECIAL_HORIZONTAL:CANDY_SPECIAL_VERTICAL,false);
						addActivedCombination(newBornCandy);
					}
			}

	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
	
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_STRIPE);
}

void CandyCombination::runCombinationCB(CandyCell *candy1, CandyCell *candy2)
{
	CandyCell *bombCandy = candy1->special == CANDY_SPECIAL_BOMB?candy1:candy2;
	CandyCell *colorCandy = candy1->special == CANDY_SPECIAL_COLORFULL?candy1:candy2;

	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(bombCandy->index);
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(colorCandy->index);
	
	CCSequence *action = CCSequence::create(CCScaleTo::create(0.3f, 1.3f),
									CCScaleTo::create(0.3f, 1.0f),
									NULL);
	colorCandy->runAction(CCRepeatForever::create(action));
	addActivedCombination(colorCandy);
#if 1
	runComCNEffect(bombCandy, bombCandy->color);
#else	
	bombCandy->runCandyDeleteAction();

	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			{
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y ));
				if(deleteCandy && deleteCandy->color == bombCandy->color)
					{
						CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(cIndex(x, y ),true);
					}
			}
#endif
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
	
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_BOMB);
}

void CandyCombination::runCombinationSS(CandyCell *candy1, CandyCell *candy2)
{
	candy1->runCandyDeleteAction();
	candy2->runCandyDeleteAction();
	
	CandyCell *targetCandy;
	if(candy1->index.x == targetIndex.x && candy1->index.y == targetIndex.y)
		targetCandy = candy1;
	else
		targetCandy = candy2;
	
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(targetIndex);
	CandyManager::getInstance()->specialMgr->runSpecialHorizontal(targetCandy->index, targetCandy->color,false);
	CandyManager::getInstance()->specialMgr->runSpecialVertical(targetCandy->index, targetCandy->color, false);
	CandyManager::getInstance()->effectLayer->displayComSSEffect(targetIndex,candy1->color, candy2->color );
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
}

void CandyCombination::runCombinationSB(CandyCell *candy1, CandyCell *candy2)
{
	const float delay = 0.15f;
	candy1->runCandyDeleteAction();
	candy2->runCandyDeleteAction();


	for(int i=-1;i<=1;i++)
		{
			for(int x=targetIndex.x; x>=0; x--)
				{
					if(CandyManager::getInstance()->specialMgr->stripeDispelCandyDelay(
							cIndex(x, targetIndex.y+i), (targetIndex.x - x)*delay))
						break;
				}

			for(int x=targetIndex.x; x<CANDY_MAP_WIDTH; x++)
				{
					if(CandyManager::getInstance()->specialMgr->stripeDispelCandyDelay(
							cIndex(x, targetIndex.y+i), (x -targetIndex.x)*delay))
						break;
				}
			
			for(int y=targetIndex.y; y>=0; y--)
				{
					if(CandyManager::getInstance()->specialMgr->stripeDispelCandyDelay(
							cIndex(targetIndex.x+i, y), (targetIndex.y - y)*delay))
						break;
				}

			for(int y=targetIndex.y; y<CANDY_MAP_HEIGH; y++)
				{
					if(CandyManager::getInstance()->specialMgr->stripeDispelCandyDelay(
							cIndex(targetIndex.x+i, y), (y - targetIndex.y)*delay))
						break;
				}
		}

	
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
	
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_BOMB_STRIPE);
}

void CandyCombination::runCombinationBB(CandyCell *candy1, CandyCell *candy2)
{
	int getScore = 0;
	for(int y=-2; y<=2; y++)
		for(int x=-2; x<=2; x++)
			{
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(targetIndex.x+x, targetIndex.y+y));
				
				if(deleteCandy == candy1 || deleteCandy == candy2)
					{
						CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(deleteCandy->index);
						CandyCell *newBornCandy = deleteCandy->changeCandySpecial( CANDY_SPECIAL_BOMBING,false);
						CandyManager::getInstance()->specialMgr->addActivedSpecial(newBornCandy);
					}
				else 
					{
						getScore = getScore + CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(cIndex(targetIndex.x+x, targetIndex.y+y));
					}
			}
	CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_BOMB + getScore, 
									CandyManager::getInstance()->shareMgr->getPosByIndex(candy1->index), candy1->color);	
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();

	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_BOMB_BOMB);
}

void CandyCombination::runCombinationCN(CandyCell *colorfulCandy)
{
	CandyColor dispelColor = colorfulCandy->extraColor;

	colorfulCandy->setCandyStates(CANDY_CELL_EFFECTING, false);
	colorfulCandy->runCandyDeleteAction();
	CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(colorfulCandy->index);
	
	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			{
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y ));
				if(deleteCandy && deleteCandy->color == dispelColor)
					{
						 CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(cIndex(x, y ),true);
					}
			}
		
	CandyManager::getInstance()->scoreMgr->increaseComboNumber();
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_COM_COLOR_NORMAL);
}

void CandyCombination::runComCNEffect(CandyCell *colorfulCandy, CandyColor dispelColor)
{
	colorfulCandy->extraColor = dispelColor;
	
	colorfulCandy->setCandyStates(CANDY_CELL_EFFECTING, true);	
	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			{
				CandyCell *deleteCandy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y ));
				if(deleteCandy && deleteCandy->color == dispelColor)
					{
						CandyManager::getInstance()->effectLayer->displayColorFire(colorfulCandy->index, deleteCandy->index, 0.3f);
						CandyManager::getInstance()->effectLayer->displayColorTarget(deleteCandy->index, 0.6f);
					}
					
			}
	CandyManager::getInstance()->effectLayer->displayColorEmit(colorfulCandy->index);
	CandyManager::getInstance()->effectLayer->delayCallBack(0.9f, 
											CCCallFuncND::create(NULL, callfuncND_selector(CandyCombination::comCNEffectCB), (void*)colorfulCandy));
	
	
}