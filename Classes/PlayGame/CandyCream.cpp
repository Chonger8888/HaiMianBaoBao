#include "CandyCream.h"
#include "CandyManager.h"

USING_NS_CC;

#define CANDY_CREAM1_IMG		"cream1.png"
#define CANDY_CREAM2_IMG		"cream2.png"
#define CANDY_CREAM3_IMG		"cream3.png"
#define CANDY_CREAM4_IMG		"cream4.png"
#define CANDY_CREAM5_IMG		"cream5.png"

CandyCreamCell* CandyCreamCell::create(CandyIndex index, int layerNum)
{
	CandyCreamCell *ret = new CandyCreamCell();
	char *imgName = getCreamImgName(layerNum);
	if(ret && ret->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imgName)) )
		{
			ret->autorelease();
			ret->index= index;
			ret->layerNum = layerNum;
			return ret;
		}
	
	CCAssert(0, "CandyCreamCell::create");
	CC_SAFE_DELETE(ret);
	return NULL;
}

char *CandyCreamCell::getCreamImgName(int layerNum)
{
	switch(layerNum)
		{
			case 1:
				return (char *)CANDY_CREAM1_IMG;

			case 2:
				return (char *)CANDY_CREAM2_IMG;

			case 3:
				return (char *)CANDY_CREAM3_IMG;

			case 4:
				return (char *)CANDY_CREAM4_IMG;

			case 5:
				return (char *)CANDY_CREAM5_IMG;
		}
	
	return (char *)CANDY_CREAM5_IMG;
}




CandyCream::CandyCream()
{
	memset(&creamInMap[0][0], 0, sizeof(CandyCreamCell*) * CANDY_MAP_WIDTH * CANDY_MAP_HEIGH);
}

CandyCream::~CandyCream()
{
	
}

void CandyCream::createCreamsWithMapData(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
		{
			if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CREAM1))
			{
				addCandyCreamCell(cIndex(x, y), 1);
			}
			else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CREAM2))
			{
				addCandyCreamCell(cIndex(x, y), 2);
			}
			else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_CREAM3))
			{
				addCandyCreamCell(cIndex(x, y), 3);
			}
		}
}

void CandyCream::addCandyCreamCell(CandyIndex index, int layerNum)
{
	CandyCreamCell* cream = CandyCreamCell::create( index,  layerNum);
	if(cream)
		{
			cream->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(index));
			CandyManager::getInstance()->candyLayer->addToCandyBarrierBottomBatchNode(cream);
			creamInMap[index.y][index.x] = cream;
		}
}

bool CandyCream::removeCandyCreamCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM1))
		{
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CREAM1, false);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_BARRIER, false);
			if(creamInMap[index.y][index.x])
				{
					creamInMap[index.y][index.x]->removeFromParent();
					creamInMap[index.y][index.x] = NULL;
					CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_CREAM1,  CandyManager::getInstance()->shareMgr->getPosByIndex(index));	
				}
		}
	else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM2))
		{
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CREAM2, false);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CREAM1, true);
			if(creamInMap[index.y][index.x])
				{
					creamInMap[index.y][index.x]->removeFromParent();
					CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_CREAM2,  CandyManager::getInstance()->shareMgr->getPosByIndex(index));	
				}
			addCandyCreamCell(index , 1);
		}
	else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM3))
		{
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CREAM3, false);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_CREAM2, true);
			if(creamInMap[index.y][index.x])
				{
					creamInMap[index.y][index.x]->removeFromParent();
					CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_CREAM3,  CandyManager::getInstance()->shareMgr->getPosByIndex(index));	
				}
			addCandyCreamCell(index , 2);
		}
	else
		{
			return false;
		}
	CandyManager::getInstance()->effectLayer->displayBreakCream(index);
	return true;
}

CandyCreamCell* CandyCream::getCandyCreamCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM1)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM2)
		|| CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_CREAM3))
		return creamInMap[index.y][index.x];
	else
		return NULL;
}


void CandyCream::dispelCandyEffectCream(CandyIndex dispelIndex)
{
	removeCandyCreamCell(cIndex(dispelIndex.x+1, dispelIndex.y));
	removeCandyCreamCell(cIndex(dispelIndex.x-1, dispelIndex.y));
	removeCandyCreamCell(cIndex(dispelIndex.x, dispelIndex.y+1));
	removeCandyCreamCell(cIndex(dispelIndex.x, dispelIndex.y-1));
}
