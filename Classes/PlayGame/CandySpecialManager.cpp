#include "CandySpecialManager.h"
#include "CandyManager.h"

USING_NS_CC;

#define SPECIAL_HOR_VER_DELAY			0.07f

CandySpecialManager::CandySpecialManager()
{
	displayEffectTime = 0;
	activedSpecialArray= new CCArray();
}

CandySpecialManager::~CandySpecialManager()
{
	CC_SAFE_DELETE(activedSpecialArray);
}

void CandySpecialManager::updateActivedSpecial(float time)
{
	if(displayingEffect(time))
		return;
	
	static int timeCount = 0;
	if(CandyManager::getInstance()->shareMgr->getAllCandyStopAction())
		{
			if(++timeCount %3)
				return;
		}
	else
		{
			timeCount = 0;
			return ;
		}
		
	bool exsitBombingCandy = false;
	int totalNum = activedSpecialArray->count();
	
	for(int i=0; i < totalNum; )
		{
			CandyCell* specialCandy  = (CandyCell*)activedSpecialArray->objectAtIndex(i);
			if(specialCandy->special == CANDY_SPECIAL_BOMBING)
				{
					totalNum--;
					exsitBombingCandy = true;
					runSpecialCandy(specialCandy);
					removeActivedSpecial(specialCandy);
				}
			
			else
				{
					i++;
				}
		}
	
	if(exsitBombingCandy)
		return;

	for(unsigned int i=0; i < activedSpecialArray->count(); )
	{
		CandyCell* specialCandy  = (CandyCell*)activedSpecialArray->objectAtIndex(i);

		if(specialCandy->special == CANDY_SPECIAL_BOMBING)
		{
			i++;
		}
		else
		{
			runSpecialCandy(specialCandy,true);
			removeActivedSpecial(specialCandy);
			if(specialCandy->special == CANDY_SPECIAL_COLORFULL) //彩球会在runSpecialCandy释放，一次释放一个
				return;
			else
				specialCandy->runCandyDeleteAction();
		}
	}
}

bool CandySpecialManager::activedSpecialContainsCandy(CandyCell *candy)
{
	return activedSpecialArray->containsObject(candy);
}

void CandySpecialManager::addActivedSpecial(CandyCell *candy)
{
	if(!activedSpecialContainsCandy(candy))
		activedSpecialArray->addObject(candy);
}

void CandySpecialManager::removeActivedSpecial(CandyCell *candy)
{
	activedSpecialArray->removeObject(candy);
}

//激活地图特殊糖果
bool CandySpecialManager:: activeSpecialCandyInMap(int num)
{
	if(activedSpecialArray->count())
		return true;

	static int timeCount = 0;
	if(CandyManager::getInstance()->shareMgr->getCandyIdle() )
		{
			if( ++timeCount%3 )
				return true;
		}
	else
		{
			timeCount = 0;
			return true;
		}
	
	int count = 0;		
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=0; y<CANDY_MAP_HEIGH; y++)
			{
				if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CANDY))
					continue;

				CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(cIndex(x, y));
				if(candy && candy->special>CANDY_SPECIAL_NORMAL && candy->special <=CANDY_SPECIAL_COLORFULL)
					{
						if(candy->special != CANDY_SPECIAL_COLORFULL) //彩球会在runSpecialCandy释放
							candy->runCandyDeleteAction();
						CandyManager::getInstance()->specialMgr->runSpecialCandy(candy,true);
						if(++count >=  num)
							return true;
					}
			}
	return count>0;
}

bool CandySpecialManager::runSpecialCandy(CandyCell *candy,bool increaesEnergy)
{
	int energyNum = 0;
	switch(candy->special)
		{
			case CANDY_SPECIAL_NORMAL:
				break;

			case CANDY_SPECIAL_HORIZONTAL:
					{
						runSpecialHorizontal(candy->index,candy->color);
						energyNum = 8;
					}
				break;

			case CANDY_SPECIAL_VERTICAL:
					{
						runSpecialVertical(candy->index,candy->color);
						energyNum = 8;
					}
				break;

			case CANDY_SPECIAL_BOMB:
					{
						runSpecialBomb(candy->index, candy->color, true);
						CandyCell *newBornCandy = CandyCell::create(candy->index, candy->color, CANDY_SPECIAL_BOMBING);
						CandyManager::getInstance()->mapDataMgr->setCandyByIndex(newBornCandy->index, newBornCandy);
						CandyManager::getInstance()->candyLayer->addToCandyParent(newBornCandy);
						addActivedSpecial(newBornCandy);
						energyNum = 10;
					}
				break;

			case CANDY_SPECIAL_BOMBING:
					{
						int externScore = 0;	
						if(CandyManager::getInstance()->jellyMgr->removeCandyJellyOne(candy->index))
							externScore  += CANDY_SCORE_JELLY;
						candy->runCandyDeleteAction();
						runSpecialBomb(candy->index, candy->color, true, externScore);

					}
				break;

			case CANDY_SPECIAL_COLORFULL:
					{
						CandyManager::getInstance()->combinationMgr->runComCNEffect(candy, candy->extraColor);
						energyNum = 10;
					}
				break;
		}

		if(increaesEnergy)
			CandyManager::getInstance()->uiLayer->increaseEnergyJarPercentage(energyNum );
		
		return true;
}

