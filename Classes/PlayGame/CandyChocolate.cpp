#include "CandyChocolate.h"
#include "CandyManager.h"

#define CANDY_CHOCOLATE_IMG	"chocolate"
#define CANDY_CHOCOLATE_NUM	7

CandyChocolateCell* CandyChocolateCell::create(CandyIndex index, bool runAction)
{
	CandyChocolateCell *ret = new CandyChocolateCell();
	int imgNum = runAction?1:CANDY_CHOCOLATE_NUM;
	if(ret && ret->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					CCString::createWithFormat("%s%d.png",CANDY_CHOCOLATE_IMG,imgNum)->getCString())))
		{
			ret->autorelease();
			ret->index= index;
			if(runAction)
				ret->runBornAction();
			return ret;
		}
	
	CCAssert(0, "CandyCreamCell::create");
	CC_SAFE_DELETE(ret);
	return NULL;
}

void CandyChocolateCell::runBornAction(void)
{
	CCArray *animFramesArray = CCArray::create();
	for(int i =0; i<CANDY_CHOCOLATE_NUM; i++)
		{
			CCSpriteFrame *frame =CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
				CCString::createWithFormat("%s%d.png",CANDY_CHOCOLATE_IMG,i+1)->getCString());
			animFramesArray->addObject(frame);
		}
	runAction(CCAnimate::create(CCAnimation::createWithSpriteFrames(animFramesArray , 0.08f)));
}
	
CandyChocolate::CandyChocolate():dispelChocolate(true)
{
	memset(&chocolateInMap[0][0], 0, sizeof(CandyChocolateCell*) * CANDY_MAP_WIDTH * CANDY_MAP_HEIGH);
}

CandyChocolate::~CandyChocolate()
{
	
}

void CandyChocolate::createChocolatesWithMapData(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
			{
				if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CHOCOLATA))
					{
						addCandyChocolateCell(cIndex(x, y));
					}
			}
}

void CandyChocolate::addCandyChocolateCell(CandyIndex index,bool runAction)
{
	CandyChocolateCell* chocolate = CandyChocolateCell::create( index,runAction);
	if(chocolate)
		{
			chocolate->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(index));
			CandyManager::getInstance()->candyLayer->addToCandyBarrierTopBatchNode(chocolate);
			chocolateInMap[index.y][index.x] = chocolate;
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CHOCOLATA, true);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_BARRIER, true);
		}
}


void CandyChocolate::updateCandyChocolate(void)
{
	if( !CandyManager::getInstance()->shareMgr->getCandyIdle())	
		return;

	if(!dispelChocolate)
		{
			swallowCandy();
			dispelChocolate = true;
		}

}

				
bool CandyChocolate::checkSwallowCandy(CandyIndex index)
{
	if(!CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CANDY)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_LOCK))
		return false;
	
	CandyCell *candy = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
	if(!candy)
		{
			return false;
		}
	else  if(candy->special == CANDY_SPECIAL_INGREDIENT || candy->special == CANDY_SPECIAL_LICORICE)//²»ÍÌ²¢°åÀõÓ£ÌÒ¸Ê²Ý
		{
			return false;
		}
	else
		{
			candy->destroyCandy();
		}
	
	CandyManager::getInstance()->mapDataMgr->setCandyByIndex(index, NULL);
	addCandyChocolateCell(index,true);
	return true;
			
}

void CandyChocolate::swallowCandy(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
			{
				if(chocolateInMap[y][x])
					{
						if(checkSwallowCandy(cIndex(x, y+1))
							|| checkSwallowCandy(cIndex(x, y-1))
							|| checkSwallowCandy(cIndex(x+1, y))
							|| checkSwallowCandy(cIndex(x-1, y)))
							return;
					}
			}
			

}

bool CandyChocolate::removeCandyChocolateCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CHOCOLATA))
		{
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CHOCOLATA, false);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_BARRIER, false);
			if(chocolateInMap[index.y][index.x])
				{
					chocolateInMap[index.y][index.x]->removeFromParent();
					chocolateInMap[index.y][index.x] = NULL;
					CandyManager::getInstance()->effectLayer->displayBreakChocolate(index);
					//CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_CHOCOLATE,  CandyManager::getInstance()->shareMgr->getPosByIndex(index));	
				}
		}
	else
		{
			return false;
		}
	
	dispelChocolate = true;
	return true;
}

void CandyChocolate::dispelCandyEffectChocolate(CandyIndex dispelIndex)
{
	removeCandyChocolateCell(cIndex(dispelIndex.x+1, dispelIndex.y));
	removeCandyChocolateCell(cIndex(dispelIndex.x-1, dispelIndex.y));
	removeCandyChocolateCell(cIndex(dispelIndex.x, dispelIndex.y+1));
	removeCandyChocolateCell(cIndex(dispelIndex.x, dispelIndex.y-1));
}

void CandyChocolate::resetDispelChocolateFlag(void)
{
	dispelChocolate = false;
}


CandyChocolateCell* CandyChocolate::getCandyChocolateCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CHOCOLATA))
		return chocolateInMap[index.y][index.x];
	else
		return NULL;

}