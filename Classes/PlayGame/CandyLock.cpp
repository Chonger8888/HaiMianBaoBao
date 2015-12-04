#include "CandyLock.h"
#include "CandyManager.h"

// lock ÕÏ°­Îï
USING_NS_CC;

#define CANDY_LOCK_IMG			"lock.png"

CandyLockCell* CandyLockCell::create(CandyIndex index)
{
	CandyLockCell *ret = new CandyLockCell();

	if(ret && ret->initWithSpriteFrameName(CANDY_LOCK_IMG) )
		{
			ret->autorelease();
			ret->index= index;
			return ret;
		}
	
	CCAssert(0, "CandyLockCell::create");
	CC_SAFE_DELETE(ret);
	return NULL;
	
}


CandyLock::CandyLock()
{
	memset(&lockInMap[0][0], 0, sizeof(CandyLockCell*) * CANDY_MAP_WIDTH * CANDY_MAP_HEIGH);
}

CandyLock::~CandyLock()
{

}


void CandyLock::createLocksWithMapData(void)
{
	for(int x=0; x<CANDY_MAP_WIDTH; x++)
		for(int y=CANDY_MAP_HEIGH-1; y>=0; y--)
			{
				if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(cIndex(x, y), MAP_CELL_LOCK))
					{
						addCandyLockCell(cIndex(x, y));
					}
			}
}

void CandyLock::addCandyLockCell(CandyIndex index)
{
	CandyLockCell* lock = CandyLockCell::create( index);
	if(lock)
		{
			lock->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(index));
			CandyManager::getInstance()->candyLayer->addToCandyBarrierTopBatchNode(lock);
			lockInMap[index.y][index.x] = lock;
		}
}

void CandyLock::removeCandyLockCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_LOCK))
		{
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_LOCK, false);
			if(lockInMap[index.y][index.x])
				{
					CandyCell *candy  = CandyManager::getInstance()->mapDataMgr->getCandyByIndex(index);
					
					CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_LOCK, 
						CandyManager::getInstance()->shareMgr->getPosByIndex(index), candy?candy->color:CANDY_COLOR_RED);	
					lockInMap[index.y][index.x]->removeFromParent();
					lockInMap[index.y][index.x] = NULL;
					CandyManager::getInstance()->effectLayer->displayBreakLock(index);
				}
		}
}

CandyLockCell* CandyLock::getLockCell(CandyIndex index)
{
	if(CandyManager::getInstance()->mapDataMgr->getMapCellStates(index, MAP_CELL_LOCK))
		return lockInMap[index.y][index.x];
	else
		return NULL;
}