void CandySpecialManager::runSpecialBomb(CandyIndex index, CandyColor color, bool skipCenter,  int externScore)
{
	int getScore = CANDY_SCORE_BOMB +  externScore;
						
	for(int y=-1; y<=1; y++)
		for(int x=-1; x<=1; x++)
			{
				if(x==0 && y ==0)
					if(skipCenter)
						continue;
				getScore  += CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(cIndex(index.x +x, index.y +y ));
			}
	
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_DISPEL_BOMB);
	CandyManager::getInstance()->effectLayer->displayBombDispelEffect(index);
	CandyManager::getInstance()->scoreMgr->addCandyScore(getScore,  CandyManager::getInstance()->shareMgr->getPosByIndex(index), color);
}

void CandySpecialManager::runSpecialHorizontal(CandyIndex index,CandyColor color, bool display)
{
	for(int x=index.x - 1; x >= 0; x--)
		{
			if(stripeDispelCandyDelay(cIndex(x,  index.y), 
							SPECIAL_HOR_VER_DELAY * ( index.x - x)))
				break;
			
		}
	for(int x=index.x + 1; x < CANDY_MAP_WIDTH; x++)
		{
			if(stripeDispelCandyDelay(cIndex(x,  index.y), 
							SPECIAL_HOR_VER_DELAY * (x - index.x)))
				break;
		}
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_DISPEL_STRIPE);
	if(display)
		CandyManager::getInstance()->effectLayer->displayHorizonDispelEffect(index, color);
}

void CandySpecialManager::runSpecialVertical(CandyIndex index,CandyColor color, bool display)
{
	for(int y=index.y - 1; y >= 0; y--)
		{
			if(stripeDispelCandyDelay(cIndex(index.x,  y), 
							SPECIAL_HOR_VER_DELAY * (index.y - y)))
				break;
		}
	for(int y= index.y + 1; y < CANDY_MAP_WIDTH; y++)
		{
			if(stripeDispelCandyDelay(cIndex(index.x,  y), 
							SPECIAL_HOR_VER_DELAY * (y - index.y)))
				break;
		}
	
	CandyManager::getInstance()->musicMgr->playMusic(CANDY_EFFECT_DISPEL_STRIPE);
	if(display)
		CandyManager::getInstance()->effectLayer->displayVerticalDispelEffect(index, color);
}

//条纹延迟消失
bool CandySpecialManager::stripeDispelCandyDelay(CandyIndex index, float delay)
{
	CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
	if(candy && !candy->getCandyStates(CANDY_CELL_DELAY_DELETING) && !candy->getCandyStates(CANDY_CELL_DELETING))
		{
			candy->runCandyDelayDelete(delay,1);
			if(candy->special == CANDY_SPECIAL_LICORICE)
				return true;//stop
		}
	else
		{
			int indexNum = (index.x &0xffff)|(index.y<<16);
			CandyManager::getInstance()->candyLayer->runAction(CCSequence::create(
										CCDelayTime::create(delay),
									       CCCallFuncND::create(NULL, callfuncND_selector(CandySpecialManager::stripeDispelEmptyCallBack), (void*)indexNum),
									       NULL));
		}
	return false;
}

void CandySpecialManager::stripeDispelEmptyCallBack(CCNode* sender, void* data)
{
	CandyIndex index;
	index.x = (int)data &0xffff;
	index.y = (int)data >>16;

	CandyManager::getInstance()->dispelMgr->specialDispelSingleCandy(index, true);
}

void CandySpecialManager::setDisplayEffectTime(float time)
{
	if(displayEffectTime < time)
		displayEffectTime = time;
}

bool CandySpecialManager::displayingEffect(float time)
{
	displayEffectTime = displayEffectTime - time;
	if(displayEffectTime < 0)
		displayEffectTime = 0;
	return displayEffectTime>0;
}
