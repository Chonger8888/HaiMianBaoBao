#include "CandyJelly.h"
#include "CandyManager.h"
/************************/
/*¹û¶³			        */
/***********************/
USING_NS_CC;

#define CANDY_JELLY1_IMG		"jelly1.png"
#define CANDY_JELLY2_IMG		"jelly2.png"

CandyJelly::CandyJelly()
{
	jellyTotalNum = 0;
	memset(&jellyInMap[0][0],0,sizeof(CCSprite*) * CANDY_MAP_WIDTH * CANDY_MAP_HEIGH);
}

CandyJelly::~CandyJelly()
{
	
}

void CandyJelly::createCandyJellys(void)
{	
	int jellyLayerNum;
	for(int y= 0; y < CANDY_MAP_HEIGH; y++)
		for(int x=0; x< CANDY_MAP_WIDTH; x++)
		{
			if(jellyLayerNum = getCandyJellyLayerNum(cIndex(x, y)), jellyLayerNum)
			{
				addCandyJelly(cIndex(x, y),  jellyLayerNum);
				jellyTotalNum++;
			}
		}

}

int CandyJelly::getCandyJellyRemainNum(void)
{
	int ret = 0;
	
	for(int y= 0; y < CANDY_MAP_HEIGH; y++)
		for(int x=0; x< CANDY_MAP_WIDTH; x++)
			if(getCandyJellyLayerNum( cIndex(x, y) ) )
				ret++;

	return ret;
}

int CandyJelly::getCandyJellyTotalNum(void)
{
	int jellyremainNum = getCandyJellyRemainNum();
	return jellyTotalNum > jellyremainNum?jellyTotalNum:jellyremainNum;
}

int CandyJelly::getCandyJellyLayerNum(CandyIndex index)
{
	if( CandyManager::getInstance()->mapDataMgr->getMapCellStates( index,  MAP_CELL_JELLY1))
		return 1;
	else if(CandyManager::getInstance()->mapDataMgr->getMapCellStates( index,  MAP_CELL_JELLY2))
		return 2;
	else 
		return 0;
}

bool CandyJelly::removeCandyJellyOne(CandyIndex index, bool displayScore)
{
	int jellyLayerNum = getCandyJellyLayerNum(index);
	if(jellyLayerNum == 1)
		{
			CandyManager::getInstance()->effectLayer->displayBreakJelly(index);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_JELLY1, false);
			jellyInMap[index.y][index.x]->removeFromParent();
			jellyInMap[index.y][index.x] = NULL;
		}
	else if(jellyLayerNum == 2)
		{
			CandyManager::getInstance()->effectLayer->displayBreakJelly(index,2);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_JELLY2, false);
			CandyManager::getInstance()->mapDataMgr->setMapCellStates(index, MAP_CELL_JELLY1, true);
			jellyInMap[index.y][index.x]->removeFromParent();
			addCandyJelly(index, 1);
		}
	else
		{
			return false;
		}

	if(displayScore)
		{
			CCPoint displayPos = CandyManager::getInstance()->shareMgr->getPosByIndex(index);
			CandyManager::getInstance()->scoreMgr->addCandyScore(CANDY_SCORE_JELLY, displayPos);
		}

	return true;
	
}

	
void CandyJelly::addCandyJelly(CandyIndex index, int jellyLayerNum)
{
	if(index.x <0 || index.x >=CANDY_MAP_WIDTH  || index.y <0 || index.y>= CANDY_MAP_HEIGH)
		return ;
	
	jellyInMap[index.y][index.x] = CCSprite::createWithSpriteFrameName(jellyLayerNum==1?CANDY_JELLY1_IMG:CANDY_JELLY2_IMG);
	if(jellyInMap[index.y][index.x])
		{
			jellyInMap[index.y][index.x]->setPosition(CandyManager::getInstance()->shareMgr->getPosByIndex(index));
			CandyManager::getInstance()->candyLayer->addToCandyBarrierBottomBatchNode(jellyInMap[index.y][index.x]);
		}
	
}
